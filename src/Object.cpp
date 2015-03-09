#include "Object.h"

void Object3d::calculateNorm(){

    unsigned int len = surfaceBuffer.size();
    unsigned int t1, t2, t3;
    Vec3 V1, V2, V3;
    Vec3 norm(0,0,0);

    for(unsigned int i=0;i<len;i+=3){
        //indexes for the vertices
        t1 =surfaceBuffer[i].x-1;
        t2 =surfaceBuffer[i+1].x-1;
        t3 =surfaceBuffer[i+2].x-1;
//

        //Actual Vertices
        V1 = vertBuffer[t1].v;
        V2 = vertBuffer[t2].v;
        V3 = vertBuffer[t3].v;

        //determine the normal of the traingle and assign
        Vec3 A = (V3-V1)/((V3-V1).magnitude());
        Vec3 B = (V2-V1)/((V2-V1).magnitude());
        norm = B.crossProduct(A);
        norm = norm / norm.magnitude();

        vertBuffer[t1].norm = norm + vertBuffer[t1].norm ;
        vertBuffer[t2].norm = norm + vertBuffer[t2].norm ;
        vertBuffer[t3].norm = norm + vertBuffer[t3].norm ;


        vertBuffer[t1].norm = vertBuffer[t1].norm / vertBuffer[t1].norm.magnitude();
        vertBuffer[t2].norm = vertBuffer[t2].norm / vertBuffer[t2].norm.magnitude();
        vertBuffer[t3].norm = vertBuffer[t3].norm / vertBuffer[t3].norm.magnitude();


        vertBuffer[t1].cnt++; vertBuffer[t2].cnt++; vertBuffer[t3].cnt++;
 }

    len = vertBuffer.size();
    for(unsigned int i=0;i<len;i++){
        vertBuffer[i].norm = vertBuffer[i].norm / vertBuffer[i].cnt;
        vertBuffer[i].norm = vertBuffer[i].norm / vertBuffer[i].norm.magnitude();

    }
//
//    unsigned int len = surfaceBuffer.size();
//    unsigned int t1,t2,t3;
//    unsigned int n1,n2,n3;
//    Vec3 V1, V2, V3;
//    for (unsigned int i =0 ;i < len;i++){
//        t1 =surfaceBuffer[i].x-1;
//        t2 =surfaceBuffer[i+1].x-1;
//        t3 =surfaceBuffer[i+2].x-1;
//
//        n1 =surfaceBuffer[i].z-1;
//        n2 =surfaceBuffer[i+1].z-1;
//        n3 =surfaceBuffer[i+2].z-1;
//
//
//        vertBuffer[t1].norm = vertBuffer[t1].norm + normBuffer[n1];
//    }
//
//    len = vertBuffer.size();
//    for(unsigned int i=0;i<len;i++){
//        vertBuffer[i].norm = vertBuffer[i].norm / vertBuffer[i].norm.magnitude();
//    }

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
        else if (keyword == "vn"){
            Vec3 v;
            linestream >> v.x;
            linestream >> v.y;
            linestream >> v.z;
            addNormal(v);
        }
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
           // replaceAll(line,"//"," "); //replace // with /0/ for texture to be 0
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
        vert2d[i] = World_To_Pixel(vertBuffer[i].v,camera,LookTo,.2,.2,1024,840);
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

void Object3d::render(Screen* S,Vec3& camera,Vec3& LookTo,vector<Vec3> Lpos){
    unsigned int len = vertBuffer.size();
    Vec2 vert2d[len];
    float intensity = 0;
    Vec3 temp(0,0,0);
    for (unsigned int i=0;i<len;i++)
    {
        temp = Vec3(0,0,0);
        intensity = 0;

        vert2d[i] = World_To_Pixel(vertBuffer[i].v,camera,LookTo,.4,.4,1024,840);
//        //assign intensity here for shading
        for(unsigned int j=0; j<Lpos.size();j++){
            Vec3 A =  vertBuffer[i].v - Lpos[j];
            A = A / A.magnitude();
            intensity = intensity + vertBuffer[i].norm.dotProduct(A);
        }
        //if it is > 1 we truncate it to be 1
        if (intensity > 1)
            intensity = 1;
//        cout << v[i].z << endl;

        // if the intensity is -ve we simply avoid the intensity as it is the back face
        if (intensity < 0)
            intensity = 0.005;
//        else
//            Lpos.push_back(vertBuffer[i].v);
         vert2d[i].i = intensity;


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

//        //vertexes
//        v[0] = Vec2(600,150,-12,.9);
//        v[2] = Vec2(600,300,-14,1);
//        v[1] = Vec2(300,200,-10,.3);

//
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

        if (E[shortIndex1].v1->y > E[shortIndex2].v1->y)
            swap (shortIndex1,shortIndex2);

        //now we draw a horizontal line that will go from the y-longest edge to other two edges
        // better use a different function for it

        drawSpan(S,E[longIndex],E[shortIndex1]);
        drawSpan(S,E[longIndex],E[shortIndex2]);

//         drawSpan(S,E[longIndex],E[shortIndex1],E[shortIndex2]);

    }

}

void Object3d::drawSpan(Screen* S,Edge& E1, Edge& E2){
    //calculate the y difference for interpolation
    float e1ydiff = (float)(E1.v2->y - E1.v1->y);
    if (e1ydiff == 0)
        return;
    float e2ydiff = (float)(E2.v2->y - E2.v1->y);
    if (e2ydiff == 0)
        return;
    // //calculate the x difference for span processing
    // float e1xdiff = (float)(E1.v2->x - E1.v1->x);
    // float e2xdiff = (float)(E2.v2->x - E2.v1->x);
    //
    // //calculate the z difference
    // float e1zdiff = (float)(E1.v2->z - E1.v1->z);
    // float e2zdiff = (float)(E2.v2->z - E2.v1->z);
    //
    // //put the intensity difference and color difference here for interpolation
    // float e1idiff = (E1.v2->i - E1.v1->i);
    // float e2idiff = (E2.v2->i - E2.v1->i);
    //
    // //
    //
    // float factor1 = (float)(E2.v1->y - E1.v1->y) / e1ydiff;
    // float step1 = 1.0f / e1ydiff;
    //
    // float factor2 = 0.0f;
    // float step2 = 1.0f / e2ydiff;
    float x1 = E1.v1->x;
    float x2 = E2.v1->x;
    float x1i = (float)(E1.v2->x - E1.v1->x)/ e1ydiff;
    float x2i = (float)(E2.v2->x - E2.v1->x)/ e2ydiff;
    // float factor,stepfactor;
    float z1= E1.v1->z;
    float z2= E2.v1->z;
    float z1i = (float)(E1.v2->z - E1.v1->z)/e1ydiff;
    float z2i = (float)(E2.v2->z - E2.v1->z)/e2ydiff;
    float i1 = E1.v1->i;
    float i2 = E2.v1->i;
    float i1i = (float)(E1.v2->i - E1.v1->i)/e1ydiff;
    float i2i = (float)(E2.v2->i - E2.v1->i)/e2ydiff;
    // float x1,x2,z1,z2,i1,i2;
    unsigned int y;
    // loop through the lines between the edges and draw spans
    for(y = E2.v1->y; y < E2.v2->y; y++) {
        // create and draw span
        x1 += x1i;
        x2 += x2i;
        z1 += z1i;
        z2 += z2i;
        i1 += i1i;
        i2 += i2i;
        //
        // x1 = E1.v1->x + (int)(e1xdiff * factor1);
        // x2 = E2.v1->x + (int)(e2xdiff * factor2);
        //
        // z1= E1.v1->z + (int)(e1zdiff * factor1);
        // z2= E2.v1->z + (int)(e2zdiff * factor2);
        //
        // i1 = E1.v1->i + e1idiff*factor1;
        // i2 = E2.v1->i + e2idiff*factor2;
        S->line(Vec2(x1,y,z1,i1),Vec2(x2,y,z2,i2),Vec3(200,200,50));
        // S->refresh();
        // factor1 += step1;
        // factor2 += step2;
        }
    *(E1.v1) = Vec2(x1,y,z1,i1);
}

//This is the new code that is not working
/*
void Object3d::drawSpan(Screen* S,Edge& E1, Edge& E2,Edge& E3){

    //calculate the y difference for interpolation
    float e1ydiff = (float)(E1.v2->y - E1.v1->y);
    if (e1ydiff == 0)
        return;
    float e2ydiff = (float)(E2.v2->y - E2.v1->y);
    if (e2ydiff == 0)
        return;
    float e3ydiff = (float)(E3.v2->y - E3.v1->y);
    if (e3ydiff == 0)
        return;

    //calculate the x difference for span processing
    float e1xdiff = (float)(E1.v2->x - E1.v1->x);
    float e2xdiff = (float)(E2.v2->x - E2.v1->x);
    float e3xdiff = (float)(E3.v2->x - E3.v1->x);

//    //calculate the z difference
//    float e1zdiff = (float)(E1.v2->z - E1.v1->z);
//    float e2zdiff = (float)(E2.v2->z - E2.v1->z);
//
//    //put the intensity difference and color difference here for interpolation
//    float e1idiff = (E1.v2->i - E1.v1->i);
//    float e2idiff = (E2.v2->i - E2.v1->i);
//
//    //
//
//    float factor1 = (float)(E2.v1->y - E1.v1->y) / e1ydiff;
//    float step1 = 1.0f / e1ydiff;
//
//    float factor2 = 0.0f;
//    float step2 = 1.0f / e2ydiff;

    float x1 = E1.v1->x;
    float x2 = E2.v1->x;
    float x3 = E3.v1->x;

    float x1i = (float)(E1.v2->x - E1.v1->x)/ e1ydiff;
    float x2i = (float)(E2.v2->x - E2.v1->x)/ e2ydiff;
    float x3i = (float)(E3.v2->x - E3.v1->x)/ e3ydiff;

//    float factor,stepfactor;

    float z1= E1.v1->z;
    float z2= E2.v1->z;
    float z3= E3.v1->z;

    float z1i = (float)(E1.v2->z - E1.v1->z)/e1ydiff;
    float z2i = (float)(E2.v2->z - E2.v1->z)/e2ydiff;
    float z3i = (float)(E3.v2->z - E3.v1->z)/e3ydiff;

    float i1 = E1.v1->i;
    float i2 = E2.v1->i;
    float i3 = E3.v1->i;

    float i1i = (float)(E1.v2->i - E1.v1->i)/e1ydiff;
    float i2i = (float)(E2.v2->i - E2.v1->i)/e2ydiff;
    float i3i = (float)(E3.v2->i - E3.v1->i)/e3ydiff;

    //float x1,x2,z1,z2,i1,i2;
    unsigned int y;
    // loop through the lines between the edges and draw spans

    for(y = E2.v1->y; y < E2.v2->y; y++) {
        // create and draw span

        x1 += x1i;
        x2 += x2i;

        z1 += z1i;
        z2 += z2i;

        i1 += i1i;
        i2 += i2i;


//        x1 = E1.v1->x + (int)(e1xdiff * factor1);
//        x2 = E2.v1->x + (int)(e2xdiff * factor2);
//
//        z1= E1.v1->z + (int)(e1zdiff * factor1);
//        z2= E2.v1->z + (int)(e2zdiff * factor2);
//
//        i1 = E1.v1->i + e1idiff*factor1;
//        i2 = E2.v1->i + e2idiff*factor2;

        S->line(Vec2(x1,y,z1,i1),Vec2(x2,y,z2,i2),Vec3(200,50,0));

//
//        factor1 += step1;
//        factor2 += step2;
    }

    for(y ;y<E3.v2->y;y++){
        x1 += x1i;
        x2 += x3i;

        z1 += z1i;
        z2 += z3i;

        i1 += i1i;
        i2 += i3i;

        S->line(Vec2(x1,y,z1,i1),Vec2(x2,y,z2,i2),Vec3(200,50,0));
        //S->refresh();
    }


}
*/

