#include "agents.h"
#include <cstdlib>
//#include<QDebug>
////C++11 não possui M_PI definido, por isso o bloco abaixo
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern void verifica_contorno(Agents* ag);

//Agents::Agents()
//{
//    this->passo=1;
//    this->prob_Inicial_AF=this->prob_Inicial_AG=this->prob_Inicial_AN=1/3;

//    this->visitado=false;//DBSCAN
//    this->cluster=0;
//}

//Agents::Agents(int id, double coordX, double coordY, double Ang, double pAF, double pAG, double pAN,
//               int N_agentes, int raio)
//{
//    this->id=id;
//    this->x=coordX;
//    this->y=coordY;
//    this->angulo=Ang;
//    this->prob_Inicial_AF=pAF;
//    this->prob_Inicial_AG=pAG;
//    this->prob_Inicial_AN=pAN;
//    this->passo=1;
//    this->raio=raio;
//    this->ator=false;
//    this->outro=false;

//    this->visitado=false;//DBSCAN
//    this->cluster=0;

//    memoria m_aux;
//    m_aux.mod_AF=m_aux.mod_AG=m_aux.mod_AN=m_aux.soma_af=m_aux.soma_ag=m_aux.soma_an=0;
//    for (int i = 0; i<N_agentes; i++)//povoa o vetor de memoria
//    {
//        this->vec_memoria.push_back(m_aux);
//        this->vec_memoria[i].id=i;

//    }
//}

Agents::Agents(int id, double coordX, double coordY, double Ang, double pAF, double pAG, double pAN,
               int N_agentes, int raio, int mem_length, int mem_type)
{
    this->id=id;
    this->x=coordX;
    this->y=coordY;
    this->angulo=Ang;
    this->prob_Inicial_AF=pAF;
    this->prob_Inicial_AG=pAG;
    this->prob_Inicial_AN=pAN;
    this->passo=1;
    this->raio=raio;
    this->ator=false;
    this->outro=false;

    this->visitado=false;//DBSCAN
    this->cluster=0;
   // qDebug()<<"construtor de agente mem_length ="<<mem_length;
    this->memory_length=mem_length;
    this->memory_type=mem_type;
    this->constroi_memoria(mem_length,mem_type, N_agentes);
}


void Agents::anda()
{
   double p=(double)rand()/RAND_MAX * this->passo;
    // anda
    this->x+=p * cos(this->angulo);
    this->y+=p * sin(this->angulo);

    double dA = (double)rand()/RAND_MAX * (M_PI*2);//angulo aleatorio entre 0 e 360, em radianos
    this->angulo+=dA;//altera o angulo do animal
//    // anda
//    this->x+=this->passo * cos(this->angulo);
//    this->y+=this->passo * sin(this->angulo);

//    double dA = (double)rand()/RAND_MAX * (M_PI*2);//angulo aleatorio entre 0 e 360, em radianos
//    this->angulo+=dA;//altera o angulo do animal
}

void Agents::anda(double ang)
{
    double p=(double)rand()/RAND_MAX * this->passo;
    this->angulo=ang;//vira na direção do outro
    //      lala->repaint();
    double dx =p * cos(this->angulo);
    double dy =p * sin(this->angulo);

    this->x+=dx;
    this->y+=dy;

    /*
    this->angulo=ang;//vira na direção do outro
    //      lala->repaint();
    double dx = this->passo * cos(this->angulo);
    double dy = this->passo * sin(this->angulo);

    this->x+=dx;
    this->y+=dy;*/

}

//double Agents::get_mod_mem(int i, char tipo)
//{

//    if (tipo=='f'){return this->vec_memoria[i].mod_AG;}
//    if (tipo=='g') {return this->vec_memoria[i].mod_AF;}
//    if (tipo=='n') {return this->vec_memoria[i].mod_AN;}
//}


//double Agents::get_prob_Init(char tipo)
//{
//    if (tipo=='f'){return this->prob_Inicial_AF;}
//    if (tipo=='g'){return this->prob_Inicial_AG;}
//    if (tipo=='n'){return this->prob_Inicial_AN;}
//}

//void Agents::set_mod_(int outro, double valor, char tipo)
//{
//    if (tipo=='f'){this->vec_memoria[outro].mod_AF+=valor;}
//    if (tipo=='g'){this->vec_memoria[outro].mod_AG+=valor;}
//    if (tipo=='n'){this->vec_memoria[outro].mod_AN+=valor;}

//}

//void Agents::set_sum_(int outro, char tipo)
//{
//    if (tipo=='f') {this->vec_memoria[outro].soma_af++;}
//    if (tipo=='g') {this->vec_memoria[outro].soma_ag++;}
//    if (tipo=='n') {this->vec_memoria[outro].soma_an++;}
//}



