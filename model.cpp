#include "model.h"
#include <iostream>
#include <fstream>
#include <string>

Model::Model() {
}

void Model::modelInit() {
	load("objects/real_hicken.obj", chicken, true);
	texture_chicken.load("texture/chicken.png");

	/* road */
	normalmap_road.load("texture/normal/road.png");
	load("objects/road.obj", roadArr[0], true);
	texture_road[0].load("texture/road.png");

	/* grass */
	normalmap_grass.load("texture/normal/grass.png");
	load("objects/grass.obj", roadArr[1], true);
	texture_road[1].load("texture/grass.png");

	/* water */
	normalmap_water.load("texture/normal/water.png");
	load("objects/rail.obj", roadArr[2], true);
	texture_road[2].load("texture/rail.png");

	/* rail */
	load("objects/water.obj", roadArr[3], true);
	texture_road[3].load("texture/water.png");
	load("objects/line.obj", lineArr, true);

	load("objects/flower.obj", flowerArr, true);
	texture_flower.load("texture/flower.png");

	/* car */
	normalmap_metal.load("texture/normal/metal.png");
	load("objects/lionCar.obj", carArr[0], true);
	texture_lion.load("texture/lionCar.png");
	load("objects/jayG.obj", carArr[1], true);
	texture_jayG.load("texture/jayG.png");

	/* tree */
	normalmap_tree.load("texture/normal/tree.png");
	load("objects/tree.obj", obsArr, true);
	texture_tree.load("texture/tree.png");

	/* house */
	normalmap_house.load("texture/normal/house.png");
	load("objects/house.obj", houseArr, true);
	texture_house.load("texture/house.png");

	load("objects/trainHead.obj", trainHead, true);
	texture_trainHead.load("texture/trainHead.png");
	load("objects/trainBody.obj", trainBody, true);
	texture_trainBody.load("texture/trainBody.png");
	load("objects/wood.obj", woodArr, true);
	texture_wood.load("texture/wood.png");

	load("objects/apeach/HAndB.obj", playerArr[0], true);
	texture_apeach.load("texture/HandB.png");
	load("objects/apeach/LeftArm1.obj", playerArr[1], false);
	load("objects/apeach/LeftArm2.obj", playerArr[2], false);
	load("objects/apeach/RightArm1.obj", playerArr[3], false);
	load("objects/apeach/RightArm2.obj", playerArr[4], false);
	load("objects/apeach/LeftLeg.obj", playerArr[5], false);
	load("objects/apeach/RightLeg.obj", playerArr[6], false);

	texture_default.load("texture/white.png");
}

void Model::loading_window_init() {
	normalmap_default.load("texture/normal/default.png");

	load("objects/acorns.obj", acorns, true);
	texture_acorns.load("texture/acorns.png");
	load("objects/frame.obj", frame, true);
	texture_frames.load("texture/acorns.png");
}

void Model::makeCube(float _x, float _y, float z, float l, vector<vec3>* arr, vec4 color, vector<vec4>* colArr) {
	float x = _x - l / 2;
	float y = _y - l / 2;

	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x, y, z + l));
	arr->push_back(vec3(x, y + l, z));
	arr->push_back(vec3(x, y + l, z));
	arr->push_back(vec3(x, y, z + l));
	arr->push_back(vec3(x, y + l, z + l));

	/* right side */
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x + l, y, z));
	arr->push_back(vec3(x, y, z + l));
	arr->push_back(vec3(x, y, z + l));
	arr->push_back(vec3(x + l, y, z));
	arr->push_back(vec3(x + l, y, z + l));

	/* back side */
	arr->push_back(vec3(x + l, y, z));
	arr->push_back(vec3(x + l, y, z + l));
	arr->push_back(vec3(x + l, y + l, z));
	arr->push_back(vec3(x + l, y + l, z));
	arr->push_back(vec3(x + l, y, z + l));
	arr->push_back(vec3(x + l, y + l, z + l));

	/* left side */
	arr->push_back(vec3(x, y + l, z));
	arr->push_back(vec3(x, y + l, z + l));
	arr->push_back(vec3(x + l, y + l, z));
	arr->push_back(vec3(x + l, y + l, z));
	arr->push_back(vec3(x, y + l, z + l));
	arr->push_back(vec3(x + l, y + l, z + l));

	/* top */
	arr->push_back(vec3(x, y, z+l));
	arr->push_back(vec3(x+l , y, z + l));
	arr->push_back(vec3(x, y+l, z+l));
	arr->push_back(vec3(x, y+l, z+l));
	arr->push_back(vec3(x+l, y, z+l));
	arr->push_back(vec3(x+l, y+l, z+l));

	/* bottom */
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x + l, y, z));
	arr->push_back(vec3(x, y + l, z));
	arr->push_back(vec3(x, y + l, z));
	arr->push_back(vec3(x + l, y, z));
	arr->push_back(vec3(x + l, y + l, z));

	for (int i = 0; i < 36; i++)
		colArr->push_back(color);
}

void Model::makeRectCube(float _x, float _y, float z, float xl, float yl, float zl, vector<vec3>* arr, vec4 color, vector<vec4>* colArr) {
	float x = _x - xl / 2;
	float y = _y - yl / 2;

	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x, y, z + zl));
	arr->push_back(vec3(x, y + yl, z));
	arr->push_back(vec3(x, y + yl, z));
	arr->push_back(vec3(x, y, z + zl));
	arr->push_back(vec3(x, y + yl, z + zl));

	/* right side */
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x + xl, y, z));
	arr->push_back(vec3(x, y, z + zl));
	arr->push_back(vec3(x, y, z + zl));
	arr->push_back(vec3(x + xl, y, z));
	arr->push_back(vec3(x + xl, y, z + zl));

	/* back side */
	arr->push_back(vec3(x + xl, y, z));
	arr->push_back(vec3(x + xl, y, z + zl));
	arr->push_back(vec3(x + xl, y + yl, z));
	arr->push_back(vec3(x + xl, y + yl, z));
	arr->push_back(vec3(x + xl, y, z + zl));
	arr->push_back(vec3(x + xl, y + yl, z + zl));

	/* left side */
	arr->push_back(vec3(x, y + yl, z));
	arr->push_back(vec3(x, y + yl, z + zl));
	arr->push_back(vec3(x + xl, y + yl, z));
	arr->push_back(vec3(x + xl, y + yl, z));
	arr->push_back(vec3(x, y + yl, z + zl));
	arr->push_back(vec3(x + xl, y + yl, z + zl));

	/* top */
	arr->push_back(vec3(x, y, z + zl));
	arr->push_back(vec3(x + xl, y, z + zl));
	arr->push_back(vec3(x, y + yl, z + zl));
	arr->push_back(vec3(x, y + yl, z + zl));
	arr->push_back(vec3(x + xl, y, z + zl));
	arr->push_back(vec3(x + xl, y + yl, z + zl));

	/* bottom */
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x + xl, y, z));
	arr->push_back(vec3(x, y + yl, z));
	arr->push_back(vec3(x, y + yl, z));
	arr->push_back(vec3(x + xl, y, z));
	arr->push_back(vec3(x + xl, y + yl, z));

	for (int i = 0; i < 36; i++)
		colArr->push_back(color);
}

void Model::setBuffer(GLuint * buf, vector<vec3>* ver, vector<vec4>* col, vector<vec3>* normal) {
	buf[1] = ver->size() * sizeof(vec3);
	buf[2] = col->size() * sizeof(vec4);
	GLuint normalSize = normal->size() * sizeof(vec3);

	glGenBuffers(1, &buf[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, buf[1] + buf[2], NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, buf[1], ver->front());
	glBufferSubData(GL_ARRAY_BUFFER, buf[1], buf[2], col->front());
	glBufferSubData(GL_ARRAY_BUFFER, buf[1] + buf[2], normalSize, normal->front());
}

void Model::makeRect(float x, float y, float x1, float y1, float z, vector<vec3>* arr, vec4 color, vector<vec4>* colArr) {
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x, y1, z));
	arr->push_back(vec3(x1, y1, z));
	arr->push_back(vec3(x1, y1, z));
	arr->push_back(vec3(x, y, z));
	arr->push_back(vec3(x1, y, z));
	for (int i = 0; i < 6; i++)
		colArr->push_back(color);
}

void Model::changeColor(vec4 color, vector<vec4>* colArr) {
	int size = colArr->size();
	colArr->assign(size, color);
}

vector<string> Model::tokenize(string str, string delim) {
	vector<string> v;
	size_t seek = 0;

	while (str.length() > seek) {
		size_t pos;
		pos = str.find_first_of(delim, seek);

		if (pos != string::npos) {
			v.push_back(str.substr(seek, pos - seek));
			seek = pos + 1;
		}
		else {
			v.push_back(str.substr(seek));
			seek = str.length();
		}
	}

	return v;
}

vec4 Model::stoc(string str) {
	if (str.compare("whiteColor") == 0)
		return whiteColor;
	else if(str.compare("grayColor") == 0)
		return grayColor;
	else if (str.compare("grayDarkColor") == 0)
		return grayDarkColor;
	else if (str.compare("grayDarkdarkColor") == 0)
		return grayDarkdarkColor;
	else if (str.compare("blackColor") == 0)
		return blackColor;
	else if (str.compare("pinkColor") == 0)
		return pinkColor;
	else if (str.compare("pinkDarkColor") == 0)
		return pinkDarkColor;
	else if (str.compare("redColor") == 0)
		return redColor;
	else if (str.compare("woodColor") == 0)
		return woodColor;
	else if (str.compare("railColor") == 0)
		return railColor;
	else if (str.compare("orangeColor") == 0)
		return orangeColor;
	else if (str.compare("greenColor") == 0)
		return greenColor;
	else if (str.compare("grassColor") == 0)
		return grassColor;
	else if (str.compare("skyblueColor") == 0)
		return skyblueColor;
	else if (str.compare("windowColor") == 0)
		return windowColor;
	else if (str.compare("yellowColor") == 0)
		return yellowColor;
	else if (str.compare("trainColor") == 0)
		return trainColor;
	else if (str.compare("beigeColor") == 0)
		return beigeColor;
	else if (str.compare("texture") == 0)
		return whiteColor;
}

void Model::load(char * file, GLuint *buf, bool isTexture) {
	ifstream infile(file);

	vector<vec3> v;
	vector<vec2> vt;
	vector<vec3> vn;	

	vector<vec3> vec;	
	vector<vec2> tex;
	vector<vec3> normal;
	vector<vec3> normal_flat;
	vector<vec4> color;

	vector<vec3> tangent;
	vector<vec3> binormal;

	vector<vec3> line;
	vector<vec4> lineColor;

	vec4 col = vec4(0.0, 0.0, 0.0, 0.0);
	int check = 0;
	int vertex[4] = { 0 }, faces;

	v.push_back(vec3(0.0, 0.0, 0.0));
	vt.push_back(vec2(0.0, 0.0));
	vn.push_back(vec3(0.0, 0.0, 0.0));	
	//tangent.push_back(vec3(0.0, 0.0, 0.0));
	//binormal.push_back(vec3(0.0, 0.0, 0.0));

	while (!infile.eof()) {
		string buf;
		getline(infile, buf);

		if (buf.length() == 0)
			continue;

		vector<string> t = tokenize(buf, " ");
		string flag = t[0];

		if (flag.compare("#") == 0) {
			if (check == 0) {
				check++;			
				continue;
			}
			else if (check == 1) {
				check++;
				vertex[0] = stoi(t[1]);
			}
			else if (check == 2) {
				check++;
				vertex[1] = stoi(t[1]);
			}
			else if (check == 3) {
				check++;
				vertex[2] = stoi(t[1]);				
			}
			else
				vertex[3] = stoi(t[1]);
		}
		else if (flag.compare("\n") == 0) {
			continue;
		}
		else if (flag.compare("v") == 0)
			v.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		else if (flag.compare("vt") == 0)
			vt.push_back(vec2(stof(t[1]), stof(t[2])));
		else if (flag.compare("vn") == 0)
			vn.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		else if (flag.compare("usemtl") == 0) {
			col = whiteColor;
		}			
		else if (flag.compare("f") == 0) {
			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");
			vector<string> p4;
			if (t.size() == 5)
				p4 = tokenize(t[4], "/");

			vec.push_back(v[stoi(p1[0])]); color.push_back(col);
			vec.push_back(v[stoi(p2[0])]); color.push_back(col);
			vec.push_back(v[stoi(p3[0])]); color.push_back(col);
			
			tex.push_back(vt[stoi(p1[1])]);
			tex.push_back(vt[stoi(p2[1])]);
			tex.push_back(vt[stoi(p3[1])]);

			normal.push_back(vn[stoi(p1[2])]);
			normal.push_back(vn[stoi(p2[2])]);
			normal.push_back(vn[stoi(p3[2])]);
			
			/* flat shading */
			normal_flat.push_back(vn[stoi(p1[2])]);
			normal_flat.push_back(vn[stoi(p1[2])]);
			normal_flat.push_back(vn[stoi(p1[2])]);

			/* wire Frame */
			line.push_back(v[stoi(p1[0])]); lineColor.push_back(blackColor);
			line.push_back(v[stoi(p2[0])]); lineColor.push_back(blackColor);
			line.push_back(v[stoi(p2[0])]); lineColor.push_back(blackColor);
			line.push_back(v[stoi(p3[0])]); lineColor.push_back(blackColor);

			/* normal mapping */
			vec3 pos1 = v[stoi(p2[0])] - v[stoi(p1[0])];
			vec3 pos2 = v[stoi(p3[0])] - v[stoi(p1[0])];
			vec2 uv1 = vt[stoi(p2[1])] - vt[stoi(p1[1])];
			vec2 uv2 = vt[stoi(p3[1])] - vt[stoi(p1[1])];
			float r = 1.0f / (uv1.x * uv2.y - uv1.y * uv2.x);

			vec3 tan = (pos1 * uv2.y - pos2 * uv1.y) * r;
			vec3 bi = (pos2 * uv1.x - pos1 * uv2.x) * r;
			for (int i = 0; i < 3; i++) {
				tangent.push_back(tan);
				binormal.push_back(bi);
			}

			if (t.size() == 5) {
				vec.push_back(v[stoi(p3[0])]);
				vec.push_back(v[stoi(p4[0])]);
				vec.push_back(v[stoi(p1[0])]);
				color.push_back(col);
				color.push_back(col);
				color.push_back(col);


				tex.push_back(vt[stoi(p3[1])]);
				tex.push_back(vt[stoi(p4[1])]);
				tex.push_back(vt[stoi(p1[1])]);

				normal.push_back(vn[stoi(p3[2])]);
				normal.push_back(vn[stoi(p4[2])]);
				normal.push_back(vn[stoi(p1[2])]);


				/* flat shading */
				normal_flat.push_back(vn[stoi(p1[2])]);
				normal_flat.push_back(vn[stoi(p1[2])]);
				normal_flat.push_back(vn[stoi(p1[2])]);

				/* wire Frame */
				line.push_back(v[stoi(p3[0])]); lineColor.push_back(blackColor);
				line.push_back(v[stoi(p4[0])]); lineColor.push_back(blackColor);
				line.push_back(v[stoi(p4[0])]); lineColor.push_back(blackColor);
				line.push_back(v[stoi(p1[0])]); lineColor.push_back(blackColor);

				/* normal mapping */
				pos1 = v[stoi(p4[0])] - v[stoi(p3[0])];
				pos2 = v[stoi(p1[0])] - v[stoi(p3[0])];
				uv1 = vt[stoi(p4[1])] - vt[stoi(p3[1])];
				uv2 = vt[stoi(p1[1])] - vt[stoi(p3[1])];
				r = 1.0f / (uv1.x * uv2.y - uv1.y * uv2.x);

				tan = (pos1 * uv2.y - pos2 * uv1.y) * r;
				bi = (pos2 * uv1.x - pos1 * uv2.x) * r;

				for (int i = 0; i < 3; i++) {
					tangent.push_back(tan);
					binormal.push_back(bi);
				}
			}
			else {
				/* wire Frame */
				line.push_back(v[stoi(p3[0])]); lineColor.push_back(blackColor);
				line.push_back(v[stoi(p1[0])]); lineColor.push_back(blackColor);
			}
		}
	}

	infile.close();
	cout << "Success!!  " << file << endl;
	cout << "v : " << vertex[0] << endl;
	cout << "vt : " << vertex[1] << endl;
	cout << "vn : " << vertex[2] << endl;
	cout << "f : " << vertex[3] << endl;
	cout << "num of line : " << line.size() << endl;
	cout << endl;

	buf[1] = vec.size(); // vertex Size
	buf[2] = line.size(); // line vertex Size

	GLuint verSize = buf[1] * sizeof(vec3);
	GLuint colSize = buf[1] * sizeof(vec4);
	GLuint textureSize = buf[1] * sizeof(vec2);
	GLuint normalSize = buf[1] * sizeof(vec3);
	GLuint lineSize = buf[2] * sizeof(vec3);
	GLuint lineColSize = buf[2] * sizeof(vec4);

	glGenBuffers(1, &buf[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, verSize + colSize + textureSize  + normalSize * 4 + lineSize + lineColSize, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verSize, vec.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize, colSize, color.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize, textureSize, tex.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize, normalSize, normal.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize + normalSize, normalSize, normal_flat.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize + normalSize*2, lineSize, line.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize + normalSize*2 + lineSize, lineColSize, lineColor.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize + normalSize * 2 + lineSize + lineColSize, normalSize, tangent.front());
	glBufferSubData(GL_ARRAY_BUFFER, verSize + colSize + textureSize + normalSize * 3 + lineSize + lineColSize, normalSize, binormal.front());
	
	v.clear();
	vt.clear();
	vn.clear();
	vec.clear();
	tex.clear();
	normal.clear();
	normal_flat.clear();
	line.clear();
	lineColor.clear();
	tangent.clear();
	binormal.clear();
}