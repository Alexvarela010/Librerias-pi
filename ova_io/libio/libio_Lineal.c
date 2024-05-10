#include <float.h>
#include <jni.h>
#include <math.h>

/*
 * Class:     libio_Lineal
 * Method:    lineal
 * Signature: (DD[D)[D
 */
typedef struct{
double x1;
double x2;
double y1;
double y2;
} Ecuacionlineales;

typedef struct{
double x;
double y;
} Interseccion;

typedef struct{
double A;
double B;
double C;
} restr;

JNIEXPORT jdoubleArray JNICALL Java_libio_Lineal_lineal
  (JNIEnv * env1, jobject obj1, jdouble x1, jdouble x2, jdoubleArray restricciones){
 jsize len = (*env1)->GetArrayLength(env1, restricciones);
    jsize len_restriccion = len / 3;
    jdouble * restriccion = (*env1)->GetDoubleArrayElements(env1, restricciones, NULL);

    double restriccion_x1[len_restriccion];
    double restriccion_x2[len_restriccion];
    double restriccion_z[len_restriccion];
	Ecuacionlineales ecuacion[len_restriccion];
	restr rest[len];
	int j=0;

	for(int i=0;i<len;i+=3){
	rest[j].A=restriccion[i];
	j++;
	}

	 j=0;

	for(int i=1;i<len;i+=3){
        rest[j].B=restriccion[i];
        j++;
        }

         j=0;

	for(int i=2;i<len;i+=3){
        rest[j].C=restriccion[i];
        j++;
        }

         j=0;

         for(int i=0;i<len;i+=3){
         ecuacion[j].x1=restriccion[i];
	 ecuacion[j].y1=0;
	 ecuacion[j].y2=restriccion[i+1];
	 ecuacion[j].x2=0;
	 j++;
 	 }

	j=0;
	for(int i=2;i<len;i+=3){
	restriccion_z[j]=restriccion[i];
	j++;
	}
        double ecuaciones[len];
	for (int i = 0; i < len_restriccion; i++) {
        if (ecuacion[i].x1 != 0) {
            ecuacion[i].x1 = restriccion_z[i] / ecuacion[i].x1;
        }
        if (ecuacion[i].y2 != 0) {
            ecuacion[i].y2 = restriccion_z[i] / ecuacion[i].y2;
        }
    }



    double solucion = DBL_MAX;
	double x,y;
	int cont_solucion=0;
	int check=0;
	Interseccion posibles_soluciones[(len_restriccion*(len_restriccion-1))/2];
	for (int i = 0; i < len_restriccion - 1; i++) {
         for (int j = i+ 1; j < len_restriccion; j++) {
            double m1, m2;
	    m1=(ecuacion[i].y2-ecuacion[i].y1)/(ecuacion[i].x2-ecuacion[i].x1);
	    m2=(ecuacion[j].y2-ecuacion[j].y1)/(ecuacion[j].x2-ecuacion[j].x1);
            if(m1!=m2){
             x = fabs(((rest[i].B * rest[j].C - rest[j].B * rest[i].C) / (rest[i].A * rest[j].B - rest[j].A * rest[i].B)));
   	     y = fabs(((rest[i].C * rest[j].A - rest[j].C * rest[i].A) / (rest[i].A * rest[j].B - rest[j].A * rest[i].B)));
	     y=(rest[i].A*rest[j].C-rest[i].C*rest[j].A)/(rest[i].A*rest[j].B-rest[i].B*rest[j].A);
	     x=(rest[i].C-rest[i].B*y)/rest[i].A;
	     check=0;
	     for(int k=0;k<len_restriccion;k++){
	     if(((x*rest[k].A + y*rest[k].B) <= rest[k].C)){
 	     check++;
	     }
	     if(check==len_restriccion){
	     posibles_soluciones[cont_solucion].x=x;
             posibles_soluciones[cont_solucion].y=y;
	     cont_solucion++;
	     }
	     }
	   }
	}
    }
int co=1;
int coo=0;
	 double fin[(len_restriccion*(len_restriccion-1))];
	for(int i=0;i<len_restriccion*2;i+=2){
	fin[i]=posibles_soluciones[coo].x;
	fin[co]=posibles_soluciones[coo].y;
	coo++;
	co+=2;
}

    for (int i = 0; i < len_restriccion; i++) {
        double respuesta = (restriccion_x1[i] * x1) + (restriccion_x2[i] * x2);
        if (respuesta < solucion) {
            solucion = respuesta;
          //  fin[0] = restriccion_x1[i] * x1;
          //  fin[1] = restriccion_x2[i] * x2;
          //  fin[2] = solucion;
        }else{
	//fin[0]=9999;
}
    }

    (*env1)->ReleaseDoubleArrayElements(env1, restricciones, restriccion, 0);

    jdoubleArray result = (*env1)->NewDoubleArray(env1, (len_restriccion*(len_restriccion-1)));
    (*env1)->SetDoubleArrayRegion(env1, result, 0, (len_restriccion*(len_restriccion-1)), fin);
    return result;
}

