/*
 * trajectory.c
 *
 *  Created on: 31 maj 2020
 *      Author: Patryk
 */
#include <math.h>
#include "trajectory.h"

void calcForwardKinematics(float y[], float q1, float q2, float q3)
{
	float t2 = cos(q1);
	float t3 = sin(q1);
	float t4 = sin(q2);
	float t5 = q2+q3;
	float t6 = cos(t5);
	float t7 = sin(t5);
	float t8 = t4*2.5E+1;
	float t9 = -t8;
	float t10 = t6*2.8E+1;
	float t11 = t9+t10;
	//A0[0][0] = t2*t6;
	//A0[0][1] = -t2*t7;
	//A0[0][2] = t3;
	//A0[0][3] = t2*t11*(3.0/5.0E+2);
	y[0] = t2*t11*(3.0/5.0E+2);
	//A0[1][0] = t3*t6;
	//A0[1][1] = -t3*t7;
	//A0[1][2] = -t2;
	//A0[1][3] = t3*t11*(3.0/5.0E+2);
	y[1] = t3*t11*(3.0/5.0E+2);
	//A0[2][0] = t7;
	//A0[2][1] = t6;
	//A0[2][3] = t7*(2.1E+1/1.25E+2)+cos(q2)*(3.0/2.0E+1)+3.1E+1/2.5E+2;
	y[2] = t7*(2.1E+1/1.25E+2)+cos(q2)*(3.0/2.0E+1)+3.1E+1/2.5E+2;
	//A0[3][3] = 1.0;
}

void initTrajectoryLine(trajectory_line* trajectory, float y[], float y_end[])
{
	trajectory->a[0] = y_end[0] - y[0];
	trajectory->a[1] = y_end[1] - y[1];
	trajectory->a[2] = y_end[2] - y[2];

	trajectory->b[0] = y[0];
	trajectory->b[1] = y[1];
	trajectory->b[2] = y[2];
}

void NextPoint(trajectory_line *trajectory,  float y_d[], int t)
{
	y_d[0] = trajectory->a[0]*t/100 + trajectory->b[0];
	y_d[1] = trajectory->a[1]*t/100 + trajectory->b[1];
	y_d[2] = trajectory->a[2]*t/100 + trajectory->b[2];
}

