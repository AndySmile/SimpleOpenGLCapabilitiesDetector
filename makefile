# /**
#  * Simple OpenGL Capabilities Detector.
#  * 
#  * LICENSE:
#  *	
#  *	The MIT License (MIT)
#  *
#  *	Copyright (c) 2013 by Andy Liebke. All rights reserved.
#  *
#  *	Permission is hereby granted, free of charge, to any person obtaining a copy
#  * 	of this software and associated documentation files (the "Software"), to deal
#  *	in the Software without restriction, including without limitation the rights
#  *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  *	copies of the Software, and to permit persons to whom the Software is
#  *	furnished to do so, subject to the following conditions:
#  *
#  *	The above copyright notice and this permission notice shall be included in
#  *	all copies or substantial portions of the Software.
#  *
#  *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  *	THE SOFTWARE.
#  *
#  * @author	Andy Liebke<coding@andysmiles5games.com>
#  * @version 	1.0.0 01-Jul-13
#  * @version	1.1.0 06-Jul-13
#  * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://www.andysmiles4games.com)
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