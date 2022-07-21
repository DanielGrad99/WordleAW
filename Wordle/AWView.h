#pragma once

#include "LFX2.h"

#include <ctime>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <tchar.h>

#include <unordered_map>

class AWView
{
public:

	AWView();

	~AWView();

	void LightUpKey(unsigned char c, PLFX_COLOR pcolour);

	void NewGame();
	void GameOver(bool won);

private:

	HINSTANCE mHLibrary;

	LFX2INITIALIZE mInitFunction = nullptr;
	LFX2RELEASE mReleaseFunction = nullptr;

	LFX2GETNUMDEVICES mGetNumDevicesFunction = nullptr;
	LFX2GETDEVDESC mGetDeviceDescriptionFunction = nullptr;
	LFX2GETNUMLIGHTS mGetNumLightsFunction = nullptr;
	LFX2GETLIGHTDESC mGetLightDescriptionFunction = nullptr;

	LFX2RESET mResetFunction = nullptr;
	LFX2UPDATE mUpdateFunction = nullptr;

	LFX2LIGHT mLightFunction = nullptr;
	LFX2SETLIGHTCOL mSetLightColFunction = nullptr;
	LFX2GETLIGHTCOL mGetLightColFunction = nullptr;

	LFX2GETVERSION mVersionFunction = nullptr;


	struct LightLoc {
		unsigned int deviceIndex;
		unsigned int lightIndex;
	};
	std::unordered_map<char, LightLoc> mLightIndex;

	void SetLightSafe(LightLoc loghtLoc, PLFX_COLOR pcolour);

public:

	// Colours

	LFX_COLOR WHITE = {
		0xff,
		0xff,
		0xff,
		0
	};

	LFX_COLOR RED = {
		0xff,
		0,
		0,
		0
	};

	LFX_COLOR GREEN = {
		0,
		0xff,
		0,
		0
	};

	LFX_COLOR YELLOW = {
		0xff,
		0xff,
		0,
		0
	};

	LFX_COLOR OFF = {
		0,
		0,
		0,
		0
	};
};

