#ifndef _messages
#define _messages

#include <iostream>
#include "node.h"
#include "link.h"

struct RoutingMessage {
    RoutingMessage();
    RoutingMessage(const RoutingMessage &rhs);
    RoutingMessage &operator=(const RoutingMessage &rhs);

    ostream & Print(ostream &os) const;

    // Anything else you need

    #if defined(LINKSTATE)
    RoutingMessage(int a, int s, int d, int l);
    int age;
    int source;
    int destination;
    int latency;
    #endif
    #if defined(DISTANCEVECTOR)
    RoutingMessage(int n, map<int, TopoLink> d);
    int node;
    map<int,TopoLink> distanceVector;
    #endif
};

inline ostream & operator<<(ostream &os, const RoutingMessage & m) { return m.Print(os);}

#endif
