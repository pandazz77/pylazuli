#include "PyLazuliLoader.h"

namespace py = pybind11;

#ifdef __linux__
    #include <dlfcn.h>
    #define init_pythonlib dlopen(PYTHON_LIBRARIES,RTLD_LAZY | RTLD_GLOBAL)
#else
    #define init_pythonlib void(0)
#endif

PyLazuliLoader::PyLazuliLoader(QObject *parent){
    init_pythonlib;
    qDebug() << "Initializing python interpreter";
    py::initialize_interpreter();
    py::module_ sys = py::module_::import("sys");
    
    py::print("python path:",sys.attr("path"));
    py::print("python version: ", sys.attr("version_info"));
    py::print("python executable:", sys.attr("executable"));
}

PyLazuliLoader::~PyLazuliLoader(){
    qDebug() << "Finalizing python interpreter";
    py::finalize_interpreter();
}

BaseNaviWidget *PyLazuliLoader::getWidget(){
    auto mod = py::module_::import("test");
    py::object *instance = new py::object(std::move(mod.attr("create_instance")()));

    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;

    BaseNaviWidget *widget = static_cast<BaseNaviWidget*>(ptr);
    return widget;
}
