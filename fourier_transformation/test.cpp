#include <complex>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

const double T = 1;
const double N = 4096;
const int N_int = 4096;
const complex<double> pi = 3.141592;
const complex<double> e = 2.71828;
complex<double> hoge(0, 2);
complex<double> W = pow(e, hoge *pi / N);

int main()
{
    cout << W << endl;
}