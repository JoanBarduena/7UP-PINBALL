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
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	map = App->textures->Load("pinball/pinball.png"); 

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
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
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
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
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
	201, 549,
	283, 549,
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
	41, 201
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
	91, 229
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
	142, 147
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
	222, 121
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
	259, 121
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
	205, 295
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
	337, 142
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
	344, 211
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
	290, 459
	};
	bottom_right_1 = App->physics->CreateChain(0, 0, bottom_right1, 28); 

	int bottom_right2[44] = {
	318, 473,
	324, 467,
	329, 461,
	334, 451,
	340, 439,
	343, 425,
	344, 413,
	347, 410,
	351, 410,
	353, 413,
	353, 420,
	352, 442,
	348, 456,
	341, 472,
	330, 487,
	319, 497,
	312, 499,
	306, 496,
	304, 491,
	304, 486,
	307, 482,
	318, 473
	};
	bottom_right_2 = App->physics->CreateChain(0, 0, bottom_right2, 44); 

	int bottom_left1[40] = {
	170, 498,
	176, 497,
	178, 492,
	178, 485,
	172, 479,
	159, 467,
	149, 451,
	142, 434,
	140, 422,
	139, 413,
	135, 409,
	131, 412,
	131, 422,
	131, 435,
	133, 449,
	139, 466,
	146, 478,
	155, 489,
	163, 497,
	170, 498
	};
	bottom_left_1 = App->physics->CreateChain(0, 0, bottom_left1, 40); 

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
	166, 418
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
	450, 345
	};
	ball_corridor_1 = App->physics->CreateChain(0, 0, ball_corridor1, 18); 

	int ball_corridor2[22] = {
	418, 318,
	418, 465,
	460, 465,
	465, 463,
	468, 460,
	470, 455,
	470, 350,
	468, 344,
	462, 340,
	449, 340,
	449, 344
	};
	ball_corridor_2 = App->physics->CreateChain(0, 0, ball_corridor2, 22); 

	int football1[26] = {
	196, 222,
	204, 222,
	209, 224,
	212, 228,
	212, 237,
	210, 241,
	205, 244,
	196, 244,
	191, 241,
	189, 236,
	189, 229,
	191, 225,
	195, 222
	};
	football_1 = App->physics->CreateChain(0, 0, football1, 26); 

	int football2[26] = {
	239, 187,
	246, 187,
	251, 189,
	254, 194,
	254, 201,
	252, 206,
	247, 209,
	239, 209,
	235, 207,
	232, 203,
	232, 195,
	234, 191,
	239, 187
	};
	football_2 = App->physics->CreateChain(0, 0, football2, 26); 

	int football3[26] = {
	281, 222,
	289, 222,
	293, 224,
	296, 228,
	296, 236,
	294, 241,
	290, 244,
	281, 244,
	277, 242,
	274, 238,
	274, 229,
	276, 225,
	281, 222
	};
	football_3 = App->physics->CreateChain(0, 0, football3, 26); 
}
