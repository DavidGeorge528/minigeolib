#ifndef SAMPLES_VERTEX_TRANSLATION_HPP	
#define SAMPLES_VERTEX_TRANSLATION_HPP

#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/vertex_3d.hpp"
#include "geometry/homogenous/transformation_3d.hpp"
#include "ogl_render/opengl_object.hpp"
#include "ogl_render/points.hpp"
#include "ogl_render/impl/hcommands_3d.hpp"
#include "ogl_render/color.hpp"

#include <boost/type_traits/is_float.hpp>
#include <boost/static_assert.hpp>


namespace Samples
{


/// \brief It provides the sample data for 3D homogeneous coordinate vertex.
template< typename U>
class HVertexTranslation
{
public:
	BOOST_STATIC_ASSERT( boost::is_float<U>::value);

	HVertexTranslation()
	{
		using namespace ogl_render;
		namespace g = geometry;

		typedef g::hcoord_system< 3, U> coord_system;
		typedef g::vertex< coord_system> vertex;
		typedef g::transformation< coord_system> transformation;

		opengl_object< coord_system> pts;
		transformation tr = transformation::translation( 0.1, 0.2, 0.3);
		vertex orig( 0,0,0);
		pts << begin_points << color( 1, 1, 1) << orig;
		pts << orig.transform( tr);
		pts << orig.transform( tr);
		pts << orig.transform( tr);
		pts << end_points;

		id_ = pts;
	}

	GLuint objectID() const { return id_; }
private:
	GLuint id_;
};

} // Samples

#endif // SAMPLES_VERTEX_TRANSLATION_HPP
