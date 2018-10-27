#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	kickers = App->textures->Load("pinball/Kickers.png");

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

	//// KICKERS INPUTS

	//if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	//{
	//	joint_left->EnableMotor(true);
	//}
	//if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	//{
	//	joint_left->EnableMotor(false);
	//}

	//if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	//{
	//	joint_right->EnableMotor(true);

	//}
	//if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	//{
	//	joint_right->EnableMotor(false);
	//}

	//// BALL LAUNCHER INPUTS

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	jointLauncher->EnableMotor(true);
	//	//current_animation = &launcher_anim_launching;
	//}

	//if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	//{
	//	jointLauncher->EnableMotor(false);
	//	//current_animation = &launcher_anim_idle;
	//}

	//int x, y;

	////LEFT KICKER
	//kicker_left->GetPosition(x, y);
	//App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_left->GetRotation());

	////RIGHT KICKER
	//kicker_right->GetPosition(x, y);
	//App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_right->GetRotation() + 180);
	return UPDATE_CONTINUE;
}

//void ModulePlayer::CreateFlippers()
//{
//	// Left flipper			------------------------------------------------------------
//
//	b2RevoluteJointDef revoluteJointDef;
//
//
//	kicker_left = App->physics->CreateRectangle(159, 767, 70, 20, 32 * DEGTORAD);
//	pivot_left = App->physics->CreateCircle(159, 767, 10, b2_staticBody);
//	kicker_left->body->SetGravityScale(30.0f);
//
//	revoluteJointDef.bodyA = kicker_left->body;
//	revoluteJointDef.bodyB = pivot_left->body;
//
//	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-30), 0);		// Set the pivot point of the rectangle where the center of the circle is
//	revoluteJointDef.localAnchorB.Set(0, 0);						// Set the pivot point of the circle on its center
//	revoluteJointDef.collideConnected = false;
//
//
//	revoluteJointDef.upperAngle = 32 * DEGTORAD;			// Angle limits
//	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
//	revoluteJointDef.enableLimit = true;
//
//	revoluteJointDef.motorSpeed = 1500.0f * DEGTORAD;		// Motor
//	revoluteJointDef.maxMotorTorque = 1500;
//	revoluteJointDef.enableMotor = false;
//
//
//	joint_left = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
//
//	// ---------------------------------------------------------------------------------
//
//	// Right flipper		------------------------------------------------------------
//
//
//	kicker_right = App->physics->CreateRectangle(318, 767, 70, 20, -32 * DEGTORAD);
//	pivot_right = App->physics->CreateCircle(318, 767, 10, b2_staticBody);
//	kicker_right->body->SetGravityScale(30.0f);
//
//	revoluteJointDef.bodyA = kicker_right->body;
//	revoluteJointDef.bodyB = pivot_right->body;
//
//	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(30), 0);		// Set the pivot point of the rectangle where the center of the circle is
//	revoluteJointDef.localAnchorB.Set(0, 0);						// Set the pivot point of the circle on its center
//	revoluteJointDef.collideConnected = false;
//	revoluteJointDef.referenceAngle = 0;
//
//	revoluteJointDef.upperAngle = 32 * DEGTORAD;			// Angle limits
//	revoluteJointDef.lowerAngle = -32 * DEGTORAD;
//	revoluteJointDef.enableLimit = true;
//
//	revoluteJointDef.motorSpeed = -1500.0f * DEGTORAD;		// Motor
//	revoluteJointDef.maxMotorTorque = 1500;
//	revoluteJointDef.enableMotor = false;
//
//	joint_right = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
//
//	// ---------------------------------------------------------------------------------
//
//
//}



