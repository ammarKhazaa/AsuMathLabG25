#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <cstring>
#include "matrix.h"
#include <fstream>

using namespace std;

bool isNum(const string &c)
{
    return (c.find_first_of("0123456789") != string::npos);
} 
bool isOp(const string&c)
{
	return (c.find_first_of("+-*^/") != string::npos);
}
bool isFunc(const string&c)
{
	return (c.find_first_of("sincostan^") != string::npos);
}
bool isEnum(const string&c)
{
    return (c.find_first_of("rezo") != string::npos);
}

int main(int argv, char* argc[])
{
    
    string line,lines[100]; 
    int x = 0;
    if(argv>1)
    {
        ifstream infile(argc[1]);
        if (infile.fail()) {
		throw("Can't read from file'");
	}
        while (getline(infile, line))
	    {
            lines[x] = line;   
            x++; 			
	    }
    }

    // for(int i = 0 ; i < 13 ; i++)
    // {
    //     cout<<lines[i]<<endl;
    // }
    
    for(int i = 0 ; i < 13 ; i++)
    {
        for(int j = 0 ; j < lines[i].length(); j++)
        {
            if(lines[i][j] == 'A' && lines[i][j+1] == ' ')
            {
                double y,z;
	
                string myText = lines[i];
                double n1 = stod(myText.substr(myText.find_first_of("0123456789"),3));
                double n2 = stod(myText.substr(myText.find_first_of("+-*^/")+2,2));
                string op1 = myText.substr(myText.find_first_of("+-*^/"),1);
                istringstream iss(myText);
                string token;
                while (getline(iss, token, ' '))
                {
                    if(token.find('^') != string::npos)
                        {
                            double x = stod(token.substr(0,token.find('^')));
                            double l = stod(token.substr(token.find('^')+1,token.find(';')));
                            z = pow(x,l);
                            //cout<<z<<endl;
                        }
                    if(isFunc(token))
                    {
                        string fun = token.substr(0,3);
                        if(fun == "sin")
                        {
                            double x = stod(token.substr(4,token.find(')')));
                            y = sin(x);
                            //cout<<y<<endl;
                        }
                        if(fun == "cos")
                        {
                            double x = stod(token.substr(4,token.find(')')));
                            y = cos(x);
                            //cout<<y<<endl;
                        }
                        if(fun == "tan")
                        {
                            double x = stod(token.substr(4,token.find(')')));
                            y = sin(x)/cos(x);
                            //cout<<y<<endl;
                        }
                    }
                }
                double A = n1+n2 * y + z;
                cout<<A<<endl;
            }
            
        }
        if(lines[i][0] == 'D')
            {
                string myText = lines[i];
                char mat = lines[i][0];
                string init = myText.substr(myText.find_first_of("rezo"),3);
                int n1 = stoi(myText.substr(myText.find_first_of("0123456789"),1));
                int n2 = stoi(myText.substr(myText.find_last_of("0123456789"),1));
                cout<<myText<<endl;
                if(init == "ran")
                {
                    CMatrix D(n1,n2,CMatrix::MI_RAND,0.0);
                    cout<< "matrix D :"<<endl;
                    cout<< D;
                }
                if(init == "eye")
                {
                    CMatrix D(n1,n2,CMatrix::MI_EYE,0.0);
                    cout<< "matrix D :"<<endl;
                    cout<< D;
                }
                if(init == "zer")
                {
                    CMatrix D(n1,n2,CMatrix::MI_ZEROS,0.0);
                    cout<< "matrix D :"<<endl;
                    cout<< D;
                }
                if(init == "one")
                {
                    CMatrix D(n1,n2,CMatrix::MI_ONES,0.0);
                    cout<< "matrix D :"<<endl;
                    cout<< D;
                }
            }
            if(lines[i][0] == 'E')
            {
                string myText = lines[i];
                char mat = lines[i][0];
                string init = myText.substr(myText.find_first_of("rezo"),3);
                int n1 = stoi(myText.substr(myText.find_first_of("0123456789"),1));
                int n2 = stoi(myText.substr(myText.find_last_of("0123456789"),1));
                cout<<myText<<endl;
                if(init == "ran")
                {
                    CMatrix E(n1,n2,CMatrix::MI_RAND,0.0);
                    cout<< "matrix E :"<<endl;
                    cout<< E;
                }
                if(init == "eye")
                {
                    CMatrix E(n1,n2,CMatrix::MI_EYE,0.0);
                    cout<< "matrix E :"<<endl;
                    cout<< E;
                }
                if(init == "zer")
                {
                    CMatrix E(n1,n2,CMatrix::MI_ZEROS,0.0);
                    cout<< "matrix E :"<<endl;
                    cout<< E;
                }
                if(init == "one")
                {
                    CMatrix E(n1,n2,CMatrix::MI_ONES,0.0);
                    cout<< "matrix E :"<<endl;
                    cout<< E;
                }
            }

            if(lines[i][0] == 'F')
            {
                string myText = lines[i];
                char mat = lines[i][0];
                string init = myText.substr(myText.find_first_of("rezo"),3);
                int n1 = stoi(myText.substr(myText.find_first_of("0123456789"),1));
                int n2 = stoi(myText.substr(myText.find_last_of("0123456789"),1));
                cout<<myText<<endl;
                if(init == "ran")
                {
                    CMatrix F(n1,n2,CMatrix::MI_RAND,0.0);
                    cout<< "matrix F :"<<endl;
                    cout<< F;
                }
                if(init == "eye")
                {
                    CMatrix F(n1,n2,CMatrix::MI_EYE,0.0);
                    cout<< "matrix F :"<<endl;
                    cout<< F;
                }
                if(init == "zer")
                {
                    CMatrix F(n1,n2,CMatrix::MI_ZEROS,0.0);
                    cout<< "matrix F :"<<endl;
                    cout<< F;
                }
                if(init == "one")
                {
                    CMatrix F(n1,n2,CMatrix::MI_ONES,0.0);
                    cout<< "matrix F :"<<endl;
                    cout<< F;
                }
            }

            if(lines[i][0] == 'G')
            {
                string myText = lines[i];
                char mat = lines[i][0];
                string init = myText.substr(myText.find_first_of("rezo"),3);
                int n1 = stoi(myText.substr(myText.find_first_of("0123456789"),1));
                int n2 = stoi(myText.substr(myText.find_last_of("0123456789"),1));
                cout<<myText<<endl;
                if(init == "ran")
                {
                    CMatrix G(n1,n2,CMatrix::MI_RAND,0.0);
                    cout<< "matrix G :"<<endl;
                    cout<< G;
                }
                if(init == "eye")
                {
                    CMatrix G(n1,n2,CMatrix::MI_EYE,0.0);
                    cout<< "matrix G :"<<endl;
                    cout<< G;
                }
                if(init == "zer")
                {
                    CMatrix G(n1,n2,CMatrix::MI_ZEROS,0.0);
                    cout<< "matrix G :"<<endl;
                    cout<< G;
                }
                if(init == "one")
                {
                    CMatrix G(n1,n2,CMatrix::MI_ONES,0.0);
                    cout<< "matrix G :"<<endl;
                    cout<< G;
                }
            }
    }
}