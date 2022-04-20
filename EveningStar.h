#include "skse/GameData.h"
#include "skse/GameForms.h"
#include "skse/NiGeometry.h"
#include "skse/NiLight.h"
#include "skse/NiNodes.h"
#include "skse/NiObjects.h"
#include "skse/NiTypes.h"
#include "skse/PapyrusNativeFunctions.h"
#include <math.h>
//#include <shlobj.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>


#define PI 3.14159265358979323846

namespace EveningStar
{
	extern float * g_sunriseBegin;
	extern float * g_sunriseEnd;
	extern float * g_sunsetBegin;
	extern float * g_sunsetEnd;
	extern float * g_sunriseDark;
	extern float * g_sunsetDark;

	extern int g_moonPhase;
	extern char * g_moonPhaseTexture;

	void UpdateSunPos();
	void UpdateDirectionalLight();
	int UpdateCheckMoonPhase(Moon * moon);
	void UpdateSetMoonPhase(Moon * moon);
	void UpdateSetMoonColor(Moon * moon);
	float GetGameHourMod();
	void loadIniFile();
	void loadLatitudesFile();

	float GetSunriseBegin(StaticFunctionTag *base);
	float GetSunriseEnd(StaticFunctionTag *base);
	float GetSunsetBegin(StaticFunctionTag *base);
	float GetSunsetEnd(StaticFunctionTag *base);

	float GetDawnBegin(StaticFunctionTag *base);
	float GetDawnEnd(StaticFunctionTag *base);
	float GetDuskBegin(StaticFunctionTag *base);
	float GetDuskEnd(StaticFunctionTag *base);

	float GetPlayerLatitude(StaticFunctionTag *base);

	float GetMasserRiseTime(StaticFunctionTag *base);
	float GetMasserRiseCycleTime(StaticFunctionTag *base);
	float GetSecundaRiseTime(StaticFunctionTag *base);
	float GetSecundaRiseCycleTime(StaticFunctionTag *base);

	float GetMasserPositionX(StaticFunctionTag *base);
	float GetMasserPositionY(StaticFunctionTag *base);
	float GetMasserPositionZ(StaticFunctionTag *base);
	float GetSecundaPositionX(StaticFunctionTag *base);
	float GetSecundaPositionY(StaticFunctionTag *base);
	float GetSecundaPositionZ(StaticFunctionTag *base);

	bool RegisterFuncs(VMClassRegistry* registry);
}
