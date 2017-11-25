#ifndef HISTORYBROWSER_H
#define HISTORYBROWSER_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class HistoryBrowser;
}

class HistoryBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryBrowser(QStringList* _history ,QWidget *_parent = 0);
    ~HistoryBrowser();

private:
    Ui::HistoryBrowser *ui;
    QString chosenUrl;
    QStringList *history;
};

#endif // HISTORYBROWSER_H
