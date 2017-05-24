#include "Obj.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <iostream>
#include "Map.h"
using namespace std;
extern Map *map;

Obj::Obj() {
	x = 0; y = 0; width = 0; height = 0;
	ver = map->ver_loc;
	col = map->col_loc;
	model_loc = map->model_loc;
	normal_loc = map->normal_loc;
	
	/* texture */
	tex = map->texture_loc;

	/* light */
	mode_loc = map->mode_loc;
	light_loc = map->light_loc;

	/* normal mapping */
	tangent = map->tangent_loc;
	binormal = map->binormal_loc;
	program = map->getProgram();
}

void Obj::set(float _x, float _y, float _width, float _height) {
	x = _x; y = _y; width = _width; height = _height;
}

void Obj::setSize(float _width, float _height) {
	width = _width; height = _height;
}

void Obj::setName(int _name) {
	name = _name;
}

void Obj::setY(float _y) {
	y = _y;
}

void Obj::setX(float _x) {
	x = _x;
}

void Obj::draw_code() {
	GLfloat shading_mode = map->getMode();
	vec4 light = map->getLightPosition();

	glBindBuffer(GL_ARRAY_BUFFER, buf);
	glUniform1f(mode_loc, shading_mode);	
	glVertexAttribPointer(ver, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer));
	glVertexAttribPointer(tex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer + sizeCol));
	if(map->getMode() == 1)
		glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer*2 + sizeCol + sizeTexture));
	else
		glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer + sizeCol + sizeTexture));
	glVertexAttribPointer(tangent, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize + sizeLineVer + sizeLineCol));
	glVertexAttribPointer(binormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize + sizeLineVer + sizeLineCol + sizeVer));
	
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, transform);
	glUniform4fv(light_loc, 1, light);
	glDrawArrays(GL_TRIANGLES, 0, sizeDraw);

	if (map->getMode() == 0) { // wire_fram mode
		glVertexAttribPointer(ver, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize));
		glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize + sizeLineVer));		
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, transform);
		glDrawArrays(GL_LINES, 0, sizeLineDraw);
	}
}

void Obj::move(float _x, float _y) {
	x += _x; y += _y;
}

/* 
 * Player class
 */
Player::Player() {
	state = 0;	
	move(48, 270);
	frame = 20;
	count = 0; upDown = 0; direction = 0;
	setSize(70, 70);
}

void Player::draw() {
	transform = Translate(x, y, 19.0) * Scale(1, 0.9, 1);
	if (direction == -1)
		transform = transform * RotateZ(90);
	if (direction == 1)
		transform = transform * RotateZ(-90);

	if (map->getGameOver() == 1)
		transform = transform * Translate(0, 0, -15.0) * Scale(1, 1, 0.2);
	else if (map->getGameOver() == 2)
		transform = transform * Translate(vec3(0.0, 0.0, -60.0));

	if (map->getView() == 1)
		return;

	if (count == 0) {
		matStack.push(transform);
		transform = matStack.top();

		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_apeach.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();
		
		drawNode(map->getModel()->playerArr[0]);

		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_default.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();

		transform = matStack.top() * Translate(0, 11, 6.6) * Scale(1, 0.9, 1);
		drawNode(map->getModel()->playerArr[1]);
		matStack.push(transform);

		transform = matStack.top() * Translate(0, 3.15, -5) * RotateY(-40);
		drawNode(map->getModel()->playerArr[2]);
		matStack.pop();

		transform = matStack.top() * Translate(0, -10.5, 6.6) * Scale(1, 0.9, 1);
		drawNode(map->getModel()->playerArr[3]);
		matStack.push(transform);

		transform = matStack.top() * Translate(0, -4, -5) * RotateY(-40);
		drawNode(map->getModel()->playerArr[4]);
		matStack.pop();

		transform = matStack.top() * Translate(0, 7.5, -17) * RotateX(180) * Scale(1, 0.8, 0.7);
		drawNode(map->getModel()->playerArr[5]);

		transform = matStack.top() * Translate(0, -7, -17) * RotateX(180) * Scale(1, 0.8, 0.7);
		drawNode(map->getModel()->playerArr[6]);

		while (matStack.empty() == false)
			matStack.pop();
	}
	else { //move
		float theta = 120 / frame*count;
		if (upDown == 0) {
			count++;
			if (count == frame)
				upDown = 1;
		}
		else
			count--;

		matStack.push(transform);
		transform = matStack.top();

		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_apeach.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();

		drawNode(map->getModel()->playerArr[0]);

		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_default.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();

		transform = matStack.top() * Translate(0, 11, 6.6)* RotateY(theta) * Scale(1, 0.9, 1);
		drawNode(map->getModel()->playerArr[1]);
		matStack.push(transform);

		transform = matStack.top() * Translate(0, 3.15, -5) * RotateY(-40);
		drawNode(map->getModel()->playerArr[2]);
		matStack.pop();

		transform = matStack.top() * Translate(0, -10.5, 6.6)* RotateY(-1 * theta) * Scale(1, 0.9, 1);
		drawNode(map->getModel()->playerArr[3]);
		matStack.push(transform);

		transform = matStack.top() * Translate(0, -4, -5) * RotateY(-40);
		drawNode(map->getModel()->playerArr[4]);
		matStack.pop();

		transform = matStack.top() * RotateY(-theta*0.5) * Translate(0, 7.5, -17) * RotateX(180) * Scale(1, 0.8, 0.7);
		drawNode(map->getModel()->playerArr[5]);

		transform = matStack.top() * RotateY(theta*0.5) * Translate(0, -7, -17) * RotateX(180) *  Scale(1, 0.8, 0.7);
		drawNode(map->getModel()->playerArr[6]);

		while (matStack.empty() == false)
			matStack.pop();
	}
}

void Player::drawNode(GLuint * arr) {
	sizeVer = arr[1] * sizeof(vec3);
	sizeCol = arr[1] * sizeof(vec4);
	sizeTexture = arr[1] * sizeof(vec2);

	sizeLineVer = arr[2] * sizeof(vec3);
	sizeLineCol = arr[2] * sizeof(vec4);
	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;

	buf = arr[0];
	draw_code();
}

void Player::keyboard(unsigned char key, int _x, int _y) {
	switch (key) {
	case 'w':
		if (map->getView() == 3) { // Ortho
			move(0, 77);
		}
		else {
			if(direction == -1)
				move(0, 77);
			else if (direction == 0) {
				move(96, 0);
				state++;
				stabilize();
			}
			else
				move(0, -77);					
		}
		count = 1; upDown = 0;
		cout << "press W x: " << x << " y: " << y << endl;
		break;
	case 'a':
		if (map->getView() == 3) {
			move(-96, 0);
			stabilize();
			state--;
		}
		else {
			if (direction == 0)
				direction = -1;
			else if (direction == 1)
				direction = 0;
		}
		cout << "change Direction!!!" << endl;
		break;
	case 's':
		if (map->getView() == 3) {
			move(0, -77);
		}
		else {
			if (direction == -1)
				move(0, -77);
			else if (direction == 0) {
				move(-96, 0);
				state--;
				stabilize();
			}
			else
				move(0, 77);
			stabilize();
		}

		cout << "press S x: " << x << " y: " << y << endl;
		break;
	case 'd':
		if (map->getView() == 3) {
			move(96, 0);
			stabilize();
			state++;
		}
		else {
			if (direction == 0)
				direction = 1;
			else if (direction == -1)
				direction = 0;
		}
		
		upDown = 0;
		cout << "change Direction!!!" << endl;
		break;
	}
	glutPostRedisplay();
}

void Player::stabilize() {
	int q = y / 77;

	if (y >= 0)	
		setY(q * 77 + 38.5);
	else
		setY(-1 * (-q * 77) - 38.5);
}

int Player::getState() {
	return state;
}

void Player::reset() {
	state = 0;
	move(48, 270);
	frame = 20;
	count = 0; upDown = 0; direction = 0;
}

/*
* Car class
*/
Car::Car(int _prop, float _x) {
	setName(_x);
	prop = _prop;
	setSize(90, 50);

	type = rand() % 2;
	if (type == 0) {
		buf = map->getModel()->carArr[0][0];
		sizeVer = map->getModel()->carArr[0][1] * sizeof(vec3);
		sizeCol = map->getModel()->carArr[0][1] * sizeof(vec4);
		sizeTexture = map->getModel()->carArr[0][1] * sizeof(vec2);
		
		sizeLineVer = map->getModel()->carArr[0][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->carArr[0][2] * sizeof(vec4);
	}
	else {
		buf = map->getModel()->carArr[1][0];
		sizeVer = map->getModel()->carArr[1][1] * sizeof(vec3);
		sizeCol = map->getModel()->carArr[1][1] * sizeof(vec4);
		sizeTexture = map->getModel()->carArr[1][1] * sizeof(vec2);

		sizeLineVer = map->getModel()->carArr[1][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->carArr[1][2] * sizeof(vec4);
	}

	baseSize = sizeVer*3 + sizeCol + sizeTexture;
	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;

	if (prop > 0)
		move(96 * (_x)+48, 640);
	else
		move(96 * (_x)+48, -200);
}

void Car::draw() {	
	if (prop == 1) {
		vec3 moveVec(x, y, 0.0);
		transform = Translate(moveVec)*RotateZ(180);
	}
	else {
		vec3 moveVec(x, y, 0.0);
		transform = Translate(moveVec);
	}		
	if (type == 0) {
		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_lion.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_jayG.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_metal.bind();
	}

	draw_code();
}

/* if car collide to wall return 1 else return 0 */
int Car::checkEnd() {
	int coord = getY();
	if (coord > 640 || coord < -200)
		return 1;
	else return 0;
}

int Car::getProp() {
	return prop;
}

/* 
 * Obstacle class
 */
Obstacle::Obstacle(int position, int _x) {
	setName(_x);

	type = rand() % 2;
	if (type == 0) {
		buf = map->getModel()->obsArr[0];
		sizeVer = map->getModel()->obsArr[1] * sizeof(vec3);
		sizeCol = map->getModel()->obsArr[1] * sizeof(vec4);
		sizeTexture = map->getModel()->obsArr[1] * sizeof(vec2);

		sizeLineVer = map->getModel()->obsArr[2] * sizeof(vec3);
		sizeLineCol = map->getModel()->obsArr[2] * sizeof(vec4);		
	}
	else {
		buf = map->getModel()->houseArr[0];
		sizeVer = map->getModel()->houseArr[1] * sizeof(vec3);
		sizeCol = map->getModel()->houseArr[1] * sizeof(vec4);
		sizeTexture = map->getModel()->houseArr[1] * sizeof(vec2);

		sizeLineVer = map->getModel()->houseArr[2] * sizeof(vec3);
		sizeLineCol = map->getModel()->houseArr[2] * sizeof(vec4);
	}
	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;

	move(96 * (_x)+48, position * 77 + 38.5);
	setSize(60, 60);
}

void Obstacle::draw() {
	vec3 moveVec(x, y , 0.0);
	transform = Translate(moveVec);

	if (type == 0) {
		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_tree.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_tree.bind();
	}
	else {
		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_house.bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_house.bind();
	}
	draw_code();
}

/*
* Flower class
*/
Flower::Flower(int position, int _x) {
	setName(_x);

	buf = map->getModel()->flowerArr[0];
	sizeVer = map->getModel()->flowerArr[1] * sizeof(vec3);
	sizeCol = map->getModel()->flowerArr[1] * sizeof(vec4);
	sizeTexture = map->getModel()->flowerArr[1] * sizeof(vec2);

	sizeLineVer = map->getModel()->flowerArr[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->flowerArr[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;

	int rand_x = rand() % 4;

	move(96 * (_x)+8 * (rand_x + 1), position * 7.7 + 3.85);
	setSize(10, 10);
}

void Flower::draw() {
	vec3 moveVec(x, y, 0.0);
	transform = Translate(moveVec);

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_flower.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();	

	draw_code();
}
/*
* Train class
*/
Train::Train(int _x) {
	setName(_x);
	move(96 * (_x)+48, -200);
	buf = map->getModel()->trainHead[0];		
	sizeVer = map->getModel()->trainHead[1] * sizeof(vec3);
	sizeCol = map->getModel()->trainHead[1] * sizeof(vec4);
	sizeTexture = map->getModel()->trainHead[1] * sizeof(vec2);
	sizeLineVer = map->getModel()->trainHead[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->trainHead[2] * sizeof(vec4);
	sizeDraw = sizeVer / 12; 
	sizeLineDraw = sizeLineVer / 12;

	buf2 = map->getModel()->trainBody[0];
	sizeVer2 = map->getModel()->trainBody[1] * sizeof(vec3);	
	sizeCol2 = map->getModel()->trainBody[1] * sizeof(vec4);	
	sizeTexture2 = map->getModel()->trainBody[1] * sizeof(vec2);
	sizeLineVer2 = map->getModel()->trainBody[2] * sizeof(vec3);
	sizeLineCol2 = map->getModel()->trainBody[2] * sizeof(vec4);
	sizeDraw2 = sizeVer2 / 12; 
	sizeLineDraw2 = sizeLineVer / 12;	
	
	baseSize = sizeVer*3 + sizeCol + sizeTexture;
	baseSize2 = sizeVer2*3 + sizeCol2 + sizeTexture2;
}

void Train::draw() {
	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_trainHead.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();
	
	vec3 moveVec(x, y, 6);
	transform = Translate(moveVec);
	draw_code();

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_trainBody.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();
	
	for (int i = 1; i < 8; i++) {
		vec3 moveVec(x, y-75*i, 0.0);
		transform = Translate(moveVec);
		GLfloat shading_mode = map->getMode();
		vec4 light = map->getLightPosition();

		glBindBuffer(GL_ARRAY_BUFFER, buf2);
		glUniform1f(mode_loc, shading_mode);

		glVertexAttribPointer(ver, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer2));
		glVertexAttribPointer(tex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer2 + sizeCol2));
		if (map->getMode() == 1)
			glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer2 * 2 + sizeCol2 + sizeTexture2));
		else
			glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeVer2 + sizeCol2 + sizeTexture2));
		glVertexAttribPointer(tangent, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize2 + sizeLineVer2 + sizeVer2));
		glVertexAttribPointer(binormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize2 + sizeLineVer2 + sizeVer2 * 2));
		glUniformMatrix4fv(model_loc, 1, GL_TRUE, transform);
		glUniform4fv(light_loc, 1, light);
		glDrawArrays(GL_TRIANGLES, 0, sizeDraw2);

		if (map->getMode() == 0) { // wire_fram mode
			glVertexAttribPointer(ver, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize2));
			glVertexAttribPointer(col, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(baseSize2 + sizeLineVer2));
			glUniformMatrix4fv(model_loc, 1, GL_TRUE, transform);
			glDrawArrays(GL_LINES, 0, sizeLineDraw2);
		}
	}
}

/*
* Wood class
*/
Wood::Wood(int _prop, int _x) {
	prop = _prop;
	setName(_x);
	buf = map->getModel()->woodArr[0];
	sizeVer = map->getModel()->woodArr[1] * sizeof(vec3);
	sizeCol = map->getModel()->woodArr[1] * sizeof(vec4);
	sizeTexture = map->getModel()->woodArr[1] * sizeof(vec2);

	sizeLineVer = map->getModel()->woodArr[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->woodArr[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;

	if (prop > 0) // down
		move(96 * (_x)+48, 740);
	else // go up
		move(96 * (_x)+48, -50); 

	size = 80*(rand() % 2+2);		
	setSize(56, size);
	setSpeed(40);
}

void Wood::draw() {
	vec3 moveVec(x, y, -5.0);
	transform = Translate(moveVec);

	int woodNum = size / 80;

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_wood.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();

	draw_code();	

	for (int i = 1; i < woodNum; i++) {		
		vec3 moveVec2(x, y - 80 * i, -5.0);
		transform = Translate(moveVec2);
		draw_code();
	}
}

int Wood::checkEnd() {
	int coord = getY();
	if (coord > 940 || coord < -320)
		return 1;
	else return 0;
}

/*
* Road class
*/
Road::Road(int _x, int _type) {
	type = _type; setName(_x);
	prop = rand() % 2;
	move(96 * (_x), 0);
	time = 150;
	randTime = rand() % 100 + 50;
	woodTime = 184;

	if (type == 0) { 
		buf = map->getModel()->roadArr[0][0]; 
		sizeVer = map->getModel()->roadArr[0][1] * sizeof(vec3);
		sizeCol = map->getModel()->roadArr[0][1] * sizeof(vec4);
		sizeTexture = map->getModel()->roadArr[0][1] * sizeof(vec2);
		sizeLineVer = map->getModel()->roadArr[0][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->roadArr[0][2] * sizeof(vec4);
	}
	else if (type == 1) { 
		buf = map->getModel()->roadArr[1][0]; 
		sizeVer = map->getModel()->roadArr[1][1] * sizeof(vec3);
		sizeCol = map->getModel()->roadArr[1][1] * sizeof(vec4);
		sizeTexture = map->getModel()->roadArr[1][1] * sizeof(vec2);
		sizeLineVer = map->getModel()->roadArr[1][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->roadArr[1][2] * sizeof(vec4);
	}
	else if (type == 2) { 
		buf = map->getModel()->roadArr[2][0]; 
		sizeVer = map->getModel()->roadArr[2][1] * sizeof(vec3);
		sizeCol = map->getModel()->roadArr[2][1] * sizeof(vec4);
		sizeTexture = map->getModel()->roadArr[2][1] * sizeof(vec2);
		sizeLineVer = map->getModel()->roadArr[2][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->roadArr[2][2] * sizeof(vec4);

	}
	else if (type == 3) { 
		buf = map->getModel()->roadArr[3][0]; 
		sizeVer = map->getModel()->roadArr[3][1] * sizeof(vec3);
		sizeCol = map->getModel()->roadArr[3][1] * sizeof(vec4);
		sizeTexture = map->getModel()->roadArr[3][1] * sizeof(vec2);
		sizeLineVer = map->getModel()->roadArr[3][2] * sizeof(vec3);
		sizeLineCol = map->getModel()->roadArr[3][2] * sizeof(vec4);		
	}
	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;
	/* set speed */
	float r = ((float)rand() / (float)(RAND_MAX)) * 2 + 1.5;

	if (type == 3) {
		int rnd = rand() % 2;
		if (rnd == 0)
			setSpeed(2);
		else
			setSpeed(3);
	}
	else
		setSpeed(r);
}

void Road::draw() {
	if (type == 2) {

		glActiveTexture(GL_TEXTURE0);
		map->getModel()->texture_road[2].bind();
		glActiveTexture(GL_TEXTURE1);
		map->getModel()->normalmap_road.bind();
		
		for (int i = 0; i < 14; i++) {
			vec3 moveVec(x, y + 54 * i - 108, 0.0);
			transform = Translate(moveVec);
			draw_code();
		}
	}		
	else {
		vec3 moveVec(x, y, 0.0);
		transform = Translate(moveVec);

		if (type == 0) {
			glActiveTexture(GL_TEXTURE0);
			map->getModel()->texture_road[0].bind();
			glActiveTexture(GL_TEXTURE1);
			map->getModel()->normalmap_road.bind();
		}
		else if (type == 1) {
			glActiveTexture(GL_TEXTURE0);
			map->getModel()->texture_road[1].bind();
			glActiveTexture(GL_TEXTURE1);
			map->getModel()->normalmap_road.bind();
		}
		else if (type == 3) {
			glActiveTexture(GL_TEXTURE0);
			map->getModel()->texture_road[3].bind();
			glActiveTexture(GL_TEXTURE1);
			map->getModel()->normalmap_water.bind();
		}
		draw_code();
	}
}

/* make a car */
void Road::makeCar(int _x) {
	Obj *node = new Car(prop, _x);
	vecCar.push_back(node);

	randTime = rand() % 50 + 150; // make random number
}

void Road::makeObs(int _x) {
	int num = rand() % 3 + 1;
	int a[3];
	Obj *node[3];

	for (int i = 0; i < num; i++)
	{
		a[i] = rand() % 7;
		for (int j = 0; j < i; j++)
			if (a[i] == a[j]) {
				i--;
				break;
			}
	}
	for (int i = 0; i < num; i++) {
		node[i] = new Obstacle(a[i], _x);
		vecObs.push_back(node[i]);
	}

}

void Road::makeFlower(int _x) {
	int num = rand() % 6 + 1;
	int a[70];
	Flower *node[6];

	for (int i = 0; i < num; i++)
	{
		a[i] = rand() % 70;
		for (int j = 0; j < i; j++)
			if (a[i] == a[j]) {
				i--;
				break;
			}
	}
	for (int i = 0; i < num; i++) {
		node[i] = new Flower(a[i], _x);
		vecFlower.push_back(node[i]);
	}
}

void Road::makeTrain(int _x) {
	train = new Train(_x);
}

void Road::makeWood(int _x) {
	Obj *node = new Wood(prop, _x);
	vecWood.push_back(node);
}

/* delete */
void Road::deleteCar() {
	vecCar.erase(vecCar.begin());
}

void Road::deleteTrain() {
	delete train;
}

void Road::deleteWood() {
	vecWood.erase(vecWood.begin());
}

/* move */
void Road::moveCar() {
	int num = vecCar.size();
	for (int i = 0; i < num; i++) {
		if (prop == 0)
			vecCar[i]->move(0, getSpeed());
		else
			vecCar[i]->move(0, -getSpeed());
	}
}

void Road::moveTrain() {
	train->move(0, 20);
	if (train->getY() > 1140)
		train->setY(-600);
	
}

void Road::moveWood() {
	int num = vecWood.size();
	if (prop == 0) {
		for (int i = 0; i < num; i++)
			vecWood[i]->move(0, getSpeed());
	}
	else {
		for (int i = 0; i < num; i++)
			vecWood[i]->move(0, -getSpeed());
	}
}

/* draw*/
void Road::drawCar() {
	int num = vecCar.size();
	for (int i = 0; i < num; i++)
		vecCar[i]->draw();
}

void Road::drawObs() {
	int num = vecObs.size();
	for (int i = 0; i < num; i++)
		vecObs[i]->draw();
}

void Road::drawFlower() {
	int num = vecFlower.size();
	for (int i = 0; i < num; i++)
		vecFlower[i]->draw();
}

void Road::drawWood() {
	int num = vecWood.size();
	for (int i = 0; i < num; i++)
		vecWood[i]->draw();
}

/* Update */
void Road::update() {
	draw();
	if (type == 0) {
		moveCar();
		drawCar();
		time++;
		if (randTime < time) {
			makeCar(getName());
			time = 0;
		}
	}
	else if (type == 1) {
		drawObs();
		drawFlower();
	}
	else if (type == 2) {
		moveTrain();
		train->draw();
	}
	else if (type == 3) {
		moveWood();
		drawWood();
		woodTime++;
		if (prop == 1) {
			if (woodTime > 150) {
				makeWood(getName());
				woodTime = 0;
			}
		}
		else {
			if (woodTime > 150) {
				makeWood(getName());
				woodTime = 0;
			}
		}		
	}
}

void Road::noUpdate() {
	draw();
	if (type == 0)
		drawCar();
	else if (type == 1) {
		drawObs();
		drawFlower();
	}
	else if (type == 2)
		train->draw();
	else if (type == 3)
		drawWood();
}

/* Destructor */
Road::~Road() {
	if (type == 0) {
		int num = vecCar.size();
		for (int i = 0; i < num; i++)
			deleteCar();
	}
	else if (type == 1) {
		int num = vecObs.size();
		for (int i = 0; i < num; i++) {
			vecObs.erase(vecObs.begin());
		}
		num = vecFlower.size();
		for (int i = 0; i < num; i++)
			vecFlower.erase(vecFlower.begin());
	}
	else if (type == 2)
		deleteTrain();
	else if (type == 3) {
		int num = vecWood.size();
		for (int i = 0; i < num; i++)
			deleteWood();
	}
}

/*
* Line class
*/
Line::Line(int _x) {
	move(96 * _x + 96, 270);
	buf = map->getModel()->lineArr[0];
	sizeVer = map->getModel()->lineArr[1] * sizeof(vec3);
	sizeCol = map->getModel()->lineArr[1] * sizeof(vec4);
	sizeTexture = map->getModel()->lineArr[1] * sizeof(vec2);	

	sizeLineVer = map->getModel()->lineArr[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->lineArr[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer*3 + sizeCol + sizeTexture;
}

void Line::draw() {
	vec3 moveVec(x, y, 1.0);
	transform = Translate(moveVec);

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_default.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();

	draw_code();
}

Frame::Frame() {
	buf = map->getModel()->frame[0];
	sizeVer = map->getModel()->frame[1] * sizeof(vec3);
	sizeCol = map->getModel()->frame[1] * sizeof(vec4);
	sizeTexture = map->getModel()->frame[1] * sizeof(vec2);

	sizeLineVer = map->getModel()->frame[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->frame[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer * 3 + sizeCol + sizeTexture;
	move(1500, 270);
}

void Frame::draw() {
	vec3 moveVec(x, y, -100.0);
	transform = Translate(moveVec);	

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_acorns.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();

	draw_code();
}

Acorns::Acorns() {
	buf = map->getModel()->acorns[0];
	sizeVer = map->getModel()->acorns[1] * sizeof(vec3);
	sizeCol = map->getModel()->acorns[1] * sizeof(vec4);
	sizeTexture = map->getModel()->acorns[1] * sizeof(vec2);

	sizeLineVer = map->getModel()->acorns[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->acorns[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer * 3 + sizeCol + sizeTexture;
	move(1500, 270);

	theta = 0.0;
	frame = new Frame();
}

void Acorns::draw() {
	vec3 moveVec(x, y, -100.0);
	transform = Translate(moveVec) * RotateZ(theta--);

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_acorns.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();

	draw_code();
	frame->draw();
}

Chicken::Chicken() {
	buf = map->getModel()->chicken[0];
	sizeVer = map->getModel()->chicken[1] * sizeof(vec3);
	sizeCol = map->getModel()->chicken[1] * sizeof(vec4);
	sizeTexture = map->getModel()->chicken[1] * sizeof(vec2);

	sizeLineVer = map->getModel()->chicken[2] * sizeof(vec3);
	sizeLineCol = map->getModel()->chicken[2] * sizeof(vec4);

	sizeDraw = sizeVer / 12;
	sizeLineDraw = sizeLineVer / 12;
	baseSize = sizeVer * 3 + sizeCol + sizeTexture;
	move(1500, 270);

	theta = 0.0;
}

void Chicken::draw() {
	vec3 moveVec(x, y, -200.0);
	transform = Translate(moveVec) * RotateZ(theta--) * RotateX(90) * Scale(10.0);

	glActiveTexture(GL_TEXTURE0);
	map->getModel()->texture_chicken.bind();
	glActiveTexture(GL_TEXTURE1);
	map->getModel()->normalmap_default.bind();

	draw_code();
}

