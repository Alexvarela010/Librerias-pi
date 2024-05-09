package aplicacion;
import libio.Lineal;

public class Aplicacion {

    static {
        System.loadLibrary("ovaIO");
    }

    public Aplicacion() {
        double[] restricciones = {3.0,2.0,18.0,1.0,0,4.0,0,2.0,12.0};
        Lineal lin = new Lineal();
        double[] sol = lin.lineal(1.5, 2.5, restricciones);
        for (int i = 0; i < sol.length; i++) {
            System.out.println(sol[i]);
        }
    }

    public static void main(String[] arguments) {
        new Aplicacion();
    }
}

