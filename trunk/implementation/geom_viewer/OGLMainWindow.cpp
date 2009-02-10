#include "OGLMainWindow.qth"
#include "OGLMainWindow.moh"
#include "OGLView.qth"
#include "Samples/HVertexTranslation.hpp"
#include "samples/HVertexRotationXYZ.hpp"
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>

OGLMainWindow::OGLMainWindow()
	: QMainWindow( NULL)
{
	pOglView_ = new OGLView( this);
	this->setCentralWidget( pOglView_);

	QMenu* pVertexOpMenu = this->menuBar()->addMenu( "&Vertex operations");
	QAction* pAction = pVertexOpMenu->addAction( "Vertex translation");
	connect( pAction, SIGNAL( triggered()), this, SLOT( vertexTranslation()));

	pAction = pVertexOpMenu->addAction( "Vertex rotation");
	connect( pAction, SIGNAL( triggered()), this, SLOT( vertexRotation()));
}

// --------------------------------------------------------------------------------------------------------------------

void OGLMainWindow::vertexTranslation()
{
	Samples::HVertexTranslation<double> sample;
	pOglView_->setDisplayedConstruct( sample.objectID());
}

// --------------------------------------------------------------------------------------------------------------------

void OGLMainWindow::vertexRotation()
{
	Samples::HVertexRotationXYZ< double> sample;
	pOglView_->setDisplayedConstruct( sample.objectID());
}