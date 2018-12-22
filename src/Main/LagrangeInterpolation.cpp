#include "interpolation_functions.hpp"

using namespace std;
//vector<long double> represents a polynomial, indexes are x powers, values are coefficients
//That to say:
//Assume we have a vector A:
//indexes:    |  3  |  2  |  1  |  0  |
//values:     | 1.5 | -1.1|  0  |  7  |
//Vector A represents a polynomial 1.5x^3 - 1.1x^2 + 7
//The operations of polynomial sum and multiplication are based on this representation
vector<long double> count_function(vector<Point> points) {
    typedef vector<Point>::size_type size;
    size sz = points.size();
    vector<double>xs;
    vector<double>ys;
    for (size i = 0; i < sz; i++) {
        double x = points[i].Getx();
        double y = points[i].Gety();
        xs.push_back(x);
        ys.push_back(y);
        cout<<"X: "<<x<<"; Y: "<<y<<endl;
    }
    vector<long double>final_polynom = {0};
    for (int i = 0; i < sz; ++i) {
        long double denominator = 1;
        vector<long double> nominator = {1};
        for (int j = 0; j < sz; ++j) {
            if (i != j) {
                denominator *= (xs[i] - xs[j]);
                vector<long double>current_polynom = {(-1)*xs[j], 1};
                nominator = polynomial_multiplication(nominator, current_polynom);
            }
        }
        vector<long double>denom = {1/denominator};
        nominator = polynomial_multiplication(nominator, denom);
        vector<long double>y_value = {ys[i]};
        nominator = polynomial_multiplication(nominator, y_value);
        final_polynom = polynomial_sum(final_polynom, nominator);
    }
    return final_polynom;
}

/*
    Two vectors represent two polynomials, indexes are x powers, values are coefficients
*/
vector<long double> polynomial_multiplication(const vector<long double>& first, const vector<long double>& second) {
    typedef vector<long double>::size_type size;
    size sz = first.size() + second.size() - 1;
    vector<long double>results;
    for (int i = 0; i < sz; ++i) {
        results.push_back(0);
    }
    for (int i = 0; i < first.size(); ++i) {
        for (int j = 0; j < second.size(); ++j) {
            long double value = first[i]*second[j];
            int index = i+j;
            results[index] += value;
        }
    }
    return results;
}

vector<long double> polynomial_sum(const vector<long double>& first, const vector<long double>& second) {
    typedef vector<long double>::size_type size;
    size sz = max(first.size(), second.size());
    vector<long double>results;
    for (int i = 0; i < sz; ++i) {
        long double val = 0;
        if (i < first.size())
            val += first[i];
        if (i < second.size())
            val += second[i];
        results.push_back(val);
    }
    return results;
}

double interpolation_function(double arg, const vector<long double>& coefficients) {
    size_t sz = coefficients.size();
    long double result = 0;
    for (size_t i = 0; i < sz; i++) {
        result += coefficients[i] * pow(arg, i);
    }
    return result;
}
