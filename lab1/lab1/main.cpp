#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(320, 240);
    w.setWindowTitle("My window");
    w.show();

    QPushButton *button2 = new QPushButton("Press me", &w);
    button2->move(40, 50);
    button2->show();

    QLabel label("Label text");
    QPushButton button("Button");

    QLineEdit textedit;
    textedit.setMaximumWidth(100);

    QHBoxLayout layout(&w);
    layout.addWidget(&label);
    layout.addWidget(&button);
    layout.addWidget(&textedit);

    return a.exec();
}
