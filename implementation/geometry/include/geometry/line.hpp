#ifndef GEOMETRY_LINE_HPP
#define GEOMETRY_LINE_HPP

#include "geometry/line_concept.hpp"
#include "geometry/vertex.hpp"
#include "geometry/direction.hpp"

namespace geometry
{

/// \ingroup geometry
/// \brief It implements a line defined by a vertex and a direction.
/// \tparam CS the coordinate system used by the line.
template< typename CS>
class line: public impl::geometric_object< CS, line_tag>
{
public:
	/// \brief The alias of the vertex type used as line position.
	typedef vertex<CS> vertex_type;
	/// \brief The alis of the direction type used for line orientation.
	typedef direction<CS> direction_type;
public:
	/// \brief Initialization
	/// \param vtx the base of the line.
	/// \param dir the orientation of the line.
	line( const vertex_type& vtx, const direction_type& dir)
		: vertex_( vtx)
		, direction_( dir)
	{}

	/// \brief It gets the position of the line.
	const vertex_type& base() const { return vertex_; }

	/// \brief It gets the orientation of the line.
	const direction_type& dir() const { return direction_; }

private:
	vertex_type vertex_;
	direction_type direction_;
};


namespace impl
{

/// \see is_line< typename L, unsigned D, typename CSID>
template< typename CS, unsigned D, typename CSID>
struct is_line< line< CS>, D, CSID>
{
	BOOST_STATIC_CONSTANT( bool, 
		value = 
			(D == CS::DIMENSIONS || D == 0)
		  &&
		  (boost::is_same< CSID, void>::value || boost::is_same< typename CS::system_type, CSID>::value));
};

} // namespace impl

} // geometry

#endif // GEOMETRY_LINE_HPP
