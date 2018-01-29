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

using namespace std;
//#define max(100,100);

CMatrix::CMatrix()
{
    nR = nC = 0;
    values = NULL;
}
CMatrix::~CMatrix()
{
    reset();
}
CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue)
{
    this->nR = nR;
    this->nC = nC;
    if((nR*nC)==0)
    {
        values=NULL;
        return;
    }
    values = new double*[nR];
    for(int iR=0; iR<nR; iR++)
    {
        values[iR] = new double[nC];
        for(int iC=0; iC<nC; iC++)
        {
            switch(initialization)
            {
            case MI_ZEROS:
                values[iR][iC] = 0;
                break;
            case MI_ONES:
                values[iR][iC] = 1;
                break;
            case MI_EYE:
                values[iR][iC] = (iR==iC)?1:0;
                break;
            case MI_RAND:
                values[iR][iC] = (rand()%1000000)/1000000.0;
                break;
            case MI_VALUE:
                values[iR][iC] = initializationValue;
                break;
            }
        }
    }
}


CMatrix::CMatrix(int nR, int nC, double first, ...)
{
    this->nR = nR;
    this->nC = nC;
    if((nR*nC)==0)
    {
        values=NULL;
        return;
    }
    values = new double*[nR];
    va_list va;
    va_start(va, first);
    for(int iR=0; iR<nR; iR++)
    {
        values[iR] = new double[nC];
        for(int iC=0; iC<nC; iC++)
        {
            values[iR][iC] = (iC==0&&iR==0)?first:va_arg(va, double);
        }
    }
    va_end(va);
}

/*
CMatrix::CMatrix(int nR, int nC, int first, ...)
{
	this->nR = nR;
	this->nC = nC;
	if ((nR*nC) == 0) { values = NULL; return; }
	values = new int*[nR];
	va_list va;
	va_start(va, first);
	for (int iR = 0; iR<nR; iR++)
	{
		values[iR] = new int[nC];
		for (int iC = 0; iC<nC; iC++)
		{
			values[iR][iC] =  va_arg(va, int);
		}
	}
	va_end(va);
}
*/

CMatrix::CMatrix(CMatrix& m)
{
    nR = nC = 0;
    values = NULL;
    copy(m);
}
CMatrix::CMatrix(std::string s)
{
    nR = nC = 0;
    values = NULL;
    copy(s);
}
void CMatrix::copy(const CMatrix& m)
{
    reset();
    this->nR = m.nR;
    this->nC = m.nC;
    if((nR*nC)==0)
    {
        values=NULL;
        return;
    }
    values = new double*[nR];
    for(int iR=0; iR<nR; iR++)
    {
        values[iR] = new double[nC];
        for(int iC=0; iC<nC; iC++)
        {
            values[iR][iC] = m.values[iR][iC];
        }
    }
}

CMatrix::CMatrix(double d)
{
    nR = nC = 0;
    values = NULL;
    copy(d);
}
void CMatrix::copy(double d)
{
    reset();
    this->nR = 1;
    this->nC = 1;
    values = new double*[1];
    values[0] = new double[1];
    values[0][0] = d;
}


/*void CMatrix::copy(string s){
	reset();
	cout << 1 << endl << s.length()+1;
	char* buffer = new char[s.length()+1];
	strcpy_s(buffer,sizeof buffer,s.c_str());
	char* lineContext;
	char* lineSeparators = ";\r\n";
	cout << 2;
	char* line = strtok_s(buffer, lineSeparators, &lineContext);
	while(line){
		CMatrix row;
		char* context;
		char* separators = " []";
		cout << 3;
		char* token = strtok_s(line, separators, &context);
		while(token){
			CMatrix item = atof(token);
			row.addColumn(item);
			cout << 4;
			token = strtok_s(NULL, separators, &context);
		}
		if(row.nC>0 && (row.nC==nC || nR==0)) addRow(row);
		cout << 5;
		line = strtok_s(NULL, lineSeparators, &lineContext);
	}
	delete[] buffer;
}*/

void CMatrix::copy(string s)
{
    int sLength = s.length();
    string sValues[32][32];
    int iC = 0, iR = 0, rC = 0;
    for (int i = 0; i < sLength; i++)
    {
        char c = s[i];
        if (c == ';')
        {
            iR++;
            if (iC != rC) throw("YOU TRIED TO TRICK ME");
            iC = 0;
        }
        else if (c == ' ' && s[i-1] != ';') iC++;
        else if (c == '[' || c == ']');
        else sValues[iR][iC] += c;
        if (rC < iC) rC = iC;
    }
    nC = iC + 1;
    nR = iR + 1;
    values = new double* [nR];
    for (iR = 0; iR < nR; iR++)
    {
        values[iR] = new double [nC];
        for (iC = 0; iC < nC; iC++)
            values[iR][iC] = atof(sValues[iR][iC].c_str());
    }
    
}



void CMatrix::reset()
{
    if(values)
    {
        for(int i=0; i<nR; i++)delete[] values[i];
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}
string CMatrix::getString()
{
    string s;
    for(int iR=0; iR<nR; iR++)
    {
        for(int iC=0; iC<nC; iC++)
        {
            char buffer[50];
            sprintf(buffer,  "%g\t", values[iR][iC]);
            s += buffer;
        }
        s+="\n";
    }
    return s;
}


CMatrix CMatrix::operator=(const CMatrix& m)
{
    copy(m);
    return *this;
}
CMatrix CMatrix::operator=(double d)
{
    copy(d);
    return *this;
}
CMatrix CMatrix::operator=(string s)
{
    copy(s);
    return *this;
}


void CMatrix::add(const CMatrix& m)
{
    if(nR!=m.nR||nC!=m.nC)throw("Invalid matrix dimension");
    for(int iR=0; iR<nR; iR++)
        for(int iC=0; iC<nC; iC++)
            values[iR][iC] += m.values[iR][iC];
}
void CMatrix::operator+=(CMatrix& m)
{
    add(m);
}
void CMatrix::operator+=(double d)
{
    add(CMatrix(nR, nC, MI_VALUE, d));
}
CMatrix CMatrix::operator+(CMatrix& m)
{
    CMatrix r = *this;
    r+=m;
    return r;
}
CMatrix CMatrix::operator+(double d)
{
    CMatrix r = *this;
    r+=d;
    return r;
}


void CMatrix::mul(CMatrix& m)
{
    if(nR!=m.nR||nC!=m.nC)throw("Invalid matrix dimension");
    CMatrix r(nR, m.nC);
    for(int iR=0; iR<r.nR; iR++)
        for(int iC=0; iC<r.nC; iC++)
        {
            r.values[iR][iC] = 0;
            for(int k=0; k<m.nC; k++)
                r.values[iR][iC] += values[iR][k]*m.values[k][iC];
        }
    copy(r);
}
void CMatrix::operator*=(CMatrix& m)
{
    mul(m);
}
void CMatrix::operator*=(double d)
{
    for(int iR=0; iR<nR; iR++)
        for(int iC=0; iC<nC; iC++)
            values[iR][iC] *= 9;
}
CMatrix CMatrix::operator*(CMatrix& m)
{
    CMatrix r = *this;
    r*=m;
    return r;
}
CMatrix CMatrix::operator*(double d)
{
    CMatrix r = *this;
    r*=d;
    return r;
}


CMatrix CMatrix::operator++()
{
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return *this;
}
CMatrix CMatrix::operator++(int)
{
    CMatrix C = *this;
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return C;
}
CMatrix CMatrix::operator--()
{
    add(CMatrix(nR, nC, MI_VALUE, -1.0));
    return *this;
}
CMatrix CMatrix::operator--(int)
{
    CMatrix r = *this;
    add(CMatrix(nR, nC, MI_VALUE, -1.0));
    return r;
}
CMatrix CMatrix::operator-()
{
    for(int iR=0; iR<nR; iR++)
        for(int iC=0; iC<nC; iC++)
            values[iR][iC] = -values[iR][iC];
    return *this;
}
void CMatrix::operator -=(double d)
{
    sub(CMatrix(nR, nC, MI_VALUE, d));
}

void CMatrix::operator-=(CMatrix& m)
{
    sub(m);
}

void CMatrix::sub(const CMatrix& m)
{
    if(nR!=m.nR||nC!=m.nC)throw("Invalid matrix dimension");
    for(int iR=0; iR<nR; iR++)
        for(int iC=0; iC<nC; iC++)
            values[iR][iC] -= m.values[iR][iC];
}
CMatrix CMatrix::operator-(CMatrix& m)
{
    CMatrix r = *this;
    r -= m;
    return r;
}
CMatrix CMatrix::operator+()
{
    return *this;
}




void CMatrix::setSubMatrix(int r, int c, CMatrix& m)
{
    if((r+m.nR)>nR || (c+m.nC)>nC)throw("Invalid matrix dimension");
    for(int iR=0; iR<m.nR; iR++)
        for(int iC=0; iC<m.nC; iC++)
            values[r+iR][c+iC] = m.values[iR][iC];
}
CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc)
{
    if((r+nr)>nR || (c+nc)>nC)throw("Invalid matrix dimension");
    CMatrix m(nr, nc);
    for(int iR=0; iR<m.nR; iR++)
        for(int iC=0; iC<m.nC; iC++)
            m.values[iR][iC] = values[r+iR][c+iC];
    return m;
}


void CMatrix::addColumn(CMatrix& m)
{
    CMatrix n(max(nR, m.nR), nC+m.nC);
    n.setSubMatrix(0, 0, *this);
    n.setSubMatrix(0, nC, m);
    *this = n;
}
void CMatrix::addRow(CMatrix& m)
{
    CMatrix n(nR+m.nR, max(nC, m.nC));
    n.setSubMatrix(0, 0, *this);
    n.setSubMatrix(nR, 0, m);
    *this = n;
}

void CMatrix::parseMatrix(string s)   // [1 2 3; 2 3 6; 8 9 4] => nR, nC, values[][]
{
    bool column = false;
    int sLength = s.length();
    char* sValues[32][32];
    int iC = 0, iR = 0, rC = 0;
    for (int i = 0; i < sLength; i++)
    {
        char c = s[i];
        if (c == ';')
        {
            iR++;
            if (iC != rC) throw("YOU TRIED TO TRICK ME");
            iC = 0;
        }
        else if (c == ' ' && iC != 0){
            column = true;
            iC++;
        }
        else if (c == ' ');
        else {
            sValues[iR][iC] += c;
            column = false;
        }
        if (rC < iC) rC = iC;
    }
    if (column) iC--;
    nC = iC + 1;
    nR = iR + 1;
    for (iR = 0; iR < nR; iR++)
        for (iC = 0; iC < nC; iC++)
            values[iR][iC] = atof(sValues[iR][iC]);
}


CMatrix CMatrix::getCofactor(int r, int c)
{
    if(nR<=1 && nC<=1)throw("Invalid matrix dimension");
    CMatrix m(nR-1, nC-1);
    for(int iR=0; iR<m.nR; iR++)for(int iC=0; iC<m.nC; iC++)
        {
            int sR = (iR<r)?iR:iR+1;
            int sC = (iC<c)?iC:iC+1;
            m.values[iR][iC] = values[sR][sC];
        }
    return m;
}
double CMatrix::getDeterminant()
{
    if(nR!=nC)throw("Invalid matrix dimension");
    if(nR==1&&nC==1)return values[0][0];
    double value = 0, m = 1;
    for(int iR=0; iR<nR; iR++)
    {
        value+= m * values[0][iR] * getCofactor(0, iR).getDeterminant();
        m *= -1;
    }
    return value;
}

/*
void CMatrix::getTranspose(CMatrix m)
{
    
    if(this != &m)
    {
        *this = m;
    }
    
    for(int r = 0 ; r < nR ; r++)
    {
        for(int c = 0 ; c < nC ; c++)
        {
            this->values[r][c] = m.values[c][r];
        }
    }
}

void CMatrix::getInverse(CMatrix m)
{
    *this = m;
    double det = this->getDeterminant();
    if(!det) {cout<<"Invalid Matrix Operation";}
    else {
        double sign_correction = 1;
        for(int i = 0 ; i < nR ; i++)
        {
            for(int j = 0 ; j < nC ; j++)
            {
                this->values[i][j] = sign_correction * m.getCofactor(i,j).getDeterminant();
                sign_correction *= -1;
            }
        }
        *this /= det;
        this->getTranspose(*this);}
}
 */

CMatrix CMatrix::getInverse()
{
    if (nR != nC)throw("Invalid matrix dimension");
    double Determinant = getDeterminant();
    if (Determinant == 0) throw("Invalid matrix Inverse");
    CMatrix r(nR, nC);
    int m = 1;
    for (int iR = 0; iR<nR; iR++)
        for (int iC = 0; iC<nC; iC++)
        {
            r.values[iC][iR] = (m*getCofactor(iR, iC).getDeterminant()) / Determinant;
            m *= -1;
        }
    
    return r;
}

CMatrix CMatrix::getTranspose()
{
    CMatrix M(nC, nR);
    for (int iR = 0; iR<nR; iR++)
        for (int iC = 0; iC<nC; iC++)
            M.values[iC][iR] = values[iR][iC];
    return M;
}
void CMatrix::div(CMatrix& m)
{
    m.getInverse();
    this->mul(m);
}


istream& operator >> (istream &is, CMatrix& m)
{
    string s;
    getline(is, s, ']');
    s+="]";
    m = CMatrix(s);
    return is;
}
ostream& operator << (ostream &os, CMatrix& m)
{
    os<<m.getString();
    return os;
}
//-----------------DOT MUL-------------------//
			void CMatrix::mul2(CMatrix& m)
			{
				if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
				CMatrix r(nR, m.nC);
				for (int iR = 0; iR<r.nR; iR++)
				for (int iC = 0; iC<r.nC; iC++)
				{
					
					r.values[iR][iC] = values[iR][iC] * m.values[iR][iC];
				
				}
				copy(r);
			}
			void CMatrix::dotProductE(CMatrix& m)
			{
				mul2(m);
			}
			CMatrix CMatrix::dotProduct(CMatrix& m)
			{
				CMatrix r = *this; r.dotProductE(m); return r;
			}
			
//-------------------Dot Add--------------//
			void CMatrix::add2(CMatrix& m)
			{
				if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
				for (int iR = 0; iR<nR; iR++)
				for (int iC = 0; iC<nC; iC++)values[iR][iC] += m.values[iR][iC];
			}
			void CMatrix::dotAddE(CMatrix& m)
			{ add2(m); }
			
			CMatrix CMatrix::dotAdd(CMatrix& m)
			{ CMatrix r = *this; r.dotAddE(m); return r; }
			

//-----------------------DOT SUB---------//
			
			void CMatrix::sub2(CMatrix& m)
			{
				if (nR != m.nR || nC != m.nC)throw("Invalid matrix dimension");
				for (int iR = 0; iR<nR; iR++)
				for (int iC = 0; iC<nC; iC++)values[iR][iC] -= m.values[iR][iC];
			}
			void CMatrix::dotSubE(CMatrix& m)
			{
				sub2(m);
			}

			CMatrix CMatrix::dotSub(CMatrix& m)
			{
				CMatrix r = *this; r.dotSubE(m); return r;
			}


			

//-------------------------------------//

}
