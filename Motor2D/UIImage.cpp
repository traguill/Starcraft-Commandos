#include "UIImage.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1UIManager.h"

UIImage::UIImage() : UIEntity()
{
	section = { 0, 0, 0, 0 };
	type = IMAGE;
	interactable = true;
}

UIImage::UIImage(SDL_Rect _section, const int x, const int y) : UIEntity()
{
	interactable = false;
	type = IMAGE;
	section = _section;

	rect.x = x;
	rect.y = y;
	rect.w = _section.w;
	rect.h = _section.h;
	init_pos.x = x;
	init_pos.y = y;
}

// Destructor
UIImage::~UIImage()
{}

// Called before render is available
bool UIImage::Update(float dt)
{
	bool ret = true;

	iPoint cam_pos(App->render->camera.x, App->render->camera.y);
	rect.x = init_pos.x - cam_pos.x;
	rect.y = init_pos.y - cam_pos.y;

	App->render->Blit(App->ui->GetAtlas(), rect.x, rect.y, &section);

	return ret;
}

bool UIImage::CleanUp()
{
	bool ret = true;

	return ret;
}