package Main;

import java.util.Arrays;
import java.util.function.BiFunction;

public class Miln implements CompMethod {
    private double x0;
    private double y0;
    private double diff;
    private double end;
    public double[] xs;
    public double[] ys;

    public Newton binding;

    private BiFunction<Double, Double, Double> function;

    public Miln(BiFunction<Double, Double, Double> function) {
        this.function = function;
    }

    private void calcFirst4(double[] x, double[] y, double h) {
        for (int i = 0; i < 4; i++) {
            double k1 = function.apply(x[i], y[i]);
            double k2 = function.apply(x[i] + h / 2, y[i] + k1 * h / 2);
            double k3 = function.apply(x[i] + h / 2, y[i] + k2 * h / 2);
            double k4 = function.apply(x[i] + h, y[i] + k3 * h);
            x[i + 1] = x[i] + h;
            y[i + 1] = y[i] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        }
    }

    public void calc() {

        double h = 0.001;
        while (true) {
            int n = (int) Math.round((end - x0) / h);
            xs = new double[n];
            ys = new double[n];

            xs[0] = x0;
            ys[0] = y0;
            calcFirst4(xs, ys, h);

            double y = 0;
            for (int i = 4; i < n; i++) {
                xs[i] = xs[i - 1] + h;
                y = ys[i - 4] + 4 * h / 3 * (2 * function.apply(xs[i - 3], ys[i - 3]) - function.apply(xs[i - 2], ys[i - 2]) + 2 * function.apply(xs[i - 1], ys[i - 1]));
                ys[i] = ys[i - 2] + h / 3 * (function.apply(xs[i - 2], ys[i - 2]) + 4 * function.apply(xs[i - 1], ys[i - 1]) + function.apply(xs[i], y));
            }

            if (Math.abs(ys[n - 1] - y) / 29 > diff) h = h / 2;
            else break;
        }
        this.binding = new Newton();
        int length = xs.length / 100;
        if (length > 5) {
            double[] xs2 = new double[length];
            double[] ys2 = new double[length];
            for (int i = 0; i < length; i++) {
                xs2[i] = xs[i * 100];
                ys2[i] = ys[i * 100];
            }
            binding.setXY(xs2, ys2);
        } else {
            binding.setXY(Arrays.copyOf(xs, xs.length), Arrays.copyOf(ys, ys.length));
        }

    }

    // setters

    public void setX0(double x0) {
        this.x0 = x0;
    }

    public void setY0(double y0) {
        this.y0 = y0;
    }

    public void setDiff(double diff) {
        this.diff = diff;
    }

    public void setEnd(double end) {
        this.end = end;
    }
}
