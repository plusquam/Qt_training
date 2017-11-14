/*!
  \date 8.11.2017r.
  \author Damian Świerk
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
#include <QHeaderView>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include "diranalyzer.h"

namespace Ui {
class MainWindow;
}
/*!
 * \brief Klasa MainWindow
 * Klasa Main Window - interfejs graficzny szperacza dyskowego.
 * Jest to pomost między operacjami na katalogach i plikach, które
 * wykonywane są w obiekcie m_analyzer, a graficzną wizualizacją danych
 * w głownym oknie programu.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);   ///< Konstruktor
    ~MainWindow();                              ///< Destruktor

private slots:
    void dirOpen();                                     ///< slot odpowiadający za proces wprowadzania nowej lokalizacji
    void displayAboutMsg();                             ///< slot odpowiadający za wyświetlenie okna informacji o programie
    void on_treeView_clicked(const QModelIndex &index); ///< slot odpowiadający za nawigację po oknie drzewa katalogów
    void filterChanged(QString);                        ///< slot odpowiadający za proces zmiany wartości filtra

private:
    Ui::MainWindow* ui;         ///< obiekt głównego okna
    DirAnalyzer* m_analyzer;    ///< obiekt analizatora przestrzeni dyskowej
    QFileSystemModel* m_model;  ///< atrybut odpowiadający za przechowywanie modelu systemu plików
    QFileDialog* m_fileDialog;  ///< atrybut przechowujący obiekt typu QFileDialog
    QModelIndex* m_tempIndex;   ///< atrybut przechowujący tymczasową wartość indeksu modelu tree view
};

#endif // MAINWINDOW_H
