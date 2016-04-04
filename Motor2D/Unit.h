#ifndef __UNIT_H__
#define __UNIT_H__


#include "p2Defs.h"
#include "p2Point.h"
#include "Entity.h"
#include <vector>


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
	UNIT_ATTACK
};

class Unit : public Entity
{
	friend class j1EntityManager;	//Provisional

public:

	Unit();
	Unit(Unit* u);


	void Update(float dt);
	void Draw();

	void SetPath(vector<iPoint> _path);

	iPoint GetDirection()const; //Returns the direction in form of a vector. Ex: (1,1) -north-east (-1) south etc
	UNIT_TYPE GetType()const;

private:

	void Move(float dt);
	void SetDirection();

private:

	uint speed;
	uint damage;
	uint vision;
	uint range;
	uint cool;
	Entity* target;
	vector<iPoint> path;
	bool costume;
	bool selected = false;
	UNIT_TYPE type;
	UNIT_STATE state;


	//Pathfinding
	fPoint direction;
	bool has_destination = false;
	iPoint	dst_point;

};
#endif