#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>


map<int, Agents *> World::get_map_of_reachable_Neighbors(Agents* ag1, double Eps)
{
    map <int, Agents*> listViz;
    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
    {
        //vai de vizinho em vizinho
        Agents* ag2= this->vec_ptr_Agentes[j];
        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
        double d=distTorus(ag1,ag2, X);
        if (d<=Eps)// se estiver dentro da distancia Epsilon
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
    this->map_of_clusters.clear();//limpando o mapa de clusters
    // this->map_of_clusters.insert(make_pair(0,  map<int,Agents*> ()));

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

    //adding clusters to time_series_of_clusters

    map<int,map <int,Agents*> >::iterator it;
    map <int,Agents*>::iterator it2;
 //auto walla=  this->map_of_clusters[1];
    if(this->time_series_of_clusters.size()<this->num_turnos+1)
    {this->time_series_of_clusters.push_back(vector<vector<int> >());}

    if (this->time_series_of_clusters[this->num_turnos].size()!= this->map_of_clusters.size()-1)
    {this->time_series_of_clusters[this->num_turnos].resize(this->map_of_clusters.size()-1,vector<int>());}

    vector<vector<int> > & ts_nt = this->time_series_of_clusters[this->num_turnos];// referencia para facilitar leitura do codigo
    int j=0;
    int k=0;
    it=this->map_of_clusters.begin();
    it++;

    for ( it ; it!=this->map_of_clusters.end();it++)
    {
        for (it2=it->second.begin();it2!=it->second.end();it2++)
        {
            //this->time_series_of_clusters[this->num_turnos][it->first].push_back(it2->first);
            ts_nt[j].push_back(it2->first);
        }
        j++;
        k++;
    }

    // creating association network
    map<int,map <int,Agents*> >::iterator clust;
    map <int,Agents*>::iterator members;
    map <int,Agents*>::iterator others;
    for (clust = this->map_of_clusters.begin(); clust !=this->map_of_clusters.end(); clust ++) // for each cluster in map of clusters
    {
        auto test0=*clust;
        for (members = clust->second.begin(); members!=clust->second.end();members++)//for each cluster member in clust
        {
            auto test1 = *members; //dereferenciar o iterador permite acessar o conteudo diretamente, assim como um ponteiro
            for(others = clust->second.begin(); others!=clust->second.end();others++)
            {
                auto test2 = *others;
                if( test1.first!=test2.first)
                {
                    this->spatial_network[test1.first][test2.first]++;
                }
            }
        }
    }

      //    }
}

bool World::ExpandCluster(vector<Agents*>& SetOfPoints, Agents* Point, int Cluster_Id, double Eps,int MinPts)
{
    map <int, Agents*> seeds = get_map_of_reachable_Neighbors(Point,Eps);
    if (seeds.size()< MinPts )  // no core point
    {
        //alterar ponto pra ruido
        //Point->cluster=0;
        this->insert_in_cluster(Point,0);// 0 is noise
        return false;
    }
    else
    {  // all points in seeds are density-reachable from Point

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
            Agents* currentPoint = seeds.begin()->second;
            map <int, Agents* > result = get_map_of_reachable_Neighbors(currentPoint,Eps);
            if( result.size() >= MinPts )
            {
                for( it= result.begin(); it != result.end(); it++ )
                {
                    //Agents* resultPoint = result[it];
                    Agents* resultPoint = it->second;
                    if (!resultPoint->visitado)
                    {
                        if (resultPoint->cluster == 0 )
                        {
                            seeds.insert(pair<int,Agents*>(resultPoint->get_id(),resultPoint));
                        }
                        // SetOfPoints.changeClId(resultPoint,Cluster_Id);
                        this->insert_in_cluster(resultPoint,Cluster_Id);
                        //  resultPoint->cluster=Cluster_Id;
                        //resultPoint->visitado=true;
                    } // UNCLASSIFIED or NOISE
                }
            } // result.size >= MinPts
            seeds.erase(currentPoint->get_id());
        } // seeds <> Empty
        return true;
    }
} // ExpandCluster

void World::insert_in_cluster(Agents * P, int Cluster_Id)
{
    P->visitado=true;
    if(this->map_of_clusters.find(Cluster_Id)==this->map_of_clusters.end())//se não existirem clusters suficientes
    {this->map_of_clusters.insert(make_pair(Cluster_Id, map<int,Agents*> ()));}
    //insere no mapa
    if (Cluster_Id!=P->cluster)//se houve fusão dos clusters
        this->remove_from_cluster(P,Cluster_Id);
    map<int,Agents*>& cluster = this->map_of_clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
    cluster.insert(make_pair(P->get_id(),P));
    //registra no proprio ponto
    P->cluster=Cluster_Id;
    P->visitado=true;
}

void World::remove_from_cluster(Agents * P, int Cluster_Id)
{
    if (Cluster_Id<map_of_clusters.size())
    {
        map<int,Agents*>& cluster =this->map_of_clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
        if(cluster.find(P->get_id())!= cluster.end())
        {
            cluster.erase(P->get_id());
        }//elimina o item cuja chave é P->get_id()

    }

}

