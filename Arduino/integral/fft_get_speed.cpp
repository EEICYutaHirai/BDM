#include <complex>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

double T;
const double N = 1024;
const int N_int = 1024;
const complex<double> pi = 3.141592;
const complex<double> e = 2.71828;
complex<double> hoge(0, 2);
complex<double> W = pow(e, hoge *pi / N);

//toruku keisuu
double ke = 0.3;

//arduinoは5msくらいで1loop
//周波数分解能は1/T
// N/2T(rad/s)まで測定できる

void partial_fft(complex<double> *x, complex<double> *y, int n, complex<double> w)
{
    if (n == 1)
    {
        y[0] = x[0];
    }
    else
    {
        complex<double> tmp_w = 1.0;
        for (int i = 0; i < n / 2; i++)
        {
            y[i] = (x[i] + x[i + n / 2]);
            y[i + n / 2] = (x[i] - x[i + n / 2]) * tmp_w;
            tmp_w *= w;
        }
        partial_fft(y, x, n / 2, w * w);
        partial_fft(y + n / 2, x + n / 2, n / 2, w * w);
        for (int i = 0; i < n / 2; i++)
        {
            y[2 * i] = x[i];
            y[2 * i + 1] = x[i + n / 2];
        }
    }
}

void fft(complex<double> *x, complex<double> *y, int n)
{
    partial_fft(x, y, n, W);
    for (int i = 0; i < n; i++)
    {
        y[i] /= (double)n;
    }
}

int main()
{
    complex<double> x[N_int], y[N_int];

	  //ifstream in("data.txt");
	    
	//cin.rdbuf(in.rdbuf());

    for (int i = 0; i < N_int; i++)
    {
        complex<double> tmp;
        cin >> tmp;
        //tmp = 100. * sin(i * 100. / (double)T);
        x[i] = tmp;
    }

    cin >> T;
	T/=1000.;

    fft(x, y, N_int);

	double res = 0.;
    for (int i = 1; i < N_int; i++)
    {
        //cout << (double)i / T << "\t" << abs(y[i]) << endl;
        if (abs(y[i]) > 3.*)
        {
            //rad/sで計算
            res=(double)i * 6.28 / T / 18.;
				//Ec(gyaku kidenryoku)
				res = res * ke;
            break;
        }
    }
	cout << res << endl;
}