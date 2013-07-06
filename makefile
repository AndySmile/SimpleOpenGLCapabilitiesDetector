# /**
#  * Simple OpenGL Capabilities Detector.
#  * 
#  * @author	Andy Liebke<coding@andysmiles5games.com>
#  * @version 	1.0.0 01-Jul-13
#  * @version	1.1.0 06-Jul-13
#  * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved.
#  */

APP_TITLE = SimpleOpenGLCapabilitiesDetector
LIST_OBJECTS = 	Build/SimpleOpenGLCapabilitiesDetectorMain.o

DEBUG_SETTINGS =  -g -D_DEBUG
COMMON_SETTINGS = $(DEBUG_SETTINGS) -Weffc++ -Wall -pedantic-errors -ansi -std=c++98 -I Source/

.PHONY: build
build: build-executable
	
.PHONY: build-executable
build-executable: $(LIST_OBJECTS) 
	g++ -framework OpenGL -framework Glut -o $(APP_TITLE) $^
	
Build/%.o: Source/%.cpp
	g++ $(COMMON_SETTINGS) -c $^ -o $@ 

.PHONY: clean
clean:
	rm -f Build/*
	rm -f $(APP_TITLE)
	
.PHONY: leakcheck
leakcheck:
	rm -f *.log
	rm -rf *.dSYM
	valgrind --leak-check=full --suppressions=./SuppressedErrorList.supp -v --track-origins=yes --log-file=$(APP_TITLE)-Mem.log --dsymutil=yes ./$(APP_TITLE)