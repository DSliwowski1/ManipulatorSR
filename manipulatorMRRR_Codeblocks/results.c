/*
 * results.c
 *
 *  Created on: May 31, 2020
 *      Author: Patryk
 */

#include "results.h"

void calcU(float u[], float invG[], float F[], float v[])
{
	int u_min = -0.05;
	int u_max = 0.05;
	u[0] = invG[0] * (-F[0]+v[0]) + invG[1] * (-F[1]+v[1]) + invG[2] * (-F[2]+v[2]);
	u[1] = invG[3] * (-F[0]+v[0]) + invG[4] * (-F[1]+v[1]) + invG[5] * (-F[2]+v[2]);
	u[2] = invG[6] * (-F[0]+v[0]) + invG[7] * (-F[1]+v[1]) + invG[8] * (-F[2]+v[2]);
/*

	if(u_max < u[0])
	{
		u[0] = u_max;
	}
	else if(u_min > u[0])
	{
		u[0] = u_min;
	}

	if(u_max < u[1])
	{
		u[1] = u_max;
	}
	else if(u_min > u[1])
	{
		u[1] = u_min;
	}

	if(u_max < u[2])
	{
		u[2] = u_max;
	}
	else if(u_min > u[2])
	{
		u[2] = u_min;
	}
*/
}


