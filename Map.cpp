#include "Map.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

Map::Map() {
	count = 0; state = 5; loadState = 0; lightMode = 1;
    gameOver = 0; cameraMoveX = 28, cameraMoveY = 270;
	view = 1; rotX = 100; rotY = 0;
	mode = 1;

	light_position = vec4(1.0, 0.0, -1.0, 2.0);
	model = new Model();
}

/* Initialize all things */
void Map::init() {
	player = new Player();
	acorns = new Acorns();
	chicken = new Chicken();

	int make, check = 0, lineCount = 0; // if check == 1 then make road else no make
	Road * road[16];
	Line * line[16];

	for (int i = 0; i < 13; i++) {
		make = rand() % 17;
		int nansoo = make % 4;
		/*
		* 0,4 -> grass
		* 1,2,3,5,6,7,9,10,11,13,14,15 -> road
		* 16 -> train
		* 12 -> water
		*/
		if (nansoo == 0 || i  < 3) {
			/* make railroad */
			if (make == 16 && i > 3) {
				road[count] = new Road(count, 2);
				road[count]->makeTrain(count);
				vecRoad.push_back(road[count++]);

			}
			/* make nansoo-number river */
			else if (make == 12 && i > 3) {
				for (int j = 0; j < 2; j++) {
					road[count] = new Road(count, 3);
					road[count]->makeTrain(count);
					vecRoad.push_back(road[count++]);
				}
				i++;
			}
			/* make grass */
			else {
				road[count] = new Road(count, 1);
				if (i != 0) {
					road[count]->makeObs(count);
					road[count]->makeFlower(count);
				}
				vecRoad.push_back(road[count++]);
			}
		}
		else {
			/* make grass */
			if (check == 1) {
				road[count] = new Road(count, 1);
				road[count]->makeObs(count);
				road[count]->makeFlower(count);
				vecRoad.push_back(road[count++]);
				check = 0;
			}
			/* make nansoo-number roads */
			else {
				for (int j = 0; j < nansoo; j++) {
					road[count] = new Road(count, 0);
					vecRoad.push_back(road[count++]);
					check = 1;
				}
				/* Make line */
				count -= nansoo;
				for (int j = 0; j < nansoo - 1; j++) {					
					line[lineCount] = new Line(count++);
					vecLine.push_back(line[lineCount++]);
				}
				count++;
				i += nansoo - 1;
			}
		}
	}
}

void Map::shaderInit() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);

	ver_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(ver_loc);
	col_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(col_loc);
	texture_loc = glGetAttribLocation(program, "vTex");
	glEnableVertexAttribArray(texture_loc);	
	normal_loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_loc);
	mode_loc = glGetUniformLocation(program, "vMode");

	tangent_loc = glGetAttribLocation(program, "vT");
	glEnableVertexAttribArray(tangent_loc);
	binormal_loc = glGetAttribLocation(program, "vB");
	glEnableVertexAttribArray(binormal_loc);

	model_loc = glGetUniformLocation(program, "model_view");
	projection_loc = glGetUniformLocation(program, "projection");
	light_loc = glGetUniformLocation(program, "light_position");

	glUniform4fv(glGetUniformLocation(program, "ambientProduct"), 1, ambientProduct);	
	glUniform4fv(glGetUniformLocation(program, "diffuseProduct"), 1, diffuseProduct);
	glUniform4fv(glGetUniformLocation(program, "specularProduct"), 1, specularProduct);	
	glUniform1i(glGetUniformLocation(program, "myTexture"), 0);		
	glUniform1i(glGetUniformLocation(program, "myNormalMap"), 1);
	glUniform1f(glGetUniformLocation(program, "shininess"), shininess);		
}

/* Make road */
void Map::makeRoad() {
	Road * road[10];
	Line * line[10];
	int make, check = 0, temp = 0, lineCount=0;

	for (int i = 0; i < 5; i++) {
		make = rand() % 17;
		int nansoo = make % 4;

		if (nansoo == 0 || i == 0) {
			if (make == 16) {
				road[temp] = new Road(count, 2);
				road[temp]->makeTrain(count++);
				vecRoad.push_back(road[temp++]);
			}
			else if (make == 12) {
				for (int j = 0; j < 2; j++) {
					road[temp] = new Road(count, 3);
					road[temp]->makeTrain(count++);
					vecRoad.push_back(road[temp++]);
				}
				i++;
			}
			else {
				road[temp] = new Road(count, 1);
				road[temp]->makeObs(count);
				road[temp]->makeFlower(count++);
				vecRoad.push_back(road[temp++]);
			}
		}
		else {
			if (check == 1) {
				road[temp] = new Road(count, 1);
				road[temp]->makeObs(count);
				road[temp]->makeFlower(count++);
				vecRoad.push_back(road[temp++]);
				check = 0;
				continue;
			}
			for (int j = 0; j < nansoo; j++) {
				road[temp] = new Road(count++, 0);
				vecRoad.push_back(road[temp++]);
				check = 1;
			}
			/* Make line */
			count -= nansoo;
			for (int j = 0; j < nansoo - 1; j++) {
				line[lineCount] = new Line(count++);
				vecLine.push_back(line[lineCount++]);
			}
			count++;
			i += nansoo - 1;
		}
	}
}

/* Draw all(road, car, player, etc) */
void Map::drawAll() {
	/* Delete road */
	if (player->getState() > state) {
		makeRoad();
		for (int i = 0; i < 3; i++) {
			if (vecRoad.front()->getX() < cameraMoveX - 200)
				vecRoad.erase(vecRoad.begin());
		}
		state += 4;
	}

	int num = vecRoad.size();
	for (int i = 0; i < num; i++) {
		if (gameOver == 1 || gameOver == 2)
			vecRoad[i]->noUpdate();
		else {
			vecRoad[i]->update();
			if (vecRoad[i]->getCar().size() != 0) {
				if (vecRoad[i]->getCar().front()->checkEnd() == 1) {
					vecRoad[i]->deleteCar();
				}
			}
			else if (vecRoad[i]->getWood().size() != 0) {
				if (vecRoad[i]->getWood().front()->checkEnd() == 1) {
					vecRoad[i]->deleteWood();
				} // add Wood;
			}
		}
	}
	num = vecLine.size();
	for (int i = 0; i < num; i++)
		vecLine[i]->draw();
	player->draw();
}

void Map::drawAcorns() {
	acorns->draw();
}

void Map::drawChicken() {
	chicken->draw();
}

void Map::reset() {
	count = 0; state = 5;
	gameOver = 0; cameraMoveX = 28, cameraMoveY = 270;
	view = 4; rotX = 100; rotY = 0;
	delete(player);

	int num = vecRoad.size();
	for (int i = 0; i < num; i++)
		vecRoad.erase(vecRoad.begin());
	num = vecLine.size();
	for (int i = 0; i < num; i++)
		vecLine.erase(vecLine.begin());
	init();
}

void Map::setLightPostion(int _lightMode) {
	if (_lightMode == 0) {
		light_position = vec4(0.8, 0.0, -1.0, 0.0);
		lightMode = 0;
	}
	else {
		light_position = vec4(1.0, 0.0, -1.0, 2.0);
		lightMode = 1;
	}
}

/* Setting */
void Map::calCameraMoveX() {
	cameraMoveX = (cameraMoveX * 7 + player->getX() * 3) / 10;
}

void Map::calCameraMoveY() {
	cameraMoveY = (cameraMoveY * 7 + player->getY() * 3) / 10;
}

void Map::calRot() {
	if (getPlayer()->getDirection() == 0) {
		if (rotY > 0) {
			rotX += 10;
			rotY -= 7;
		}
		else if (rotY < 0) {
			rotX += 10;
			rotY += 7;
		}
		else
			return;
	}
	else if (getPlayer()->getDirection() == -1) {
		if (rotX > 0) {
			rotX -= 10;
			rotY += 7;
		}
	}
	else if (getPlayer()->getDirection() == 1) {
		if (rotX > 0) {
			rotX -= 10;
			rotY -= 7;
		}
	}
}

void Map::loadewindow() {
	shaderInit();
	model->loading_window_init();
	model->modelInit();
	init();
	loadState = 1;
}
