#include "handgesture.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    handGesture w;
    /*QGraphicsScene scene;
    QGraphicsProxyWidget* gpw = scene.addWidget();
    gpw->setRotation(180);
    QGraphicsView view(&scene);*/
    w.show();
    //view.show();
    return a.exec();
}
