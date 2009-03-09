#ifndef GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
#define GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP

#include "algebra/matrix.hpp"
#include "geometry/transformation.hpp"
#include "geometry/direction_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include <cmath>

namespace geometry
{

template< typename CS >
class transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type >
	: public impl::transformation_base< CS >
{
	typedef algebra::matrix< 4, 4, unit_type, unit_traits_type> matrix_type;
private:
	transformation( const matrix_type& tr)
		: tr_( tr) {}

	typedef transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type > my_type_;
public:
	transformation(		
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: tr_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	static my_type_ translation( const unit_type& dx, const unit_type& dy, const unit_type& dz)
	{
		return transformation( 1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1);
	}

	// TEST
	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix
	template< unsigned D>
	static typename boost::enable_if_c< D == 1, my_type_>::type rotation( const unit_type& angle)
	{
		unit_type 
			cos = std::cos( angle),
			sin = std::sin( angle);
		return my_type_( 
			1,   0,	   0, 0,
			0, cos, -sin, 0,
			0, sin,  cos, 0,
			0,   0,    0, 1
			);
	}

	// TEST
	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix
	template< unsigned D>
	static typename boost::enable_if_c< D == 2, my_type_>::type rotation( const unit_type& angle)
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
	static typename boost::enable_if_c< D == 3, my_type_>::type rotation( const unit_type& angle)
	{
		unit_type
			cos = std::cos( angle),
			sin = std::sin( angle);
		return my_type_( 
			cos, -sin, 0, 0,
			sin,  cos, 0, 0,
			  0,    0, 1, 0,
			  0,    0, 0, 1
			);
	}

	/// \sa http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_about_an_arbitrary_vector
	template< typename Dir>
	static typename boost::enable_if< impl::is_direction< Dir, CS::DIMENSIONS>, my_type_>::type
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
		
		return my_type_(
			lx2+(1-lx2)*cos,    lxly*(1-cos)-lzsin,  lxly*(1-cos)+lysin, 0,
			lxly*(1-cos)+lzsin, ly2+(1-ly2)*cos,     lylz*(1-cos)-lxsin, 0,
			lxlz*(1-cos)-lysin, lylz*(1-cos)+lxsin,  lz2+(1-lz2)*cos,    0,
			0,                  0,                   0,                  1
			);
	}

	template< typename L>
	static typename boost::enable_if< impl::is_line<L, CS::DIMENSIONS>, my_type_>::type
		rotation( const L& line, const unit_type& angle)
	{
		BOOST_CONCEPT_ASSERT( (Line<L>));
		unit_type 
			tr_x = line.base().x()/line.base().w(),
			tr_y = line.base().y()/line.base().w(),
			tr_z = line.base().z()/line.base().w();

		my_type_ tr_to_org = my_type_::translation( -tr_x, -tr_y, -tr_z);
		my_type_ tr_from_org = my_type_::translation( tr_x, tr_y, tr_z);
		my_type_ rot = my_type_::rotation( line.dir(), angle);
		return 
			tr_from_org.tr_ * rot.tr_ * tr_to_org.tr_;
	}

	/// \brief It defines scaling transformation around origin.
	/// \param xscale the scaling factor on X axis.
	/// \param yscale the scaling factor on Y axis.
	/// \param zscale the scaling factor on Z axis.
	static my_type_ scaling( const unit_type& xscale, const unit_type& yscale, const unit_type& zscale)
	{
		return my_type_(
			xscale, 0, 0, 0,
			0, yscale, 0, 0,
			0, 0, zscale, 0,
			0, 0, 0, 1);
	}

	/// \brief It defines scaling transformation around a given position.
	/// \tparam V the implementation of the vertex concept, giving the position to use as center of scaling.
	/// \param center the position to use as center of scaling.
	/// \param xscale the scaling factor on X axis.
	/// \param yscale the scaling factor on Y axis.
	/// \param zscale the scaling factor on Z axis.
	template< typename V>
	static typename boost::enable_if< impl::is_vertex< V, CS::DIMENSIONS>, my_type_>::type
		scaling( const V& center, const unit_type& xscale, const unit_type& yscale, const unit_type& zscale)
	{
		my_type_ tr_to_org = my_type_::translation( -center.x(), -center.y(), -center.z());
		my_type_ tr_from_org = my_type_::translation( center.x(), center.y(), center.z());
		my_type_ scale = my_type_::scaling( xscale, yscale, zscale);
		return tr_from_org.tr_ * scale.tr_ * tr_to_org.tr_;
	}


	/// \brief It defines uniform scaling transformation around origin.
	/// \param unif_scale the scaling for all directions.
	static my_type_ scaling( const unit_type& unif_scale)
	{
		return my_type_::scaling( unif_scale, unif_scale, unif_scale);
	}

	/// \brief It defines uniform scaling transformation aroung a given center position.
	/// \tparam V the implementation of the vertex concept, giving the position to use as center of scaling.
	/// \param center the position to use as center of scaling.
	/// \param xscale the scaling factor on all directions.
	template< typename V>
	static typename boost::enable_if< impl::is_vertex< V, CS::DIMENSIONS>, my_type_>::type
		scaling( const V& center, const unit_type& unif_scale)
	{
		return my_type_::scaling( center, unif_scale, unif_scale, unif_scale);
	}


	coord_rep transformed( const coord_rep& pos) const
	{
		return tr_ * pos;
	}

	void transform( coord_rep& pos) const
	{
		pos = tr_ * pos;
	}

private:
	matrix_type tr_;
};

} // geometry

#endif // GEOMETRY_HOMOGENOUS_TRANSFORMATION_3_HPP
