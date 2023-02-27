#ifndef __Matrix_h
#define __Matrix_h
#include <iostream>
#include <string>
using namespace std;

class Matrix {
public:
    Matrix();
    Matrix(unsigned int rowsCount, unsigned int columnsCount,double afill);
    Matrix(const Matrix& m) { copy(m); }

    ~Matrix();

    //accessors use get_ name of private()
    unsigned int num_rows()const; // returns rows
    unsigned int num_cols()const;// retuen collumn
    double get_fill()const; // return fill

    //modifiers change the variables
    void clear();//clear the matrix
    bool get(unsigned int r, unsigned int c, double &store)const;//get a location in the matrix
    bool set(unsigned int r, unsigned int c, double value);//
    void multiple_by_coefficient(const double &num);
    bool swap_row(unsigned int &first, unsigned int &second);
    void transpose();
    bool add(Matrix &x);
    bool subtract(Matrix &x);
    double *get_row(unsigned int r);
    double *get_col(unsigned int c);
    Matrix *quarter();
    Matrix& operator=(const Matrix& m);
    bool operator==(const Matrix& m);
    bool operator!=(const Matrix& m);
    double& operator[](unsigned int i) { return *data[i]; }
    double& operator[](unsigned int i) const {return *data[i];}
    friend std::ostream& operator<<(std::ostream& out, const Matrix& m); 
    




private:
unsigned int rows;
unsigned int collumns;
double fill;
double **data; // the actual array for matrix
void copy(const Matrix& m); 


};



#endif
