//#include <C:\Users\Vrios\Dropbox\Doutorado\codigo\socrats\Socrats_Doc_Gui__codigo_base\agents.h>
#include </home/vrios/Documents/codigo/socrats/Socrats_Doc_Gui__codigo_base/agents.h>
#include <algorithm>
#include<QDebug>
#include <iostream>


void Agents::constroi_memoria(int length, int type, int N_agentes)
{
    if (type==0)//memoria individuo a individuo
    {
        this->map_mem_individual.clear();//memoria individual
        this->mem_deque_grupal.clear();
    }

    if (type==1)//memoria grupal
    {
        this->map_mem_individual.clear();
        //qDebug()<<"gera memoria mem_length ="<<length;
        pair <int,int> aux;
        aux=make_pair(-1,-1);
        this->mem_deque_grupal.assign(length,aux);
    }

    if (type!=0 && type!=1)
    {
        std::cerr<<" tipo incorreto de memoria, 1 = global, 0 = individual";
        exit(35);
    }
}


void Agents::registra_mem_g(int id, int tipo_acao )
{
    //memória grupal
    if (this->mem_deque_grupal.size()>=this->memory_length)
    {
        this->mem_deque_grupal.pop_front();
    }
    pair <int,int> c_aux;
    c_aux = make_pair(id,tipo_acao);
    this->mem_deque_grupal.push_back(c_aux);

}

void Agents::registra_mem_i(int id, int tipo_acao )
{
    //memória individual
    map <int, deque<int> >::iterator it;
    it=this->map_mem_individual.find(id);// busca se há memoria prévia para o individuo id
    if (it ==this->map_mem_individual.end()) //caso nao haja
    {
        this->map_mem_individual.insert(make_pair(id, deque <int>(1, tipo_acao)));
    }
    else// caso exista a memoria
    {
        if(it->second.size()>=this->memory_length)// se já preencheu todo o comprimento de memoria permitido
        {
            it->second.pop_front();//esquecer o primeiro
        }
        it->second.push_back(tipo_acao);//memorizar
    }

}


Agents::mod Agents::get_mem_g(int id)//memoria grupal
{
    int sum_ag = 0;
    int sum_af = 0;
    int sum_an = 0;

    double percent_ag = 0;
    double percent_af = 0;
    double percent_an = 0;

    double af=0;
    double ag=0;
    double an=0;
    double mods[3] ={
        af,  //af
        ag,  //ag
        an};


    for ( memory_deque::iterator it = mem_deque_grupal.begin(); it!=mem_deque_grupal.end(); it++)
    {
        if ((*it).first==id && (*it).second== 1) sum_af ++;
        if ((*it).first==id && (*it).second==-1) sum_ag ++;
        if ((*it).first==id && (*it).second== 0) sum_an ++;
    }

    percent_af = (double)sum_af/(double)this->memory_length;//convertendo em % da memoria total
    percent_ag = (double)sum_ag/(double)this->memory_length;
    percent_an = (double)sum_an/(double)this->memory_length;

    //    qDebug()<<"mem_lenght"<<this->memory_length;
    //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
    //       qDebug()<<"s_af_ag_an<<"<<percent_af<<" "<<percent_ag<<" "<<percent_an;
    af=this->prob_Inicial_AF + percent_af - (percent_ag/2) - (percent_an/2);
    ag=this->prob_Inicial_AG + percent_ag - (percent_af/2) - (percent_an/2);
    an=this->prob_Inicial_AN + percent_an - (percent_af/2) - (percent_ag/2);
    mods[0] = af;
    mods[1] = ag;
    mods[2] = an;

    //    qDebug()<<"mods1"<<mods[0] << mods[1] << mods[2];
    if (mods[0]>=0.99)mods[0]=0.99; // limitando os valores de probabilidade para somar 1
    if (mods[1]>=0.99)mods[1]=0.99; // e para permitir a ocorrencia de todas as açoes
    if (mods[2]>=0.99)mods[2]=0.99;
    //    qDebug()<<"mods2"<<mods[0] << mods[1] << mods[2];
    if (mods[0]<=0.005)mods[0]=0.005; // prob máxima 99%
    if (mods[1]<=0.005)mods[1]=0.005; // prob mínima 0.5%
    if (mods[2]<=0.005)mods[2]=0.005;
    //    qDebug()<<"mods3"<<mods[0] << mods[1] << mods[2];
    if (mods[0] + mods[1] + mods[2]>1)
    {
        double temp = * max_element(&mods[0],&mods[3]);
        temp += (1 - (mods[0] + mods[1] + mods[2]));// limitando novamente os valores de probabilidade para somar 1
        *max_element(&mods[0],&mods[3])= temp;
        //qDebug()<<"limite max";
    }   //se a soma for maior que 1, o excesso será subtraído da maior probabilidade


    modificadores m = {mods[0] , mods[1] , mods[2]};
    // qDebug()<<"mods fim"<<mods[0] << mods[1] << mods[2];
    return m;
}

Agents::mod Agents::get_mem_i(int id)//memoria grupal
{
    int sum_ag = 0;
    int sum_af = 0;
    int sum_an = 0;

    double percent_ag = 0;
    double percent_af = 0;
    double percent_an = 0;

    double af=(double)1/3;
    double ag=(double)1/3;
    double an=(double)1/3;

    double mods[3] ={
        af,  //af
        ag,  //ag
        an
    };

    map <int, deque<int> >::iterator it;
    it = this->map_mem_individual.find(id);

    if (it!=map_mem_individual.end())// se já se encontraram anteriormente
    {
        deque <int>::iterator it2;
        for (it2 = this->map_mem_individual[id].begin(); it2 != this->map_mem_individual[id].end(); it2++)

        {
            if(*it2 ==  1) sum_af ++;
            if(*it2 == -1) sum_ag ++;
            if(*it2 ==  0) sum_an ++;
        }


        percent_af = (double)sum_af/(double)this->memory_length;//convertendo em % da memoria total
        percent_ag = (double)sum_ag/(double)this->memory_length;
        percent_an = (double)sum_an/(double)this->memory_length;

        //    qDebug()<<"mem_lenght"<<this->memory_length;
        //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
        //       qDebug()<<"s_af_ag_an<<"<<percent_af<<" "<<percent_ag<<" "<<percent_an;
        af=this->prob_Inicial_AF + percent_af - (percent_ag/2) - (percent_an/2);
        ag=this->prob_Inicial_AG + percent_ag - (percent_af/2) - (percent_an/2);
        an=this->prob_Inicial_AN + percent_an - (percent_af/2) - (percent_ag/2);
        mods[0] = af;
        mods[1] = ag;
        mods[2] = an;

        //    qDebug()<<"mods1"<<mods[0] << mods[1] << mods[2];
        if (mods[0]>=0.99)mods[0]=0.99; // limitando os valores de probabilidade para somar 1
        if (mods[1]>=0.99)mods[1]=0.99; // e para permitir a ocorrencia de todas as açoes
        if (mods[2]>=0.99)mods[2]=0.99;
        //    qDebug()<<"mods2"<<mods[0] << mods[1] << mods[2];
        if (mods[0]<=0.005)mods[0]=0.005; // prob máxima 99%
        if (mods[1]<=0.005)mods[1]=0.005; // prob mínima 0.5%
        if (mods[2]<=0.005)mods[2]=0.005;
        //    qDebug()<<"mods3"<<mods[0] << mods[1] << mods[2];
        if (mods[0] + mods[1] + mods[2]>1)
        {
            double temp = * max_element(&mods[0],&mods[3]);
            temp += (1 - (mods[0] + mods[1] + mods[2]));// limitando novamente os valores de probabilidade para somar 1
            *max_element(&mods[0],&mods[3])= temp;
            //qDebug()<<"limite max";
        }   //se a soma for maior que 1, o excesso será subtraído da maior probabilidade


        modificadores m = {mods[0] , mods[1] , mods[2]};
        return m;
    }

    else // se nunca se encontraram
    {
        modificadores m = {mods[0] , mods[1] , mods[2]};
        return m;
    }

}

