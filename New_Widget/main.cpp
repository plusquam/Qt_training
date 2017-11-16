/*!
 *\mainpage Własna kontrolka
 * \author Damian Świerk
 * \date 15.11.2017
 * \section Założenia
 *
 * Założenia projektowe
 Cel projektu:
    * -# przeglądanie zawartości systemu plików,
    * -# wizualizacja hierarchii plików w postaci drzewa,
    * -# wyszukiwanie i "katalogowanie" plików konkretnego rodzaju (np. robienie spisu filmów, książek czy muzyki),
    * -# obliczanie zajętego przez katalog i pliki miejsca,
    * -# podgląd wybranych rodzajów plików (np. tekstowych),
    * -# program powinien prezentować zawartość katalogu w postaci graficznej,
    * -# w przypadku katalogu z podkatalogami, rozmiar podkatalogów powinien być obliczony rekurencyjnie,
    * -# wybranie konkretnego obszaru przy pomocy myszki powinno dostarczać dodatkowych informacji o pliku,
    * -# pliki o podobnych formatach (np. pliki tekstowe, muzyczne czy filmy) powinny być podobnie kolorowane.


 Wnioski:
    * -# Nie udało się poprawnie wyświetlić danych zawartych w katalogach, we własnej kontrolce,
    * w spósób wymieniony w założeniach,
    * -# Wprowadzono samo-skalującą się kontrolkę przedstawiającą w sposób graficzny udział wielkości,
    * zdefiniowanego w konstruktorze klasy DirVisualizer, wektora liczb całkowitych wraz z automatyczną
    * kontrolą odcieni wycinków koła.

*/


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
