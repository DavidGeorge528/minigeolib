#include "geometry/homogenous/hvertex_3.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/htransformation_3.hpp"

namespace 
{

	using namespace geometry;

int f()
{
	geometry::vertex< hcoord_system< 3, double> > v( 1, 2,3);
	geometry::transformation< hcoord_system< 3, double> > tr 
		= geometry::transformation< hcoord_system< 3, double> >::translation( 10, 20, 30);
	v.transform( tr);
	return 0;
}

} // namespace
