#include "MatVec.h"

float Matrix::magnitude(){
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

float Matrix::dot(Matrix& mat){
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

const float Matrix::operator() (int r, int c) const
{
    int pos = col* r + c ;
    return data[pos];
}

float& Matrix::operator() (int pos)
{
    return data[pos];
}

const float Matrix::operator() (int pos) const
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
