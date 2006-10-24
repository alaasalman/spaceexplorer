#include <QApplication>
#include <QMainWindow>

#include "GameMainWindow.h"

int main(int argc, char** argv)
{
    QApplication qapp(argc, argv);
    GameMainWindow* gmw = new GameMainWindow();

    gmw->show();

    return qapp.exec();
}
