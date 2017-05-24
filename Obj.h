#ifndef OBJ_H
#define OBJ_H
#include <vector>
#include <stack>
#include "Angel.h"
using namespace std;

class Obj {
private:
	float width, height, name;		

protected:
	float x, y;
	GLuint ver, col, tex, model_loc, proj_loc, normal_loc, diffuse_loc, light_loc, mode_loc, tangent, binormal, program;
	GLuint buf, sizeVer, sizeCol, sizeTexture;
	GLuint sizeLineVer, sizeLineCol;
	mat4 transform;	
	int sizeDraw, sizeLineDraw;
	int baseSize;
	vec4 diffuseProduct;

public:
	Obj();
	void set(float _x, float _y, float _width, float _height);
	void setSize(float _width, float _height);
	void setName(int _name);
	void setY(float _y);	
	void setX(float _x);
	void draw_code();
	virtual int checkEnd() = 0;
	virtual void draw() = 0;
	virtual void setSpeed(float _speed) = 0;
	virtual float getSpeed() = 0;	
	void move(float _x, float _y);
	float getX() { return x; }
	float getY() { return y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	float getName() { return name; }
	vec4 getDiffuse() { return diffuseProduct; }
};

class Player : public Obj {
private:
	int state;
	stack<mat4> matStack;
	int count, frame;
	int upDown;
	int direction; // 0, -1 -> left, 1 ->right

public:
	Player();
	void draw();
	void drawNode(GLuint *arr);
	void keyboard(unsigned char key, int _x, int _y);
	void stabilize();
	int getState();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	void setDirection(int _dir) { direction = _dir; }
	float getSpeed() { return 0.0; }
	int getDirection() { return direction; }
	void reset();
};

class Car : public Obj {
private:
	int prop, size12, type;

public:
	Car(int _prop, float _x);
	void setSpeed(float _speed) {}
	void draw();
	int checkEnd();
	int getProp();
	float getSpeed() { return 0.0; }
};

class Obstacle : public Obj {
private:
	int type;

public:
	Obstacle(int position, int _x);
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
	
};

class Flower : public Obj {
public:
	Flower(int position, int _x);
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};

class Train : public Obj {
private:
	GLuint buf2, sizeVer2, sizeCol2, sizeLineVer2, sizeLineCol2, baseSize2;
	int sizeDraw2, sizeTexture2, sizeLineDraw2;

public:
	Train(int _x);
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};

class Wood : public Obj {
private:
	int size, prop;

public:
	Wood(int _prop, int _x);
	void draw();
	int checkEnd();
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
	int getProp() { return prop; }
};

class Road : public Obj {
private:
	int type; // 0 -> road, 1 -> grass, 2 -> train, 3 -> water
	int prop; // if prop = 0 then up else down
	int time, randTime;
	int woodTime;
	float speed;
	vector<Obj*> vecCar;
	vector<Obj*> vecObs;
	vector<Obj*> vecFlower;
	vector<Obj*> vecWood;
	vector<Obj*> vecLine;
	Obj *train;

public:
	Road(int _x, int _type);
	void draw();
	void makeCar(int _x);
	void makeObs(int _x);
	void makeFlower(int _x);
	void makeTrain(int _x);
	void makeWood(int _x);
	void setSpeed(float _speed) { speed = _speed; }

	/* Delete */
	void deleteCar();
	void deleteTrain();
	void deleteWood();

	/* Move */
	void moveCar();
	void moveTrain();
	void moveWood();

	/* Draw */
	void drawCar();
	void drawObs();
	void drawFlower();
	void drawWood();
	void update();
	void noUpdate();

	/* Get */
	int getProp() { return prop; }
	int getType() { return type; }
	float getSpeed() { return speed; }
	vector<Obj*> getCar() { return vecCar; }
	vector<Obj*> getWood() { return vecWood; }
	vector<Obj *> getObs() { return vecObs; }
	vector<Obj*> getFlower() { return vecFlower; }
	Obj *getTrain() { return train; }

	int checkEnd() { return 0; }
	~Road();
};

class Line : public Obj {
public:
	Line(int _x);
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};

class Frame : public Obj {
public:
	Frame();
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};

class Acorns : public Obj {
private:
	float theta;
	Frame *frame;

public:
	Acorns();
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};

class Chicken : public Obj {
private:
	float theta;

public:
	Chicken();
	void draw();
	int checkEnd() { return 0; }
	void setSpeed(float _speed) {}
	float getSpeed() { return 0.0; }
};
#endif