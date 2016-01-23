
#include "cPlayer.h"
#include "cScene.h"
#include <gl/glut.h>
#include <math.h>
#include <stdio.h>



cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Init(int cx,int cy)
{
	Camera.Init(cx,cy,STEP_LENGTH);
	

}
void cPlayer::Look()
{
	Camera.Look();
}
void cPlayer::Update(bool keys[],int mouseX,int mouseY, object *plane)
{
	Camera.Update(keys,mouseX,mouseY, plane);
}
void cPlayer::Move(cVector3D pos)
{
	Camera.SetPosition(pos);
}
void cPlayer::GetPosition(cVector3D *pos)
{
	Camera.GetPosition(pos);
}
void cPlayer::GetRotated(cVector3D *rot)
{
	Camera.GetRotated(rot);
}

