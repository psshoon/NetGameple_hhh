#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Define.h"
#include "SceneMgr.h"

DWORD prevTime = 0;
SOCKET sock;



void RenderScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DWORD curTime = timeGetTime();
	DWORD elapsedTime = curTime - prevTime;
	prevTime = curTime;

	SceneMgr::GetInstance()->Update(elapsedTime);
	SceneMgr::GetInstance()->Render();

	glutSwapBuffers();
}

void Update(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	SceneMgr::GetInstance()->GetKey(key);

	RenderScene();
}

void KeyInputUp(unsigned char key, int x, int y)
{
	SceneMgr::GetInstance()->GetKeyUp(key);

	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(WINDOWSIZEX / 2), (WINDOWSIZEX / 2), -(WINDOWSIZEY / 2), (WINDOWSIZEY / 2));
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZEX, WINDOWSIZEY);
	glutCreateWindow("NetworkGameProgamming");

	glewInit();

	// Initialize Renderer
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Update);
	glutKeyboardFunc(KeyInput);
	glutKeyboardUpFunc(KeyInputUp);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutReshapeFunc(Reshape);

	prevTime = timeGetTime();
	glutMainLoop();

    return 0;
}

