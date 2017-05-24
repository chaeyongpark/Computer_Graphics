/*
* [CSED451] POSTECH Computer Graphics assn 4
* Two acorns
* pcy8201, lshhhhh
*
* 2016.05 
*/

#include <iostream>
#include <windows.h>
#include "Angel.h"
#include <gl/gl.h>
#include <gl/glut.h>
#include <ctime>
#include <cstdlib>
#include "Obj.h"
#include "Map.h"
#include "model.h"
#define GLOBALTIMER 16
using namespace std;

Map *map;
mat4 projection;

/* isCollision? */
bool isCollision(float x, float y, float sizeX, float sizeY, float cx, float cy, float size) {
	float right = cx + size / 2;
	float left = cx - size / 2;
	float top = cy + size / 2;
	float bot = cy - size / 2;

	float leftLine = x - sizeX / 2;
	float rightLine = x + sizeX / 2;
	float topLine = y + sizeY / 2;
	float botLine = y - sizeY / 2;

	if (leftLine < left && left < rightLine) {
		if (botLine < top && top < topLine)
			return true;
		else if (botLine < bot && bot < topLine)
			return true;
		else
			return false;
	}
	else if (leftLine < right && right < rightLine) {
		if (botLine < top && top < topLine)
			return true;
		else if (botLine < bot && bot < topLine)
			return true;
		else
			return false;
	}
	else
		return false;

}

/* Reaction without input */
void reaction_without_input() {
	vector<Road*> vecRoad = map->getVecRoad();
	int num = vecRoad.size();
	int check_collision = 0;

	if (map->getGameOver() == 1 || map->getGameOver() == 2)
		return;

	for (int i = 0; i < num; i++) {
		if (vecRoad[i]->getName() == map->getPlayer()->getState()) {
			float playX = map->getPlayer()->getX();
			float playY = map->getPlayer()->getY();

			switch (vecRoad[i]->getType()) {
			case 0: {
				int car_num = vecRoad[i]->getCar().size();
				for (int j = 0; j < car_num; j++) {
					float carX = vecRoad[i]->getCar()[j]->getX();
					float carY = vecRoad[i]->getCar()[j]->getY();
					float carH = vecRoad[i]->getCar()[j]->getHeight();
					float carW = vecRoad[i]->getCar()[j]->getWidth();

					if (isCollision(carX, carY, carW, carH, playX, playY, 50) == true) {
						cout << "collision with car!" << endl;
						map->setGameOver(1);
					}
				} break;
			}
			case 2: {
				float trainX = vecRoad[i]->getTrain()->getX();
				float trainY = vecRoad[i]->getTrain()->getY();

				if (isCollision(trainX, trainY-200, 80, 500, playX, playY, 50) == true) {
					cout << "collision with Train!" << endl;
					map->setGameOver(1);
				} break;
			}
			case 3: {
				int obs_num = vecRoad[i]->getWood().size();
				for (int j = 0; j < obs_num; j++) {
					float woodY = vecRoad[i]->getWood()[j]->getY();
					float woodH = vecRoad[i]->getWood()[j]->getHeight();

					if (vecRoad[i]->getProp() == 1)
						map->getPlayer()->move(0, -vecRoad[i]->getSpeed());
					else
						map->getPlayer()->move(0, vecRoad[i]->getSpeed());
					cout << "in water " << vecRoad[i]->getWood()[0]->getSpeed() << endl;
					check_collision = 1;
					break;
				}
				if (check_collision == 0)
					map->setGameOver(2);
				break;
			}
			default:
				break;
			}
		}
	}
}

/* Draw */
void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);
	reaction_without_input();
	if (map->getLoadState() < 2)
		map->drawAcorns();
	else if (map->getLoadState() == 2)
		map->drawChicken();
	else
		map->drawAll();
	glutSwapBuffers();
	glFlush();
}

/* Input key */
void keyboard(unsigned char key, int x, int y) {
	if (map->getLoadState() == 1) {
		map->setLoadState(2);
		return;
	} // before loading 

	switch (key) {
	case '1':
		map->setView(1);
		return;
	case '2':
		map->setView(2);
		return;
	case '3':
		map->setView(3);
		return;
	case '4':
		map->setView(4);
		return;
	case '5':
		map->setView(5);
		return;
	case 'm':
		if (map->getMode() == 0)
			map->setMode(1);
		else if (map->getMode() == 1)
			map->setMode(2);
		else if (map->getMode() == 2)
			map->setMode(3);
		else
			map->setMode(0);
		return;
	case 'l':
		if (map->getLightMode() == 0)
			map->setLightPostion(1);
		else
			map->setLightPostion(0);
		return;
	case 'p':
		glClearColor(0.7, 0.9, 1.0, 0.0);
		map->setLoadState(3);
		map->setView(4);
		map->setMode(3);
		map->setLightPostion(0);
		return;
	default:
		if (map->getLoadState() == 2)
			return;
	}	

	if (map->getGameOver() == 0) {
		int next_y, next_state, cur_state, next_x;
		switch (key) {
		case 'w':
			if (map->getView() == 3) {
				map->getPlayer()->setDirection(-1);
				next_x = map->getPlayer()->getX();
				next_y = map->getPlayer()->getY() + 77;	
				next_state = map->getPlayer()->getState();
			}
			else {
				if (map->getPlayer()->getDirection() == -1) {
					next_x = map->getPlayer()->getX();
					next_y = map->getPlayer()->getY() + 77;
					next_state = map->getPlayer()->getState();
				}
				else if (map->getPlayer()->getDirection() == 0) {
					next_x = map->getPlayer()->getX() + 96;
					next_y = map->getPlayer()->getY();
					next_state = map->getPlayer()->getState() + 1;
				}
				else {
					next_x = map->getPlayer()->getX();
					next_y = map->getPlayer()->getY() - 77;
					next_state = map->getPlayer()->getState();
				}				
			}
			break;
		case 's':
			if (map->getView() == 3) {
				map->getPlayer()->setDirection(1);
				next_x = map->getPlayer()->getX();
				next_y = map->getPlayer()->getY() - 77;
				next_state = map->getPlayer()->getState();
			}
			else {
				if (map->getPlayer()->getDirection() == -1) {
					next_x = map->getPlayer()->getX();
					next_y = map->getPlayer()->getY() - 77;
					next_state = map->getPlayer()->getState();
				}
				else if (map->getPlayer()->getDirection() == 0) {
					next_x = map->getPlayer()->getX() - 96;
					next_y = map->getPlayer()->getY();
					next_state = map->getPlayer()->getState() - 1;
				}
				else {
					next_x = map->getPlayer()->getX();
					next_y = map->getPlayer()->getY() + 77;
					next_state = map->getPlayer()->getState();
				}
			}
			break;
		case 'a':
			if (map->getView() == 3) {
				map->getPlayer()->setDirection(0);
				next_x = map->getPlayer()->getX() - 96;
				next_y = map->getPlayer()->getY();
				next_state = map->getPlayer()->getState() - 1;
			}
			else {
				if (map->getPlayer()->getDirection() == 0)
					map->getPlayer()->setDirection(-1);
				else if (map->getPlayer()->getDirection() == 1)
					map->getPlayer()->setDirection(0);
				cout << "click A!" << endl;
				return;
			}
			break;
		case 'd':
			if (map->getView() == 3) {
				map->getPlayer()->setDirection(0);
				next_x = map->getPlayer()->getX() + 96;
				next_y = map->getPlayer()->getY();
				next_state = map->getPlayer()->getState() + 1;
			}
			else {
				if (map->getPlayer()->getDirection() == 0)
					map->getPlayer()->setDirection(1);
				else if (map->getPlayer()->getDirection() == -1)
					map->getPlayer()->setDirection(0);
				cout << "click E!" << endl;
				return;
			}
			break;
		default:
			return;
		}

		vector<Road*> vecRoad = map->getVecRoad();
		int num = vecRoad.size();
		int check_collision = 0;

		for (int i = 0; i < num; i++) {
			if (vecRoad[i]->getName() == next_state) {
				float playY = map->getPlayer()->getY();
				float playX = map->getPlayer()->getX();
				float playH = map->getPlayer()->getHeight();

				switch (vecRoad[i]->getType()) {
				case 0: {
					int car_num = vecRoad[i]->getCar().size();
					for (int j = 0; j < car_num; j++) {
						float carX = vecRoad[i]->getCar()[j]->getX();
						float carY = vecRoad[i]->getCar()[j]->getY();
						float carH = vecRoad[i]->getCar()[j]->getHeight();
						float carW = vecRoad[i]->getCar()[j]->getWidth();

						if (isCollision(carX, carY, carW, carH, next_x, next_y, 50) == true) {
							cout << "collision with car!" << endl;
							map->setGameOver(1);
						}
					}
					map->getPlayer()->keyboard(key, x, y);
					break;
				}
				case 1: {
					int obs_num = vecRoad[i]->getObs().size();
					for (int j = 0; j < obs_num; j++) {
						float obsX = vecRoad[i]->getObs()[j]->getX();
						float obsY = vecRoad[i]->getObs()[j]->getY();					

						if (isCollision(obsX, obsY, 80, 80, next_x, next_y, 70) == true) {
							cout << "collision with tree!" << endl;
							check_collision = 1;
						}
					}
					if (check_collision == 0)
						map->getPlayer()->keyboard(key, x, y);
					break;
				}
				case 2: {
					float trainX = vecRoad[i]->getTrain()->getX();
					float trainY = vecRoad[i]->getTrain()->getY();

					cout << trainY << endl;

					if (isCollision(trainX, trainY-200, 80, 500, playX, playY, 70) == true) {
						cout << "collision with Train!" << endl;
						map->setGameOver(1);
					}
					map->getPlayer()->keyboard(key, x, y);
					break;
				}
				case 3: {
					int obs_num = vecRoad[i]->getWood().size();
					for (int j = 0; j < obs_num; j++) {
						float woodX = vecRoad[i]->getWood()[j]->getX();
						float woodY = vecRoad[i]->getWood()[j]->getY();
						float woodH = vecRoad[i]->getWood()[j]->getHeight();
						float center;

						if (woodH == 160)
							center = woodY - 40;
						else
							center = woodY - 80;	
							
						if (isCollision(woodX, center, 80, woodH+20, next_x, next_y, 30) == true) {
							float diff = next_y - center;

							/* Stabilize */
							if (next_y == playY) {
								if (woodH == 160) {
									if (diff >= 0)
										map->getPlayer()->setY(center + 40);
									else
										map->getPlayer()->setY(center - 40);
								}
								else {
									if (diff >= 40)
										map->getPlayer()->setY(center + 80);
									else if (diff <= -40)
										map->getPlayer()->setY(center - 80);
									else
										map->getPlayer()->setY(center);
								}
							}

							cout << "go to wood!" << endl;
							map->getPlayer()->keyboard(key, x, y);
							check_collision = 1;
						}
					}
					if (check_collision == 0) {
						map->getPlayer()->setY(next_y);
						map->getPlayer()->setX(next_x);
						map->setGameOver(2);
					}
					break;
				}
				default:
					break;
				}
			}
		}
	}
	else {
		switch (key) {
		case 'y':
			map->reset();
			break;
		case 'n':
			exit(0);
			break;
		default:
			break;
		}
	}

}

/* Initiate */
void init(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA ); /* depth? */
	glutInitWindowSize(960, 540);
	glutInitWindowPosition(500, 200);

	glutInitContextVersion(3, 2); 
	glutInitContextProfile(GLUT_CORE_PROFILE); 
	glutCreateWindow("Computer Graphics");

	glewExperimental = GL_TRUE; 
	glewInit(); 

	glShadeModel(GL_FLAT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);

	glDepthFunc(GL_LEQUAL);

	srand(time(NULL));
	map = new Map();
	map->loadewindow();
}

/* Reshape */
void myReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);	
}

/* timer */
void timer(int value) {
	if(map->getLoadState() < 3)
		glClearColor(0.0, 0.0, 0.0, 0.0);

	else if(map->getMode() == 0)
		glClearColor(1.0, 1.0, 1.0, 1.0);
	else
		glClearColor(0.7, 0.9, 1.0, 0.0);

	if (map->getView() == 1) { // First-person perspective
		vec4 at = vec4(map->getCameraMoveX() + map->getRotX()/ 4 , map->getCametaMoveY() + map->getRotY(), 40.0, 1.0);
		vec4 eye = at + vec4(-1 *map->getRotX(), -1* map->getRotY(), 10.0, 0.0);
		vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
		projection = LookAt(eye, at, up);
		projection = Perspective(20, 2, 10, 2000) * projection;
	}
	else if (map->getView() == 2) { // third-person Perspective
		vec4 at = vec4(map->getCameraMoveX() + map->getRotX() * 4, map->getCametaMoveY() + map->getRotY() * 5, 40.0, 1.0);
		vec4 eye = at + vec4(-10.5 * map->getRotX() , -15 * map->getRotY() , 200.0, 0.0);
		vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
		projection = LookAt(eye, at, up);
		projection = Perspective(20, 2, 10, 2000) * projection;		
	}
	else if (map->getView() == 3) {	// Ortho viewpoint	
		projection = Ortho(map->getCameraMoveX()-192, 768.0 + map->getCameraMoveX(), 0.0, 540.0, -100.0, 100.0);
	}
	else if (map->getView() == 4) { // Diagonal ViewPoint 
		vec4 at = vec4(map->getCameraMoveX(), -20+ map->getCametaMoveY(), 40.0, 1.0);
		vec4 eye = at + vec4(-500.0, -200.0, 150.0, 0.0);
		vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
		projection = LookAt(eye, at, up);
		projection = Perspective(20, 2, 10, 2000) * projection;
	}
	else if (map->getView() == 5) { // Front ViewPoint
		vec4 at = vec4(200 + map->getCameraMoveX(), map->getCametaMoveY(), 40.0, 1.0);
		vec4 eye = at + vec4(90.0, 0.0, 5.0, 0.0);
		vec4 up = vec4(0.0, 0.0, 1.0, 0.0);
		projection = LookAt(eye, at, up);
		projection = Perspective(20, 2, 10, 2000) * projection;
	}
	map->calRot();

	map->calCameraMoveX();
	map->calCameraMoveY();
	glUniformMatrix4fv(map->projection_loc, 1, GL_TRUE, projection);
	glutPostRedisplay();

	glutTimerFunc(GLOBALTIMER, timer, value);
}

/* main */
int main(int argc, char **argv) {
	init(argc, argv);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(Draw);
	glutKeyboardFunc(keyboard);
	timer(0);
	glutMainLoop();

	return 0;
}