#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib_Sjf.h"
#include <string.h> 

// Estructura para representar un proceso
typedef struct {
    char nombre[20];
    int rafaga;
    int tiempo_llegada;
    int tiempo_espera;
    int tiempo_en_sistema;
} Proceso;

JNIEXPORT jobjectArray JNICALL Java_lib_Sjf_sjf(JNIEnv *env, jobject obj, jobjectArray nombres, jintArray rafagas, jintArray tiemposLlegada) {
    // Obtener la longitud de los arrays
    jsize n = (*env)->GetArrayLength(env, nombres);

    // Crear arrays de procesos y tiempos de llegada en C
    Proceso *procesos = (Proceso *)malloc(n * sizeof(Proceso));
    jint *rafagas_c = (*env)->GetIntArrayElements(env, rafagas, NULL);
    jint *tiempos_llegada_c = (*env)->GetIntArrayElements(env, tiemposLlegada, NULL);

    // Obtener nombres de procesos
    for (int i = 0; i < n; i++) {
        jstring nombre = (jstring)(*env)->GetObjectArrayElement(env, nombres, i);
        const char *nombre_c = (*env)->GetStringUTFChars(env, nombre, NULL);
        strcpy(procesos[i].nombre, nombre_c);
        (*env)->ReleaseStringUTFChars(env, nombre, nombre_c);
    }

    // Llenar estructuras de procesos
    for (int i = 0; i < n; i++) {
        procesos[i].rafaga = rafagas_c[i];
        procesos[i].tiempo_llegada = tiempos_llegada_c[i];
    }

    // Implementación del algoritmo SJF
    Proceso temp;
    int tiempo_actual = 0;

    // Ordenar los procesos por rafaga de CPU
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - i; j++) {
            if (procesos[j].rafaga > procesos[j + 1].rafaga) {
                temp = procesos[j];
                procesos[j] = procesos[j + 1];
                procesos[j + 1] = temp;
            }
        }
    }

    // Calcular tiempos de espera y en el sistema
    for (int i = 0; i < n; i++) {
        // Calcular tiempo de espera
        procesos[i].tiempo_espera = tiempo_actual - procesos[i].tiempo_llegada;
        if (procesos[i].tiempo_espera < 0)
            procesos[i].tiempo_espera = 0;

        // Calcular tiempo en el sistema
        procesos[i].tiempo_en_sistema = procesos[i].tiempo_espera + procesos[i].rafaga;

        // Actualizar tiempo actual para el siguiente proceso
        tiempo_actual += procesos[i].rafaga;
    }

    // Crear un array de strings para almacenar los resultados
    jobjectArray resultados = (*env)->NewObjectArray(env, n, (*env)->FindClass(env, "java/lang/String"), NULL);

    // Rellenar el array de strings con los resultados
    for (int i = 0; i < n; i++) {
        char result[100];
        sprintf(result, "%s\t%d\t%d\t%d\t%d", procesos[i].nombre, procesos[i].rafaga,
                procesos[i].tiempo_llegada, procesos[i].tiempo_espera, procesos[i].tiempo_en_sistema);
        jstring resultado = (*env)->NewStringUTF(env, result);
        (*env)->SetObjectArrayElement(env, resultados, i, resultado);
    }

    // Liberar recursos
    (*env)->ReleaseIntArrayElements(env, rafagas, rafagas_c, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, tiemposLlegada, tiempos_llegada_c, JNI_ABORT);
    free(procesos);

    return resultados;
}

