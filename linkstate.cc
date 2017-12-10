#include "linkstate.h"
#include "context.h"
#include <set>

LinkState::LinkState(unsigned n, SimulationContext* c, double b, double l) :
    Node(n, c, b, l)
{}

LinkState::LinkState(const LinkState & rhs) :
    Node(rhs)
{
    *this = rhs;
}

LinkState & LinkState::operator=(const LinkState & rhs) {
    Node::operator=(rhs);
    return *this;
}

LinkState::~LinkState() {}


/** Write the following functions.  They currently have dummy implementations **/
void LinkState::LinkHasBeenUpdated(Link* l) {
    cerr << *this << ": Link Update: " << *l << endl;
    int dest = 1->GetDest();
    int source = 1->GetSrc();
    int lat = 1->GetLatency();
    routing_table.topo[source][dest].cost = lat;
    routing_table.topo[source][dest].age++; /////////////////////////////////////////////CHECK///////////////////////////
    int age = routing_table.topo[source][dest].age;
    Dijk();
    routing_table.changed = true;
    SendToNeighbors(new RoutingMessage());
}

void LinkState::Dijk(){
  map<int, map<int,TopoLink>>::const_iterator i;
  for(i = routing_table.topo.begin(); i != routing_table.topo.end(); i++){
    routing_table.topo[i->first][i->first].cost = 0;
  }
  std::cout << "Dijk: " << number <<  routing_table << std::endl;
  map<int,int> distance;
  map<int, int> previous;
  map<int, int>::const_iterator di;
  set<int> visit;
  int length = routing_table.topo.size();
  for (int j = 0; (unsigned)j < routing_table.topo.size(); j++) {
    distance[j] = MAX_INT;
    previous[j] = -1;
  }
  distance[number] = 0;
  previous[number] = number;
  for (int j = 0; j < length - 1; j++) {
    for (di = distance.begin(); di != distance.end(); di++) {
      std::cout << di->first << " : " << di->second << std::endl;
    }
    int k = -1;
    int minNode = MAX_INT;
    for (i = routing_table.topo.begin(); i != routing_table.topo.end(); i++) {
      std::cout << "Node: " << i->first << std::endl;
      if (visited.count(i->first) < 1 && distance[i->first] <= minNode) {
        minNode = distance[i->first];
        k = i->first;
      }
    }
    std::cout << "Node: " << k << std::endl;
    visited.insert(k);
    for (i = routing_table.topo.begin(); i != routing_table.topo.end(); i++) {
      int g = i->first;
      if (visited.count(g) < 1 && routing_table.topo[k][g].cost != -1 && distance[k] != MAX_INT && distance[k] + routing_table.topo[k][g].cost < distance[g]) {
        distance[g] = distance[k] + routing_table.topo[k][g].cost;
        previous[g] = k;
      }
    }
  }
  for (di = previous.begin(); di != previous.end(); di++) {
    std::cout << di->first << " : " << di->second << std::endl;
  }
  routing_table.edgeTo = previous;
}

void LinkState::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    cerr << *this << " got a routing message: " << *m << " (ignored)" << endl;
    int src = m->source;
    int destn = m->destination;
    int latency = m->latency;
    int age1 = m->age;
    if(routing_table.topo[src][destn].cost == -1 || routing_table.topo[src][destn].age < age1){
      routing_table.topo[src][destn].cost = latency;
      routing_table.topo[src][destn].age = age1;
      Dijk();
      routing_table.changed = true;
      SendToNeighbors(m);
    }
}

void LinkState::TimeOut() {
    cerr << *this << " got a timeout: (ignored)" << endl;
}

Node* LinkState::GetNextHop(Node *destination) {
  std::cout << "\nNEXT HOP" << destination->GetNumber() << std::endl;
  int hop = destination->GetNumber();
  while((unsigned)routing_table.edgeTo[hop] != number){
    hop = routing_table.edgeTo[hop];
  }
  Node *n = new Node(hop,NULL,0,0);
  std::cout << "STEP: " << hop << std::endl;
  Node *n1 = context->FindMatchingNode(const_cast<Node *>(n));
  return n1;
}

Table* LinkState::GetRoutingTable() {
    return NULL;
}

ostream & LinkState::Print(ostream &os) const {
    Node::Print(os);
    return os;
}
