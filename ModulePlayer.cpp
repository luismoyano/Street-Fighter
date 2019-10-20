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
	speed = 1.0f;
	position.x = 100;
	position.y = 120;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.11f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({ 10, 120, 57, 100 });
	forward.frames.push_back({ 79, 120, 57, 100});
	forward.frames.push_back({ 158, 120, 57, 100 });
	forward.frames.push_back({ 255, 120, 57, 100 });
	forward.frames.push_back({ 349, 120, 57, 100 });
	forward.frames.push_back({ 429, 120, 57, 100 });
	forward.speed = 0.12f;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks --- Tried with dr memory and haven't found anything...
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

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	updatePosition();
	updateAnimState();

	return UPDATE_CONTINUE;
}

void ModulePlayer::updatePosition()
{
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		position.x -= speed;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		position.x += speed;
}

void ModulePlayer::updateAnimState()
{
	Animation* current = nullptr;
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		current = &backward;

	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		current = &forward;

	else current = &idle;


	App->renderer->Blit(graphics, position.x, position.y, &(current->GetCurrentFrame()), 1.08f, 1.12f);
}
