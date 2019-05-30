#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

double f(double x)
{
    return x*exp(x);
}

double de1(double x, double h)
{
    return (1/(2*h))*(f(x+h)-f(x-h));
}

double dei_plus_1(double h, int i, const vector<double> &d, int i_stopnia)
{
    //cout<<"in function - i: "<<i<<" di(h): "<<d[i]<<" di(2h): "<<d[i-1]<<'\n';
    return (pow(4,i_stopnia)*d[i]-d[i-1])/(pow(4,i_stopnia)-1);
}


void liczenie_richardsona()
{
     double x = 2, h = 0.4;

    //double d1 = 0, d2 = 0;
    vector<double> d1, d2, d3, d4;

    cout<<"h = "<<h<<"\n\n\n";

    d1.push_back(de1(x, h));

    cout<<"d1 = "<<setprecision(12)<<d1[0]<<'\n';


    h = 0.2;
    cout<<"\n\n\nh = "<<h<<"\n\n\n";

    d1.push_back(de1(x,h));

    cout<<"d1 = "<<setprecision(12)<<d1[1]<<'\n';

    d2.push_back(dei_plus_1(h,1,d1, 1));

    cout<<"d2 = "<<setprecision(12)<<d2[0]<<'\n';

    h = 0.1;
    cout<<"\n\n\nh = "<<h<<"\n\n\n";

    d1.push_back(de1(x,h));
    cout<<"d1 = "<<setprecision(12)<<d1[2]<<'\n';

    d2.push_back(dei_plus_1(h, 2, d1, 1));
    cout<<"d2 = "<<setprecision(12)<<d2[1]<<'\n';

    d3.push_back(dei_plus_1(h,1,d2, 2));
    cout<<"d3 = "<<setprecision(12)<<d3[0]<<'\n';

    h = 0.05;
    cout<<"\n\n\nh = "<<h<<"\n\n\n";

    d1.push_back(de1(x,h));
    cout<<"d1 = "<<setprecision(12)<<d1[3]<<'\n';

    d2.push_back(dei_plus_1(h,3,d1, 1));
    cout<<"d2 = "<<setprecision(12)<<d2[2]<<'\n';

    d3.push_back(dei_plus_1(h,2,d2, 2));
    cout<<"d3 = "<<setprecision(12)<<d3[1]<<'\n';

    d4.push_back(dei_plus_1(h,1,d3, 3));
    cout<<"d4 = "<<setprecision(12)<<d4[0]<<'\n';


}


double trapezoid_rule(int m, double h, double x)
{
    int n = pow(2,n);

    double result = sin(x);


    for(int i =1; i<n-1; ++i)
    {
        result+=sin(x*i);
    }

    result+=sin(x*(n-1));

    return h*result;
}

void liczenie_romberga()
{
    cout<<trapezoid_rule(2, 1, 0)<<'\n';
}

int main()
{
    //liczenie_richardsona();
    liczenie_romberga();

    return 0;
}
