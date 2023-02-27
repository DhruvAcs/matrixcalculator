#include <iostream>
#include <fstream>
#include <cmath>
#include "Matrix.h"

Matrix::Matrix(){
    //variables
    rows = 0; // the row of the array
    collumns =0; // the collumn of the array
    fill = 0.00; // the number inside tha array
    data = NULL;
}

Matrix::Matrix(unsigned int rowsCount, unsigned int columnsCount,double afill){
    rows = rowsCount;
    collumns = columnsCount;
    fill = afill;
    data = new double *[rows]; // creating the array data to store the matrix
    for( unsigned int x = 0; x< rows;x++){
        data[x] = new double [collumns];
        for( unsigned int y = 0; y<collumns;y++){
            data[x][y] = fill;
        }
    }


}
Matrix::~Matrix(){ // the deconstroctor to remove things from heap and not have any sort of leaks
    for( unsigned int x = 0; x< rows;x++){
        if (data[x] != NULL){
            delete[] data[x];
            data[x] = NULL;
        }
    }
    delete[] data;
    data = NULL;
}



unsigned int Matrix::num_rows()const{ // returns rows 
    return rows;
}
unsigned int Matrix::num_cols()const{ // getter for collumns
    return collumns;
}
double Matrix::get_fill()const{ // getter for the fill number
    return fill;
}
void Matrix::clear(){ // clear resets the matrix
    for( unsigned int x = 0; x< rows;x++){
        delete[] data[x];
        data[x] = NULL;
    }
    delete[] data;
    data = NULL;
    rows =0;
    collumns=0; // reset rows and collumns 

}


bool Matrix::get(unsigned int r, unsigned int c, double &store)const{ // boolean to see the value ofa certain location in the matrix
    if (0<=(int)r && r<rows && 0<=(int)c && c <collumns){
        store = data[r][c];

        return true;

    }
    return false;
}
bool Matrix::set(unsigned int r, unsigned int c, double value){ // sets a value of a specific location of a matrix
    if (0<=(int)r && r<rows && 0<=(int)c && c <collumns){
        data[r][c] = value;
        return true;

    }
    return false;

}
void Matrix::multiple_by_coefficient(const double &num){ // multiple the whole array by a single number using the num as the number
    for( unsigned int x = 0; x< rows;x++){
        for( unsigned int y = 0; y<collumns;y++){
            data[x][y] *= num;
        }
    }


}
bool Matrix::swap_row(unsigned int &first, unsigned int &second){ // swap two of the rows
    if (0<=(int)first && first<rows && 0<=(int)second && second<rows){
        double *temp; // a temp variable used to temporarily store one of the rows
        temp = data[first];
        data[first] = data[second];
        data[second] = temp;
        temp = NULL;
        return true;
    }
    return false;

}
void Matrix::transpose(){ // change the layout
    double **temp; // temp to temporily store
    temp =new double*[collumns];
    for( unsigned int x = 0; x< collumns;x++){
        temp[x] = new double [rows];
        for( unsigned int y = 0; y<rows;y++){
            temp[x][y] = data[y][x]; // for loop that swaps all of the locations to match it by fliping the x and y 
        }
    }   
    for( unsigned int x = 0; x< rows;x++){
        delete[] data[x];
        data[x] = NULL;
    }
    delete[] data;// reset the data
    data = NULL;
    data = temp;

    int tempstore;
    tempstore = rows;
    rows = collumns;
    collumns = tempstore;
    temp = NULL;

}
bool Matrix::add(Matrix &x){ // add two of the matrix's together
    if(rows != x.num_rows() && collumns != x.num_cols()){
        return false;
    }
    for( unsigned int z = 0; z< rows;z++){
        for( unsigned int y = 0; y<collumns;y++){
            double tempstore;
            x.get(z,y,tempstore);
            data[z][y] += tempstore;
        }
    }


    return true;

}
bool Matrix::subtract(Matrix &x){ // subtract two of the matix's
    if(rows != x.num_rows() && collumns != x.num_cols()){
        return false;
    }
    for( unsigned int z = 0; z< rows;z++){
        for( unsigned int y = 0; y<collumns;y++){
            double tempstore;
            x.get(z,y,tempstore);// its the same as the add with a -=
            data[z][y] -= tempstore;
        }
    }


    return true;

}

double* Matrix::get_row(unsigned int r){ // return the entire row
    double* temp = new double[collumns];
    if(0<=(int)r && r<rows){
        for (unsigned int i = 0; i < collumns; i++){
            temp[i] = data[r][i];
        }
    }
    else{
        delete[] temp;
        temp = NULL;
    }
    return  temp;
}
double *Matrix::get_col(unsigned int c){// return an entire collumn
    double *temp=NULL;
    if(0<=(int)collumns&& c<collumns){
        temp = new double [rows];
        for( unsigned int num =0; num < rows;num++){ //longer for loop beacuse we have to access the elemnts by each row first
            temp[num]=data[num][c];
        }
    }
    return temp;
}

Matrix *Matrix::quarter(){ //splits the matrices into 4 matrices by quarters
    Matrix* holder = new Matrix[4]; // the matrix that stores the 5 quarters
    int qrow;
    int qcol;
    if(rows%2 == 0){
        qrow = rows/2; // calculate the rows if they are odd or even by modular
    }
    else{
        qrow = (rows/2)+1; // if odd we round up
    }
    if(collumns%2 == 0){
        qcol = collumns/2;
    }
    else{
        qcol = (collumns/2)+1;
    }

    holder[0]= Matrix(qrow,qcol,0);
    holder[1]= Matrix(qrow,qcol,0); // creating the four quadrants
    holder[2]= Matrix(qrow,qcol,0);
    holder[3]= Matrix(qrow,qcol,0);
//q1
    int r =0; // we have to start at the top left for each of the quarters that is what these are for
    int c=0;
    for( int x =0 ; x<qrow;x++){
        for( int y=0;y<qcol;y++){
            holder[0].set(r,c,data[x][y]);
            c++;
        }
        r++;
        c=0;
    }
//q2
    r =0;
    c=0;
    for( int x =0 ; x<qrow;x++){
        for(int y=qcol;y<(int)collumns;y++){
            holder[1].set(r,c,data[x][y]);
            c++;
        }
        r++;
        c=0;
    }
//q3
    r =0;
    c=0;
    for( int x =qrow-1 ; x<(int)rows;x++){
        for( int y=0;y<qcol;y++){
            holder[2].set(r,c,data[x][y]);
            c++;
        }
        r++;
        c=0;
    }

//q4
    r =0;
    c=0;
    for( int x =qrow-1 ; x<(int)rows;x++){
        for( int y=qcol;y<(int)collumns;y++){
            holder[3].set(r,c,data[x][y]);
            c++;
        }
        r++;
        c=0;
    }
    return holder;
}


// Create the vector as a copy of the given vector. 
void Matrix::copy(const Matrix& m) {
    rows = m.num_rows();
    collumns = m.num_cols();
    data = new double *[rows];
    for( int x = 0; x< (int)rows;x++){
        data[x] = new double [collumns];
        for( int y = 0; y<(int)collumns;y++){
            double tempstore;
            m.get(x,y,tempstore);
            data[x][y] = tempstore;
        }
    }
}

bool Matrix::operator==(const Matrix &m){ // comparing operatoir   
    if (rows != m.num_rows() && collumns != m.num_cols())
        return false;
    for( unsigned int i = 0; i < rows; i++){
        for (unsigned int j = 0; j < collumns; j++){
            double t1,t2;
            t1 = data[i][j];
            m.get(i,j,t2);
            if (t1 != t2)
                return false;
        }
    }
    return true;
}
bool Matrix::operator!=(const Matrix &m){
    return !(*this == m);
}
std::ostream& operator<<(std::ostream& out, const Matrix& m){
    out << std::endl << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
    out << "[ ";
    bool first = true;
    for (unsigned int i = 0; i < m.num_rows(); i++){
        if (!first)
            out << "  ";
        for (unsigned int j = 0; j < m.num_cols(); j++){
            double t1;
            m.get(i,j,t1);
            out << t1 << " ";
        }
        first = false;
        if (i + 1 != m.num_rows())
        out << std::endl;
    }
    out << "]" << std::endl;

    return out;
}

Matrix& Matrix::operator=(const Matrix& m){
  if (this != &m) {
    for (unsigned int i = 0; i < rows; i++){
        delete[] data[i];
        data[i] = NULL;
    }
    if (data != NULL){
        delete[] data;
        data = NULL;
    }
    this->copy(m);
  }
  return *this;
}
