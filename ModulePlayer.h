#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	float speed;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation backward;
	Animation forward;
	iPoint position;

	void updatePosition();
	void updateAnimState();
};

#endif // __MODULEPLAYER_H__