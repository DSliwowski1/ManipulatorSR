#ifndef POLACZENIA_H
#define POLACZENIA_H

#include <QDialog>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QList>

namespace Ui {
class Polaczenia;
}

/*! \class Polaczenia
    \brief Klasa przechowująca obsługująca połączenia z mikrokontrolerem.
*/
class Polaczenia : public QDialog
{
    Q_OBJECT

public:
    explicit Polaczenia(QWidget *parent = nullptr);
    ~Polaczenia();

public:
    /*!
     * \brief GetDevice - Zwraca wskaźnik na urządzenie.
     * \return Wskaźnik na urządzenie.
     */
    QSerialPort* GetDevice() {return device;}

signals:
    /*!
     * \brief FoundNoDevices() - sygnał znaleziono urządzenia.
     */
    void FoundNoDevices();
    /*!
     * \brief NoAvaiableDevices() - sygnał braku dostępnych urządzeń.
     */
    void NoAvaiableDevices();
    /*!
     * \brief ConnectionDenied() - sygnał niemożliwości nawiązania połączenia.
     */
    void ConnectionDenied();
    /*!
     * \brief ConnectionUp() - sygnał poprawnego nawiązania połączenia.
     */
    void ConnectionUp();
    /*!
     * \brief NoDeviceConnected() - sygnał braku połączenia z urządzeniem.
     */
    void NoDeviceConnected();
    /*!
     * \brief ConnectionClosed() - sygnał zakończenia połączenia.
     */
    void ConnectionClosed();

private slots:
    void on_Szukaj_clicked();


    void on_Polacz_clicked();

    void on_Rozlacz_clicked();

private:
    Ui::Polaczenia *ui;
    QList<QSerialPortInfo> devices;
    QSerialPort    *device;
};

#endif // POLACZENIA_H
