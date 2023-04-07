out=./main
libs=-lGL -lglut -lGLU -lglfw

clean:
	rm -f $(out)

build:
	g++ Shapes.cpp $(libs) -o $(out)

run:
	make build
	vblank_mode=0 $(out) # disable vsync for linux systems
