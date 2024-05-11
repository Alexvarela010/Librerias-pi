package aplicacion;

import lib.Sjf;

public class Aplicacion {

    static {
        System.loadLibrary("_Sjf");
    }

    public static void main(String[] args) {
        // Datos de ejemplo: nombres de procesos, ráfagas y tiempos de llegada
        String[] nombres = {"Word", "Excel", "Paint", "Cal"};
        int[] rafagas = {8, 6, 4, 2};
        int[] tiemposLlegada = {0, 2, 4, 6};

        // Crear una instancia de la clase Sjf
        Sjf sjf = new Sjf();

        // Llamar al método nativo para calcular los resultados
        String[] resultados = sjf.sjf(nombres, rafagas, tiemposLlegada);

        // Mostrar los resultados
        System.out.println("Proceso\tRáfaga\tTiempo de llegada\tTiempo de espera\tTiempo en el sistema");
        for (String resultado : resultados) {
            System.out.println(resultado);
        }
    }
}

