#include <math.h>
#include <iostream>
#include <random>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include "funciones/rvgs.h"
#include "funciones/rvgs.c"

#define _USE_MATH_DEFINES
using namespace std;

// Función de prueba
double function(double x){
	double result = exp(-(x*x))*(2+sin(x*5)+sin(x*2));
	return result;
}


// Función pedida en el punto 2.2.2
double funcion2(double x){
	double result = exp(-pow(x,3))*(8+cos(3*x)+sin(x)-2*M_PI);
}


// Función generadora de siguiente valor (punto actual, desviación)
double MHstep(double xo, double ds, int flag){
	// semilla random
	std::default_random_engine generator;
	// generador random de distribución uniforme (cotas)
  	std::uniform_real_distribution<double> distribution(0.0,1.0);

  	// valor siguiente
  	double x1;
  	// se genera un número aleatorio en distribución normal (media,desviación)
	double xp=Normal(xo,ds);
	// probabilidad de aceptación (alpha)
  double accprob;
  if (flag==0){
      accprob=function(xp)/function(xo);
  }else{
      accprob= funcion2(xp)/funcion2(xo);
  }
	
	// alpha = min(1,probabilidad de aceptación)
	if(accprob>1){
		accprob=1;
	}
	// genera número en distribución uniforme (entre 0 y 1)
	double u = distribution(generator);
	// Se acepta si número generado es menor o igual a probabilidad de aceptación
	if(u <= accprob){
		// si se acepta el nuevo punto es candidato
		x1 = xp; 
	}else{
		// si no se acepta el candidato es el mismo punto ingresado
		x1 = xo;
	}
	return x1;
}

void muestreo(int burnin, int samples, int lag, double x, int sd, int flag){
	  // iteraciones previas (burn in)
  for(int i=1;i<=burnin;i=i+1){ 
  		x = MHstep(x,sd,flag);
  }


  // ciclo de muestreo
  for(int i=1;i<=samples;i=i+1){

  		// ciclo de lag entre muestreo 
  		for (int j = 1; j <=lag; ++j)
  		{
  			// función para obtener siguiente valor
  			x=MHstep(x,sd,flag);
  		}

  		//muestra por pantalla valores obtenidos
  		cout << x << "\n";

      // Escritura en archivo
      fstream fichero;
      fichero.open ( "resultados" , ios::app);
      fichero << x << "\n";
      fichero.close();
  }

}



int main(int argc, char **argv){
 
 ///Parámetros
  int burnin = 0; // burn-in iterations -> iteraciones previas para evitar mal punto de partida
  int lag = 1; // lag entre muestreo -> para distribuciones con baja tasa de aceptación
  int samples = 1000; // numero de muestras
  int sd; // desviación estándar
  double x = -1; // punto de partida

  //Variables getopt
  int c,sflag=0,lflag=0,bflag=0,fflag=0;
  int index;

    while ((c = getopt (argc, argv, "slbf")) != -1)
    switch (c)
      {
      case 's':
        sflag = 1;
        break;
      case 'l':
        lflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'f':
        fflag = 1;
        break;
      case '?':
        if (isprint (optopt))
          fprintf (stderr, "Opción incorrecta`-%c'.\n", optopt);
        else
          fprintf (stderr,"Opción desconocida `\\x%x'.\n",optopt);
        return 1;
          default:
            abort ();
      }


  for (index = optind; index < argc; index++)
    printf ("Argumento inválido %s\n", argv[index]);

  ///// MENU //////////
  cout << "Ingrese desviación estándar: \n";
  cin >> sd;
  while(!cin || sd<0){

    cin.clear(); 
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    cout << "Desviación debe ser un número mayor o igual a 0\nPor favor, introduzca un número válido: \n";
    cin >> sd;
  }

 if(sflag==1){
    cout << "Ingrese cantidad de muestras: \n";
    cin >> samples;
    while(!cin || samples<=0){

      cin.clear(); 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      cout << "Cantidad de muestras debe ser un número mayor a 0\nPor favor, introduzca un número válido: \n";
      cin >> samples;
    }
 }

  if(lflag==1){
    cout << "Ingrese cantidad de lag: \n";
    cin >> lag;
    while(!cin || lag<=0){

      cin.clear(); 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      cout << "lag debe ser un número mayor a 0\nPor favor, introduzca un número válido: \n";
      cin >> lag;
    }
 }

   if(bflag==1){
    cout << "Ingrese cantidad de lag: \n";
    cin >> burnin;
    while(!cin || burnin<=0){

      cin.clear(); 
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
      cout << "burn-in debe ser un número mayor a 0\nPor favor, introduzca un número válido: \n";
      cin >> burnin;
    }
 }


fstream fichero;
fichero.open ( "resultados" , ios::out | ios::trunc);
fichero << "";
fichero.close();

//Realiza muestreo
muestreo(burnin,samples,lag,x,sd,fflag); 

//Avisa sobre la función utilizada
  if(fflag==0){
    cout << "\nUtiliza función 1\n";
 }else{
    cout << "\nUtiliza función 2\n";
 }
  
  return 0;
}