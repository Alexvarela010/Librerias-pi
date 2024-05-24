package aplicacion;

import libreria.Taylor;

public class Aplicacion {

    static {
        System.loadLibrary("libreria_Taylor"); // Cargar la biblioteca nativa
    }

    public static void main(String[] args) {

	 Taylor taylor = new Taylor();

        // Probar CharSenx
        String[] senx = taylor.CharSenx(10);
        System.out.println("Resultados de CharSenx:");

        // Usar el bucle for-each
        for (String s : senx) {
            if (s != null) {
                System.out.println(s);
            } else {
                break; // Salir del bucle si se encuentra un null
            }
       }
	
        // Probar CharCosx
        String[] cosx = taylor.CharCosx(10);
        System.out.println("Resultados de CharCosx:");

        // Usar el bucle for-each
        for (String s : cosx) {
            if (s != null) {
                System.out.println(s);
            } else {
                break; // Salir del bucle si se encuentra un null
            }
        }
	
	 // Probar CharLnx
        String[] lnx = taylor.CharLnx(10);
       System.out.println("Resultados de CharLnx:");

        // Usar el bucle for-each
        for (String s : lnx) {
            if (s != null) {
                System.out.println(s);
            } else {
                break; // Salir del bucle si se encuentra un null
            }
        }

	// Probar CharEulerx
        String[] Eulerx = taylor.CharEulerx(10);
        System.out.println("Resultados de CharEulerx:");

        // Usar el bucle for-each
        for (String s : Eulerx) {
            if (s != null) {
                System.out.println(s);
            } else {
                break; // Salir del bucle si se encuentra un null
            }
        }

	// Probar CharCombinacionx
        String[] Combinacion = taylor.CharCombinacionx(10);
        System.out.println("Resultados de CharCombinacionx:");

        // Usar el bucle for-each
        for (String s : Combinacion) {
            if (s != null) {
                System.out.println(s);
            } else {
                break; // Salir del bucle si se encuentra un null
            }
        }

 	double resultado = 0.0;

	// Probar TaylorSenxNum
        resultado = taylor.SenxNum(10, 3.3);
        System.out.println("Resultado de TaylorSenxNum (N=10, X=3.3):");
        System.out.println(resultado);

	 // Probar TaylorCosxNum
	resultado = taylor.CosxNum(10, 3.3);
        System.out.println("Resultado de TaylorCosNum (N=10, X=3.3):");
        System.out.println(resultado);
	
	 // Probar TaylorLnxNum
        resultado = taylor.LnxNum(10, 3.3);
        System.out.println("Resultado de TaylorLnxNum (N=10, X=3.3):");
        System.out.println(resultado);
	
	 // Probar TaylorEulerxNum
        resultado = taylor.EulerxNum(10, 3.3);
        System.out.println("Resultado de TaylorEulerxNum (N=10, X=3.3):");
        System.out.println(resultado);

	 // Probar TaylorCombinacionxNum
        resultado = taylor.CombinacionxNum(10, 3.3);
        System.out.println("Resultado de TaylorCombinacionxNum (N=10, X=3.3):");
        System.out.println(resultado);
 }        

}

