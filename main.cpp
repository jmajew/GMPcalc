#include <QApplication>

#include "calculator_form.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalculatorForm calc;
    calc.show();
    return app.exec();
}
