#ifndef _PSP_JMOUSE_H_
#define _PSP_JMOUSE_H_

#include <SDL/SDL_types.h>
#include <SDL/SDL_events.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
int psp_jmouse_init(int width, int height, Uint16 cursor_x, Uint16 cursor_y, Uint16 divider);
void psp_jmouse_quit();
void psp_jmouse_update(const SDL_Event* event);
__END_DECLS

#endif
