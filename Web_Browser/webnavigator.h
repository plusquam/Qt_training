#ifndef WEBNAVIGATOR_H
#define WEBNAVIGATOR_H

#include <QObject>
#include <QVector>
#include <QWebView>

class WebNavigator : public QObject
{
    Q_OBJECT
public:
    explicit WebNavigator(QWebHistory* _webHist, QObject *_parent = 0);
    QString getCurrUrl();

    QWebHistory* m_history;

signals:

public slots:
    void urlChanged(QString _url);

private:


};

#endif // WEBNAVIGATOR_H
