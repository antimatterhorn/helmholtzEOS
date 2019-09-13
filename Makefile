pp=g++ -g 
fort=gfortran

co : public_helm.o wrapper_co.cpp
	$(pp) -o helmco wrapper_co.cpp public_helm.o -lgfortran

sdot : public_helm.o chop_aprox13.o wrapper_sdot.cpp
	$(pp) -o sdot wrapper_sdot.cpp public_helm.o chop_aprox13.o -lgfortran

sdot2 : public_helm.o chop_aprox13.o wrapper_sdot2.cpp
	$(pp) -o sdot2 wrapper_sdot2.cpp public_helm.o chop_aprox13.o -lgfortran

helm : public_helm.o wrapper_helm.cpp
	$(pp) -o helm wrapper_helm.cpp public_helm.o -lgfortran

find : public_helm.o wrapper_find.cpp
	$(pp) -o find wrapper_find.cpp public_helm.o -lgfortran

invert : invert_helm.o public_helm.o wrapper_invert.cpp 
	$(pp) -o invert wrapper_invert.cpp invert_helm.o public_helm.o -lgfortran

public_helm.o : public_helm.f90 *.dek
	$(fort) -c public_helm.f90

chop_aprox13.o : chop_aprox13.f90 *.dek
	$(fort) -c chop_aprox13.f90

invert_helm.o : invert_helm.f90 *.dek
	$(fort) -c invert_helm.f90

clean :
	rm $(WRAPPER) *.o