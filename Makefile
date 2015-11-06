PSPSDK = $(shell psp-config --pspsdk-path)

CPPFLAGS = -Isrc
LIBS = -lSDL -lGL -lpspgu -lpspaudio -lpsphprm -lpspirkeyb -lpspvfpu -lpsprtc -lpsppower

TARGET = example
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSP JMouse Example

BUILD_PRX = 1
PSP_FW_VERSION = 660

OBJS  = example.o src/psp_jmouse.o

include $(PSPSDK)/lib/build.mak

src/psp_jmouse.o:
	@$(MAKE) -C src
