#include "Object.h"
#include "MatVec.h"
#include "Graphics.h"
#include "Transformation.h"
#include "Fire.h"

Vec3 camera(-5,0,-40);
Vec3 fcamera(-5,0,-80);

//Vec3 camera(-25,-25,-25);
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
        RotateY(camera,-2);
    }

    if(keystate[SDLK_RIGHT]){
        RotateY(camera,2);
    }

    if(keystate[SDLK_UP]){
        RotateX(camera,2);
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
    Screen S(1024,840);
    Object3d obj2(0,140);
    obj2.LoadObject("objects/torch.obj");

    Object3d obj1(200,0);
    obj1.LoadObject("objects/teapot.obj");

    Fire F(20,&S,fcamera,LookTo,30,30);
//
//    Lpos.push_back(Vec3(10,0,0));
//    Lpos.push_back(Vec3(-10,0,0));
//    Lpos.push_back(Vec3(0,100,0));
//    Lpos.push_back(Vec3(0,-100,0));
//    Lpos.push_back(Vec3(0,0,100));
//    Lpos.push_back(Vec3(0,0,-100));

    while (processInput() != -1){

        S.clrscr();
        S.resetZ();

        F.showFire();
        F.updateFire(fcamera,LookTo);
        obj2.render(&S,camera,LookTo,F,10,10);
        obj1.render(&S,camera,LookTo,F,1,1);
        cout << "FPS: " << 1000/(SDL_GetTicks() - S.initTime) << endl;
        S.refresh();

    }

    return 0;
}
