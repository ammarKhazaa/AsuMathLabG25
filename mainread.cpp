#include "matrix.h"
#include <stdio.h>
#include "math.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <cstring>
#include "string.h"
#include <stdio.h>
#include <algorithm>
#include <fstream>

using namespace std;

int main(int argv, char* argc[])
{
    
    
    if(argv>1)
    {
//        cout<<argc[1]<<endl;
//
//        string s;
//        ifstream infile(argc[1]);
//        while(getline(infile, s))
//        {
//            cout<<s<<endl;
//        }
//        infile.close();
//        cout<<endl;
        
        
        ifstream infile(argc[1]);
        
        if (infile.good())
        {
            
            string sLine,line;
            getline(infile, sLine);
            //CMatrix a(sLine);
            string a = sLine.substr(4,68);
            CMatrix x(a);
            cout<<"Matrix A : "<<endl;
            cout << x << endl;
            
            for (int lineno = 0; getline (infile,line) && lineno < 7; lineno++)
            {
                if (lineno == 0)
                {
                    string b = line.substr(4,68);
                    CMatrix y(b);
                    cout<<"Matrix B : "<<endl;
                    cout << y << endl;
                    
                    CMatrix c;
                    c = x+y;
                    cout<<"A+B: "<<endl;
                    cout<<c<<endl;
                    
                    CMatrix d;
                    d = x-y;
                    cout<<"A-B: "<<endl;
                    cout<<d<<endl;
                    
                    CMatrix e;
                    e = x*y;
                    cout<<"A*B: "<<endl;
                    cout<<e<<endl;
                    
                    CMatrix g;
                    g = x;
                    
                    CMatrix h;
                    h = c.getTranspose();
                    
                    
                    CMatrix f;
                    x.div(y);
                    f = x;
                    cout<<"A/B: "<<endl;
                    cout<<x<<endl;
                    
                    
                    cout<<"1 ./ A: "<<endl;
                    cout<<g<<endl;
                    
                    
                    
                    cout<<"C': "<<endl;
                    cout<<h<<endl;
                    
                }
            }
            
        }
        
        
        
        infile.close();
    }
    
    return 0;
}
