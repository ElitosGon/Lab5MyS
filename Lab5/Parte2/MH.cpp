#include <math.h>
#include <iostream>
#include <random>
#include "rvgs.h"
#include "rvgs.c"

#define _USE_MATH_DEFINES
using namespace std;

double function(double x){
	double result = exp(-(x*x))*(2+sin(x*5)+sin(x*2));
	return result;
}

double funcion2(double x){
	double result = exp(-pow(x,3))*(8+cos(3*x)+sin(x)-2*M_PI);
}

double MHstep(double xo, double sig){
	std::default_random_engine generator;
  	std::uniform_real_distribution<double> distribution(0.0,1.0);

  	double x1;
	double xp=Normal(xo,sig);
	double accprob= funcion2(xp)/funcion2(xo);
	if(accprob>1){
		accprob=1;
	}
	double u = distribution(generator);
	if(u <= accprob){
		x1 = xp;
	}else{
		x1 = xo;
	}
	return x1;
}

int main(){
 
  int burnin = 0;
  int lag = 1;
  int samples = 1000;
  int sd = 50;
  double x = -1;

  for(int i=1;i<=burnin;i=i+1){
  		x = MHstep(x,sd);
  }
  for(int i=1;i<=samples;i=i+1){
  		for (int j = 1; j <=lag; ++j)
  		{
  			x=MHstep(x,sd);
  		}
  		cout << x << "\n";
  }
  
  return 0;
}