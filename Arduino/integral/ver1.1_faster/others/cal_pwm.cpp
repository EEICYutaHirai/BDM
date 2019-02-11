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
double ke = 0.03;

const double MIN_WEIGHT = 500.;
const double MAX_WEIGHT = 10000.;

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

    ifstream in("data.txt");

    cin.rdbuf(in.rdbuf());

    for (int i = 0; i < N_int; i++)
    {
        complex<double> tmp;
        cin >> tmp;
        //tmp = 100. * sin(i * 100. / (double)T);
        x[i] = tmp;
    }

    cin >> T;
    T /= 1000.;

	double weight;
	cin >> weight;

    fft(x, y, N_int);

    double Ec = 0.;
    for (int i = 1; i < N_int; i++)
    {
        //cout << (double)i / T << "\t" << abs(y[i]) << endl;
        if (abs(y[i]) > 3.)
        {
            //rad/sで計算
            Ec = (double)i * 6.28 * ke / T / 18.;
            //Ec(gyaku kidenryoku)
            break;
        }
        //cout << (double)i * 6.28 * ke / T / 18. << "\t" << abs(y[i]) << endl;
        //cout << (double)i / T << "\t" << abs(y[i]) << endl;
    }
	//res = res>12?0:res;
    //cout << res << endl;
	//cal pwm
	int pwm = 0;
	int limit_pwm = 255./12.*(5.+Ec);
	if(weight<MIN_WEIGHT){
		pwm = 0;
	}else if(weight >= MAX_WEIGHT){
		pwm = limit_pwm;
	}else{
		int ideal_value = (weight-MIN_WEIGHT)*255./(MAX_WEIGHT-MIN_WEIGHT);
		pwm = limit_pwm > ideal_value ? ideal_value : limit_pwm;
	}
	cout << pwm << endl;
}