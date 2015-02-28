#ifndef ORZ_LOG_H_INCLUDED
#define ORZ_LOG_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
namespace Orz
{
    using std::cout;
    using std::endl;
    using std::string;

    inline void ERROR_OUT(const char *information)
    {
        if(information)
        cout<<information
        <<"\nSDL����Ĵ���Ϊ: "<<SDL_GetError()
        <<"\nSDL_imgae����Ĵ���Ϊ:"<<IMG_GetError()
        //<<"\nTTF����Ĵ���Ϊ:"TTF_GetError()
        <<endl<<endl;
    }

    inline void ERROR_OUT(string& information)
    {
        cout<<information
        <<"\nSDL����Ĵ���Ϊ: "<<SDL_GetError()
        <<"\nSDL_imgae����Ĵ���Ϊ: "<<IMG_GetError()
        //<<"\nTTF����Ĵ���Ϊ:"TTF_GetError()
        <<endl<<endl;
    }

    inline void error_out(string &information)
    {
        cout<<information
        <<"\nSDL����Ĵ���Ϊ: "<<SDL_GetError()
        <<"\nSDL_imgae����Ĵ���Ϊ: "<<IMG_GetError()
        //<<"\nTTF����Ĵ���Ϊ:"TTF_GetError()
        <<endl<<endl;
    }

    inline void error_out(const char *information)
    {
        if(information)
        cout<<information
        <<"\nSDL����Ĵ���Ϊ: "<<SDL_GetError()
        <<"\nSDL_imgae����Ĵ���Ϊ: "<<IMG_GetError()
        //<<"\nTTF����Ĵ���Ϊ:"TT
        <<endl<<endl;
    }
}

#endif // ORZ_LOG_H_INCLUDED
