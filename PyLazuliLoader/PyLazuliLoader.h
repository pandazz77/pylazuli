#pragma once

#include <pybind11/embed.h>

#include <QWidget>
#include <QtPlugin>
#include <BaseNaviWidget.h>
#include <NaviPluginInterface.h>


class PyLazuliLoader : public NaviPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.example.NaviPluginInterface/1.0")
    Q_INTERFACES(NaviPluginInterface)
public:
    explicit PyLazuliLoader(QObject *parent = nullptr);
    ~PyLazuliLoader();
public:

    void onActivate() override {}
    void onDeactivate() override {}

    BaseNaviWidget *getWidget();
};
