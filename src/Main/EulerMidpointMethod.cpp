#include "differential_equation_functions.hpp"
#include <math.h>
#include "interpolation_functions.hpp"
#include <iostream>
#include "Point.h"

using namespace std;

vector<Point>solve_equation(double func(double, double), double X0, double Y0, double x_max, double inaccuracy) {
    vector<Point> to_ret;
    double y = Y0;
    double step = std::abs(X0 - x_max);
    double diff;
    double fin1;
    double fin2;
    for (double x = X0; x <= x_max; x = x + step) {
        fin1 = y;
        double delta_y = step*func(x + step/2, y + step/2*func(x - step, y));
        y += delta_y;
    }
    y = Y0;
    step = step/2;
    for (double x = X0; x <= x_max; x = x + step) {
        fin2 = y;
        double delta_y = step*func(x + step/2, y + step/2*func(x - step, y));
        y += delta_y;
    }

    diff = std::abs(fin1 - fin2)/3;
    step /=2;
    while (diff > inaccuracy) {
    y = Y0;
    vector<Point> local;
    for (double x = X0; x <= x_max; x = x + step) {
        Point* pnt = new Point(x, y);
        fin1 = y;
        double delta_y = step*func(x + step/2, y + step/2*func(x - step, y));
        y += delta_y;
        local.push_back(*pnt);
    }

    to_ret = local;
    step /= 2;
    diff = std::abs(fin1 - fin2)/3;
    fin2 = fin1;
    }
    /*for (size_t o = 0; o < to_ret.size(); ++o) {
        cout<<"X: "<<to_ret[o].Getx()<<"; Y: "<<to_ret[o].Gety()<<endl;
    }*/
    return to_ret;
}
