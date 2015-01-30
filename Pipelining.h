#ifndef PIPELINING_H_
#define PIPELINING_H_

#include "MatVec.h"


Vec2 World_To_Pixel(const Vec3& source ,          //World pofloat to convert floato pixel pofloat
                        const Vec3& camera,       //Point from where you are watching
                        const Vec3& LookTo,       //Where are we looking at from the camera pos
                        float planeWidth,         //width of the perspective plane
                        float planeHeight,        //height of the perspectice plane
                        float winWidth,           //width of the screen window
                        float winHeight);         //height of the screen window


Vec2 World_To_Pixel(const Vec3& source ,const Vec3& camera, const Vec3& LookTo,float planeWidth, float planeHeight, float winWidth, float winHeight){
    //first determine the World to Camera transforming matrix
    Matrix WtoC(4,4);
    //for that use the concept of N, U and V unit vectors
    Vec3 N,U,V(0,1,0) ;

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


#endif // PIPELINING_H_
