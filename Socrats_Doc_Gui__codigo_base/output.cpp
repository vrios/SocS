#include "world.h"
#include "agents.h"
#include <limits>
#include <math.h>
#include <string>

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

        //tamanho de cada cluster
        for (int j=0; j< this->time_series_of_clusters[i].size(); j++)
        {
            int tam_clust=0;
            //   for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)
            {
                //tam_clust++;
                vec_tamanhos.push_back(this->time_series_of_clusters[i][j].size());
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

        //tamanho de cada cluster
        for (int j=0; j< this->time_series_of_clusters[i].size(); j++)
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
    for (int i=0; i < this->time_series_of_clusters.size(); i++ )
    {
        if(this->time_series_of_clusters[i].size()!=0)
        {temp.push_back(this->time_series_of_clusters[i].size());}
        else
        {temp.push_back(0);}

    }

    return temp;
}

vector<string> World::out_clust_content()
{
    //retorna o conteudo dos clusters
    vector<string> temp;
    temp.resize(this->time_series_of_clusters.size());

    for (int i=0; i < this->time_series_of_clusters.size(); i++ )//para cada momento
        //output de todos os clusters, inclusive ruído
    {
        for (int j=0; j< this->time_series_of_clusters[i].size(); j++)//para cada cluster // inclusive ruido
        {
            if(!this->time_series_of_clusters[i].empty())
            {
                for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)// para cada individuo
                {
                    temp[i]+=to_string(this->time_series_of_clusters[i][j][k])+" ";
                }
                temp[i]+=", ";
            }
        }
    }
    return temp;
}

string World::out_spatial_final_edges(){
    string temp="";
    for (int i=0; i<this->spatial_network.size(); i++)
    {
        for (int j=0; j<this->spatial_network.size();j++)
        {
            // if (i<j)//only the lower triangle, no repeated edges
            if (i!=j)
            {temp +=  to_string(i) + ";" + to_string(j) + ";" + to_string(this->spatial_network[i][j]) + ";u"+"\n";}
        }
    }
    return temp;
}

string World::out_spatial_dynamic_edges()
{

    string temp = "";
    //temp.resize(this->time_series_of_clusters.size());
    for (int t=0; t < this->time_series_of_clusters.size(); t++ )//para cada momento
    {
        if (this->time_series_of_clusters[t].size()!=0)
        {
            for (int j=0; j< this->time_series_of_clusters[t].size(); j++)//para cada cluster
            {
                for (int k=0;k<this->time_series_of_clusters[t][j].size();k++)//para cada individuo do cluster
                {
                    for (int l=0;l<this->time_series_of_clusters[t][j].size();l++)//para cada outro individuo do cluster
                    {
                        // if(k<l)//only the lower triangle, no repeated edges
                        if(k<l)
                        {
                            temp+=to_string(this->time_series_of_clusters[t][j][k]) + ";" + to_string(this->time_series_of_clusters[t][j][l])
                                    +";"
                                    +to_string(t)
                                    +"\n";
                        }
                    }
                }
            }
        }
    }

    return temp;
}
string World::out_social_final_edges()
{
    string temp="";
    for (int i=0; i<this->cumulative_interactions.size(); i++)
    {
        for (int j=0; j<this->cumulative_interactions.size();j++)
        {
            // if(i<j)//only the lowertriangle, no repeated edges
            if (i!=j)
            { temp += to_string(i) + ";" + to_string(j) + ";" + to_string(cumulative_interactions[i][j])+"\n";}
        }
    }
    return temp;
}

string World::out_social_dynamic_edges()
{
    //retorna o conteudo dos clusters
    string temp ="";
    //temp.resize(this->social_network.size());
    for (int t=0; t < this->social_network.size(); t++ )//para cada momento
    {
        for (int i=0; i<this->social_network[t].size(); i++)
        {
            for (int j=0; j<this->social_network[t][i].size();j++)
            {
                if (
                        //i<j &&
                        this->social_network[t][i][j] !=0)
                { temp += to_string(i)+";"+to_string(j)+";"+to_string(this->social_network[t][i][j])+";"+to_string(t)+"\n";}
            }
        }
    }

    return temp;
}
