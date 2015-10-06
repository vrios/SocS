#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>

#include "agents.h"
#include "space.h"

//#include"mainwindow.h"
using namespace std;

//class MainWindow;// necessário para poder atualizar a janela a cada passo, retirar depois
class space;
class World
{
    friend class space;
public:
    World();
    // World(double TAM, int N_agentes, int raio, double Eps, int MinPts);
    World(double TAM, int N_agentes, int raio, double Eps, int MinPts, int mem_length, int mem_type, double mem_mod, int interacoes, int numRep) ;

    ~World();
    int num_turnos;
    int numRep;
    //    void update(// arquivo world-funcao_update.cpp
    //                // class MainWindow *lala
    //                );
//    void update2_g(
//            //class MainWindow *lala
//            space &MySpace
//            );

//    void update2_i(
//            //class MainWindow *lala
//            space &MySpace
//            );


    //funções de acesso ?s propriedades
    Agents* get_agent(int i){return vec_ptr_Agentes[i];}// retorna um ponteiro para o agente i
    int get_size_agentes() {return this->vec_ptr_Agentes.size();}
    int get_id_agent(int i){return this->vec_ptr_Agentes[i]->get_id();}
    double get_X(){return this->X;}
    double get_Y(){return this->Y;}
    void verifica_contorno(Agents *ag);

    double raio_medio;

    //interaction registers
    vector <vector < int> > spatial_network;  // rede de interaç?o agente x agente. cada vez que o agente estiver no mesmo cluster, soma um na célula da matriz
    vector <vector <int> > cumulative_interactions; //cumulative interaction
    vector <vector <int> > total_interactions;
    vector <vector<vector<int> > > social_network;// rede de interaç?o agente x agente x tempo. todas interaç?ess?o registradas aqui


    //output functions
    int n_clusters(){return this->map_of_clusters.size();}
    vector<double> output_sd_cluster();
    vector<double> output_tam_cluster();
    vector<string> out_clust_content();
    vector<double> out_num_clust();
    string out_spatial_dynamic_edges();
    string out_social_dynamic_edges();
    string out_social_final_edges();
    string out_spatial_final_edges();


    void update(space &MySpace);
    void define_tipo_encontro(Agents *ator, Agents *outro, space &MySpace);

private:
    double X;//x e y
    double Y;


    //funcoes para calculo do dbscan
    double Eps;
    int MinPts;
    void DBSCAN(vector<Agents *> &SetOfPoints, double Eps, int MinPts, space &MySpace);
    bool ExpandCluster(vector<Agents *> &SetOfPoints, Agents *Point, int Cluster_Id, double Eps, int MinPts, space &MySpace);
    map <int, Agents *> get_map_of_reachable_Neighbors(Agents *ag1, double Eps, space &MySpace);//region query que retorna mapa
    void insert_in_cluster(Agents *P, int Cluster_Id);//insercao e remocao de individuos nos clusters
    void remove_from_cluster(Agents *P, int Cluster_Id);

    map<int,map <int,Agents*> > map_of_clusters;// mapa de clusters, cada cluster é um mapa de agents
    vector <Agents*> vec_ptr_Agentes;// vetor de ponteiros para agentes. é a população local
    vector <Agents*> vec_ptr_vizinhos;

    vector<                                     //turno
            vector <                            //conjunto de clusters
                     vector <int>                //membros dos clusters
                                    > > time_series_of_clusters; // perfil dos clusters em cada momento de tempo




    //funções de encontro
    double distTorus(Agents* a1, Agents* a2, int tam);// distancia toroidal dos agentes
    double distEuclidean(Agents *a1, Agents *a2);
    void busca_vizinho(Agents *ag1, space &MySpace);



//    void define_tipo_encontro_2_i(Agents *ator, Agents *outro
//                                  //, MainWindow *lala
//                                  , space &MySpace);
//    void define_tipo_encontro_2_g(Agents *ator, Agents *outro
//                                  //, MainWindow *lala
//                                  , space &MySpace);

//    void afiliativo(Agents* ator, Agents* outro
//                    //, MainWindow *lala
//                    , space &MySpace);
//    void agonistico(Agents *ator, Agents *outro
//                    //, MainWindow *lala
//                    , space &MySpace);
//    void neutro(Agents* ator, Agents* outro
//                , space &MySpace);

    //funções de ação
    void age_soh(Agents* ator, space &MySpace);
    void afasta(Agents* ator, Agents* outro
                //, MainWindow *lala
                , space &MySpace);
    void aproxima(Agents* ator, Agents* outro
                  //,  MainWindow *lala
                  , space &MySpace);


};

#endif // WORLD_H
