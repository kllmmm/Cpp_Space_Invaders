#pragma once

#include "gameobject.h"
#include "box.h"
#include <sgg/graphics.h>
#include "player.h"

class Laser : public GameObject, public Box {


	graphics::Brush laser_brush;

	int ID = 0;

public:
	Laser(std::string name) : GameObject(name) {}
	void update(float dt) override;
	void init();
	void draw() override;

	void setPosX(float x) { pos_x = x; }
	void setPosY(float y) { pos_y = y; }
	float getPosX() { return pos_x; }
	float getPosY() { return pos_y; }
	void setID(int id) { this->ID = id; }
	int getID() { return ID; }

protected:
	void debugDraw();

};
