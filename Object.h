#ifndef OBJECT_H_
#define OBJECT_H_

#include "Pipelining.h"
#include "Graphics.h"
#include "MatVec.h"

class Object3d{
    private:
        Vec3* V;
        int no_of_vertices; //point count
    public:
        Object3d(int num){
            no_of_vertices = num;
            V = new Vec3[no_of_vertices];
        }

        void render();
        void SaveObject();
        void LoadObject();


};

#endif // OBJECT_H_

