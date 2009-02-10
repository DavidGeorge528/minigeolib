#ifndef OGL_RENDER_LINES_HPP
#define OGL_RENDER_LINES_HPP

#include "ogl_render/opengl_object.hpp"

namespace ogl_render
{

template< typename CS>
opengl_object<CS>& begin_lines( opengl_object<CS>& ogl)
{
	glBegin( GL_LINES);
	return ogl;
}

template< typename CS>
opengl_object<CS>& end_lines( opengl_object<CS>& ogl)
{
	glEnd();
	return ogl;
}

} // ogl_render

#endif // OGL_RENDER_LINES_HPP
