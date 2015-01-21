#include "space.h"

space::space()// : MyWorld( World())/// :: MyWorld( World()) é uma lista de inicializaç?o, necessária para inicializar a variável referencia
{
    // this->MyWorld =  World();
}

space::space(int XY, int cell_size, World &world)//: MyWorld( World())/// :: MyWorld( World()) é uma lista de inicializaç?o, necessária para inicializar a variável referencia
{
    //this->MyWorld=*world;
    this->fill_grid(
                XY,
                cell_size,
                world);
    int w=0;
}

void space::fill_grid(int XY, int cell_size,  World &world)
{
    this->grid.clear();
    for (int x = 0; x< XY; x++)// cria o grid
    {
        for (int y = 0; y<XY; y++)
        {
//            Agents* ag;//// problema, no preenchimento inicial do espaço, ag n?o é inicializado. resolver bagaço doido
//            // pair<int,Agents*> quem = make_pair(0,ag);
//            add(
//                        ag
//                        ,x
//                        ,y);
            pair<int,int>coord = make_pair(x,y);
            map<int, Agents*> list;
            pair< pair<int,int>, map<int, Agents*> > cell = make_pair(coord,list);
           // this->map_of_clusters.insert(make_pair(ICluster_Id, map<int,Agents*> ()));
            map <pair<int,int>,map<int, Agents*>> grid;
            this->grid.insert(cell);
        }
    }
    for (int i=0; i< world.get_size_agentes(); i++)// povoa o grid
    {
        add(world.get_agent(i), world.get_agent(i)->get_x(),world.get_agent(i)->get_y());
    }
    int w=0;
}

void space::add(Agents *ag, int X, int Y)
{

    pair <int, int> xy = make_pair(X,Y);
    pair <int, Agents*> a=make_pair(ag->get_id(),ag);
    //    pair <int, int> xy = make_pair(vec_ptr_Agentes[i].get_x(),vec_ptr_Agentes[i].get_y());
    //    pair <int, Agents*> a=make_pair(vec_ptr_Agentes[i].get_id(),*vec_ptr_Agentes[i]);
    this->grid[xy].insert(a);
    // ag->set_grid_cell(X,Y);

}

void space::remove_from_cell(Agents *ag) //removes agent from the cell it is currently in
{
    pair <int, int> xy = make_pair(ag->get_x(),ag->get_y());
    int id = ag->get_id();
    // pair <int, Agents*> a = make_pair(id,ag);
    this->grid[xy].erase(id);//erase takes only the key as parameter
}

vector <Agents *> space::Range_query(Agents* ag1, double Range,  World &world)

{
    int a= (int)ag1->get_x();
    int b=(int)ag1->get_y();
    pair<int,int> center_cell= make_pair(a,b);
    vector < Agents*> neighbors;
    for (int x = (center_cell.first - Range); x <= (center_cell.first + Range); x++)
    {
        for (int y = (center_cell.second - Range); y <= (center_cell.second + Range); y++)
        {
            pair<int,int> search_cell = make_pair(x,y);
            auto members = grid[search_cell];
            for (auto it : members)// for each agent in cell
            {
                Agents* ag2= it.second;
                if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
                double d=world.distTorus(ag1,ag2, world.get_X());
                if (d<=Range) // se estiver dentro da distancia Epsilon
                {neighbors.push_back(ag2);}
            }
        }
    }
    return neighbors;
}

map<int, Agents *>  space::Map_Range_query(Agents* ag1, double Range,  World *world)

{
    int a= (int)ag1->get_x();
    int b=(int)ag1->get_y();
    pair<int,int> center_cell= make_pair(a,b);
     map <int, Agents*> neighbors;
    for (int x = (center_cell.first - Range); x <= (center_cell.first + Range); x++)
    {
        for (int y = (center_cell.second - Range); y <= (center_cell.second + Range); y++)
        {
            pair<int,int> search_cell = make_pair(x,y);
            auto members = grid[search_cell];
            for (auto it : members)// for each agent in cell
            {
                Agents* ag2= it.second;
                if (ag1->get_id()==ag2->get_id()) continue;// se for mesmo individuo passa para o proximo
                double d=world->distTorus(ag1,ag2, world->get_X());
                if (d<=Range) // se estiver dentro da distancia Epsilon
                {neighbors.insert( pair<int, Agents*> (ag2->get_id(),ag2 ));}
            }
        }
    }
    return neighbors;

}
