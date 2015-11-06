#include <psp_jmouse.h>
#include <SDL/SDL.h>
#include <pspkernel.h>
#include <pspdebug.h>

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272

PSP_MODULE_INFO("PSP JMouse Example", 0, 1, 0);

int exit_callback(int arg1, int arg2, void* common)
{
	psp_jmouse_quit();
	SDL_Quit();

	sceKernelExitGame();

	return 0;
}

int callback_thread(SceSize args, void *argp)
{
	int cbid;
	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

int SetupCallbacks(void)
{
	int thid = 0;
	thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xfa0, 0, 0);
	if (thid >= 0)
		sceKernelStartThread(thid, 0, 0);

	return thid;
}

int main(int argc, char** argv)
{
	pspDebugScreenInit();
	SetupCallbacks();

	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_SetVideoMode(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, 32, SDL_HWSURFACE);

	psp_jmouse_init(PSP_SCREEN_WIDTH, PSP_SCREEN_HEIGHT, 0, 0, 100);

	while (1) {
		SDL_PollEvent(&event);

		psp_jmouse_update(&event);
	}

	return 0;
}
