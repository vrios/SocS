#include "world.h"
#include <cstdlib>
#include <algorithm>
#include <QDebug>

////C++11 não possui M_PI definido, por isso o bloco abaixo
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


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

    //povoa os quadrats para facilitar busca pelos individuos
    this->lado_quad = this->raio_medio;//largura do quadrat = raio
    this->n_quad_lado = (int)this->X/lado_quad; //numero de quadrats por lado
    this->n_quad_total = this->n_quad_lado * this->n_quad_lado;//construção dos qudrats
    this->povoa_quadrats();

    this->Eps=Eps;
    this->MinPts=MinPts;
    this->num_turnos=0;
    this->map_of_clusters.insert(make_pair(0,  map<int,Agents*> ()));
    this->time_series_of_clusters.push_back(vector<vector<int> > ());

    //cria rede que vai armazenar interaç?es espaciais
    this->spatial_network.clear();
    vector<int> temp(N_agentes, 0);
    spatial_network.assign(N_agentes,temp);

    //cria rede que vai armazenar interaç?es sociais
    this->social_network.clear();
    vector<int>temps(N_agentes,-9);
    vector<vector<int> > temps2 (N_agentes,temps);
    this->social_network.assign(interacoes,temps2);


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


void World::busca_vizinho(Agents* ag1)//preenche a lista de vizinhos e passa para o agente i
{
    //Agents* ag1=this->vec_ptr_Agentes[i];
    vector <Agents*> listViz;
    // ag1->clearptrListaVizinhos();
    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
    {
        //vai de vizinho em vizinho
        Agents* ag2= this->vec_ptr_Agentes[j];
        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
        double d=this->distTorus(ag1,ag2, this->X);
        if (d<=ag1->get_raio())
        {listViz.push_back(ag2);}
    }
    ag1->setptrListaVizinhos(listViz);
}



void World::define_tipo_encontro_2_g(Agents* ator, Agents* outro
                                     //, MainWindow* lala
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
                       );
        //qDebug()<<"afiliativo";
        ator->ja_agiu=true;
        this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if (p>af_ator && p<=(af_ator+ag_ator))
    {
        ator->registra_mem_g(outro_id,-1);//agonistic
        outro->registra_mem_g(ator_id,-1);//agonistic
        this->afasta(ator, outro
                     //,lala
                     );
        //qDebug()<<"agonistico";
        ator->ja_agiu=true;
         this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if(p>ag_ator+af_ator)
    {
        ator->registra_mem_g(outro_id,0);//neutro
        outro->registra_mem_g(ator_id,0);//neutro
        this->age_soh(ator);
        ator->ja_agiu=true;
         this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
}

void World::define_tipo_encontro_2_i(Agents* ator, Agents* outro
                                     //, MainWindow* lala
                                     )
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
                       );
        //qDebug()<<"afiliativo";
        ator->ja_agiu=true;
         this->social_network[this->num_turnos][ator_id][outro_id]=1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if (p>af_ator && p<=(af_ator+ag_ator))
    {
        ator->registra_mem_i(outro_id,-1);//agonistico
        outro->registra_mem_i(ator_id,-1);//afiliativo
        this->afasta(ator, outro
                     //,lala
                     );
        //qDebug()<<"agonistico";
        ator->ja_agiu=true;
         this->social_network[this->num_turnos][ator_id][outro_id]=-1; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
    if(p>ag_ator+af_ator)
    {
        ator->registra_mem_i(outro_id,0);//neutro
        outro->registra_mem_i(ator_id,0);//afiliativo
        this->age_soh(ator);
        ator->ja_agiu=true;
         this->social_network[this->num_turnos][ator_id][outro_id]=0; //this->social_network[this->num_turnos] tamanho é veirificado no world_update
    }
}



void World::age_soh(Agents* ator)
{
    //qDebug()<<"age soh";
    ator->anda();
    this->verifica_contorno(ator);

}

void World::neutro(Agents* ator, Agents* outro)
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
                       )
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
                       )
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
                     )
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
    //    ator->set_angulo(alfa);//vira na direção do outro
    //    //      lala->repaint();

    //    dx = ator->get_passo() * cos(ator->get_angulo());
    //    dy = ator->get_passo() * sin(ator->get_angulo());
    //    ator->set_x(ator->get_x()+dx);
    //    ator->set_y(ator->get_y()+dy);
    //lala->repaint();


    //    outro->set_angulo(beta);//vira na direção do ator
    //    //    lala->repaint();
    //    dx = outro->get_passo()* (cos(outro->get_angulo()));
    //    dy = outro->get_passo()* (sin(outro->get_angulo())); // anda
    //    outro->set_x(outro->get_x()+dx);
    //    outro->set_y(outro->get_y()+dy);

}

void World::afasta(Agents* ator, Agents* outro
                   //,MainWindow *lala
                   )
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
    //    ator->set_angulo(M_PI-alfa);//vira na direção oposta ao outro
    //    //      lala->repaint();
    //    outro->set_angulo(M_PI-beta);//vira na direção oposta ao ator
    //    //     lala->repaint();
    //    dx = ator->get_passo() * cos(ator->get_angulo());
    //    dy = ator->get_passo() * sin(ator->get_angulo());
    //    ator->set_x(ator->get_x()+dx);
    //    ator->set_y(ator->get_y()+dy);
    //    //  lala->repaint();
    //    //verificar
    //    dx = outro->get_passo()* (cos(outro->get_angulo()));//
    //    dy = outro->get_passo()* (sin(outro->get_angulo())); // anda

    //    outro->set_x(outro->get_x()+dx);
    //    outro->set_y(outro->get_y()+dy);
    //lala->repaint();

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

//void World::define_tipo_encontro(Agents* ator, Agents* outro
//                                // , MainWindow *lala
//                                 )
//{
//    //probabilidades de ação sao um distribuidas em um simplex, com af+ag+an=1, portanto, estrutura nova do codigo
//    // neste caso, o encontro é simétrico qnto ao tipo de ação, q é determinado pela memória do ator
//    //ator; indivíduo que percebe a presença do busca_vizinho e reage a ele
//    // outro;

//    //    double ag_ator; double af_ator; double an_ator;

//    //       ag_ator = (ator->get_ag() + ator->get_mod_ag(outro->get_id()) - (ator->get_mod_af(outro->get_id())/2) - (ator->get_mod_an(outro->get_id())/2));
//    //       af_ator = (ator->get_af() + ator->get_mod_af(outro->get_id()) - (ator->get_mod_ag(outro->get_id())/2) - (ator->get_mod_an(outro->get_id())/2));
//    //       an_ator = (ator->get_an() + ator->get_mod_an(outro->get_id()) - (ator->get_mod_af(outro->get_id())/2) - (ator->get_mod_ag(outro->get_id())/2));

//    //       double p =0;
//    //       p = ((double)rand()/RAND_MAX);

//    //       if (p<=ag_ator)
//    //       {this->agonistico(ator, outro
//    //                         //,lala
//    //                         );}
//    //       if (p>ag_ator && p<=(ag_ator+af_ator))
//    //       {this->afiliativo(ator, outro
//    //                         , lala
//    //                         );}
//    //       if(p>ag_ator+af_ator)
//    //       {this->neutro(ator, outro);}


//    //    double ag_ator; double af_ator; double an_ator;

//    //    ag_ator = (ator->get_prob_Init('g') + ator->get_mod_mem(outro->get_id(), 'g') - (ator->get_mod_mem(outro->get_id(), 'f')/2) - (ator->get_mod_mem(outro->get_id(), 'n')/2));
//    //    af_ator = (ator->get_prob_Init('f') + ator->get_mod_mem(outro->get_id(), 'f') - (ator->get_mod_mem(outro->get_id(), 'g')/2) - (ator->get_mod_mem(outro->get_id(), 'n')/2));
//    //    an_ator = (ator->get_prob_Init('n') + ator->get_mod_mem(outro->get_id(), 'n') - (ator->get_mod_mem(outro->get_id(), 'f')/2) - (ator->get_mod_mem(outro->get_id(), 'g')/2));

//    //    double p =0;
//    //    p = ((double)rand()/RAND_MAX);

//    //    if (p<=ag_ator)
//    //    {this->agonistico(ator, outro
//    //                      //,lala
//    //                      );}
//    //    if (p>ag_ator && p<=(ag_ator+af_ator))
//    //    {this->afiliativo(ator, outro
//    //                      , lala
//    //                      );}
//    //    if(p>ag_ator+af_ator)
//    //    {this->neutro(ator, outro);}

//    double ag_ator; double af_ator; double an_ator;

//    ag_ator = (ator->get_prob_Init('g') + ator->get_mod_mem(outro->get_id(), 'g') - (ator->get_mod_mem(outro->get_id(), 'f')/2) - (ator->get_mod_mem(outro->get_id(), 'n')/2));
//    af_ator = (ator->get_prob_Init('f') + ator->get_mod_mem(outro->get_id(), 'f') - (ator->get_mod_mem(outro->get_id(), 'g')/2) - (ator->get_mod_mem(outro->get_id(), 'n')/2));
//    an_ator = (ator->get_prob_Init('n') + ator->get_mod_mem(outro->get_id(), 'n') - (ator->get_mod_mem(outro->get_id(), 'f')/2) - (ator->get_mod_mem(outro->get_id(), 'g')/2));

//    double p =0;
//    p = ((double)rand()/RAND_MAX);

//    if (p<=ag_ator)
//    {this->agonistico(ator, outro
//                      //,lala
//                      );}
//    if (p>ag_ator && p<=(ag_ator+af_ator))
//    {this->afiliativo(ator, outro
//                      //, lala
//                      );}
//    if(p>ag_ator+af_ator)
//    {this->neutro(ator, outro);}

//}


//void World::define_tipo_encontro_2(Agents* ator, Agents* outro
//                                   //, MainWindow* lala
//                                   )
//{
//    //qDebug()<<"Define";
//    //ator->get_mem(outro->get_id()).af;
//    double af_ator = ator->get_mem(outro->get_id()).af;
//    double ag_ator = ator->get_mem(outro->get_id()).ag;
//    double an_ator = ator->get_mem(outro->get_id()).an;


//    double p =0;

//    p = ((double)rand()/RAND_MAX);

//    if (p<=af_ator)
//    {
//        ator->registra_mem(outro->get_id(),1);//afiliativo
//        outro->registra_mem(ator->get_id(),1);//afiliativo
//        this->aproxima(ator, outro
//                      // ,lala
//                       );
//        //qDebug()<<"afiliativo";
//        ator->ja_agiu=true;
//    }
//    if (p>af_ator && p<=(af_ator+ag_ator))
//    {
//        ator->registra_mem(outro->get_id(),-1);//agonistic
//        outro->registra_mem(ator->get_id(),-1);//afiliativoo
//        this->afasta(ator, outro
//                     //,lala
//                     );
//        //qDebug()<<"agonistico";
//        ator->ja_agiu=true;
//    }
//    if(p>ag_ator+af_ator)
//    {
//        ator->registra_mem(outro->get_id(),0);//neutro
//        outro->registra_mem(ator->get_id(),0);//afiliativo
//        this->age_soh(ator);
//        ator->ja_agiu=true;
//    }
//}

//double World::calc_mc()
//{
//    //vou definir o numero de quadrados como sendo o lado do mundo dividido pelo raio de ação
//    //variáveis auxiliares para calculo do mean crowding
//    double mean_crowding =0;
//    double var=0;//variancia

//    double densidade_media=0; //média da população dos quadrats

//    //calcular media e variancia p calc do mean crowding
//    densidade_media = this->media_pop();
//    this->povoa_quadrats();
//    //calculo da variancia

//    var = this->variancia();

//    //calculo do mean crowding
//    mean_crowding = densidade_media + ( (var/densidade_media) -1 ) ;
//    return mean_crowding;
//}

//double World::media_pop()
//{
//    double pop=0;
//    for (int i=0; i<this->quadrats.size();i++)
//    {
//        for (int j= 0; j<this->quadrats.size();j++)
//        {
//            pop += this->quadrats[i][j];
//        }
//    }

//    return (pop / this->n_quad_total);

//}
//double World::variancia()
//{
//    double somaDosQuadrados=0;//soma do quadrado das diferencias entre a média e a pop d cada quadrat
//    for ( int i=0; i<this->n_quad_lado; i++)//linhas
//    {
//        for ( int j=0; j<(this->n_quad_lado); j++)//colunas
//        {
//            somaDosQuadrados += ((this->quadrats[i][j] - this->media_pop()) * (this->quadrats[i][j] - this->media_pop()));
//        }
//    }

//    return(somaDosQuadrados / this->n_quad_total);
//}

void World::povoa_quadrats()
{
    //    this->quadrats.clear();//limpa para repovoar
    //    vector <int> aux;
    //    aux.clear();
    //    aux.assign(this->n_quad_lado,0);
    //    this->quadrats.assign(this->n_quad_lado,aux);
    //    int idx=0;
    //    int idy=0;
    //    for(unsigned int g=0;g<this->vec_ptr_Agentes.size();g++)
    //    {
    //        idx=(int)((this->get_agente(g)->get_x())/this->lado_quad); //o valor inteiro da divisao é o indice que se refere ao numero do quadrat na dimensao x
    //        idy=(int)((this->get_agente(g)->get_y())/this->lado_quad);//o valor inteiro da divisao é o indice que se refere ao numero do quadrat na dimensao y
    //        this->quadrats[idx][idy]++;//adiciona um individuo ao quadrat em questao
    //    }

}
