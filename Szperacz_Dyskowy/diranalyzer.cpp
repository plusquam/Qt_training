#include "diranalyzer.h"
#include <QDebug>

DirAnalyzer::DirAnalyzer(QObject *parent) :
    QObject(parent)
{
}

void DirAnalyzer::showParams(const QModelIndex &index)
{
    qDebug() << index.data(QFileSystemModel::FilePathRole).toString();

}
