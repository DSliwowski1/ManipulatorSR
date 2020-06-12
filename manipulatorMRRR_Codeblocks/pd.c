/*
 * pd.c
 *
 *  Created on: 31 maj 2020
 *      Author: Patryk
 */

#ifndef SRC_PD_C_
#define SRC_PD_C_
#include "pd.h"
#include "stdio.h"


void calcV(float v[], float y[], float y_d[], reg_pd* pd)
{
	float e[3];
	float d_e[3];

	//uchyb jako roznica miedzy wejsciem a wyjsciem ukadu
	e[0] = y[0] - y_d[0];
	e[1] = y[1] - y_d[1];
	e[2] = y[2] - y_d[2];


	//czlon i
	pd->i[0] += pd->k_i[0] * e[0] *pd->d_t;
	pd->i[1] += pd->k_i[1] * e[1] *pd->d_t;
	pd->i[2] += pd->k_i[2] * e[2] *pd->d_t;

	//e obecne - e poprzednie / czas ktory minal. e
	d_e[0] = (e[0] - pd->e_last[0])/ pd->d_t;
	d_e[1] = (e[1] - pd->e_last[1])/ pd->d_t;
	d_e[2] = (e[2] - pd->e_last[2])/ pd->d_t;

	//przypisanie wartosci poprzedniego uchybu
	pd->e_last[0] = e[0];
	pd->e_last[1] = e[1];
	pd->e_last[2] = e[2];


	//liczymy wektor V
	//v[0] = -(pd->k_d*d_e[0])-(pd->k_p*e[0]) - pd->i[0];
	//v[1] = -(pd->k_d*d_e[1])-(pd->k_p*e[1]) - pd->i[1];
	//v[2] = -(pd->k_d*d_e[2])-(pd->k_p*e[2]) - pd->i[2];

	//printf("MACIERZ KP %f,%f,%f\n", pd->k_p[0], pd->k_p[1], pd->k_p[2]);
	//e[0] to x który zale¿y od q2 które zale¿y od u2 a wiêc od v2 = v[1]
	v[0] = -(pd->k_d[0]*d_e[0])-(pd->k_p[0]*e[0])- pd->i[0];
	v[1] = -(pd->k_d[1]*d_e[1])-(pd->k_p[1]*e[1])- pd->i[1];
    v[2] = -(pd->k_d[2]*d_e[2])-(pd->k_p[2]*e[2])- pd->i[2];
    //printf("MACIERZ V %f,%f,%f\n", v[0], v[1], v[2]);
}




#endif /* SRC_PD_C_ */
