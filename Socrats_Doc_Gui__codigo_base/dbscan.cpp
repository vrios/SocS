//#include "dbscan.h"
#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>




//vector <Agents* > World::regionQuery(Agents* ag1, double Eps)
//{//função que calcula as distancias.
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

    vector<vector<int> > & ts_nt = this->time_series_of_clusters[this->num_turnos];
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

    //    for (  it=this->m_clusters.begin(); it!=this->m_clusters.end();it++)
    //    {
    //        //this->time_series_of_clusters[this->num_turnos][it->first].push_back(it2->first);
    //            this->time_series_of_clusters[this->num_turnos][j].push_back(it->second);
    //            j++;
    //        }
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


vector<double> World::output_tam_cluster()
{
    //retorna o tamanho medio dos clusters
    vector <double> vec_tams_medios;//tamanhos medios para toda a simulação
    vector <double> vec_tamanhos;//tamanhos dos clusters para cada passo de tempo
    for ( int i=0; i < this->time_series_of_clusters.size(); i++)
    {
        double tam_medio=0;
        double soma_tams = 0;
        vec_tamanhos.clear();

        //tamanho de cada cluster exceto ruido
        for (int j=1; j< this->time_series_of_clusters[i].size(); j++)
        {
            int tam_clust=0;
            //   for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)
            {
                //tam_clust++;
                vec_tamanhos.push_back(this->time_series_of_clusters[i][j].size()-1);
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
        else //pra resolver problemas de divisão por zero
        {
//            vec_tams_medios.push_back(std::numeric_limits<double>::quiet_NaN());
            vec_tams_medios.push_back(0);
        }
    }
    return vec_tams_medios;
}

vector<double> World::output_sd_cluster()
{
    //retorna os desvios padrao, nao as variancias
    vector <double> vec_tams_medios;//tamanhos medios para toda a simulação
    vector <double> vec_tamanhos;//tamanhos dos clusters para cada passo de tempo
    vector <double> vec_sd;
    for ( int i=0; i < this->time_series_of_clusters.size(); i++)

    {
        double tam_medio=0;
        double soma_tams = 0;
        double sd_tam = 0;
        vec_tamanhos.clear();

        //tamanho de cada cluster exceto ruido
        for (int j=1; j< this->time_series_of_clusters[i].size(); j++)
        {
            int tam_clust=0;
            //  for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)
            {
                //                tam_clust++;
                //                vec_tamanhos.push_back(tam_clust);
                vec_tamanhos.push_back(this->time_series_of_clusters[i][j].size());
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
            vec_sd.push_back(sqrt((double)temp_somaQuad/(double)vec_tamanhos.size()));
        }
        else {vec_sd.push_back(std::numeric_limits<double>::quiet_NaN());}//pra resolver problemas de divisão por zero
    }
    return vec_sd;
}

vector<double> World::out_num_clust()
{
    //retorna o numero    de clusters
    vector <double> temp;
    temp.clear();
    //   temp.resize(this->time_series_of_clusters.size());
    // for ( int i=0; i < this->time_series_of_clusters.size(); i++)
    //   {
    for (int i=0; i < this->time_series_of_clusters.size(); i++ )
    {
        if(this->time_series_of_clusters[i].size()!=0)
                {temp.push_back(this->time_series_of_clusters[i].size()-1);}
        else
        {temp.push_back(0);}

    }

    // }
    return temp;
}

vector<string> World::out_clust()
{
    //retorna o conteudo dos clusters
    vector<string> temp;
    temp.resize(this->time_series_of_clusters.size());

    for (int i=0; i < this->time_series_of_clusters.size(); i++ )
        //output de todos os clusters, inclusive ruído
    {
        for (int j=0; j< this->time_series_of_clusters[i].size(); j++)
        {
            temp[i]+="[";
            for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)
            {
                temp[i]+=to_string(this->time_series_of_clusters[i][j][k])+" ";
            }
            temp[i]+="]";
        }
    }
    return temp;
}


//void World::expandCluster(Agents* P,vector<Agents*> NeighborPts, int Cluster_Id, double Eps, int MinPts)
//{                                                                   //pseudocodigo da wikipedia
//    P->cluster=Cluster_Id;                                                //   add P to cluster C
//    for (int i=0;i<NeighborPts.size();i++)                          //   for each point P' in NeighborPts
//    {//busca viznhos de P
//        if (!NeighborPts[i]->visitado)                              //      if P' is not visited
//        {
//            NeighborPts[i]->visitado=true;                          //         mark P' as visited
//            NeighborPts[i]->cluster=Cluster_Id;
//            vector<Agents*>NeighborPts2=regionQuery(P,Eps);         //         NeighborPts' = regionQuery(P', eps)
//            //busca os vizinhos do ponto vzinho a P
//            if(NeighborPts2.size() >= MinPts)                       //         if sizeof(NeighborPts') >= MinPts
//            {//caso haja o vizinho de P tenha na sua vizinhança mais pontos q o mínimo para formar clusters, une as vizinhanças em um cluster só
//                for (int j = 0; j < (int)NeighborPts2.size(); j++)  //            NeighborPts = NeighborPts joined with NeighborPts'
//                {
//                    if (!NeighborPts2[j]->visitado) NeighborPts2[j]->visitado= true;
//                    if (NeighborPts2[j]->cluster != Cluster_Id)
//                    {
//                        NeighborPts2[j]->cluster = Cluster_Id;
//                        //NeighborPts.push_back(NeighborPts2[j]);
//                    }
//                }

//            }
//        }
//        if(NeighborPts[i]->cluster=0)                               //      if P' is not yet member of any cluster
//        {
//            NeighborPts[i]->cluster=Cluster_Id;                            //         add P' to cluster C
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

//    int Cluster_Id = 0;// numero do cluster. ruído é cluster zero
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
//                this->inserir(SetOfPoints[i], 0);  //insere no objeto cluster do dbscan como ruído
//            }
//            else//se tiver vinhos>MinPts
//            {                                                   //            else
//                Cluster_Id++;                                         //            C = next cluster
//                expandCluster(SetOfPoints[i],NeighborPts,Cluster_Id,Eps,MinPts);    //            expandCluster(P, NeighborPts, C, eps, MinPts)
//                this->inserir(SetOfPoints[i], Cluster_Id);
//            }

//        }
//    }
//}

//void World::inserir(Agents * P, int Cluster_Id)
//{
//    //    if(this->clusters.size() < Cluster_Id+1 )
//    //    {
//    //        clusters.push_back(map<int,Agents*>());
//    //    } //se não existirem clusters suficientes
//    //    map<int,Agents*>& cluster =this->clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
//    //    cluster.insert(make_pair(P->get_id(),P));
//}

//void World::remover(Agents * P, int Cluster_Id)
//{
//    map<int,Agents*>& cluster =this->clusters[Cluster_Id]; // & é uma referencia, usado para alterar o valor do mapa em clusters[Cluster_Id] diretamente
//    cluster.erase(P->get_id());//elimina o item cuja chave é P->get_id()
//}













