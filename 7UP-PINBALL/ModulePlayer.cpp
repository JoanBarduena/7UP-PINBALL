#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

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
	//Load kickers
	kickers = App->textures->Load("Images/kicker.png");
	//Load audio
	kicker_fx = App->audio->LoadFx("Audio/kicker.wav"); 

	//Load of functions
	LoadKickers(); 
	Launcher(); 

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
		App->audio->PlayFx(kicker_fx); 
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		joint_left->EnableMotor(false);
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		joint_right->EnableMotor(true);
		App->audio->PlayFx(kicker_fx);

	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		joint_right->EnableMotor(false);
	}

	int x, y;

	//LEFT KICKER
	kicker_left->GetPosition(x, y);
	App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_left->GetRotation());

	//RIGHT KICKER
	kicker_right->GetPosition(x, y);
	App->renderer->Blit(kickers, x, y, NULL, 1.0f, kicker_right->GetRotation() + 180);

	//-------------------------------------------------------------------------------------

	//LAUNCHER INPUTS 
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		jointLauncher->EnableMotor(true);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		jointLauncher->EnableMotor(false);
	}
	launcher->GetPosition(x, y);
	//App->renderer->Blit(launcher_tex, x - 3, y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

void ModulePlayer::LoadKickers()
{
	// LEFT KICKER	

	b2RevoluteJointDef revoluteJointDef;

	kicker_left = App->physics->CreateRectangle(174, 492, 58, 13, 20 * DEGTORAD, b2_dynamicBody);
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

	kicker_right = App->physics->CreateRectangle(310, 492, 58, 13, -32 * DEGTORAD, b2_dynamicBody); //RECTANGLE COORDENATES
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

}

void ModulePlayer::Launcher()
{

	b2RevoluteJointDef revoluteJointDef;

	//LAUNCHER POSITIONS OF PUSHING RECTANGLE AND STATIC RECTANGLE
	launcher = App->physics->CreateRectangle(429, 508, 20, 80, 0, b2_dynamicBody);
	launcher_pivot = App->physics->CreateRectangle(429, 508, 20, 20, 0, b2_staticBody);

	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.bodyA = launcher->body;
	prismaticJointDef.bodyB = launcher_pivot->body;

	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.collideConnected = false;

	prismaticJointDef.localAxisA.Set(0, 1);


	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = 0;
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);

	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = 400;
	prismaticJointDef.motorSpeed = 5000;

	jointLauncher = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);

	//ANIMATIONS SOON...

}



