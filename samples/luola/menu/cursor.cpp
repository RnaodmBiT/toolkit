#include "cursor.hpp"
#include "SDL.h"
#include <map>

namespace Cursor {

    std::map<Type, SDL_Cursor*> cursors;

    void initialize() {
        cursors[Arrow] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
        cursors[IBeam] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
        cursors[Crosshair] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    }

    void set(Type cursor) {
        SDL_SetCursor(cursors[cursor]);
    }

}