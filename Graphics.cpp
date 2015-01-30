//#include "Graphics.h"
//#include "Object.h"

#include "Pipelining.h"
#include "Graphics.h"

void draw(Vec3 camera, Vec3 LookTo)
{
    Vec3 O(0,0,0), X(15,0,0), Y(0,15,0), Z(0,0,15);
    Vec2 o = World_To_Pixel(O,camera,LookTo,3,3,1024,840);
    Vec2 x = World_To_Pixel(X,camera,LookTo,3,3,1024,840);
    Vec2 y = World_To_Pixel(Y,camera,LookTo,3,3,1024,840);
    Vec2 z = World_To_Pixel(Z,camera,LookTo,3,3,1024,840);

    Screen S(1024,840);
    Color C(255,0,0);

    S.line(o,x,C);
    C = Color(0,255,0);
    S.line(o,y,C);
    C = Color(0,0,255);
    S.line(o,z,C);



    Vec3 p3[4] = {Vec3(0,0,0),Vec3(0,10,0),Vec3(10,0,0),Vec3(5,5,10)};
    Vec2 p2[4];

    for (int i=0;i<4;i++)
        p2[i] = World_To_Pixel(p3[i],camera,LookTo,2,2,1024,840);

    C = Color(255,255,255);

    for(int i=0;i<3;i++){
        S.line(p2[3],p2[i],C);
    }

    S.line(p2[0],p2[1],C);
    S.line(p2[1],p2[2],C);
    S.line(p2[2],p2[0],C);
    SDL_Delay(100);
    S.refresh();

}


int main(){
    Vec3 camera(25,25,25);
    Vec3 LookTo(0,0,0);

    SDL_Event event;

    while (1)
    {
        draw(camera,LookTo);
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_a:
                        camera.x -= 1;
                        break;
                    //Triggered for keydown
                    case SDLK_s:
                        camera.y -= 1;
                        break;
                    case SDLK_d:
                        camera.x += 1;
                        break;
                    case SDLK_w:
                        camera.y += 1;
                        break;
                    case SDLK_z:
                        camera.z += 1;
                        break;
                    case SDLK_x:
                        camera.z -= 1;
                        break;
                    case SDLK_ESCAPE:
                        goto outside;
                        break;
                }
            }
        }
    }
    outside: SDL_Quit();
    return 0;
}
