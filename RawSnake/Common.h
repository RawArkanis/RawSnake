#ifndef __RGL_COMMON_H__
#define __RGL_COMMON_H__

#include <Windows.h>
#include <iostream>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "GL/GL.h"
#include "GL/GLU.h"

const std::string GAME_NAME = "RawSnake";

const int GAME_WIDTH = 800;
const int GAME_HEIGHT = 600;

const int GAME_BPP = 32;

const bool GAME_FULLSCREEN = false;

const int FOVY = 45;
const double ZNEAR = 0.1;
const double ZFAR = 1000.0;

#define GL_BGRA 0x80E1

inline void ViewOrtho()
{ 
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
  
	glOrtho(0, GAME_WIDTH, GAME_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

inline void ViewPerspective(void)
{
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

inline void DrawBox(float x0, float y0, float z0, float xf, float yf, float zf)
{
    // BACK
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(x0, y0, z0);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(x0, yf, z0);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xf, yf, z0);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xf, y0, z0);
    glEnd();

    // FRONT
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(x0, y0, zf);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xf, y0, zf);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xf, yf, zf);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(x0, yf, zf);
    glEnd();

    // LEFT
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(x0, y0, z0);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(x0, y0, zf);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(x0, yf, zf);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(x0, yf, z0);
    glEnd();

    // RIGHT
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xf, y0, z0);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(xf, yf, z0);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(xf, yf, zf);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xf, y0, zf);
    glEnd();

    // TOP
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(x0, yf, z0);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(x0, yf, zf);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xf, yf, zf);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xf, yf, z0);
    glEnd();

    // BOTTOM
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2d(0.0f, 1.0f);
    glVertex3f(x0, y0, z0);
    glTexCoord2d(1.0f, 1.0f);
    glVertex3f(xf, y0, z0);
    glTexCoord2d(1.0f, 0.0f);
    glVertex3f(xf, y0, zf);
    glTexCoord2d(0.0f, 0.0f);
    glVertex3f(x0, y0, zf);
    glEnd();
}

inline int LoadTexture(const std::string &name)
{
	GLuint index;

	SDL_Surface *image = IMG_Load(name.c_str());

	if (image)
	{
		glGenTextures(1, &index);

		glBindTexture(GL_TEXTURE_2D, index);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		GLint format = image->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
		SDL_FreeSurface(image);

		return index;
	}

	else return -1;
}

#endif
