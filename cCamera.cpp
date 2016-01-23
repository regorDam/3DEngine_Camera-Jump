
#include <math.h>
#include "cCamera.h"

cCamera::cCamera()
{
}

void cCamera::Init(int cx,int cy,float s)
{
	//Init with standard OGL values:
	Position = cVector3D(0.0,40.0,0.0);
	ViewDir  = cVector3D(0.0,0.0,-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	//Screen
	middleX = cx;
	middleY = cy;
	//Step length
	speed = s;


	jumping = false;
}

object* cCamera::GetCollider()
{
	collider.x = Position.x;
	collider.y = Position.y;
	collider.z = Position.z;
	collider.depth = 1;
	collider.height = 1;
	collider.width = 1;
	collider.radius_x = 1;
	collider.radius_y = 1;
	collider.radius_z = 1;
	
	return &collider;
}

void cCamera::Look()
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}

void cCamera::GetPosition(cVector3D *pos)
{
	*pos = Position;
}

void cCamera::SetPosition(cVector3D pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
}

void cCamera::GetRotated(cVector3D *rot)
{
	*rot = cVector3D(RotatedX,RotatedY,RotatedZ);
}

void cCamera::Rotate(cVector3D v)
{
	RotatedX = v.x;
	RotatedY = v.y;
	RotatedZ = v.z;
	ViewDirChanged = true;
}

void cCamera::Update(bool keys[],int mouseX,int mouseY, object *plane)
{
	float angle;
	float alfa;
	Map = plane;
	if(mouseX!=middleX)
	{
		angle = (middleX - mouseX) / 50.0f;
		RotateY(angle);
	}
	if(mouseY!=middleY)
	{
		angle = (middleY - mouseY) / 50.0f;
		RotateX(angle);
	}

	if (keys['w'])		MoveForwards(-speed);
	if (keys['s'])		MoveForwards(speed);
	if (keys['a'])		StrafeRight(-speed);
	if (keys['d'])		StrafeRight(speed);
	if (keys[' '])		Jump();


	// JUMP & GRAVITY
	if (jumping)
	{
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180)
		{
			jumping = false;
			Position.y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			Position.y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

			if (jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMap(GetCollider(), Map);
			}
		}
	}
	else
	{
		//Over floor?
		if (!CollidesMap(GetCollider(), Map))
			Position.y -= (2 * speed);
	}


}



void cCamera::GetViewDir(void)
{
	cVector3D Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = -sin( (RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180);
	Step2.x = Step1.x * cosX;
	Step2.z = Step1.z * cosX;
	Step2.y = sin(RotatedX * PIdiv180);
	//Rotation around Z-axis not implemented, so:
	ViewDir = Step2;
}

void cCamera::RotateX (GLfloat angle)
{
	RotatedX += angle;
	ViewDirChanged = true;
}

void cCamera::RotateY (GLfloat angle)
{
	RotatedY += angle;
	ViewDirChanged = true;
}

void cCamera::RotateZ (GLfloat angle)
{
	RotatedZ += angle;
	ViewDirChanged = true;
}

void cCamera::MoveForwards( GLfloat distance )
{
	bool col;
	if (ViewDirChanged) GetViewDir();
	cVector3D MoveVector;
	MoveVector.x = ViewDir.x * -distance;
	MoveVector.y = ViewDir.y * -distance;
	MoveVector.z = ViewDir.z * -distance;
	
	if (CollidesMap(GetCollider(), Map))
		MoveVector.y = 0;
	else
		MoveVector.y = -1;
	Position.Add(MoveVector);
}

void cCamera::StrafeRight ( GLfloat distance )
{
	if (ViewDirChanged) GetViewDir();
	cVector3D MoveVector;
	MoveVector.z = -ViewDir.x * -distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -distance;

	if (CollidesMap(GetCollider(), Map))
		MoveVector.y = 0;
	else
		MoveVector.y = -1;
	Position.Add(MoveVector);
}

void cCamera::Folk(GLfloat distance)
{
	cVector3D MoveVector;
	MoveVector.x = 0.0;
	MoveVector.y = 1.0 * distance;
	MoveVector.z = 0.0;
	
	if (CollidesMap(GetCollider(), Map))
	{
		onFloor = true;
	}
	else
	{
		Position.Add(MoveVector);
	}
}
void cCamera::Jump()
{
	if (!jumping)
	{
		if (CollidesMap(GetCollider(), Map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = Position.y;
		}
	}
		
}

bool cCamera::CollidesMap(object *obj1, object *obj2)
{
	int center_x1 = obj1->x + (obj1->width >> 1);
	int center_y1 = obj1->y + (obj1->height >> 1);
	int center_z1 = obj1->z + (obj1->depth >> 1);

	int center_x2 = obj2->x + (obj2->width >> 1);
	int center_y2 = obj2->y + (obj2->height >> 1);
	int center_z2 = obj2->z + (obj2->depth >> 1);

	int delta_x = abs(center_x1 - center_x2);
	int delta_y = abs(center_y1 - center_y2);
	int delta_z = abs(center_z1 - center_z2);

	int sum_x = obj1->radius_x + obj2->radius_x;
	int sum_y = obj1->radius_y + obj2->radius_y;
	int sum_z = obj1->radius_z + obj2->radius_z;

	if (delta_x <= sum_x && delta_y <= sum_y && delta_z <= sum_z)
		return true;
	else
		return false;
}
