#include <SDL/SDL.h>

#define	PSP_JOYSTICK_NEUTRAL_RANGE_FROM -2000
#define PSP_JOYSTICK_NEUTRAL_RANGE_TO 2000

#define X 0
#define Y 1

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static float cursor_position[2] = {0};
static float axes_values[2] = {0};
static SDL_Joystick* joystick = NULL;
static Uint16 value_divider = 1;
static int screen_size[2] = {0};
static Uint32 time;
static unsigned int frame_cnt = 0;
static unsigned int fps = 0;

int psp_jmouse_init(int width, int height, Uint16 cursor_x, Uint16 cursor_y, Uint16 divider)
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0 || SDL_NumJoysticks() == 0)
		return -1;

	joystick = SDL_JoystickOpen(0);
	if (!joystick || SDL_JoystickNumAxes(joystick) != 2)
		return -1;

	screen_size[X] = width;
	screen_size[Y] = height;
	value_divider = divider;

	cursor_position[X] = MIN(cursor_x, width);
	cursor_position[Y] = MIN(cursor_y, height);
	SDL_WarpMouse(cursor_position[X], cursor_position[Y]);

	return 0;
}

void psp_jmouse_quit()
{
	if (joystick)
		SDL_JoystickClose(joystick);
}

void psp_jmouse_update(const SDL_Event* event)
{
	Uint32 new_time;
	int i;

	if (event->type == SDL_JOYAXISMOTION) {
		if (event->jaxis.value < PSP_JOYSTICK_NEUTRAL_RANGE_FROM ||
				event->jaxis.value > PSP_JOYSTICK_NEUTRAL_RANGE_TO)
			axes_values[event->jaxis.axis] = event->jaxis.value / value_divider;
		else
			axes_values[event->jaxis.axis] = 0;
	}

	for (i = 0; i < 2; i++) {
		cursor_position[i] += axes_values[i] / (fps + 1);

		if (cursor_position[i] < 0)
			cursor_position[i] = 0;
		else if (cursor_position[i] > screen_size[i])
			cursor_position[i] = screen_size[i];
	}

	SDL_WarpMouse(cursor_position[X], cursor_position[Y]);

	++frame_cnt;

	new_time = SDL_GetTicks();
	if (new_time - time > 1000) {
		time = new_time;
		fps = frame_cnt;
		frame_cnt = 0;
	}
}
