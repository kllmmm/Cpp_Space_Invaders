#include "alien.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"

void Alien::update(float dt)
{
	static float direction = 1.f;

	float delta_time = dt / 1000.0f;  
	float s = .04f;
	float speed = s * delta_time;
	
	//If the ID is 1 then the alien is a normal alien that goes down.
	if (ID == 1) { 
		if (pos_y < state->getCanvasHeight() / 2.f) pos_y += speed;
		else pos_y += speed + .02f * delta_time;
			
	}

	//If it's 2 then the alien is the alien ship (mystery ship) and goes side to side
	else if (ID == 2) {
		pos_x += direction * 2.f * delta_time;
		if (pos_x >= 7.0f || pos_x <= 1.f) direction *= -1.f;
	}

	//When the ID becomes 3, the mystery ship attacks the player by going down and still side to side so it is harder to kill
	else {
		pos_y += speed + .3f * delta_time;
		pos_x += direction * 2.f * delta_time;
		if (pos_x >= 7.0f || pos_x <= 1.f) direction *= -1.f;
	}



	GameObject::update(dt);
}

//The dubugDraw() method, draws the hitbox of the alien
void Alien::debugDraw() {

	graphics::Brush debug_brush;
	SETCOLOR(debug_brush.fill_color, 1, 0.f, 0);
	SETCOLOR(debug_brush.outline_color, 1, 0.f, 0);
	debug_brush.fill_opacity = 0.4f;
	debug_brush.outline_opacity = 1.f;
	graphics::drawRect(pos_x, pos_y, width, height, debug_brush);

}
