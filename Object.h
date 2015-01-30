#ifndef OBJECT_H_
#define OBJECT_H_

#include "Graphics.h"
#include "MatVec.h"
#include <vector>
#include <iostream>
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

struct Vertex{
    Vec3 v;
    vector <Vec3> normals;
};

class Object3d{
    private:
        vector <Vertex> vertBuffer;   //List of Vertices
        vector <Vec2> textureBuffer; //List of textures
        vector <Vec3> normBuffer;   //List of normals
        vector <Vec3> surfaceBuffer; //list of Surfaces(vert,texture,norm)
        bool texture;

    public:
        Object3d(){texture = false;}

        void addVertex(Vec3& v){
            vertBuffer.push_back(Vertex());
            unsigned int index = vertBuffer.size()-1;
            vertBuffer[index].v = v;
        }
        void addVertex(unsigned int index, Vec3 norm){
            vertBuffer[index].normals.push_back(norm);
            cout << index << ": " << norm.x << " " << norm.y << " "<<norm.z << endl;
        }

        void addSurface(Vec3& v){surfaceBuffer.push_back(v);}
        void addNormal(Vec3& v){normBuffer.push_back(v);}
        void addTexture(Vec2& v){textureBuffer.push_back(v);}
        void render();
        void drawWire(Vec3& camera,Vec3& LookTo);
        void SaveObject(string filename);
        void LoadObject(string filename);
};



#endif // OBJECT_H_

