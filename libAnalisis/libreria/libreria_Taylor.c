#include <jni.h>
#include "libreria_Taylor.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        double result = 1;
        for (int i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }
}



// Implementación del método CharSenx
JNIEXPORT jobjectArray JNICALL Java_libreria_Taylor_CharSenx(JNIEnv *env, jobject obj, jint N) {
    jobjectArray result;
    result = (*env)->NewObjectArray(env, N, (*env)->FindClass(env, "java/lang/String"), NULL);

	int variable=0;             // esta es igual al exponente y denominador de la serie 2*n+1
    	int signo=0;                // signo del (-1)^n
    	char signoc=' ';            // signo en caracter + , -
    	int n=0; 

    for (int i = 0 ; i<N; i++) {
 	
	char buffer[50];

	variable= 2*n+1;

	if(variable>N){
            	break;
        	}

     	signo= pow(-1,n);		
	

     if(signo==1){
        signoc='+';
     }else{
        signoc='-';
     }

	snprintf(buffer, sizeof(buffer), "%c x^%d/%d!", signoc, variable, variable); // Ejemplo simple
        jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, i, str); 
	n++;

	 }

    return result;
}

// Implementación del método CharCosx
JNIEXPORT jobjectArray JNICALL Java_libreria_Taylor_CharCosx(JNIEnv *env, jobject obj, jint N) {

 jobjectArray result;
    result = (*env)->NewObjectArray(env, N, (*env)->FindClass(env, "java/lang/String"), NULL);

        int variable=0;             // esta es igual al exponente y denominador de la serie 2*n+1
        int signo=0;                // signo del (-1)^n
        char signoc=' ';            // signo en caracter + , -
        int n=1;

    for (int i = 1 ; i<=N; i++) {

        char buffer[50];

	if(i==1){
	 snprintf(buffer, sizeof(buffer), "1"); // Ejemplo simple
        jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, 0, str);
	}

        variable= 2*n;

        if(variable>N){
                break;
                }

        signo= pow(-1,n);

     if(signo==1){
        signoc='+';
     }else{
        signoc='-';
     }

        snprintf(buffer, sizeof(buffer), "%c x^%d/%d!", signoc, variable, variable); // Ejemplo simple
        jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, i, str);
        n++;

         }

    return result;
}


// Implementación del método CharEulerx
JNIEXPORT jobjectArray JNICALL Java_libreria_Taylor_CharEulerx(JNIEnv *env, jobject obj, jint N) {
    N =N+1;
    jobjectArray result;
    jclass stringClass = (*env)->FindClass(env, "java/lang/String");
    result = (*env)->NewObjectArray(env, N, stringClass, NULL);

    int n = 0; // n es la variable del algoritmo de e^x

    for (int i = 0; i < N; i++) {
        char buffer[50];

        if (i == 0) {
            snprintf(buffer, sizeof(buffer), "1");
        } else {
            snprintf(buffer, sizeof(buffer), "+ x^%d/%d!", n, n);
        }

        jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, i, str);

        n++;
    }
	 return result;
}


// Implementación del método CharLnx
JNIEXPORT jobjectArray JNICALL Java_libreria_Taylor_CharLnx(JNIEnv *env, jobject obj, jint N) {
     jobjectArray result;
    result = (*env)->NewObjectArray(env, N, (*env)->FindClass(env, "java/lang/String"), NULL);

        
    int signo=0;                // signo del (-1)^n+1
    char signoc=' ';            // signo en caracter + , -
    int n=1;                    //es el grado de la serie o polinomio


    for (int i = 0 ; i<N; i++) {

        char buffer[50];

     signo= pow(-1,n+1);

     if(signo==1){
        signoc='+';
     }else{
        signoc='-';
     }

        snprintf(buffer, sizeof(buffer), "%c x^%d/%d!", signoc, n, n);
        jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, i, str);
        n++;

         }

    return result;
}



//char de taylor x^2*e^-x
JNIEXPORT jobjectArray JNICALL Java_libreria_Taylor_CharCombinacionx(JNIEnv *env, jobject obj, jint N) {
     
    N= N+1;
    jobjectArray result;
    result = (*env)->NewObjectArray(env, N, (*env)->FindClass(env, "java/lang/String"), NULL);

   
    int variable= 0;         // signo del (-1)^n
    char signoc=' ';            // signo en caracter + , -
    int signo=0;                // signo del (-1)^n
    int n=0;                    //es el grado de la serie o polinomio
	


    for(int i=0;i<N;i++){    // i es el numero de iteraciones de la sumatoria


        char buffer[50];


if(i==0){
         snprintf(buffer, sizeof(buffer), "0"); 
        
	}else{

	 variable=n*n-n;    // n*n-n
   	 signo = pow(-1,n);
     	
	if(signo==1){
       		 signoc='+';
     	}else{

	         signoc='-';
     	}

    	snprintf(buffer, sizeof(buffer), "%c %dx^%d/%d!", signoc, variable, n, n);
        }

	jstring str = (*env)->NewStringUTF(env, buffer);
        (*env)->SetObjectArrayElement(env, result, i, str);
	
	


           n++;


    }


    return result;
}


// Implementación del método NumSenx
JNIEXPORT jdouble JNICALL Java_libreria_Taylor_SenxNum(JNIEnv *env, jobject obj, jint N, jdouble X) {

    int variable = 0;
    int signo = 0;
    int n = 0;
    double resultado = 0;

    for (int i = 1; i <= N; i++) {
        variable = 2 * n + 1;

        if (variable > N) {
            break;
        }

        signo = pow(-1, n);

        resultado += (double)(signo * pow(X, variable)) / factorial(variable);

        n++;
    }

    return resultado;
}


// Implementación del método NumCosx
JNIEXPORT jdouble JNICALL Java_libreria_Taylor_CosxNum(JNIEnv *env, jobject obj, jint N, jdouble X) {


     //N limite de la sumatoria  serie de taylor alrededor de Xo

    int variable=0;                   // esta es igual al exponente y denominador de la serie 2*n
    int signo=0;                      // signo del (-1)^n
    int n=0;                          //es el grado de la serie o polinomio
    double resultado=0;               // resultado de taylor calculado en x


    // i es el numero de iteraciones

    for(int i=1;i<=N;i++){

     variable= 2*n;

      if(variable>N){
            break;
        }

     signo= pow(-1,n);

     resultado+=(double)(signo * pow(X,variable))/(factorial(variable));

     n++;
    }
         //printf("Polinomio grado n=%d evaluado en x=%f es igual a %f\n", N, X, resultado);
         
	return resultado;

    }

// Implementación del método NumLnx
JNIEXPORT jdouble JNICALL Java_libreria_Taylor_LnxNum(JNIEnv *env, jobject obj, jint N, jdouble X) {


     //N limite de la sumatoria  serie de taylor alrededor de Xo

    int signo=0;                      // signo del (-1)^n
    int n=1;                        //es el grado de la serie o polinomio
    double resultado=0;               // resultado de taylor calculado en x


    // i es el numero de iteraciones

    for(int i=1;i<=N;i++){

     signo= pow(-1,n+1);

     resultado+=(double)(signo * pow(X,n))/n;

     n++;
    }
       //printf("Polinomio grado n=%d evaluado en x=%f es igual a %f\n", N, X, resultado);
         
	return resultado;
    }



// Implementación del método NumEulerx
JNIEXPORT jdouble JNICALL Java_libreria_Taylor_EulerxNum(JNIEnv *env, jobject obj, jint N, jdouble X) {

     //N limite de la sumatoria  serie de taylor alrededor de Xo

    int n=0;                        //es el grado de la serie o polinomio y la variable
    double resultado=0;             // resultado de taylor calculado en x

    // i es el numero de iteraciones

    for(int i=0;i<=N;i++){

     resultado+=(double)((pow(X,n))/(factorial(n)));
     n++;
    }
         
	return resultado;
    }


// Implementación del método CombinacionNum
JNIEXPORT jdouble JNICALL Java_libreria_Taylor_CombinacionxNum(JNIEnv *env, jobject obj, jint N, jdouble X) {

     //N limite de la sumatoria  serie de taylor alrededor de Xo

    int variable=0;                   // esta es igual al numeror n*n-n
    int signo=0;                      // signo del (-1)^n
    int n=1;                          //es el grado de la serie o polinomio
    double resultado=0;               // resultado de taylor calculado en x


    // i es el numero de iteraciones

    for(int i=1;i<=N;i++){


     variable= n*n-n;

     signo= pow(-1,n);

     resultado+=(double)(signo *variable* pow(X,n))/factorial(n);

     n++;
    }
         return resultado;
    }


