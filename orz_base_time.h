#ifndef ORZ_BASE_TIME_H_INCLUDED
#define ORZ_BASE_TIME_H_INCLUDED

#include <SDL.h>

inline uint32_t GetTickTime(void) {return SDL_GetTicks();}
inline uint32_t GetCurrentTime(void) {return SDL_GetTicks();}

#endif // ORZ_BASE_TIME_H_INCLUDED
