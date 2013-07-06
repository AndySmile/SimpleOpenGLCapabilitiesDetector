/**
 * @mainpage Simple OpenGL Capabilities Detector.
 *
 * This tool detects several features supported by GPU. It runs on Windows and Mac OS X as well.
 *
 * @todo Add linux support!
 *
 * LICENSE:
 *	
 *	The MIT License (MIT)
 *
 *	Copyright (c) 2013 by Andy Liebke. All rights reserved.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 *
 * @author		Andy Liebke<coding@andysmiles4games.com>
 * @version 	1.0.0 01-Jul-13
 * @version		1.1.0 02-Jul-13
 * @version		1.2.0 03-Jul-13
 * @version		1.2.1 05-Jul-13
 * @copyright	Copyright (c) 2013 by Andy Liebke. All rights reserved. (http://www.andysmiles4games.com)
 */
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <Glut/glut.h>
#elif WIN32
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

/**
 * Performs this application as start point.
 *
 * @return 	integer value including 0 in case this application terminates successfully,
 *			otherwise -1
 */
int main(void)
{
	// initilizes GLUT library and Glew library (windows only)
	int argc = 1;
	char* argv[1];
	
	argv[0] = strdup("Simple OpenGL Capabilities Detector -gldebug");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Simple OpenGL Capabilities Detector");

#ifdef WIN32
	GLenum glewInitError = glewInit();

	if(glewInitError != GLEW_OK){
		std::cout << "Glew Init Failure: " << glewGetErrorString(glewInitError) << std::endl;
	}
	else
	{
#endif
		// determine hardware and driver information
#ifdef GL_VERSION_3_0	
		int numExtensions = 0;
	
		glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
#else
		unsigned char* listExtensions = (unsigned char*)glGetString(GL_EXTENSIONS);
#endif

		int numCompressedTextureFormats = 0;
	
	
		glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCompressedTextureFormats);
	
		int *compressedTextureFormats = new int[numCompressedTextureFormats];
	
		glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, compressedTextureFormats);
	
		// print out all detected information
		std::cout << "--> OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl; 
		std::cout << "--> OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl; 
		std::cout << "--> OpenGL Version: " << glGetString(GL_VERSION) << std::endl; 
		std::cout << "--> Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "--> Number of available compressed texture formats: " << numCompressedTextureFormats << std::endl;
		std::cout << "--> Available compressed texture formats: " << std::endl;

		for(int i=0;i < numCompressedTextureFormats;++i)
		{
			switch(compressedTextureFormats[i])
			{
#ifdef GLEW_EXT_texture_compression_s3tc			
				case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:{
					std::cout << "-----> RGB S3TC DXT1" << std::endl;
				}break;
			
				case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:{
					std::cout << "-----> RGBA S3TC DXT1" << std::endl;
				}break;
			
				case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:{
					std::cout << "-----> RGBA S3TC DXT3" << std::endl;
				}break;
			
				case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:{
					std::cout << "-----> RGBA S3TC DXT5" << std::endl;
				}break;
#endif

#ifdef GLEW_3DFX_texture_compression_FXT1
				case GL_COMPRESSED_RGB_FXT1_3DFX:{
					std::cout << "-----> RGB FXT1 3DFX" << std::endl;
				}break;

				case GL_COMPRESSED_RGBA_FXT1_3DFX:{
					std::cout << "-----> RGBA FXT1 3DFX" << std::endl;
				}break;
#endif			
				default:{
					printf("-----> Unknown Compressed Texture Format: %X\n", compressedTextureFormats[i]);
				}break;
			}
		}

		delete[] compressedTextureFormats;

		compressedTextureFormats = NULL;

#ifdef GL_VERSION_3_0
		std::cout << "--> Number of available extensions: " << numExtensions << std::endl;
#else
		std::cout << "--> Extension List: " << std::endl;
		std::cout << "-----> ";
	
		while(*listExtensions != '\0')
		{
			if(*listExtensions == ' '){
				std::cout << "\n-----> ";
			}
			else{
				std::cout << (char)(*listExtensions);
			}
		
			++listExtensions;
		}
	
		std::cout << "Done!" << std::endl;
#endif

#ifdef WIN32
	}

	char continueChar = 0;

	std::cout << "\nPlease, enter any key to terminate this application!" << std::endl;
	std::cin >> continueChar;
#endif

	return EXIT_SUCCESS;
}