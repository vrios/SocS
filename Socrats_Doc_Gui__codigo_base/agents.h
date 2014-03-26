#ifndef AGENTS_H
#define AGENTS_H
#include <vector>
#include <deque>
#include <map>
#include <utility>
using namespace std;

//testing git
class Agents
{
public:
    Agents();
//    Agents(int id, double coordX, double coordY,double Ang,
//           double pAF,double pAG, double pAN,
//           int N_agentes, int raio);
    Agents(int id, double coordX, double coordY, double Ang,
           double pAF, double pAG, double pAN,
           int N_agentes, int raio,
           int mem_length, int mem_type);

    bool ja_agiu;
    bool ator;
    bool outro;
    int get_id(){return this->id;}

    //funções de movimentação
    void anda();
    void anda(double ang);

    double get_x(){return this->x;}
    double get_y(){return this->y;}
    double get_angulo(){return this->angulo;}
    double get_raio() {return this->raio;}
    double get_passo() {return this->passo;}

    void set_x (double i) {this->x=i;}
    void set_y (double i) {this->y=i;}
    void set_angulo(double i){this->angulo=i;}


    //memoria antiga

//    double get_prob_Init(char tipo);
//    double get_af(){return this->prob_Inicial_AF;}
//    double get_ag(){return this->prob_Inicial_AG;}
//    double get_an(){return this->prob_Inicial_AN;}

//    double get_mod_mem(int i, char tipo);
//    double get_mod_ag(int i){return this->vec_memoria[i].mod_AG;}
//    double get_mod_af(int i){return this->vec_memoria[i].mod_AF;}
//    double get_mod_an(int i){return this->vec_memoria[i].mod_AN;}

//    void set_mod_ (int outro, double valor, char tipo);
//    void set_mod_af (int outro, double valor){this->vec_memoria[outro].mod_AF+=valor;}
//    void set_mod_ag (int outro, double valor){this->vec_memoria[outro].mod_AG+=valor;}
//    void set_mod_an (int outro, double valor){this->vec_memoria[outro].mod_AN+=valor;}

    void set_sum_ (int outro, char tipo);
    void set_sum_af(int outro){this->vec_memoria[outro].soma_af++;}
    void set_sum_ag(int outro){this->vec_memoria[outro].soma_ag++;}
    void set_sum_an(int outro){this->vec_memoria[outro].soma_an++;}

    //vizinhança
    vector <Agents*> ptrListaVizinhos;
    void clearptrListaVizinhos(){this->ptrListaVizinhos.clear();}
    void setptrListaVizinhos(vector <Agents*> lis){this->ptrListaVizinhos=lis;}

    //DBSCAN
    bool visitado;    int cluster;

    typedef struct modificadores //representa os modificadores de ação baseados em memória
    {
        double af;
        double ag;
        double an;
    }mod;

    //memoria moderna

    //mod get_mem(int id);
    //void registra_mem(int id, int tipo_acao);
    Agents::mod get_mem_i(int id);
    Agents::mod get_mem_g(int id);
    void registra_mem_i(int id, int tipo_acao);
    void registra_mem_g(int id, int tipo_acao);

private:
    int id;
    double passo;
    double raio;
    double x; //x, y, angulo
    double y;
    double angulo;
    //probabilidades iniciais de ação
    double prob_Inicial_AG;
    double prob_Inicial_AF;
    double prob_Inicial_AN;

//    struct memoria//armazena a memoria dos encontros
//    {
//        int id;//id do outro individuo
//        //acumuladores de memória
//        double mod_AG;
//        double mod_AF;
//        double mod_AN;
//        //quantas vezes ocorreu cada interação
//        int soma_af;
//        int soma_ag;
//        int soma_an;
//    };

//    vector <memoria> vec_memoria;//memoria dos individuos, substituir por map futuramente

    //nova arquitetura de memoria
 //   pair <int,int> mem_cell; // int-> id do outro, char -> tipo de interação
//    vector < pair <int,int> > vec_mem_cell;

  //  vector <deque<int> > vec_deq_mem;// vetor de memoria indiividuo a individuo. cada individuos é um item do vetor, com sua lista de encontros na forma de um deque
    map <int, deque<int> > map_mem; // mapa de memoria indiividuo a individuo. cada individuos é uma chave do mapa, com sua lista de encontros na forma de um deque

    typedef  deque< pair<int,int> > memory_deque;
    memory_deque mem_deque; //memoria coletiva. cada pair <int,int> representa uma ação com um individuo e seu respectivo modificador




    void constroi_memoria(int length, int type, int N_agentes);

 //   void memory(int tipo, double valor, int id);
    int memory_length;
    int memory_type;

};


#endif // AGENTS_H
