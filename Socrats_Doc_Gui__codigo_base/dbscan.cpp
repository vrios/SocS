#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>
#include "space.h"


///// original algorithm from ester et al 1996 is marked with ///***comments

map<int, Agents *> World::get_map_of_reachable_Neighbors(Agents* ag1, double Eps, space &MySpace)
{
    map <int, Agents*> listViz;
//    for (int j=0;j<this->vec_ptr_Agentes.size();j++)
//    {
//        //vai de vizinho em vizinho
//        Agents* ag2= this->vec_ptr_Agentes[j];
//        if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
//        double d=distTorus(ag1,ag2, X);
//        if (d<=Eps) // se estiver dentro da distancia Epsilon
//        {listViz.insert( pair<int, Agents*> (ag2->get_id(),ag2 ));}
//    }
    listViz= MySpace.Map_Range_query(ag1,Eps, *this);
    return listViz;
}


void World::DBSCAN (vector<Agents* >& SetOfPoints, double Eps, int MinPts, space &MySpace)
///***DBSCAN (SetOfPoints, Eps, MinPts)
{
    for (int p =0; p<SetOfPoints.size();p++)// para garantir que o dbscan funciona sequencialmente
    {
        SetOfPoints[p]->MyCluster=-1;
        // SetOfPoints[p]->visitado=false;
    }
    this->map_of_clusters.clear();//limpando o mapa de clusters
    // this->map_of_clusters.insert(make_pair(0,  map<int,Agents*> ()));


    int ClusterId = 1;///***ClusterId := nextId(NOISE);//0 é ruído

    for (int i =0; i<SetOfPoints.size();i++)///***FOR i FROM 1 TO SetOfPoints.size DO
    {
        Agents* Point = SetOfPoints[i];///***	Point := SetOfPoints.get(i);
        //if (!Point->visitado)///***	IF Point.ClId = UNCLASSIFIED THEN
        if (Point->MyCluster==-1)///***	IF Point.ClId = UNCLASSIFIED THEN ///-1 é unvisited
        {
            if(this->ExpandCluster(SetOfPoints, Point, ClusterId, Eps, MinPts, MySpace) )///***		IF ExpandCluster(SetOfPoints, Point, ClusterId, Eps, MinPts) THEN
            {
                ClusterId ++;///***			ClusterId := nextId(ClusterId)
            }///***		END IF
        }///***	END IF
    }///***END FOR
    //end DBSCAN

    //adding clusters to time_series_of_clusters
    map<int,map <int,Agents*> >::iterator cluster;
    map <int,Agents*>::iterator individual;

    if(this->time_series_of_clusters.size()<this->num_turnos+1)
    {this->time_series_of_clusters.push_back(vector<vector<int> >());}
    if (this->time_series_of_clusters[this->num_turnos].size()!= this->map_of_clusters.size())
    {
        this->time_series_of_clusters[this->num_turnos].resize(this->map_of_clusters.size(),vector<int>());
    }

    vector<vector<int> > & this_turn = this->time_series_of_clusters[this->num_turnos];// referencia para facilitar leitura do codigo
    int j=0;
    //int k=0;
    cluster=this->map_of_clusters.begin();
    //it++;

    for ( cluster ; cluster!=this->map_of_clusters.end();cluster++)
    {
        if (cluster->first!=0)
        {
            for (individual=cluster->second.begin();individual!=cluster->second.end();individual++)
            {
                //this->time_series_of_clusters[this->num_turnos][it->first].push_back(it2->first);
                this_turn[j].push_back(individual->first);
            }
            j++;
            // k++;
        }
    }

    // creating association network
    map<int,map <int,Agents*> >::iterator clust;
    map <int,Agents*>::iterator members;
    map <int,Agents*>::iterator others;
    clust = this->map_of_clusters.begin();
    // clust++;
    for (clust; clust !=this->map_of_clusters.end(); clust ++) // for each cluster in map of clusters, except for noise
    {
        auto test0=*clust;
        if (clust->first !=0)
        {
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
    }

    //    }
}

bool World::ExpandCluster(vector<Agents*>& SetOfPoints, Agents* Point, int Cluster_Id, double Eps, int MinPts, space &MySpace)///***ExpandCluster(SetOfPoints, Point, ClId, Eps,MinPts) : Boolean;
{
   // map <int, Agents*> reachable_Neighbors = get_map_of_reachable_Neighbors(Point,Eps);///***  seeds:=SetOfPoints.regionQuery(Point,Eps);
    map <int, Agents*> reachable_Neighbors = MySpace.Map_Range_query(Point,Eps,*this);
    if (reachable_Neighbors.size() < MinPts ) ///***  IF seeds.size<MinPts THEN // no core point
    {
        //alterar ponto pra ruido
        ///***SetOfPoint.changeClId(Point,NOISE);
        this->insert_in_cluster(Point,0);// 0 is noise
        return false;///***    RETURN False;
    }
    else
    {  // all points in reachable_Neighbors are density-reachable from Point
        ///***  ELSE   // all points in seeds are density-reachable from Point
        map <int,Agents*>::iterator neighbor = reachable_Neighbors.begin();
        for (neighbor = reachable_Neighbors.begin();neighbor!=reachable_Neighbors.end();neighbor++)
        {
            ///***SetOfPoints.changeClIds(seeds,ClId);

            this->insert_in_cluster(neighbor->second, Cluster_Id);
            neighbor->second->MyCluster=Cluster_Id;//marcar todos de SetofPoints como Cluster_Id


        }
        reachable_Neighbors.erase(Point->get_id());///***    seeds.delete(Point);

        while (!reachable_Neighbors.empty()) ///***    WHILE seeds <> Empty DO
        {
            Agents* currentPoint = reachable_Neighbors.begin()->second; ///***      currentP := seeds.first();
            map <int, Agents* > result = get_map_of_reachable_Neighbors(currentPoint,Eps, MySpace);///***      result := SetOfPoints.regionQuery(currentP, Eps);
            if( result.size() >= MinPts )///***      IF result.size >= MinPts THEN
            {
                for( neighbor= result.begin(); neighbor != result.end(); neighbor++ )///***FOR i FROM 1 TO result.size DO
                {
                    Agents* resultPoint = neighbor->second;///***resultP := result.get(i);
                    if (resultPoint->MyCluster== -1 || resultPoint->MyCluster == 0  ) ///***          IF resultP.ClId IN {UNCLASSIFIED, NOISE} THEN
                    {
                        if (resultPoint->MyCluster==-1)///***IF resultP.ClId = UNCLASSIFIED THEN
                        {
                            reachable_Neighbors.insert(pair<int,Agents*>(resultPoint->get_id(),resultPoint));///***seeds.append(resultP);
                        } ///***            END IF;
                        this->insert_in_cluster(resultPoint,Cluster_Id);///***SetOfPoints.changeClId(resultP,ClId);
                        //  resultPoint->cluster=Cluster_Id;
                        // resultPoint->visitado=true;
                    } ///***END IF; // UNCLASSIFIED or NOISE
                }///***        END FOR;
            }///***      END IF; // result.size >= MinPts
            reachable_Neighbors.erase(currentPoint->get_id());///***      seeds.delete(currentP);
        }///***    END WHILE; // seeds <> Empty
        return true;///***RETURN True;
    }///***  END IF
} ///***END; // ExpandCluster

void World::insert_in_cluster(Agents * P, int ICluster_Id)
{
    // P->visitado=true;
    if(this->map_of_clusters.find(ICluster_Id)==this->map_of_clusters.end())//se não existirem clusters suficientes
    {
        this->map_of_clusters.insert(make_pair(ICluster_Id, map<int,Agents*> ()));
    }
    //insere no mapa
    //  if (P->MyCluster != ICluster_Id)
    //  {
    this->remove_from_cluster(P,P->MyCluster);
    // }
    map<int,Agents*>& cluster = this->map_of_clusters[ICluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
    cluster.insert(make_pair(P->get_id(),P));
    //registra no proprio ponto
    P->MyCluster=ICluster_Id;
    //  P->visitado=true;
}

void World::remove_from_cluster(Agents * P, int Cluster_Id)
{
    if (Cluster_Id != -1)
    {
        map<int,Agents*>& cluster =this->map_of_clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
        if(cluster.find(P->get_id())!= cluster.end())
        {
            cluster.erase(P->get_id());
        }//elimina o item cuja chave é P->get_id()

    }

}
