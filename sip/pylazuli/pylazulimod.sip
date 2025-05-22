%Module(name=pylazuli, language="C++")
%DefaultEncoding "UTF-8"


%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip
%Import QtWidgets/QtWidgetsmod.sip

class BaseNaviWidget : public QWidget
{
public:
    explicit BaseNaviWidget(QWidget *parent = nullptr);
    explicit BaseNaviWidget(int timerInterval,QWidget *parent = nullptr);
    ~BaseNaviWidget();
public:
    virtual bool isActive();
    virtual void startSend();
    virtual void stopSend();
    virtual QIcon icon() const = 0;
    virtual QString name() const = 0;
    virtual QString description() const = 0;
public slots:
    virtual void setPos(double lat, double lon);
    void setRetranslate(QString retranslateName);    
signals:
    void sendData(QStringList data);
protected slots:
    virtual QStringList getNavigationData() = 0;

protected:  
    // int tickInterval = 1000;
    QString getRetranslateName(QString retranslateName);
    void retranslate();
};

