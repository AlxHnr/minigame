#include <SDL.h>
#include "SDL_image.h"

void set_frame(SDL_Rect *char_source, SDL_Rect *char_dest, short x, short y, short w, short h)
{
  char_source->x = x;
  char_source->y = y;
  char_source->w = w;
  char_source->h = h;

  char_dest->w = char_source->w;
  char_dest->h = char_source->h;
}

#ifdef __WIN32__
  int WinMain(int argc, char *argv[])
#else
  int main(int argc, char *argv[])
#endif
{
  //var declaration start
  SDL_Surface *screen, *background, *character;
  SDL_Event keyboard_input;
  SDL_Rect character_source, character_dest;
  char programm_running = 1;
  //var declaration end

  //init start
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    exit(-1);
  }
  if((screen = SDL_SetVideoMode(640, 400, 16, SDL_SWSURFACE)) == NULL)
  {
    exit(-1);
  }
  SDL_WM_SetCaption("Minigame", NULL);
  atexit(SDL_Quit);

  if((character = IMG_Load("character.png")) == NULL)
  {
    exit(-1);
  }
  if((background = IMG_Load("background.png")) == NULL)
  {
    exit(-1);
  }
  SDL_BlitSurface(background, NULL, screen, NULL);
  SDL_Flip(screen);

  set_frame(&character_source, &character_dest, 0, 0, 31, 35);
  character_dest.x = screen->w/2 - character_source.w/2;
  character_dest.y = screen->h/2 - character_source.h/2;

  SDL_EnableKeyRepeat(1, 0);
  SDL_ShowCursor(SDL_DISABLE);
  //init end

  //main programm start
  while(programm_running)
  {
    while(SDL_PollEvent(&keyboard_input))
    {
      //erase old character
      SDL_BlitSurface(background, &character_dest, screen, &character_dest);
      SDL_UpdateRects(screen, 1, &character_dest);
      switch(keyboard_input.type)
      {
        case SDL_QUIT:
          programm_running = 0;
        break;
        case SDL_KEYDOWN:
          switch(keyboard_input.key.keysym.sym)
          {
            case SDLK_LEFT:
              set_frame(&character_source, &character_dest, 0, 35, 42, 35);
              character_dest.x -= 1;
            break;
            case SDLK_RIGHT:
              set_frame(&character_source, &character_dest, 0, 70, 43, 35);
              character_dest.x += 1;
            break;
            case SDLK_UP:
              set_frame(&character_source, &character_dest, 0, 106, 23, 36);
              character_dest.y -= 1;
            break;
            case SDLK_DOWN:
              set_frame(&character_source, &character_dest, 0, 0, 31, 35);
              character_dest.y += 1;
            break;
            case SDLK_ESCAPE:
             programm_running = 0;
            break;
            default:
            break;
          }
        break;
        default:
        break;
      }
    }
    //correct x, y
    if(character_dest.x < 0) character_dest.x = 0;
    else if(character_dest.x > screen->w-character_source.w) character_dest.x = screen->w-character_source.w;
    else if(character_dest.y < 0) character_dest.y = 0;
    else if(character_dest.y > 330-character_source.h) character_dest.y = 330-character_source.h;
    //update screen
    SDL_BlitSurface(character, &character_source, screen, &character_dest);
    SDL_UpdateRects(screen, 1, &character_dest);
    SDL_Delay(5);
  }
  //main programm end

  //programm end
  SDL_FreeSurface(character);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  return 0;
}
