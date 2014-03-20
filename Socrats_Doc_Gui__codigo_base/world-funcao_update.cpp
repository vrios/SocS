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

void World::update2_g( //update global memory
        //MainWindow *lala
        )
{
    //this->num_turnos++;
      random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
    int i, j;
    i=j=0;
    //verifica se há encontro
    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
    {
        Agents* ag1 = this->vec_ptr_Agentes[i];
        ag1->ator=true;
        ag1->ja_agiu=false;///
        this->busca_vizinho(ag1);
        //qDebug() << ag1->get_id();
        //lala->repaint();
        if (!ag1->ptrListaVizinhos.empty())
        {
            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
            ag2->outro=true;
            this->define_tipo_encontro_2_g(ag1,ag2
                                         // , lala
                                         );
            ag2->outro=false;
            ag1->ja_agiu=true;
        }
        if (ag1->ptrListaVizinhos.size()==0
                && ag1->ja_agiu==false
                )//se já varreu toda a visao e nao agiu, age neutro
        {
            this->age_soh(ag1);
            ag1->ja_agiu=true;
        }
        //lala->repaint();
        this->verifica_contorno(ag1);
        ag1->ator=false;
    }
    //qDebug() << "fim turno "<<num_turnos;

    //    for (i=0; i<this->vec_ptr_Agentes.size(); i++)
    //    {
    //        Agents* ag1 = this->vec_ptr_Agentes[i];
    //        this->verifica_contorno(ag1);
    //    }
    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts);
    this->num_turnos++;
}

void World::update2_i(//update individual memory
        //MainWindow *lala
        )
{
    //this->num_turnos++;
      random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
    int i, j;
    i=j=0;
    //verifica se há encontro
    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
    {
        Agents* ag1 = this->vec_ptr_Agentes[i];
        ag1->ator=true;
        ag1->ja_agiu=false;///
        this->busca_vizinho(ag1);
        //qDebug() << ag1->get_id();
        //lala->repaint();
        if (!ag1->ptrListaVizinhos.empty())
        {
            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
            ag2->outro=true;
            this->define_tipo_encontro_2_i(ag1,ag2
                                         // , lala
                                         );
            ag2->outro=false;
            ag1->ja_agiu=true;
        }
        if (ag1->ptrListaVizinhos.size()==0
                && ag1->ja_agiu==false
                )//se já varreu toda a visao e nao agiu, age neutro
        {
            this->age_soh(ag1);
            ag1->ja_agiu=true;
        }
        //lala->repaint();
        this->verifica_contorno(ag1);
        ag1->ator=false;
    }
    //qDebug() << "fim turno "<<num_turnos;

    //    for (i=0; i<this->vec_ptr_Agentes.size(); i++)
    //    {
    //        Agents* ag1 = this->vec_ptr_Agentes[i];
    //        this->verifica_contorno(ag1);
    //    }
    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts);
    this->num_turnos++;
}

//void World::update(
//        // class MainWindow *lala
//        )
//{
//    this->num_turnos++;
//    for (int w=0; w<this->vec_ptr_Agentes.size(); w++)
//    {   //gera a lista de vizinhos
//        Agents* ag1=this->vec_ptr_Agentes[w];
//        ag1->ja_agiu=false;///se ainda não agiu no turno
//        this->busca_vizinho(ag1);//determina quem está no raio de ação
//    }
//    int i, j;
//    i=j=0;
//    //verifica se há encontro
//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        ag1->ator=true;
//        lala->repaint();
//        if (!ag1->ptrListaVizinhos.empty())
//        {
//            Agents* ag2 = ag1->ptrListaVizinhos[0];
//            ag2->outro=true;
//            // double dist = this->distTorus(ag1, ag2,this->X);
//            this->define_tipo_encontro(ag1,ag2
//                                       , lala
//                                       );
//            ag2->outro=false;
//        }
//        if (j==ag1->ptrListaVizinhos.size()&&ag1->ja_agiu==false)//se já varreu toda a visao e nao agiu, age neutro
//        {
//            this->age_soh(ag1);
//            ag1->ja_agiu=true;
//        }
//        lala->repaint();
//        ag1->ator=false;
//    };

//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        this->verifica_contorno(ag1);

//    }
//    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts);
//  //  this->num_turnos++;
//    //this->mc1();
//    random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end());

//    if (this->num_turnos % 100 == 0)
//    {
//    //    this->mc1(0.1);
//    }
//}


//void World::update(
//        //MainWindow *lala
//        )
//{
//    this->num_turnos++;
//    random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
//    int i, j;
//    i=j=0;
//    //verifica se há encontro
//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        ag1->ator=true;
//        ag1->ja_agiu=false;///

//        this->busca_vizinho(ag1);
//        //lala->repaint();
//        if (!ag1->ptrListaVizinhos.empty())
//        {
//            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
//            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
//            ag2->outro=true;
//            this->define_tipo_encontro(ag1,ag2
//                                       // , lala
//                                       );
//            ag2->outro=false;
//            ag1->ja_agiu=true;
//        }
//        if (ag1->ptrListaVizinhos.size()==0 && ag1->ja_agiu==false)//se já varreu toda a visao e nao agiu, age neutro
//        {
//            this->age_soh(ag1);
//            ag1->ja_agiu=true;
//        }
//        //lala->repaint();
//        this->verifica_contorno(ag1);
//        ag1->ator=false;
//    };

//    //    for (i=0; i<this->vec_ptr_Agentes.size(); i++)
//    //    {
//    //        Agents* ag1 = this->vec_ptr_Agentes[i];
//    //        this->verifica_contorno(ag1);
//    //    }
//    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts);
//}

//void World::update2(
//        //MainWindow *lala
//        )
//{
//    this->num_turnos++;
//    //  random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
//    int i, j;
//    i=j=0;
//    //verifica se há encontro
//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        ag1->ator=true;
//        ag1->ja_agiu=false;///
//        this->busca_vizinho(ag1);
//        //qDebug() << ag1->get_id();
//        //lala->repaint();
//        if (!ag1->ptrListaVizinhos.empty())
//        {
//            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
//            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
//            ag2->outro=true;
//            this->define_tipo_encontro_2(ag1,ag2
//                                         // , lala
//                                         );
//            ag2->outro=false;
//            ag1->ja_agiu=true;
//        }
//        if (ag1->ptrListaVizinhos.size()==0
//                && ag1->ja_agiu==false
//                )//se já varreu toda a visao e nao agiu, age neutro
//        {
//            this->age_soh(ag1);
//            ag1->ja_agiu=true;
//        }
//        //lala->repaint();
//        this->verifica_contorno(ag1);
//        ag1->ator=false;
//    }
//    //qDebug() << "fim turno "<<num_turnos;

//    //    for (i=0; i<this->vec_ptr_Agentes.size(); i++)
//    //    {
//    //        Agents* ag1 = this->vec_ptr_Agentes[i];
//    //        this->verifica_contorno(ag1);
//    //    }
//    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts);
//}
