#include "win.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Win win(0);
    win.show();
    return a.exec();
}
