


#ifndef matrix_h
#define matrix_h

#include <iostream>
#include "string"
using namespace std;

class CMatrix{int nR, nC ;

    
    double** values;
    public:CMatrix();
    ~CMatrix();
    enum MI{MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE};
    CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);
    CMatrix(int nR, int nC, double first, ...);
	CMatrix(int nR, int nC, int first, ...);
    CMatrix(CMatrix& m);
    CMatrix(double d);
    CMatrix(string s);
    void copy(const CMatrix& m);
    void copy(double d);
    void copy(string s);
    void reset();
    string getString();
    CMatrix operator=(const CMatrix& m);
    CMatrix operator=(double d);
    CMatrix operator=(string s);
    void add(const CMatrix& m);
    void operator+=(CMatrix& m);
    void operator+=(double d);
    CMatrix operator+(CMatrix& m);CMatrix operator+(double d);
    void sub(const CMatrix& m);
    void operator-=(CMatrix& m);
    void operator-=(double d);
    CMatrix operator-(CMatrix& m);
    CMatrix operator-(double d);
    void mul(CMatrix& m);
    void operator*=(CMatrix& m);
    void operator*=(double d);
    CMatrix operator*(CMatrix& m);
    CMatrix operator*(double d);
    void div(CMatrix& m);
    void operator/=(CMatrix& m);
    void operator/=(double d);
    CMatrix operator/(CMatrix& m);
    CMatrix operator/(double d);
    void dotSubE(CMatrix& m);
    CMatrix dotSub(CMatrix& m);
    void sub2(CMatrix& m);
    void dotAddE(CMatrix& m);
    CMatrix dotAdd(CMatrix& m);
    void add2(CMatrix& m);
    void dotProductE(CMatrix& m);
    CMatrix dotProduct(CMatrix& m);
    void mul2(CMatrix& m);
    CMatrix operator++(); //Pre Increment
    CMatrix operator++(int); //Post Increment, int is not used
    CMatrix operator--(); //Pre Increment
    CMatrix operator--(int); //Post Increment, int is not used
    CMatrix operator-();CMatrix operator+();
    friend istream& operator >> (istream &is, CMatrix& C); //Stream
    friend ostream& operator << (ostream &os, CMatrix& C); //Stream
    void setSubMatrix(int iR, int iC, CMatrix& m);
    CMatrix getSubMatrix(int r, int c, int nr, int nc);
    CMatrix getCofactor(int r, int c);
	void addColumn(CMatrix& m);
    void addRow(CMatrix& m);
	void setMatrix(int r, int c, CMatrix& m);
    double& operator[](int i){return values[i/nC][i%nC];}
    double& operator()(int i){return values[i/nC][i%nC];}
    double& operator()(int r, int c){return values[r][c];}
    int getn(){return nR*nC;};
    int getnR(){return nR;};
    int getnC(){return nC;};
    double getDeterminant();
    CMatrix getTranspose();
    CMatrix getInverse();
    CMatrix inverse(CMatrix &m);
	void parseMatrix(string s);
};
#endif
