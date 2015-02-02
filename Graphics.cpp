//#include "Graphics.h"
//#include "Object.h"

#include "Object.h"
#include "MatVec.h"
#include "Graphics.h"

//void draw(Vec3 camera, Vec3 LookTo)
//{
//
//
//    Vec3 O(0,0,0), X(15,0,0), Y(0,15,0), Z(0,0,15);
//    Vec2 o = World_To_Pixel(O,camera,LookTo,3,3,1024,840);
//    Vec2 x = World_To_Pixel(X,camera,LookTo,3,3,1024,840);
//    Vec2 y = World_To_Pixel(Y,camera,LookTo,3,3,1024,840);
//    Vec2 z = World_To_Pixel(Z,camera,LookTo,3,3,1024,840);
//
//    Screen S(1024,840);
//    Color C(255,0,0);
//
//    S.line(o,x,C);
//    C = Color(0,255,0);
//    S.line(o,y,C);
//    C = Color(0,0,255);
//    S.line(o,z,C);
//
//
//
//    Vec3 p3[4] = {Vec3(0,0,0),Vec3(0,10,0),Vec3(10,0,0),Vec3(5,5,10)};
//    Vec2 p2[4];
//
//    for (int i=0;i<4;i++)
//        p2[i] = World_To_Pixel(p3[i],camera,LookTo,2,2,1024,840);
//
//    C = Color(255,255,255);
//
//    for(int i=0;i<3;i++){
//        S.line(p2[3],p2[i],C);
//    }
//
//    S.line(p2[0],p2[1],C);
//    S.line(p2[1],p2[2],C);
//    S.line(p2[2],p2[0],C);
//    SDL_Delay(100);
//    S.refresh();
//
//}


int main(){
    Vec3 camera(25,25,25);
    Vec3 LookTo(0,0,0);
    Object3d obj;
    obj.LoadObject("teapot.obj");

    SDL_Event event;
    Screen S(1024,840);
    while (1)
    {
        obj.drawWire(&S,camera,LookTo);
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
                        return 0;
                }
            }
        }
    }
}

void Screen::setpixel(Vec2 P,Color c)
{
    int *pixmem32;
    int colour;

    int width = screen->w;
    int height = screen->h;

    //Check for boundaries
    int x = P.x;
    int y = P.y;
    if (!(x>=0 && x <= width && y >=0 && y<=height)) return;
    //assert (x>0 && x < width && y >0 && y<height) ;

    //Zbuffer[row*col] == Zbuffer[width*height]
    //Zbuffer[x][y] = Zbuffer[x*col+y]
    //If the present z value is greater than the previous on, do not draw i
    if (P.z > Zbuffer[height*x + y])
        return;
    else
        Zbuffer[height*x + y] = P.z;

    colour = SDL_MapRGB ( screen->format,c.r,c.g,c.b);
    pixmem32 = (int*) screen->pixels+y*screen->pitch/4+x;
    *pixmem32 = colour;
}


//Draw line considering the depth of the points.
void Screen::line(Vec2 P1, Vec2 P2,Color c){

    int x1 = P1.x; int y1 = P1.y;
    int x2 = P2.x; int y2 = P2.y;
    float dStart = P1.z, dEnd = P2.z;// Starting depth value, and ending depth values
    float dVal = dStart, delta_d = dStart - dEnd; // The depth value of that point, and the difference delta_d

//
//    if (x1 <= 0) x1 = 1;
//    if (x1 >= screen->w) x1 = screen->w -1;
//    if (y1 <= 0) y1 = 1;
//    if (y1 >= screen->h) y1 = screen->h -1;
//
//    if (x2 <= 0) x2 = 1;
//    if (x2 >= screen->w) x2 = screen->w -1 ;
//    if (y2 <= 0) y2 = 1;
//    if (y2 >= screen->h) y2 = screen->h -1;


    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = ABS(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = ABS(delta_y) << 1;

    setpixel(x1,y1,dVal,c);

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        float id = delta_d / (float) delta_x;
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            dVal += id;
            setpixel(x1, y1 ,dVal, c);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        float id = delta_d / (float) delta_y;
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;
            dVal += id;
            setpixel(x1, y1,dVal, c);
        }
    }
}

bool Screen::WaitQuit()
{
    SDL_Event event;
    bool keypress = false;

    while (!keypress)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            //If the cross on the top is pressed it is triggered
            case SDL_QUIT:
                keypress = true;
                break;
            //Triggered for keydown
            case SDL_KEYDOWN:
                keypress = true;
                break;
            }
        }
    }
    return true; //wait ends
}

