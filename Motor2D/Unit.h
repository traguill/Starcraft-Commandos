#ifndef __UNIT_H__
#define __UNIT_H__

#include "TacticalAI.h"
#include "p2Defs.h"
#include "p2Point.h"
#include "Entity.h"
#include "UIProgressBar.h"
#include "Bullet.h"
#include <vector>
#include <queue>

#define MOVE_RADIUS 8

#define INVISIBILITY_ALPHA 155 //Load this from xml...

enum UNIT_TYPE{ 
	MARINE, 
	FIREBAT, 
	GHOST, 
	MEDIC, 
	OBSERVER, 
	ENGINEER, 
	SHIP, 
	GOLIATH, 
	TANK, 
	VALKYRIE };

enum UNIT_STATE{
	UNIT_IDLE, 
	UNIT_MOVE,
	UNIT_ATTACK,
	UNIT_DIE
};

enum UNIT_ABILITY
{
	INVISIBLE,
	SNIPPER,
	HEAL
};

//FIREBATATTACK
struct Projectile
{
	Sprite sprite;

	float anim_speed;

	iPoint pos_up;
	iPoint pos_down;
	iPoint pos_right;
	iPoint pos_left;
	iPoint pos_up_right;
	iPoint pos_down_right;
	iPoint pos_up_left;
	iPoint pos_down_left;

	Animation up;
	Animation down;
	Animation right;
	Animation left;
	Animation up_right;
	Animation down_right;
	Animation up_left;
	Animation down_left;

	iPoint current_pos;
	Animation* current_animation;

	Projectile(){}

	Projectile(Projectile* p);

	~Projectile()
	{
		sprite.texture = NULL;
		current_animation = NULL;
	}
};

class Unit : public Entity
{
	friend class j1EntityManager;	//Provisional

public:

	Unit();
	Unit(Unit* u, bool is_enemy);

	~Unit();


	void Update(float dt);
	void Draw();

	void SetPath(vector<iPoint> _path);
	void AddPath(vector<iPoint> _path); //Adds the path to the existing one combining them
	vector<iPoint> GetPath()const;

	iPoint GetDirection()const; //Returns the direction in form of a vector. Ex: (1,1) -north-east (-1) south etc

	UNIT_TYPE GetType()const;
	uint GetRange()const;

	void SetTarget(Unit* unit);
	Unit* GetTarget();

	void DiscardTarget(); //Stops attacking the target for some reason

	bool IsVisible()const;

	void ApplyDamage(uint dmg, Unit* source);

private:

	void Move(float dt);
	void Attack(float dt);
	void SetDirection();
	void CenterUnit();

	void SetAnimation();

	bool CheckTargetRange();

	void Delete(); 

	void UseAbility(uint id); //Unit use the ability asigned to the id number
	void CastAbility(const UNIT_ABILITY ability); //Actual method to USE the ability

	//Abilities
	void Invisibility();
	void SetVisible();

	void Snipper();
	void DisableSnipper();
	void Shoot(int x, int y);

private:

	uint speed;
	uint damage;
	uint range;
	uint cool;
	vector<iPoint> path;
	bool costume;
	bool selected = false;
	Unit* target = NULL;
	UNIT_TYPE type;

	float max_mana;
	float mana;
	int mana_regen;

	list<Unit*> attacking_units; //Units that are attacking me

	//For abilities
	bool invisible = false;
	bool snipping = false;

	list<UNIT_ABILITY> abilities;
public:
	UNIT_STATE state;
	queue<UNIT_EVENT> events;
	uint vision;

	//Can't change state when is resolving a collision or do another thing
	bool avoid_change_state = false;

	bool is_enemy;

	//Animations
	//MOVE
	Animation up;
	Animation down;
	Animation right;
	Animation left;
	Animation up_right;
	Animation down_right;
	Animation up_left;
	Animation down_left;
	//IDLE
	Animation i_up;
	Animation i_down;
	Animation i_right;
	Animation i_left;
	Animation i_up_right;
	Animation i_down_right;
	Animation i_up_left;
	Animation i_down_left;
	//ATTACK
	Animation a_up;
	Animation a_down;
	Animation a_right;
	Animation a_left;
	Animation a_up_right;
	Animation a_down_right;
	Animation a_up_left;
	Animation a_down_left;
	//DEATH
	iPoint death_pos_corrector;
	iPoint death_size;
	Animation death;

	Projectile p;

	//Has to be updated inside update();
	Animation* current_animation;
	float walk_anim_speed;
	float idle_anim_speed;
	float attack_anim_speed;
	float death_anim_speed;

	//Pathfinding
	fPoint direction;
	bool has_destination = false;
	iPoint	dst_point; //Tile point

	//Attacking
	float cool_timer = 0;

	//HP bar
	UIProgressBar* hp_bar;
	UIProgressBar* mana_bar;

	//Sniping
	bool has_hit = false; //If the bullet that I've shoot have hit something (wall, end, enemy)


};
#endif