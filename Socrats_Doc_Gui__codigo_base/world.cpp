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

World::World(double TAM, int N_agentes, int raio, double Eps, int MinPts, int mem_length, int mem_type, double mem_mod, int interacoes, int numRep)
{
    this->numRep=numRep;
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

    while(!vec_ptr_vizinhos.empty())
    {
        delete vec_ptr_vizinhos.back();
        vec_ptr_vizinhos.pop_back();
    }
    this->vec_ptr_vizinhos.clear();

    spatial_network.clear();
    cumulative_interactions.clear();
    total_interactions.clear();
    social_network.clear();
    time_series_of_clusters.clear();
    map_of_clusters.clear();

}


void World::busca_vizinho(Agents* ag1, space &MySpace)//preenche a lista de vizinhos e passa para o agente i
{
   vector <Agents*> listViz = MySpace.Range_query(ag1,this->raio_medio, *this);
    ag1->setptrListaVizinhos(listViz);

}


//void World::define_tipo_encontro_2_g(Agents* ator, Agents* outro
//                                     //, MainWindow* lala
//                                     ,space &MySpace
//                                     )
//{
//    //qDebug()<<"Define";
//    //ator->get_mem(outro->get_id()).af;
//    //    double af_ator = ator->get_mem_g(outro->get_id()).af;
//    //    double ag_ator = ator->get_mem_g(outro->get_id()).ag;
//    //    double an_ator = ator->get_mem_g(outro->get_id()).an;

//    Agents::mod mods =ator->get_mem_g(outro->get_id());

//    double af_ator = mods.af;
//    double ag_ator = mods.ag;
//    double an_ator = mods.an;

//    int ator_id = ator->get_id();
//    int outro_id=outro->get_id();


//    double p =0;

//    p = ((double)rand()/RAND_MAX);

//    if (p<=af_ator)
//    {
//        ator->registra_mem_g(outro_id,1);//afiliativo
//        outro->registra_mem_g(ator_id,1);//afiliativo
//        this->aproxima(ator, outro
//                       // ,lala
//                       , MySpace );
//        //qDebug()<<"afiliativo";
//        ator->ja_agiu=true;
//        this->cumulative_interactions[ator_id][outro_id]++;
//        //  this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//    if (p>af_ator && p<=(af_ator+ag_ator))
//    {
//        ator->registra_mem_g(outro_id,-1);//agonistic
//        outro->registra_mem_g(ator_id,-1);//agonistic
//        this->afasta(ator, outro
//                     //,lala
//                     , MySpace);
//        //qDebug()<<"agonistico";
//        ator->ja_agiu=true;
//        this->cumulative_interactions[ator_id][outro_id]--;
//        // this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//    if(p>ag_ator+af_ator)
//    {
//        ator->registra_mem_g(outro_id,0);//neutro
//        outro->registra_mem_g(ator_id,0);//neutro
//        this->age_soh(ator, MySpace);
//        ator->ja_agiu=true;
//        //   this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//}

//void World::define_tipo_encontro_2_i(Agents* ator, Agents* outro
//                                     //, MainWindow* lala
//                                     , space &MySpace)
//{
//    //qDebug()<<"Define";
//    //ator->get_mem(outro->get_id()).af;

//    //      double q = aa.af;
//    //      double r = aa.ag;
//    //      double s = aa.an;
//    //    //double a= (double) ator->get_mem_i(outro->get_id()).af;
//    //    double af_ator = ator->get_mem_i(outro->get_id()).af;
//    //    double ag_ator = ator->get_mem_i(outro->get_id()).ag;
//    //    double an_ator = ator->get_mem_i(outro->get_id()).an;

//    Agents::mod mods =ator->get_mem_i(outro->get_id());

//    double af_ator = mods.af;
//    double ag_ator = mods.ag;
//    double an_ator = mods.an;

//    int ator_id = ator->get_id();
//    int outro_id=outro->get_id();

//    double p =0;
//    p = ((double)rand()/RAND_MAX);
//    if (p<=af_ator)
//    {
//        ator->registra_mem_i(outro_id,1);//afiliativo
//        outro->registra_mem_i(ator_id,1);//afiliativo
//        this->aproxima(ator, outro
//                       // ,lala
//                       , MySpace);
//        //qDebug()<<"afiliativo";
//        ator->ja_agiu=true;
//        this->cumulative_interactions[ator_id][outro_id]++;
//        //  this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//    if (p>af_ator && p<=(af_ator+ag_ator))
//    {
//        ator->registra_mem_i(outro_id,-1);//agonistico
//        outro->registra_mem_i(ator_id,-1);//afiliativo
//        this->afasta(ator, outro
//                     //,lala
//                     , MySpace);
//        //qDebug()<<"agonistico";
//        ator->ja_agiu=true;
//        this->cumulative_interactions[ator_id][outro_id]--;
//        //   this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//    if(p>ag_ator+af_ator)
//    {
//        ator->registra_mem_i(outro_id,0);//neutro
//        outro->registra_mem_i(ator_id,0);//afiliativo
//        this->age_soh(ator, MySpace);
//        ator->ja_agiu=true;
//        //    this->total_interactions[ator_id][outro_id]++;
//        this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
//    }
//}


void World::define_tipo_encontro(Agents* ator, Agents* outro,space &MySpace)
{
    Agents::mod mods;

    mods = ator->get_mem(outro->get_id());
    double af_ator = mods.af;
    double ag_ator = mods.ag;
    double an_ator = mods.an;

    int ator_id = ator->get_id();
    int outro_id=outro->get_id();

    double p = ((double)rand()/RAND_MAX);

        if (p<=af_ator)
        {
            ator->set_mem(outro_id,1);//afiliativo
            outro->set_mem(ator_id,1);//afiliativo
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
            ator->set_mem(outro_id,-1);//agonistic
            outro->set_mem(ator_id,-1);//agonistic
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
            ator->set_mem(outro_id,0);//neutro
            outro->set_mem(ator_id,0);//neutro
            this->age_soh(ator, MySpace);
            ator->ja_agiu=true;
            //   this->total_interactions[ator_id][outro_id]++;
            this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
        }

}

void World::age_soh(Agents* ator, space &MySpace)
{
    //qDebug()<<"age soh";
    ator->anda();
    this->verifica_contorno(ator);
    MySpace.move_on_grid(ator);

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

    MySpace.move_on_grid(ator);

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
    MySpace.move_on_grid(ator);
    MySpace.move_on_grid(outro);

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

