#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const double pi = 3.1415926;
const double onethird = 1.0 / 3.0;
const double twothirds = 2.0 / 3.0;
const double fourthirds = 4.0 / 3.0;

char csvfile[80];

#define Fortran(x) x

#define Fortran2(x) x##_

extern "C" {
	void Fortran2(azbar)(double *xmass, double *aion, double *zion, int *ionmax, 
						 double *ymass, double *abar, double *zbar);
	
	
	void Fortran2(burner)(double *dt, double *temperature, double *density, 
						  double *energy, double *bund, double *temperatureout, double *energyout, double *abundout); 
	
	void Fortran2(init_burner)();
}

double zarray[13]={ 2,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28};
double aarray[13]={ 4, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56};
double abund[13],abund2[13],molarabund[13],abar,zbar;
double energy, density, temperature, tempout, eout, denergy, dt;

double dummy1,dummy2,dummy3,dummy4,dummy5,dummy6,dummy7,dummy8,dummy9,dummy10,dummy11,dummy12,dummy13;

int i,j;

int main()
{
	char* isotopes[13];
	
	printf("energy density temperature dt\n");
	scanf("%lf %lf %lf %lf", &energy, &density, &temperature, &dt);	
	
	isotopes[0] = "he4";
	isotopes[1] = "c12";
	isotopes[2] = "o16";
	isotopes[3] = "ne20";
	isotopes[4] = "mg24";
	isotopes[5] = "si28";
	isotopes[6] = "s32";
	isotopes[7] = "ar36";
	isotopes[8] = "ca40";
	isotopes[9] = "ti44";
	isotopes[10] = "cr48";
	isotopes[11] = "fe52";
	isotopes[12] = "ni56";
	
 	for (i=0; i<13; i++){
		printf("%s ",isotopes[i]);
	}
	printf("\n");
	scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &dummy1, &dummy2, &dummy3, &dummy4, 
		  &dummy5, &dummy6, &dummy7, &dummy8, &dummy9, &dummy10, &dummy11, &dummy12, &dummy13);
	
	abund[0]=dummy1;
	abund[1]=dummy2;
	abund[2]=dummy3;
	abund[3]=dummy4;
	abund[4]=dummy5;
	abund[5]=dummy6;
	abund[6]=dummy7;
	abund[7]=dummy8;
	abund[8]=dummy9;
	abund[9]=dummy10;
	abund[10]=dummy11;
	abund[11]=dummy12;
	abund[12]=dummy13;
		
	Fortran2(init_burner)();
	
	Fortran2(burner)(&dt, &temperature,  
					 &density, &energy, abund, &tempout, &eout, 
					 abund2);
	
	
	printf("eout: %3.8e\n",eout);
	printf("sdot: %3.8e\n\n",(eout-energy)/dt);
	for (i=0; i<13; i++){
		printf("%s = %3.8e\n",isotopes[i],abund2[i]);
	}
	
	
	return 0;
}