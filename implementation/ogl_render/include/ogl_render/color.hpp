#ifndef OGL_RENDER_COLOR_HPP
#define OGL_RENDER_COLOR_HPP

namespace ogl_render
{

class color
{
public:
	color( double r, double g, double b, double a = 0)
		: red_( r), green_( g), blue_(b), alpha_( a) { }

	template< typename CS>
	friend opengl_object<CS>& operator<<( opengl_object<CS>& ogl, const color& c)
	{
		glColor4d( c.red_, c.green_, c.blue_, c.alpha_);
		return ogl;
	}

private:
	double red_, green_, blue_, alpha_;
};

} // ogl_render

#endif // OGL_RENDER_COLOR_HPP
