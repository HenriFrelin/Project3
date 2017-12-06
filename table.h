#ifndef _table
#define _table

#include <iostream>
#include <map>

using namespace std;

struct TopoLink {
    TopoLink(): cost(-1), age(0) {}

    TopoLink(const TopoLink & rhs) {
        *this = rhs;
    }

    TopoLink & operator=(const TopoLink & rhs) {
        this->cost = rhs.cost;
        this->age = rhs.age;

        return *this;
    }

    int cost;
    int age;
};

// Students should write this class
class Table {
    private:
        
    public:
        Table();
        Table(const Table &);
        Table & operator=(const Table &);
        ostream & Print(ostream &os) const;
	map < int, map < int, TopoLink > > topo;

        // Anything else you need

        #if defined(LINKSTATE)
		map<int,int> edgeTo;
		bool changed;
        #endif

        #if defined(DISTANCEVECTOR)
		map<int, TopoLink> neighborLinks;
		map<int, TopoLink> distanceVector;
		map<int, int> edgeTo; 
        #endif
};

inline ostream & operator<<(ostream &os, const Table & t) { return t.Print(os);}


#endif
