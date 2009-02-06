#ifndef OGL_RENDER_OPENGL_OBJECT_HPP
#define OGL_RENDER_OPENGL_OBJECT_HPP

#include <gl/gl.h>

namespace ogl_render
{

template< typename CS>
class opengl_object
{
public:
	opengl_object()
		: id_( glGenLists(1))
	{
		glNewList( id_, GL_COMPILE);
	}

	~opengl_object()
	{
		glEndList();
	}

	operator GLuint() const { return id_; }

	opengl_object& operator<<( opengl_object& (*manipulator)( opengl_object& ))
	{
		manipulator( *this);
		return *this;
	}
private:
	GLuint id_;
};

} // namespace ogl_render

#endif // OGL_RENDER_OPENGL_OBJECT_HPP
