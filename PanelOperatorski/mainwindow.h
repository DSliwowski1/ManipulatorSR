#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include <QDateTimeAxis>
#include <QValueAxis>
#include "manipulator.h"

QT_CHARTS_USE_NAMESPACE


#include "polaczenia.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*! \class MainWindow
    \brief Klasa głównego okna programu.

    Klasa głównego okna programu. Przechowuje informacje na temat
    głównego okna, wykresów oraz nastaw. Odpowiada za ich poprawne
    wyświetlanie.
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionPolaczenia_triggered();

    void on_PB_Wyczysc_clicked();

    void on_PB_Wyslij_clicked();

    void readFromPort();

public slots:
    void NoDevicesAvaiable();
    void ConnectionSucceded();
    void ConnectionFailed();
    void NoDevices();
    void NoConnected();
    void StopConnection();

    void UpdateChatrs();

private:
    /*!
     * \var ui
     * \brief ui - wskaźnik na UI okna.
     */
    Ui::MainWindow *ui;
    /*!
     * \var pol
     * \brief ui - wskaźnik na okno połączeń.
     */
    Polaczenia     *pol;
    /*!
     * \var q1
     * \brief q1 - kąt pierwszego przegubu.
     */
    /*!
     * \var q2
     * \brief q2 - kąt drugiego przegubu.
     */
    /*!
     * \var q3
     * \brief q2 - kąt trzeciego przegubu.
     */
    int q1=0, q2=0, q3=0;


    QLineSeries *Daneq1;
    QLineSeries *Daneq2;
    QLineSeries *Daneq3;

    QChart *Wq1;
    QChart *Wq2;
    QChart *Wq3;

    QDateTimeAxis *xAxis1;
    QValueAxis    *yAxis1;
    QDateTimeAxis *xAxis2;
    QValueAxis    *yAxis2;
    QDateTimeAxis *xAxis3;
    QValueAxis    *yAxis3;

    QTimer *timer;


private:
    void sendMessageToDevice(QString msg);
};
#endif // MAINWINDOW_H
