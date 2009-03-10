#ifndef GEOMETRY_IMPL_TRANSFORMATION_BASE_HPP
#define GEOMETRY_IMPL_TRANSFORMATION_BASE_HPP

namespace geometry
{
namespace impl
{

template< typename CS>
class transformation_base
{
public:
	typedef CS coord_system;
	typedef typename coord_system::unit_type unit_type;
	typedef typename coord_system::unit_traits_type unit_traits_type;
	typedef typename coord_system::coord_vector coord_vector;
};

} // impl
} // geometry

#endif // GEOMETRY_IMPL_TRANSFORMATION_BASE_HPP
