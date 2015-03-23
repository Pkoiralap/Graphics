#include "Object.h"
#include "MatVec.h"
#include "Graphics.h"
#include "Transformation.h"
#include "Fire.h"

Vec3 camera(25,-15,-25);
Vec3 LookTo(0,0,0);
vector<Vec3> Lpos;

int processInput(){
     Uint8* keystate = SDL_GetKeyState(NULL);

    //continuous-response keys
    if(keystate[SDLK_a]){
        camera.x -= 1;
    }

    if(keystate[SDLK_s]){
        camera.y -= 1;
    }
    if(keystate[SDLK_d]){
        camera.x += 1;
    }
    if(keystate[SDLK_w]){
        camera.y += 1;
    }
    if(keystate[SDLK_z]){
        camera.z += 1;
    }
    if(keystate[SDLK_x]){
        camera.z -= 1;
    }

    if(keystate[SDLK_LEFT]){
        RotateX(camera,2);
         for(unsigned int i=0;i<Lpos.size();i++)
            RotateX(Lpos[i],2);
    }

    if(keystate[SDLK_RIGHT]){
        RotateY(camera,2);
          for(unsigned int i=0;i<Lpos.size();i++)
            RotateY(Lpos[i],2);

    }

    if(keystate[SDLK_UP]){
        RotateZ(camera,2);
         for(unsigned int i=0;i<Lpos.size();i++)
            RotateZ(Lpos[i],2);
    }

    if(keystate[SDLK_l]){
        for(unsigned int i=0;i<Lpos.size();i++)
            RotateY(Lpos[i],2);
    }


    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return -1;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    return -1;
            break;
        }
    }
    return 0;
}

int main(){
//    Object3d obj1;
//    obj1.LoadObject("objects/teapot.obj");
    Screen S(1024,840);
    Object3d obj2;
    obj2.LoadObject("objects/vemask.obj");
//
//    Lpos.push_back(Vec3(10,0,0));
//    Lpos.push_back(Vec3(-10,0,0));
//    Lpos.push_back(Vec3(0,100,0));
//    Lpos.push_back(Vec3(0,-100,0));
//    Lpos.push_back(Vec3(0,0,100));
//    Lpos.push_back(Vec3(0,0,-100));

   Fire F(20,&S,camera,LookTo,20,20);

    while (processInput() != -1){

        S.clrscr();
        S.resetZ();

        F.showFire();
        F.updateFire(camera,LookTo);


        obj2.render(&S,camera,LookTo,F,.9,.9);


        //cout << "FPS: " << 1000/(SDL_GetTicks() - S.initTime) << endl;
        S.refresh();

//        obj1.render(&S,camera,LookTo,Lpos);


    }

    return 0;
}
