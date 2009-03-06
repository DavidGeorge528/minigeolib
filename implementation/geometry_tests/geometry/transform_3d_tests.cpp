#include "geometry/homogenous/transformation_3d.hpp"
#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/line.hpp"
#include "geometry/homogenous/direction_3d.hpp"
#include "../tests_common.hpp"
#include "../test_traits.hpp"
#include <boost/mpl/list.hpp>

namespace
{

using namespace geometry;

typedef hcoord_system< 3, float, algebra::unit_traits< float> > float_hcoord_system;
typedef hcoord_system< 3, double, algebra::unit_traits< double> > double_hcoord_system;
typedef vertex< float_hcoord_system> float_vertex;
typedef vertex< double_hcoord_system> double_vertex;
typedef transformation< float_hcoord_system> float_transform;
typedef transformation< double_hcoord_system> double_transform;

typedef boost::mpl::list<
	boost::mpl::pair< float_transform, float_vertex>,
	boost::mpl::pair< double_transform, double_vertex> > tested_types;

// ---------------------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE_TEMPLATE( test_scaling, P, tested_types)
{
	typedef P::first transform_type;
	typedef P::second vertex_type;
	typedef typename transform_type::unit_type unit_type;
	const unit_type xscale = 10, yscale = 20, zscale = 30;

	// Non-uniform, origin related scaling
	transform_type t1( transform_type::scaling( xscale, yscale, zscale));
	vertex_type v1( 20, 30, 40);
	v1.transform( t1);

	ALGTEST_CHECK_EQUAL_UNIT( 200, v1.x());
	ALGTEST_CHECK_EQUAL_UNIT( 600, v1.y());
	ALGTEST_CHECK_EQUAL_UNIT( 1200, v1.z());

	// Uniform, origin related scaling
	transform_type t2( transform_type::scaling( xscale));
	vertex_type v2( 10, 20, 30);
	v2.transform( t2);
	ALGTEST_CHECK_EQUAL_UNIT( 100, v2.x());
	ALGTEST_CHECK_EQUAL_UNIT( 200, v2.y());
	ALGTEST_CHECK_EQUAL_UNIT( 300, v2.z());

	// Non-uniform, arbitrary center scaling
	vertex_type v3( 20, 30, 40);
	vertex_type center3( 10, 20, 30);
	transform_type t3( transform_type::scaling( center3, xscale, yscale, zscale));
	v3.transform( t3);

	ALGTEST_CHECK_EQUAL_UNIT( 110, v3.x());
	ALGTEST_CHECK_EQUAL_UNIT( 220, v3.y());
	ALGTEST_CHECK_EQUAL_UNIT( 330, v3.z());

	// Uniform, arbitrary center scaling
	vertex_type v4( 20, 30, 40);
	vertex_type center4( 10, 20, 30);
	transform_type t4( transform_type::scaling( center4, xscale));
	v4.transform( t4);

	ALGTEST_CHECK_EQUAL_UNIT( 110, v4.x());
	ALGTEST_CHECK_EQUAL_UNIT( 120, v4.y());
	ALGTEST_CHECK_EQUAL_UNIT( 130, v4.z());
}

} // namespace
