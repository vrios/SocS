#include "agents.h"
#include <cstdlib>
//#include <map>
//#include<QDebug>
////C++11 não possui M_PI definido, por isso o bloco abaixo
#define _USE_MATH_DEFINES
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern void verifica_contorno(Agents* ag);

Agents::Agents(int id, double coordX, double coordY, double Ang, double pAF, double pAG, double pAN,
               int N_agentes, int raio, int mem_length, int mem_type, double mem_mod)
{
    this->id=id;
    this->x=coordX;
    this->y=coordY;
    this->myCell=make_pair(coordX,coordY);
    this->angulo=Ang;
    this->prob_Inicial_AF=pAF;
    this->prob_Inicial_AG=pAG;
    this->prob_Inicial_AN=pAN;
    this->passo=1;
    this->raio=raio;
    this->ator=false;
    this->outro=false;

    this->visitado=false;//DBSCAN
    this->MyCluster=0;
   // qDebug()<<"construtor de agente mem_length ="<<mem_length;
    this->memory_length=mem_length;
    this->memory_type=mem_type;
    this->constroi_memoria(mem_length, mem_type, N_agentes);
    this->mem_modifier=mem_mod;

}


void Agents::anda()
{
   double p=(double)rand()/RAND_MAX * this->passo;
    // anda
    this->x+=p * cos(this->angulo);
    this->y+=p * sin(this->angulo);

    double dA = (double)rand()/RAND_MAX * (M_PI*2);//angulo aleatorio entre 0 e 360, em radianos
    this->angulo+=dA;//altera o angulo do animal
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

}

