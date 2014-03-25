#ifndef WORLD_H
#define WORLD_H
#include "agents.h"
//#include "grid.h"

#include <vector>
#include <map>
//#include "dbscan.h"

//#include"mainwindow.h"
using namespace std;


//class MainWindow;// necessário para poder atualizar a janela a cada passo, retirar depois

class World
{
public:
    World();
    // World(double TAM, int N_agentes, int raio, double Eps, int MinPts);
    World(double TAM, int N_agentes, int raio, double Eps, int MinPts, int mem_length, int mem_type);

    int num_turnos;

    void update(// arquivo world-funcao_update.cpp
                // class MainWindow *lala
                );
    void update2(
            //class MainWindow *lala
            );

    void update2_i(
            //class MainWindow *lala
            );
    void update2_g(
            //class MainWindow *lala
            );

    //funções de acesso às propriedades
    Agents* get_agente(int i){return vec_ptr_Agentes[i];}// retorna um ponteiro para o agente i
    int get_size_agentes() {return this->vec_ptr_Agentes.size();}
    int get_id_agent(int i){return this->vec_ptr_Agentes[i]->get_id();}
    double get_X(){return this->X;}
    double get_Y(){return this->Y;}
    void verifica_contorno(Agents *ag);



    //funções para calculo do mean crowding
    //    double calc_mc();
    //    double media_pop();
    double raio_medio;
    //    double variancia();


    int n_clusters(){return this->m_clusters.size();}
    //  void mc1(double theta);//função que cria os clusters móveis
    void printOutput();


    //vector<int> output_tam_cluster();
    vector<double> output_var_cluster();
    vector<double> output_tam_cluster();
    vector<string> out_clust();
    vector<double> out_num_clust();
private:
    double X;//x e y
    double Y;

    //funcoes para calculo do dbscan
    double Eps;
    int MinPts;
    //vector<Agents *> regionQuery(Agents *ag1, double Eps);
    //void expandCluster(Agents *P, vector<Agents *> NeighborPts, int Cluster_Id, double Eps, int MinPts);
    //vector <map <int,Agents*> > clusters;
    void DBSCAN(vector<Agents *> &SetOfPoints, double Eps, int MinPts);
    bool ExpandCluster(vector<Agents *> &SetOfPoints, Agents *Point, int Cluster_Id, double Eps, int MinPts);

    map <int, Agents *> m_regionQuery(Agents *ag1, double Eps);//region query que retorna mapa

    void inserir(Agents *P, int Cluster_Id);//insercao e remocao de individuos nos clusters
    void remover(Agents *P, int Cluster_Id);

    map<int,map <int,Agents*> > m_clusters;// mapa de clusters
    vector<                                     //turno
             vector <                            //conjunto de clusters
                      vector <int>                //membros dos clusters
                                     > > time_series_of_clusters; // perfil dos clusters em cada momento de tempo
    //vector<vector < vector <int> > >vec_output;

    struct m_c{//clusters
        bool extended = false;
        vector<int>clust;
    };

    void output(vector<m_c>::iterator g, int i);
    //quadrats
    vector <vector <int> > quadrats;
    void povoa_quadrats();
    int lado_quad;
    int n_quad_total;
    int n_quad_lado;

    vector <Agents*> vec_ptr_Agentes;// vetor de ponteiros para agentes. é a população local
    vector <Agents*> vec_ptr_vizinhos;

    //funções de encontro
    double distTorus(Agents* a1, Agents* a2, int tam);// distancia toroidal dos agentes
    double distEuclidean(Agents *a1, Agents *a2);
    void busca_vizinho(Agents *ag1);

    //    void define_tipo_encontro(Agents *ator, Agents *outro
    //                              //,  MainWindow *lala
    //                              );
    //    void define_tipo_encontro_2(Agents *ator, Agents *outro
    //                                //, MainWindow *lala
    //                                );// com nova memória

    void define_tipo_encontro_2_i(Agents *ator, Agents *outro
                                  //, MainWindow *lala
                                  );
    void define_tipo_encontro_2_g(Agents *ator, Agents *outro
                                  //, MainWindow *lala
                                  );

    void afiliativo(Agents* ator, Agents* outro
                    //, MainWindow *lala
                    );
    void agonistico(Agents *ator, Agents *outro
                    //, MainWindow *lala
                    );
    void neutro(Agents* ator, Agents* outro);

    //funções de ação
    void age_soh(Agents* ator);
    void afasta(Agents* ator, Agents* outro
                //, MainWindow *lala
                );
    void aproxima(Agents* ator, Agents* outro
                  //,  MainWindow *lala
                  );

};

#endif // WORLD_H
