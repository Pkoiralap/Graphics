#include "Object.h"

void Object3d::render(){

    for(int i=0;i<surfaceBuffer.

}

void Object3d::LoadObject(string filename){
    vertBuffer.clear();

    ifstream obj(filename,ios::in);
    if (!obj.is_open()) throw "Can not open";

    vector <Vec3> temp;
    string s;
    while(getline(obj,s)){

        while(s.compare(0,1," ")==0)
            s.erase(s.begin()); // remove leading whitespaces
        while(s.size()>0 && s.compare(s.size()-1,1," ")==0)
            s.erase(s.end()-1); // remove trailing whitespaces

        istringstream linestream(line);
        string key;

        linestream >> key;
        if (key == "v"){
            Vec3
        }

    }

}

