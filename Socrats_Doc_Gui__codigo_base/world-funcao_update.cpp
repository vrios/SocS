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

//void World::update2_g(//update global memory
//                       //MainWindow *lala
//                       space &MySpace
//                       )
//{/*
//    //this->num_turnos++;
//    random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
//    int i, j;
//    i=j=0;
//    //verifica se há encontro
//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        ag1->ator=true;
//        ag1->ja_agiu=false;///
//        this->busca_vizinho(ag1,MySpace);
//        //qDebug() << ag1->get_id();
//        //lala->repaint();
//        if (!ag1->ptrListaVizinhos.empty())
//        {
//            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
//            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
//            ag2->outro=true;
//            this->define_tipo_encontro_2_g(ag1,ag2
//                                           // , lala
//                                           ,MySpace
//                                           );
//            ag2->outro=false;
//            ag1->ja_agiu=true;
//        }
//        if (ag1->ptrListaVizinhos.size()==0
//                && ag1->ja_agiu==false
//                )//se já varreu toda a visao e nao agiu, age neutro
//        {
//            this->age_soh(ag1,MySpace);
//            ag1->ja_agiu=true;
//        }
//        //lala->repaint();
//        this->verifica_contorno(ag1);
//        ag1->ator=false;
//    }
//    //qDebug() << "fim turno "<<num_turnos;

//    this->DBSCAN(
//                this->vec_ptr_Agentes,
//                this->Eps,
//                this->MinPts,
//                MySpace);
//    this->num_turnos++;*/
//}

//void World::update2_i(//update individual memory
//                      //MainWindow *lala
//                      space &MySpace
//                      )
//{/*
//    //this->num_turnos++;
//    random_shuffle(this->vec_ptr_Agentes.begin(),this->vec_ptr_Agentes.end()); // aleatoriza ordem das ações
//    int i, j;
//    i=j=0;
//    //verifica se há encontro
//    for (i=0; i<this->vec_ptr_Agentes.size(); i++)//vai de agente em agente
//    {
//        Agents* ag1 = this->vec_ptr_Agentes[i];
//        ag1->ator=true;
//        ag1->ja_agiu=false;///
//        this->busca_vizinho(ag1,MySpace);
//        //qDebug() << ag1->get_id();
//        //lala->repaint();
//        if (!ag1->ptrListaVizinhos.empty())
//        {
//            random_shuffle(ag1->ptrListaVizinhos.begin(), ag1->ptrListaVizinhos.end());//embaralha a lista de vizinhos
//            Agents* ag2 = ag1->ptrListaVizinhos[0];// age com o primeiro da lista
//            ag2->outro=true;
//            this->define_tipo_encontro_2_i(ag1,ag2
//                                           // , lala
//                                           ,MySpace
//                                           );
//            ag2->outro=false;
//            ag1->ja_agiu=true;
//        }
//        if (ag1->ptrListaVizinhos.size()==0
//                && ag1->ja_agiu==false
//                )//se já varreu toda a visao e nao agiu, age neutro
//        {
//            this->age_soh(ag1, MySpace);
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
//    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts, MySpace);
//    this->num_turnos++;*/
//}

void World::update(space &MySpace)
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
        this->busca_vizinho(ag1,MySpace);
        //lala->repaint();
        if (!ag1->ptrListaVizinhos.empty())
        {
            Agents* ag2 = ag1->get_largest_afilliative_mem();
            ag2->outro=true;
            this->define_tipo_encontro(ag1,ag2,MySpace);
            ag2->outro=false;
            ag1->ja_agiu=true;
        }
        if (ag1->ptrListaVizinhos.size()==0&& ag1->ja_agiu==false)//se já varreu toda a visao e nao agiu, age neutro
        {
            this->age_soh(ag1, MySpace);
            ag1->ja_agiu=true;
        }
        //lala->repaint();
        this->verifica_contorno(ag1);
        ag1->ator=false;
    }
    this->DBSCAN(this->vec_ptr_Agentes,this->Eps,this->MinPts, MySpace);
    this->num_turnos++;
}

