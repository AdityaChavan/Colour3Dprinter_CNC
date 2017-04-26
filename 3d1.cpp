#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <boost/thread.hpp>


using namespace std;
int steps1 = 0;
int steps2 = 0;
int steps3 = 0;
int steps4 = 0;

int stp1_1a = 47;
int stp1_1b = 46;
int stp1_2a = 27;
int stp1_2b = 65;

int stp2_1a = 66;
int stp2_1b = 69;
int stp2_2a = 45;
int stp2_2b = 23;

int stp3_1a = 67;
int stp3_1b = 68;
int stp3_2a = 44;
int stp3_2b = 26;

int stp4_1a = 30;
int stp4_1b = 60;
int stp4_2a = 31;
int stp4_2b = 50;

int global_ms=7;
float inchtocm=25.4;
int inch;

FILE *export_file = NULL;
FILE *IO_direction = NULL;

int direction[6];
string str123[2];
//float dist[2];
float extruder1=0;
int ttime = 0;
float multi = 1;
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void pinexport(int a)
{//exports pin number a


	char str[100];       //value to pass to export file
	sprintf(str, "%d", a);

	export_file = fopen("/sys/class/gpio/export", "w");
	fwrite(str, 1, sizeof(str), export_file);
	fclose(export_file);
	printf("Exported pin %d\n", a);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pinwrite(int a, int b)
{
	///// pinwrite(pin,value)/////

	char str[100];
	char str1[] = "low";
	char str2[] = "high";


	sprintf(str, "/sys/class/gpio/gpio%d/direction", a);

	IO_direction = fopen(str, "w");

	if (b == 0)
	{
		fwrite(str1, 1, sizeof(str1), IO_direction);   //set the pin to LOW
	}
	else if (b == 1)
	{
		fwrite(str2, 1, sizeof(str2), IO_direction);   //set the pin to HIGH
	}
	fclose(IO_direction);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX*/
void incstepperx()
{
	int a, b, c, d, stp;

	a = stp1_1a;
	b = stp1_1b;
	c = stp1_2a;
	d = stp1_2b;

	stp = steps1;


	if (direction[1] == 1)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 1;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 2;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 3;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 0;
		}

		//printf("\t\t\t\t\t\t\tstep1=%d\n",steps1);

		steps1 = stp;
	}
	else if (direction[1] == 0)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 3;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 0;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 1;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 2;
		}
		//printf("\t\t\t\t\t\t\tstep1=%d\n",steps1);
		steps1 = stp;

	}
	//usleep(10);
}
/*YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY*/
void incsteppery()
{
	int a, b, c, d, stp;

	a = stp2_1a;
	b = stp2_1b;
	c = stp2_2a;
	d = stp2_2b;

	stp = steps2;

	if (direction[2] == 1)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 1;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 2;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 3;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 0;
		}
		//printf("\t\t\t\t\t\t\t\tstep2=%d\n",steps2);

		steps2 = stp;
	}
	else if (direction[2] == 0)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 3;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 0;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 1;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 2;
		}
		//printf("\t\t\t\t\t\t\t\tstep2=%d\n",steps2);

		steps2 = stp;
	}
	//usleep(10);
}
/*ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ*/
void incstepperz()
{
	int a, b, c, d, stp;
	//printf("Direction_3==%d\t%d\n",direction[3],steps3);
	a = stp3_1a;
	b = stp3_1b;
	c = stp3_2a;
	d = stp3_2b;

	stp = steps3;


	if (direction[3] == 1)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 1;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 2;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 3;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 0;
		}

		//	printf("\t\t\t\t\t\t\tstep3=%d\n",steps3);

		steps3 = stp;
	}
	else if (direction[3] == 0)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 3;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 0;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 1;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 2;
		}
		//printf("\t\t\t\t\t\t\tstep3=%d\n",steps3);
		steps3 = stp;

	}
	//usleep(10);
}
/*EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE1111111111111111111111111111111111111111*/
void incsteppere()
{
	int a, b, c, d, stp;
	//printf("Direction_4==%d\t%d\n",direction[4],steps4);
	a = stp4_1a;
	b = stp4_1b;
	c = stp4_2a;
	d = stp4_2b;

	stp = steps4;


	if (direction[4] == 1)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 1;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 2;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 3;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 0;
		}

		//	printf("\t\t\t\t\t\t\tstep3=%d\n",steps3);

		steps4 = stp;
	}
	else if (direction[4] == 0)
	{
		if (stp == 0)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 3;
		}
		else if (stp == 1)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 1);
			pinwrite(d, 0);
			stp = 0;
		}
		else if (stp == 2)
		{
			pinwrite(a, 0);
			pinwrite(b, 1);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 1;
		}
		else if (stp == 3)
		{
			pinwrite(a, 1);
			pinwrite(b, 0);
			pinwrite(c, 0);
			pinwrite(d, 1);
			stp = 2;
		}
		//printf("\t\t\t\t\t\t\tstep4=%d\n",steps4);
		steps4 = stp;

	}
	//usleep(10);
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stepper(int num, float dist, int time) /*num from 1 to 3; dist in mm; time in usec */
{
	printf("num=%d\tdist= %f\ttime= %d\t", num, dist, time);

	if ((dist <= 0.00001) && (dist >= -0.00001))
	{
		printf("Dist zero for %d motor\n", num);
		return;
	}
	if (dist<0)
	{
		direction[num] = 0; //reverse
		dist = fabs(dist);
	}
	else
		direction[num] = 1;//forward

	if (dist != 0)
	{
		int stps;
		float t;
		float rstps = (dist * 25) - 0.5;
		stps = ceil(rstps);
	
		int t1;
		if (stps != 0)
		{
			t = (float)time / (float)stps;
			t1 = ceil(t * 1000 - 0.5);
		}
		else t1 = 10001;
		//printf("%f\n",t);
				printf("\t\tmotor:%d ,  %d steps, %d time\n", num, stps, t1);

			for (int i = 0; i<stps; i++)
			{

				if (num == 1) { incstepperx(); }
				else if (num == 2) { incsteppery(); }
				else if (num == 3) { incstepperz(); }
				else if (num == 4) { incsteppere(); }

				usleep(t1);

			}
			//printf("Moved Motor %d in direction %d for distance of %f mm, %d steps with step time %d micro sec.\n\n", num, direction[num], dist, stps, t1);
	
		//else
		//printf("time too small for %d\nCalulated time: %f\nFor %f mm, time must be %f sec\n",num,t*1000,dist,(float)stps/100); 
	}

}

void clearall()
{
	pinwrite(stp1_1a, 0);
	pinwrite(stp1_1b, 0);
	pinwrite(stp1_2a, 0);
	pinwrite(stp1_2b, 0);

	pinwrite(stp2_1a, 0);
	pinwrite(stp2_1b, 0);
	pinwrite(stp2_2a, 0);
	pinwrite(stp2_2b, 0);

	pinwrite(stp3_1a, 0);
	pinwrite(stp3_1b, 0);
	pinwrite(stp3_2a, 0);
	pinwrite(stp3_2b, 0);

	pinwrite(stp4_1a, 0);
	pinwrite(stp4_1b, 0);
	pinwrite(stp4_2a, 0);
	pinwrite(stp4_2b, 0);

}

void movex(float f)
{
	//printf("1\t%f\n",f);
	stepper(1, f, ttime);
}

void movey(float f)
{

	//printf("\t2\t%f\n",f);
	stepper(2, f, ttime);

}

void movee(float e)
{

extruder1=e+extruder1;
if((extruder1>=0.021)||(extruder1<=-0.021))
{stepper(4, extruder1, ttime);
extruder1=0;
}
//printf("/t/t/t/t/tetr1=%f\n",extruder1);

}

void multithread(float dist1, float dist2, float e, int time)
{

	int k = time;
	ttime = time;

	//dist[1]=dist1;
	//dist[2]=dist2;

	//printf("Motor 1 will rotate for %f mm and motor 2 for %f mm in %f sec\n",dist1,dist2,(float)k/1000);

	boost::thread th1(&movex, dist1);
	boost::thread th2(&movey, dist2);
	boost::thread th3(&movee, e);


	th1.join();
	th2.join();
	th3.join();

	clearall();
}

/*GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG*/
//void g23(int n, float x, float y, float X, float Y,float i,float j)
//{printf("Gcode: %d x=%f y=%f X=%f Y=%f I=%f J=%f\n",n,x,y,X,Y,i,j);}


void g23(int n, float x, float y, float X, float Y, float i, float j, float e)
{
	//int n;
	//float x=0, y=0; //current coordinates
	//float X=10, Y=10; //destination coordinates
	//float i=10, j=0; //distance from x,y to centre
	float a = 0, b = 0; //centre coordinates
	float r = 0; //radius
	float R = 0;
	float pi = 3.14159;
	float theta1 = 0;
	float theta2 = 0;
	float beta = 0;
	float alpha = 0;
	float z = 0;
	float steps = 0;
	float p = 10;//number of steps per mm
	int s = 0;
	float stepper_x;
	float stepper_y;
	int time;
	float abs_stepperx, abs_steppery;
	float xold = x, yold = y;

	a = x + i;
	b = y + j;

	r = sqrt(i*i + j*j);
	R = 4 * p * r;

	if (j != 0)
	{
		z = fabs(i / j);
		beta = atan(z);
	}
	else
	{
		beta = pi;
	}

	if (n == 2)
	{
		if (i >= 0 && j > 0)//1
		{
			alpha = 3 * pi / 2 - beta;
			if (X <= a && Y > y)
			{
				steps = (Y - y) * p;
			}
			else if (X >= a)
			{
				steps = ((r + j) + (2 * r - (Y - (b - r)))) * p*multi;
			}
			else if (X <= a && Y <= y)
			{
				steps = ((r + j) + 2 * r + (Y - (b - r))) * p*multi;
			}
		}

		else if (i >= 0 && j < 0)//2
		{
			alpha = pi / 2 + beta;
			if (X <= a && Y > y)
			{
				steps = (Y - y) * p*multi;
			}
			else if (X >= a)
			{
				steps = ((b + r - y) + (2 * r - (Y - (b - r)))) * p*multi;
			}
			else if (X <= a && Y <= y)
			{
				steps = ((b + r - y) + 2 * r + (Y - (b - r))) * p*multi;
			}
		}

		else if (i <= 0 && j > 0)//3
		{
			alpha = 3 * pi / 2 + beta;
			if (X >= a && Y < y)
			{
				steps = (y - Y) * p*multi;
			}
			else if (X <= a)
			{
				steps = ((y - (b - r)) + 2 * r - (Y - (b - r))) * p*multi;
			}
			else if (X >= a && Y >= y)
			{
				steps = ((y - (b - r)) + 2 * r + (b + r - Y)) * p*multi;
			}
		}

		else if (j == 0 && i > 0)//4
		{
			alpha = pi;
			if (X <= a && Y > y)
			{
				steps = (Y - y) * p*multi;
			}
			else if (X >= a)
			{
				steps = (r + 2 * r - (Y - (b - r))) * p*multi;
			}
			else if (X <= a && Y <= y)
			{
				steps = (3 * r + (Y - (b - r))) * p*multi;
			}
		}

		else if (j == 0 && i < 0)//5
		{
			alpha = 0;
			if (X >= a && Y < y)
			{
				steps = (y - Y) * p*multi;
			}
			else if (X <= a)
			{
				steps = (y - (b - r) + 2 * r - (Y - (b - r))) * p*multi;
			}
			else
			{
				steps = (3 * r + (b + r - Y)) * p*multi;
			}
		}
	}

	if (n == 3)
	{
		if (i >= 0 && j > 0)//1
		{
			alpha = 3 * pi / 2 - beta;
			if (X <= a && Y < y)
			{
				steps = (y - Y) * p*multi;
			}
			else if (X >= a)
			{
				steps = ((y - (b - r)) + (Y - (b - r))) * p*multi;
			}
			else if (X <= a && Y >= y)
			{
				steps = ((y - (b - r)) + 2 * r + (b + r - Y)) * p*multi;
			}
		}

		else if (i >= 0 && j < 0)//2
		{
			alpha = pi / 2 + beta;
			if (X <= a && Y < y)
			{
				steps = (y - Y) * p*multi;
			}
			else if (X >= a)
			{
				steps = ((y - (b - r)) + (Y - (b - r))) * p*multi;
			}
			else if (X <= a && Y >= y)
			{
				steps = ((y - (b - r)) + 2 * r + (b + r - Y)) * p*multi;
			}
		}

		else if (i <= 0 && j > 0)//3
		{
			alpha = 3 * pi / 2 + beta;
			if (X >= a && Y > y)
			{
				steps = (Y - y) * p*multi;
			}
			else if (X <= a)
			{
				steps = ((b + r - y) + (b + r - Y)) * p*multi;
			}
			else if (X >= a && Y <= y)
			{
				steps = ((b + r - y) + 2 * r + (Y - (b - r))) * p*multi;
			}
		}

		else if (j == 0 && i > 0)//4
		{
			alpha = pi;
			if (X <= a && Y < y)
			{
				steps = (y - Y) * p*multi;
			}
			else if (X >= a)
			{
				steps = (r + Y - (b - r)) * p*multi;
			}
			else if (X <= a && Y >= y)
			{
				steps = (3 * r + (b + r - Y)) * p*multi;
			}
		}

		else if (j == 0 && i < 0)//5
		{
			alpha = 0;
			if (X >= a && Y > y)
			{
				steps = (Y - y) * p*multi;
			}
			else if (X <= a)
			{
				steps = (r + b + r - Y) * p*multi;
			}
			else
			{
				steps = (3 * r + (Y - (b - r))) * p*multi;
			}
		}
	}
	e = e / steps;
	for (s = 0; s <= steps; s++)
	{
		//if(G2)
		theta1 = (alpha - ((2 * pi* s) / (R)));
		theta2 = (alpha + ((2 * pi*s) / (R)));
		if (n == 2)
		{
			stepper_x = a + r*cos(theta1);
			stepper_y = b + r*sin(theta1);
		}

		else if (n == 3)
		{
			stepper_x = a + r*cos(theta2);
			stepper_y = b + r*sin(theta2);

		}
		//

		stepper_x = stepper_x - xold; stepper_y = stepper_y - yold;
		xold = stepper_x + xold; yold = stepper_y + yold;


		abs_stepperx = fabs(stepper_x);
		abs_steppery = fabs(stepper_y);
		if (abs_stepperx>abs_steppery) { abs_stepperx = (abs_stepperx * 25*global_ms) - 0.5; time = ceil(abs_stepperx); }
		else { abs_steppery = (abs_steppery * 25*global_ms) - 0.5; time = ceil(abs_steppery); }


		multithread(stepper_x, stepper_y, e, time);

		//printf("dist_x==%f\tdist_y==%f\tin time==%d\n",stepper_x,stepper_y,time);
	}

}


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL*/
void plot_line(float X, float Y, float x, float y, float e)
{
	printf("#############################################################################\n##################################################################\n");
	printf("from X= %f to %f and Y= %f to %f with E= %e\n", x, X, y, Y,e);
printf("#############################################################################\n##################################################################\n");
	
	float stepper_x_old = x, stepper_y_old = y, stepper_x1, stepper_y1;
	float m;
	float n = 0;
	float c;
	float i = 0;
	float j = 0;
	int steps1 = 0;
	float x1, y1;
	int time;

	float steps = 0;
	int s = 0;
	float p = 1;//number of steps per mm
	float stepper_x = x;
	float stepper_y = y;

	m = (Y - y) / (X - x);
	i = X - x;
	j = Y - y;
	c = y - m*x;

	if (j != 0)
	{
		steps = fabs(j*multi*p);
	}
	else
	{
		steps = fabs(i*multi*p);
	}
	steps1 = ceil(steps - 0.5);
	e = e / (steps1 + 1);
	for (s = 0; s < steps1; s++)
	{
		if (j != 0)
		{
			if (j > 0)
			{
				n = 1;
			}
			else
			{
				n = -1;
			}
			if (i != 0)
			{
				stepper_y = stepper_y + (n * 1/(p*multi));
				stepper_x = (stepper_y - c) / m;
			}
			else
			{
				stepper_y = stepper_y + (n * 1/(p*multi));
				stepper_x = x;
			}
		}
		else if (j == 0)
		{
			if (i > 0)
			{
				n = 1;
			}
			else
			{
				n = -1;
			}
			stepper_x = stepper_x + (n * 1/(p*multi));
			stepper_y = y;
		}


		//abs

		stepper_x1 = stepper_x; stepper_y1 = stepper_y;
		stepper_x1 = stepper_x1 - stepper_x_old; stepper_y1 = stepper_y1 - stepper_y_old;
		stepper_x_old = stepper_x1 + stepper_x_old; stepper_y_old = stepper_y1 + stepper_y_old;

		x1 = abs(stepper_x1);
		y1 = abs(stepper_y1);
		if (x1>y1) { x1 = (x1 * 25*global_ms) - 0.5; time = ceil(x1); }
		else { y1 = (y1 * 25*global_ms) - 0.5; time = ceil(y1); }



		printf("### xold=%f Yold=%f    x=%f y=%f \te=%f steps:%d\n", stepper_x_old, stepper_y_old, stepper_x1, stepper_y1,e,steps1+1);
		multithread(stepper_x1, stepper_y1, e, time);

	}
	stepper_x = X;
	stepper_y = Y;

	stepper_x1 = stepper_x; stepper_y1 = stepper_y;
	stepper_x1 = stepper_x1 - stepper_x_old; stepper_y1 = stepper_y1 - stepper_y_old;
	stepper_x_old = stepper_x1 + stepper_x_old; stepper_y_old = stepper_y1 + stepper_y_old;

	x1 = abs(stepper_x1);
	y1 = abs(stepper_y1);
	if (x1>y1) { x1 = (x1 * 25*global_ms) - 0.5; time = ceil(x1); }
	else { y1 = (y1 * 25*global_ms) - 0.5; time = ceil(y1); }

	multithread(stepper_x1, stepper_y1, e, time);

	printf("##################enddd###########################################################\n##################################################################\n");

}

/*GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	float i, j;
	int k;

	pinexport(stp1_1a); //stepper1 input1a
	pinexport(stp1_1b); //stepper1 input1b
	pinexport(stp1_2a); //stepper1 input2a
	pinexport(stp1_2b); //stepper1 input1b

	pinexport(stp2_1a); //stepper2 input1a
	pinexport(stp2_1b); //stepper2 input1b
	pinexport(stp2_2a); //stepper2 input2a
	pinexport(stp2_2b); //stepper2 input1b

	pinexport(stp3_1a); //stepper3 input1a
	pinexport(stp3_1b); //stepper3 input1b
	pinexport(stp3_2a); //stepper3 input2a
	pinexport(stp3_2b); //stepper3 input1b

	pinexport(stp4_1a); //stepper3 input1a
	pinexport(stp4_1b); //stepper3 input1b
	pinexport(stp4_2a); //stepper3 input2a
	pinexport(stp4_2b); //stepper3 input1b


	string line;
	char linec[100];
	int lineno = 0;

	string str1, str2, str3, strI, strJ, strtmp, strE;

	char x_coord[10], tmprry;
	char y_coord[10];
	char z_coord[10];
	char i_coord[10];
	char j_coord[10];
	char e_coord[10];

	strcpy(x_coord, "X0");
	strcpy(y_coord, "Y0");
	strcpy(z_coord, "Z0");
	strcpy(i_coord, "I0");
	strcpy(j_coord, "J0");
	strcpy(e_coord, "E0");

	float circle_i = 0, circle_j = 0, extru = 0;
	float x = 0, y = 0, x1 = 0, y1 = 0, z = 0, z1 = 0, e = 0, e1 = 0;
	int a = 0, b = 0;
	int gcode = 999;
	char * pch;
	int time = 0;

	float xold = 0;
	float yold = 0;
	float zold = 0;
	float eold = 0;

	int is_z = 0;
	ifstream myfile("/var/www/html/Upload/sample.gcode");
	if (myfile.is_open())
	{
		while (getline(myfile, line)) //string: line // char linec
		{
			lineno++;
			strcpy(linec, line.c_str());



			pch = strtok(linec, " ");
			while (pch != NULL)
			{

				/*///////////////////////////////////////////////////////////////////////////////////////////*/

				if (pch[0] == 'G') {
					cout << pch << endl;

					if (strlen(pch) == 2)
					{
						if (pch[1] == '1')
							gcode = 1;
						else if (pch[1] == '0')
							gcode = 0;

						else if (pch[1] == '2')
							gcode = 2;
						else if (pch[1] == '3')
							gcode = 3;



					}
					else if (strlen(pch) == 3)
					{
						if ((pch[1] == '0') && (pch[2] == '1'))
							gcode = 1;
						else if ((pch[1] == '0') && (pch[2] == '0'))
							gcode = 0;
						else if ((pch[1] == '0') && (pch[2] == '2'))
							gcode = 2;
						else if ((pch[1] == '0') && (pch[2] == '3'))
							gcode = 3;

					}
				}
				if (pch[0] == 'X') { strcpy(x_coord, pch); }
				if (pch[0] == 'Y') { strcpy(y_coord, pch); }
				if (pch[0] == 'Z') { strcpy(z_coord, pch); is_z = 1; }
				else { z = zold; is_z = 0; }
				if (pch[0] == 'I') { strcpy(i_coord, pch); }
				if (pch[0] == 'J') { strcpy(j_coord, pch); }
				if (pch[0] == 'E') { strcpy(e_coord, pch); }




				pch = strtok(NULL, " ");
			}
			/*///////////////////////////////////////////////////////////////////////////////////////////*/
			str1 = x_coord; str1 = str1.substr(1); x = atof(str1.c_str());
			str2 = y_coord; str2 = str2.substr(1); y = atof(str2.c_str());
			str3 = z_coord; str3 = str3.substr(1); z = atof(str3.c_str());
			strI = i_coord; strI = strI.substr(1); circle_i = atof(strI.c_str());
			strJ = j_coord; strJ = strJ.substr(1); circle_j = atof(strJ.c_str());
			strE = e_coord; strE = strE.substr(1); e = atof(strE.c_str());
/*
multi=10;
x=x*inchtocm;
//xold=xold*inchtocm;
y=y*inchtocm;
//yold=yold*inchtocm;
z=z*inchtocm;
//zold=zold*inchtocm;
e=e*inchtocm;
//eold=eold*inchtocm;
*/
cout << "x=" << x << "xold=" << xold << endl;

			x = x - xold; y = y - yold; e = e - eold; 
			xold = x + xold; yold = y + yold; eold = e + eold;
			//eold = dist_after
			//e=0.displacement	
			if (is_z == 1)
			{

				z = z - zold;
				zold = z + zold;

			}
			printf("Gcode: %d X=%f Y=%f Z=%f I=%f J=%f E=%f", gcode, x, y, z, circle_i, circle_j, extruder1);

			//
			if (is_z == 1) { printf("Z= %f\n", z); }
			else printf("\n");

if (gcode == 20)
{
inch=1;
printf("\n\n\n\nunits set to inches\n\n\n\n\n");
}			


			/*########################################################*/
			if (gcode == 1 || gcode == 0)
			{



				if ((x<10) && (y<10))
				{
					x1 = abs(x);
					y1 = abs(y);
					if (x1>y1) { x1 = (x1 * 25*global_ms) - 0.5; a = ceil(x1); time = a; }
					else { y1 = (y1 * 25*global_ms) - 0.5; b = ceil(y1); time = b; }

					multithread(x, y, e, time);
				}
				else
				{
					plot_line(x + xold, y + yold, xold, yold, e);
				}
				if (is_z == 1) { z1 = abs(z); z1 = z1 * 25*global_ms - 0.5; time = ceil(z1); stepper(3, z, time); printf("------------------------------------------------\n"); is_z = 0; }


			}


			else if (gcode == 2 || gcode == 3)
			{
				printf("Gcode: %d x=%f y=%f X=%f Y=%f I=%f J=%f\n", gcode, x, y, xold, yold, circle_i, circle_j);


				g23(gcode, x + xold, y + yold, xold, yold, circle_i, circle_j, e);

				//g23(2,0,10,10,0,0,-10);

			}

			/*########################################################*/

		}
	}
	clearall();
	printf("#####################\n#####################\nJOB DONE\n#####################\n#####################\n");
	return 0;

}
