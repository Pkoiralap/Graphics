#include "Object.h"

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void Object3d::LoadObject(string filename){
    vertBuffer.clear();

    ifstream obj(filename.c_str());
    if (!obj.is_open()) throw "Can not open";

    vector <Vec3> temp;
    string line,keyword;;
    while(getline(obj,line)){
        while(line.compare(0,1," ")==0)
            line.erase(line.begin()); // remove leading whitespaces
        while(line.size()>0 && line.compare(line.size()-1,1," ")==0)
            line.erase(line.end()-1); // remove trailing whitespaces

        istringstream linestream(line);
        linestream >> keyword;
        cout << keyword;
        if (keyword == "v"){
            Vec3 temp;
            unsigned int t;
            linestream >> temp.x;
            linestream >> temp.y;
            linestream >> temp.z;
            if (!(linestream>>t))
                t = 1.0f;

            //normalize wrt t
            if (t>0 && t<1)
                temp = temp / t;

            addVertex(temp);
        }
        else if (keyword == "vn"){
            Vec3 v;
            linestream >> v.x;
            linestream >> v.y;
            linestream >> v.z;
            addNormal(v);
        }

        else if(keyword == "vt"){
            texture = true;
            Vec2 v;
            linestream >> v.x;
            linestream >> v.y;
            addTexture(v);
        }

        else if(keyword == "f"){
            line = line.substr(1,line.length()-1); //remove the preceding f
            while(line.compare(0,1," ")==0)
                line.erase(line.begin()); // remove leading whitespaces
            replaceAll(line,"//","/0/"); //replace // with /0/ for texture to be 0
            replaceAll(line,"/"," "); //remove the / for easy calculatoin

            istringstream lstream(line);
            //v contains .x = vertex index, .y = texture .z= normal index

            Vec3 v[3];
            lstream >> v[0].x;
            lstream >> v[0].y;
            lstream >> v[0].z;
            lstream >> v[1].x;
            lstream >> v[1].y;
            lstream >> v[1].z;
            lstream >> v[2].x;
            lstream >> v[2].y;
            lstream >> v[2].z;

            addSurface(v[0]);
            addSurface(v[1]);
            addSurface(v[2]);
        }
    }
    obj.close();
    //count of vertices and surfaces
    unsigned int n_vertices = vertBuffer.size();
    unsigned int n_surfaces = surfaceBuffer.size();

    for(unsigned int i=0;i<n_surfaces;i++){
        addVertex(surfaceBuffer[i].x-1,normBuffer[surfaceBuffer[i].z]);
    }
}


void Object3d::drawWire(Vec3& camera,Vec3& LookTo){
    Screen S(1024,840);
    Color C(255,255,255);
    unsigned int len = vertBuffer.size();
    Vec2 v[len];
    for (unsigned int i=0;i<len;i++)
    {
        v[i] = World_To_Pixel(vertBuffer[i].v,camera,LookTo,.15,.15,1024,840);
    }
    len = surfaceBuffer.size();
    unsigned int t1;
    unsigned int t2;
    for (unsigned int i=0;i<len;i+=3)
    {
        t1 =surfaceBuffer[i].x-1;
        t2 =surfaceBuffer[i+1].x-1;
        S.line(v[t1],v[t2],C);

        t1 =surfaceBuffer[i+1].x-1;
        t2 =surfaceBuffer[i+2].x-1;
        S.line(v[t1],v[t2],C);

        t1 =surfaceBuffer[i+2].x-1;
        t2 =surfaceBuffer[i].x-1;
        S.line(v[t1],v[t2],C);
    }

    S.refresh();
}

