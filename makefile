all: audisen_sim audisen_usb

audisen_sim: audisen_sim.o
	gcc audisen_sim.o amp.o ams.o frame.o -L. -l:ftd2xx.lib -o audisen_sim.exe

audisen_usb: audisen_usb.o
	gcc audisen_usb.o amp.o ams.o frame.o usb.o -L. -l:ftd2xx.lib -o audisen_usb.exe

audisen_sim.o: audisen_sim.c
	gcc -c audisen_sim.c

audisen_usb.o: audisen_usb.c
	gcc -c audisen_usb.c

amp.o: amp.c amp.h
	gcc -c amp.c

ams.o: ams.c ams.h
	gcc -c ams.c

frame.o: frame.c frame.h
	gcc -c frame.c

usb.o: usb.c usb.h
	gcc -c usb.c
