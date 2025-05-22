#pragma once

#include <QWidget>
#include <QtPlugin>

#ifdef Q_EXPORT
#define Q_EXPORT1 Q_DECL_EXPORT
#else
#define Q_EXPORT1 Q_DECL_IMPORT
#endif

class Q_EXPORT1 NaviPluginInterface : public QObject{
    Q_OBJECT
public:
    explicit NaviPluginInterface(QObject *parent = nullptr);
    ~NaviPluginInterface();

    virtual void onActivate() {};
    virtual void onDeactivate() {};
};

// Объявляем интерфейс для плагинов
Q_DECLARE_INTERFACE(NaviPluginInterface, "com.example.NaviPluginInterface/1.0")
