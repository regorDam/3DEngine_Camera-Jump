
#include "cScene.h"
#include <gl/freeglut.h>
#include <string.h>
#include <math.h>

cScene::cScene() {}
cScene::~cScene(){}

bool cScene::Init()
{
	plane.x = 0;
	plane.y = 0;
	plane.z = 0;
	plane.depth = SIZE;
	plane.height = SIZE;
	plane.width = SIZE;
	plane.radius_x = SIZE * 8;
	plane.radius_y = 1;
	plane.radius_z = SIZE * 10;
	return true;
}

void cScene::Render(cPlayer *Player)
{
	Player->Look();
	

	//Room
	glColor3f(1.0f,1.0f,1.0f);
	glPushMatrix();
		glScalef(8.0f,1.0f,10.0f);
		RenderRoom();
	glPopMatrix();
}

void cScene::RenderRoom()
{
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-SIZE,-SIZE,-SIZE);
		glVertex3f(-SIZE, SIZE,-SIZE);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( SIZE,-SIZE,-SIZE);
		glVertex3f( SIZE, SIZE,-SIZE);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( SIZE,-SIZE, SIZE);
		glVertex3f( SIZE, SIZE, SIZE);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(-SIZE,-SIZE, SIZE);
		glVertex3f(-SIZE, SIZE, SIZE);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-SIZE,-SIZE,-SIZE);
		glVertex3f(-SIZE, SIZE,-SIZE);
	glEnd();

	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-SIZE, -SIZE, -SIZE);
		glVertex3f(SIZE, -SIZE, -SIZE);
		glVertex3f(SIZE, -SIZE, SIZE);
		glVertex3f(-SIZE, -SIZE, SIZE);
	glEnd();
}