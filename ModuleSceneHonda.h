#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda(bool start_enabled = true);
	~ModuleSceneHonda() = default;

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect bathtub;
	SDL_Rect ceiling;
	Animation water;
};

#endif // __MODULESCENEHONDA_H__
