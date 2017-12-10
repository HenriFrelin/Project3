#include "messages.h"

RoutingMessage::RoutingMessage()
{}

RoutingMessage::RoutingMessage(const RoutingMessage &rhs) {
    *this = rhs;
}

RoutingMessage & RoutingMessage::operator=(const RoutingMessage & rhs) {
    /* For now.  Change if you add data members to the struct */
    return *this;
}

#if defined(GENERIC)
ostream &RoutingMessage::Print(ostream &os) const
{
    os << "Generic RoutingMessage()";
    return os;
}
#endif

#if defined(LINKSTATE)

RoutingMessage::RoutingMessage(int a, int s, int d, int l){
	age = a;
	source = s;
	destination = d;
	latency = l;
	
}

ostream &RoutingMessage::Print(ostream &os) const
{
	os << "LinkState RoutingMessage()";
	os << "Age: " << age << std::endl;
	os << "Source: " << source << std::endl;
	os << "Destination: " << destination << std::endl;
	os << "Latency: " << latency << std:: endl;	
	return os;
}
#endif

#if defined(DISTANCEVECTOR)

RoutingMessage::RoutingMessage(int n, map<int, TopoLink> d){
	node = n;
	distanceVector = d;
}
ostream &RoutingMessage::Print(ostream &os) const
{
	os << "DistanceVector RoutingMessage()";
	//os << "NODE: " << node << std::endl;
	//os << "DistanceVector: " << d << std::endl;
	return os;
}
#endif
