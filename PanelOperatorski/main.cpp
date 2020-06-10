#include "mainwindow.h"

#include <QApplication>

/*!
 * \mainpage Panel Operatorski
 *
 *  \section intro_sec 1. Wstęp
 *
 *  Program panelu operatorskiego, służący do obsługi manipulatora
 *  o trzech stopniach swobody. Pogram wizualizuje położenie ramienia,
 *  rysuje wykresy obrazujące zmianę nasatwienia przegubów w czasie
 *  oraz pozwala na zadawanie współrzędnej w przestrzeni zadaniowej
 *  robota, do której ma sie poruszać koncówka efektora. Program został
 *  przygotowany został w ramach kursu "Wizualizacja Danych Sensorycznych - Projekt"
 *  i obsługuje manipulator przygotowany w ramach kursu "Sterowniki Robotów - Projekt".
 *
 *  \section obsluga_sec 2. Obsługa
 *  Poniżej przedstawione zostanie pokrótce sposób osbługi programu.
 *
 *  \subsection obs_sub1 2.1 Nawiązywanie połączenia
 *  W pasku narzędzi znajduje się opcja "Połączenia". Klikając ją pojawia się okno pozwalające
 *  na nawiązywanie połączenia. Naciśnięcie przycisku "Szukaj" spowoduje wyszukanie wszystkich
 *  możliwych urządzeń, które pojawią się w rozwijanej liście po prawej. Z niej można wybrać
 *  urządzenia do jakiego się chcemy połączyć. Po tym kroku nacisnięcie przycisku "Połącz"
 *  spowoduje połączenie się z urządzeniem.  Przycisk "Rozłącz" kończy połączenie.
 *
 *  \subsection obs_sub2 2.2 Okno manipulatora
 *  - Przyciśnięcie LPM i ruch myszką powoduje obracanie kamery.
 *  - Przyciśnięcie PPM i ruch myszką powoduje przesuwanie kamery.
 *  - SCROLLUP podowuje przybliżanie kamery.
 *  - SCROLLDOWN powoduje oddlanie kamery.
 *  - ALT + F1-9 zapisuje położenie kamry.
 *  - F1-9 przechodzi do zapisanego wcześniej położenia kamery.
 *
 *  \subsection obs_sub3 2.3 Wysyłanie informacji
 *  Gdy połączenie w urządzeniem jest nawiązane mozliwe jest wtedy wysłanie do niego informacji.
 *  Następuje to poprzez wprowadzenie wartości w odpowiednie pola i naciśnięcie przycisku "Wyślij".
 *  UWAGA! Wszystkie pola muszą mieć wpisaną wartość, aby ją wysłać.
 *
 *  \section ekran_sec 3. Zrzut ekranu
 *  \image html app.png
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
