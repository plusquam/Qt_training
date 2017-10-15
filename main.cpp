#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QLabel labelka("hello world");

    labelka.setAlignment(Qt::AlignCenter);
    //labelka.show();

    QPushButton b("Close All");
    //b.show();

    QObject::connect(&b, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout layout;

    QWidget window;

    layout.addWidget(&labelka);
    layout.addWidget(&b);

    window.setLayout(&layout);
    window.show();

    return app.exec();
}
