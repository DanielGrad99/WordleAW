#include "AWView.h"

AWView::AWView() :
	mHLibrary(LoadLibrary(_T(LFX_DLL_NAME)))
{
	if (!mHLibrary)
	{
		return;
	}

	mInitFunction = (LFX2INITIALIZE)GetProcAddress(mHLibrary, LFX_DLL_INITIALIZE);
	mReleaseFunction = (LFX2RELEASE)GetProcAddress(mHLibrary, LFX_DLL_RELEASE);

	mGetNumDevicesFunction = (LFX2GETNUMDEVICES)GetProcAddress(mHLibrary, LFX_DLL_GETNUMDEVICES);
	mGetDeviceDescriptionFunction = (LFX2GETDEVDESC)GetProcAddress(mHLibrary, LFX_DLL_GETDEVDESC);
	mGetNumLightsFunction = (LFX2GETNUMLIGHTS)GetProcAddress(mHLibrary, LFX_DLL_GETNUMLIGHTS);
	mGetLightDescriptionFunction = (LFX2GETLIGHTDESC)GetProcAddress(mHLibrary, LFX_DLL_GETLIGHTDESC);

	mResetFunction = (LFX2RESET)GetProcAddress(mHLibrary, LFX_DLL_RESET);
	mUpdateFunction = (LFX2UPDATE)GetProcAddress(mHLibrary, LFX_DLL_UPDATE);

	mLightFunction = (LFX2LIGHT)GetProcAddress(mHLibrary, LFX_DLL_LIGHT);
	mSetLightColFunction = (LFX2SETLIGHTCOL)GetProcAddress(mHLibrary, LFX_DLL_SETLIGHTCOL);
	mGetLightColFunction = (LFX2GETLIGHTCOL)GetProcAddress(mHLibrary, LFX_DLL_GETLIGHTCOL);

	mVersionFunction = (LFX2GETVERSION)GetProcAddress(mHLibrary, LFX_DLL_GETVERSION);

	mInitFunction();

	// Find the light index of each letter

	LFX_RESULT result;
	unsigned int descSize = 255;
	char* description = new char[descSize];

	unsigned int numDevices;
	mGetNumDevicesFunction(&numDevices);

	for (unsigned int deviceIndex = 0; deviceIndex < numDevices; ++deviceIndex)
	{
		unsigned int numLights;
		mGetNumLightsFunction(deviceIndex, &numLights);

		for (unsigned int lightIndex = 0; lightIndex < numLights; ++lightIndex)
		{
			result = mGetLightDescriptionFunction(1, lightIndex, description, descSize);
			if (result != LFX_SUCCESS)
			{
				continue;
			}

			if (description[0] >= 'A' && description[0] <= 'Z' && description[1] == '\0')
			{
				mLightIndex[description[0]] = { deviceIndex, lightIndex };
			}
		}
	}
}

AWView::~AWView()
{
	mReleaseFunction();
	mUpdateFunction();

	FreeLibrary(mHLibrary);
}

void AWView::LightUpKey(unsigned char c, PLFX_COLOR pcolour)
{
	SetLightSafe(mLightIndex[toupper(c)], pcolour);
}

void AWView::NewGame()
{
	mResetFunction();
	mUpdateFunction();
	Sleep(5);

	for (const auto& p : mLightIndex) {
		SetLightSafe(p.second, &WHITE);
	}
}

void AWView::GameOver(bool won)
{

	const auto& colour = won ? LFX_GREEN : LFX_RED;

	for (int i = 0; i < 3; ++i)
	{
		mLightFunction(LFX_DEVTYPE_KEYBOARD, colour);
		mUpdateFunction();
		Sleep(200);

		mLightFunction(LFX_DEVTYPE_KEYBOARD, LFX_OFF);
		mUpdateFunction();
		Sleep(100);
	}
}

void AWView::SetLightSafe(LightLoc lightLoc, PLFX_COLOR pcolour) {

	mSetLightColFunction(lightLoc.deviceIndex, lightLoc.lightIndex, pcolour);
	mUpdateFunction();
	Sleep(5);

	/*
	
	// Does not work because GetLightColor always fails

	LFX_COLOR colour;

	do {
		mSetLightColFunction(1, index, pcolour);
		mUpdateFunction();
		Sleep(1);
		std::cerr << mGetLightColFunction(1, index, &colour) << std::endl;
	} while (
		colour.red != pcolour->red ||
		colour.green != pcolour->green ||
		colour.blue != pcolour->blue ||
		colour.brightness != pcolour->brightness
	);
	*/
}
