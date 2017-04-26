#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"

struct Path;
struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation* animation = nullptr;
	uint hitPoints;
	uint currentTime;
	uint lastTime;
	int time = 0;
	bool shot;

public:
	Collider* collider = nullptr;
	iPoint position;
	Path path;
	int type;
	int score;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual uint getHitPoints() { return 0; }
};

#endif // __ENEMY_H__