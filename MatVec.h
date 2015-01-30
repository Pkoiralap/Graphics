#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>

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
};



Vec2 World_To_Pixel(const Vec3& source ,          //World pofloat to convert floato pixel pofloat
                        const Vec3& camera,       //Point from where you are watching
                        const Vec3& LookTo,       //Where are we looking at from the camera pos
                        float planeWidth,         //width of the perspective plane
                        float planeHeight,        //height of the perspectice plane
                        float winWidth,           //width of the screen window
                        float winHeight);         //height of the screen window



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
