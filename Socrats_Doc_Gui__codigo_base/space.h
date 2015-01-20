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
    space(int XY, int cell_size, World *world);
    void fill_grid(int XY, int cell_size,  World *world);
    vector<Agents *> Range_query(Agents *ag1, double Range, World *world);
    map<int, Agents *> Map_Range_query(Agents *ag1, double Range, World *world);
private:
    //World &MyWorld;
    map <pair<int,int>,map<int, Agents*>> grid;// mapa cuja chave é um pair<int x ,int y>
    void add (Agents* ag, int X, int Y);
    void remove_from_cell (Agents* ag);
};

#endif // SPACE_H
