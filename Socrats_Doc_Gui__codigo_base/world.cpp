#include "world.h"
#include <cstdlib>
#include <algorithm>
#include <QDebug>
#include <math.h>
////C++11 não possui M_PI definido, por isso o bloco abaixo
#define _USE_MATH_DEFINES

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <limits>
World::World()
{
}

World::World(double TAM, int N_agentes, int raio, double Eps, int MinPts, int mem_length, int mem_type, int interacoes)
{
    this->X=this->Y=TAM;
    this->raio_medio=raio;
    for (int i=0; i<N_agentes; i++)
    {
        //cria N agentes
        this->vec_ptr_Agentes.push_back(new Agents (i,
                                                    (double) rand() / RAND_MAX * this->X,
                                                    (double) rand() / RAND_MAX * this->Y,
                                                    (double) rand() / RAND_MAX * 360,
                                                    (double)1/3,
                                                    (double)1/3,
                                                    (double)1/3,
                                                    N_agentes,
                                                    raio,
                                                    mem_length,
                                                    mem_type
                                                    )
                                        );
        //qDebug()<<"gera agente mem_length ="<<mem_length;
    }


    this->Eps=Eps;
    this->MinPts=MinPts;
    this->num_turnos=0;
    this->map_of_clusters.insert(make_pair(0,  map<int,Agents*> ()));
    this->time_series_of_clusters.push_back(vector<vector<int> > ());
    this->time_series_of_clusters.resize(interacoes);

    //cria rede que vai armazenar interaç?es espaciais
    this->spatial_network.clear();
    vector<int> temp(N_agentes, 0);
    spatial_network.assign(N_agentes,temp);

  //  cria rede que vai armazenar interaç?es sociais
    this->cumulative_interactions.clear();
    vector<int>temps1(N_agentes,0);
    this->cumulative_interactions.assign(N_agentes,temps1);
//    this->total_interactions.clear();
//    vector<int>z(N_agentes,0);
//    this->total_interactions.assign(N_agentes,z);

    this->social_network.clear();
    vector<int>a(N_agentes,0);
    vector<vector<int> > b (N_agentes,a);
    this->social_network.assign(interacoes,b);


}

World::~World()
{
    while(!vec_ptr_Agentes.empty())
    {
        delete vec_ptr_Agentes.back();
        vec_ptr_Agentes.pop_back();
    }
    this->vec_ptr_Agentes.clear();
}


void World::busca_vizinho(Agents* ag1, space &MySpace)//preenche a lista de vizinhos e passa para o agente i
{

    //    vector <Agents*> listViz;

    //    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
    //    {
    //        //vai de vizinho em vizinho
    //        Agents* ag2= this->vec_ptr_Agentes[j];
    //        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
    //        double d=this->distTorus(ag1,ag2, this->X);
    //        if (d<=ag1->get_raio())
    //        {listViz.push_back(ag2);}
    //    }
    //    ag1->setptrListaVizinhos(listViz);
    vector <Agents*> listViz = MySpace.Range_query(ag1,this->raio_medio, *this);
    ag1->setptrListaVizinhos(listViz);

}



void World::define_tipo_encontro_2_g(Agents* ator, Agents* outro
                                     //, MainWindow* lala
                                     ,space &MySpace
                                     )
{
    //qDebug()<<"Define";
    //ator->get_mem(outro->get_id()).af;
    double af_ator = ator->get_mem_g(outro->get_id()).af;
    double ag_ator = ator->get_mem_g(outro->get_id()).ag;
    double an_ator = ator->get_mem_g(outro->get_id()).an;

    int ator_id = ator->get_id();
    int outro_id=outro->get_id();


    double p =0;

    p = ((double)rand()/RAND_MAX);

    if (p<=af_ator)
    {
        ator->registra_mem_g(outro_id,1);//afiliativo
        outro->registra_mem_g(ator_id,1);//afiliativo
        this->aproxima(ator, outro
                       // ,lala
                      , MySpace );
        //qDebug()<<"afiliativo";
        ator->ja_agiu=true;
        this->cumulative_interactions[ator_id][outro_id]++;
      //  this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if (p>af_ator && p<=(af_ator+ag_ator))
    {
        ator->registra_mem_g(outro_id,-1);//agonistic
        outro->registra_mem_g(ator_id,-1);//agonistic
        this->afasta(ator, outro
                     //,lala
                     , MySpace);
        //qDebug()<<"agonistico";
        ator->ja_agiu=true;
        this->cumulative_interactions[ator_id][outro_id]--;
       // this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if(p>ag_ator+af_ator)
    {
        ator->registra_mem_g(outro_id,0);//neutro
        outro->registra_mem_g(ator_id,0);//neutro
        this->age_soh(ator, MySpace);
        ator->ja_agiu=true;
     //   this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
}

void World::define_tipo_encontro_2_i(Agents* ator, Agents* outro
                                     //, MainWindow* lala
                                     , space &MySpace)
{
    //qDebug()<<"Define";
    //ator->get_mem(outro->get_id()).af;
    //  Agents::mod aa =ator->get_mem_i(outro->get_id());
    //double a= (double) ator->get_mem_i(outro->get_id()).af;
    double af_ator = ator->get_mem_i(outro->get_id()).af;
    double ag_ator = ator->get_mem_i(outro->get_id()).ag;
    double an_ator = ator->get_mem_i(outro->get_id()).an;

    int ator_id = ator->get_id();
    int outro_id=outro->get_id();

    double p =0;
    p = ((double)rand()/RAND_MAX);
    if (p<=af_ator)
    {
        ator->registra_mem_i(outro_id,1);//afiliativo
        outro->registra_mem_i(ator_id,1);//afiliativo
        this->aproxima(ator, outro
                       // ,lala
                       , MySpace);
        //qDebug()<<"afiliativo";
        ator->ja_agiu=true;
        this->cumulative_interactions[ator_id][outro_id]++;
      //  this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if (p>af_ator && p<=(af_ator+ag_ator))
    {
        ator->registra_mem_i(outro_id,-1);//agonistico
        outro->registra_mem_i(ator_id,-1);//afiliativo
        this->afasta(ator, outro
                     //,lala
                     , MySpace);
        //qDebug()<<"agonistico";
        ator->ja_agiu=true;
        this->cumulative_interactions[ator_id][outro_id]--;
     //   this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if(p>ag_ator+af_ator)
    {
        ator->registra_mem_i(outro_id,0);//neutro
        outro->registra_mem_i(ator_id,0);//afiliativo
        this->age_soh(ator, MySpace);
        ator->ja_agiu=true;
    //    this->total_interactions[ator_id][outro_id]++;
        this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
}



void World::age_soh(Agents* ator, space &MySpace)
{
    //qDebug()<<"age soh";
    ator->anda();
    this->verifica_contorno(ator);
    MySpace.move__on_grid(ator);

}

void World::neutro(Agents* ator, Agents* outro, space &MySpace)
{

    //    //    //memoriza a ação
    //    //    ator->set_mod_an(outro->get_id(), 0.001);
    //    //    ator->set_mod_af(outro->get_id(),0.0005);
    //    //    ator->set_mod_ag(outro->get_id(),0.0005);
    //    ator->set_sum_an(outro->get_id());

    //    //    outro->set_mod_an(ator->get_id(),0.001);
    //    //    outro->set_mod_af(ator->get_id(),0.0005);
    //    //    outro->set_mod_ag(ator->get_id(),0.0005);
    //    outro->set_sum_an(ator->get_id());
    //    //    //limita os valores da memoria do ator
    //    //    if (ator->get_prob_Init('n')+ator->get_mod_mem(outro->get_id(), 'n')>01)
    //    //    {ator->set_mod_an(outro->get_id(),(0.99999-ator->get_prob_Init('n')));}
    //    //    if (ator->get_prob_Init('f')+ator->get_mod_mem(outro->get_id(), 'f')<=0)
    //    //    {ator->set_mod_af(outro->get_id(),0.0001);}
    //    //    if (ator->get_prob_Init('g')+ator->get_mod_mem(outro->get_id(), 'g')<=0)
    //    //    {ator->set_mod_ag(outro->get_id(),0.0001);}

    //    //    //limita os valores da memoria do outro
    //    //    if (outro->get_prob_Init('n')+outro->get_mod_an(ator->get_id())>1)
    //    //    {outro->set_mod_an(ator->get_id(),(0.99999-outro->get_prob_Init('n')));}
    //    //    if (outro->get_prob_Init('f')+outro->get_mod_af(ator->get_id())<=0)
    //    //    {outro->set_mod_af(ator->get_id(),0.0001);}
    //    //    if (outro->get_prob_Init('g')+outro->get_mod_ag(ator->get_id())<=0)
    //    //    {outro->set_mod_ag(ator->get_id(),0.0001);}

    //    this->age_soh(ator);
    //    ator->ja_agiu=true;
}

void World::agonistico(Agents* ator, Agents* outro
                       // ,MainWindow *lala
                       , space &MySpace)
{

    //    //    //memoriza a ação
    //    //    ator->set_mod_ag(outro->get_id(),0.001);
    //    //    ator->set_mod_af(outro->get_id(),0.0005);
    //    //    ator->set_mod_an(outro->get_id(),0.0005);
    //    ator->set_sum_ag(outro->get_id());
    //    //    outro->set_mod_ag(ator->get_id(),0.001);
    //    //    outro->set_mod_af(ator->get_id(),0.0005);
    //    //    outro->set_mod_an(ator->get_id(),0.0005);
    //    outro->set_sum_ag(ator->get_id());
    //    //    //limita os valores da memoria do ator
    //    //    if (ator->get_prob_Init('g')+ator->get_mod_mem(outro->get_id(), 'g')>01)
    //    //    {ator->set_mod_ag(outro->get_id(),(0.99999-ator->get_prob_Init('g')));}
    //    //    if (ator->get_prob_Init('f')+ator->get_mod_mem(outro->get_id(), 'f')<=0)
    //    //    {ator->set_mod_af(outro->get_id(),0.0001);}
    //    //    if (ator->get_prob_Init('n')+ator->get_mod_mem(outro->get_id(), 'n')<=0)
    //    //    {ator->set_mod_an(outro->get_id(),0.0001);}

    //    //    //limita os valores da memoria do outro
    //    //    if (outro->get_prob_Init('g')+outro->get_mod_ag(ator->get_id())>1)
    //    //    {outro->set_mod_ag(ator->get_id(),(0.99999-outro->get_prob_Init('g')));}
    //    //    if (outro->get_prob_Init('f')+outro->get_mod_af(ator->get_id())<=0)
    //    //    {outro->set_mod_af(ator->get_id(),0.0001);}
    //    //    if (outro->get_prob_Init('n')+outro->get_mod_an(ator->get_id())<=0)
    //    //    {outro->set_mod_an(ator->get_id(),0.0001);}

    //    afasta(ator, outro
    //          //,lala
    //           );
    //    ator->ja_agiu=true;
}

void World::afiliativo(Agents* ator, Agents* outro
                       //, MainWindow *lala
                       , space &MySpace)
{

    //    //    //memoriza a ação
    //    //    ator->set_mod_af(outro->get_id(), 0.001);
    //    //    ator->set_mod_ag(outro->get_id(),0.0005);
    //    //    ator->set_mod_an(outro->get_id(),0.0005);
    //    ator->set_sum_an(outro->get_id());

    //    //    outro->set_mod_af(ator->get_id(),0.001);
    //    //    outro->set_mod_ag(ator->get_id(),0.0005);
    //    //    outro->set_mod_an(ator->get_id(),0.0005);
    //    outro->set_sum_ag(ator->get_id());

    //    //    //limita os valores da memoria do ator
    //    //    if (ator->get_prob_Init('f')+ator->get_mod_mem(outro->get_id(), 'f')>01)
    //    //    {ator->set_mod_af(outro->get_id(),(0.99999-ator->get_prob_Init('f')));}
    //    //    if (ator->get_prob_Init('g')+ator->get_mod_mem(outro->get_id(), 'g')<=0)
    //    //    {ator->set_mod_ag(outro->get_id(),0.0001);}
    //    //    if (ator->get_prob_Init('n')+ator->get_mod_mem(outro->get_id(), 'n')<=0)
    //    //    {ator->set_mod_an(outro->get_id(),0.0001);}

    //    //    //limita os valores da memoria do outro
    //    //    if (outro->get_prob_Init('f')+outro->get_mod_af(ator->get_id())>1)
    //    //    {outro->set_mod_af(ator->get_id(),(0.99999-outro->get_prob_Init('f')));}
    //    //    if (outro->get_prob_Init('g')+outro->get_mod_ag(ator->get_id())<=0)
    //    //    {outro->set_mod_ag(ator->get_id(),0.0001);}
    //    //    if (outro->get_prob_Init('n')+outro->get_mod_an(ator->get_id())<=0)
    //    //    {outro->set_mod_an(ator->get_id(),0.0001);}

    //    aproxima(ator, outro
    //             //, lala
    //             );
    //    ator->ja_agiu=true;
}


void World::aproxima(Agents* ator, Agents* outro
                     //, MainWindow* lala
                     , space &MySpace)
{
    //qDebug()<<"aproxima";
    double alfa, beta, adx, ady, odx,ody;//,dx, dy;
    //calculo das distancias lineares em cada eixo
    adx = ator->get_x() - outro->get_x();
    ady = ator->get_y()- outro->get_y();
    odx = outro->get_x()- ator->get_x();
    ody = outro->get_y()- ator->get_y();
    //calculo dos angulos entre os individuos
    alfa = atan2(ady,adx);
    beta = atan2 (ody,odx);

    ator->anda(alfa);
    this->verifica_contorno(ator);
    outro->anda(beta);
    this->verifica_contorno(outro);

    MySpace.move__on_grid(ator);

}

void World::afasta(Agents* ator, Agents* outro
                   //,MainWindow *lala
                   , space &MySpace)
{
    //qDebug()<<"afasta";
    double alfa, beta, adx, ady, odx,ody;
    //calculo das distancias lineares em cada eixo
    adx = ator->get_x() - outro->get_x();
    ady = ator->get_y()- outro->get_y();
    odx = outro->get_x()- ator->get_x();
    ody = outro->get_y()- ator->get_y();
    //calculo dos angulos entre os individuos
    alfa = atan2(ady,adx);
    beta = atan2 (ody,odx);

    ator->anda(M_PI-alfa);
    this->verifica_contorno(ator);
    outro->anda(M_PI-beta);
    this->verifica_contorno(outro);
    MySpace.move__on_grid(ator);
    MySpace.move__on_grid(outro);

}

void World::verifica_contorno( Agents* ag)
{
    double ax,ay;
    ax=ag->get_x();
    ay=ag->get_y();
    if(ag->get_x()<0)       {ag->set_x(ax + this->X);}
    if(ag->get_x()>this->X) {ag->set_x(ax - this->X);}
    if(ag->get_y()<0)       {ag->set_y(ay + this->Y);}
    if(ag->get_y()>this->Y) {ag->set_y(ay - this->Y);}
}

double World::distTorus(Agents* a1, Agents* a2, int tam) // Considerando o toroide
{
    double x1=a1->get_x();
    double x2=a2->get_x();
    double y1=a1->get_y();
    double y2=a2->get_y();

    double dMin= sqrt(
                min(abs(x1 - x2), tam - abs(x1 - x2)) * min(abs(x1 - x2), tam - abs(x1 - x2))
                +
                min(abs(y1 - y2), tam - abs(y1 - y2)) * min(abs(y1 - y2), tam - abs(y1 - y2))
                );
    return dMin;

}

double World::distEuclidean(Agents* a1, Agents* a2)
{
    double x1=a1->get_x();
    double x2=a2->get_x();
    double y1=a1->get_y();
    double y2=a2->get_y();
    double dMin= sqrt((x1 - x2) *(x1 - x2)+(y1 - y2)*(y1 - y2));
    return dMin;
}

