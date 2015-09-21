#ifndef AGENTS_H
#define AGENTS_H
#include <vector>
#include <deque>
#include <map>
#include <utility>
using namespace std;

class Agents
{
public:
    Agents();
    Agents(int id, double coordX, double coordY, double Ang,
           double pAF, double pAG, double pAN,
           int N_agentes, int raio,
           int mem_length, int mem_type, double mem_mod);

    bool ja_agiu;
    bool ator;
    bool outro;
    int get_id(){return this->id;}

    //funções de movimentação
    void anda();
    void anda(double ang);
    pair <int,int>myCell;

    double get_x(){return this->x;}
    double get_y(){return this->y;}
    pair <int,int> get_myCell() {return this->myCell;}
    double get_angulo(){return this->angulo;}
    double get_raio() {return this->raio;}
    double get_passo() {return this->passo;}

    void set_x (double i) {this->x=i;}
    void set_y (double i) {this->y=i;}
    void set_angulo(double i){this->angulo=i;}


    //vizinhança
    vector <Agents*> ptrListaVizinhos;
    void clearptrListaVizinhos(){this->ptrListaVizinhos.clear();}
    void setptrListaVizinhos(vector <Agents*> lis){this->ptrListaVizinhos=lis;}

    //DBSCAN
    bool visitado;
    int MyCluster;

    typedef struct modificadores //representa os modificadores de ação baseados em memória
    {
        double af;
        double ag;
        double an;
    }mod;

    //memoria moderna
   // Agents::mod get_mem_i(int id);
    //Agents::mod get_mem_g(int id);
    Agents::mod get_mem (int id);
    Agents * get_abs_largest_mem();
    Agents * get_largest_afilliative_mem();
    void registra_mem_i(int id, int tipo_acao);
    void registra_mem_g(int id, int tipo_acao);
    int memory_type;
    void set_mem(int id, int tipo_acao);

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
    double mem_modifier;

    int memory_length;

    map <int, deque<int> > map_mem_individual; // mapa de memoria individuo a individuo. cada individuo é uma chave do mapa, com sua lista de encontros na forma de um deque
    typedef  deque< pair<int,int> > memory_deque;
    memory_deque mem_deque_grupal; //memoria coletiva. cada pair <int,int> representa uma ação com um individuo e seu respectivo modificador

    void constroi_memoria(int length, int type, int N_agentes);
    //vector <string> out_memory();



};


#endif // AGENTS_H
