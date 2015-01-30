#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <iostream>
class Vec2
{
    public: float x, y ;
    public: Vec2(){}
            Vec2(float xx, float yy): x(xx) ,y(yy) {}
};

class Vec3
{
    public: float x,y,z;
    public: Vec3(){}
            Vec3(float xx, float yy, float zz): x(xx) ,y(yy), z(zz) {}
            Vec3 operator + (const Vec3& vec) const {return Vec3(x+vec.x,y+vec.y,z+vec.z); }
            Vec3 operator - (const Vec3& vec) const {return Vec3(x-vec.x,y-vec.y,z-vec.z); }
            Vec3 operator / (const float& d) const {return Vec3(x/d,y/d,z/d);}
            Vec3 operator * (const float& d) const {return Vec3(x*d,y*d,z*d);}
            Vec3 crossProduct (const Vec3& v) const {return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}
            float dotProduct (const Vec3& v) const {return x * v.x + y * v.y + z * v.z;}
            float norm() const {return x*x + y*y + z*z ;}
            float magnitude() const {return sqrt(norm());}
            float& operator [] (int i){return (&x)[i];}
};





class Matrix
{
    private:
        float* data;
        int row, col;
    public:
        Matrix(int rows,int column) : row(rows), col(column)
        {
            data = new float[row*col];
        }

        Matrix(const Matrix& mat)
        {
            row = mat.row;
            col = mat.col;
            data = new float[row*col];
            data = mat.data;
        }

        float& operator() (int r, int c);   //mat(i,j)
        float& operator() (int pos) ;       //mat(pos)
        Matrix operator * (Matrix& mat);    // M = T * M
        Matrix operator + (Matrix& mat);    // C = A + B
        Matrix operator - (Matrix& mat);    // C = A - B
        Matrix operator / (float val);      // C[] = C[] / val
        float dot(Matrix& mat);             // A.dot(B) == (A = A DOT B)
        float magnitude();                  //returns the square root of sum of squares of all element
        void print()
        {
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    std::cout << data[col*i+j] << " ";
                }
                std::cout << std::endl;
            }
        }

};


float Matrix::magnitude()
{
    float res = 0;
    int pos;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            //pos gives the value of this(i,j)

            res += data[pos] * data[pos];

        }
    }
    return sqrt(res);
}

float Matrix::dot(Matrix& mat)
{
    if ((this->row != mat.row) || (this->col != mat.col))
    throw "ERROR";
    int pos;
    float res = 0;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            //pos gives the value of this(i,j)

            res += data[pos] * mat(i,j);
        }
    }
    return res;

}

Matrix Matrix::operator*(Matrix& mat)
{
    if (this->col != mat.row) throw "ERROR";
    int pos;
    Matrix res(row,mat.col);

    for(int i = 0; i< this->row; i++ )
    {
        for (int j= 0; j< mat.col; j++)
        {
            res(i,j) = 0;
            for(int k=0; k< this->col; k++)
            {
                pos = (this->col)*i + k ; // ith row kth column
                res(i,j) += data[pos] * mat(k,j);
            }
        }
    }
    return res;
}

float& Matrix::operator() (int r, int c)
{
    int pos = col* r + c ;
    return data[pos];
}

float& Matrix::operator() (int pos)
{
    return data[pos];
}

Matrix Matrix::operator+(Matrix& mat)
{
    if ((this->row != mat.row) || (this->col != mat.col))
        throw "ERROR";
    Matrix res(this->row,this->col);
    int pos;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            res(i,j) = data[pos] + mat(i,j);
        }
    }
    return res;
}

Matrix Matrix::operator - (Matrix& mat)
{
    if ((this->row != mat.row) || (this->col != mat.col))
        throw "ERROR";
    Matrix res(this->row,this->col);
    int pos;
    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            res(i,j) = data[pos] - mat(i,j);
        }
    }
    return res;
}

Matrix Matrix::operator / (float val)
{
    Matrix res(this->row,this->col);
    int pos;

    for (int i =0;i < this->row; i++)
    {
        for (int j=0;j<this->col;j++)
        {
            pos = (this->col)*i + j;
            res(i,j) = data[pos] / val ;
        }
    }

    return res;
}

//
//int main()
//{
//    Matrix m(3,3);
//    Matrix n(3,3);
//
//    m(0) = 1; m(1) = 2; m(2) = 3;
//    m(3) = 4; m(4) = 5; m(5) = 6;
//    m(6) = 2; m(7) = 4; m(8) = 5;
//
//    n(0) = 1; n(1) = 0; n(2) = 0;
//    n(3) = 0; n(4) = 1; n(5) = 0;
//    n(6) = 0; n(7) = 0; n(8) = 1;
//
//    n = m * n;
//
//    for (int i =0; i< 3; i++,std::cout << std::endl)
//        for (int j =0; j< 3; j++)
//            std::cout << n(i,j) << " ";
//
//}

#endif // MATRIX_H_
