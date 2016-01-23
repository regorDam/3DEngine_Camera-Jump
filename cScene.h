
#pragma once

#include "cPlayer.h"

#define SIZE		5.0f

class cScene  
{
public:
	cScene();
	virtual ~cScene();

	void Render(cPlayer *Player);

	object *GetMap(){ return &plane; };
	bool Init();

private:
	void RenderRoom();
	object plane;
};

