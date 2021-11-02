#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"
#include "SDL/include/SDL.h"

// Reference at https://youtu.be/OEhmUuehGOA?t=72

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	ship.x = 8;
	ship.y = 24;
	ship.w = 521;
	ship.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	girl.frames.push_back({624, 16, 32, 56});
	girl.frames.push_back({624, 80, 32, 56});
	girl.frames.push_back({624, 144, 32, 56});
	girl.frames.push_back({624, 80, 32, 56});
	girl.speed = 0.05f;

	shipMovement.frames.push_back({-1, 0, 0, 0});
	shipMovement.frames.push_back({-2, 0, 0, 0});
	shipMovement.frames.push_back({-3, 0, 0, 0});
	shipMovement.frames.push_back({ -4, 0, 0, 0 });
	shipMovement.frames.push_back({ -5, 0, 0, 0 });
	shipMovement.frames.push_back({ -5, 0, 0, 0 });
	shipMovement.frames.push_back({ -4, 0, 0, 0 });
	shipMovement.frames.push_back({ -3, 0, 0, 0 });
	shipMovement.frames.push_back({ -2, 0, 0, 0 });
	shipMovement.frames.push_back({ -1, 0, 0, 0 });
	shipMovement.speed = 0.02f;
}

ModuleSceneKen::~ModuleSceneKen()
{
}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");

	graphics = App->textures->Load("ken_stage.png");

	App->player->Enable();

	App->audio->PlayMusic("ken.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	const int change = shipMovement.GetCurrentFrame().x;

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	App->renderer->Blit(graphics, 0, change, &ship, 0.925f);//ship

	App->renderer->Blit(graphics, 192, 104 + change, &(girl.GetCurrentFrame()), 0.925f); //girl animation

	App->renderer->Blit(graphics, 0, 170, &ground);

	// TODO this should be in another class
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_honda, App->scene_ken, 1.0f);
	}

	return UPDATE_CONTINUE;
}
