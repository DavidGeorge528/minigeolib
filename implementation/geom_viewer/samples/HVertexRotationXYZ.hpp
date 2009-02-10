#ifndef HVERTEX_ROTATION_XYZ_HPP
#define HVERTEX_ROTATION_XYZ_HPP

#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/homogenous/transformation_3d.hpp"
#include "geometry/homogenous/direction_3d.hpp"
#include "geometry/angle.hpp"
#include "ogl_render/opengl_object.hpp"
#include "ogl_render/points.hpp"
#include "ogl_render/lines.hpp"
#include "ogl_render/impl/hcommands_3d.hpp"
#include "ogl_render/color.hpp"

#include <boost/type_traits/is_float.hpp>
#include <boost/static_assert.hpp>


namespace Samples
{
/// \brief It provides the sample data for 3D homogeneous coordinate vertex rotation around X,Y and Z axis.
template< typename U>
class HVertexRotationXYZ
{
public:
	BOOST_STATIC_ASSERT( boost::is_float<U>::value);

	HVertexRotationXYZ()
	{
		using namespace ogl_render;
		namespace g = geometry;

		typedef g::hcoord_system< 3, U> coord_system;
		typedef g::vertex< coord_system> vertex;
		typedef g::transformation< coord_system> transformation;
		typedef g::direction< coord_system> direction;

		opengl_object< coord_system> pts;
		unsigned n_pts = 32;
		U a = 2 * geometry::impl::angle_base<U>::PI() / static_cast< U>( n_pts);
		transformation rot_x = transformation::rotation<1>( a);
		transformation rot_y = transformation::rotation<2>( a);
		transformation rot_z = transformation::rotation<3>( a);

		// X rotation
		pts << begin_points;
		vertex v_x( 1, 1, 0);
		pts << color( 1, 0, 0) << v_x << color( 1, 1, 1);
		for( int i = 0; i < n_pts; ++i)
		{
			v_x.transform( rot_x);
			pts << v_x;	
		}
		pts << end_points;

		// Y rotation
		pts << begin_points;
		vertex v_y( 0, 1, 1);
		pts << color( 0, 1, 0) << v_y << color( 1, 1, 1);
		for( int i = 0; i < n_pts; ++i)
		{
			v_y.transform( rot_y);
			pts << v_y;	
		}
		pts << end_points;

		// Z rotation
		pts << begin_points;
		vertex v_z( 1, 0, 1);
		pts << color( 0, 0, 1) << v_z << color( 1, 1, 1);
		for( int i = 0; i < n_pts; ++i)
		{
			v_z.transform( rot_z);
			pts << v_z;	
		}
		pts << end_points;

		// Arbitrary axis through origin rotation
		// Draw rotation axis
		pts << begin_lines << color( 0.5, 0.5, 0.5);
		vertex dir_vertex( 200, 300, 400);
		pts << vertex( 0, 0, 0) << dir_vertex;
		pts << end_lines;
		direction rot_dir( dir_vertex.x(), dir_vertex.y(), dir_vertex.z());
		vertex v_rot( 2, 0, 0);
		transformation rot_dir_tr = transformation::rotation( rot_dir, a);
		pts << begin_points;
		pts << color( 0, 1, 1) << v_rot << color( 1, 1, 1);
		for( int i = 0; i < n_pts; ++i)
		{
			v_rot.transform( rot_dir_tr);
			pts << v_rot;
		}
		pts << end_points;

		id_ = pts;
	}

	GLuint objectID() const { return id_; }
private:
	GLuint id_;
};


} // Samples

#endif // HVERTEX_ROTATION_X_HPP
