#include "distancevector.h"
#include "context.h"

DistanceVector::DistanceVector(unsigned n, SimulationContext* c, double b, double l) :
    Node(n, c, b, l)
{}

DistanceVector::DistanceVector(const DistanceVector & rhs) :
    Node(rhs)
{
    *this = rhs;
}

DistanceVector & DistanceVector::operator=(const DistanceVector & rhs) {
    Node::operator=(rhs);
    return *this;
}

DistanceVector::~DistanceVector() {}


/** Write the following functions.  They currently have dummy implementations **/
void DistanceVector::LinkHasBeenUpdated(Link* l) {
    cerr << *this << ": Link Update: " << *l << endl;
    int destination = l->GetDest();
    int latency = l->GetLatency();
    routing_table.neighborLinks[destination].cost = latency;
    routing_table.distanceVector[destination].cost = -1;
    routing_table.topo[destination][destination].cost = 0;
    if(updateDV()){
      SendToNeighbors(new RoutingMessage(number, routing_table.distanceVector));
    }
}

void DistanceVector::ProcessIncomingRoutingMessage(RoutingMessage *m) {
    cerr << *this << " got a routing message: " << *m << " (ignored)" << endl;
    routing_table.topo[m->node] = m-> distanceVector;
    map<int,TopoLink>::const_iterator i;
    for(i = m->distanceVector.begin(); i != m->distanceVector.end(); i++){ 
      if(routing_table.distanceVector[i->first].cost == -1){
        //do something
      }
    }
    if(updateDV()){
      SendToNeighbors(new RoutingMessage(number, routing_table.distanceVector));
    }
}

void DistanceVector::TimeOut() {
    cerr << *this << " got a timeout: (ignored)" << endl;
}

Node* DistanceVector::GetNextHop(Node *d) {
    Node *n = new Node(routing_table.edgeTo[d->GetNumber()],NULL,0,0);
    Node *n1 = context->FindMatchingNode(const_cast<Node*>(n));
    return n1;
}

Table* DistanceVector::GetRoutingTable() {
    Table *table = new Table(routing_table);
    return table;
}

ostream & DistanceVector::Print(ostream &os) const {
    Node::Print(os);
    return os;
}

bool DistanceVector::updateDV(){
  bool updated = false;
  map<int,TopoLink>:: const_iterator i;
  map<int,TopoLink>:: const_iterator n;
  for(i = routing_table.distanceVector.begin(); i != routing_table.distanceVector.end(); i++){
    int node = i->first;
    if((unsigned)node == number){
      routing_table.distanceVector[node].cost = 0;
      continue;
    }
    int min = MAX_INT;
    int path = 0;
    int hop = -1;
    for(n = routing_table.neighborLinks.begin(); n != routing_table.neighborLinks.end(); n++){
      int cn = n->first;
      if(routing_table.neighborLinks[cn].cost != -1 && routing_table.topo[cn][node].cost != -1){
        path = routing_table.neighborLinks[cn].cost + routing_table.topo[cn][node].cost;
        if(path < min){
          min = path;
          hop = cn;
        }
      }
    }
    if(min != MAX_INT && min != routing_table.distanceVector[node].cost){
      routing_table.distanceVector[node].cost = min;
      routing_table.edgeTo[node] = hop;
      updated = true;
    }
  }
  return updated;
}
