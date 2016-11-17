#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

/* Variables para generar los numeros aleatoreos */
#define SEED 35791246

using namespace std;

double f1(double x){
    double y;
    y = ((3*x*x)+(2*x)-1)/(4*x + 7);
    return y;
}

double monte_carlo_univar(double(*f)(double), double& errest, double a, double b, int n){
    double resultado, x, random, f2x, fx;
    /*f2x y fx son utilizadas para estimar el error*/
    /*Se setea el seed para obtener el numero aleatorio*/
    srand(SEED);               
    
    /*Se inicializan los valores de las funciones*/
    fx  = 0.0;
    f2x = 0.0;

    for (int i = 1; i <= n; i=i+1){
        random = (double)rand()/(RAND_MAX); /*Obtengo el número aleatorio*/
        x = a + (b-a)*random; /*Obtengo el numero en el intervalo*/
        fx = fx + f(x); /*Evaluo funcion*/
        f2x= f2x+ f(x)*f(x);
    }
    resultado = fx*(b-a)/n;
    /* calculo del error */
    fx = fx/n;
    f2x = f2x/n;
    errest = (b-a)*sqrt((f2x - fx*fx)/n);
    return resultado;
}

long double f2(long double x[],long int n){
    long double y;
    y = 0.0;
    y = (4*x[0]*x[0]*x[0]) + (20*x[0]*x[1]) - (((5*x[0]*x[0])-(4*x[0]))/((2*x[0])-1));   
    return y;
}

long double monte_carlo_bivar(long double(*fn)(long double[],long int),long double a[],long double b[], long int n, long int m){
    long double r, x[n], p;
    long int i, j;

    srand(SEED); 

    r = 0.0;
    p = 1.0;

    for (j = 0; j < n; j = j+1)
      {
         p = p*(b[j]-a[j]);
      } 

    long double random;

    for (i = 1; i <= m; i=i+1)
    {
        for (j = 0; j < n; j = j+1)
        {   
            random = (long double)rand()/(RAND_MAX);
            x[j] = a[j] + (b[j]-a[j])*random;
        }         
        r = r + fn(x,n);
    }
    r = r*p/m;
    return r;
}

long double f3(long double x[],long int n){
    long double pi = 3.1415926; 
    long double y;
    y = 0.0;
    y = (5*x[0]*x[0]) - (4*x[0]) + (2*pi);   
    return y;
}

long double monte_carlo_trivar(long double(*fn)(long double[],long int),long double a[],long double b[],long int n, long int m){
    long double r, x[n], p;
    long int i, j;

    srand(time(NULL));

    r = 0.0;
    p = 1.0;

    for (j = 0; j < n; j = j+1)
      {
         p = p*(b[j]-a[j]);
      } 

    long double random;

    for (i = 1; i <= m; i=i+1)
    {
        for (j = 0; j < n; j = j+1)
        {   
            random = (long double)rand()/(RAND_MAX);
            x[j] = a[j] + (b[j]-a[j])*random;
        }         
        r = r + fn(x,n);
    }
    r = r*p/m;
    return r;
}

void getPi(){
    int numero_iteraciones = 0;
    double x,y,z,pi;
    int i, contador = 0;
    printf("\nIngrese el numero de iteraciones para estimar pi: ");
    scanf("%d",&numero_iteraciones);
    /*Inicializando numero aleatorios*/
    srand(SEED);
    for(i = 0; i < numero_iteraciones; i++){
        x = (double)rand()/RAND_MAX; /*Obtengo aleatorio x*/
        y = (double)rand()/RAND_MAX; /*Obtengo aleatorio y*/
        z = x*x + y*y; /*Donde x^2 + y^2 <= 1*/
        if(z <= 1){ /*Si se cumpre condicion dentro de area circunferencia*/
            contador = contador + 1;
        }
    } 
    pi = ((double) contador/numero_iteraciones)*4; /*(Numero de puntos dentro/Numero puntos en total)*4*/
    printf("\nPara %d de iteraciones, se estima pi con valor %g",numero_iteraciones,pi);
}

void getF1(){
    int numero_iteraciones = 0;
    double a,b,mc,errest;
    int i;
   
    a = 0.0;              // left endpoint
    b = 10.0;               // right endpoint

    printf("\nIngrese el numero de iteraciones para estimar f1: ");
    scanf("%d",&numero_iteraciones);
    /*Inicializando numero aleatorios*/
    
    mc = monte_carlo_univar(f1, errest, a, b, numero_iteraciones);

    printf("\nPara %d de iteraciones, se estimar f1 con valor %g",numero_iteraciones,mc);
}

void getF2(){
    long int numero_iteraciones = 0;
    printf("\nIngrese el numero de iteraciones para estimar f2: ");
    scanf("%d",&numero_iteraciones);
    long double a[2] = {2.0, 0.0}; 
    long double b[2] = {25.0, 17.0}; 
    long double result;
    long int n = 2;
    result = monte_carlo_bivar(f2, a, b, n, numero_iteraciones);
    printf("\nPara %ld de iteraciones, se estimar f2 con valor %Lf",numero_iteraciones,result);
}

void getF3(){
    long int numero_iteraciones = 0;
    printf("\nIngrese el numero de iteraciones para estimar f3: ");
    scanf("%d",&numero_iteraciones);
    long double a[3] = {0.0, 0.0, 0.0}; 
    long double b[3] = {5.0, 10.0, 2.0}; 
    long double result;
    long int n = 3;
    result = monte_carlo_bivar(f3, a, b, n, numero_iteraciones);
    printf("\nPara %ld de iteraciones, se estimar f3 con valor %Lf",numero_iteraciones,result);
}

int main(int argc, char** argv) {

   //getPi();
   
   //getF1();
   
   //getF2();
    
   getF3();
    
   return 0;
}

