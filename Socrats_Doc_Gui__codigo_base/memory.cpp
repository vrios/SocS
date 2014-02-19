#include <C:\Users\Vrios\Dropbox\Doutorado\codigo\socrats\Socrats_Doc_Gui__codigo_base\agents.h>
#include <algorithm>
#include<QDebug>
#include <iostream>


void Agents::constroi_memoria(int length, int type, int N_agentes)
{
    if (type==0)//memoria individuo a individuo
    {
        // this->vec_deq_mem.assign(N_agentes,deque <int>());
        //        for (int i = 0; i<N_agentes;i++)
        //        {
        //            this->vec_deq_mem.push_back( deque <int>());
        //        }
        this->map_mem.clear();
    }

    if (type==1)//memoria grupal
    {
        //qDebug()<<"gera memoria mem_length ="<<length;
        pair <int,int> aux;
        aux=make_pair(-1,-1);
        this->mem_deque.assign(length,aux);
        //        pair <int,int> c_aux;
        //        c_aux = make_pair(-13, -22);
        //        for (int i = 0; i< length; i++)
        //        {
        //            this->mem_deque.push_back(c_aux);
        //        }
        //        pair <int,int> c_aux;
        //        c_aux = make_pair(-13, -22);
        //        for (int i = 0; i< length; i++)
        //        {
        //            this->mem_deque.push_back(c_aux);
        //        }
    }
    if (type!=0 && type!=1)
    {
        std::cerr<<" tipo incorreto de memoria";
        exit(35);
    }
}


void Agents::registra_mem_g(int id, int tipo_acao )
{
    //memória grupal

    if (this->mem_deque.size()>=this->memory_length)
    {
        this->mem_deque.pop_front();
    }
    pair <int,int> c_aux;
    c_aux = make_pair(id,tipo_acao);
    this->mem_deque.push_back(c_aux);

}

void Agents::registra_mem_i(int id, int tipo_acao )
{
    //memória individual
    map <int, deque<int> >::iterator it;
    it=this->map_mem.find(id);// busca se há memoria prévia para o individuo id
    if (it ==this->map_mem.end()) //caso nao haja
    {
        this->map_mem.insert(make_pair(id, deque <int>(1, tipo_acao)));
    }
    else// caso exista a memoria
    {
        if(it->second.size()>=this->memory_length)// se já preencheu todo o comprimento de memoria permitido
        {
            it->second.pop_front();//esquecer o primeiro
        }
        it->second.push_back(tipo_acao);//memorizar
    }

    //    //memória individual

    //    if (this->vec_deq_mem[id].size() >= this->memory_length)
    //    {
    //        this->vec_deq_mem[id].pop_front();
    //    }
    //    this->vec_deq_mem[id].push_back(tipo_acao);
}


Agents::mod Agents::get_mem_g(int id)//memoria grupal
{
    int w_ag = 0;
    int w_af = 0;
    int w_an = 0;

    double s_ag = 0;
    double s_af = 0;
    double s_an = 0;

    double af=0;
    double ag=0;
    double an=0;
    double mods[3] ={
        af,  //af
        ag,  //ag
        an};


    for ( mq::iterator it = mem_deque.begin(); it!=mem_deque.end(); it++)
    {
        if ((*it).first==id && (*it).second== 1) w_af ++;
        if ((*it).first==id && (*it).second==-1) w_ag ++;
        if ((*it).first==id && (*it).second== 0) w_an ++;
    }

    s_af = (double)w_af/(double)this->memory_length;//convertendo em % da memoria total
    s_ag = (double)w_ag/(double)this->memory_length;
    s_an = (double)w_an/(double)this->memory_length;

    //    qDebug()<<"mem_lenght"<<this->memory_length;
    //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
    //       qDebug()<<"s_af_ag_an<<"<<s_af<<" "<<s_ag<<" "<<s_an;
    af=this->prob_Inicial_AF + s_af - (s_ag/2) - (s_an/2);
    ag=this->prob_Inicial_AG + s_ag - (s_af/2) - (s_an/2);
    an=this->prob_Inicial_AN + s_an - (s_af/2) - (s_ag/2);
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
    int w_ag = 0;
    int w_af = 0;
    int w_an = 0;

    double s_ag = 0;
    double s_af = 0;
    double s_an = 0;

    double af=(double)1/3;
    double ag=(double)1/3;
    double an=(double)1/3;

    double mods[3] ={
        af,  //af
        ag,  //ag
        an
    };



    map <int, deque<int> >::iterator it;
    it = this->map_mem.find(id);

    if (it!=map_mem.end())// se já se encontraram anteriormente
    {
        deque <int>::iterator it2;
        for (it2 = this->map_mem[id].begin(); it2 != this->map_mem[id].end(); it2++)

        {
            if(*it2 ==  1) w_af ++;
            if(*it2 == -1) w_ag ++;
            if(*it2 ==  0) w_an ++;
        }

        //    for ( int it3= 0; it3 < this->vec_deq_mem[id].size(); it3++)
        //    {

        //        if (this->vec_deq_mem[id][it3]==  1) w_af ++;
        //        if (this->vec_deq_mem[id][it3]== -1) w_ag ++;
        //        if (this->vec_deq_mem[id][it3]==  0) w_an ++;
        //    }
        s_af = (double)w_af/(double)this->memory_length;//convertendo em % da memoria total
        s_ag = (double)w_ag/(double)this->memory_length;
        s_an = (double)w_an/(double)this->memory_length;

        //    qDebug()<<"mem_lenght"<<this->memory_length;
        //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
        //       qDebug()<<"s_af_ag_an<<"<<s_af<<" "<<s_ag<<" "<<s_an;
        af=this->prob_Inicial_AF + s_af - (s_ag/2) - (s_an/2);
        ag=this->prob_Inicial_AG + s_ag - (s_af/2) - (s_an/2);
        an=this->prob_Inicial_AN + s_an - (s_af/2) - (s_ag/2);
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


//Agents::mod Agents::get_mem(int id)//memoria grupal
//{
//    if (this->memory_type==0)
//    {
//        int w_ag = 0;
//        int w_af = 0;
//        int w_an = 0;

//        double s_ag = 0;
//        double s_af = 0;
//        double s_an = 0;

//        double af=0;
//        double ag=0;
//        double an=0;
//        double mods[3] ={
//            af,  //af
//            ag,  //ag
//            an,};


//        // vector<deque<int> >::iterator it;
//        for ( int it3= 0; it3 < this->vec_deq_mem[id].size(); it3++)
//        {

//            if (this->vec_deq_mem[id][it3]==  1) w_af ++;
//            if (this->vec_deq_mem[id][it3]== -1) w_ag ++;
//            if (this->vec_deq_mem[id][it3]==  0) w_an ++;
//        }
//        s_af = (double)w_af/(double)this->memory_length;//convertendo em % da memoria total
//        s_ag = (double)w_ag/(double)this->memory_length;
//        s_an = (double)w_an/(double)this->memory_length;

//        //    qDebug()<<"mem_lenght"<<this->memory_length;
//        //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
//        //       qDebug()<<"s_af_ag_an<<"<<s_af<<" "<<s_ag<<" "<<s_an;
//        af=this->prob_Inicial_AF + s_af - (s_ag/2) - (s_an/2);
//        ag=this->prob_Inicial_AG + s_ag - (s_af/2) - (s_an/2);
//        an=this->prob_Inicial_AN + s_an - (s_af/2) - (s_ag/2);
//        mods[0] = af;
//        mods[1] = ag;
//        mods[2] = an;

//    }
//    if (this->memory_type==1)
//    {
//        int w_ag = 0;
//        int w_af = 0;
//        int w_an = 0;

//        double s_ag = 0;
//        double s_af = 0;
//        double s_an = 0;

//        double af=0;
//        double ag=0;
//        double an=0;
//        double mods[3] ={
//            af,  //af
//            ag,  //ag
//            an,};


//        for ( mq::iterator it = mem_deque.begin(); it!=mem_deque.end(); it++)
//        {
//            if ((*it).first==id && (*it).second== 1) w_af ++;
//            if ((*it).first==id && (*it).second==-1) w_ag ++;
//            if ((*it).first==id && (*it).second== 0) w_an ++;
//        }

//        s_af = (double)w_af/(double)this->memory_length;//convertendo em % da memoria total
//        s_ag = (double)w_ag/(double)this->memory_length;
//        s_an = (double)w_an/(double)this->memory_length;

//        //    qDebug()<<"mem_lenght"<<this->memory_length;
//        //       qDebug()<<"mods0"<<mods[0] << mods[1] << mods[2];
//        //       qDebug()<<"s_af_ag_an<<"<<s_af<<" "<<s_ag<<" "<<s_an;
//        af=this->prob_Inicial_AF + s_af - (s_ag/2) - (s_an/2);
//        ag=this->prob_Inicial_AG + s_ag - (s_af/2) - (s_an/2);
//        an=this->prob_Inicial_AN + s_an - (s_af/2) - (s_ag/2);
//        mods[0] = af;
//        mods[1] = ag;
//        mods[2] = an;

//        //    qDebug()<<"mods1"<<mods[0] << mods[1] << mods[2];
//        if (mods[0]>=0.99)mods[0]=0.99; // limitando os valores de probabilidade para somar 1
//        if (mods[1]>=0.99)mods[1]=0.99; // e para permitir a ocorrencia de todas as açoes
//        if (mods[2]>=0.99)mods[2]=0.99;
//        //    qDebug()<<"mods2"<<mods[0] << mods[1] << mods[2];
//        if (mods[0]<=0.005)mods[0]=0.005; // prob máxima 99%
//        if (mods[1]<=0.005)mods[1]=0.005; // prob mínima 0.5%
//        if (mods[2]<=0.005)mods[2]=0.005;
//        //    qDebug()<<"mods3"<<mods[0] << mods[1] << mods[2];
//        if (mods[0] + mods[1] + mods[2]>1)
//        {
//            double temp = * max_element(&mods[0],&mods[3]);
//            temp += (1 - (mods[0] + mods[1] + mods[2]));// limitando novamente os valores de probabilidade para somar 1
//            *max_element(&mods[0],&mods[3])= temp;
//            //qDebug()<<"limite max";
//        }   //se a soma for maior que 1, o excesso será subtraído da maior probabilidade


//        modificadores m = {mods[0] , mods[1] , mods[2]};
//        // qDebug()<<"mods fim"<<mods[0] << mods[1] << mods[2];
//        return m;
//    }
//}

//void Agents::registra_mem(int id, int tipo_acao )
//{
//    if (this->memory_type==0)
//    {
//        //memória individual
//        map <int, deque<int> >::iterator it;
//        it=this->map_mem.find(id);// busca se há memoria prévia para o individuo id
//        if (it ==this->map_mem.end()) //caso nao haja
//        {
//            this->map_mem.insert(make_pair(id, deque <int>(1, tipo_acao)));
//        }
//        else// caso exista a memoria
//        {
//            if(it->second.size()>=this->memory_length)// se já preencheu todo o comprimento de memoria permitido
//            {
//                it->second.pop_front();//esquecer o primeiro
//            }
//            it->second.push_back(tipo_acao);//memorizar
//        }
//        //        if (this->vec_deq_mem[id].size()>=this->memory_length)
//        //        {
//        //            this->vec_deq_mem[id].pop_front();
//        //        }
//        //        this->vec_deq_mem[id].push_back(tipo_acao);


//    }
//    if (this->memory_type==1)
//    {
//        //memória grupal

//        if (this->mem_deque.size()>=this->memory_length)
//        {
//            this->mem_deque.pop_front();
//        }
//        pair <int,int> c_aux;
//        c_aux = make_pair(id,tipo_acao);
//        this->mem_deque.push_back(c_aux);
//    }
//}
