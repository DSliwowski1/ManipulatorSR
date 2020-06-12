#include <stdio.h>
#include <stdlib.h>
#include "stdio.h"
#include "matrix.h"
#include "results.h"
#include "pd.h"
#include "trajectory.h"



void initManip(float q1_init, float q2_init, float q3_init, float* q1, float* q2, float* q3, float* q1_last, float* q2_last, float* q3_last)
{
	*q1 = *q1_last = q1_init;
	*q2 = *q2_last = q2_init;
	*q3 = *q3_last = q3_init;
}

// d_t to czas w sekundach!!!
void initPd(reg_pd* pd, float d_t, float k_p, float k_d, float k_i)
{
	pd->i[0] = 0;
	pd->i[1] = 0;
	pd->i[2] = 0;
	pd->k_i = k_i;
	pd->e_last[0] = 0;
	pd->e_last[1] = 0;
	pd->e_last[2] = 0;
	pd->d_t = d_t;
	pd->k_p = k_p;
	pd->k_d = k_d;
}



int main()
{
    FILE * csvFile;

    csvFile = fopen ("results.txt","w");

    float i = 0;
    float j = 0;
    float k = 0;
    long long cycleNumber = 1;
    float q1, q2, q3;
    float q3_fall_point = 0;
    float q1_last, q2_last, q3_last;
	float dq1=0, dq2=0, dq3=0;
	float du1 = 0, du2 = 0, du3 = 0;
	float u1_last = 0, u2_last = 0, u3_last =0;
	int t = 1;
	float matF[3];
	float matG[9];
	//Pozycja efektora
	float y[3] = {0,0,0};
	//Upragniona pozycja efektora
	float y_end[3] = {0,0,0};
	//Upragniona pozycja efektora
	float y_base[3] = {0,0,0};
	//Nastepna pozycja efektora
	float y_d[3] = {0,0,0};
	//Wektor v
	float v[3] = {0,0,0};
	//momenty na silnik
	float u[3] = {0,0,0};
	//momenty na silnik part 1
	float uGF[3] = {0,0,0};
	//momenty na silnik part 2
	float uV[3] = {0,0,0};
	//Regulator PD uzyty w algorytmie
	reg_pd pd;
	reg_pd pd2;
	//trajektoria ruchu manipulatora
	trajectory_line trajectory;

    //inicjalizacja manipulatora
    initManip(0, 0, 0, &q1, &q2, &q3, &q1_last, &q2_last, &q3_last);
    initPd(&pd, 0.5, -20, -0.8, 0);
    initPd(&pd2, 0.5, 10, 0.0, 0);

    printf("Zaczynam prace!\n");

    y_end[0] = 0.150;
    y_end[1] = 0.0;
    y_end[2] = 0.250;

    calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej

    printf("Macierz y %f,%f,%f\n", y[0], y[1], y[2]);
    initTrajectoryLine(&trajectory, y, y_end); //wyliczenie trajektorii manipulatora


    //przypisanie poczatkowych wartosci u1_last, u2_last, u3_last

    calcF(matF, q1, q2, q3, dq1, dq2, dq3);
    calcInvG(matG, q1, q2, q3);


    uGF[0] = matG[0] * (-matF[0]) + matG[1] * (-matF[1]) + matG[2] * (-matF[2]);
    uGF[1] = matG[3] * (-matF[0]) + matG[4] * (-matF[1]) + matG[5] * (-matF[2]);
    uGF[2] = matG[6] * (-matF[0]) + matG[7] * (-matF[1]) + matG[8] * (-matF[2]);

    u1_last = uGF[0];
    u2_last = uGF[1];
    u3_last = uGF[2];

    printf("Poczatkowe u: %f, %f, %f \r\n\n", uGF[0], uGF[1], uGF[2]);

    fprintf(csvFile,"NumerPomiaru, x, y, z, yd1,yd2,yd3\n");
    while(t<=100)
    {

        //ruszmy najpierw przegubem numer 2
        //wyliczenie nastepnej pozycji efektora w algorytmie

	  	NextPoint(&trajectory, y_d, t++);
	  	printf("Nastepny punkt: %f, %f, %f \r\n", y_d[0], y_d[1], y_d[2]);

        //Wyliczenie sterowan u
	  	calcF(matF, q1, q2, q3, dq1, dq2, dq3);
        calcInvG(matG, q1, q2, q3);

        calcV(v, y, y_d, &pd);

        //printf("Macierz v %f,%f,%f\n", v[0], v[1], v[2]);

        calcU(u, matG, matF, v);

        printf("Wyliczone u: %f, %f, %f \r\n", u[0], u[1], u[2]);

        printf("Poprzednie u: %f, %f, %f \r\n", u1_last, u2_last, u3_last);

        //Uno: liczymy roznice pomiedzy obecnym u i poprzednim u

        du1 = (u[0] - u1_last);
        printf("du1: %f\r\n", du2);
        q1 += (du1 * (0.5)); //wspolczynnik wyliczony z wykresu

        du2 = (u[1] - u2_last);
        printf("du2: %f\r\n", du2);
        q2 += (du2 * (-12.4)); //wspolczynnik wyliczony z wykresu

        q1_last = q1;
        q2_last = q2;
        q3_last = q3;

        printf("Obecne q1:%f , q2:%f , q3:%f  \r\n", q1, q2, q3);
        u1_last = u[0];
        u2_last = u[1];

        calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej
        printf("Obecny punkt koncowki manipulatora: %f, %f, %f \r\n\n", y[0], y[1], y[2]);

        //teraz powtorzmy kroki dla q3

         //Wyliczenie sterowan u
	  	calcF(matF, q1, q2, q3, dq1, dq2, dq3);
        calcInvG(matG, q1, q2, q3);

        calcV(v, y, y_d, &pd);

        //printf("Macierz v %f,%f,%f\n", v[0], v[1], v[2]);

        calcU(u, matG, matF, v);

        printf("Wyliczone u: %f, %f, %f \r\n", u[0], u[1], u[2]);

        printf("Poprzednie u: %f, %f, %f \r\n", u1_last, u2_last, u3_last);

        //sprawdzenie punktu przegiecia charakterystyki u3(q3) dla zadanego q2
        q3_fall_point = - q2;
        printf("Fall point: %f \r\n", q3_fall_point);
        //po pierwsze ruch q2

        //dobra, teraz mozemy zajac sie q3. Sprawdzamy roznice miedzy wartosciami u3 i u3_last
        du3 = (u[2] - u3_last);
        printf("du3: %f\r\n", du3);

        //Jesli ta roznica jest ujemna --> zwiekszamy nasz kat. Jesli jest dodatnia --> powinnismy zmniejszyc kat

        //jestesmy w lewej czesci wykresu
        if(q3 < q3_fall_point )
        {
            //q3 += (du3 *(-250));
            //skorygujmy wartosc regulatorem PD
            calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej

            printf("E: %f\n", y_d[2] - y[2]);
            printf("Przed korekta: %f\n", q3);
            q3 += 4*(y_d[2] - y[2]);
            q3 += 0.5*((y_d[2] - y[2]) - pd2.e_last[2])/pd2.d_t;

            pd2.e_last[2] = y_d[2] - y[2];
            printf("Po korekcie: %f\n", q3);
            printf("Mniejsze od fall_point\n");
        }

        else if(q3 > q3_fall_point)
        {
            //q3 += (du3 *(250));
            //skorygujmy wartosc regulatorem PD
            calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej
            
            q3 += 4*(y_d[2] - y[2]);
            q3 += 0.5*((y_d[2] - y[2]) - pd2.e_last[2])/pd2.d_t;
			pd2.e_last[2] = y_d[2] - y[2];
            printf("Wieksze od fall_point\n");
        }


        calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej
        printf("Obecny punkt koncowki manipulatora: %f, %f, %f \r\n\n", y[0], y[1], y[2]);
        u3_last = u[2];

        fprintf(csvFile,"%I64d, %f, %f, %f, %f,%f,%f\n",cycleNumber++, y[0], y[1], y[2], y_d[0], y_d[1], y_d[2]);

    }

    fclose(csvFile);
    return 0;





  /* USER CODE END 3 */
}
