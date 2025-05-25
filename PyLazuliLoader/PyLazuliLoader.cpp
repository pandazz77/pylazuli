#include "PyLazuliLoader.h"

namespace py = pybind11;

PyLazuliLoader::PyLazuliLoader(QObject *parent){
    py::scoped_interpreter guard{};
    py::module_ sys = py::module_::import("sys");
    
    py::print("python path:",sys.attr("path"));
    py::print("python version: ", sys.attr("version_info"));
    py::print("python executable", sys.attr("executable"));
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
