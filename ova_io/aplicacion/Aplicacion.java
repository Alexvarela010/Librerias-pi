package aplicacion;
import libio.Lineal;

public class Aplicacion {

    static {
        System.loadLibrary("ovaIO");
    }

    public Aplicacion() {
        double[] restricciones = {1.0,4.0,1600.0,1.0,30.0,20.0,18000.0,1.0};
        Lineal lin = new Lineal();
        double[] sol = lin.lineal("max",10.0, 8.0, restricciones);
        for (int i = 0; i < sol.length; i++) {
            System.out.println(sol[i]);
        }
    }

    public static void main(String[] arguments) {
        new Aplicacion();
    }
}

