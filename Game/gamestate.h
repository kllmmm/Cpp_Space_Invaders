#pragma once
#include <string>
#include <sgg/graphics.h>

class GameState {

private:
	std::string asset_path = "assets\\";

	float canvas_width = 8.0f;
	float canvas_height = 8.0f;

	static GameState* unique_instance;
	GameState();

	class Player* player = 0;
	class Level* level = 0;

	

public:
	bool debugging = false;

	graphics::Brush background_brush;
	graphics::Brush player_brush;

	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();
	~GameState();

	float getCanvasWidth() { return canvas_width; }
	float getCanvasHeight() { return canvas_height; }

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);

	class Player* getPlayer() { return player; }
	
};

