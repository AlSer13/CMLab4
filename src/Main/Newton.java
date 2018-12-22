package Main;

import java.util.Arrays;
import java.util.function.Function;

public class Newton implements CompMethod {
    private double[] x;
    private double[] y;

    public Function<Double, Double> function;

    public Newton(Function<Double, Double> function){
        this.function = function;
    }

    public Newton() {}

    public void setXY(double[] x) {
        this.x = x;
        Arrays.sort(x);
        this.y = new double[x.length];
        for (int i = 0; i < y.length; i++) {
            y[i] = function.apply(x[i]);
        }
        calcY(x, y);
        for (int i = 0; i < y.length; i++) {
            System.out.printf("\nx%d: %f, y%d: %f", i, x[i], i, y[i]);
        }
    }

    public void setXY(double[] x, double[] y) {
        this.x = x;
        this.y = y;
        calcY(this.x, this.y);
        for (int i = 0; i < y.length; i++) {
            System.out.printf("\nx%d: %f, y%d: %f", i, x[i], i, y[i]);
        }
    }

    // разделенные разности
    private void calcY(double[] x, double[] y) {
        for (int i = 0; i < x.length; i++) {
            for (int j = i + 1; j < x.length; j++) {
                y[j] = (y[i] - y[j]) / (x[i] - x[j]);
            }
        }
    }

    public double calc(double c) {
        double y0 = y[0];
        double p = 1;

        for (int j = 1; j < x.length; j++) {
            p = p * (c - x[j - 1]);
            double k = y[j] * p;
            y0 = y0 + k;
        }
        return y0;
    }

    public double[] getX() {
        return x;
    }

    public double[] getY() {
        return y;
    }
}
