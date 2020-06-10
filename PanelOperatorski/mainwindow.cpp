#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CRC.h"

#include <QDebug>
#include <cstdio>
#include <QByteArray>

/*!
 * \brief MainWindow::MainWindow() - Konstruktor klasy, odpowiada ustawienie okna, połączeń oraz skonfigurowanie wykresów.
 * \param parent - wskaźnik na okno rodzica
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("Manipulator MRR"));
    this->setWindowIcon(QIcon(QPixmap(":/zasoby/img/MIcone.png")));

    timer = new QTimer(this);

    pol = new Polaczenia(this);
    pol->setModal(true);
    pol->setWindowTitle(tr("Połączenia"));

    connect(pol, SIGNAL(FoundNoDevices()), this, SLOT(NoDevices()));
    connect(pol, SIGNAL(NoAvaiableDevices()), this, SLOT(NoDevicesAvaiable()));
    connect(pol, SIGNAL(ConnectionUp()), this, SLOT(ConnectionSucceded()));
    connect(pol, SIGNAL(ConnectionDenied()), this, SLOT(ConnectionFailed()));
    connect(pol, SIGNAL(NoDeviceConnected()), this, SLOT(NoConnected()));
    connect(pol, SIGNAL(ConnectionClosed()), this, SLOT(StopConnection()));
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateChatrs()));

    this->ui->LE_ZadajX->setValidator(new QIntValidator());
    this->ui->LE_ZadajY->setValidator(new QIntValidator());
    this->ui->LE_ZadajZ->setValidator(new QIntValidator());

    this->ui->statusbar->addPermanentWidget(this->ui->StatusLabel);
    this->ui->StatusLabel->setText(tr("<font color='red'> Rozłączony </font> z urządzeniem."));

    timer->start(1000);

    this->Daneq1 = new QLineSeries(this);
    this->Daneq2 = new QLineSeries(this);
    this->Daneq3 = new QLineSeries(this);

    Wq1 = new QChart();
    Wq1->legend()->hide();
    Wq1->addSeries(Daneq1);
    Wq1->setTitle("Q1");
    this->ui->QChartView_Q1->setChart(Wq1);

    Wq2 = new QChart();
    Wq2->legend()->hide();
    Wq2->addSeries(Daneq2);
    Wq2->setTitle("Q2");
    this->ui->QChartView_Q2->setChart(Wq2);

    Wq3 = new QChart();
    Wq3->legend()->hide();
    Wq3->addSeries(Daneq3);
    Wq3->setTitle("Q3");
    this->ui->QChartView_Q3->setChart(Wq3);

    xAxis1 = new QDateTimeAxis(this);
    yAxis1 = new QValueAxis(this);
    xAxis2 = new QDateTimeAxis(this);
    yAxis2 = new QValueAxis(this);
    xAxis3 = new QDateTimeAxis(this);
    yAxis3 = new QValueAxis(this);

    xAxis1->setTickCount(10);
    xAxis1->setFormat("hh:mm:ss");
    xAxis1->setTitleText("Czas");
    Wq1->addAxis(xAxis1, Qt::AlignBottom);
    Daneq1->attachAxis(xAxis1);

    yAxis1->setLabelFormat("%i");
    yAxis1->setTitleText("Kąt");
    Wq1->addAxis(yAxis1, Qt::AlignLeft);
    Daneq1->attachAxis(yAxis1);

    xAxis2->setTickCount(10);
    xAxis2->setFormat("hh:mm:ss");
    xAxis2->setTitleText("Czas");
    Wq2->addAxis(xAxis2, Qt::AlignBottom);
    Daneq2->attachAxis(xAxis2);

    yAxis2->setLabelFormat("%i");
    yAxis2->setTitleText("Kąt");
    Wq2->addAxis(yAxis2, Qt::AlignLeft);
    Daneq2->attachAxis(yAxis2);

    xAxis3->setTickCount(10);
    xAxis3->setFormat("hh:mm:ss");
    xAxis3->setTitleText("Czas");
    Wq3->addAxis(xAxis3, Qt::AlignBottom);
    Daneq3->attachAxis(xAxis3);

    yAxis3->setLabelFormat("%i");
    yAxis3->setTitleText("Kąt");
    Wq3->addAxis(yAxis3, Qt::AlignLeft);
    Daneq3->attachAxis(yAxis3);
}

MainWindow::~MainWindow()
{
    delete Wq1;
    delete ui;
}

/*!
 * \brief MainWindow::on_actionPolaczenia_triggered() - slot, którego zadaniem jest wyświetlenie okna połączeń
 */
void MainWindow::on_actionPolaczenia_triggered()
{
    pol->show();
}

/*!
 * \brief MainWindow::on_PB_Wyczysc_clicked() - slot, którego zadaniem jest wyczyszczenie QLineEdit odpowiedzialnych za wprowadzanie współżędnych.
 */
void MainWindow::on_PB_Wyczysc_clicked()
{
    this->ui->LE_ZadajX->clear();
    this->ui->LE_ZadajY->clear();
    this->ui->LE_ZadajZ->clear();
    this->ui->statusbar->showMessage(tr("Wyczyszczono"), 5000);
}

/*!
 * \brief MainWindow::on_PB_Wyslij_clicked() - slot obsługujący za wysyłanie informacji do mikrokontorlera.
 */
void MainWindow::on_PB_Wyslij_clicked()
{
    QString xstr = this->ui->LE_ZadajX->text();
    QString ystr = this->ui->LE_ZadajY->text();
    QString zstr = this->ui->LE_ZadajZ->text();
    int x = xstr.toInt();
    int y = ystr.toInt();
    int z = zstr.toInt();

    //char tmp[13];
    //sprintf(tmp, "%03d\t%03d\t%03d\n\r", x, y, z);
    QString msg = QString("Z%1 %2 %3").arg(x, 3, 10, QChar('0')).arg(y, 3, 10, QChar('0')).arg(z, 3, 10, QChar('0'));

    if(xstr.isEmpty() || ystr.isEmpty() || zstr.isEmpty())
    {
        this->ui->statusbar->showMessage(tr("UWAGA! Pola współrzędnych nie mogą być puste przy wysyłaniu"), 10000);
        return;
    }

    if((x <= 99 && x >=-99) && (y <= 99 && y >=-99) && (z <= 99 && z >=-99))
    {
        if(this->pol->GetDevice()->isOpen() && this->pol->GetDevice()->isWritable())
        {
            char crc = CRC8(msg.toStdString().c_str(), 12);
            QByteArray tmp(1, crc);
            msg += " " + QString(tmp.toHex()) + "\r\n";
            qDebug() << msg.toStdString().c_str();
            this->ui->statusbar->showMessage(tr("Wysyłanie wiadomości: ") + msg, 10000);
            this->pol->GetDevice()->write(msg.toStdString().c_str());
        }
        else
        {
            this->ui->statusbar->showMessage(tr("UWAGA! Błąd przy wysyłaniu, nie wykryto urządzenia!"), 10000);
            return;
        }
    }
    else
    {
        this->ui->statusbar->showMessage(tr("UWAGA! Podane liczy są z poza zakresu [-99, 99]!"), 10000);
        return;
    }
}


/*!
 * \brief MainWindow::readFromPort() - slot odpowiedzialny za obsługę odbierania ramek z mikrokontorlera.
 */
void MainWindow::readFromPort()
{
    while(this->pol->GetDevice()->canReadLine())
    {
        QString line = this->pol->GetDevice()->readLine();

        if(line[0] == 'Q' && line[15] == '\r' && line[16] == '\n')
        {
            //qDebug() << line.left(12).toStdString().c_str();
            char crc = CRC8((line.toStdString().c_str()), 12);
            char tmp = static_cast<char>(line.mid(13, 2).toInt(nullptr,16));
            if(crc == tmp)
            {
                        QString terminator = "\n";
                        int pos = line.lastIndexOf(terminator);

                        QList<QString> tmp = line.left(pos).split(" ");
                        //qDebug() << tmp.at(0).mid(1, 3).toInt();
                        q1 = tmp.at(0).mid(1, 3).toInt();
                        q2 = tmp.at(1).toInt();
                        q3 = tmp.at(2).toInt();
                        //qDebug() << q1 << " " << q2 << " " << q3;
                        this->ui->LE_Q1->setText(QString::number(q1));
                        this->ui->LE_Q2->setText(QString::number(q2));
                        this->ui->LE_Q3->setText(QString::number(q3));
                        Manip.SetQ0_deg(q1);
                        Manip.SetQ1_deg(q2);
                        Manip.SetQ2_deg(q3);
                        this->ui->View->update();
            }
        }
    }
}

/*!
 * \brief MainWindow::UpdateChatrs() - slot odpowiedzialny za akutalizowanie wykresów.
 */
void MainWindow::UpdateChatrs()
{
    QDateTime time;
    time.setDate(QDate::currentDate());
    time.setTime(QTime::currentTime());

    xAxis1->setMin(time.addSecs(-15));
    xAxis1->setMax(time.addSecs(15));
    xAxis2->setMin(time.addSecs(-15));
    xAxis2->setMax(time.addSecs(15));
    xAxis3->setMin(time.addSecs(-15));
    xAxis3->setMax(time.addSecs(15));

    yAxis1->setMax(q1 + 20);
    yAxis2->setMax(q2 + 20);
    yAxis3->setMax(q3 + 20);

    yAxis1->setMin(q1 - 20);
    yAxis2->setMin(q2 - 20);
    yAxis3->setMin(q3 - 20);

    Daneq1->append(time.toMSecsSinceEpoch(), q1);
    Daneq2->append(time.toMSecsSinceEpoch(), q2);
    Daneq3->append(time.toMSecsSinceEpoch(), q3);
}

/*!
 * \brief MainWindow::NoDevices() - slot odpowiedzialny za wyświetlenie informacji o braku wykrytych urządzeń.
 */
void MainWindow::NoDevices()
{
    this->ui->statusbar->showMessage(tr("UWAGA!  Nie znaleziono urządzeń"), 10000);
}

/*!
 * \brief MainWindow::NoDevicesAvaiable() - slot odpowiedzialny za wyświetlenie informacji o braku dostępnych urządzeń.
 */
void MainWindow::NoDevicesAvaiable()
{
    this->ui->statusbar->showMessage(tr("UWAGA!  Brak dostępnych urządzeń"), 10000);
}

/*!
 * \brief MainWindow::ConnectionSucceded() - slot odpowiedzialny za wyświetlenie informacji o nawiązaniu połączenia.
 */
void MainWindow::ConnectionSucceded()
{
    connect(this->pol->GetDevice(), SIGNAL(readyRead()), this, SLOT(readFromPort()));
    this->ui->statusbar->showMessage(tr("Połączono"), 10000);
    this->ui->StatusLabel->setText(tr("<font color='Green'> Połączony </font> z urządzeniem."));
}

/*!
 * \brief MainWindow::ConnectionFailed() - slot odpowiedzialny za wyświetlenie informacji o niemożliwości połączenia z urządzeniem.
 */
void MainWindow::ConnectionFailed()
{
    this->ui->statusbar->showMessage(tr("UWAGA! Nie można połączyć się z urządzeniem"), 10000);
}

/*!
 * \brief MainWindow::NoConnected() - slot odpowiedzialny za wyświetlenie informacji o braku połączonych urządzeń.
 */
void MainWindow::NoConnected()
{
    this->ui->statusbar->showMessage(tr("UWAGA! Żadne urządzenie nie jest podłączone"), 10000);
}

/*!
 * \brief MainWindow::StopConnection() - slot odpowiedzialny za wyświetlenie informacji o zakończeniu połączenia.
 */
void MainWindow::StopConnection()
{
    disconnect(this->pol->GetDevice(), SIGNAL(readyRead()), this, SLOT(readFromPort()));
    this->ui->statusbar->showMessage(tr("Rozłączono"), 10000);
    this->ui->StatusLabel->setText(tr("<font color='red'> Rozłączony </font> z urządzeniem."));
}
