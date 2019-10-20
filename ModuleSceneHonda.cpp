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



ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 850;
	ground.h = 60;

	//Pool thingy
	foreground.x = 163;
	foreground.y = 65;
	foreground.w = 413;
	foreground.h = 53;

	// Background
	background.x = 121;
	background.y = 127;
	background.w = 670;
	background.h = 200;

	// Roof
	roof.x = 92;
	roof.y = 9;
	roof.w = 766;
	roof.h = 50;

	// TODO 4: Pool water thingy
	pool.frames.push_back({ 9, 449, 284, 19  });
	pool.frames.push_back({ 297, 448, 284, 19 });
	pool.frames.push_back({ 583, 448, 284, 19 });
	pool.speed = 0.02f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading Honda scene");

	graphics = App->textures->Load("honda_stage2.png");

	// TODO 7: Enable the player module
	App->player->Start();

	// TODO 0: trigger background music --- DONE
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
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 1.08f, 1.12f);
	App->renderer->Blit(graphics, 0, 0, &roof, 1.08f, 1.12f);
	App->renderer->Blit(graphics, 0, -8, &foreground, 1.05f, 1.1f); 
	App->renderer->Blit(graphics, 560, 8, &(pool.GetCurrentFrame()), 1.08f, 1.12f);
	App->renderer->Blit(graphics, 0, 170, &ground);

	App->player->Update();

	return UPDATE_CONTINUE;
}