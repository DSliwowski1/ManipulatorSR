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
//void initPd(reg_pd* pd, float d_t, float k_p, float k_d, float k_i)
void initPd(reg_pd* pd, float d_t, float k_p[], float k_d[], float k_i[])
{
	pd->i[0] = 0;
	pd->i[1] = 0;
	pd->i[2] = 0;
	//pd->k_i = k_i;
	pd->e_last[0] = 0;
	pd->e_last[1] = 0;
	pd->e_last[2] = 0;
	pd->d_t = d_t;
	//pd->k_p = k_p;
	//pd->k_d = k_d;

	pd->k_d[0]=k_d[0]; //dla u1
	pd->k_d[1]=k_d[1];
	pd->k_d[2]=k_d[2];

	pd->k_p[0]=k_p[0];
	pd->k_p[1]=k_p[1];
	pd->k_p[2]=k_p[2];

	pd->k_i[0]=k_i[0];
	pd->k_i[1]=k_i[1];
	pd->k_i[2]=k_i[2];
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

	float e_z=0;
	float e_z_last=0;
	float d_e_z=0;
	float I=0;
    float d_t_z=1;
    float korekta_q3 = 0;
	float k_p_z=6.2;
	float k_d_z=0.01;
	float k_i_z=0;

    float e_y=0;
	float e_y_last=0;
	float d_e_y=0;
	float I_y=0;
    float d_t_y=1;
    float korekta_q1 = 0;
	float k_p_y=2;
	float k_d_y=0.05;
	float k_i_y=0;

    float e_x=0;
	float e_x_last=0;
	float d_e_x=0;
	float I_x=0;
    float d_t_x=1;
    float korekta_q2 = 0;
	float k_p_x=2;
	float k_d_x=0.05;
	float k_i_x=0;



    //inicjalizacja manipulatoraxv
    initManip(0, 0, 0, &q1, &q2, &q3, &q1_last, &q2_last, &q3_last);
    //initPd(&pd, 0.5, -23, -0.02, 0);
    //initPd(&pd, 0.5, -30, 0.04, 0);
    float KP[3] = {-20,-19,-30};
    float KD[3] = {-0.02,-0.02,-0.02};
    //float KI[3] = {-80,-3,0};
    float KI[3] = {-50,-3,0};
    initPd(&pd, 0.5, KP, KD, KI);

    printf("Zaczynam prace!\n");

    // Tutaj należy podać zmiany w cm (niemogą one przekraczać jednak możliwośći manipulatora bo zacyna się sypać
    float x_change = 10;
    float y_change = 15;
    float z_change = -20;
    y_end[0] = 0.1688 + x_change/100;
    y_end[1] = 0.0 + y_change/100;
    y_end[2] = 0.274 + z_change/100;


    calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej

    printf("Macierz y %f,%f,%f\n", y[0], y[1], y[2]);
    initTrajectoryLine(&trajectory, y, y_end); //wyliczenie trajektorii manipulatora


    //przypisanie poczatkowych wartosci u1_last, u2_last, u3_last/

    //for(i = -90; i<90; i++)
    //{
    //q3 = i*3.14/180; // przekszta³cenie na radiany



    //u[0] = matG[0] * (-matF[0]) + matG[1] * (-matF[1]) + matG[2] * (-matF[2]);
    //u[1] = matG[3] * (-matF[0]) + matG[4] * (-matF[1]) + matG[5] * (-matF[2]);
   // u[2] = matG[6] * (-matF[0]) + matG[7] * (-matF[1]) + matG[8] * (-matF[2]);

   // printf("Wartosc q1: %f \r\n" ,q3*180/3.14);
   // printf("Wartosc u1: %f \r\n\n", u[2]);

   // fprintf(csvFile,"%I64d, %f, %f, %f, %f,%f,%f\n",cycleNumber++, q1, q2, q3, u[0], u[2], u[3]);
   // }

 while(t<=100)
    {
        //wyliczenie nastepnej pozycji efektora w algorytmie
	  	NextPoint(&trajectory, y_d, t++);

	  	//printf("Nastepny punkt: %f, %f, %f \r\n", y_d[0], y_d[1], y_d[2]);

        //Wyliczenie sterowan u
        calcForwardKinematics(y, q1, q2, q3);
	  	calcF(matF, q1, q2, q3, dq1, dq2, dq3);
        calcInvG(matG, q1, q2, q3);
        calcV(v, y, y_d, &pd);
        calcU(u, matG, matF, v);

        //printf("Wyliczone u: %f, %f, %f \r\n", u[0], u[1], u[2]);



        //printf("Poprzednie u: %f, %f, %f \r\n", u1_last, u2_last, u3_last);

        //sprawdzenie punktu przegiecia charakterystyki u3(q3) dla zadanego q2
        q3_fall_point = - q2;
        //printf("Fall point: %f \r\n", q3_fall_point);
        du1 = (u[0] - u1_last);
        //po pierwsze ruch q2
        //Uno: liczymy roznice pomiedzy obecnym u i poprzednim u
        //du2 = (u[1] - u2_last);
        //dobra, teraz mozemy zajac sie q3. Sprawdzamy roznice miedzy wartosciami u3 i u3_last
        //du3 = (u[2] - u3_last);


       // printf("du1, du2, du3: %f, %f, %f \r\n",du1, du2, du3);


        //Jesli ta roznica jest ujemna --> zwiekszamy nasz kat. Jesli jest dodatnia --> powinnismy zmniejszyc kat

        q1_last = q1;
        q2_last = q2;
        q3_last = q3;

         if(t>2)
        {
             q1 += (du1 * (-17.0)); //wspolczynnik wyliczony z wykresu

        }

        calcForwardKinematics(y, q1, q2, q3);
         //liczenie uchybu na y
        e_y = y_d[1] -y[1];
        //cz³on I dla y
        I_y += k_i_y * e_y * d_t_y;
        //czlon D dla y
        d_e_y = (e_y - e_y_last)/ d_t_y;

        e_y_last = e_y;

        korekta_q1 =  k_d_y*d_e_y + k_p_y*e_y + I_y;
        q1 += korekta_q1;


        calcForwardKinematics(y, q1, q2, q3);
	  	calcF(matF, q1, q2, q3, dq1, dq2, dq3);
        calcInvG(matG, q1, q2, q3);
        calcV(v, y, y_d, &pd);
        calcU(u, matG, matF, v);

        du2 = (u[1] - u2_last);
        //zwiekszamy otrzymany przez nas kat
        if(t>2)
        {
             q2 += (du2 * (-15.0)); //wspolczynnik wyliczony z wykresu

        }

         calcForwardKinematics(y, q1, q2, q3);
         //liczenie uchybu na y
        e_x = y_d[0] -y[0];
        //cz³on I dla y
        I_x += k_i_x * e_x * d_t_x;
        //czlon D dla y
        d_e_x = (e_x - e_x_last)/ d_t_x;

        e_x_last = e_x;

        korekta_q2 =  k_d_x*d_e_x + k_p_x*e_x + I_x;
        //q2 += korekta_q2;

        //printf("Korekta Q2: %f \r\n", korekta_q2);


        calcForwardKinematics(y, q1, q2, q3);
	  	calcF(matF, q1, q2, q3, dq1, dq2, dq3);
        calcInvG(matG, q1, q2, q3);
        calcV(v, y, y_d, &pd);
        calcU(u, matG, matF, v);

        du3 = (u[2] - u3_last);
        //jestesmy w lewej czesci wykresu

        if(q3 < q3_fall_point )
        {
            q3 += (du3 *(-20));
            //printf("Mniejsze od fall_ponit\n");
        }

        else if(q3 > q3_fall_point)
        {
            q3 += (du3 *(20));
            //printf("Wieksze od fall_ponit\n");
        }

        calcForwardKinematics(y, q1, q2, q3);





        calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej

        //liczenie uchybu na Z
        e_z = y_d[2] -y[2];
        //cz³on I dla z
        I += k_i_z * e_z * d_t_z;
        //czlon D dla z
        d_e_z = (e_z - e_z_last)/ d_t_z;

        e_z_last = e_z;

        korekta_q3 =  k_d_z*d_e_z + k_p_z*e_z + I;
        q3 += korekta_q3;





        calcForwardKinematics(y, q1, q2, q3); //wyliczenie kinematyki prostej


        printf("Obecne q1:%f stopni, q2:%f stopni, q3:%f stopni \r\n", q1*180/3.14, q2*180/3.14, q3*180/3.14);
        printf("Obecny punkt koncowki manipulatora: %f, %f, %f \r\n", y[0], y[1], y[2]);

        printf("BLAD POMIARU: %f, %f, %f \r\n\n", y_d[0]-y[0], y_d[1]-y[1], y_d[2]-y[2]);
        u1_last = u[0];
        u2_last = u[1];
        u3_last = u[2];

        fprintf(csvFile,"%I64d %f %f %f %f %f %f \n",cycleNumber++, y[0], y[1], y[2], y_d[0], y_d[1], y_d[2]);


    }

    //printf("Poczatkowe u: %f, %f, %f \r\n\n", uGF[0], uGF[1], uGF[2]);

    //fprintf(csvFile,"Numerpomiaru, q1, q2, q3, u1, u2, u3\n");


    fclose(csvFile);
    return 0;





  /* USER CODE END 3 */
}
