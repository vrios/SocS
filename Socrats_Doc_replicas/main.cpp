#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<C:\Users\Vrios\Dropbox\Doutorado\codigo\socrats\Socrats_Doc_Gui__codigo_base\world.h>
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
        int interacoes = atoi (argv[6]); //recebe o numero de iterações
        int eps =atoi (argv[7]);
        int minPts=atoi (argv[8]);
        int tipo_mem=atoi (argv[9]);
        int tam_mem=atoi (argv[10]);
        int replica = 0;
        for (replica=0; replica<num_replicas;replica++)
        {
            srand(seed);
            World* ptrMundo;
            ptrMundo=new World (tam, num_agentes, raio, eps, minPts, tam_mem, tipo_mem);

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
              // to_string() é uma função do C++11 que converte qualquer tipo p string.
              //é necessário colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro.open(
                        "i_tam_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)registro.open(
                        "g_tam_clust_rep_"+to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            registro.precision(5);
            registro << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;
            for (int w=0; w<out.size();w++)
            {
                registro<<out[w]<<endl;
            }
            registro.close();

            // variancia dos tamanhos dos clusters
            vector <double> out2 = ptrMundo->output_var_cluster();
            fstream registro2;
              // to_string() é uma função do C++11 que converte qualquer tipo p string.
              //é necessário colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro2.open(
                        "i_var_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)registro2.open(
                        "g_var_clust_rep_"+to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            registro2.precision(5);
            registro2 << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;
            for (int w=0; w<out2.size();w++)
            {
                registro2<<out2[w]<<endl;
            }
            registro2.close();




            // numero de clusters
            vector <double> out3 = ptrMundo->out_num_clust();
            fstream registro3;
              // to_string() é uma função do C++11 que converte qualquer tipo p string.
              //é necessário colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro3.open(
                        "i_num_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)registro3.open(
                        "g_num_clust_rep_"+to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            registro3.precision(5);
            registro3 << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;
            for (int w=0; w<out3.size();w++)
            {
                registro3<<out3[w]<<endl;
            }
            registro3.close();


            //conteúdo dos clusters
            fstream r_content;
            if (tipo_mem == 0)r_content.open(
                        "i_cont_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)r_content.open(
                        "g_cont_clust_rep_" + to_string(replica)+
                        "_tam_"+to_string((int)tam)+
                        "_ags_"+to_string(num_agentes)+
                        "_raio_"+to_string(raio)+
                        "_eps_"+to_string(eps)+
                        "_mPts_"+to_string(minPts)+
                        "_tMem_"+to_string(tam_mem)+
                        "_nTurnos_"+to_string(interacoes)+
                        ".txt", ios::out | ios::app);//cria o arquivo
            vector<string> out_c=ptrMundo->out_clust();
            for (int w=0; w<out.size();w++)
            {
                r_content<<out_c[w]<<endl;
            }
            r_content.close();
            delete  ptrMundo;
            seed++;
        }
    }
}
