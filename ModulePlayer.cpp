#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 125;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 11, 59, 94});
	idle.frames.push_back({95, 11, 60, 94});
	idle.frames.push_back({184, 11, 59, 94});
	idle.frames.push_back({276, 11, 60, 94});
	idle.frames.push_back({366, 11, 60, 94});
	idle.speed = 0.2f;

	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// walk forward animation
	forward.frames.push_back({6, 128, 64, 92});
	forward.frames.push_back({78, 128, 64, 92});
	forward.frames.push_back({162, 128, 64, 92});
	forward.frames.push_back({259, 128, 64, 92});
	forward.frames.push_back({352, 128, 64, 92});
	forward.frames.push_back({432, 128, 64, 92});
	forward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

update_status ModulePlayer::PreUpdate()
{
	anim = &idle;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		anim = &forward;
		++position.x;
	}

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		anim = &backward;
		--position.x;
	}

	return UPDATE_CONTINUE;
}

// Update
update_status ModulePlayer::Update()
{
	App->renderer->Blit(graphics, position.x, position.y, &(anim->GetCurrentFrame()), 1.0f);

	return UPDATE_CONTINUE;
}
