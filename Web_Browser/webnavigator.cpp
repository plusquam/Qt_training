#include "webnavigator.h"
#include <QDebug>

WebNavigator::WebNavigator(QWebHistory *_webHist, QObject *_parent) :
    QObject(_parent),
    m_history(_webHist)
{}

QString WebNavigator::getCurrUrl()
{

}

void WebNavigator::urlChanged(QString _url)
{

}
