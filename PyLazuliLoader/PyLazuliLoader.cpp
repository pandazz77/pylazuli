#include "PyLazuliLoader.h"

#include <QFileInfo>
#include <QDir>

namespace py = pybind11;

#ifdef __linux__
    #include <dlfcn.h>
    #define init_pythonlib dlopen(PYTHON_LIBRARIES,RTLD_LAZY | RTLD_GLOBAL)
#else
    #define init_pythonlib void(0)
#endif

QString getCurrentDllPath();
#ifdef __linux__
    #include <dlfcn.h>
    QString getCurrentDllPath() {
        Dl_info dl_info;
        if (dladdr((void*)getCurrentDllPath, &dl_info) != 0 && dl_info.dli_fname != nullptr) {
            return QString::fromLocal8Bit(dl_info.dli_fname);
        }
        return QString();
    }
#else 
    #include <windows.h>
    QString getCurrentDllPath() {
        HMODULE hModule = NULL;
        DWORD size = GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                        (LPCTSTR)getCurrentDllPath, &hModule);
        if (!size) {
            return QString();
        }

        char path[MAX_PATH];
        size = GetModuleFileNameA(hModule, path, MAX_PATH);
        if (size == 0) {
            return QString();
        }

        return QString::fromLocal8Bit(path);
    }
#endif

QString getPluginsDir(){
    return QFileInfo(getCurrentDllPath()).dir().path();
}

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
    py::module_ os = py::module_::import("os");

    std::string cwd = getPluginsDir().toStdString();
    os.attr("chdir")(cwd);

    auto mod = py::module_::import("test");
    py::object *instance = new py::object(std::move(mod.attr("create_instance")()));

    auto raw_ptr = mod.attr("unwrap")(instance).cast<unsigned long long>();
    void *ptr = (void*)raw_ptr;

    BaseNaviWidget *widget = static_cast<BaseNaviWidget*>(ptr);
    return widget;
}
