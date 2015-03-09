#include "MatVec.h"

//We have a fire particle class here
class fParticle{
    public:
        Vec3 pos,vel;   // pos and vel in 3d
        float i;        //i the intensity
        int lifetime;   //the life time of the particle
    public:
        fParticle(){}
        fParticle(const Vec3& ipos,const Vec3& ivel,const float& ii, const int& ilifetime):
            pos(ipos),vel(ivel),i(ii),lifetime(ilifetime) {}

}
