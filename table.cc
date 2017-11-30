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
	distanceVector = rhs.distanecVector;
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
  return os;
}
#endif

#if defined(DISTANCEVECTOR)
ostream & Table::Print(ostream &os) const
{
  os << "DistanceVector Table()";
  //map<int, TopoLink>


  return os;
}
#endif
