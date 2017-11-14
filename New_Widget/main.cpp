/*!
 *\mainpage Szperacz dyskowy
 * \author Damian Świerk
 * \date 8.11.2017
 * \section Założenia
 *
 * Założenia projektowe
 Cel projektu:
    * -# przeglądanie zawartości systemu plików,
    * -# wizualizacja hierarchii plików w postaci drzewa,
    * -# wyszukiwanie i "katalogowanie" plików konkretnego rodzaju (np. robienie spisu filmów, książek czy muzyki),
    * -# obliczanie zajętego przez katalog i pliki miejsca,
    * -# podgląd wybranych rodzajów plików (np. tekstowych)
    * -# program ma mieć menu z zaimplementowanymi opcjami np. do odczytywania/zapisywania plików,
    * okienko "o programie" oraz podstawową pomoc (np. opisy przeznaczenia widgetów w postaci "dymków"),
    * -# program ma zapisywać swój "stan" (np. rozmiar i pozycja okna programu, aktualnie analizowany katalog)
    * i po kolejnym włączeniu wracać do niego (np. minimum zapisywanie pozycji i rozmiaru okna programu).



 Wnioski:
    * -# Zadanie pozwoliło na poznanie działania i metod obsługi widgetów, modeli i obiektów odpowiadających za obsługę danych.
    * -# Zdobyto wiedzę na temat sposobu dostępu do danych oraz możliwości ich odczytu.
    * -# Nie zaimplementowano możliwości edycji plików tekstowych oraz rekurencyjnego wyszukiwania plików

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
