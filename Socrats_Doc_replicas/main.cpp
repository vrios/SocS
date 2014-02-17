#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<C:\Users\Vrios\Dropbox\Doutorado\codigo\testes de clusters_b\Socrats_Doc_Gui__codigo_base\world.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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
        int tam_mem=atoi (argv[9]);
        int tipo_mem=atoi (argv[10]);
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

            vector <double> out = ptrMundo->output_tam_cluster();

            fstream registro;
            // to_string() é uma função do C++11 que converte qualquer tipo p string.
            //é necessário colocar a macro QMAKE_CXXFLAGS += -std=c++11 no arquivo.pro p fazer funcionar
            if (tipo_mem == 0)registro.open("i_"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            if (tipo_mem == 1)registro.open("g_"+to_string(replica)+".txt", ios::out | ios::app);//cria o arquivo
            registro.precision(5);
            registro << setiosflags(ios::fixed)<<showpoint;
            //registro<<"tamanho medio dos clusters"<<endl;

            for (int w=0; w<out.size();w++)
            {
                registro<<out[w]<<endl;
            }
            delete  ptrMundo;
            //cout<<"fim "<<replica<<endl;
            registro.close();
            seed++;
          // replica++;
        }
    //    return 0;
    }

    a.quit();
    exit;;;
   // return a.exec();
}
