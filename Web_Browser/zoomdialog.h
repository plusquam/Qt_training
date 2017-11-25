#ifndef ZOOMDIALOG_H
#define ZOOMDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>

namespace Ui {
class ZoomDialog;
}

class ZoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZoomDialog(int _zoomVal, QWidget *_parent = 0);
    ~ZoomDialog();
    int value();

public slots:
    void zoomChanged(int _factor);

private:
    Ui::ZoomDialog *ui;
    int zoomVal;
    bool isAccepted;
};

#endif // ZOOMDIALOG_H
