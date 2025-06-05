#include <pybind11/embed.h>
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include "BaseNaviWidget.h"
#include "NaviPluginInterface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

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

    // Use the plugin
    BaseNaviWidget *pyWidget = myPlugin->getWidget();
    pyWidget->show();

    return app.exec();
}