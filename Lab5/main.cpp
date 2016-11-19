#include <cstdlib> /*Librería básica c++*/
#include <cmath>   /*Librería matemática c++*/
#include <cstdio>  /*Librería de entrada y salida estándar c++*/
#include <ctime>   /*Librería de funciones asociadas al tiempo en c++*/

/*Declaración del nacespace para trabajar con directorios o librerías personales*/
using namespace std; 

double funcionA(double x){ /*Función para la parte 2.1.1 dx*/
    double y;
    y = ((3*x*x)+(2*x)-1)/(4*x + 7);
    return y;
}

long double funcionB(long double x[]){ /*Función para la parte 2.1.1 dx dy*/
    long double y;
    y = 0.0;
    y = (4*x[0]*x[0]*x[0]) + (20*x[0]*x[1]) - (((5*x[0]*x[0])-(4*x[0]))/((2*x[0])-1));   
    return y;
}

long double funcionC(long double x[]){ /*Función para la parte 2.1.1 dx dy dz*/
    long double pi = 3.1415926; 
    long double y;
    y = 0.0;
    y = (5*x[0]*x[0]) - (4*x[0]) + (2*pi);   
    return y;
}

/*Función que obtiene el resultado de aplicar el método Montecarlo para una integral uni-variada*/
double monteCarloUniVar(double(*f)(double), double LimInf, double LimSup, int nIter){
    double resultado;
    double x;
    double random; 
    double fx; 
    /*Se llama la función para obtener números aleatorios distintos */
    srand(time(NULL)); 
    
    /*Se inicializan los variables*/
    fx  = 0.0;
    /*Se realizan las iteraciones*/
    for (int i = 1; i <= nIter; i=i+1){
        /*Obtengo el número aleatorio*/
        random = (double)rand()/(RAND_MAX);
        /*Obtengo el número en el intervalo de la integral*/
        x = LimInf + (LimSup-LimInf)*random; 
        /*Evalúo función*/
        fx = fx + f(x); 
    }
    /*Se calcula resultado de mátodo Montecarlo*/
    resultado = fx*(LimSup-LimInf)/nIter;     
    return resultado;
}

/*Función que obtiene el resultado de aplicar el método Montecarlo para una integral bi-variada*/
long double monteCarloBiVar(long double(*fn)(long double[]),long double LimInf[],long double LimSup[], long int nGrado, long int nIter){
    long double resultado;
    long double x[nGrado];
    long double p;
    long double random;
    /*Se llama la función para obtener números aleatorios distintos */
    srand(time(NULL)); 
    /*Se inicializan los variables*/
    resultado = 0.0;
    p = 1.0;
    /*Se obtiene el parametro de la integral*/
    for (int j = 0; j < nGrado; j = j+1){
        p = p*(LimSup[j]-LimInf[j]);
    } 

    /*Se realizan las iteraciones*/
    for (int i = 1; i <= nIter; i = i+1){
        /*Se realizan para dava varaible x e y*/
        for (int j = 0; j < nGrado; j = j+1){
            /*Obtengo el número aleatorio*/
            random = (long double)rand()/(RAND_MAX);
            /*Obtengo el número en el intervalo de la integral*/
            x[j] = LimInf[j] + (LimSup[j]-LimInf[j])*random;
        }
        /*Se calcula resultado de la iteración*/
        resultado = resultado + fn(x);
    }
    /*Se calcula resultado de mátodo Montecarlo*/
    resultado= resultado*p/nIter;
    return resultado;
}

/*Función que obtiene el resultado de aplicar el método Montecarlo para una integral Tri-variada*/
long double monteCarloTriVar(long double(*fn)(long double[]),long double LimInf[],long double LimSup[],long int nGrado, long int nIter){
    long double resultado;
    long double x[nGrado];
    long double p;
    long double random;
    /*Se llama la función para obtener números aleatorios distintos */
    srand(time(NULL));
    /*Se inicializan los variables*/
    resultado = 0.0;
    p = 1.0;
    /*Se obtiene el parametro de la integral*/
    for (int j = 0; j < nGrado; j = j+1){
         p = p*(LimSup[j]-LimInf[j]);
    } 

    /*Se realizan las iteraciones*/
    for (int i = 1; i <= nIter; i = i+1){
        /*Se realizan para dava varaible x, y, z*/
        for (int j = 0; j < nGrado; j = j+1){
            /*Obtengo el número aleatorio*/
            random = (long double)rand()/(RAND_MAX);
            /*Obtengo el número en el intervalo de la integral*/
            x[j] = LimInf[j] + (LimSup[j]-LimInf[j])*random;
        }
        /*Se calcula resultado de la iteración*/
        resultado = resultado + fn(x);
    }
    /*Se calcula resultado de mátodo Montecarlo*/
    resultado = resultado*p/nIter;
    return resultado;
}

/*Función que controla el proceso de obtener pi por método Montecarlo*/
void getPi(){
    int nIter = 0;
    double x,y,z,pi;
    int contador = 0;
    /*Se solicita ingresar el número de iteraciones*/
    printf("\nIngrese el número de iteraciones para estimar pi: ");
    scanf("%d",&nIter);
    /*Se llama la función para obtener números aleatorios distintos */
    srand(time(NULL));
    
    /*Se realizan las iteraciones*/
    for(int i = 0; i < nIter; i++){
        /*Obtengo aleatorio x*/
        x = (double)rand()/RAND_MAX;
        /*Obtengo aleatorio y*/
        y = (double)rand()/RAND_MAX; 
        /*Se calcula z, donde x^2 + y^2 <= 1*/
        z = x*x + y*y; 
        /*Si se cumple condición dentro de área circunferencia*/
        if(z <= 1){
            /*Aumento contador de veces dentro del área*/
            contador = contador + 1;
        }
    } 
    /*Obtengo pi, equivale a (Número de puntos dentro/Nímero puntos en total)*4*/
    pi = ((double) contador/nIter)*4; 
    printf("\nPara %d iteraciones, se estima pi con valor %g",nIter,pi);
}

/*Función que controla el proceso de obtener integral 1 (2.1.1) por método Montecarlo*/
void getF1(){
    /*Se declaran/inicializan los variables*/
    int nIter = 0;
    double LimInf, LimSup, MonteCarlo;
    LimInf = 0.0;              
    LimSup = 10.0;             
    
    /*Se solicita ingresar el número de iteraciones*/
    printf("\nIngrese el numero de iteraciones para estimar f1: ");
    scanf("%d",&nIter);

    /*Se calula la estimación de la integral mediante método Montecarlo*/
    MonteCarlo = monteCarloUniVar(funcionA, LimInf, LimSup, nIter);
    printf("\nPara %d de iteraciones, se estimar f1 con valor %g",nIter, MonteCarlo);
}

/*Función que controla el proceso de obtener integral 2 (2.1.1) por método Montecarlo*/
void getF2(){
    /*Se declaran/inicializan los variables*/
    long double LimInf[2] = {2.0, 0.0}; 
    long double LimSup[2] = {25.0, 17.0}; 
    long double MonteCarlo;
    long int nGrado = 2;
    long int nIter;
    
    /*Se solicita ingresar el número de iteraciones*/
    printf("\nIngrese el numero de iteraciones para estimar f2: ");
    scanf("%ld",&nIter);
    
    /*Se calula la estimación de la integral mediante método Montecarlo*/
    MonteCarlo = monteCarloBiVar(funcionB, LimInf, LimSup, nGrado, nIter);
    printf("\nPara %ld de iteraciones, se estimar f2 con valor %Lf",nIter,MonteCarlo);
}

/*Función que controla el proceso de obtener integral 3 (2.1.1) por método Montecarlo*/
void getF3(){
    /*Se declaran/inicializan los variables*/
    long int nIter = 0;
    long double LimInf[3] = {0.0, 0.0, 0.0}; 
    long double LimSup[3] = {5.0, 10.0, 2.0}; 
    long double MonteCarlo;
    long int nGrado = 3;
    
    /*Se solicita ingresar el número de iteraciones*/
    printf("\nIngrese el numero de iteraciones para estimar f3: ");
    scanf("%ld",&nIter);
    
    /*Se calula la estimación de la integral mediante método Montecarlo*/
    MonteCarlo = monteCarloTriVar(funcionC, LimInf, LimSup, nGrado, nIter);
    printf("\nPara %ld de iteraciones, se estimar f3 con valor %Lf",nIter,MonteCarlo);
}

/*Función que obtiene el resultado de aplicar el método Montecarlo para análisis de problema (2.1.2)*/
void monteCarlosAnalisis(long double resultado[]){
    long double nLicencia;
    long double random;
    
    /*Obtengo el número aleatorio*/
    random = (long double)rand()/(RAND_MAX);
    resultado[0] = random;
    
    /*Se evalua el rango de la distribución de probabilidad encontrada por expertos*/
    /*Luego se asigna el valor correspondiente*/
    if(random < 0.3){
        nLicencia = 100;
    }else{
        if(random < 0.5){
           nLicencia = 150;
        }else{
            if(random < 0.80){
                nLicencia = 200;
            }else{
                if (random < 0.95){
                    nLicencia = 250;
                }else{
                    if(random < 1){
                        nLicencia = 300;
                    }
                }
            }
        }
    }
    /*Se almacen el resultado*/
    resultado[1] = nLicencia;
}

void getRecomendacion(){
    /*Se declaran/inicializan los variables*/
    long double resultadoIter[2];
    long int nIter = 1000;
    long double resultadoGeneral[nIter][2];
    int frec100 = 0, frec150 = 0, frec200 = 0, frec250 = 0, frec300 = 0;
    /*Se llama la función para obtener números aleatorios distintos */
    srand(time(NULL));
    /*Se realizan las iteraciones*/
    for(int i = 0; i<nIter; i++){
        /*Se calcula Montecarlos*/
        monteCarlosAnalisis(resultadoIter);
        /*Se guarga infromacion de iteracion*/
        resultadoGeneral[i][0] = resultadoIter[0];
        resultadoGeneral[i][1] = resultadoIter[1];
        /*Se actualiza la frecuencia*/
        if(resultadoGeneral[i][1] == 100) frec100++;
        if(resultadoGeneral[i][1] == 150) frec150++;
        if(resultadoGeneral[i][1] == 200) frec200++;
        if(resultadoGeneral[i][1] == 250) frec250++;
        if(resultadoGeneral[i][1] == 300) frec300++;
    }
    
    /*Se calcula el promedio de la distribución del caso*/
    double promedio = (double)frec100*100 + (double)frec150*150 + (double)frec200*200 + (double)frec250*250 + (double)frec300*300;
    promedio = promedio/nIter;
    
    /*Se calcula la varianza de la distribución del caso*/
    double varianza = ((double)frec100*(100-promedio)*(100-promedio))+((double)frec150*(150-promedio)*(150-promedio))+((double)frec200*(200-promedio)*(200-promedio))+((double)frec250*(250-promedio)*(250-promedio))+((double)frec300*(300-promedio)*(300-promedio));
    varianza = varianza/nIter;
    
    /*Se calcula la desviación estandar de la distribución del caso*/
    double desviacion = sqrt(varianza);
    
    printf("\nLa cantidad que recomiendo comprar es : %d \n",(int)promedio);
}

int main(int argc, char** argv) {

    getPi();
   
    getF1();
   
    getF2();
    
    getF3();
    
    getRecomendacion();
    
   return 0;
}

