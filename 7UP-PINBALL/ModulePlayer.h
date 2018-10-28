#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleTextures.h"
#include "Box2D/Box2D/Box2D.h"
#include <string>

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void Ball(); 
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB); 
	void LoadKickers(); 
	void Launcher(); 

public:
	//Textures
	SDL_Texture* kickers;
	SDL_Texture* ball_tx; 

	//Player attributes
	uint tries = 5;

	//Kicker right
	PhysBody* kicker_left;
	PhysBody* pivot_left;
	b2RevoluteJoint* joint_left;

	//Kicker left 
	PhysBody* kicker_right;
	PhysBody* pivot_right;
	b2RevoluteJoint* joint_right;

	//Sensors
	PhysBody* dead_sensor; 
	
	//bools
	bool is_dead = false; 

private:

	PhysBody* ball; 

	PhysBody* launcher;
	PhysBody* launcher_pivot;
	b2PrismaticJoint* jointLauncher;

	uint kicker_fx;

};