# PSP-JMouse
Small library enabling the use of the PSP's joystick as a mouse with SDL


Documentation
-------------
```C
int psp_jmouse_init(int width, int height, Uint16 cursor_x, Uint16 cursor_y, Uint16 divider)
```
Initializes PSP JMouse  
width: screen width  
height: screen height  
cursor_x: initial cursor position on the x axis  
cursor_y: initial cursor position on the y axis  
divider: value used to regulate the cursor's speed. A small value means a fast cursor (100 is a good value).  

returns 0 on success, -1 on error.
<br><br>
```C
void psp_jmouse_quit()
```
Closes the opened joystick.
<br><br>
```C
void psp_jmouse_update(const SDL_Event* event)
```
Processes the event. You should get the event with SDL_PollEvent, using SDL_WaitEvent won't work properly.
