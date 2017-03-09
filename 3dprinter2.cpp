#define _GLIBCXX_USE_C99 1

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>



using namespace std;

/*global var*/
int stp1_1a=30;
int stp1_1b=60;
int stp1_2a=31;
int stp1_2b=50;

int stp2_1a=23;
int stp2_1b=26;
int stp2_2a=47;
int stp2_2b=46;

int steps1,steps2,steps3;
FILE *export_file = NULL;  
FILE *IO_direction = NULL;
float gbl_dist_x;
float gbl_dist_y;
int gbl_time_x;
int gbl_time_y;
int isset_x=0;
int isset_y=0;


/*///////////////////////////////////////////////////// PINWRITE // WRITES VALUE 1 0 TO PINS//////////////////////////////////////////////////////////////*/
void pinwrite(int a, int b)
{

///// pinwrite(pin,value)/////

char str[100];
char str1[]="low";
char str2[]="high";
/*
sprintf(str, "/sys/class/gpio/gpio%d/direction",a);
IO_direction = fopen (str, "w");
if(b==0){ fwrite (str1, 1, sizeof(str1), IO_direction);}
else if (b==1){ fwrite (str2, 1, sizeof(str2), IO_direction);}
fclose (IO_direction);

*/
}

/*/////////////////////////////////////////////////CLEAR ALL WRITES ZERO TO ALL STEPPER PINS////////////////////////////////////////////////////////////////////*/
void clearall(int num)
{

int a , b , c , d , stp;
if(num==1)
{
a=stp1_1a;
b=stp1_1b;
c=stp1_2a;
d=stp1_2b;

}

else if(num==2)
{
a=stp2_1a;
b=stp2_1b;
c=stp2_2a;
d=stp2_2b;

}
pinwrite(a,0);
pinwrite(b,0);
pinwrite(c,0);
pinwrite(d,0);

}
/*/////////////////////////INCSTEPPER////////////////////////ROTATES STEPPER BY 1 STEP////////////called by void stepper////////////////////////////////////////////////////////*/
void incstepper(int num)
{
int a , b , c , d , stp;

//motor definitions
if(num==1){a=stp1_1a;b=stp1_1b;c=stp1_2a;d=stp1_2b;stp=steps1;}
/*
else if(num==2){a=stp2_1a;b=stp2_1b;c=stp2_2a;d=stp2_2b;stp=steps2;}

//write
if(stp==0){pinwrite(a,1);pinwrite(b,0);pinwrite(c,1);pinwrite(d,0);stp=1;}

else if(stp==1){pinwrite(a,0);pinwrite(b,1);pinwrite(c,1);pinwrite(d,0);stp=2;}

else if( stp==2){pinwrite(a,0);pinwrite(b,1);pinwrite(c,0);pinwrite(d,1);stp=3;}

else if(stp==3){pinwrite(a,1);pinwrite(b,0);pinwrite(c,0);pinwrite(d,1);stp=0;}

//save step
if(num==1)steps1=stp;else if(num==2)steps2=stp;else if(num==3)steps3=stp;
*/

}
/*///////////////////////////////////////////////////////////MOVES STEPPER /////called by movex movey/////////////////////////////////////////////////////*/

void stepper(int num, float dist, int time) /*num from 1 to 3; dist in mm; time in usec */
{


int stps;
float t;

float rstps=((dist*25)-0.5);

if(num==1)
steps1=0;
else if(num==2)
steps2=0;
else if(num=3) //line 84
steps3=0;

stps=ceil(rstps);
if(stps!=0)
{
t=(float)time/(float)stps;
}
else (t=0);

int i;
for( i=1;i<stps;i++)
{
incstepper(num);
usleep(t);
}

printf("Stepper %d moved for %f in time %d\n",num,dist,time);
clearall(num);


}

/*///////////////////////////////////////////////////////////EXPORTS PINS AT START//////////////////////////////////////////////////////////*/

void pinexport(int a)
{//exports pin number a
char str[100] ;       //value to pass to export file
sprintf(str,"%d",a);
export_file = fopen ("/sys/class/gpio/export", "w");
fwrite (str, 1, sizeof(str), export_file);
fclose (export_file);
printf("Pin %d exported succesfully\n",a);
}
/*/////////////////////////////////////////////////////////////MOVE X AND Y AT THE SAME TIME////////////////////////////////////////////////////////*/

void *movex(void *t) {
if(isset_x=1)
{
isset_x=0;

stepper(1,gbl_dist_x,gbl_time_x);
//printf("Movex done\n");
 }pthread_exit(NULL);
}
/*///////////////////////////////////////////////////////////////////////*/
void *movey(void *t) {
if(isset_y=1)
{
isset_y=0;

stepper(2,gbl_dist_y,gbl_time_y);
//printf("Movey done\n");
 }
pthread_exit(NULL);
}
/*////////////////////////////////////////////////////////  MULTITHREAD FUNCTION   /////////////////////////////////////////////////////////////*/

int multithread (float x, int timex, float y, int timey) {
gbl_dist_x=x;
gbl_dist_y=y;
gbl_time_x=timex;
gbl_time_y=timey;
isset_x=1;
isset_y=1;

 

  int rc;
   int i;
	
   pthread_t threads[2];
   pthread_attr_t attr;
   void *status;

   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   rc = pthread_create(&threads[0], &attr, movex, (void *)i );
   rc = pthread_create(&threads[1], &attr, movey, (void *)i );
		
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   

   // free attribute and wait for the other threads
   pthread_attr_destroy(&attr);
	
       rc = pthread_join(threads[0], &status);
       rc = pthread_join(threads[1], &status);
		
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      
		
     // printf("Main: completed thread id \n");
       }
  //printf("Main: completed thread id \n");  
}
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/






int main () {

pinexport(stp1_1a); //stepper1 input1a
pinexport(stp1_1b); //stepper1 input1b
pinexport(stp1_2a); //stepper1 input2a
pinexport(stp1_2b); //stepper1 input1b

pinexport(stp2_1a); //stepper2 input1a
pinexport(stp2_1b); //stepper2 input1b
pinexport(stp2_2a); //stepper2 input2a
pinexport(stp2_2b); //stepper2 input1b



  string line;
char linec[100];
int i,j,k;

string temp,temp1;
int gcode;
int lineno=0;
char x_coord[10];
double x_c=1;
char y_coord[10];
float y_c=1;
char * pch;
char * dup;
const char * temp2;
std::string::size_type sz;     // alias of size_t
  ifstream myfile ("sample.gcode");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) ) //string: line // char linec
    {lineno++;
	strcpy(linec,line.c_str());
    								pch = strtok (linec," ");
  								  while (pch != NULL)
  								{
if(pch[0]=='G')
{
/*/////////////////////////////////////////////*/

	if ((pch[1]=='0')&&(pch[2]=='1'))
		{
		gcode=1;
		}
	

/*/////////////////////////////////////////////*/
}
if(pch[0]=='X')
{strcpy(x_coord,pch);}
if(pch[0]=='Y')
{strcpy(y_coord,pch);}
 								    pch = strtok (NULL, " ");
    								}
//conversions
temp=x_coord;
temp=temp.substr(1);
x_c=atof(temp.c_str());
strcpy(x_coord,temp.c_str());
temp=y_coord;
temp=temp.substr(1);
y_c=atof(temp.c_str());
strcpy(y_coord,temp.c_str());
//printf("%f %f\n\n",x_c,y_c);
/*****************************************************************************************************************************x_c and y_c are respective floats**/

multithread(x_c,100,y_c,100);
x_c=0;
y_c=0;
printf("Successful\n");

clearall(1);
clearall(2);
 // pthread_exit(NULL);
/*****************************************************************************************************************************/
    }
    myfile.close();
  }
  else 
cout << "Unable to open file"<< endl; 
  pthread_exit(NULL);
  return 0;
}