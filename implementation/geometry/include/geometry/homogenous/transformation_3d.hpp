#ifndef GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
#define GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP

#include "geometry/transformation.hpp"
#include "geometry/direction_concept.hpp"
#include <cmath>

namespace geometry
{

template< typename CS >
class transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type >
	: public impl::transformation_base< CS >
{
public:
	transformation(		
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: tr_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	static transformation translation( const unit_type& dx, const unit_type& dy, const unit_type& dz)
	{
		return transformation( 1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1);
	}

	// TEST
	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix
	template< unsigned D>
	static typename boost::enable_if_c< D == 1, transformation>::type rotation( const unit_type& angle)
	{
		unit_type 
			cos = std::cos( angle),
			sin = std::sin( angle);
		return transformation( 
			1,   0,	   0, 0,
			0, cos, -sin, 0,
			0, sin,  cos, 0,
			0,   0,    0, 1
			);
	}

	// TEST
	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix
	template< unsigned D>
	static typename boost::enable_if_c< D == 2, transformation>::type rotation( const unit_type& angle)
	{
		unit_type 
			cos = std::cos( angle),
			sin = std::sin( angle);
		return transformation( 
			 cos, 0, sin, 0,
			   0, 1,   0, 0, 
			-sin, 0, cos, 0,
			   0, 0,   0, 1
			);
	}

	// TEST
	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix
	template< unsigned D>
	static typename boost::enable_if_c< D == 3, transformation>::type rotation( const unit_type& angle)
	{
		unit_type
			cos = std::cos( angle),
			sin = std::sin( angle);
		return transformation( 
			cos, -sin, 0, 0,
			sin,  cos, 0, 0,
			  0,    0, 1, 0,
			  0,    0, 0, 1
			);
	}

	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_about_an_arbitrary_vector
	template< typename Dir>
	static typename boost::enable_if< boost::is_same< typename Dir::tag, direction_tag>, transformation>::type
		rotation( const Dir& direction, const unit_type& angle)
	{
		BOOST_CONCEPT_ASSERT( (Direction< Dir>));
		unit_type 
			cos = std::cos( angle),
			sin = std::sin( angle);
		unit_type 
			lx = direction.dx(), ly = direction.dy(), lz = direction.dz(), 
			lx2 = lx*lx, ly2 = ly*ly, lz2 = lz*lz,
			lxly = lx*ly, lxlz = lx*lz, lylz = ly*lz,
			lxsin = lx*sin, lysin = ly*sin, lzsin = lz*sin;
		
		return transformation(
			lx2+(1-lx2)*cos,    lxly*(1-cos)-lzsin,  lxly*(1-cos)+lysin, 0,
			lxly*(1-cos)+lzsin, ly2+(1-ly2)*cos,     lylz*(1-cos)-lxsin, 0,
			lxlz*(1-cos)-lysin, lylz*(1-cos)+lxsin,  lz2+(1-lz2)*cos,    0,
			0,                  0,                   0,                  1
			);
	}

	position_type transformed( const position_type& pos) const
	{
		return tr_ * pos;
	}

	void transform( position_type& pos) const
	{
		pos = tr_ * pos;
	}

private:
	typedef algebra::matrix< 4, 4, unit_type, unit_traits_type> matrix_type;
	matrix_type tr_;
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
