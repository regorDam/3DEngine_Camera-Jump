
#pragma once

#include <gl\freeglut.h>

#define PI			3.1415265359
#define PIdiv180	0.0174529252
#define JUMP_HEIGHT			20
#define JUMP_STEP			4

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

#include "cVector3D.h" 

struct object
{
	float x, y, z;
	int width;
	int height;
	int depth;
	float radius_x;
	float radius_y;
	float radius_z;
};



class cCamera
{
private:
	cVector3D Position;
	cVector3D ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	GLfloat RotatedX, RotatedY, RotatedZ;

	int middleX,middleY;
	float speed;

	void GetViewDir (void);

public:
	cCamera();						
	void Init(int cx,int cy,float s);	//necessary for input updates
	void Look();						//glRotate+glTranslate commands
	
	void Rotate	(cVector3D Angles);
	void Update (bool keys[256], int mouseX, int mouseY, object *plane);

	void GetPosition(cVector3D *pos);
	void GetRotated(cVector3D *rot);
	void SetPosition(cVector3D pos);
	void MoveForwards(GLfloat distance);
	bool CollidesMap(object *obj1, object *obj2);
	object* cCamera::GetCollider();
	void Jump();

private:
	void RotateX(GLfloat angle);
	void RotateY(GLfloat angle);
	void RotateZ(GLfloat angle);

	void StrafeRight(GLfloat distance);
	void Folk(GLfloat distance);

	object collider;
	object *Map;

	const float piover180 = 0.0174532925f;
	float heading;
	GLfloat walkbias = 0;
	GLfloat walkbiasangle = 0;
	bool onFloor;
	
	//Jumping control
	bool jumping;
	int jump_alfa;
	int jump_y;
};

