#include "world.h"

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
             for (int k=0;k<this->time_series_of_clusters[i][j].size();k++)
            {
                temp[i]+=to_string(this->time_series_of_clusters[i][j][k])+" ";
            }
            temp[i]+=" ,";
        }
    }
    return temp;
}

vector <string> World::out_network()
{
    vector <string> temp;
    temp.resize(this->vec_ptr_Agentes.size());
    for (auto i : this->vec_ptr_Agentes)
    {
        this->vec_ptr_Agentes(i).out_mem();
    }

}















