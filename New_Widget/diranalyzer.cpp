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
    m_suffFilter(new QString)
{
}

/*!
 * \brief DirAnalyzer::passNewDir
 * Metoda pobierająca index modelu przedstawiającego wybraną przez użytkownika lokalizację, a następnie rekursywnie
 * przetwarza informacje o danych zawierających się w tej lokalizacji. Algorytm sprawdza czy podana ścieżka
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
    m_dirContent.clear();
    m_dirContent.begin();

    if(m_fileInfo->isDir())
    {
        *m_dir = QDir(path);
        m_dir->setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        m_dir->setSorting(QDir::Name | QDir::Reversed);

        QDirIterator iterator(*m_dir, QDirIterator::Subdirectories);
        qDebug() << endl << m_dir->absolutePath() << endl;
        while (iterator.hasNext())
        {
            iterator.next();
            qDebug() << iterator.fileInfo().absoluteFilePath();
            m_dirContent.append(iterator.fileInfo());
        }
    }
    else
        if(m_fileInfo->isFile())
        {
            *m_dir = m_fileInfo->dir();

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
 * Metoda zwracająca listę plików w katalogu wraz z ich rozmiarami jako obiekt
 * typu QStringList.
 */
QStringList DirAnalyzer::getFileList()
{
    qint64 _allFileSize = 0;

    QStringList _list;
    foreach(QFileInfo _file, m_dirContent)
    {
        _allFileSize += _file.size();

        if(_file.suffix() == m_suffFilter || m_suffFilter == QString(""))
        {
            _list.append("Name:  " + QString(_file.fileName()) +
                             "    Size: " + QString::number(_file.size()) + " B");
        }
    }

    _list.append("\nAll data size: " + QString::number(_allFileSize) + " B");

    return _list;
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
 * \brief DirAnalyzer::getDirMap
 * Metoda zwracająca gotową mapę podkatalogów wraz z ich rozmiarami.
 */
QMultiMap< QString, QString > DirAnalyzer::getDirMap()
{
    QMultiMap< QString, QString > _outputMap;
    QMap< QString, qint64 > _sizeMap;

    foreach(QFileInfo _file, m_dirContent)
    {
        QString _dirPath = _file.absoluteDir().absolutePath();

        _dirPath.remove(m_dir->absolutePath());
        QStringList _dirs = _dirPath.split("/");

        QString _prevPath(".");

        foreach(QString _dirIter, _dirs)
        {
            QString _tempPath = "/" + _dirIter;

            if(_dirIter == "")
            {
                qint64 _size = _sizeMap.value(".");
                _size += _file.size();
                _sizeMap.insert(".", _size);
            }
            else
            {
                if(!_outputMap.contains(_prevPath, _tempPath))
                    _outputMap.insert(_prevPath, _tempPath);

                qint64 _size = 0;

                if(_sizeMap.contains(_prevPath + _tempPath))
                {
                    _size = _sizeMap.value(_prevPath + _tempPath);
                    _size += _file.size();
                }
                _sizeMap.insert(_prevPath + _tempPath, _size);

                if(_prevPath == ".")
                    _prevPath = _tempPath;
                else
                    _prevPath += _tempPath;
            }
        }
    }

    QMapIterator<QString, qint64> iter(_sizeMap);

    while (iter.hasNext()) {
        iter.next();
        _outputMap.insert(iter.key(), DIR_SIZE_PREFIX + QString::number(iter.value()));
    }
    qDebug() << _outputMap;

    return _outputMap;
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

