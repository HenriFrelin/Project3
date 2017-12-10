#include "table.h"

Table::Table() {
    topo.clear();
}

Table::Table(const Table & rhs) {
    *this = rhs;
}

Table & Table::operator=(const Table & rhs) {
    /* For now,  Change if you add more data members to the class */
    topo = rhs.topo;
    #if defined(DISTANCEVECTOR)
	neighborLinks = rhs.neighborLinks;
	distanceVector = rhs.distanceVector;
	edgeTo = rhs.edgeTo;
    #endif
    return *this;
}

#if defined(GENERIC)
ostream & Table::Print(ostream &os) const
{
  os << "Generic Table()";
  return os;
}
#endif

#if defined(LINKSTATE)
ostream & Table::Print(ostream &os) const
{
	os << "LinkState Table()";
	map<int, map<int, TopoLink> >::const_iterator r = topo.begin();
	while(r != topo.end()){
		map<int, TopoLink>::const_iterator c = (*row).second.begin();
		os << "SOURCE: " << (*r).first << std::endl;
		while(c != (*r).second.end()){
			os << "DESTINATION: " << (*s).first << std::endl;
			c++;
		}
		r++;
	}

	return os;
}
#endif

#if defined(DISTANCEVECTOR)
ostream & Table::Print(ostream &os) const
{
	os << "DistanceVector Table()";
	map<int, TopoLink>::const_iterator i = distanceVector.begin();
	while(i !=  distanceVector.end()){
		os << "NODE: " << (*i).first << "DISTANCE: " << (*i).second.cost << std::endl;
		i++;
	}
	os << "NEIGHBOR LIST: " << std::endl;
	i = neighborLinks.begin();
	while(i != neighborLinks.end()){
		os << "NODE: " << (*i).first << "DISTANCE: " << (*i).second.cost << std::endl;
		i++;
	}

	return os;
}
#endif
