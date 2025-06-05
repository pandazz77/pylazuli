#include <pybind11/embed.h>
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include "BaseNaviWidget.h"
#include "NaviPluginInterface.h"

namespace py = pybind11;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // py::scoped_interpreter();

    // Load the plugin
    QString pluginPath = argv[1];
    qDebug() << "loading" << pluginPath;
    QPluginLoader loader(pluginPath);
    QObject* plugin = loader.instance();

    if (!loader.isLoaded()) {
        qWarning() << "Failed to load plugin:" << loader.errorString();
        return -1;
    }

    // Assuming the plugin implements MyPluginInterface
    auto myPlugin = qobject_cast<NaviPluginInterface*>(plugin);
    if (!myPlugin) {
        qWarning() << "Invalid plugin instance";
        return -1;
    }

    py::module_ os = py::module_::import("os");
    py::print("python pid2:",os.attr("getpid")());

    auto mod = py::module_::import("test");

    // Use the plugin
    void *ptr = myPlugin->getWidget();
    qDebug() << "PLUGIN LOADER:" << ptr;
    BaseNaviWidget *pyWidget = static_cast<BaseNaviWidget*>(ptr);
    py::print("python pid3:",os.attr("getpid")());
    pyWidget->show();

    return app.exec();
}