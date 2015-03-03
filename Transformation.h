#pragma once

#include "MatVec.h"
#include <math.h>
const float pi = 3.1415926535897;

void RotateX(Vec3& Point,float theta);
void RotateY(Vec3& Point,float theta);
void RotateZ(Vec3& Point,float theta);
void Translate(Vec3& Point,const Vec3& tMat);

Vec2 World_To_Pixel(const Vec3& source ,          //World pofloat to convert floato pixel pofloat
                        const Vec3& camera,       //Point from where you are watching
                        const Vec3& LookTo,       //Where are we looking at from the camera pos
                        float planeWidth,         //width of the perspective plane
                        float planeHeight,        //height of the perspectice plane
                        float winWidth,           //width of the screen window
                        float winHeight);         //height of the screen window
