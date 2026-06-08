#pragma once
#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>

class Alien : public GameObject, public Box {

	graphics::Brush alien_brush;

	int hp;
	int ID;

public:
	Alien(float x, float y, float w, float h, int hp, int id) { 
		pos_x = x;
		pos_y = y;
		width = w;
		height = h;
		this->hp = hp;
		this->ID = id;

    }

	void update(float dt) override;

	float getPos_x() { return pos_x; }
	float getPos_y() { return pos_y; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	int getHp() { return hp; }
	int getId() { return ID; }

	void setPos_x(float x) { pos_x = x; }
	void setPos_y(float y) { pos_y = y; }
	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
	void setHp(int hp) { this->hp = hp; }
	void setId(int id) { this->ID = id; }


	void debugDraw();
};
