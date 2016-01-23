
#include <windows.h> 
#include <gl/freeglut.h>
#include <stdio.h>
#include <math.h>
#include "cScene.h"
#include "cPlayer.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define SCREEN_Xo		100
#define SCREEN_Yo		100

cScene Scene;
cPlayer Player;

//User Input Control
bool keys[265];		// Lookup table for keyboard state 
int  mouseX,mouseY;
bool input;

//OpenGL initializations
bool init(void)
{
	bool res;

	glClearColor(0.0f,0.0f,0.0f,0.0f);	// Background
	glEnable(GL_DEPTH_TEST);

	input = false;
	mouseX = SCREEN_WIDTH >> 1;
	mouseY = SCREEN_HEIGHT >> 1;
	glutWarpPointer(glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2);

	Player.Init(mouseX, mouseY);
	
	res = Scene.Init();

	return res;
}

//Rendering
void GameRender(void)   
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	Scene.Render(&Player);

    glutSwapBuffers();					//Swap makes rendering visible
}

//Reshaping handler (required even in fullscreen-only modes)
void GameReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Calculate the aspect ratio and set the clipping volume
	gluPerspective(45, (float)w/(float)h, 0.1, 10000.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Keyboard handler (normal keys)
void GameKeyboard(unsigned char key, int x, int y)
{
	input = true;
	keys[key] = true;
	switch (key)
	{
		case 27: exit(0);			break;
	}
}
//Keyboard handler (normal keys) releases
void GameKeyboardUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}

//Keyboard handler for special keys (like arrow keys and function keys)
void GameSpecialKeys(int a_keys, int x, int y)
{
	input = true;
	keys[a_keys] = true;
}

//Keyboard handler for special key releases.
void GameSpecialKeysUp(int a_key, int x, int y)
{
	keys[a_key] = false;
}

void GameMouse(int x, int y)
{
	input = true;
	mouseX = x - glutGet(GLUT_WINDOW_X);
	mouseY = y - glutGet(GLUT_WINDOW_Y);
}

//Check the user input and performs the rendering
void GameLoop()
{
	int t1, t2;
	t1 = glutGet(GLUT_ELAPSED_TIME);

	//Process Input
	if (input)
	{
		Player.Update(keys, mouseX, mouseY, Scene.GetMap());
		glutWarpPointer(glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2);
		input = false;
	}

	//Do The Rendering
	GameRender();

	// Frame rate sync: 1000/20 = 50 fps
	do { t2 = glutGet(GLUT_ELAPSED_TIME); 
	} while (t2 - t1 < 20);	
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);										// GLUT initialization
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);	// Display mode (rgb and double buffered)
	
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_Xo,SCREEN_Yo);
	glutCreateWindow("Navigation Camera: mouse and arrow keys");

	glutSetCursor(GLUT_CURSOR_NONE);							// Make the default cursor disappear
	init();
	glutDisplayFunc(GameRender);								// Register the display function
	glutReshapeFunc(GameReshape);								// Register the Reshape handler
	glutKeyboardFunc(GameKeyboard);								// Register the keyboard handler
	glutKeyboardUpFunc(GameKeyboardUp);								// Called when a keyboard released
	glutSpecialFunc(GameSpecialKeys);							// Register special keys handler
	glutSpecialUpFunc(GameSpecialKeysUp);						// Called when a special key released
	glutPassiveMotionFunc(GameMouse);
	glutIdleFunc(GameLoop);										// Process user input and does rendering
	glutMainLoop();												// Go to GLUT main loop
}