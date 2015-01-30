#ifndef OBJECT_H_
#define OBJECT_H_

#include "Pipelining.h"
#include "Graphics.h"
#include "MatVec.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

class Surface;

//
//class Edge{
//    public:
//        Vec3 *v1, *v2;
//        list <Surface*> ParentSurface;
//    public:
//        Edge(){}
//        //An Edge may be shared by two triangles at once not more than that.
//        Edge(Vec3* vv1, Vec3* vv2,Surface* S1 = nullptr,Surface* S2 = nullptr){
//            v1 = vv1; v2 = vv2;
//            ParentSurface.push_back(S1);
//            ParentSurface.push_back(S2);
//
//        }
//};

class Surface{
    public:
        Vec3 *v1,*v2,*v3;
        Vec3 norm;
    public:
        Surface(){
            norm = Vec3(0,0,0); //uninitialized normal
        }

        Surface(Vec3* vv1,Vec3* vv2,Vec3* vv3){

            v1 = vv1; v2 = vv2; v3 = vv3;
            //surface is made up from coordiates v1,v2 and v3
            // N = (v2-v1) X (v3-v1)

            norm = v2 - v1;
            Vec3 temp = v3 - v1;

            norm = norm.crossProduct(temp);
        }

};

class Vertex{
    Vec3 v; //the vertex
    vector <Vec3> vn; //the vertex normal
};

class Object3d{
    private:
        vector <Vertex> vertBuffer;   //List of Vertices
        vector <Surface> surfaceBuffer; //list of Surfaces
    public:
        Object3d(){}
        void addVertex(Vec3& v);
        void addSurface(Surface& s);
        void render();
        void drawWire();
        void SaveObject(string filename);
        void LoadObject(string filename);
};

void Object3d::addVertex(Vertex& v){
    vertBuffer.push_back(v);
}

void Object3d::addSurface(Surface& e){
    surfaceBuffer.push_back(e);
}


void Object3d::render(){

    for(unsigned int i=0;i<surfaceBuffer.size();i++)
    {


    }
}

#endif // OBJECT_H_

