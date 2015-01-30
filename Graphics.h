#ifndef GRAPHICS_H_
#define GRAPHICS_H_


#include <SDL/SDL.h>
#include <math.h>
#include <cassert>
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

    public:
        Screen(int width = 640,int height=480){
            SDL_Init(SDL_INIT_EVERYTHING);
            screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
        }

        void setpixel(Vec2 P,Color c);
        void setpixel(int x,int y, Color c){
            Vec2 temp(x,y);
            setpixel(temp,c);
        }
        void line(Vec2 P1,Vec2 P2,Color c);
        bool WaitQuit();

        void refresh(){
            SDL_Flip(screen);
        }

        void clrscr(){
            SDL_Rect R;
            R.x =0; R.y =0;
            R.h = screen->h; R.w = screen->w;
            SDL_FillRect(screen,&R,0);
        }
};

void Screen::setpixel(Vec2 P,Color c)
{
    int *pixmem32;
    int colour;

    int width = screen->w;
    int height = screen->h;

    //Check for boundaries
    int x = P.x;
    int y = P.y;

    assert (x>0 && x < width && y >0 && y<height) ;

    colour = SDL_MapRGB ( screen->format,c.r,c.g,c.b);
    y = y*screen->pitch/4;
    pixmem32 = (int*) screen->pixels+y+x;
    *pixmem32 = colour;
}

void Screen::line(Vec2 P1, Vec2 P2,Color c){

    int x1 = P1.x; int y1 = P1.y;
    int x2 = P2.x; int y2 = P2.y;

    if (x1 <= 0) x1 = 1;
    if (x1 >= screen->w) x1 = screen->w -1;
    if (y1 <= 0) y1 = 1;
    if (y1 >= screen->h) y1 = screen->h -1;

    if (x2 <= 0) x2 = 1;
    if (x2 >= screen->w) x2 = screen->w -1 ;
    if (y2 <= 0) y2 = 1;
    if (y2 >= screen->h) y2 = screen->h -1;


    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = ABS(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = ABS(delta_y) << 1;

    setpixel(x1, y1,c);

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

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

            setpixel(x1, y1,c);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

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

            setpixel(x1, y1,c);
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


#endif // GRAPHICS_H_

