audisen: audisen_sim.o audisen_usb.o
	gcc audisen_sim.o audisen_usb.o -o audisen.exe

audisen_sim: audisen_sim.c
	gcc audisen_sim.c amp.c ams.c frame.c -L. -l:ftd2xx.lib -o audisen_sim.exe

audisen_usb: audisen_usb.c
	gcc audisen_usb.c amp.c ams.c frame.c usb.c -L. -l:ftd2xx.lib -o audisen_usb.exe

