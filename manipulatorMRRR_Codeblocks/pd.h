/*
 * pd.h
 *
 *  Created on: 31 maj 2020
 *      Author: Patryk
 */

#ifndef INC_PD_H_
#define INC_PD_H_

typedef struct
{
	float i[3];
	//ostatni uchyb
	float e_last[3];
	//okres aktualizacji pozycji efektora
	float d_t;
	//wzmocnienie czlonu D regulatora
	//float k_p;
	//wzmocnienie czlonu D regulatora
	//float k_d;
	float k_i[3];

	float k_d[3];
	float k_p[3];

} reg_pd;


void calcV(float v[], float y[], float y_d[], reg_pd* pd);



#endif /* INC_PD_H_ */
