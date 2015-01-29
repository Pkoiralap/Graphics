//#include "Graphics.h"
//#include "Object.h"

#include "Pipelining.h"
#include "Graphics.h"


int main(){
    Vec3 camera(10,5,-15);
    Vec3 LookTo(0,0,0);

//    Vec3 O(0,0,0), X(40,0,0), Y(0,40,0), Z(0,0,40);
//    Vec2 o = World_To_Pixel(O,camera,3,3,640,480);
//    Vec2 x = World_To_Pixel(X,camera,3,3,640,480);
//    Vec2 y = World_To_Pixel(Y,camera,3,3,640,480);
//    Vec2 z = World_To_Pixel(Z,camera,3,3,640,480);
//
    Screen S(1024,840);
    Color C(255,0,0);
//    S.clrscr();
//    S.line(o,x,C);
//    C = Color(0,255,0);
//    S.line(o,y,C);
//    C = Color(0,0,255);
//    S.line(o,z,C);



    Vec3 p3[4] = {Vec3(0,0,0),Vec3(0,5,0),Vec3(5,0,0),Vec3(5,5,5)};
    Vec2 p2[4];

    for (int i=0;i<4;i++)
        p2[i] = World_To_Pixel(p3[i],camera,2,2,640,480);


    C.r = 255; C.g = 0; C.b = 0;
    S.line(p2[0],p2[1],C);
    C.g = 255; C.r = 0; C.b = 0;
    S.line(p2[1],p2[2],C);
    C.b = 255; C.r = 0; C.r = 0;
    S.line(p2[2],p2[0],C);


    C.r = 255; C.g = 255; C.b = 255;
    for(int i=0;i<3;i++)
        S.line(p2[3],p2[i],C);

    S.WaitQuit();

    return 0;
}
