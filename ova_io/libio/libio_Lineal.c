#include<float.h>
#include<jni.h>
#include<math.h>
#include<string.h>
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
}Ecuacionlineales;

typedef struct{
double x;
double y;
}Interseccion;

typedef struct{
double A;
double B;
double C;
}restr;

JNIEXPORT jdoubleArray

JNICALL Java_libio_Lineal_lineal
        (JNIEnv *env1, jobject obj1, jstring min_max, jdouble x1, jdouble x2, jdoubleArray restricciones) {

	const char *comparar = "minimizar";
    jsize len = ( * env1)->GetArrayLength(env1, restricciones);
    jsize len_restriccion = len / 4;
    jdouble * restriccion = ( * env1)->GetDoubleArrayElements(env1, restricciones, NULL);

    double restriccion_x1[ len_restriccion];
    double restriccion_x2[ len_restriccion];
    double restriccion_z[ len_restriccion];
    double mayor_menor[ len_restriccion];
    double xfob = x1;
    double yfob = x2;
    Ecuacionlineales ecuacion[ len_restriccion];
    restr rest[ len];
    int j = 0;
	const char *max_min = ( * env1)->GetStringUTFChars(env1, min_max, NULL);
    for (int i = 0; i < len; i += 4) {
        rest[j].A = restriccion[i];
        j++;
    }

    j = 0;

    for (int i = 1; i < len; i += 4) {
        rest[j].B = restriccion[i];
        j++;
    }

    j = 0;

    for (int i = 3; i < len; i += 4) {
        mayor_menor[j] = restriccion[i];
        j++;
    }

    j = 0;

    for (int i = 2; i < len; i += 4) {
        rest[j].C = restriccion[i];
        j++;
    }

    j = 0;

    for (int i = 0; i < len; i += 4) {
        ecuacion[j].x1 = restriccion[i];
        ecuacion[j].y1 = 0;
        ecuacion[j].y2 = restriccion[i + 1];
        ecuacion[j].x2 = 0;
        j++;
    }

    j = 0;
    for (int i = 2; i < len; i += 4) {
        restriccion_z[j] = restriccion[i];
        j++;
    }
    Interseccion posibles_soluciones[ ((len_restriccion * (len_restriccion - 1)) / 2) + len_restriccion];
    int check = 0;
    for (int i = 0; i < ((len_restriccion * (len_restriccion - 1)) / 2) + len_restriccion; i++) {
        posibles_soluciones[i].x = -2.0;
        posibles_soluciones[i].y = -2.0;
    }
    int cont_solucion = 0;
    double ecuaciones[ len];
    for (int i = 0; i < len_restriccion; i++) {
        if (ecuacion[i].x1 != 0) {
            ecuacion[i].x1 = restriccion_z[i] / ecuacion[i].x1;
        }
        if (ecuacion[i].y2 != 0) {
            ecuacion[i].y2 = restriccion_z[i] / ecuacion[i].y2;
        }

        check = 0;
        for (int k = 0; k < len_restriccion; k++) {
            if (mayor_menor[k] == 1.0) {
                if (((ecuacion[i].x1 * rest[k].A) <= rest[k].C) && ecuacion[i].x1 >= 0) {
                    check++;
                }
            } else {
                if (((ecuacion[i].x1 * rest[k].A) >= rest[k].C) && ecuacion[i].x1 >= 0) {
                    check++;
                }
            }
        }
        if (check == len_restriccion) {
            posibles_soluciones[cont_solucion].x = ecuacion[i].x1;
            posibles_soluciones[cont_solucion].y = ecuacion[i].y1;
            cont_solucion++;
        }
        check = 0;
        for (int k = 0; k < len_restriccion; k++) {
            if (mayor_menor[k] == 1.0) {
                if (((ecuacion[i].y2 * rest[k].B) <= rest[k].C) && ecuacion[i].y2 >= 0) {
                    check++;
                }
            } else {
                if (((ecuacion[i].y2 * rest[k].B) >= rest[k].C) && ecuacion[i].y2 >= 0) {
                    check++;
                }
            }
        }
        if (check == len_restriccion) {
            posibles_soluciones[cont_solucion].x = ecuacion[i].x2;
            posibles_soluciones[cont_solucion].y = ecuacion[i].y2;
            cont_solucion++;
        }
    }
    double x, y;
    for (int i = 0; i < len_restriccion - 1; i++) {
        for (int j = i + 1; j < len_restriccion; j++) {
            double m1, m2;
            m1 = (ecuacion[i].y2 - ecuacion[i].y1) / (ecuacion[i].x2 - ecuacion[i].x1);
            m2 = (ecuacion[j].y2 - ecuacion[j].y1) / (ecuacion[j].x2 - ecuacion[j].x1);
            if (m1 != m2) {
                x = fabs(((rest[i].B * rest[j].C - rest[j].B * rest[i].C) / (rest[i].A * rest[j].B - rest[j].A * rest[i].B)));
                y = fabs(((rest[i].C * rest[j].A - rest[j].C * rest[i].A) / (rest[i].A * rest[j].B - rest[j].A * rest[i].B)));
                y = (rest[i].A * rest[j].C - rest[i].C * rest[j].A) / (rest[i].A * rest[j].B - rest[i].B * rest[j].A);
                x = (rest[i].C - rest[i].B * y) / rest[i].A;
                check = 0;
                for (int k = 0; k < len_restriccion; k++) {
                    if (mayor_menor[k] == 1.0) {
                        if (((x * rest[k].A + y * rest[k].B) <= rest[k].C) && x >= 0 && y >= 0) {
                            check++;
                        }
                    } else {
                        if (((x * rest[k].A + y * rest[k].B) >= rest[k].C) && x >= 0 && y >= 0) {
                            check++;
                        }
                    }
                }
                if (check == len_restriccion) {
                    posibles_soluciones[cont_solucion].x = x;
                    posibles_soluciones[cont_solucion].y = y;
                    cont_solucion++;
                }
            }
        }
    }
    int size = 0;
    int cerrar_ciclo = 0;
    for (int i = 0; i < (len_restriccion * (len_restriccion - 1)) + len_restriccion * 2; i++) {
        if (posibles_soluciones[i].x != -2.0 && posibles_soluciones[i].y != -2.0) {
            for (int j = 0; j < len_restriccion; j++) {
                if (posibles_soluciones[i].x == rest[j].A && posibles_soluciones[i].y == rest[j].B) {
                    cerrar_ciclo = 1;
                    break;
                }
            }
            if (cerrar_ciclo == 1) {
                break;
            }
            size += 2;
        }
    }
    int co = 1;
    int conn = 0;
    double fin[ size + 1];
    for (int i = 0; i < size; i++) {
        if ((posibles_soluciones[i].x != -2.0 && posibles_soluciones[i].y != 2.0)) {
            fin[conn] = posibles_soluciones[i].x;
            fin[co] = posibles_soluciones[i].y;
            conn += 2;
            co += 2;
        }
    }
    double solucion[ 3];
    if (strcmp(max_min, comparar) == 0) {
        solucion[2] = DBL_MAX;
        double respuesta = 0;
        for (int i = 1; i < size; i += 2) {
            respuesta = (fin[i - 1] * xfob) + (fin[i] * yfob);
            if (respuesta < solucion[2]) {
                solucion[2] = respuesta;
                solucion[0] = fin[i - 1];
                solucion[1] = fin[i];
            }
        }
    } else {
        solucion[2] = DBL_MIN;
        double respuesta = 0;
        for (int i = 1; i < size; i += 2) {
            respuesta = (fin[i - 1] * xfob) + (fin[i] * yfob);
            if (respuesta > solucion[2]) {
                solucion[2] = respuesta;
                solucion[0] = fin[i - 1];
                solucion[1] = fin[i];
            }
        }
    }
    ( * env1)->ReleaseDoubleArrayElements(env1, restricciones, restriccion, 0);
    ( * env1)->ReleaseStringUTFChars(env1, min_max, max_min);
    jdoubleArray result = ( * env1)->NewDoubleArray(env1, 3);
    ( * env1)->SetDoubleArrayRegion(env1, result, 0, 3, solucion);
    return result;
}
