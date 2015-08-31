#ifndef SPACE_H
#define SPACE_H
#include <map>
#include <vector>
#include <utility>
#include "agents.h"
#include "world.h"

class World;
class space
{
public:
    space();
    ~space();
    space(int XY, int cell_size, World &world);
    void fill_grid(int XY, int cell_size,  World &world);
    vector<Agents *> Range_query(Agents *ag1, double Range, World &world);
    map<int, Agents *> Map_Range_query(Agents *ag1, double Range, World &world);
    void move__on_grid(Agents *ag);
private:
    //World &MyWorld;
    map <pair<int,int>,map<int, Agents*>> grid;// mapa cuja chave é um pair<int x ,int y>
    void add (Agents* ag, int X, int Y);
    void add(Agents *ag,pair<int,int>cell);
    void remove_from_cell (Agents* ag);
    void remove_from_cell (Agents* ag,pair<int,int>cell);
    pair<int, int> get_search_cell(int x_in, int y_in, World &world);
};

#endif // SPACE_H
