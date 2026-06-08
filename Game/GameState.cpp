#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "alien.h"


GameState::GameState()
{
}

void GameState::init()
{
	//Player and Level initializations
	player = new Player("Player");
	player->init();

	level = new Level();
	level->init();

	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(asset_path + "nulshockbd.otf");
}

void GameState::draw()
{
	if (!level) return;

	//Draw the level
	level->draw();

}

void GameState::update(float dt)
{
	if (dt > 500) return;

	if (!level) return;

	//Update the level
	level->update(dt);
	
	//Enter debugging mode
	debugging = graphics::getKeyState(graphics::SCANCODE_0);

}

GameState* GameState::getInstance()
{
	if (unique_instance == nullptr) unique_instance = new GameState;
	return unique_instance;
}

GameState::~GameState()
{
	if (player) delete player;
	if (level) delete level;

}

std::string GameState::getAssetDir()
{
	return asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return asset_path + asset;
}

GameState* GameState::unique_instance = nullptr;