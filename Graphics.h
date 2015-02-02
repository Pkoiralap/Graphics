#ifndef GRAPHICS_H_
#define GRAPHICS_H_


#include <SDL/SDL.h>
#include <math.h>
#include <cassert>
#include "MatVec.h"
#define round(a) ((int) (a+0.5))
#define ABS(a) ((a<0)? a*-1 : a)

class Color{
    public:
        int r,g,b,a;
    public: Color(){}
            Color(int rr, int gg, int bb, int aa=255):r(rr),g(gg),b(bb),a(aa){}

};

class Screen{
    SDL_Surface* screen;
    float* Zbuffer;
    public:
        Screen(int width = 640,int height=480){
            SDL_Init(SDL_INIT_EVERYTHING);
            screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
            Zbuffer = new float [width*height](); // () for setting everything to zero
        }

        void setpixel(Vec2 P,Color c);
        inline void setpixel(int x,int y,float dVal, Color c){
            Vec2 temp(x,y);
            temp.z = dVal;
            setpixel(temp,c);
        }
        void line(Vec2 P1,Vec2 P2,Color c);
        bool WaitQuit();
        void resetZ(){
            delete[] Zbuffer;
            Zbuffer = new float [(screen->w)*(screen->h)]();
        }
        void refresh(){
            SDL_Flip(screen);
        }

        void clrscr(){
            SDL_FreeSurface(screen);
            SDL_Rect rect;

            rect.x = 0; rect.y = 0;
            rect.h = screen->h; rect.w = screen->w;
            SDL_FillRect(screen,&rect,0);
            //screen = SDL_SetVideoMode(screen->w,screen->h,32,SDL_SWSURFACE);
        }

        ~Screen(){
            if (screen) {
                SDL_FreeSurface(screen);
                screen = NULL;
            }
            SDL_Quit();
            delete[] Zbuffer;
        }
};



#endif // GRAPHICS_H_

