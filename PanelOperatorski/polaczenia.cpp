#include "polaczenia.h"
#include "ui_polaczenia.h"

#include <QtDebug>

/*!
 * \brief Polaczenia::Polaczenia() - Konstuktor klasy, ustawiający okno
 * \param parent - Wskaźnik na rodzica
 */
Polaczenia::Polaczenia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Polaczenia)
{
    ui->setupUi(this);
    device = new QSerialPort(this);
}

/*!
 * \brief Polaczenia::~Polaczenia() - Destruktor
 */
Polaczenia::~Polaczenia()
{
    delete ui;
}

/*!
 * \brief Polaczenia::on_Szukaj_clicked() - Slot obsługujący wyszukiwanie dostępnych urządzeń.
 */
void Polaczenia::on_Szukaj_clicked()
{
    qDebug() << "Szukanie urządzeń";
    devices = QSerialPortInfo::availablePorts();
    if(!devices.isEmpty())
    {
        for(int i = 0; i<devices.count(); ++i){
            qDebug() << devices.at(i).portName() << " " << devices.at(i).description();
            this->ui->CB_Urzadzenia->addItem(devices.at(i).portName() + " " + devices.at(i).description());
        }
    }
    else
    {
        emit FoundNoDevices();
    }
}

/*!
 * \brief Polaczenia::on_Polacz_clicked() - slot obługujący nawiązywanie połączenia z urządzeniem.
 */
void Polaczenia::on_Polacz_clicked()
{
    if(this->ui->CB_Urzadzenia->count() == 0)
    {
        emit NoAvaiableDevices();
        return;
    }

    QString portName = this->ui->CB_Urzadzenia->currentText().split(" ").first();
    qDebug() << portName;
    this->device->setPortName(portName);

    if(this->device->open(QSerialPort::ReadWrite))
    {
        this->device->setBaudRate(QSerialPort::Baud9600);
        this->device->setDataBits(QSerialPort::Data8);
        this->device->setParity(QSerialPort::EvenParity);
        this->device->setStopBits(QSerialPort::OneStop);
        this->device->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "Connected";
        emit ConnectionUp();
    }
    else
    {
        qDebug() << "Connection denied";
        emit ConnectionDenied();
    }
}

/*!
 * \brief Polaczenia::on_Rozlacz_clicked() - slot obsługujący rozłączanie z urządzeniem.
 */
void Polaczenia::on_Rozlacz_clicked()
{
    if(this->device->isOpen())
    {
        device->close();
        emit ConnectionClosed();
        qDebug() << "Disconnected";
    }
    else
    {
        qDebug() << "No device connected";
        emit NoDeviceConnected();
    }
}
