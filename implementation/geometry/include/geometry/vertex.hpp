#ifndef GEOMETRY_VERTEX_HPP
#define GEOMETRY_VERTEX_HPP

#include "geometry/impl/vertex_base.hpp"
#include "geometry/impl/enablers.hpp"
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace geometry
{

template< typename CS, typename Enable = void >
class vertex
{
};

namespace impl
{

/// \brief It specializes the vertex type checking for vertex class.
/// \sa is_vertex< typename V, unsigned D, typename CSID>
template< typename CS, unsigned D, typename CSID>
struct is_vertex< vertex< CS>, D, CSID >
{
	BOOST_STATIC_CONSTANT( bool, 
		value = (
			(CS::DIMENSIONS == D || D == 0) 
			&& (
				boost::is_same< typename CS::system_type, CSID>::value 
				|| 
				boost::is_same< CSID, void>::value))
		);
};

} // namespace impl

} // geometry

#endif // GEOMETRY_VERTEX_HPP
