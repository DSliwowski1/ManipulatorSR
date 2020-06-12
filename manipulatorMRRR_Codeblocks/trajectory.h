/*
 * trajectory.h
 *
 *  Created on: 31 maj 2020
 *      Author: Patryk
 */

//typ przechowujacy informacje o zadanej trajektorii
typedef struct
{
	float a[3];
	float b[3];
} trajectory_line;

//wyliczenie kinematyki prostej manipulatora
void calcForwardKinematics(float y[], float q1, float q2, float q3);

//zainicjalizowanie trajektorii po ktorej checemy poruszac koncowka manipulatora
void initTrajectoryLine(trajectory_line* trajectory, float y[], float y_end[]);

//funkcja zwraca nastepny punkt na trasie koncowki manipulatora
// trajectory -> trajektoria po ktorej poruszac ma sie koncowka manipulatora
// y_d 	-> tablica przechowujaca punkt w przestrzeni w ktorym ma znalezc sie koncowka manipulatora, w nastepnym kroku
// t -> aktualny krok w ruchu <0,100%>
void NextPoint(trajectory_line *trajectory,  float y_d[], int t);
