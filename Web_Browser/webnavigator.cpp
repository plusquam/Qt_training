#include "webnavigator.h"
#include <QDebug>

WebNavigator::WebNavigator(QObject *_parent) :
    QObject(_parent),
    m_histIter(0)
{}

QString WebNavigator::getCurrUrl()
{
    return this->m_urlHistory[this->m_histIter];
}

void WebNavigator::urlChanged(QString _url)
{
    if(this->m_histIter == this->m_urlHistory.size() - 1)
    //this->m_urlHistory.erase(this->m_histIter, this->m_urlHistory.end());

    this->m_urlHistory.push_back(_url);
    this->m_histIter++;
    qDebug() << m_urlHistory;
}
