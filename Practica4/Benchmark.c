#include <sys/types.h>  	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
//Este es el número de operaciones necesarias en una matriz de dimensión 1000
const long long operaciones = 2668664000;
using namespace std;
void invermat(int n, double **a, double **ainv, double &determ, struct timeval &diff) {
// Algoritmo para la eliminación simple de Gauss
   struct timeval start, end;
   int i, j, k;
   double factor;
   double **L, *D, *X;
   X = new double [n]; D = new double [n];
   L = new double* [n];
   for (j = 0; j < n; j++){
     L[j] = new double [n];
   }
   gettimeofday(&start,NULL);
   //Aquí se realizan
   for (k = 0; k < n - 1; k++) {
      for (i = k+1; i < n;  i++) {
         factor = a[i][k]/a[k][k];

         for (j = k+1; j < n + 1; j++) {
           a[i][j] = a[i][j] - factor * a[k][j];


         }
      }
   }
// Cálculo del determinante
   determ = 1.;
   for (i = 0; i < n; i++) {
     determ = determ * a[i][i];
   }
// Rutina para determinar las matrices  L (inferior)
//  y U (superior) de la descomposición LU
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (i > j) {
       L[i][j] = a[i][j]/a[j][j];

       a[i][j] = 0;
      }
    }
  }
  for (i = 0; i < n; i++) {
     for (j = 0; j < n; j++) {
       L[j][j] = 1;
     }
  }
// cálculo de la inversa
 for (k = 0; k < n; k++) {
// Esta rutina inicializa los L[i][n]
    for (i = 0; i < n; i++) {
       if (i == k){
         L[i][n] = 1;
       }
       else {
         L[i][n] = 0;
       }
     }
// Esta función implementa la sustitución hacia adelante con
// los L[i][n] que produce la rutina anterior
  double sum;
  D[0] = L[0][n];
  for (i = 1; i < n; i++) {
     sum = 0;
     for (j = 0; j < i; j++) {
       sum = sum + L[i][j]*D[j];
     }
     D[i] = L[i][n] - sum;
  }
// Esta rutina asigna los D[i] que produce forward para
// ser utilizados con la matriz U
  for (i = 0; i < n; i++) {
    a[i][n] = D[i];
  }
  // Rutina que aplica la sustitución hacia atras
  X[n-1] = a[n-1][n]/a[n-1][n-1];

  // Determinación de las raíces restantes
  for (i = n - 2; i > -1; i--) {
     sum = 0;
     for (j = i+1; j < n; j++) {
        sum = sum + a[i][j]*X[j];
     }
     X[i] = (a[i][n] - sum)/a[i][i];
  }

// Esta rutina asigna los X[i] que produce Sustituir
// como los elementos de la matriz inversa
    for (i = 0; i < n; i++) {
      ainv[i][k] = X[i];
    }
  }   // llave de cierre del for para k
  gettimeofday(&end,NULL);
  timersub(&end, &start, &diff);

}




int main(int argc, char *argv[]){
    if(argc < 1){
        printf("El uso correcto es: benchmark <dimensión de la matriz>.\n");
        printf("La prueba consistirá en crear una matriz  de dimensión n aleatoria e invertirla.\n");
        printf("Se medirá el tiempo que tarda en ejecutar la inversión de la matriz.\n");
        printf("Por último, ćalcularemos cuantas operaciones en coma flotante hemos hecho");
        printf(" y calcularemos los MFLOPS.\n");

    }


    // Definición de variables y asignación dinámica de memoria

    int i, j, n=0;
    n = atoi(argv[1]);
    double **a, **ainv, determ = 0;
    a = new double* [n], ainv = new double* [n];
    for(j=0; j<n; j++){
      a[j] = new double [n], ainv[j] = new double [n];
    }
    // Lectura de la matriz
    for(i=0; i<n; i++){
      for(j=0; j<n; j++){
        a[i][j] = random()/100.0;
      }
    }
    struct timeval diff;
    invermat (n, a, ainv, determ, diff);

    double time = diff.tv_sec + diff.tv_usec*1.0/(1000000);
    cout << operaciones*1.0/time/1000000 << " " << endl;
    // Matriz inversa; ainv


    return 0;

}
