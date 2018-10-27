#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	kickers = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	kickers = App->textures->Load("pinball/kicker.png");

	LoadKickers(); 

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(kickers);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	// KICKERS INPUTS

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		joint_left->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		joint_left->EnableMotor(false);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		joint_right->EnableMotor(true);

	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		joint_right->EnableMotor(false);
	}

	// BALL LAUNCHER INPUTS

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		//jointLauncher->EnableMotor(true);
		//current_animation = &launcher_anim_launching;
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//jointLauncher->EnableMotor(false);
		//current_animation = &launcher_anim_idle;
	}

	int x, y;

	//LEFT KICKER
	kicker_left->GetPosition(x, y);
	App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_left->GetRotation());

	//RIGHT KICKER
	kicker_right->GetPosition(x, y);
	App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_right->GetRotation() + 180);
	return UPDATE_CONTINUE;
}

void ModulePlayer::LoadKickers()
{
	// LEFT KICKER	

	b2RevoluteJointDef revoluteJointDef;

	kicker_left = App->physics->CreateRectangle(174, 492, 48, 10, 20 * DEGTORAD, b2_dynamicBody);
	pivot_left = App->physics->CreateCircle(174, 492, 6, b2_staticBody);
	kicker_left->body->SetGravityScale(30.0f);

	revoluteJointDef.bodyA = kicker_left->body;
	revoluteJointDef.bodyB = pivot_left->body;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-30), 0);		// PIVOT POINT OF THE RECTANGLE ON THE CENTER OF THE CIRCLE
	revoluteJointDef.localAnchorB.Set(0, 0);						// PIVOT POINT OF THE CIRCLE ON ITS CENTER
	revoluteJointDef.collideConnected = false;

	//ANGLE LIMITS
	revoluteJointDef.upperAngle = 32 * DEGTORAD;		
	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
	revoluteJointDef.enableLimit = true;

	//MOTOR SPEED AND TORQUE 
	revoluteJointDef.motorSpeed = 1500.0f * DEGTORAD;		
	revoluteJointDef.maxMotorTorque = 1500;
	revoluteJointDef.enableMotor = false;


	joint_left = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);

	// RIGHT KICKER

	kicker_right = App->physics->CreateRectangle(310, 492, 48, 10, -32 * DEGTORAD, b2_dynamicBody); //RECTANGLE COORDENATES
	pivot_right = App->physics->CreateCircle(310, 492, 6, b2_staticBody); //CIRCLE COORDENATES
	kicker_right->body->SetGravityScale(30.0f);

	revoluteJointDef.bodyA = kicker_right->body;
	revoluteJointDef.bodyB = pivot_right->body;

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(30), 0);		// PIVOT POINT OF THE RECTANGLE ON THE CENTER OF THE CIRCLE
	revoluteJointDef.localAnchorB.Set(0, 0);						// PIVOT POINT OF THE CIRCLE ON ITS CENTER
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.referenceAngle = 0;

	//ANGLE LIMITS
	revoluteJointDef.upperAngle = 32 * DEGTORAD;		
	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
	revoluteJointDef.enableLimit = true;

	//MOTOR SPEED AND TORQUE
	revoluteJointDef.motorSpeed = -1500.0f * DEGTORAD;	
	revoluteJointDef.maxMotorTorque = 1500;
	revoluteJointDef.enableMotor = false;

	joint_right = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);

	// ---------------------------------------------------------------------------------


}



