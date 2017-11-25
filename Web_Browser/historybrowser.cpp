#include "historybrowser.h"
#include "ui_historybrowser.h"

HistoryBrowser::HistoryBrowser(QStringList* _history, QWidget *_parent) :
    QDialog(_parent),
    ui(new Ui::HistoryBrowser)
{
    ui->setupUi(this);
    this->setWindowTitle("Browser history");

    history = _history;


    connect(ui->gotoButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

HistoryBrowser::~HistoryBrowser()
{
    delete ui;
}
