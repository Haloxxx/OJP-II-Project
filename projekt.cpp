#include <iostream>
#include <vector>
#include "Window.hpp"
#include "Graph.hpp"
#include "Simple_window.hpp"





template<typename TypZmiennych>
double de1(function<TypZmiennych(TypZmiennych)> f, double x, double h)
{
    return (1/(2*h))*(f(x+h)-f(x-h));
}

template<typename TypZmiennych>
double de1pp(function<TypZmiennych(TypZmiennych)> f, double x, double h)
{
    return (1/(h*h))*(f(x+h)-2*f(x)+f(x-h));
}


typedef double de_function(function<double(double)>, double, double);


double dei_plus_1(double h, int i, const vector<double> &d, int i_stopnia)
{
    return (pow(4,i_stopnia)*d[i]-d[i-1])/(pow(4,i_stopnia)-1);
}


template<typename TypZmiennych>
vector<double> base(function<TypZmiennych(TypZmiennych)> f, double x, double h_start, int n, de_function de)
{
    vector<double> d1;

    double h = h_start;

    for(int i = 0; i<n; ++i)
    {
        d1.push_back(de(f, x, h));
        h/=2;
    }

    return d1;
}


vector<vector<double>> next(double x, double h_start, int n, const vector<double> &d1)
{
    double h = h_start/2;

    vector<vector<double>> de;

    for(int i =0; i<n-1; ++i)
    {
        vector<double> di;

        for(int j = 0; j<n-1-i; ++j)
        {
            if(i==0) di.push_back(dei_plus_1(h,j+1,d1, i+1));
            else di.push_back(dei_plus_1(h,j+1,de[i-1], i+1));
            h=h/2;
        }

        de.push_back(di);
        h = h_start/(2*pow(2,i));
    }

    return de;
}


template<typename TypZmiennych>
vector<vector<double>> Richardson_fp(function<TypZmiennych(TypZmiennych)> f, double x, double h_start, int n)
{
    if(h_start>=1) error("h is invalid!");

    vector<double> d1 = base(f, x, h_start, n, de1);

    vector<vector<double>> d2 = next(x, h_start, n, d1);

    vector<vector<double>> result;
    result.push_back(d1);

    for(int i =0; i<d2.size(); ++i)
    {
        result.push_back(d2[i]);
    }

    return result;
}

template<typename TypZmiennych>
vector<vector<double>> Richardson_fpp(function<TypZmiennych(TypZmiennych)> f, double x, double h_start, int n)
{
    if(h_start>=1) error("h is invalid!");

    vector<double> d1 = base(f, x, h_start, n, de1pp);

    vector<vector<double>> d2 = next(x, h_start, n, d1);

    vector<vector<double>> result;
    result.push_back(d1);

    for(int i =0; i<d2.size(); ++i)
    {
        result.push_back(d2[i]);
    }

    return result;
}


void file_save(vector<vector<double>> dp, vector<vector<double>> dpp, int n)
{
    ofstream ist {"f'.txt"};
    ofstream ist2 {"f''.txt"};


    for(int j = 0; j < dp.size(); ++j)
    {
        for(int i = 0; i < n-j; ++i)
        {
            ist<<setw(8)<<dp[i][j]<<" ";
        }
        ist<<'\n';
    }

    for(int j = 0; j < dpp.size(); ++j)
    {
        for(int i = 0; i < n-j; ++i)
        {
            ist2<<setw(8)<<dpp[i][j]<<" ";
        }
        ist2<<'\n';
    }

}


void draw(Graph_lib::Fct f, double x_point)
{
    Point tl {100,100};

    Simple_window win {tl,600,400,"Canvas"};
    //Graph_lib::Window win {tl,600,400,"Canvas"};

    Graph_lib::Function func {f, x_point-50,x_point+50,Point{270-int(x_point)*50,300+int(f(x_point))*50},1000,50,50};
    

    win.attach(func);


    Graph_lib::Line poi {{270,400},{270,0}};

    poi.set_color(Graph_lib::Color::red);

    win.attach(poi);


    Graph_lib::Text t {Point{280,370}, "x0"};
    t.set_color(Graph_lib::Color::red);
    win.attach(t);


    win.wait_for_button();
}



double f1(double x)
{
    return x*exp(x);
}

double f2(double x)
{
    if(x>5) return 0.5*x;
    
    else return 1;
}


int f3(int x)
{
    return 1;
}







int main()
{

    double x_point = 2.0;
    double h_start = 0.4;
    int n = 4;
    int negative = 0;
    
    
    //////////////////////////////////////////////////////////////////
    ///////////   Liczenie pierwszej i drugiej pochodnej /////////////
    //////////////////////////////////////////////////////////////////


    vector<vector<double>> fp = Richardson_fp <double>(f1,x_point,h_start,n);
    vector<vector<double>> fpp = Richardson_fpp <double>(f1,x_point,h_start,n);



    //////////////////////////////////////////////////////////////////
    //////////////// Rysowanie poglądowego wykresu /////////////////////
    //////////////////////////////////////////////////////////////////


    draw(f1, x_point);

    //////////////////////////////////////////////////////////////////
    /////////////////////   Wyświetlanie wynikow ////////////////////
    //////////////////////////////////////////////////////////////////


    cout<<"f'("<<x_point<<") = "<<fp[n-1][0]<<'\n';
    cout<<"f''("<<x_point<<") = "<<fpp[n-1][0]<<'\n';


    cout<<"\n\n\n";


    //////////////////////////////////////////////////////////////////
    /////////////////////   Zapisywanie wynikow ////////////////////
    //////////////////////////////////////////////////////////////////


    cout<<"Zapisać od pliku? (t/n): ";

    char input;
    
    while(cin>>input)
    {
        if(input=='t') {file_save(fp, fpp, n); break; }
        if(input=='n') break;
        cout<<"Zapisać od pliku? (t/n): ";
    }

    
}