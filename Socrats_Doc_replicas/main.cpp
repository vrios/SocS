#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>


#include <../Socrats_Doc_Gui__codigo_base/world.h>
#include <../Socrats_Doc_Gui__codigo_base/space.h>


string create_filename(string filename, int type, int replica, int tam, int num_agentes, int raio, int eps, int minPts, int tam_mem, double mem_mod, int interacoes);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);


    if (argc != 12)

    {
        std::cerr << "argument required" << endl;
        std::cerr<< "lista de argumentos: tamanho, numero de agentes, raio de acao, semente, numero de replicas, numero de turnos, eps, minPts, tipo de memoria, tamanho da memoria, modificador de memoria"<<endl;


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
        //int tipo_mem;//=atoi (argv[9]);
        int tam_mem=atoi (argv[10]);
        double mem_mod=atof (argv[11]);
        int replica = 0;
        // bool worldExists=false;
        //World ptrMundo;
        for (int tipo_mem=0;tipo_mem<=2;tipo_mem++)//cicles through all memory types
            //0=individual
            //1=grupal
            //2= no recognition
        {
            for (replica=0; replica<num_replicas;replica++)
            {
                srand(seed);
                //if(ptrMundo)
                // if (worldExists==true){ptrMundo.~World();}
                World  ptrMundo  (tam, num_agentes, raio, eps, minPts, tam_mem, tipo_mem, mem_mod, interacoes, replica);
                //worldExists=true;
                space ptrMySpace(
                            tam,
                            raio,
                            ptrMundo);


                for (int j=0; j<interacoes; j++)
                {
                    ptrMundo.update(ptrMySpace);
                }


                //tamanhos dos clusters
                fstream registro;
                registro.open(create_filename("MeanSizeOfClusters",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem, mem_mod,  interacoes)
                              , ios::out | ios::trunc);//cria o arquivo
                registro.precision(5);
                registro << setiosflags(ios::fixed)<<showpoint;
                vector <double> out = ptrMundo.output_tam_cluster();
                for (int w=0; w<out.size();w++)
                {
                    registro<<out[w]<<endl;
                }
                registro.close();

                // desvio padrao dos tamanhos dos clusters
                vector <double> out2 = ptrMundo.output_sd_cluster();
                fstream registro2;
                registro2.open(create_filename("StandardDevOfClustSize",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  mem_mod,  interacoes)
                               , ios::out | ios::trunc);//cria o arquivo
                registro2.precision(5);
                registro2 << setiosflags(ios::fixed)<<showpoint;
                //registro<<"tamanho medio dos clusters"<<endl;
                for (int w=0; w<out2.size();w++)
                {
                    registro2<<out2[w]<<endl;
                }
                registro2.close();

                // numero de clusters
                vector <double> out3 = ptrMundo.out_num_clust();
                fstream registro3;
                registro3.open(create_filename("numberOfClusters",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  mem_mod,  interacoes)
                               , ios::out | ios::trunc);//cria o arquivo
                registro3.precision(5);
                registro3 << setiosflags(ios::fixed)<<showpoint;
                //registro<<"tamanho medio dos clusters"<<endl;
                for (int w=0; w<out3.size();w++)
                {
                    registro3<<out3[w]<<endl;
                }
                registro3.close();

                //conte�do dos clusters
                fstream r_content;
                r_content.open(create_filename("clusterContent",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  mem_mod,  interacoes), ios::out | ios::trunc);//cria o arquivo
                vector<string> out_c=ptrMundo.out_clust_content();
                for (int w=0; w<out.size();w++)
                {
                    r_content<<out_c[w]<<endl;
                }
                r_content.close();

                //sa�da das redes de intera�?o espaciais finais
                fstream network;
                network.open(create_filename("finalSpaceEdges",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  mem_mod,  interacoes), ios::out | ios::trunc);//cria o arquivo
                string space_edges = ptrMundo.out_spatial_final_edges();
                network<<"Source;Target;Weight;Type"<<"\n";
                network<< space_edges;
                network.close();

                //            //sa�da das redes de intera�?o espaciais dinamicas
                //            //which individuals are in the same cluster in a given moment
                //            fstream dyn_edges;
                //            dyn_edges.open(create_filename("dynSpacEdges",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  interacoes), ios::out | ios::trunc);//cria o arquivo
                //            string d_edges=ptrMundo.out_spatial_dynamic_edges();
                //            dyn_edges<<"Source;Target;Time_initial\n";
                //            //Type;
                //            //Time_final\n";
                //            //for (int e=0; e<d_edges.size();e++)
                //            //{
                //                dyn_edges<<d_edges;
                //            //}
                //            dyn_edges.close();

                //sa�da das redes de intera�?o sociais finais
                fstream social;
                social.open(create_filename("finalSocEdges",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  mem_mod,  interacoes), ios::out | ios::trunc);//cria o arquivo
                string soc_edges=ptrMundo.out_social_final_edges();
                social<<"Source;Target;Weight\n";
                //for (int x =0; x<soc_edges.size();x++)
                //{
                social<<soc_edges;
                //}
                social.close();

                //            fstream dyn_social;
                //            dyn_social.open(create_filename("dynSocEdges",tipo_mem, replica,  tam,  num_agentes,  raio,  eps,  minPts,  tam_mem,  interacoes), ios::out | ios::trunc);//cria o arquivo
                //            string dyn_soc_edges=ptrMundo.out_social_dynamic_edges();
                //            dyn_social<<"Source;Target;Weight;Time_initial;\n";
                //            //for (int x =0; x<dyn_soc_edges.size();x++)
                //            //{
                //                dyn_social<<dyn_soc_edges;
                //            //}
                //            dyn_social.close();

                // fim do mundo
                //  ptrMundo.~World();

                seed++;
            }
        }
    }
    // system("commit.bat");
    return 0;
}

string create_filename(string filename, int type, int replica, int tam, int num_agentes, int raio, int eps, int minPts, int tam_mem, double mem_mod, int interacoes)
{
    string t;
    if (type == 0) {t="i_";}
    if (type == 1) {t="g_";}
    if (type == 2) {t="nr_";}
    string name = t + filename +
            "_tam_"+to_string((int)tam)+
            "_ags_"+to_string(num_agentes)+
            "_raio_"+to_string(raio)+
            "_eps_"+to_string(eps)+
            "_mPts_"+to_string(minPts)+
            "_nTurnos_"+to_string(interacoes)+
            "_tMem_"+to_string(tam_mem)+
            "_MemMod_"+to_string(mem_mod) +
            "_rep_"+ to_string(replica)+
            ".txt";
    return name;
}
