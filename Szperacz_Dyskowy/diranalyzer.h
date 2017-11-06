#ifndef DIRANALYZER_H
#define DIRANALYZER_H

#include <QObject>
#include <QFileSystemModel>

class DirAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit DirAnalyzer(QObject *parent = 0);

signals:

public slots:
    void showParams(const QModelIndex &index);
};

#endif // DIRANALYZER_H
