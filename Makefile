all:
	gcc main.c -o main `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0`
	gcc main_screen.c -o main_screen `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0`
	gcc main2.c -o main2 `pkg-config --cflags --libs gstreamer-1.0 gstreamer-audio-1.0`