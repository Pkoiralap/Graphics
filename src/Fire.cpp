#include "Fire.h"


// this will initialize the fire particles in
// a grid of size gridSize X gridSize X gridSize

Fire::Fire(int gSize,Screen *iS,Vec3& cam, Vec3& LT, float Width, float Height){
    S = iS;
    gridSize = gSize;
    srand(SDL_GetTicks());
    gridOrigin = Vec3(-60,100,60);
    initFire(cam,LT,Width,Height);
}

void Fire::initFire(Vec3& cam, Vec3& LT, float Width, float Height){
    camera = cam;
    LookTo = LT;
    pHeight = Height;
    pWidth = Width;
    for(int i=0;i<gridSize/2; i++){
        for(int j=0;j<gridSize/2; j++){
            for(int k=0;k<gridSize/2; k++){
                float ran = (float)(rand() % 50) / 10;
                float nran = ran- 2.5;
                Vec3 pos = gridOrigin + Vec3(i,j,k)*nran;
                fPart.push_back(fParticle(pos,Vec3(1,1,1)*ran));
            }
        }
    }
    nOfParticles = fPart.size();

}

void Fire::updateFire(Vec3& cam,Vec3& LT){
    float ran;
    camera = cam;
    LookTo = LT;
    for (unsigned int i =0;i<nOfParticles;i++){
        ran = (float)(rand() % 10) / 10;
        ran -= .5 ;

        if((fPart[i].lifetime -= 1) < 0 || fPart[i].i < 0){
            fPart.erase(fPart.begin()+i);
            continue;
        }
        fPart[i].vel = Vec3(60*ran,20*fPart[i].i,20*ran);
        fPart[i].pos = fPart[i].pos + fPart[i].vel;
//        std::cout << fPart[i].pos.x << " "  << fPart[i].pos.y << " " << fPart[i].pos.z << std::endl;

        fPart[i].i -= (rand() % 10) * .01;
        //fPart[i].alpha = 1 / fPart[i].i;

        //initFire(camera,LookTo,pHeiht,pWidth);
    }
    initFire(camera,LookTo,pWidth,pHeight);
    nOfParticles = fPart.size();
}

void Fire::showFire(){

    Vec2 vert2d[nOfParticles];
    for (unsigned i =0;i<nOfParticles;i++){
        vert2d[i] = World_To_Pixel(fPart[i].pos,camera,LookTo,pWidth,pWidth,1024,840);
        vert2d[i].x -= 200;
        vert2d[i].y += 100;

        //S->setpixel(vert2d[i].x,vert2d[i].y,vert2d[i].z,Vec3(200,10,0),fPart[i].i);
        for (unsigned int j=0 ;j<4;j++){
            for (unsigned int k = 0;k<4;k++){
                S->setpixel_a(vert2d[i].x+j,vert2d[i].y+k,vert2d[i].z,Vec3(250,10,0),fPart[i].i,fPart[i].alpha);
                S->setpixel_a(vert2d[i].x+k,vert2d[i].y+j,vert2d[i].z,Vec3(250,10,0),fPart[i].i,fPart[i].alpha);
            }
        }
    }
}
