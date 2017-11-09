#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

/*!
 * \brief MainWindow::MainWindow
 * Konstruktor klasy. W Konstruktorze tym jest zawarta obsługa slotów i sygnałów programu, a także
 * wprowadzone są ustawienia programu, wraz z deklaracją koniecznych obiektów.
 *
 * \param parent - wskaźnik na widget nadrzędny
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_analyzer(new DirAnalyzer),
    m_model(new QFileSystemModel),
    m_fileDialog(new QFileDialog)
{
    ui->setupUi(this);

    QSettings settings ("Damian_Swierk", "Szperacz_Dyskowy");
    settings.beginGroup("MainWindow");
    resize(settings.value("size",QSize (800,800)).toSize());
    move(settings.value("pos",QPoint(200,200)).toPoint());
    settings.endGroup();

    ui->treeView->setModel(m_model);
    m_model->setRootPath(QDir::homePath());
    ui->treeView->setRootIndex(m_model->index(m_model->rootPath()));
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_fileDialog->setFileMode(QFileDialog::Directory);
    m_fileDialog->setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);


    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionOpen_directory, SIGNAL(triggered()), this, SLOT(dirOpen()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(displayAboutMsg()));
    connect(ui->filterEdit, SIGNAL(textChanged(QString)), this, SLOT(filterChanged(QString)));

}

/*!
 * \brief MainWindow::~MainWindow
 * Destruktor klasy.
 *
 */
MainWindow::~MainWindow()
{
    QSettings settings ("Damian_Swierk", "Szperacz_Dyskowy");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    delete ui;
}

/*!
 * \brief MainWindow::dirOpen
 * Metoda odpowiadająca za obsługę funkcjonalności wybierania wyświetlanego katalogu.
 */
void MainWindow::dirOpen()
{
    QString _dirPath = m_fileDialog->getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    m_model->setRootPath(_dirPath);
    ui->treeView->setRootIndex(m_model->index(m_model->rootPath()));
}

/*!
 * \brief MainWindow::displayAboutMsg
 * Metoda odpowiadająca za wyświetlenie okna informacyjnego dla użytkownika.
 */
void MainWindow::displayAboutMsg()
{
    QMessageBox::about(this, "Szperacz_Dyskowy", "Ten program służy do sprawnego poruszania się po "
                                                 "zasobach systemu, oferując również możliwość filtrowaniania"
                                                 "zawartości katalogów oraz przeglądu plików tekstowych.");
}

/*!
 * \brief MainWindow::on_treeView_clicked
 * Metoda odpowiadająca za obsługę wyboru katalogu/pliku z poziomu graficznego interfejsu.
 *
 * \param index - indeks modelu zawierającego wybraną przez użytkownika lokalizację.
 */
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    m_analyzer->passNewDir(index);

    ui->statusBar->showMessage(m_analyzer->getPath());

    if(m_analyzer->isDir())
    {
        ui->fileTextEdit->clear();
        ui->fileName->clear();
        ui->dirListTextEdit->clear();
        ui->dirName->setText(m_analyzer->getDirName());
        ui->dirListTextEdit->insertPlainText(m_analyzer->getFileList().join('\n'));
    }
    else
        if(m_analyzer->isTextFile())
        {
            ui->fileTextEdit->clear();
            ui->fileName->setText(m_analyzer->getFileName());
            ui->dirListTextEdit->clear();
            ui->dirName->clear();
            ui->fileTextEdit->insertPlainText(m_analyzer->getTextFileContent());
        }
        else
        {

            ui->fileTextEdit->clear();
            ui->fileName->clear();
            ui->dirListTextEdit->clear();
            ui->dirName->clear();
        }
}

/*!
 * \brief MainWindow::filterChanged
 * Metoda odpowiadająca za zmianę filtru rozszerzeń plików w obiekcie m_analyzer po wprowadzeniu zmiany filtru.
 *
 * \param filter - indeks modelu zawierającego wybraną przez użytkownika lokalizację.
 */
void MainWindow::filterChanged(QString filter)
{
    m_analyzer->setFilter(filter);
}
