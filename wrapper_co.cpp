//this code is currently broken since it doesn't use rho,temp to solve for u.


#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

const double pi = 3.1415926;
const double onethird = 1.0 / 3.0;
const double twothirds = 2.0 / 3.0;
const double fourthirds = 4.0 / 3.0;

#define Fortran(x) x

#define Fortran2(x) x##_

extern "C" {
	void Fortran(teos)();
	void Fortran2(init_helm_table)(); 
	
	void Fortran2(get_helm_table)(double *f,double *fd,double *ft,double *fdd,
								  double *ftt,double *fdt,double *fddt,
								  double *fdtt,double *fddtt,double *dpdf,
								  double *dpdfd,double *dpdft,double *dpdfdt,
								  double *ef,double *efd,double *eft,double *efdt,
								  double *xf,double *xfd,double *xft,double *xfdt);
	
	void Fortran2(wrapper_invert_helm_ed)(int *npart, double *density,
										  double *energy, double *abar,
										  double *zbar, double *temperature, 
										  double *pressure, double *small_temp, double *vsound);
	
	void Fortran2(wrapper_helmeos)(int *npart, double *den_row, 
								   double *etot_row, double *abar_row, 
								   double *zbar_row, double *temperature,
								   double *pressure);
	
	void Fortran2(set_helm_table)(double *f, double *fd, double *ft, double *fdd,
								  double *ftt, double *fdt, double *fddt,
								  double *fdtt, double *fddtt, double *dpdf,
								  double *dpdfd, double *dpdft, double *dpdfdt,
								  double *ef, double *efd, double *eft, 
								  double *efdt, double *xf, double *xfd,
								  double *xft, double *xfdt);
	
	void Fortran2(azbar)(double *xmass, double *aion, double *zion, int *ionmax, 
						 double *ymass, double *abar, double *zbar);
}



int main()
{
	int nion = 13;
	int npart = 1;
	double abund[13]	={ 0,0.5,0.5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}; //50% C-O
	double zarray[13]	={ 2,  6,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28};
	double aarray[13]	={ 4, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56};
	double molarabund[13];
	
	char* isotopes[13];
	
	isotopes[0] = "he4 ";
	isotopes[1] = "c12 ";
	isotopes[2] = "o16 ";
	isotopes[3] = "ne20";
	isotopes[4] = "mg24";
	isotopes[5] = "si28";
	isotopes[6] = "s32 ";
	isotopes[7] = "ar36";
	isotopes[8] = "ca40";
	isotopes[9] = "ti44";
	isotopes[10] = "cr48";
	isotopes[11] = "fe52";
	isotopes[12] = "ni56";
	
	double density, energy, abar, zbar, temperature, pressure;
	int i, j, k;
	
	cout << "density? ";
	cin >> density;
	cout << "temperature? ";
	cin >> temperature;
	
	Fortran2(azbar)(abund, aarray, zarray, &nion, molarabund, &abar, &zbar );
	
	Fortran2(wrapper_helmeos)(&npart, &density, &energy, &abar, &zbar, &temperature, &pressure); 
	
	printf("density\t\t= %2.3e g/cc\n",density);
	printf("energy\t\t= %2.3e erg/g\n",energy);
	printf("temperature\t= %2.3e K\n",temperature);
	printf("pressure\t= %2.3e g/cm/s^2\n",pressure);
	printf("abar\t\t= %2.3e\n",abar);
	printf("zbar\t\t= %2.3e\n",zbar);
	
	return 0;
}