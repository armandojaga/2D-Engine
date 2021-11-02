#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://youtu.be/OEhmUuehGOA?t=72

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// Ground:
	ground.x = 8;
	ground.y = 375;
	ground.w = 848;
	ground.h = 65;
	// ground_draw_pos = iPoint(-96, 170);

	// Background:
	background.x = 120;
	background.y = 128;
	background.w = 671;
	background.h = 199;
	// background_draw_pos = iPoint(-16, -5);

	// Ceiling: 
	ceiling.x = 91;
	ceiling.y = 8;
	ceiling.w = 765;
	ceiling.h = 48;
	// ceiling_draw_pos = iPoint(-68, -5);

	// Bath Tub:
	bathtub.x = 164;
	bathtub.y = 66;
	bathtub.w = 336;
	bathtub.h = 51;
	// bath_tub_draw_pos = iPoint(140, 136);

	// Bath Tub Water:
	water.frames.push_back({8, 448, 284, 18});
	water.frames.push_back({296, 448, 284, 18});
	water.frames.push_back({580, 448, 284, 18});
	water.frames.push_back({296, 448, 284, 18});
	water.speed = 0.01f;
	// bath_tub_water_draw_pos = iPoint(168, 148);
}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	App->player->Enable();

	App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	constexpr float speed = 0.75f;
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 159, &ground);

	App->renderer->Blit(graphics, 50, -15, &background, speed);

	App->renderer->Blit(graphics, 0, -15, &ceiling, speed);

	App->renderer->Blit(graphics, 280, 125, &bathtub);

	App->renderer->Blit(graphics, 306, 137, &(water.GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
