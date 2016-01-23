
#pragma once

#include "cCamera.h"
#include "cVector3D.h"

#define STEP_LENGTH	0.5f

class cPlayer  
{
public:
	cPlayer();
	virtual ~cPlayer();

	void Init(int cx,int cy);

	void Move(cVector3D pos);
	void Look();
	void Update(bool keys[256], int mouseX, int mouseY, object *plane);

	void GetPosition(cVector3D *pos);
	void GetRotated(cVector3D *rot);

private:
	cCamera Camera;
	
};

