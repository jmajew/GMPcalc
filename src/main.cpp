#include <QApplication>

#include "qcalcwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCalcWidget calc;
    calc.show();
    return app.exec();
}
