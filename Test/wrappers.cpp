#include <pybind11/embed.h>
#include <QWidget>
#include <QApplication>
#include "BaseNaviWidget.h"
#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>

namespace py = pybind11;

int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    py::scoped_interpreter guard{};

    auto mod = py::module_::import("test");
    auto instance = mod.attr("create_instance")();
    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;
    qDebug() << ptr;

    BaseNaviWidget *pyWidget = static_cast<BaseNaviWidget*>(ptr);

    QWidget *nativeWidget = new QWidget;
    nativeWidget->setLayout(new QHBoxLayout);
    nativeWidget->layout()->addWidget(new QLabel("Hello from native widget!"));


    QMainWindow *mainWindow = new QMainWindow();
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(nativeWidget);
    layout->addWidget(pyWidget);
    container->setLayout(layout);
    mainWindow->setCentralWidget(container);

    mainWindow->show();

    app.exec();
}