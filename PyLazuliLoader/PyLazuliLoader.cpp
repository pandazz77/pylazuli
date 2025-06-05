#include "PyLazuliLoader.h"

namespace py = pybind11;

PyLazuliLoader::PyLazuliLoader(QObject *parent){
    qDebug() << "Initializing python interpreter";
    py::initialize_interpreter();
    py::module_ sys = py::module_::import("sys");
    py::module_ os = py::module_::import("os");
    
    py::print("python path:",sys.attr("path"));
    py::print("python version: ", sys.attr("version_info"));
    py::print("python executable:", sys.attr("executable"));
    py::print("python pid:",os.attr("getpid")());
}

PyLazuliLoader::~PyLazuliLoader(){
    qDebug() << "Finalizing python interpreter";
    py::finalize_interpreter();
}

BaseNaviWidget *PyLazuliLoader::getWidget(){
    auto mod = py::module_::import("test");
    py::object *instance = new py::object(std::move(mod.attr("create_instance")()));

    // auto instance = mod.attr("create_instance")();
    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;
    qDebug() << "PyLazuliLoader getWidget raw ptr:" << ptr;

    BaseNaviWidget *widget = static_cast<BaseNaviWidget*>(ptr);
    qDebug() << "PyLazuliLoader getWidget ptr:" << widget;
    return widget;
}
