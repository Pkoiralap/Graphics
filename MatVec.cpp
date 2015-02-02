#include "MatVec.h"




Vec2 World_To_Pixel(const Vec3& source ,const Vec3& camera, const Vec3& LookTo,float planeWidth, float planeHeight, float winWidth, float winHeight){
    //first determine the World to Camera transforming matrix
    Matrix WtoC(4,4);
    //for that use the concept of N, U and V unit vectors
    Vec3 N,U,V(0,1,0);

    //calculate the N unit vector
    //N is the vector from LookTo point to Camera point
    N = camera-LookTo;
    N = N/ N.magnitude();

    //U = V X N
    U = V.crossProduct(N);
    U = U / U.magnitude();


    //readjust the V vector
    V = N.crossProduct(U);
//
//    std::cout << U.x << " "<< U.y << " "<< U.z << std::endl;
//    std::cout << V.x << " "<< V.y << " "<< V.z << std::endl;
//    std::cout << N.x << " "<< N.y << " "<< N.z << std::endl;
//    std::cout << std::endl <<std::endl ;

    //Transpose matrix from World co-ordinate to View co-ordinate
    Matrix T(4,4);
    T(0,0) = 1 ; T(0,1) = 0; T(0,2) = 0; T(0,3) = -camera.x;
    T(1,0) = 0 ; T(1,1) = 1; T(1,2) = 0; T(1,3) = -camera.y;
    T(2,0) = 0 ; T(2,1) = 0; T(2,2) = 1; T(2,3) = -camera.z;
    T(3,0) = 0 ; T(3,1) = 0; T(3,2) = 0; T(3,3) = 1;

    //Rotation Matrix
    Matrix R(4,4);
    R(0,0) = U[0] ; R(0,1) = U[1]; R(0,2) = U[2]; R(0,3) = 0;
    R(1,0) = V[0] ; R(1,1) = V[1]; R(1,2) = V[2]; R(1,3) = 0;
    R(2,0) = N[0] ; R(2,1) = N[1]; R(2,2) = N[2]; R(2,3) = 0;
    R(3,0) = 0 ; R(3,1) = 0; R(3,2) = 0; R(3,3) = 1;


    //Calculating the WtoC matrix W = T*R (rotate and then translate)
    WtoC = R*T;
//
//    std::cout << std::endl << " MATRIX START" << std::endl;
//    WtoC.print();
//    std::cout <<"MATRIX END"<< std::endl << std::endl;

    Matrix S(4,1); //The source point in matrix form
    S(0) = source.x ; S(1) = source.y; S(2) = source.z ; S(3) = 1;

    S = WtoC * S;
//    //S now represents the camera co-ordinate system's values
//    std::cout << S(0) << " " << S(1) << " "<<S(2) <<std::endl;
//    //calculate the screen pixels


    Vec2 retVal;
    retVal.x = S(0) / -S(2);
    retVal.y = S(1) / -S(2);

    //normalize the screen pixels
    retVal.x = (retVal.x + planeWidth*0.5)/planeWidth;
    retVal.y = (retVal.y + planeHeight*0.5)/planeHeight;

    //now to original screen pos in computer
    retVal.x = (int)(retVal.x * winWidth);
    retVal.y = (int)((1-retVal.y) * winHeight);

    return retVal;
}



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
