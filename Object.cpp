#include "Object.h"

void Object3d::calculateNorm(){
    unsigned int len = surfaceBuffer.size();
    unsigned int t1, t2, t3;
    Vec3 V1, V2, V3;
    Vec3 norm;

    for(unsigned int i=0;i<len;i+=3){
        //indexes for the vertices
        t1 =surfaceBuffer[i].x-1;
        t2 =surfaceBuffer[i+1].x-1;
        t3 =surfaceBuffer[i+2].x-1;

        //Actual Vertices
        V1 = vertBuffer[t1].v;
        V2 = vertBuffer[t2].v;
        V3 = vertBuffer[t3].v;

        //determine the normal of the traingle and assign
        norm = (V3-V1).crossProduct(V2-V1);
        vertBuffer[t1].norm = vertBuffer[t2].norm = vertBuffer[t3].norm = norm;

        //increase the surface shared count by 1 for each assignation
        vertBuffer[t1].cnt ++; vertBuffer[t2].cnt ++; vertBuffer[t3].cnt ++;
    }

    len = vertBuffer.size();
    for(unsigned int i=0;i<len;i++){
        vertBuffer[i].norm = vertBuffer[i].norm / vertBuffer[t1].cnt;
        vertBuffer[i].norm = vertBuffer[i].norm /vertBuffer[i].norm.magnitude();
    }

}



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
    surfaceBuffer.clear();
    normBuffer.clear();
    textureBuffer.clear();

    ifstream obj(filename.c_str());
    if (!obj.is_open()) throw "Can not open";

    vector <Vec3> temp;
    string line,keyword;;
    while(getline(obj,line)){
        while(line.compare(0,1," ")==0)
            line.erase(line.begin()); // remove leading whitespaces
        while(line.size()>0 && line.compare(line.size()-1,1," ")==0)
            line.erase(line.end()-1); // remove trailing whitespaces
        if (line == "" || line == "\n") continue;
        istringstream linestream(line);
        linestream >> keyword;
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
//        else if (keyword == "vn"){
//            Vec3 v;
//            linestream >> v.x;
//            linestream >> v.y;
//            linestream >> v.z;
//            addNormal(v);
//        }
//
//        else if(keyword == "vt"){
//            texture = true;
//            Vec2 v;
//            linestream >> v.x;
//            linestream >> v.y;
//            addTexture(v);
//        }

        else if(keyword == "f"){
            line = line.substr(1,line.length()-1); //remove the preceding f
            while(line.compare(0,1," ")==0)
                line.erase(line.begin()); // remove leading whitespaces
            while(line.size()>0 && line.compare(line.size()-1,1," ")==0)
            line.erase(line.end()-1); // remove trailing whitespaces

//
//            replaceAll(line," ","//"); //replace // with /0/ for texture to be 0
//            replaceAll(line,"//","/0/0/"); //replace // with /0/ for texture to be 0
//            replaceAll(line,"/"," "); //remove the / for easy calculatoin
            istringstream lstream(line);
            //v contains .x = vertex index, .y = texture .z= normal index

            Vec3 v[3];
            lstream >> v[0].x;
//            lstream >> v[0].y;
//            lstream >> v[0].z;
            lstream >> v[1].x;
           // lstream >> v[1].y;
//            lstream >> v[1].z;
            lstream >> v[2].x;
            //lstream >> v[2].y;
//            lstream >> v[2].z;

            addSurface(v[0]);
            addSurface(v[1]);
            addSurface(v[2]);
        }
    }
    obj.close();

//    //count of vertices and surfaces
//    unsigned int n_vertices = vertBuffer.size();
//    unsigned int n_surfaces = surfaceBuffer.size();
//
//    //for no vertex normal
//    Vec3 t(0,0,0);
//    for(unsigned int i=0;i<n_surfaces;i++){
//        //addVertex(surfaceBuffer[i].x-1,normBuffer[surfaceBuffer[i].z]);
//          addVertex(surfaceBuffer[i].x-1,t);
//
//    }

    calculateNorm();
}


void Object3d::drawWire(Screen* S,Vec3& camera,Vec3& LookTo){
    Vec3 C(255,255,255);
    S->clrscr();
    S->resetZ();

    //Adding the 3d vertices into 2d vertex
    unsigned int len = vertBuffer.size();
    Vec2 vert2d[len];
    for (unsigned int i=0;i<len;i++)
    {
        vert2d[i] = World_To_Pixel(vertBuffer[i].v,camera,LookTo,.3,.3,1024,840);
//        cout << v[i].z << endl;
    }

    len = surfaceBuffer.size();
    unsigned int t1;
    unsigned int t2;
    for (unsigned int i=0;i<len;i+=3)
    {
        t1 =surfaceBuffer[i].x-1;
        t2 =surfaceBuffer[i+1].x-1;
        S->line(vert2d[t1],vert2d[t2]);

        t1 =surfaceBuffer[i+1].x-1;
        t2 =surfaceBuffer[i+2].x-1;
        S->line(vert2d[t1],vert2d[t2]);

        t1 =surfaceBuffer[i+2].x-1;
        t2 =surfaceBuffer[i].x-1;
        S->line(vert2d[t1],vert2d[t2]);
    }

    S->refresh();
}

void Object3d::render(Screen* S,Vec3& camera,Vec3& LookTo,Vec3& Lpos){
    S->clrscr();
    S->resetZ();

    fillObject(S,camera,LookTo,Lpos);
    S->refresh();
}

void Object3d::fillObject(Screen* S,Vec3& camera,Vec3& LookTo,Vec3& Lpos){
    unsigned int len = vertBuffer.size();
    Vec2 vert2d[len];
    float intensity;
    for (unsigned int i=0;i<len;i++)
    {
        vert2d[i] = World_To_Pixel(vertBuffer[i].v,camera,LookTo,.4,.4,1024,840);
        //assign intensity here for shading
        Vec3 temp = Lpos - vertBuffer[i].v ;
        temp = temp / temp.magnitude();
        vert2d[i].i = temp.dotProduct(vertBuffer[i].norm);
//        cout << v[i].z << endl;
    }

    unsigned int t1,t2,t3;
    len = surfaceBuffer.size();

    //temp store of vertices and edges
    Vec2 v[3];
    Edge E[3];

    //for all surfaces
    for(unsigned int i=0;i<len;i+=3){
        //indexes for the vertices
        t1 =surfaceBuffer[i].x-1;
        t2 =surfaceBuffer[i+1].x-1;
        t3 =surfaceBuffer[i+2].x-1;

        //vertexes
        v[0] = vert2d[t1];
        v[1] = vert2d[t2];
        v[2] = vert2d[t3];

//        vertexes
//        v[0] = Vec2(50,50,-12,.5);
//        v[1] = Vec2(100,100,-14,.6);
//        v[2] = Vec2(50,150,-10,.9);


        //Edges
        E[0] = Edge(v,v+1);
        E[1] = Edge(v+1,v+2);
        E[2] = Edge(v+2,v);

        //we need to find the longest edge in y-axis. to do so check the y-lenght of all edges
        float maxLen =0;
        int longIndex =0;
        for (int i=0;i<3;i++){
            float Len = E[i].v2->y - E[i].v1->y;
            if (Len>maxLen){
                maxLen = Len;
                longIndex = i;
            }
        }

        //Index for other two edges
        int shortIndex1 = (longIndex + 1) % 3;
        int shortIndex2 = (longIndex + 2) % 3;

        //now we draw a horizontal line that will go from the y-longest edge to other two edges
        // better use a different function for it
        drawSpan(S,camera,LookTo,E[longIndex],E[shortIndex1]);
        drawSpan(S,camera,LookTo,E[longIndex],E[shortIndex2]);
    }

}

void Object3d::drawSpan(Screen* S,Vec3& camera,Vec3& LookTo,Edge& E1, Edge& E2){

    //calculate the y difference for interpolation
    float e1ydiff = (float)(E1.v2->y - E1.v1->y); if (e1ydiff == 0) return;
    float e2ydiff = (float)(E2.v2->y - E2.v1->y); if (e2ydiff == 0) return;

    //calculate the x difference for span processing
    float e1xdiff = (float)(E1.v2->x - E1.v1->x);
    float e2xdiff = (float)(E2.v2->x - E2.v1->x);

    //calculate the z difference
    float e1zdiff = (float)(E1.v2->z - E1.v1->z);
    float e2zdiff = (float)(E2.v2->z - E2.v1->z);

    //put the intensity difference and color difference here for interpolation
    float e1idiff = (E1.v2->i - E1.v1->i);
    float e2idiff = (E2.v2->i - E2.v1->i);

    //

    float factor1 = (float)(E2.v1->y - E1.v1->y) / e1ydiff;
    float step1 = 1.0f / e1ydiff;

    float factor2 = 0.0f;
    float step2 = 1.0f / e2ydiff;


    float x1,x2,xdiff;
    float factor,stepfactor;

    float zdiff,z1,z2;
    float i1,i2;
    // loop through the lines between the edges and draw spans
    for(int y = E2.v1->y; y <= E2.v2->y; y++) {
        // create and draw span
        x1 = E1.v1->x + (int)(e1xdiff * factor1);
        x2 = E2.v1->x + (int)(e2xdiff * factor2);

        z1= E1.v1->z + (int)(e1zdiff * factor1);
        z2= E2.v1->z + (int)(e2zdiff * factor2);

        i1 = E1.v1->i + e1idiff*factor1;
        i2 = E2.v1->i + e2idiff*factor2;

        S->line(Vec2(x1,y,z1,i1),Vec2(x2,y,z2,i2),Vec3(255,100,100));

        // increase factors
        factor1 += step1;
        factor2 += step2;
    }

}
