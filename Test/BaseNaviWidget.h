#pragma once

#include <QWidget>
#include <QtPlugin>
#include <QTimer>
#include <QTranslator>

#ifdef BASENAVIWIDGET_LIBRARY
#define BASENAVIWIDGET_EXPORT Q_DECL_EXPORT
#else
#define BASENAVIWIDGET_EXPORT Q_DECL_IMPORT
#endif

class BASENAVIWIDGET_EXPORT BaseNaviWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseNaviWidget(QWidget *parent = nullptr);
    explicit BaseNaviWidget(int timerInterval,QWidget *parent = nullptr);
    ~BaseNaviWidget();
public:
    virtual bool isActive();
    /// @brief Запуск отправки данных
    virtual void startSend();
    /// @brief Остановка оправки данных
    virtual void stopSend();
    /// @brief Иконка плагина
    /// @return QIcon 
    virtual QIcon icon() const = 0;
    /// @brief Название плагина
    /// @return QString 
    virtual QString name() const = 0;
    /// @brief Описание плагина 
    /// @return QString 
    virtual QString description() const = 0;
public slots:
    virtual void setPos(double lat, double lon);
    void setRetranslate(QString retranslateName);    
signals:
    void sendData(QStringList data);
protected slots:
    virtual QStringList getNavigationData() = 0;
private slots:
    void onTimeout();

protected:  
    int tickInterval = 1000;
    virtual QString getRetranslateName(QString retranslateName);
    virtual void retranslate();
private:
    QTimer *timer = nullptr;
    QTranslator * translator;
};

// Объявляем интерфейс для плагинов
Q_DECLARE_INTERFACE(BaseNaviWidget, "com.example.BaseNaviWidget/1.0")
