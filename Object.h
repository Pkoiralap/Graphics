#ifndef OBJECT_H_
#define OBJECT_H_

#include "Graphics.h"
#include "MatVec.h"
#include "Transformation.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

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

//The vertex has a vertex and vertex normal
struct Vertex{
    Vec3 v;     //the 3d point of the normal
    Vec3 norm; // The vertex normal
    int cnt; //cnt keeps track of the shared surfaces

    Vertex(){
        norm = Vec3(0,0,0);
    }

    Vertex(const Vec3& input){
        v = input;
    }
};

//Edge is used in scanline filling algorithm
struct Edge{
    Vec2 *v1,*v2; //we have two vertices
    float yMin,yMax; //we have min y and max y
    float xMin,xMax; // this is the x-value
    float slope; //And yes the Edge has a slope as well

    //the initializer function
    Edge(){
        v1 = NULL;
        v2 = NULL;
    }

    Edge(Vec2* a, Vec2* b):v1(a),v2(b){
        //if the y value of v1 is greater, ymax is v1->y
        if (v1->y > v2->y){
            yMax = v1->y;
            yMin = v2->y;
        }
        //else ymax is v2->y
        else{
            yMax = v2->y;
            yMin = v1->y;
        }

        //if the x value of v1 is greater, xMax is v1->x
        if (v1->x > v2->x){
            xMax = v1->x;
            xMin = v2->x;
        }
        //else ymax is v2->y
        else{
            xMax = v2->x;
            xMin = v1->x;
        }



        slope = (v2->y - v1->y) / (v2->x - v1->x);
    }

    //simply a copy overloaded with =
    void operator = (Edge Ed){
        v1 = Ed.v1; v2 = Ed.v2;
        yMin = Ed.yMin; yMax = Ed.yMax;
        xMin = Ed.xMin; xMax = Ed.xMax;
        slope = Ed.slope;
    }

};

class Object3d{
    private:
        vector <Vertex> vertBuffer;     //List of Vertices
        vector <Vec2> textureBuffer;    //List of textures
        vector <Vec3> normBuffer;       //List of normals
        vector <Vec3> surfaceBuffer;    //list of Surfaces(vert,texture,norm)
        vector <Vec3> vertexNorm;       //List of vertex normal

        bool texture;

    //adders
    public:
        Object3d(){texture = false;}
        void addVertex(Vec3& v){vertBuffer.push_back(Vertex(v));}
        void addSurface(Vec3& v){surfaceBuffer.push_back(v);}
        void addNormal(Vec3& v){normBuffer.push_back(v);}
        void addTexture(Vec2& v){textureBuffer.push_back(v);}

    //file manipulators
    public:
        void SaveObject(string filename);
        void LoadObject(string filename);

    //Object fillers
    public:
        void drawWire(Screen* S,Vec3& camera,Vec3& LookTo);
        void fillObject(Screen* S,Vec3& camera,Vec3& LookTo,Vec3& Lpos);
        void render(Screen* S,Vec3& camera,Vec3& LookTo);
        void drawSpan(Screen* S,Vec3& camera,Vec3& LookTo,Edge& E1, Edge& E2);

    //calculators
    public:
        void calculateNorm();


};



#endif // OBJECT_H_

