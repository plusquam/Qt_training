/*!
 *\mainpage Przeglądarka www
 * \author Damian Świerk
 * \date 25.11.2017
 * \section Założenia
 *
 * Założenia projektowe:
    * -# Wyświetlanie stron www o zadanym adresie,
    * -# Miejsce do wpisywania adresu strony z automatycznym dodawaniem brakujących informacji
    * (np. protokołu "http:\\") oraz wyświetlaniem adresu załadowanej strony np. po kliknięciu odnośnika,
    * -# Reagowanie na nawigację przy pomocy myszki (np. przechodzenie do klikniętych odnośników),
    * -# Podgląd adresu odnośnika na pasku statusu po najechaniu myszką nad odnośnik,
    * -# Nawigacja po odwiedzonych stronach przy pomocy klawiszy poprzednia/następna strona,
    * -# Menu kontekstowe do nawigacji,
    * -# Zapamiętywanie historii odwiedzanych stron, prezentacja w kontrolce graficznej i w menu np. Historia,
    * -# Wyszukiwanie tekstu w zawartości strony,
    * -# Informowanie o postępie w ładowaniu strony (ang. progress bar),
    * -# Zoom - skalowanie zawartości strony www,
    * -# Zaimplementowane funkcjonalności powinny się pojawić w menu,
    * -# Program powinien wykorzystywać ikonki, podpowiedzi oraz okienko "O programie..." w celu ułatwienia obsługi,
    * -# Przeglądarka powinna zapisywać swój stan (np. rozmiar i pozycję okna, ostatnio przeglądaną stronę itp.).



 Wnioski:
    * -# Zadanie pozwoliło na poznanie obsługi i wykorzystywania narzędzi dostepnych w pakiecie QWebKitWidgets
    * oraz utrwalenie znajomości poznanych dotychczas narzędzi frameworku Qt.
    * -# Udało się zaimplementować wszystkie z ww. założeń.
    * -# Nie zaimplementowano dodatkowych funkcjonalności.

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
