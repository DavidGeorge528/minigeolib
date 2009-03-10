#ifndef GEOMETRY_HOMOGENOUS_TRANSFORMATION_HPP
#define GEOMETRY_HOMOGENOUS_TRANSFORMATION_HPP

#include "geometry/transformation.hpp"
#include "geometry/direction_concept.hpp"
#include "geometry/line_concept.hpp"
#include "geometry/vertex_concept.hpp"
#include <cmath>

namespace geometry
{
namespace impl
{

/// \ingroup geometry
/// \brief It provides the common methods for all specializations of the homogenous transformation class.
/// \tparam CS the coordinate system used by the transformation.
/// \tparam Derived the derived class, used to access the data from.
/// \details
///		This template depends on the most derived class for two reasons: 
///		\li Optimized data initialization: the transformation with three dimensions need constructor with 16 parameters, 
///			the one with two dimensions need a constructor with 9 paramaters. Since there is no optimized way of passing 
///			different number of parameters to the base class constructors, the data is put in the most derived classes 
///			and initialized by the most derived constructors. 
///		\li Most of the generic methods can be expressed using generic representation of the transformation and 
///			coordinates, so the base class needs access to the specialized data, so Derived template parameter is used 
///			to perform a static cast for getting to that data. Note that the derived class should declare this class as 
///			friend, in order to allow direct access to the private data.
template< typename CS, typename Derived>
class htransformation_base: public transformation_base< CS>
{
public:
	/// \brief Alias for internal representation of the transformation matrix.
	typedef typename coord_system::transform_matrix transform_matrix;

	/// \brief Transforms a vector with homogenous coordinates.
	/// \return the result of the transformation.
	coord_vector transformed( const coord_vector& pos) const
	{
		return this->tr_matrix() * pos;
	}

	/// \brief It applies the transformation on the specified vector with homogenous coordinates.
	void transform( coord_vector& pos) const
	{
		pos = this->tr_matrix() * pos;
	}

private:
	transform_matrix& tr_matrix() { return static_cast< Derived*>( this)->tr_; }
	const transform_matrix& tr_matrix() const { return static_cast< const Derived*>( this)->tr_; }
};

} // namespace impl


/// \ingroup geometry
/// \brief It specializes the transformation for two dimensions, homogenous coordinates.
/// \tparam CS the coordinate system used by the transformation.
template< typename CS >
class transformation< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type >
	: public impl::htransformation_base< CS, transformation< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type > >
{
	typedef transformation< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type > my_type_;
	typedef impl::htransformation_base< CS, transformation< CS, typename impl::enabled_for< CS, 2, hcoord_system_tag>::type > > base_type_;

	template< typename C, typename D> friend class impl::htransformation_base;
public:
	// TODO: Test
	/// \brief Explicit initialization of all transformation matrix elements.
	transformation(	
		const unit_type& a11, const unit_type& a12, const unit_type& a13,
		const unit_type& a21, const unit_type& a22, const unit_type& a23,
		const unit_type& a31, const unit_type& a32, const unit_type& a33)
		: tr_( a11, a12, a13, a21, a22, a23, a31, a32, a33) 
	{ }

	// TODO: Test
	/// \brief Explicit initialization of all transformation matrix elements.
	transformation( const transform_matrix& tr)
		: tr_( tr)
	{
	}

	/// \brief It creates a translation transformation.
	static my_type_ translation( const unit_type& dx, const unit_type& dy)
	{
		return transformation( 1, 0, dx, 0, 1, dy, 0, 0, 1);
	}

private:
	transform_matrix tr_;
};


template< typename CS >
class transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type >
	: public impl::htransformation_base< CS, transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type > >
{
	typedef transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type > my_type_;
	typedef impl::htransformation_base< CS, transformation< CS, typename impl::enabled_for< CS, 3, hcoord_system_tag>::type > > base_type_;

	template< typename C, typename D> friend class impl::htransformation_base;

public:
	// TODO: Test
	/// \brief Explicit initialization of all transformation matrix elements.
	transformation( const transform_matrix& tr)
		: tr_( tr) {}

	// TODO: Test
	transformation(		
		const unit_type& a11, const unit_type& a12, const unit_type& a13, const unit_type& a14,
		const unit_type& a21, const unit_type& a22, const unit_type& a23, const unit_type& a24,
		const unit_type& a31, const unit_type& a32, const unit_type& a33, const unit_type& a34,
		const unit_type& a41, const unit_type& a42, const unit_type& a43, const unit_type& a44)
		: tr_( a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44) 
	{ }

	/// \brief It creates the translation transformation.
	static my_type_ translation( const unit_type& dx, const unit_type& dy, const unit_type& dz)
	{
		return transformation( 1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1);
	}

	/// \brief It creates the rotation around X axis.
	/// \param angle the rotation angle, in radians.
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

	/// \brief It creates the rotation around Y axis.
	/// \param angle the rotation angle, in radians.
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

	/// \brief It creates the rotation around Z axis.
	/// \param angle the rotation angle, in radians.
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

	/// \brief It creates the rotation transformation about an arbitrary direction.
	/// \tparam Dir the direction type, implementing Direction concept.
	/// \param angle the rotation angle, in radians.
	/// \param direction the direction to rotate about.
	/// \details
	///		This transformation is equivalent with rotation about a line of the given direction, passing through origin.
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

	/// \brief It creates the rotation transformation about an arbitrary line.
	/// \tparam L the line type, implementing the Line concept.
	/// \param angle the rotation angle, in radians.
	/// \param line the line to rotate about.
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
	/// \param unif_scale the scaling factor on all directions.
	template< typename V>
	static typename boost::enable_if< impl::is_vertex< V, CS::DIMENSIONS>, my_type_>::type
		scaling( const V& center, const unit_type& unif_scale)
	{
		return my_type_::scaling( center, unif_scale, unif_scale, unif_scale);
	}

private:
	transform_matrix tr_;
};
} // namespace geometry

#endif // GEOMETRY_HOMOGENOUS_TRANSFORMATION_HPP
