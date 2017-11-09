#include "diranalyzer.h"
#include <QDebug>

/*!
 * \brief DirAnalyzer::DirAnalyzer
 * Konstruktor klasy.
 *
 * \param parent - wskaźnik na widget nadrzędny
 */
DirAnalyzer::DirAnalyzer(QObject *parent) :
    QObject(parent),
    m_dir(new QDir),
    m_fileInfo(new QFileInfo),
    m_file(new QFile),
    m_txtContent(new QString),
    m_suffFilter(new QString),
    m_dirContent(new QStringList)
{
}

/*!
 * \brief DirAnalyzer::passNewDir
 * Metoda pobierająca index modelu przedstawiającego wybraną przez użytkownika lokalizację, a następnie
 * przetwarza informacje o danych zawierających się pod tą lokalizacją. Algorytm sprawdza czy podana ścieżka
 * przechowuje plik, jeśli tak to sprawdza czy jest on również plikiem tekstowym. Jeżeli ścieżka przechowuje plik
 * tekstowy to jego zawartość zostaje pobrana i zapisana w atrybucie m_txtContent.
 * Jeżeli ścieżka wskazuje na folder, to zostaje wczytana zawartość folderu wraz z rozmarami plików i uwzględnieniem
 * filtru rozszerzenia.
 *
 * \param index - indeks modelu przechowującego adres lokalizacji
 */
void DirAnalyzer::passNewDir(const QModelIndex &index)
{
    QString path = index.data(QFileSystemModel::FilePathRole).toString();

    m_fileInfo->setFile(path);
    m_dirContent->clear();
    m_dirContent->begin();

    if(m_fileInfo->isDir())
    {
        *m_dir = QDir(path);
        m_dir->setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        m_dir->setSorting(QDir::Name | QDir::Reversed);

        QFileInfoList _list = m_dir->entryInfoList();
        qint64 allFileSize = 0;

        for(int i = 0; i < _list.size(); ++i) {
            QFileInfo fileInfo = _list.at(i);
            if(fileInfo.suffix() == m_suffFilter || m_suffFilter == QString(""))
            {
                allFileSize += fileInfo.size();
                m_dirContent->append("Name:  " + QString("%1").arg(fileInfo.fileName()) +
                                 "    Size: " + QString("%1").arg(fileInfo.size(), 10) + " B");
            }
         }

        m_dirContent->append("\nAll data size: " + QString::number(allFileSize) + " B");
    }
    else
        if(m_fileInfo->isFile())
        {
            *m_dir = m_fileInfo->dir();

            qDebug() << m_fileInfo->suffix() << endl;

            if(m_fileInfo->suffix() == "txt" || m_fileInfo->suffix() == "cpp"
                    || m_fileInfo->suffix() == "h" || m_fileInfo->suffix() == "pro")
            {
                m_file->setFileName(path);

                if (!m_file->open(QIODevice::ReadOnly | QIODevice::Text))
                    return;

                QTextStream _textStream(m_file);
                *m_txtContent = _textStream.readAll();

                m_file->close();

                qDebug() << *m_txtContent << endl;
            }
        }
        else
            return;
}

/*!
 * \brief DirAnalyzer::isDir
 * Metoda sprawdzająca czy przechowywana ścieżka jest adresem folderu.
 */
bool DirAnalyzer::isDir()
{
    return m_fileInfo->isDir();
}

/*!
 * \brief DirAnalyzer::isTextFile
 * Metoda sprawdzająca czy przechowywana ścieżka jest adresem pliku tekstowego.
 */
bool DirAnalyzer::isTextFile()
{
    if(m_fileInfo->isFile())
        return (m_fileInfo->suffix() == "txt" || m_fileInfo->suffix() == "cpp"
                || m_fileInfo->suffix() == "h" || m_fileInfo->suffix() == "pro");
}

/*!
 * \brief DirAnalyzer::getTextFileContent
 * Metoda zwracająca zawartość pliku tekstowego.
 */
QString DirAnalyzer::getTextFileContent()
{
    return *m_txtContent;
}

/*!
 * \brief DirAnalyzer::getDirName
 * Metoda zwracająca nazwę katalogu.
 */
QString DirAnalyzer::getDirName()
{
    return m_dir->dirName();
}

/*!
 * \brief DirAnalyzer::getFileList
 * Metoda zwracająca listę plików w katalogu wraz z ich rozmiarami.
 */
QStringList DirAnalyzer::getFileList()
{
    return *m_dirContent;
}

/*!
 * \brief DirAnalyzer::getFileName
 * Metoda zwracająca nazwę wybranego pliku.
 */
QString DirAnalyzer::getFileName()
{
    return m_fileInfo->fileName();
}

/*!
 * \brief DirAnalyzer::getPath
 * Metoda zwracająca bezwzględny adres do pliku.
 */
QString DirAnalyzer::getPath()
{
    return m_fileInfo->absoluteFilePath();
}

/*!
 * \brief DirAnalyzer::setFilter
 * Metoda ustawiająca nowy filtr rozszerzenia plików.
 *
 * \param index - indeks modelu przechowującego adres lokalizacji
 */
void DirAnalyzer::setFilter(QString suffix)
{
    *m_suffFilter = suffix;
}

