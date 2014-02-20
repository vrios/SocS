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
            if (tipo_mem == 0)registro.open("i_tam-clust"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)registro.open("g_tam-clust"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            registro.precision(5);
            registro << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;
            for (int w=0; w<out.size();w++)
            {
                registro<<out[w]<<endl;
            }
            registro.close();
            //conteúdo dos clusters
            fstream r_content;
            if (tipo_mem == 0)r_content.open("i_cont-clust"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)r_content.open("g_cont-clust"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            vector<string> out_c=ptrMundo->out_clust();
            for (int w=0; w<out.size();w++)
            {
                r_content<<out_c[w]<<endl;
            }

            r_content.close();
            delete  ptrMundo;
            //cout<<"fim "<<replica<<endl;
            seed++;
          // replica++;
        }
    //    return 0;
    }

//    a.quit();
//   // QCoreApplication::quit();
//    return
//    a.exec();
   // return(0);
}
