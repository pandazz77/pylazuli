#include <pybind11/embed.h>
#include <QWidget>
#include <QApplication>

namespace py = pybind11;

int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    py::scoped_interpreter guard{};

    auto mod = py::module_::import("test");
    auto instance = mod.attr("create_instance")();
    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;
    qDebug() << ptr;

    QWidget *widget = static_cast<QWidget*>(ptr);
    widget->show();
    
    app.exec();
}