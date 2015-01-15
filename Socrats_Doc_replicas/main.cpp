#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>

//#include </home/vrios/Documents/codigo/socrats/Socrats_Doc_Gui__codigo_base/world.h>
//#include <C:\Users\Vrios\Dropbox\Doutorado\codigo\socrats\Socrats_Doc_Gui__codigo_base\world.h>
#include <..\Socrats_Doc_Gui__codigo_base\world.h>

string create_filename(string filename, int type, int replica, int tam, int num_agentes, int raio, int eps, int minPts, int tam_mem, int interacoes);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    if (argc != 11)

    {
        std::cerr << "argument required" << endl;
        std::cerr<< "lista de argumentos: tamanho, numero de agentes, raio de acao, semente, numero de replicas, numero de turnos, eps, minPts, tipo de memoria, tamanho da memoria"<<endl;


        return 1;
    }
    else
    {
        double tam=atoi (argv[1]);
        int num_agentes = atoi(argv[2]);//converte o valor de argv[1] de char para int
        int raio = atoi(argv[3]);
        double seed = atof(argv[4]);
        int num_replicas = atoi(argv[5]);
        int interacoes = atoi (argv[6]); //recebe o numero de intera��es
        int eps =atoi (argv[7]);
        int minPts=atoi (argv[8]);
        int tipo_mem=atoi (argv[9]);
        int tam_mem=atoi (argv[10]);
        int replica = 0;
        for (replica=0; replica<num_replicas;replica++)
        {
            srand(seed);
            //if(ptrMundo)

            World* ptrMundo;
            ptrMundo=new World (tam, num_agentes, raio, eps, minPts, tam_mem, tipo_mem, interacoes);

            if (tipo_mem==1)
            {
                for (int j=0; j<interacoes; j++)
                {
                    ptrMundo->update2_g();
                }
            }

            if (tipo_mem==0)
            {
                for (int j=0; j<interacoes; j++)
                {
                    ptrMundo->update2_i();
                }
            }

            //tamanhos dos clusters
            vector <double> out = ptrMundo->output_tam_cluster();
            fstream registro;
            // to_string() � uma fun��o do C++11 que converte qualquer tipo p string.
            //� necess�rio colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro.open(
                        "i_tam_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            if (tipo_mem == 1)registro.open(
                        "g_tam_clust_rep_"+to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            registro.precision(5);
            registro << setiosflags(ios::fixed)<<showpoint;
           for (int w=0; w<out.size();w++)
            {
                registro<<out[w]<<endl;
            }
            registro.close();

//            // desvio padrao dos tamanhos dos clusters
//            vector <double> out2 = ptrMundo->output_sd_cluster();
//            fstream registro2;
//            // to_string() � uma fun��o do C++11 que converte qualquer tipo p string.
//            //� necess�rio colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
//            if (tipo_mem == 0)registro2.open(
//                        "i_sd_clust_rep_" + to_string(replica)+
//                        "_tam_"+to_string((int)tam)+
//                        "_ags_"+to_string(num_agentes)+
//                        "_raio_"+to_string(raio)+
//                        "_eps_"+to_string(eps)+
//                        "_mPts_"+to_string(minPts)+
//                        "_tMem_"+to_string(tam_mem)+
//                        "_nTurnos_"+to_string(interacoes)+
//                        ".txt", ios::out | ios::trunc);//cria o arquivo
//            if (tipo_mem == 1)registro2.open(
//                        "g_sd_clust_rep_"+to_string(replica)+
//                        "_tam_"+to_string((int)tam)+
//                        "_ags_"+to_string(num_agentes)+
//                        "_raio_"+to_string(raio)+
//                        "_eps_"+to_string(eps)+
//                        "_mPts_"+to_string(minPts)+
//                        "_tMem_"+to_string(tam_mem)+
//                        "_nTurnos_"+to_string(interacoes)+
//                        ".txt", ios::out | ios::trunc);//cria o arquivo
//            registro2.precision(5);
//            registro2 << setiosflags(ios::fixed)<<showpoint;
//            //registro<<"tamanho medio dos clusters"<<endl;
//            for (int w=0; w<out2.size();w++)
//            {
//                registro2<<out2[w]<<endl;
//            }
//            registro2.close();

            // numero de clusters
            vector <double> out3 = ptrMundo->out_num_clust();
            fstream registro3;
            // to_string() � uma fun��o do C++11 que converte qualquer tipo p string.
            //� necess�rio colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro3.open(
                        "i_num_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            if (tipo_mem == 1)registro3.open(
                        "g_num_clust_rep_"+to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            registro3.precision(5);
            registro3 << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;
            for (int w=0; w<out3.size();w++)
            {
                registro3<<out3[w]<<endl;
            }
            registro3.close();


//            //conte�do dos clusters
//            fstream r_content;
//            if (tipo_mem == 0)r_content.open(
//                        "i_cont_rep_" + to_string(replica)+
//                        "_tam_"+to_string((int)tam)+
//                        "_ags_"+to_string(num_agentes)+
//                        "_raio_"+to_string(raio)+
//                        "_eps_"+to_string(eps)+
//                        "_mPts_"+to_string(minPts)+
//                        "_tMem_"+to_string(tam_mem)+
//                        "_nTurnos_"+to_string(interacoes)+
//                        ".txt", ios::out | ios::trunc);//cria o arquivo
//            if (tipo_mem == 1)r_content.open(
//                        "g_cont_rep_" + to_string(replica)+
//                        "_tam_"+to_string((int)tam)+
//                        "_ags_"+to_string(num_agentes)+
//                        "_raio_"+to_string(raio)+
//                        "_eps_"+to_string(eps)+
//                        "_mPts_"+to_string(minPts)+
//                        "_tMem_"+to_string(tam_mem)+
//                        "_nTurnos_"+to_string(interacoes)+
//                        ".txt", ios::out | ios::trunc);//cria o arquivo
//            vector<string> out_c=ptrMundo->out_clust_content();
//            for (int w=0; w<out.size();w++)
//            {
//                r_content<<out_c[w]<<endl;
//            }
//            r_content.close();

            //sa�da das redes de intera�?o totais
           // ptrMundo->out_network();
            fstream network;
            if (tipo_mem == 0)network.open(
                        "i_rede_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            if (tipo_mem == 1)network.open(
                        "g_rede_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo

            network<<"Source;Target;Weight;Type"<<"\n";
            for (int i=0; i<ptrMundo->spatial_network.size(); i++)
            {
                for (int j=0; j<ptrMundo->spatial_network.size();j++)
                {
                   if (i!=j){ network<<i<<";"<<j<<";"<<ptrMundo->spatial_network[i][j] <<";undirected"<<"\n";}
                }
               // network<<"\n";
            }

            network.close();

            //sa�da das redes de intera�?o dinamicas
           // ptrMundo->out_network();
            fstream dyn_edges;
            if (tipo_mem == 0)dyn_edges.open(
                        "i_dynedge_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo
            if (tipo_mem == 1)dyn_edges.open(
                        "g_dynedge_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::trunc);//cria o arquivo

             vector<string> d_edges=ptrMundo->out_spatial_dynamic_edges();
             dyn_edges<<"Source;Target;Time_initial\n";
             //Type;
             //Time_final\n";
             for (int e=0; e<d_edges.size();e++)
             {
                 dyn_edges<<d_edges[e]
                            //<<endl
                            ;
             }
             dyn_edges.close();

             fstream dyn_social;
             dyn_social.open(create_filename("dynsoc",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  interacoes), ios::out | ios::trunc);//cria o arquivo
             vector<string> soc_edges=ptrMundo->out_social_dynamic_edges();
                dyn_social<<"Source;Target;Weight;Time_initial;\n";
             for (int x =0; x<soc_edges.size();x++)

             {
                 dyn_social<<soc_edges[x];
             }

            //fim do mundo
            delete  ptrMundo;
            seed++;
        }
    }
return 0;
}

string create_filename(string filename, int type, int replica, int tam, int num_agentes, int raio, int eps, int minPts, int tam_mem, int interacoes)
{
    string t;
    if (type == 0) {t="i_";}
    if (type == 1) {t="g_";}
    string name = t+filename + "_rep_"+ to_string(replica)+
            "_tam_"+to_string((int)tam)+
            "_ags_"+to_string(num_agentes)+
            "_raio_"+to_string(raio)+
            "_eps_"+to_string(eps)+
            "_mPts_"+to_string(minPts)+
            "_tMem_"+to_string(tam_mem)+
            "_nTurnos_"+to_string(interacoes)+
            ".txt";
    return name;
}
