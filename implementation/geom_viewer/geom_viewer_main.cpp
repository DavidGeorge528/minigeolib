#include <QtGui/QApplication>
#include "OGLMainWindow.qth"
#include "OGLView.qth"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	OGLMainWindow mainWin;
	mainWin.showMaximized();
	return app.exec();
}
