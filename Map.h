#ifndef MAP_H
#define MAP_H
#include "Obj.h"
#include <vector>
#include "model.h"
using namespace std;

class Map {
private:
	int mode, loadState, lightMode;
	int count, state, gameOver, view;
	float cameraMoveX, cameraMoveY;
	float rotX, rotY;
	GLuint program;

	vector<Road*> vecRoad;
	vector<Line*> vecLine;
	Player *player;
	Acorns *acorns;
	Model *model;
	Chicken *chicken;
	
	vec4 light_position;
	vec4 diffuseProduct = vec4(1.0, 1.0, 1.0, 0.0);
	vec4 ambientProduct = vec4(0.2, 0.2, 0.2, 0.0);
	vec4 specularProduct = vec4(0.1, 0.1, 0.1, 0.0);
	float shininess = 0.1;


public:
	GLuint bufMat[7]; // 0-> position, 1-> color, 2-> modelview, 3-> projectionview
	GLuint ver_loc, col_loc, model_loc, normal_loc, texture_loc, mode_loc, projection_loc, light_loc;
	GLuint tangent_loc, binormal_loc;

	Map();
	void init(); // just make player
	void shaderInit();
	void makeRoad(); // make roads, lines and cars
	void drawAll();
	void drawAcorns();
	void drawChicken();
	void reset();

	/* Setting Method */
	void setGameOver(int _gameOver) { gameOver = _gameOver; }
	void setView(int _view) { view = _view; }
	void setCameraMoveX(float _t) { cameraMoveX = _t; }
	void setMode(int _mode) { mode = _mode; }
	void setLoadState(int _loadState) { loadState = _loadState; }
	void setLightPostion(int _lightMode);
	void calCameraMoveX();
	void calCameraMoveY();
	void calRot();
	void loadewindow();

	/* Get information */
	int getCount() { return count; }
	int getGameOver() { return gameOver; }
	int getMode() { return mode; }
	float getCameraMoveX() { return cameraMoveX; }
	float getCametaMoveY() { return cameraMoveY; }
	float getRotX() { return rotX; }
	float getRotY() { return rotY; }
	int getView() { return view; }
	int getLoadState() { return loadState; }
	int getLightMode() { return lightMode; }
	GLuint getProgram() { return program; }
	vec4 getLightPosition() { return light_position; }
	Player *getPlayer() { return player; }
	vector<Road*> getVecRoad() { return vecRoad; }
	Model *getModel() { return model; }	
};
#endif
