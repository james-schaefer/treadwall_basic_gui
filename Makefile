.PHONY: pack run

all: pack build 

pack:
	packfolder ui resources.cpp -v "resources"

build:
	g++ main.cpp sciter-gtk-main.cpp -o treadwall_basic_gui \
  -I/usr/include/sciter \
  -L/usr/lib/sciter \
  -lsciter \
  -I/usr/include/gtk-3.0 \
  -L/usr/lib/x86_64-linux-gnu \
  -lgtk-3 \
  -I/usr/include/glib-2.0/ \
  -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
  -lglib-2.0 \
  -I/usr/include/cairo/ \
  -lcairo \
  -I/usr/include/pango-1.0 \
  -lpango-1.0 \
  -I/usr/include/gdk-pixbuf-2.0 \
  -L/usr/lib/x86_64-linux-gnu/gdk-pixbuf-2.0/2.10.0/loaders \
  -L/usr/lib/x86_64-linux-gnu/libgtk2.0-0 \
  -I/usr/include/atk-1.0 \
  -latk-1.0 \
  -ldl \
  -lpthread \
  -I./libshm_vars \
  -L./libshm_vars \
  -lshm_vars \
  -lrt \
  -lgobject-2.0


run: 
	sudo ./treadwall_basic_gui

