#include "PyLazuliLoader.h"

namespace py = pybind11;

PyLazuliLoader::PyLazuliLoader(QObject *parent){

}

PyLazuliLoader::~PyLazuliLoader(){

}

BaseNaviWidget *PyLazuliLoader::getWidget(){
    py::scoped_interpreter guard{};

    auto mod = py::module_::import("test");
    auto instance = mod.attr("create_instance")();
    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;
    qDebug() << ptr;

    BaseNaviWidget *widget = static_cast<BaseNaviWidget*>(ptr);
    return widget;
}
