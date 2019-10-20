#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include <cmath>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// TODO 2 : setup the foreground (red ship) with
	// coordinates x,y,w,h from ken_stage.png --- DONE
	foreground.x = 9;
	foreground.y = 19;
	foreground.w = 543;
	foreground.h = 208;

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

	// TODO 4: Setup Girl Animation from coordinates from ken_stage.png ---  DONE
	bgGirl.frames.push_back({ 625, 15, 32, 55 });
	bgGirl.frames.push_back({ 625, 79, 32, 55 });
	bgGirl.frames.push_back({ 625, 143, 32, 55 });
	bgGirl.speed = 0.05f;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");

	// TODO 7: Enable the player module
	App->player->Start();

	// TODO 0: trigger background music --- DONE
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
	// TODO 5: make sure the ship goes up and down --- DONE

	// Draw everything --------------------------------------
	// TODO 1: Tweak the movement speed of the sea&sky + flag to your taste --- DONE (Small improvement created as well)
	App->renderer->Blit(graphics, 0, 0, &background, 1.08f, 1.12f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 1.08f, 1.12f); // flag animation

	// TODO 3: Draw the ship. Be sure to tweak the speed. --- DONE
	App->renderer->Blit(graphics, 0, -8 + (shipSpeed * sin(shipCycle)), &foreground, 1.05f, 1.1f); // Red ship
	App->renderer->Blit(graphics, 192, 100 + (shipSpeed * sin(shipCycle)), &(bgGirl.GetCurrentFrame()), 1.05f, 1.1f); // Girl animation
	shipCycle += 0.1f;


	// TODO 6: Draw the girl. Make sure it follows the ship movement! --- DONE
	
	App->renderer->Blit(graphics, 0, 170, &ground);

	App->player->Update();

	// TODO 10: Build an entire new scene "honda", you can find its --- DONE
	// and music in the Game/ folder

	// TODO 11: Make that pressing space triggers a switch to honda logic module
	// using FadeToBlack module
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack((Module*)App->scene_honda, this);
	}

	return UPDATE_CONTINUE;
}