#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL/SDL.h>
#include "SDL/SDL_main.h"
#include "SDL/SDL_stdinc.h"
#include "SDL/SDL_audio.h"
#include "SDL/SDL_cdrom.h"
#include "SDL/SDL_cpuinfo.h"
#include "SDL/SDL_endian.h"
#include "SDL/SDL_error.h"
#include "SDL/SDL_events.h"
#include "SDL/SDL_loadso.h"
#include "SDL/SDL_mutex.h"
#include "SDL/SDL_rwops.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_video.h"
#include "SDL/SDL_version.h"

#include "MatVec.h"
#include <math.h>
#include <cassert>
#include "MatVec.h"
#define round(a) ((int) (a+0.5))
#define ABS(a) ((a<0)? a*-1 : a)

class Screen{
    SDL_Surface* screen;
    float* Zbuffer;
    public:
        Uint32 initTime;

        Screen(int width = 640,int height=480){
            SDL_Init(SDL_INIT_EVERYTHING);
            initTime = SDL_GetTicks();
            screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
            Zbuffer = new float [width*height](); // () for setting everything to zero
        }

        void setpixel(Vec2 P,Vec3 c,float intensity =.8);
        inline void setpixel(int x,int y,float dVal, Vec3 c,float intensity =1 ){
            Vec2 temp(x,y);
            temp.z = dVal;
            setpixel(temp,c,intensity);
        }

        void setpixel_a(Vec2 P,Vec3 c,float intensity,float alpha );
        inline void setpixel_a(int x, int y, float dVal ,Vec3 c,float intensity,float alpha ){
            Vec2 temp(x,y);
            temp.z = dVal;
            setpixel_a(temp,c,intensity,alpha);
        }

        void gn_line(Vec2 P1,Vec2 P2,Vec3 c= Vec3(255,255,255)); // gn_line
        void st_line(Vec2 P1,Vec2 P2,Vec3 c= Vec3(255,255,255)); // line parallel to x axis

        void resetZ(){
            delete[] Zbuffer;
            Zbuffer = new float [(screen->w)*(screen->h)]();
        }
        void refresh(){
            initTime = SDL_GetTicks();
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

