#pragma once

#include <QWidget>
#include <QtPlugin>

#include "BaseNaviWidget.h"

#ifdef Q_EXPORT_LIB
#define Q_EXPORT Q_DECL_EXPORT
#else
#define Q_EXPORT Q_DECL_IMPORT
#endif

class Q_EXPORT NaviPluginInterface : public QObject{
    Q_OBJECT
public:
    explicit NaviPluginInterface(QObject *parent = nullptr);
    ~NaviPluginInterface();

    virtual void onActivate() {};
    virtual void onDeactivate() {};

    virtual BaseNaviWidget *getWidget() { return nullptr; }
};

// Объявляем интерфейс для плагинов
Q_DECLARE_INTERFACE(NaviPluginInterface, "com.example.NaviPluginInterface/1.0")
