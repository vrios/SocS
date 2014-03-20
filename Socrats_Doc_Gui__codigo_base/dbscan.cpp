//#include "dbscan.h"
#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>




//vector <Agents* > World::regionQuery(Agents* ag1, double Eps)
//{//fun��o que calcula as distancias.
//    vector <Agents*> listViz;
//    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
//    {
//        //vai de vizinho em vizinho
//        Agents* ag2= this->vec_ptr_Agentes[j];
//        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
//        double d=distTorus(ag1,ag2, X);
//        if (d<=Eps)
//        {listViz.push_back(ag2);}
//    }
//    return listViz;
//}


map<int, Agents *> World::m_regionQuery(Agents* ag1, double Eps)
{
    map <int, Agents*> listViz;
    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
    {
        //vai de vizinho em vizinho
        Agents* ag2= this->vec_ptr_Agentes[j];
        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
        double d=distTorus(ag1,ag2, X);
        if (d<=Eps)
        {listViz.insert(pair<int, Agents*>(ag2->get_id(),ag2));}
    }
    return listViz;
}


void World::DBSCAN (vector<Agents* >& SetOfPoints, double Eps, int MinPts)
{
    for (int i =0; i<SetOfPoints.size();i++)// para garantir que o dbscan funciona sequencialmente
    {
        SetOfPoints[i]->cluster=0;
        SetOfPoints[i]->visitado=false;
    }
    this->m_clusters.clear();//limpando o mapa de clusters
    this->m_clusters.insert(make_pair(0,  map<int,Agents*> ()));

    // SetOfPoints is UNCLASSIFIED
    int ClusterId = 1;//0 � ru�do
    for (int i =0; i<SetOfPoints.size();i++)
    {
        Agents* Point = SetOfPoints[i];
        if (!Point->visitado)
        {
            if(this->ExpandCluster(SetOfPoints, Point, ClusterId, Eps, MinPts) )
            {
                ClusterId ++;
            }
        }
    }
    //end DBSCAN

    //adding clusters to timeSlices for mc1

    map<int,map <int,Agents*> >::iterator it;
    map <int,Agents*>::iterator it2;

    if(this->timeSlices.size()<this->num_turnos+1)
    {this->timeSlices.push_back(vector<vector<int> >());}

    if (this->timeSlices[this->num_turnos].size() < this->m_clusters.size()+1)
    {this->timeSlices[this->num_turnos].resize(this->m_clusters.size(),vector<int>());}

    vector<vector<int> > & ts_nt = this->timeSlices[this->num_turnos];
    int j=0;
    int k=0;
    it=this->m_clusters.begin();
    it++;


    for ( it ; it!=this->m_clusters.end();it++)
    {
        for (it2=it->second.begin();it2!=it->second.end();it2++)
        {
            //this->timeSlices[this->num_turnos][it->first].push_back(it2->first);
            ts_nt[j].push_back(it2->first);
        }
        j++;
        k++;
    }

    //    for (  it=this->m_clusters.begin(); it!=this->m_clusters.end();it++)
    //    {
    //        //this->timeSlices[this->num_turnos][it->first].push_back(it2->first);
    //            this->timeSlices[this->num_turnos][j].push_back(it->second);
    //            j++;
    //        }
    //    }
}

bool World::ExpandCluster(vector<Agents*>& SetOfPoints, Agents* Point, int ClId, double Eps,int MinPts)
{
    map <int, Agents*> seeds = m_regionQuery(Point,Eps);
    if (seeds.size()< MinPts )
        // no core point
    {
        ///alterar ponto pra ruido
        //Point->cluster=0;
        this->inserir(Point,0);
        return false;
    }
    else
    {  // all points in seeds are density-
        // reachable from Point
        // SetOfPoints.changeClIds(seeds,ClId);//marcar todos de SetofPoints como ClI
        //        for (int k =0; k<seeds.size();k++)
        //        {
        //            seeds[k]->cluster=ClId;
        //        }
        map <int,Agents*>::iterator it = seeds.begin();//usando iterador e as porra!
        for (it = seeds.begin();it!=seeds.end();it++) {it->second->cluster=ClId;}//marcar todos de SetofPoints como ClId

        //seeds.erase(Point->get_id());
        while (!seeds.empty())
        {
            Agents* currentP = seeds.begin()->second;
            map <int, Agents* > result = m_regionQuery(currentP,Eps);
            if( result.size() >= MinPts )
            {
                for( it= result.begin(); it != result.end(); it++ )
                {
                    //Agents* resultP = result[it];
                    Agents* resultP = it->second;
                    if (!resultP->visitado)
                    {
                        if (resultP->cluster == 0 )
                        {
                            seeds.insert(pair<int,Agents*>(resultP->get_id(),resultP));
                        }
                        // SetOfPoints.changeClId(resultP,ClId);
                        this->inserir(resultP,ClId);
                        //  resultP->cluster=ClId;
                        //resultP->visitado=true;
                    } // UNCLASSIFIED or NOISE
                }
            } // result.size >= MinPts
            seeds.erase(currentP->get_id());
        } // seeds <> Empty
        return true;
    }
} // ExpandCluster

void World::inserir(Agents * P, int ClID)
{
    P->visitado=true;
    if(this->m_clusters.find(ClID)==this->m_clusters.end())//se n�o existirem clusters suficientes
    {this->m_clusters.insert(make_pair(ClID, map<int,Agents*> ()));}
    //insere no mapa
    if (ClID!=P->cluster)//se houve fus�o dos clusters
        this->remover(P,ClID);
    map<int,Agents*>& c = this->m_clusters[ClID]; // & � uma referencia, usado para alterar o valor do mapa em clusters[ClID] diretamente
    c.insert(make_pair(P->get_id(),P));
    //registra no proprio ponto
    P->cluster=ClID;
    P->visitado=true;
}

void World::remover(Agents * P, int ClID)
{
    if (ClID<m_clusters.size())
    {
        map<int,Agents*>& c =this->m_clusters[ClID]; // & � uma referencia, usado para alterar o valor do mapa em clusters[ClID] diretamente
        if(c.find(P->get_id())!= c.end())
        {
            c.erase(P->get_id());
        }//elimina o item cuja chave � P->get_id()

    }

}


vector<double> World::output_tam_cluster()
{
    //retorna o tamanho medio dos clusters
    vector <double> vec_tams_medios;//tamanhos medios para toda a simula��o
    vector <double> vec_tamanhos;//tamanhos dos clusters para cada passo de tempo
    for ( int i=0; i < this->timeSlices.size(); i++)

    {
        double tam_medio=0;
        double soma_tams = 0;
        vec_tamanhos.clear();

        //tamanho de cada cluster
        for (int j=0; j< this->timeSlices[i].size(); j++)
        {
            int tam_clust=0;
            //   for (int k=0;k<this->timeSlices[i][j].size();k++)
            {
                //tam_clust++;
                vec_tamanhos.push_back(this->timeSlices[i][j].size());
                //                tam_clust++;
                //                vec_tamanhos.push_back(tam_clust);
            }
        }
        //soma dos tamanhos dos clusters
        for (int w=0; w<vec_tamanhos.size();w++)
        {
            soma_tams=soma_tams+vec_tamanhos[w];
        }
        //tamanho medio dos clusters
        if (vec_tamanhos.size()!=0)
        {
            tam_medio= (double)soma_tams /(double)vec_tamanhos.size();
            vec_tams_medios.push_back(tam_medio);
        }
        else {vec_tams_medios.push_back(std::numeric_limits<double>::quiet_NaN());}//pra resolver problemas de divis�o por zero
    }
    return vec_tams_medios;
}

vector<double> World::output_var_cluster()
{
    //retorna os desvios padrao, nao as variancias
    vector <double> vec_tams_medios;//tamanhos medios para toda a simula��o
    vector <double> vec_tamanhos;//tamanhos dos clusters para cada passo de tempo
    vector <double> vec_var;
    for ( int i=0; i < this->timeSlices.size(); i++)

    {
        double tam_medio=0;
        double soma_tams = 0;
        double var_tam = 0;
        vec_tamanhos.clear();

        //tamanho de cada cluster
        for (int j=0; j< this->timeSlices[i].size(); j++)
        {
            int tam_clust=0;
            //  for (int k=0;k<this->timeSlices[i][j].size();k++)
            {
                //                tam_clust++;
                //                vec_tamanhos.push_back(tam_clust);
                vec_tamanhos.push_back(this->timeSlices[i][j].size());
            }
        }
        //soma dos tamanhos dos clusters
        for (int w=0; w<vec_tamanhos.size();w++)
        {
            soma_tams=soma_tams+vec_tamanhos[w];

        }
        //tamanho medio dos clusters
        if (vec_tamanhos.size()!=0)
        {
            double temp_somaQuad = 0;
            for (int w=0; w<vec_tamanhos.size();w++)
            {
                tam_medio = (double)soma_tams /(double)vec_tamanhos.size();
                vec_tams_medios.push_back(tam_medio);
                temp_somaQuad += (vec_tamanhos[w] - tam_medio)*(vec_tamanhos[w] - tam_medio);

            }
            vec_var.push_back(sqrt((double)temp_somaQuad/(double)vec_tamanhos.size()));
        }
        else {vec_var.push_back(std::numeric_limits<double>::quiet_NaN());}//pra resolver problemas de divis�o por zero
    }
    return vec_var;
}

vector<double> World::out_num_clust()
{
    //retorna o numero    de clusters
    vector <double> temp;
 //   temp.resize(this->timeSlices.size());
    for ( int i=0; i < this->timeSlices.size(); i++)
    {
        for (int i=0; i < this->timeSlices.size(); i++ )
        {
            temp.push_back(this->timeSlices[i].size()-1);

        }
        return temp;
    }
}

vector<string> World::out_clust()
{
    //retorna o conteudo dos clusters
    vector<string> temp;
    temp.resize(this->timeSlices.size());

    for (int i=0; i < this->timeSlices.size(); i++ )
        //output de todos os clusters, inclusive ru�do
    {
        for (int j=0; j< this->timeSlices[i].size(); j++)
        {
            temp[i]+="[";
            for (int k=0;k<this->timeSlices[i][j].size();k++)
            {
                temp[i]+=to_string(this->timeSlices[i][j][k])+", ";
            }
            temp[i]+="]";
        }
    }
    return temp;
}


//void World::expandCluster(Agents* P,vector<Agents*> NeighborPts, int ClId, double Eps, int MinPts)
//{                                                                   //pseudocodigo da wikipedia
//    P->cluster=ClId;                                                //   add P to cluster C
//    for (int i=0;i<NeighborPts.size();i++)                          //   for each point P' in NeighborPts
//    {//busca viznhos de P
//        if (!NeighborPts[i]->visitado)                              //      if P' is not visited
//        {
//            NeighborPts[i]->visitado=true;                          //         mark P' as visited
//            NeighborPts[i]->cluster=ClId;
//            vector<Agents*>NeighborPts2=regionQuery(P,Eps);         //         NeighborPts' = regionQuery(P', eps)
//            //busca os vizinhos do ponto vzinho a P
//            if(NeighborPts2.size() >= MinPts)                       //         if sizeof(NeighborPts') >= MinPts
//            {//caso haja o vizinho de P tenha na sua vizinhan�a mais pontos q o m�nimo para formar clusters, une as vizinhan�as em um cluster s�
//                for (int j = 0; j < (int)NeighborPts2.size(); j++)  //            NeighborPts = NeighborPts joined with NeighborPts'
//                {
//                    if (!NeighborPts2[j]->visitado) NeighborPts2[j]->visitado= true;
//                    if (NeighborPts2[j]->cluster != ClId)
//                    {
//                        NeighborPts2[j]->cluster = ClId;
//                        //NeighborPts.push_back(NeighborPts2[j]);
//                    }
//                }

//            }
//        }
//        if(NeighborPts[i]->cluster=0)                               //      if P' is not yet member of any cluster
//        {
//            NeighborPts[i]->cluster=ClId;                            //         add P' to cluster C
//        }
//    }
//}

//void World::DBSCAN(vector <Agents*> SetOfPoints, double Eps, int MinPts )
//{
//    for (int i =0; i<SetOfPoints.size();i++)
//    {
//        SetOfPoints[i]->cluster=0;
//        SetOfPoints[i]->visitado=false;
//    }

//    int ClId = 0;// numero do cluster. ru�do � cluster zero
//    this->clusters.clear();
//    for(int i=0; i<SetOfPoints.size(); i++)                     //pseudocodigo da wikipedia
//    {
//        if (!SetOfPoints[i]->visitado)                          //    for each unvisited point P in dataset D
//        {
//            SetOfPoints[i]->visitado=true;                      //            mark P as visited
//            vector<Agents*>NeighborPts = regionQuery(SetOfPoints[i],Eps);     //            NeighborPts = regionQuery(P, eps)
//            if (NeighborPts.size()<MinPts)                       //            if sizeof(NeighborPts) < MinPts
//            {
//                SetOfPoints[i]->cluster=0;                      //            mark P as NOISE
//                this->inserir(SetOfPoints[i], 0);  //insere no objeto cluster do dbscan como ru�do
//            }
//            else//se tiver vinhos>MinPts
//            {                                                   //            else
//                ClId++;                                         //            C = next cluster
//                expandCluster(SetOfPoints[i],NeighborPts,ClId,Eps,MinPts);    //            expandCluster(P, NeighborPts, C, eps, MinPts)
//                this->inserir(SetOfPoints[i], ClId);
//            }

//        }
//    }
//}

//void World::inserir(Agents * P, int ClID)
//{
//    //    if(this->clusters.size() < ClID+1 )
//    //    {
//    //        clusters.push_back(map<int,Agents*>());
//    //    } //se n�o existirem clusters suficientes
//    //    map<int,Agents*>& c =this->clusters[ClID]; // & � uma referencia, usado para alterar o valor do mapa em clusters[ClID] diretamente
//    //    c.insert(make_pair(P->get_id(),P));
//}

//void World::remover(Agents * P, int ClID)
//{
//    map<int,Agents*>& c =this->clusters[ClID]; // & � uma referencia, usado para alterar o valor do mapa em clusters[ClID] diretamente
//    c.erase(P->get_id());//elimina o item cuja chave � P->get_id()
//}













