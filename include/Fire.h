#pragma once

#include "MatVec.h"
#include "Graphics.h"
#include "Transformation.h"
//#include <random>
#include <vector>
#include <iostream>


//We have a fire particle class here
class fParticle{
    public:
        Vec3 pos,vel;   // pos and vel in 3d
        float i;        //i the intensity
        int lifetime;   //the life time of the particle
        float alpha;    //Transparency of the particle
    public:
        fParticle(){}
        fParticle(const Vec3& ipos,const Vec3& ivel,const float& ii=1, const int& ilifetime=110,const int ialpha=1):
            pos(ipos),vel(ivel),i(ii),lifetime(ilifetime) {}

        //we will simply decrese the life time each time
        //the code exucutes and delete the particle when lifetime == 0
};

class Fire{
    private:
        unsigned int gridSize;
        unsigned int pWidth;
        unsigned int pHeight;
        Screen *S;
        Vec3 gridOrigin;
        Vec3 camera;
        Vec3 LookTo;

    public:
        std::vector <fParticle> fPart;
        unsigned int nOfParticles;

    public:
        Fire(int gSize,Screen *iS,Vec3& cam, Vec3& LT, float Width, float Height);
        void initFire(Vec3& cam, Vec3& LT, float Width, float Height);
        void updateFire(Vec3& cam, Vec3& LT);
        void showFire();
};
