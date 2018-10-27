#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	map = ball = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	ball = App->textures->Load("Images/redball.png"); 
	bonus_fx = App->audio->LoadFx("Audio/bonus.wav");
	map = App->textures->Load("Images/pinball.png"); 

	DrawColliders();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(map, 0, 0, NULL); 

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 9, b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50, 0, b2_dynamicBody));
	}


	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	App->audio->PlayFx(bonus_fx);
}

void ModuleSceneIntro::DrawColliders()
{

	int Map[150] = {
	41, 201,
	60, 228,
	75, 249,
	92, 274,
	100, 290,
	105, 302,
	109, 316,
	111, 329,
	113, 347,
	113, 370,
	111, 396,
	109, 413,
	110, 434,
	113, 454,
	122, 475,
	132, 492,
	143, 505,
	155, 517,
	168, 526,
	184, 536,
	195, 541,
	201, 542,
	201, 570,
	283, 570,
	283, 543,
	305, 534,
	329, 519,
	350, 496,
	365, 469,
	372, 442,
	374, 412,
	371, 386,
	367, 369,
	367, 355,
	368, 333,
	373, 311,
	380, 297,
	393, 277,
	401, 266,
	400, 255,
	394, 249,
	385, 248,
	376, 256,
	367, 266,
	363, 266,
	362, 262,
	366, 253,
	373, 238,
	377, 227,
	381, 215,
	384, 198,
	384, 179,
	382, 160,
	370, 133,
	352, 118,
	326, 104,
	306, 97,
	285, 93,
	282, 81,
	204, 80,
	200, 93,
	176, 98,
	151, 108,
	138, 117,
	127, 126,
	115, 120,
	101, 116,
	85, 115,
	68, 119,
	53, 128,
	44, 137,
	36, 152,
	33, 171,
	34, 186,
	40, 201
	};
	map_ = App->physics->CreateChain(0, 0, Map, 150); 

	int top_left1[30] = {
	91, 229,
	98, 241,
	103, 249,
	109, 257,
	114, 262,
	118, 266,
	123, 267,
	124, 262,
	121, 253,
	117, 244,
	113, 235,
	109, 227,
	100, 228,
	91, 229,
	90, 229
	};
	top_left_1 = App->physics->CreateChain(0, 0, top_left1, 30); 

	int top_left2[22] = {
	127, 216,
	133, 211,
	138, 203,
	141, 211,
	144, 220,
	147, 228,
	148, 234,
	147, 238,
	141, 237,
	134, 229,
	127, 216
	};
	top_left_2 = App->physics->CreateChain(0, 0, top_left2, 22);

	int top_left3[24] = {
	142, 147,
	146, 156,
	147, 163,
	147, 171,
	165, 165,
	178, 160,
	185, 155,
	188, 146,
	184, 136,
	175, 132,
	162, 134,
	141, 147
	};
	top_left_3 = App->physics->CreateChain(0, 0, top_left3, 24); 

	int middle_top1[18] = {
	222, 121,
	227, 121,
	230, 124,
	230, 148,
	226, 152,
	222, 152,
	219, 148,
	219, 125,
	221, 121
	};
	middle_top_1 = App->physics->CreateChain(0, 0, middle_top1, 18); 

	int middle_top2[18] = {
	259, 121,
	264, 121,
	267, 124,
	267, 148,
	264, 152,
	260, 152,
	256, 148,
	256, 125,
	258, 121
	};
	middle_top_2 = App->physics->CreateChain(0, 0, middle_top2, 18); 

	int middle[36] = {
	205, 295,
	206, 287,
	213, 284,
	226, 282,
	243, 281,
	262, 282,
	275, 284,
	282, 289,
	281, 299,
	276, 310,
	269, 318,
	259, 324,
	259, 327,
	225, 327,
	225, 323,
	217, 318,
	208, 308,
	204, 295
	};
	middle_ = App->physics->CreateChain(0, 0, middle, 36); 

	int top_right1[22] = {
	337, 142,
	317, 132,
	308, 132,
	300, 137,
	297, 146,
	298, 154,
	305, 160,
	332, 170,
	333, 160,
	334, 151,
	336, 142
	};
	top_right_1 = App->physics->CreateChain(0, 0, top_right1, 22); 

	int top_right2[18] = {
	344, 211,
	350, 216,
	356, 221,
	351, 232,
	345, 238,
	339, 239,
	336, 235,
	337, 227,
	343, 211
	};
	top_right_2 = App->physics->CreateChain(0, 0, top_right2, 18); 

	int bottom_right1[28] = {
	290, 459,
	295, 448,
	302, 432,
	309, 419,
	312, 415,
	317, 415,
	320, 419,
	319, 429,
	316, 440,
	310, 452,
	301, 463,
	296, 466,
	291, 464,
	291, 459
	};
	bottom_right_1 = App->physics->CreateChain(0, 0, bottom_right1, 28); 

	int bottom_right2[52] = {
		347, 410,
		344, 415,
		343, 423,
		341, 431,
		339, 440,
		335, 450,
		330, 459,
		324, 467,
		314, 478,
		306, 483,
		304, 489,
		313, 484,
		318, 489,
		313, 499,
		318, 498,
		325, 492,
		332, 483,
		338, 475,
		344, 464,
		347, 455,
		350, 444,
		352, 431,
		353, 420,
		353, 415,
		352, 411,
		348, 410
	};
	bottom_right_2 = App->physics->CreateChain(0, 0, bottom_right2, 52); 

	int bottom_left1[48] = {
		133, 410,
		131, 414,
		131, 419,
		132, 434,
		137, 460,
		144, 475,
		152, 486,
		159, 493,
		164, 497,
		170, 498,
		163, 488,
		167, 484,
		178, 486,
		175, 482,
		166, 475,
		159, 467,
		152, 457,
		147, 447,
		143, 437,
		141, 429,
		139, 420,
		139, 413,
		137, 410,
		135, 410
	};
	bottom_left_1 = App->physics->CreateChain(0, 0, bottom_left1, 48); 

	int bottom_left2[24] = {
	166, 418,
	169, 415,
	173, 415,
	194, 455,
	195, 462,
	193, 466,
	187, 466,
	180, 459,
	173, 449,
	168, 440,
	166, 430,
	165, 418
	};
	bottom_left_2 = App->physics->CreateChain(0, 0, bottom_left2, 24); 

	int ball_corridor1[18] = {
	450, 345,
	447, 342,
	443, 342,
	439, 345,
	439, 437,
	442, 441,
	447, 441,
	450, 437,
	451, 345
	};
	ball_corridor_1 = App->physics->CreateChain(0, 0, ball_corridor1, 18); 

	int ball_corridor2[70] = {
		406, 136,
		418, 144,
		426, 155,
		431, 170,
		432, 186,
		428, 204,
		423, 224,
		419, 248,
		417, 272,
		417, 304,
		418, 570,
		440, 570,
		440, 467,
		460, 466,
		466, 463,
		470, 458,
		471, 453,
		471, 347,
		468, 343,
		463, 340,
		456, 339,
		443, 339,
		442, 276,
		443, 246,
		445, 230,
		450, 208,
		454, 192,
		456, 172,
		452, 152,
		443, 134,
		430, 120,
		412, 110,
		390, 107,
		375, 109,
		366, 112
	};
	ball_corridor_2 = App->physics->CreateChain(0, 0, ball_corridor2, 70);

	int football1[30] = {
	190, 237,
	190, 229,
	193, 225,
	195, 223,
	198, 222,
	201, 222,
	204, 223,
	208, 225,
	210, 229,
	210, 236,
	208, 239,
	204, 243,
	198, 243,
	193, 241,
	189, 238
	};
	football_1 = App->physics->CreateChain(0, 0, football1, 30, 1.0f); 

	int football2[30] = {
	233, 195,
	233, 201,
	235, 204,
	239, 207,
	247, 207,
	250, 205,
	252, 201,
	252, 195,
	250, 191,
	248, 189,
	245, 188,
	241, 188,
	238, 189,
	235, 191,
	232, 194
	};
	football_2 = App->physics->CreateChain(0, 0, football2, 30, 1.0f); 

	int football3[30] = {
	277, 226,
	275, 230,
	275, 236,
	277, 240,
	282, 242,
	288, 242,
	292, 240,
	294, 236,
	294, 229,
	292, 225,
	289, 223,
	286, 222,
	282, 222,
	279, 224,
	276, 226
	};
	football_3 = App->physics->CreateChain(0, 0, football3, 30, 1.0f); 
}
