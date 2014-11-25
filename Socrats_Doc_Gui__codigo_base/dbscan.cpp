//#include "dbscan.h"
#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>


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
    // this->m_clusters.insert(make_pair(0,  map<int,Agents*> ()));

    // SetOfPoints is UNCLASSIFIED
    int ClusterId = 1;//0 é ruído
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

    //adding clusters to time_series_of_clusters for mc1

    map<int,map <int,Agents*> >::iterator it;
    map <int,Agents*>::iterator it2;

    if(this->time_series_of_clusters.size()<this->num_turnos+1)
    {this->time_series_of_clusters.push_back(vector<vector<int> >());}

    if (this->time_series_of_clusters[this->num_turnos].size()!= this->m_clusters.size()-1)
    {this->time_series_of_clusters[this->num_turnos].resize(this->m_clusters.size()-1,vector<int>());}

    vector<vector<int> > & ts_nt = this->time_series_of_clusters[this->num_turnos];// referencia para facilitar leitura do codigo
    int j=0;
    int k=0;
    it=this->m_clusters.begin();
    it++;

    for ( it ; it!=this->m_clusters.end();it++)
    {
        for (it2=it->second.begin();it2!=it->second.end();it2++)
        {
            //this->time_series_of_clusters[this->num_turnos][it->first].push_back(it2->first);
            ts_nt[j].push_back(it2->first);
        }
        j++;
        k++;
    }

      //    }
}

bool World::ExpandCluster(vector<Agents*>& SetOfPoints, Agents* Point, int Cluster_Id, double Eps,int MinPts)
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
        // SetOfPoints.changeClIds(seeds,Cluster_Id);//marcar todos de SetofPoints como ClI
        //        for (int k =0; k<seeds.size();k++)
        //        {
        //            seeds[k]->cluster=Cluster_Id;
        //        }
        map <int,Agents*>::iterator it = seeds.begin();//usando iterador e as porra!
        for (it = seeds.begin();it!=seeds.end();it++) {it->second->cluster=Cluster_Id;}//marcar todos de SetofPoints como Cluster_Id

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
                        // SetOfPoints.changeClId(resultP,Cluster_Id);
                        this->inserir(resultP,Cluster_Id);
                        //  resultP->cluster=Cluster_Id;
                        //resultP->visitado=true;
                    } // UNCLASSIFIED or NOISE
                }
            } // result.size >= MinPts
            seeds.erase(currentP->get_id());
        } // seeds <> Empty
        return true;
    }
} // ExpandCluster

void World::inserir(Agents * P, int Cluster_Id)
{
    P->visitado=true;
    if(this->m_clusters.find(Cluster_Id)==this->m_clusters.end())//se não existirem clusters suficientes
    {this->m_clusters.insert(make_pair(Cluster_Id, map<int,Agents*> ()));}
    //insere no mapa
    if (Cluster_Id!=P->cluster)//se houve fusão dos clusters
        this->remover(P,Cluster_Id);
    map<int,Agents*>& cluster = this->m_clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
    cluster.insert(make_pair(P->get_id(),P));
    //registra no proprio ponto
    P->cluster=Cluster_Id;
    P->visitado=true;
}

void World::remover(Agents * P, int Cluster_Id)
{
    if (Cluster_Id<m_clusters.size())
    {
        map<int,Agents*>& cluster =this->m_clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
        if(cluster.find(P->get_id())!= cluster.end())
        {
            cluster.erase(P->get_id());
        }//elimina o item cuja chave é P->get_id()

    }

}

