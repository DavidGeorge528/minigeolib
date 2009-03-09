#include "geometry/homogenous/distances_2d.hpp"
#include "geometry/homogenous/distances_3d.hpp" // Keep this include, to check on SFINAE
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>
#include <boost/bind.hpp>
#include <algorithm>

namespace 
{

using namespace geometry;

typedef boost::mpl::list< 
	vertex< hcoord_system< 2, float, algebra::unit_traits< float> > >,
	vertex< hcoord_system< 2, double, algebra::unit_traits< double> > >
> tested_vertices;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_distance, V, tested_vertices)
{
	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::coord_system::length_type length_type;

	vertex v1( 10, 20, 10), v2( -1, -2);
	length_type expected_distance = std::sqrt( unit_type(4+16));
	ALGTEST_CHECK_EQUAL_UNIT( expected_distance, distance( v1, v2));
	ALGTEST_CHECK_EQUAL_UNIT( unit_type(0), distance( v1, v1));
}

// ---------------------------------------------------------------------------------------------------------------------
	
BOOST_AUTO_TEST_CASE_TEMPLATE( test_distance_as_predicate, V, tested_vertices)
{
	using namespace boost;

	typedef V vertex;
	typedef typename vertex::unit_type unit_type;
	typedef typename vertex::coord_system::length_type length_type;

	vertex v1( 10, 20, 10);
	std::list< vertex> lv;
	lv.push_back( vertex(0,0,0));
	lv.push_back( vertex(2,2,2));
	std::vector< unit_type> distances( lv.size());
	std::transform( lv.begin(), lv.end(), distances.begin(), bind( distance<vertex>, _1, v1));
}

} // namespace
