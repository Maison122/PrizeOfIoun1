#pragma once
/*
==========================================================================
cSound.h
==========================================================================
*/

#ifndef _SOUND_H
#define _SOUND_H

// OpenGL Headers
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class cSound
{
private:

	Mix_Chunk * SoundFX = NULL;
	Mix_Music * sMusic = NULL;
	soundType theSoundType;

public:
	cSound();
	cSound(soundType sndType);
	~cSound();

	bool load(LPCSTR filename);
	//void setSoundType(soundType sndType);
	//soundType getSoundType();
	void play(int loop);  // Use a -1 so the music and sound will play on a loop
};
#endif