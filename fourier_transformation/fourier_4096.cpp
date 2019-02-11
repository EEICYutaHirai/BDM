#include <complex>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

//const double T = 1.734;
const double T = 1.384;
const double N = 4096;
const int N_int = 4096;
const complex<double> pi = 3.141592;
const complex<double> e = 2.71828;
complex<double> hoge(0, 2);
complex<double> W = pow(e, hoge *pi / N);

//arduinoは5msくらいで1loop
//周波数分解能は1/T
// N/2T(rad/s)まで測定できる

int main()
{
    vector<complex<double>> x;

    for (int i = 0; i < N_int; i++)
    {
        complex<double> tmp;
        cin >> tmp;
        //tmp = 100. * sin(i * 100. / (double)T);
        x.push_back(tmp);
    }

    for (int i = 0; i < N_int; i++)
    {
        complex<double> y;
        for (int j = 0; j < N_int; j++)
        {
            y += pow(W, -(double)j * i) * x[j];
        }
        y /= N;
        cout << (double)i / T << "\t" << abs(y) << endl;
    }
}