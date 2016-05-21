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

	ui_sprite.texture = App->ui->GetAtlas();
	ui_sprite.position = init_pos;
	ui_sprite.rect = section;
	
}

// Destructor
UIImage::~UIImage()
{}

// Called before render is available
bool UIImage::Update(float dt)
{
	bool ret = true;

	Draw();

	return ret;
}

//For images that make more than one blit
bool UIImage::Draw()
{
	iPoint cam_pos(App->render->camera.x, App->render->camera.y);
	ui_sprite.position.x = init_pos.x - cam_pos.x;
	ui_sprite.position.y = init_pos.y - cam_pos.y;

	App->render->BlitUI(&ui_sprite);

	return true;
}

bool UIImage::CleanUp()
{
	bool ret = true;

	return ret;
}

void UIImage::SetImageRect(SDL_Rect image_rect)
{
	ui_sprite.rect = image_rect;

	rect.w = ui_sprite.rect.w;
	rect.h = ui_sprite.rect.h;
}

Sprite* UIImage::GetSprite()
{
	return &ui_sprite;
}