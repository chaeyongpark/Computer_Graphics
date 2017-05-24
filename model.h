#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include "Angel.h"
#include "texture.h"
#include "normalmap.h"
using namespace std;

class Model {
private:
	/* Color */
	vec4 whiteColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 grayColor = vec4(0.7, 0.7, 0.7, 1.0);
	vec4 grayDarkColor = vec4(0.4, 0.4, 0.4, 1.0);
	vec4 grayDarkdarkColor = vec4(0.3, 0.3, 0.3, 1.0);
	vec4 blackColor = vec4(0.0, 0.0, 0.0, 1.0);

	vec4 pinkColor = vec4(0.99, 0.74, 0.81, 1.0);
	vec4 pinkDarkColor = vec4(0.74, 0.3, 0.3, 1.0);
	vec4 redColor = vec4(1.0, 0.0, 0.0, 1.0);

	vec4 woodColor = vec4(0.4, 0.2, 0.0, 1.0);
	vec4 railColor = vec4(0.36, 0.24, 0.1, 1.0);

	vec4 orangeColor = vec4(0.84, 0.6, 0.2, 1.0);
	vec4 greenColor = vec4(0, 0.5, 0, 1.0);
	vec4 grassColor = vec4(0.66, 0.91, 0.38, 1.0);
	vec4 yellowColor = vec4(1.0, 0.76, 0.0, 1.0);

	vec4 skyblueColor = vec4(0.0, 0.9, 1.0, 1.0);
	vec4 windowColor = vec4(0.3, 0.5, 0.9, 0.2);
	vec4 trainColor = vec4(0.35, 0.6, 0.8, 1.0);
	vec4 beigeColor = vec4(1.0, 0.9, 0.5, 1.0);

public:
	/* modelinit 각각의 init, public으로 arr선언,*/
	Model();
	GLuint lineArr[3], carArr[2][3], roadArr[4][3], obsArr[3], playerArr[7][3];
	GLuint trainHead[3], trainBody[3], woodArr[3], flowerArr[3], houseArr[3], acorns[3], frame[3];
	Texture texture_house, texture_tree, texture_lion, texture_jayG, texture_flower;
	Texture texture_wood, texture_line, texture_road[4], texture_apeach, texture_trainHead, texture_trainBody;
	Texture texture_default, texture_acorns, texture_frames;

	NormalMap normalmap_default, normalmap_tree, normalmap_house, normalmap_road, normalmap_grass;
	NormalMap normalmap_water, normalmap_metal;

	GLuint chicken[3];
	Texture texture_chicken;

	void modelInit();
	void loading_window_init();

	void makeCube(float _x, float _y, float z, float l, vector<vec3>* arr, vec4 color, vector<vec4>* colArr);
	void makeRectCube(float _x, float _y, float _z, float xl, float yl, float zl, vector<vec3>* arr, vec4 color, vector<vec4>* colArr);
	void setBuffer(GLuint *buf, vector<vec3> * ver, vector<vec4> * col, vector<vec3>* normal);
	void makeRect(float x, float y, float x1, float y1, float z, vector<vec3> *arr, vec4 color, vector<vec4> *colArr);
	void changeColor(vec4 color, vector<vec4>* colArr);
	vector<string> tokenize(string str, string delim);
	vec4 stoc(string str);
	void load(char * file, GLuint *buf, bool isTexture);
};