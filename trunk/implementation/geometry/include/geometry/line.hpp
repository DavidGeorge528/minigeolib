#ifndef GEOMETRY_LINE_HPP
#define GEOMETRY_LINE_HPP

#include "geometry/line_concept.hpp"
#include "geometry/vertex.hpp"
#include "geometry/direction.hpp"

namespace geometry
{

template< typename CS>
class line: public impl::geometric_object< CS, line_tag>
{
public:
	typedef vertex<CS> vertex_type;
	typedef direction<CS> direction_type;
public:
	line( const vertex_type& vtx, const direction_type& dir)
		: vertex_( vtx)
		, direction_( dir)
	{}

	const vertex_type& base() const { return vertex_; }
	const direction_type& dir() const { return direction_; }

private:
	vertex_type vertex_;
	direction_type direction_;
};

} // geometry

#endif // GEOMETRY_LINE_HPP
