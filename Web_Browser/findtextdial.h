/*!
  \date 25.11.2017r.
  \author Damian Świerk
  */

#ifndef FINDTEXTDIAL_H
#define FINDTEXTDIAL_H

#include <QWidget>

namespace Ui {
class FindTextDial;
}

/*!
 * \brief Klasa FindTextDial
 * Klasa zawiera funkcjonalności widgetu odpowiedzialnego za wprowadzanie wyszukiwanego tesktu
 * w oknie przeglądarki.
 */
class FindTextDial : public QWidget
{
    Q_OBJECT

public:
    explicit FindTextDial(QWidget *_parent = 0);    ///< Konstruktor
    ~FindTextDial();                                ///< Destruktor

signals:
    void sendText(QString);     ///< Sygnał przekazujący wyszuiwaną frazę
    void findClickedReturn();   ///< Sygnał po kliknięciu przycisku enter

public slots:
    void setText(QString _text);    ///< Slot wywoływany w chwili zmiany wyszukiwanego tekstu
    void setText();                 ///< Slot wywoływany w chwili zmiany wyszukiwanego tekstu po naciśnięciu klawisza enter
    void findClicked();             ///< Slot wywoływany po naciśnięciu klawisza Find

private:
    Ui::FindTextDial *ui;   ///< Obiekt klasy FindTextDial
    QString text;           ///< Atrybut przechowujący szukany tekst
};

#endif // FINDTEXTDIAL_H
