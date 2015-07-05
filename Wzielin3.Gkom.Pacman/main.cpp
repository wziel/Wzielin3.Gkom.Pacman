/*
* GKOM Lab. 3: OpenGL
*
* Program stanowi zaadaptowana wersje przykladu accnot.c.
*/

#include <windows.h>
#include "GL/gl.h"
#include "glut.h"

#include "Plane.h"
#include "Consts.h"
#include "Textures.h"
#include "Background.h"
#include "Camera.h"

Plane* plane;
Pacman* pacman;
Background* backGround;
Camera* camera;

void init()
{
	Textures::init();

	camera = new Camera();
	backGround = new Background(130, 70, 5);
	pacman = new Pacman();
	plane = new Plane();
	plane->start(pacman, 10);

	GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

void checkPacmanAlive()
{
	if (!pacman->isAlive())
	{
		pacman->resurect();
		if (!pacman->isAlive())
		{
			//TODO
			//GAME OVER
		}
		else
		{
			//delete all creatures except of pacman
			auto creatures = plane->clearCreatures();
			for (auto creature : creatures)
			{
				if (pacman != creature)
				{
					delete creature;
				}
			}
			plane->start(pacman, 10);
		}
	}

}

void displayLight()
{
	static float frame_no = 0;
	static float frame_dif = 0.5;
	if (frame_no < -15 || frame_no > 15) frame_dif = -frame_dif;
	frame_no += frame_dif;

	GLfloat light_position1[] = { frame_no, 10, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);

}

void display()
{
	checkPacmanAlive();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glPushMatrix(); 

	glTranslatef(0, 0, -30);
		glRotatef(270, 1, 0, 0);
		backGround->draw();
		backGround->update();
	glPopMatrix();

	camera->move();
	camera->createLook();

	displayLight();

	glPushMatrix();
		glScalef(1, 1, 1);
		plane->draw();
	glPopMatrix();

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	if (h > 0 && w > 0) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		double clip_far = 100;
		double clip_near = 1.0;
		double side = 1;

		if( w <= h ) {
			glFrustum(-side, side, -side*h / w, side*h / w, clip_near, clip_far);
		}
		else {
			glFrustum(-side*w / h, side*w / h, -side, side, clip_near, clip_far);
		}
		glTranslatef(0.0, 0.0, -3.5);

		glMatrixMode(GL_MODELVIEW);
	}
}

void keyEvent(unsigned char key, KeyEvent keyEvent)
{
	auto mapNode = keyToDirection.find(key);
	if (mapNode != keyToDirection.end())
	{
		pacman->go(mapNode->second);
	}
	auto cameraNode = keyToCamera.find(key);
	if (cameraNode != keyToCamera.end())
	{
		camera->registerEvent(cameraNode->second, keyEvent);
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		exit(0);
	}
	keyEvent(key, KeyEvent::Pressed);
}

void keyReleased(unsigned char key, int x, int y)
{
	keyEvent(key, KeyEvent::Released);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);

	glutCreateWindow("Wzielin3.Gkom.Pacman");

	glutFullScreen();

	glutIdleFunc(display);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	

	init();

	glutMainLoop();

	return 0;
}
