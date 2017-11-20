#ifndef WEBNAVIGATOR_H
#define WEBNAVIGATOR_H

#include <QObject>
#include <QVector>

class WebNavigator : public QObject
{
    Q_OBJECT
public:
    explicit WebNavigator(QObject *_parent = 0);
    QString getCurrUrl();

signals:

public slots:
    void urlChanged(QString _url);

private:
    QVector<QString> m_urlHistory;
    int m_histIter;

};

#endif // WEBNAVIGATOR_H
