#include "Object.h"
#include "MatVec.h"
#include "Graphics.h"
#include "Transformation.h"

Vec3 camera(25,25,25);
Vec3 LookTo(0,0,0);

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
    }

    if(keystate[SDLK_RIGHT]){
        RotateY(camera,2);
    }

    if(keystate[SDLK_UP]){
        RotateZ(camera,2);
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
    Object3d obj;
    obj.LoadObject("teapot.obj");

    Screen S(1024,840);
    while (processInput() != -1)
    {
        obj.render(&S,camera,LookTo);
    }

    return 0;
}
