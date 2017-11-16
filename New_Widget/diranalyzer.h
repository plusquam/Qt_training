/*!
  \date 15.11.2017r.
  \author Damian Świerk
  */

#ifndef DIRANALYZER_H
#define DIRANALYZER_H

#include <QObject>
#include <QFileSystemModel>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QString>
#include <QDirIterator>
#include <QMultiMap>

#define DIR_SIZE_PREFIX "$S$"

/*!
 * \brief Klasa DirAnalyzer
 * Klasa służy do przetwarzania informacji o danych zamieszczonych w podanej lokalizacji.
 * Pozwala na rekursywne pozyskanie listy plików znajdujących się w katalogu.
 * Posiada funkcjonalność otwierania plików tekstowych.
 */
class DirAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit DirAnalyzer(QObject *parent = 0);  ///< Konstruktor
    void passNewDir(const QModelIndex &index);  ///< metoda przygotowywująca nowe informacje o danych w podanej lokalizacji

    bool isDir();       ///< metoda sprawdzająca czy podana lokalizacja jest folderem
    bool isTextFile();  ///< metoda sprawdzająca czy podana lokalizacja jest plikiem tekstowym

    QString getTextFileContent();   ///< metoda zwracająca zawartość pliku tekstowego
    QString getDirName();           ///< metoda zwracająca nazwę katalogu
    QStringList getFileList();      ///< metoda zwracająca zawartość katalogu
    QString getFileName();          ///< metoda zwracająca nazwe pliku
    QString getPath();              ///< metoda zwracająca podaną ścieżkę
    QMultiMap< QString, QString > getDirMap();    ///< metoda zwracająca mapę podkatalogów

    void setFilter(QString suffix); ///< metoda ustawiająca filtr plików

private:
    QDir* m_dir;                    ///< atrybut przechowujący obiekt katalogu
    QFileInfo* m_fileInfo;          ///< atrybut przechowujący informacje o pliku/katalogu
    QFile* m_file;                  ///< atrybut przechowujący obiekt katalogu
    QString* m_txtContent;          ///< atrybut przechowujący zawartość pliku tekstowego
    QString* m_suffFilter;          ///< atrybut przechowujący filtr nazw plików
    QList<QFileInfo> m_dirContent;  ///< kontener przechowujący listę zawartości katalogu
};

#endif // DIRANALYZER_H
