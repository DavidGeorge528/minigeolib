#ifndef OGL_RENDER_POINTS_HPP
#define OGL_RENDER_POINTS_HPP

#include "ogl_render/opengl_object.hpp"
#include "ogl_render/impl/commands.hpp"
#include "geometry/vertex.hpp"

namespace ogl_render
{

template< typename CS>
opengl_object<CS>& begin_points( opengl_object<CS>& ogl)
{
	glBegin( GL_POINTS);
	return ogl;
}

template< typename CS>
opengl_object<CS>& end_points( opengl_object<CS>& ogl)
{
	glEnd();
	return ogl;
}

template< typename CS>
opengl_object<CS>& operator<<( opengl_object<CS>& ogl, const geometry::vertex<CS>& v)
{
	impl::commands<CS>::vertex( v);
	return ogl;
}

} // ogl_render

#endif // OGL_RENDER_POINTS_HPP
