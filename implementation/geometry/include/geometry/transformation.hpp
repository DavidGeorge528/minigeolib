#ifndef GEOMETRY_TRANSFORMATION_HPP
#define GEOMETRY_TRANSFORMATION_HPP

namespace geometry
{

/// \brief It defines a generic transformation.
/// \tparam CS the coordinate system the transformation type is compatible with.
template< typename CS>
class transformation
{
	BOOST_STATIC_ASSERT( CS::DIMENSIONS != 2);
	BOOST_STATIC_ASSERT( CS::DIMENSIONS != 3);
};

} // geometry

#endif // GEOMETRY_TRANSFORMATION_HPP
