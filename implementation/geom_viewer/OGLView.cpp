#include "OGLView.qth"
#include "OGLView.moh"
#include "ogl_render/opengl_object.hpp"
#include "ogl_render/points.hpp"
#include <QtOpenGL/QtOpenGL>

#include "geometry/homogenous/hcoord_system.hpp"
#include "geometry/homogenous/hvertex_3.hpp"
#include "geometry/homogenous/htransformation_3.hpp"
#include "ogl_render/opengl_object.hpp"
#include "ogl_render/points.hpp"
#include "ogl_render/impl/hcommands_3.hpp"

OGLView::OGLView(QWidget *parent)
	: QGLWidget(parent)
	, curDispObjId_(-1)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
	gear1Rot = 0;
}

// ---------------------------------------------------------------------------------------------------------------------

OGLView::~OGLView()
{
	makeCurrent();
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		updateGL();
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		updateGL();
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::initializeGL()
{
	static const GLfloat lightPos[4] = { 5.0f, 5.0f, 10.0f, 1.0f };
	static const GLfloat reflectance1[4] = { 0.8f, 0.1f, 0.0f, 1.0f };
	static const GLfloat reflectance2[4] = { 0.0f, 0.8f, 0.2f, 1.0f };
	static const GLfloat reflectance3[4] = { 0.2f, 0.2f, 1.0f, 1.0f };

//	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);

	originId_ = glGenLists( 1);
	glNewList( originId_, GL_COMPILE);
	glBegin( GL_LINES);
	glColor3f( 0, 1, 0);
	glVertex3d( 0,0,0);
	glVertex3d( 100,0,0);
	glColor3f( 0, 0.5, 0);
	glVertex3d( 0,0,0);
	glVertex3d( -100,0,0);
	glColor3f( 0, 0, 1);
	glVertex3d( 0,0,0);
	glVertex3d( 0, 100,0);
	glColor3f( 0, 0, 0.5);
	glVertex3d( 0,0,0);
	glVertex3d( 0, -100,0);
	glColor3f( 1, 0, 0);
	glVertex3d( 0,0,0);
	glVertex3d( 0, 0, 100);
	glColor3f( 0.5, 0, 0);
	glVertex3d( 0,0,0);
	glVertex3d( 0, 0, -100);
	glEnd();
	glEndList();

	/*{
		using namespace ogl_render;
		namespace g = geometry;

		typedef g::hcoord_system< 3, float> coord_system;
		typedef g::vertex< coord_system> vertex;
		typedef g::transformation< coord_system> transformation;

		opengl_object< coord_system> pts;
		transformation tr = transformation::translation( 0.1, 0.2, 0.3);
		vertex orig( 0,0,0);
		pts << begin_points << orig;
			orig.transform( tr);
			pts << orig; 
			orig.transform( tr);
			pts << orig;
			orig.transform( tr);
		pts << orig << end_points;

		curDispObjId_ = pts;
	}*/

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

	// DO drawing here
	glCallList( originId_);

	//glBegin( GL_POINTS);
	//glColor3f( 1, 1, 1);
	//glVertex3d( 0.1, 0.2, 0.3);
	//glVertex3d( 0.2, 0.4, 0.8);
	//glEnd();
	if( glIsList( curDispObjId_))
		glCallList( curDispObjId_);

	glPopMatrix();
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, +1.0, -1.0, 1.0, 5.0, 60.0);
	glTranslated(0.0, 0.0, -40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
		this->updateGL();
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
		this->updateGL();
	}
	lastPos = event->pos();
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::normalizeAngle(int *angle)
{
	while (*angle < 0)
		*angle += 360 * 16;
	while (*angle > 360 * 16)
		*angle -= 360 * 16;
}

// ---------------------------------------------------------------------------------------------------------------------

void OGLView::setDisplayedConstruct( GLuint id)
{
	glDeleteLists( curDispObjId_, 1);
	curDispObjId_ = id;
	this->updateGL();
}