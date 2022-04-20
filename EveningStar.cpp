#include "EveningStar.h"


namespace EveningStar
{
	float * g_fDaytimeColorExtension = reinterpret_cast<float *>(0x01B11704);
	float * g_fSunAlphaTransTime = reinterpret_cast<float *>(0x01B117D8);
	float * g_fSunXExtreme = reinterpret_cast<float *>(0x01B117E4);
	float * g_fSunYExtreme = reinterpret_cast<float *>(0x01B117F0);

	float * g_sunriseBegin = reinterpret_cast<float *>(0x01B1175C);
	float * g_sunriseEnd = reinterpret_cast<float *>(0x01B11760);
	float * g_sunsetBegin = reinterpret_cast<float *>(0x01B11764);
	float * g_sunsetEnd = reinterpret_cast<float *>(0x01B11768);
	float * g_sunriseDark = reinterpret_cast<float *>(0x01B1176C);
	float * g_sunsetDark = reinterpret_cast<float *>(0x01B11770);

	float * g_maxFloat = reinterpret_cast<float *>(0x012C52E8); // 3.402823e+38

	int g_masserPhase = 0;
	int g_secundaPhase = 0;

	// Used to set the alpha level during a solar eclipse
	float g_sunEclipseAlpha = 0;
	float g_masserEclipseAlpha = 0;
	float g_secundaEclipseAlpha = 0;
	int g_isMasserEclipse = 0;
	int g_isSecundaEclipse = 0;

	// used to set the texture for the current moon
	int g_moonPhase = -1;
	char * g_moonPhaseTexture;

	char * g_masserEclipse = "Data/Textures/Sky/EveningStar/Masser_eclipse.dds";
	char * g_secundaEclipse = "Data/Textures/Sky/EveningStar/Secunda_eclipse.dds";

	char * g_masserTextures[] = {
		"Data/Textures/Sky/Masser_full.dds",
		"Data/Textures/Sky/Masser_three_wan.dds",
		"Data/Textures/Sky/Masser_half_wan.dds",
		"Data/Textures/Sky/Masser_one_wan.dds",
		"Data/Textures/Sky/Masser_new.dds", //NULL,
		"Data/Textures/Sky/Masser_one_wax.dds",
		"Data/Textures/Sky/Masser_half_wax.dds",
		"Data/Textures/Sky/Masser_three_wax.dds"
	};

	char * g_secundaTextures[] = {
		"Data/Textures/Sky/Secunda_full.dds",
		"Data/Textures/Sky/Secunda_three_wan.dds",
		"Data/Textures/Sky/Secunda_half_wan.dds",
		"Data/Textures/Sky/Secunda_one_wan.dds",
		"Data/Textures/Sky/Secunda_new.dds", //NULL,
		"Data/Textures/Sky/Secunda_one_wax.dds",
		"Data/Textures/Sky/Secunda_half_wax.dds",
		"Data/Textures/Sky/Secunda_three_wax.dds"
	};

	char * g_masserTextures2[] = {
		"Data/Textures/Sky/EveningStar/Masser_full_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_full_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_full_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_new_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_new_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_new_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_one_wax_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_half_wax_2.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Masser_three_wax_2.dds"
	};

	char * g_secundaTextures2[] = {
		"Data/Textures/Sky/EveningStar/Secunda_full_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_full_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_full_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wan_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wan_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wan_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_new_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_new_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_new_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_one_wax_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_half_wax_2.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wax_0.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wax_1.dds",
		"Data/Textures/Sky/EveningStar/Secunda_three_wax_2.dds"
	};

	class BSSkyShaderProperty : public BSShaderProperty
	{
	public:
		virtual ~BSSkyShaderProperty();

		UInt32 unk44; // 44
		NiColorA emissiveColor; // 48
		NiSourceTexture* unk58; // 58
	};


	float g_fPlayerLatitude = -100.0;
	float g_fMasserRiseTime = -1.0;
	float g_fSecundaRiseTime = -1.0;
	float g_fHoursDaylight = 12.0f;
	float g_fGameHourNpcSchedule = 0.0f;


	char ini_path[] = "Data\\SKSE\\Plugins\\EveningStar.ini";
	char latitudes_path[] = "Data\\SKSE\\Plugins\\EveningStar_Latitudes.txt";

	int g_bEnablePrintDebug;
	float g_fDefaultLatitude;
	float g_fLatitudeMult;
	float g_fLatitudeOffset;
	float g_fAxialTilt;
	float g_fSolarNoonOffset;
	int g_bUpdateDaylightHours;
	int g_bUpdateSunPosition;
	int g_bUpdateNpcSchedules;
	int g_bUpdateStarsRotation;
	//int g_bEnableENBFix;
	int g_bUseExtendedMasserTextures;
	int g_bUseExtendedSecundaTextures;
	float g_fNpcScheduleSunrise;
	float g_fNpcScheduleSunset;
	float g_fNpcScheduleLinearRange;
	float g_fNpcScheduleLinearBase;
	float g_fNpcScheduleLinearMult;
	float g_fNpcScheduleLogBase;
	float g_fNpcScheduleLogMult;
	float g_fSunLightZOffset;
	float g_fMoonLightZOffset;
	float g_fMoonLightPercentFullMoon;
	float g_fMoonLightPercentWaningGibbous;
	float g_fMoonLightPercentLastQuarter;
	float g_fMoonLightPercentWaningCrescent;
	float g_fMoonLightPercentNewMoon;
	float g_fMoonLightPercentWaxingCrescent;
	float g_fMoonLightPercentFirstQuarter;
	float g_fMoonLightPercentWaxingGibbous;
	float g_fMasserRiseCycleTime;
	float g_fSecundaRiseCycleTime;
	float g_fMasserEclipseMoonFadeAngleStart;
	float g_fMasserEclipseMoonFadeAngleEnd;
	float g_fMasserEclipseSunFadeAngleStart;
	float g_fMasserEclipseSunFadeAngleEnd;
	float g_fSecundaEclipseMoonFadeAngleStart;
	float g_fSecundaEclipseMoonFadeAngleEnd;
	float g_fSecundaEclipseSunFadeAngleStart;
	float g_fSecundaEclipseSunFadeAngleEnd;

	float g_fMasserAngleFadeRedStart;
	float g_fMasserAngleFadeRedEnd;
	float g_fMasserAngleFadeGreenStart;
	float g_fMasserAngleFadeGreenEnd;
	float g_fMasserAngleFadeBlueStart;
	float g_fMasserAngleFadeBlueEnd;
	float g_fMasserAngleFadeAlphaStart;
	float g_fMasserAngleFadeAlphaEnd;
	float g_fSecundaAngleFadeRedStart;
	float g_fSecundaAngleFadeRedEnd;
	float g_fSecundaAngleFadeGreenStart;
	float g_fSecundaAngleFadeGreenEnd;
	float g_fSecundaAngleFadeBlueStart;
	float g_fSecundaAngleFadeBlueEnd;
	float g_fSecundaAngleFadeAlphaStart;
	float g_fSecundaAngleFadeAlphaEnd;

	std::vector<std::pair<std::string,float>> g_vLatitudeData;



	// Gets a reference from editor id
	// Note: only works for certain types of editor ids (such as worldspace)
	const UInt32 kGetFormFromEditorIdCall = 0x00451B60;

	void * GetFormFromEditorId(const char * name) {
		_asm
		{
			mov eax, name
			push eax
			call kGetFormFromEditorIdCall
			add esp, 4
		}
	}

	const UInt32 kGetPlayerMapPositionCall = 0x004F0AC0;

	// Returns the player position on the map
	// Set position to player position, it is also used as return variable
	void GetPlayerMapPosition(TESWorldSpace * worldspace, NiPoint3 &position) {
		_asm
		{
			mov edx, position
			mov ecx, worldspace
			push 0
			push edx
			call kGetPlayerMapPositionCall
		}
	}


	// Returns the GameHour global variable
	_declspec(noinline) float GetGameHour() {
		_asm
		{
			mov ecx, DS:[0x012E35DC]
			test ecx, ecx
			jz end

			mov edx, [ecx+0x10]
			fld [edx+0x20]
			retn
		end:
			fldz
			retn
		}
	}

	// Returns the GameDay global variable
	_declspec(noinline) float GetGameDay() {
		_asm
		{
			mov ecx, DS:[0x012E35DC]
			test ecx, ecx
			jz end

			mov edx, [ecx+0x0C]
			fld [edx+0x20]
			retn
		end:
			fldz
			retn
		}
	}

	// Returns the GameMonth global variable
	_declspec(noinline) float GetGameMonth() {
		_asm
		{
			mov ecx, DS:[0x012E35DC]
			test ecx, ecx
			jz end

			mov edx, [ecx+0x08]
			fld [edx+0x20]
			retn
		end:
			fldz
			retn
		}
	}

	// Returns the GameDaysPassed global variable
	_declspec(noinline) float GetGameDaysPassed() {
		_asm
		{
			mov ecx, DS:[0x012E35DC]
			test ecx, ecx
			jz end

			mov edx, [ecx+0x14]
			fld [edx+0x20]
			retn
		end:
			fldz
			retn
		}
	}

	// Get the time of sunrise
	float GetSunriseTime() {
		return (*g_sunriseBegin + *g_sunriseEnd - *g_fSunAlphaTransTime)/2;
	}

	// Get the time of sunset
	float GetSunsetTime() {
		return (*g_sunsetBegin + *g_sunsetEnd + *g_fSunAlphaTransTime)/2;
	}

	// Returns the sun NiNode
	NiNode * GetSunNiNode() {
		NiNode * sunNode = NULL;
		Sky * sky = GetSky();
		if (sky) {
			Sun * sun = sky->sun;
			if (sun) {
				sunNode = reinterpret_cast<NiNode*>(sun->m_refCount);
			}
		}
		return sunNode;
	}

	// Returns the sun NiDirectionalLight
	NiDirectionalLight * GetSunNiDirectionalLight() {
		NiDirectionalLight * light = NULL;
		Sky * sky = GetSky();
		if (sky) {
			Sun * sun = sky->sun;
			if (sun) {
				light = reinterpret_cast<NiDirectionalLight*>(sun->unk1C);
			}
		}
		return light;
	}

	// Returns Masser NiTriShape
	NiTriShape * GetMasserNiTriShape() {
		NiTriShape * masserShape = NULL;
		Sky * sky = GetSky();
		if (sky) {
			Moon * masser = sky->masser;
			if (masser) {
				masserShape = reinterpret_cast<NiTriShape*>(masser->unk10);
			}
		}
		return masserShape;
	}

	// Returns Secunda NiTriShape
	NiTriShape * GetSecundaNiTriShape() {
		NiTriShape * secundaShape = NULL;
		Sky * sky = GetSky();
		if (sky) {
			Moon * secunda = sky->secunda;
			if (secunda) {
				secundaShape = reinterpret_cast<NiTriShape*>(secunda->unk10);
			}
		}
		return secundaShape;
	}

	// Returns the stars NiNode
	NiNode * GetStarsNiNode() {
		NiNode * starsNode = NULL;
		Sky * sky = GetSky();
		if (sky) {
			Stars * stars = sky->stars;
			if (stars) {
				//starsNode = reinterpret_cast<NiNode*>(stars->m_refCount);
				starsNode = reinterpret_cast<NiNode*>(stars->unk08);
			}
		}
		return starsNode;
	}


	// Returns true if the object reference is in an interior
	bool IsInInterior(TESObjectREFR * reference) {
		if (reference) {
			TESObjectCELL * cell = reference->parentCell;
			if (cell) {
				UInt16 flags = cell->unk2C;
				return flags&1;
			}
		}
		return false;
	}

	// Get the base latitude from the world space
	float GetLatitudeForWorldSpace(TESWorldSpace ** worldSpaceOut) {
		*worldSpaceOut = NULL;
		if (*g_TES) {
			TESWorldSpace * worldSpace = reinterpret_cast<TESWorldSpace *>((*g_TES)->worldSpace);
			while (worldSpace) {
				*worldSpaceOut = worldSpace;
				std::vector<std::pair<std::string,float>>::iterator it;
				for (it = g_vLatitudeData.begin(); it < g_vLatitudeData.end(); it++) {
					//Console_Print("%s %f", (*it).first.c_str(), (*it).second);
					void * form = GetFormFromEditorId((*it).first.c_str());
					if (!form) continue;
					if (worldSpace == form) {
						//*worldSpaceOut = worldSpace;
						return (*it).second;
					}
				}
				// Check parent worldspace
				worldSpace = *reinterpret_cast<TESWorldSpace **>(&(worldSpace->unk0CC));
			}
		}
		//*worldSpaceOut = NULL;
		return g_fDefaultLatitude;
	}

	// Returns the player's current latitude
	float GetCurrentLatitude() {

		if (!(*g_TES)) return *g_maxFloat;
		TESWorldSpace * currentWorldSpace = reinterpret_cast<TESWorldSpace *>((*g_TES)->worldSpace);
		TESWorldSpace * worldSpace;

		//if (currentWorldSpace) {
		//	Console_Print(currentWorldSpace->fullName.name.data);
		//}

		float baseLatitude = GetLatitudeForWorldSpace(&worldSpace);
		float latitude;
		//Console_Print("worldSpace %x %x", worldSpace, currentWorldSpace);

		if (baseLatitude >= -90.0f && baseLatitude <= 90.0f) {

			PlayerCharacter * player = (*g_thePlayer);
			float ypos;
			//TESWorldSpace * currentWorldSpace;

			if (IsInInterior(player)) {
				//float mapX = *reinterpret_cast<float *>(&(player->pad238[90]));
				float mapY = *reinterpret_cast<float *>(&(player->pad238[91]));
				//if (mapX < *g_maxFloat && mapY < *g_maxFloat) {
				//Console_Print("mapY %f", ypos);
				if (mapY < *g_maxFloat) {
					ypos = mapY;
					//Console_Print("Interior mapY %f", ypos);
				} else {
					//ypos = 0.0f;
					//Console_Print("Interior 0.0f", ypos);
					return *g_maxFloat;
				}
				

			} else {
				if (worldSpace == currentWorldSpace || worldSpace == NULL) {
					ypos = player->pos.y;
					//Console_Print("PlayerY %f", ypos);
				} else {
					NiPoint3 position;
					position.x = player->pos.x;
					position.y = player->pos.y;
					position.z = player->pos.z;
					GetPlayerMapPosition(currentWorldSpace, position);
					ypos = position.y;
					//Console_Print("PlayerY %f, MapY %f", player->pos.y, ypos);
				}
			}
			latitude = baseLatitude + (ypos * g_fLatitudeMult) + g_fLatitudeOffset;
			if (latitude > 90.0f) latitude = 90.0f;
			if (latitude < -90.0f) latitude = -90.0f;

		} else {
			latitude = baseLatitude;
		}

		if (g_bEnablePrintDebug) {
			Console_Print("BaseLatitude %f, Latitude %f", baseLatitude, latitude);
		}

		return latitude;
	}


	// Convert degrees to radians
	float toRadians(float degrees) {
		return degrees * PI / 180;
	}

	// Convert radians to degrees
	float toDegrees(float radians) {
		return radians * 180 / PI;
	}

	// Multiplies a matrix by a vector
	void MatrixVectorMultiply(NiPoint3 * s, NiMatrix33 * m, NiPoint3 * v) {
		s->x = m->data[0][0] * v->x + m->data[0][1] * v->y + m->data[0][2] * v->z;
		s->y = m->data[1][0] * v->x + m->data[1][1] * v->y + m->data[1][2] * v->z;
		s->z = m->data[2][0] * v->x + m->data[2][1] * v->y + m->data[2][2] * v->z;
	}

/*
	float getfSunY(float degrees) {
		float angle = degrees;
		float y = 0;

		if (angle >= 45.0) {
			// use logarithmic fit
			y = log(angle / 90.0) / -0.0023772;
		} else {
			y = -2.16482639 * angle + 9.552473693 + 17099.08296 / angle;
		}
		return y;
	}
*/

	// Get the day number from game date
	int DayNumberFromDate(int day, int month) {
		int startDay = 0;
		switch(month) {
			case 0: //  Morning Star
				startDay = 11;
				break;
			case 1: // Sun's Dawn
				startDay = 42;
				break;
			case 2: // First Seed
				startDay = 71;
				break;
			case 3: // Rain's Hand
				startDay = 101;
				break;
			case 4: // Second Seed
				startDay = 131;
				break;
			case 5: // Midyear
				startDay = 162;
				break;
			case 6: // Sun's Height
				startDay = 192;
				break;
			case 7: // Last Seed
				startDay = 223;
				break;
			case 8: // Hearthfire
				startDay = 254;
				break;
			case 9: // Frostfall
				startDay = 284;
				break;
			case 10: // Sun's Dusk
				startDay = 315;
				break;
			case 11: // Evening Star
				startDay = 345;
				break;
		}
		int dayNumber = (startDay + day - 1);
		if (dayNumber > 365) dayNumber -= 365;
		return dayNumber;
	}


	float GetGameHourNpcSchedule() {
		float gameHour = GetGameHour();

		//Console_Print("GetGameHourNpcSchedule %f", gameHour);

		// Change current gameHour depending on sunrise time
		if (g_bUpdateNpcSchedules && g_fPlayerLatitude >= -90.0f && g_fPlayerLatitude <= 90.0f) {
			float gameHourMod;
			float daylightDiff = g_fHoursDaylight/2.0f - 6.0f;
			float influence = abs(daylightDiff);

			if (influence > g_fNpcScheduleLinearRange) {
				float influenceMod = (g_fNpcScheduleLinearBase + g_fNpcScheduleLinearRange) * g_fNpcScheduleLinearMult;
				influence -= g_fNpcScheduleLinearRange;

				influenceMod += log(g_fNpcScheduleLogBase + influence)*g_fNpcScheduleLogMult;
				influence = influenceMod;
			} else {
				influence = (g_fNpcScheduleLinearBase + influence) * g_fNpcScheduleLinearMult;
			}
			if (daylightDiff < 0) influence *= -1;


			float sunriseTimeMod = g_fNpcScheduleSunrise - influence;
			float sunsetTimeMod = g_fNpcScheduleSunset + influence;

			float start, end, t;
			if (gameHour < sunriseTimeMod) {
				start = 0.0f;
				end = g_fNpcScheduleSunrise;
				t = gameHour/sunriseTimeMod;
			} else if (gameHour < sunsetTimeMod) {
				start = g_fNpcScheduleSunrise;
				end = g_fNpcScheduleSunset;
				t = (gameHour - sunriseTimeMod)/(sunsetTimeMod - sunriseTimeMod);
			} else {
				start = g_fNpcScheduleSunset;
				end = 24.0f;
				t = (gameHour - sunsetTimeMod)/(end - sunsetTimeMod);
			}
			gameHourMod = (1 - t)*start + t*end;
			//Console_Print("gameHour %f, start %f, end %f", gameHour, start, end);

			if (g_bEnablePrintDebug) {
				Console_Print("gameHour %f, daylightDiff %f, influence %f, gameHourMod %f", gameHour, daylightDiff, influence, gameHourMod);
			}

			return gameHourMod;
		}

		return gameHour;
	}

	void CalculateDaylightHours(int dayNumber, float latitude, bool isEclipse = false) {

		float axis = g_fAxialTilt;
		float j = PI / (365 / 2);

		// p = axis*cos(j*day) in radians
		float p = axis * cos(j * dayNumber);
		float tan_p = tan(p * 2 * PI / 360);
		float tan_latitude = tan(latitude * 2 * PI / 360);
		// m = 1 - tan(Lat)tan(Axis × cos(j × Day)) = 1-tan(lat)*tan(p)
		float m = 1 - tan_latitude * tan_p;
		float raw_m = m;
		if (m < 0) m = 0;
		if (m > 2) m = 2;
		float b = (acos(1.0 - m)) / PI;
		float hoursDaylight = 24.0 * b;

		// hoursDaylight is the time for which the centre of the sun is above the horizon. Sunrise occurs when the centre of
		// the sun rises above the horizon; dawnDuration takes place BEFORE this.
		// Sunset occurs when the centre of the sun drops below the horizon; duskDuration occurs AFTER this.
		// True night is darkness from the end of dusk to the beginning of dawn.

		// twilight: DawnDuration = DuskDuration
		float h = 0.21255656; //combining civil and nautical twilight at 12 degrees; ignore astronomical twilight.
		float i = h / (cos(latitude * 2.0 * PI / 360));
		float n = raw_m + i;
		if (n < 0) n = 0.0;
		if (n > 2) n = 2.0;
		float k = acos(1.0 - n);
		float t = ((k / PI) - b) / 2.0;
		float hoursTwilight = t * 24.0;

		// Set minimum to fix bugs with 24 hour day/night
		if (hoursTwilight == 0) hoursTwilight = 0.001;

		//float night = 24 - (hoursDaylight + 2 * hoursTwilight);
		//if (night < 0) night = 0;
		//if (night > 24) night = 24;

		// Support for eclipses
		if (isEclipse) {
			hoursDaylight = 0.0;
			hoursTwilight = 0.001;
		} else {
			// Used to determine npc schedules
			g_fHoursDaylight = hoursDaylight;
		}

		// Calculate values for sunrise/sunset           
		float DayTime = 12.0 + g_fSolarNoonOffset;
		//float NightTime = 0.0;
		float DawnDuration = hoursTwilight;
		float DuskDuration = hoursTwilight;
		float SunriseTime = DayTime - hoursDaylight / 2.0;
		float SunsetTime = DayTime + hoursDaylight / 2.0;

		// Prevent values outside 0 to 24, may occur if fSolarNoonOffset is set
		if (SunriseTime < 0) {
			SunsetTime += -SunriseTime;
			SunriseTime = 0.0f;
		} else if (SunsetTime > 24) {
			SunriseTime += -(SunsetTime - 24.0f);
			SunsetTime = 24.0f;
		}

		*g_sunriseDark = (SunriseTime - DawnDuration); // Sky starts brightening (sun below horizon)
		*g_sunsetDark = (SunsetTime + DuskDuration); // Sky finishes darkening (sun below horizon)
		*g_sunriseBegin = (*g_sunriseDark + *g_fDaytimeColorExtension);
		*g_sunriseEnd = (SunriseTime + DawnDuration);
		*g_sunsetBegin = (SunsetTime - DuskDuration);
		*g_sunsetEnd = (*g_sunsetDark - *g_fDaytimeColorExtension);

		// Fix for sky brightness during near 24 hour daylight
		if (SunriseTime == DayTime && SunsetTime == DayTime) {
			float hoursTwilightMod = DayTime - hoursTwilight;
			*g_sunriseEnd = (SunriseTime + hoursTwilightMod);
			*g_sunsetBegin = (SunsetTime - hoursTwilightMod);
		}


		// Fix for bright sky during dusk if sunriseEnd > sunsetBegin
		float gameHour = GetGameHour();
		if (gameHour > 12.0 && *g_sunriseEnd > 12.0) {
			*g_sunriseEnd = 12.0;
		} else if (gameHour <= 12.0 && *g_sunsetBegin <= 12.0) {
			*g_sunsetBegin = 12.0;
		}

		if (g_bEnablePrintDebug) {
			Console_Print("Sunrise %f %f, Dawn %f %f", *g_sunriseBegin, *g_sunriseEnd, *g_sunriseDark, SunriseTime);
			Console_Print("Sunset %f %f, Dusk %f %f", *g_sunsetBegin, *g_sunsetEnd, SunsetTime, *g_sunsetDark);
		}
	}


	void CalculateStarsRotation(int dayNumber, float latitude) {

		NiNode * starsNode = GetStarsNiNode();
		if (!starsNode) return;

		float gameHour = GetGameHour();

		float rotx = -toRadians(90 - latitude);
		float rotz = -toRadians(360.0*gameHour/24.0) - toRadians(360.0*dayNumber/365 - 99.5);
		//Console_Print("Stars Rotation X %f, Z %f", rotx*180/PI, rotz*180/PI);

		// Create the XZ rotation matrix
		NiMatrix33 m;
		m.data[0][0] = cos(rotz);
		m.data[0][1] = -sin(rotz);
		m.data[0][2] = 0;
		m.data[1][0] = cos(rotx)*sin(rotz);
		m.data[1][1] = cos(rotx)*cos(rotz);
		m.data[1][2] = -sin(rotx);
		m.data[2][0] = sin(rotx)*sin(rotz);
		m.data[2][1] = cos(rotz)*sin(rotx);
		m.data[2][2] = cos(rotx);

		memcpy(&(starsNode->m_localTransform.rot), &m, sizeof(m));
		memcpy(&(starsNode->m_worldTransform.rot), &m, sizeof(m));

	}


	int GetMoonPhase(float moonRise) {
		float phaseTest = moonRise - 19.0 + 0.5; // 0.5 rounds value to nearest int (during static_cast)
		if (phaseTest < 0) phaseTest += 24.0;
		int moonPhase = static_cast<int>(phaseTest);
		//int moonPhase = static_cast<int>(phaseTest)/3;
		return moonPhase;
	}

	void CalculateMoonPosition() {

		Sky * sky = GetSky();
		Moon * masser;
		Moon * secunda;
		if (sky) {
			masser = sky->masser;
			secunda = sky->secunda;
		}
		if (!sky || !masser || !secunda) {
			return;
		}


		// Calculate the angle for Masser/Secunda
		// Note: Time units are in days, not hours
		float gameHour = GetGameHour();
		float daysPassed = GetGameDaysPassed();
		//float hoursPassed = daysPassed * 24.0;
		float masserCycleTime = g_fMasserRiseCycleTime;
		float secundaCycleTime = g_fSecundaRiseCycleTime;

		float masserTime = fmod((daysPassed - 19.0f/24.0f), masserCycleTime);
		float secundaTime = fmod((daysPassed - 19.0f/24.0f), secundaCycleTime);
		masserTime = (masserTime > 0.0) ? masserTime : (masserTime + masserCycleTime);
		secundaTime = (secundaTime > 0.0) ? secundaTime : (secundaTime + secundaCycleTime);

		float masserPercent = masserTime / masserCycleTime;
		float secundaPercent = secundaTime / secundaCycleTime;
		float masserAngle = masserPercent * 360.0;
		float secundaAngle = secundaPercent * 360.0;

		*reinterpret_cast<float *>(&(masser->unk7C[6])) = masserAngle;
		*reinterpret_cast<float *>(&(secunda->unk7C[6])) = secundaAngle;


		// Calculate the moon rise time, used to determine moon phase
		float masserRise = gameHour + (masserCycleTime - masserTime)*24.0;
		float secundaRise = gameHour + (secundaCycleTime - secundaTime)*24.0;
		if (masserRise > 24.0) masserRise -= 24.0;
		if (secundaRise > 24.0) secundaRise -= 24.0;

		g_fMasserRiseTime = masserRise;
		g_fSecundaRiseTime = secundaRise;


		// Use the previous moon rise time if the moon is above the horizon
		// Fixes the wrong moon phase issue when loading a saved game
		float masserRiseTest = (masserAngle > 180.0) ? masserRise : (masserRise - masserCycleTime*24.0);
		float secundaRiseTest = (secundaAngle > 180.0) ? secundaRise : (secundaRise - secundaCycleTime*24.0);
		if (masserRiseTest < 0.0) masserRiseTest += 24.0;
		if (secundaRiseTest < 0.0) secundaRiseTest += 24.0;

		g_masserPhase = GetMoonPhase(masserRiseTest);
		g_secundaPhase = GetMoonPhase(secundaRiseTest);


		if (g_bEnablePrintDebug) {
			Console_Print("Masser Angle %f, Secunda Angle %f", masserAngle, secundaAngle);
			Console_Print("Masser Rise %f %f, Secunda Rise %f %f", masserRise, masserRiseTest, secundaRise, secundaRiseTest);
			Console_Print("Masser Phase %d, Secunda Phase %d", g_masserPhase/3, g_secundaPhase/3);
		}
	}


	int UpdateCheckMoonPhase(Moon * moon) {

		Sky * sky = GetSky();
		Moon * masser;
		Moon * secunda;
		if (sky) {
			masser = sky->masser;
			secunda = sky->secunda;
		}
		if (!sky || !masser || !secunda) {
			return 0;
		}

		// Detect changes to the moon phase
		// moon->unk7C[5] is set to 2 when loading a saved game
		if (moon == masser) {
			static int currentMasserPhase = -1;
			float angle = *reinterpret_cast<float*>(&(masser->unk7C[6]));
			static int currentMasserEclipse = 0;
			if (g_isMasserEclipse != currentMasserEclipse) {
				masser->unk7C[5] = 2;
				currentMasserEclipse = g_isMasserEclipse;
			}
			if (masser->unk7C[5] == 2 || 
					(currentMasserPhase != g_masserPhase && angle > 180)) {
				currentMasserPhase = g_masserPhase;
				g_moonPhase = g_masserPhase;
				return 1;
			}

		} else if (moon == secunda) {
			static int currentSecundaPhase = -1;
			float angle = *reinterpret_cast<float*>(&(secunda->unk7C[6]));
			static int currentSecundaEclipse = 0;
			if (g_isSecundaEclipse != currentSecundaEclipse) {
				secunda->unk7C[5] = 2;
				currentSecundaEclipse = g_isSecundaEclipse;
			}
			if (secunda->unk7C[5] == 2 || 
					(currentSecundaPhase != g_secundaPhase && angle > 180)) {
				currentSecundaPhase = g_secundaPhase;
				g_moonPhase = g_secundaPhase;
				return 1;
			}
		}

		return 0;
	}

	void UpdateSetMoonPhase(Moon * moon) {
		Sky * sky = GetSky();
		Moon * masser;
		Moon * secunda;
		if (sky) {
			masser = sky->masser;
			secunda = sky->secunda;
		}
		if (!sky || !masser || !secunda) {
			g_moonPhaseTexture = NULL;
			return;
		}

		if (moon == masser) {
			//g_moonPhaseTexture = g_masserTextures[g_moonPhase];
			//g_moonPhaseTexture = NULL;
			if (g_isMasserEclipse) {
				g_moonPhaseTexture = g_masserEclipse;
			} else if (g_bUseExtendedMasserTextures) {
				g_moonPhaseTexture = g_masserTextures2[g_moonPhase];
			} else {
				g_moonPhaseTexture = g_masserTextures[g_moonPhase/3];
			}
		}  else if (moon == secunda) {
			if (g_isSecundaEclipse) {
				g_moonPhaseTexture = g_secundaEclipse;
			} else if (g_bUseExtendedSecundaTextures) {
				g_moonPhaseTexture = g_secundaTextures2[g_moonPhase];
			} else {
				g_moonPhaseTexture = g_secundaTextures[g_moonPhase/3];
			}
			//g_moonPhaseTexture = g_secundaTextures2[0];
			//g_moonPhaseTexture = g_secundaTextures2[g_moonPhase];
		} else {
			g_moonPhaseTexture = NULL;
		}
	}


	float GetMoonLightPercent(Moon * moon, float angleStart, float angleEnd) {
		float moonAlpha;

		float angleStart2 = 180.0 - angleStart;
		float angleEnd2 = 180.0 - angleEnd;

		float moonAngle = *reinterpret_cast<float *>(&(moon->unk7C[6]));
		if (moonAngle > 270.0) moonAngle -= 360.0;

		if (moonAngle < angleEnd) {
			moonAlpha = 0.0;
		} else if (moonAngle < angleStart) {
			moonAlpha = (moonAngle - angleEnd)/(angleStart - angleEnd);
		} else if (moonAngle < angleStart2) {
			moonAlpha = 1.0;
		} else if (moonAngle < angleEnd2) {
			moonAlpha = 1.0f - (moonAngle - angleStart2)/(angleEnd2 - angleStart2);
		} else {
			moonAlpha = 0.0;
		}
		return moonAlpha;
	}

	void UpdateSetMoonColor(Moon * moon) {
		Sky * sky = GetSky();
		Moon * masser;
		Moon * secunda;
		if (sky) {
			masser = sky->masser;
			secunda = sky->secunda;
		}
		if (!sky || !masser || !secunda) {
			return;
		}

		if (moon == masser) {
			NiTriShape * masserShape = reinterpret_cast<NiTriShape *>(masser->unk10);
			if (masserShape) {
				BSSkyShaderProperty * skyShaderProperty = reinterpret_cast<BSSkyShaderProperty *>(masserShape->m_spEffectState.m_pObject);
				if (skyShaderProperty) {
					float redPercent = GetMoonLightPercent(masser, g_fMasserAngleFadeRedStart, g_fMasserAngleFadeRedEnd);
					float greenPercent = GetMoonLightPercent(masser, g_fMasserAngleFadeGreenStart, g_fMasserAngleFadeGreenEnd);
					float bluePercent = GetMoonLightPercent(masser, g_fMasserAngleFadeBlueStart, g_fMasserAngleFadeBlueEnd);
					float alphaPercent = GetMoonLightPercent(masser, g_fMasserAngleFadeAlphaStart, g_fMasserAngleFadeAlphaEnd);

					skyShaderProperty->emissiveColor.r *= redPercent;
					skyShaderProperty->emissiveColor.g *= greenPercent;
					skyShaderProperty->emissiveColor.b *= bluePercent;
					skyShaderProperty->emissiveColor.a = alphaPercent*g_masserEclipseAlpha;
				}
			}
		}  else if (moon == secunda) {
			NiTriShape * secundaShape = reinterpret_cast<NiTriShape *>(secunda->unk10);
			if (secundaShape) {
				BSSkyShaderProperty * skyShaderProperty = reinterpret_cast<BSSkyShaderProperty *>(secundaShape->m_spEffectState.m_pObject);
				if (skyShaderProperty) {
					float redPercent = GetMoonLightPercent(secunda, g_fSecundaAngleFadeRedStart, g_fSecundaAngleFadeRedEnd);
					float greenPercent = GetMoonLightPercent(secunda, g_fSecundaAngleFadeGreenStart, g_fSecundaAngleFadeGreenEnd);
					float bluePercent = GetMoonLightPercent(secunda, g_fSecundaAngleFadeBlueStart, g_fSecundaAngleFadeBlueEnd);
					float alphaPercent = GetMoonLightPercent(secunda, g_fSecundaAngleFadeAlphaStart, g_fSecundaAngleFadeAlphaEnd);

					skyShaderProperty->emissiveColor.r *= redPercent;
					skyShaderProperty->emissiveColor.g *= greenPercent;
					skyShaderProperty->emissiveColor.b *= bluePercent;
					skyShaderProperty->emissiveColor.a = alphaPercent*g_secundaEclipseAlpha;
				}
			}
		}
	}


	void TestEclipse() {

		//g_masserEclipseAlpha = 1.0f;
		//g_secundaEclipseAlpha = 1.0f;
		//g_sunEclipseAlpha = 1.0f;
		//return;

		PlayerCharacter * player = (*g_thePlayer);

		Sky * sky = GetSky();
		NiNode * sunNode = NULL;
		NiTriShape * sunShape = NULL;
		NiTriShape * masserShape = GetMasserNiTriShape();
		NiTriShape * secundaShape = GetSecundaNiTriShape();
		if (sky) {
			Sun * sun = sky->sun;
			if (sun) {
				sunNode = reinterpret_cast<NiNode *>(sun->m_refCount);
				sunShape = reinterpret_cast<NiTriShape *>(sun->unk10);
			}
		}
		if (!sky || !sunNode || !sunShape || !masserShape || !secundaShape) {
			return;
		}
		BSSkyShaderProperty * skyShaderProperty = reinterpret_cast<BSSkyShaderProperty*>(sunShape->m_spEffectState.m_pObject);
		if (!skyShaderProperty) {
			return;
		}

		float sunMasserAlpha, sunSecundaAlpha;
		float masserAlpha, secundaAlpha;

		NiPoint3 sunPos = sunNode->m_localTransform.pos;
		float sunX, sunY, sunZ;
		sunX = sunNode->m_localTransform.pos.x;
		sunY = sunNode->m_localTransform.pos.y;
		sunZ = sunNode->m_localTransform.pos.z;
		//Console_Print("Sun Position %f %f %f", sunX, sunY, sunZ);

		float sunRadial, sunZenith, sunAzimuth;
		sunRadial = sqrt(sunX*sunX+sunY*sunY+sunZ*sunZ);
		sunZenith = -acos(sunZ/sunRadial);
		sunAzimuth = atan2(sunY, sunX);
		//Console_Print("Sun Spherical %f %f %f", sunRadial, sunZenith*180/PI, sunAzimuth*180/PI);


		NiPoint3 masserPos;
		MatrixVectorMultiply(&masserPos, &(masserShape->m_parent->m_worldTransform.rot), &(masserShape->m_localTransform.pos));
		float masserX, masserY, masserZ;
		masserX = masserPos.x;
		masserY = masserPos.y;
		masserZ = masserPos.z;
		//Console_Print("Masser Position %f %f %f", masserX, masserY, masserZ);

		float masserRadial, masserZenith, masserAzimuth; 
		masserRadial = sqrt(masserX*masserX+masserY*masserY+masserZ*masserZ);
		masserZenith = -acos(masserZ/masserRadial);
		masserAzimuth = atan2(masserY, masserX);
		//Console_Print("Masser Spherical %f %f %f", masserRadial, masserZenith*180/PI, masserAzimuth*180/PI);

		// Use dot product to compute angle between sun and moon
		float sunMasserAngle = acos(cos(sunZenith)*cos(masserZenith)+sin(sunZenith)*sin(masserZenith)*cos(sunAzimuth-masserAzimuth));
		//Console_Print("Sun Masser Angle %f", sunMasserAngle*180/PI);

		sunMasserAngle *= 180.0f/PI;

		// ToDo: figure out better values for sun light level during eclipse transition
		if (sunMasserAngle < g_fMasserEclipseSunFadeAngleEnd) {
			sunMasserAlpha = 0.0f;
			masserAlpha = 1.0f;
		} else if (sunMasserAngle < g_fMasserEclipseSunFadeAngleStart) {
			sunMasserAlpha = (sunMasserAngle - g_fMasserEclipseSunFadeAngleEnd)/(g_fMasserEclipseSunFadeAngleStart - g_fMasserEclipseSunFadeAngleEnd);
			masserAlpha = 0.0f;
		} else {
			sunMasserAlpha = 1.0f;
			if (sunMasserAngle < g_fMasserEclipseMoonFadeAngleEnd) {
				masserAlpha = 0.0f;
			} else if (sunMasserAngle < g_fMasserEclipseMoonFadeAngleStart) {
				masserAlpha = (sunMasserAngle - g_fMasserEclipseMoonFadeAngleEnd)/(g_fMasserEclipseMoonFadeAngleStart - g_fMasserEclipseMoonFadeAngleEnd);
			} else {
				masserAlpha = 1.0f;
			}
		}
		g_isMasserEclipse = (sunMasserAngle < g_fMasserEclipseSunFadeAngleEnd);

		g_masserEclipseAlpha = masserAlpha;
		//Console_Print("Sun Masser Alpha %f, Masser Alpha %f", sunMasserAlpha, masserAlpha);


		NiPoint3 secundaPos;
		MatrixVectorMultiply(&secundaPos, &(secundaShape->m_parent->m_worldTransform.rot), &(secundaShape->m_localTransform.pos));
		float secundaX, secundaY, secundaZ;
		secundaX = secundaPos.x;
		secundaY = secundaPos.y;
		secundaZ = secundaPos.z;
		//Console_Print("Secunda Position %f %f %f", secundaX, secundaY, secundaZ);

		float secundaRadial, secundaZenith, secundaAzimuth; 
		secundaRadial = sqrt(secundaX*secundaX+secundaY*secundaY+secundaZ*secundaZ);
		secundaZenith = -acos(secundaZ/secundaRadial);
		secundaAzimuth = atan2(secundaY, secundaX);
		//Console_Print("Secunda Spherical %f %f %f", secundaRadial, secundaZenith*180/PI, secundaAzimuth*180/PI);

		// Use dot product to compute angle between sun and moon
		float sunSecundaAngle = acos(cos(sunZenith)*cos(secundaZenith)+sin(sunZenith)*sin(secundaZenith)*cos(sunAzimuth-secundaAzimuth));
		//Console_Print("Sun Secunda Angle %f", sunSecundaAngle*180/PI);

		sunSecundaAngle *= 180.0f/PI;

		// ToDo: figure out better values for sun light level during eclipse transition
		// Moon should be invisible until sun is gone?
		if (sunSecundaAngle < g_fSecundaEclipseSunFadeAngleEnd) {
			sunSecundaAlpha = 0.0f;
			secundaAlpha = 1.0f;
		} else if (sunSecundaAngle < g_fSecundaEclipseSunFadeAngleStart) {
			sunSecundaAlpha = (sunSecundaAngle - g_fSecundaEclipseSunFadeAngleEnd)/(g_fSecundaEclipseSunFadeAngleStart - g_fSecundaEclipseSunFadeAngleEnd);
			secundaAlpha = 0.0f;
		} else {
			sunSecundaAlpha = 1.0f;
			if (sunSecundaAngle < g_fSecundaEclipseMoonFadeAngleEnd) {
				secundaAlpha = 0.0f;
			} else if (sunSecundaAngle < g_fSecundaEclipseMoonFadeAngleStart) {
				secundaAlpha = (sunSecundaAngle - g_fSecundaEclipseMoonFadeAngleEnd)/(g_fSecundaEclipseMoonFadeAngleStart - g_fSecundaEclipseMoonFadeAngleEnd);
			} else {
				secundaAlpha = 1.0f;
			}
		}
		g_isSecundaEclipse = (sunSecundaAngle < g_fSecundaEclipseSunFadeAngleEnd);



		g_secundaEclipseAlpha = secundaAlpha;
		//Console_Print("Sun Secunda Alpha %f, Secunda Alpha %f", sunSecundaAlpha, secundaAlpha);

		//NiPoint3 pos = sunPos - secundaPos;
		//x -= secundaPos.x;
		//y -= secundaPos.y;
		//z -= secundaPos.z;
		//d = sqrt(x*x+y*y+z*z);
		//float d = sqrt(pos.x*pos.x+pos.y*pos.y+pos.z*pos.z);
		//Console_Print("SunMoon distance %f", d);


		//x = sunNode->m_worldTransform.pos.x;
		//y = sunNode->m_worldTransform.pos.y;
		//z = sunNode->m_worldTransform.pos.z;
		//Console_Print("SunWorldPos %f %f %f", x, y, z);

		//x = sunNode->m_localTransform.pos.x + player->pos.x;
		//y = sunNode->m_localTransform.pos.y + player->pos.y;
		//z = sunNode->m_localTransform.pos.z + player->pos.z;
		//Console_Print("SunPlayerPos %f %f %f", x, y, z);

		//g_sunEclipseAlpha = sunMasserAlpha*sunSecundaAlpha;
		//skyShaderProperty->emissiveColor.a *= g_sunEclipseAlpha;
		// TestEclipse
		g_sunEclipseAlpha = 1.0f;
		skyShaderProperty->emissiveColor.r = 0.1f;
		skyShaderProperty->emissiveColor.g = 0.1f;
		skyShaderProperty->emissiveColor.b = 0.1f;
		skyShaderProperty->emissiveColor.a = 1.0f;

	}


	void CalculateSunPositionVanilla() {
		NiNode * sunNode = GetSunNiNode();
		if (!sunNode) return;

		float gameHour = GetGameHour();
		float fSunX = *g_fSunXExtreme;
		float fSunY = *g_fSunYExtreme;

		// Times when the sun is on the horizon
		// By default, Skyrim moves the sun along a curve that passes through these points
		// sunUp - x: 400, y: 40, z: 0
		// midDay - x: 0, y: 40, z: 400
		// sunDown - x: -400, y: 40, z: 0
		float sunriseTime = GetSunriseTime();
		float sunsetTime = GetSunsetTime();

		//Console_Print("GameHour %f, sunriseTime %f, sunsetTime %f", gameHour, sunriseTime, sunsetTime);

		// Calculate position
		float percent;
		if (gameHour >= sunriseTime && gameHour < sunsetTime) {
			percent = 1.0f - ((gameHour-sunriseTime)/(sunsetTime-sunriseTime))*2.0f;
		} else if (gameHour >= sunsetTime) {
			percent = ((gameHour-sunsetTime)/(24.0f-(sunsetTime-sunriseTime)))*2.0f - 1.0f;
		} else {//if (gameHour < sunriseTime) {
			percent = ((gameHour+24.0f-sunsetTime)/(24.0f-(sunsetTime-sunriseTime)))*2.0f - 1.0f;
		}
		//Console_Print("SunPos percent %f", percent);

		float x = fSunX * percent;
		float y = fSunY;
		float z = abs(fSunX) - abs(x);

		//Console_Print("SunPos %f %f %f", x, y, z);

		// Update position of the sun node
		sunNode->m_localTransform.pos.x = x;
		sunNode->m_localTransform.pos.y = y;
		sunNode->m_localTransform.pos.z = z;
	}

	_declspec(noinline) void FixENBSun(float y) {

		typedef BOOL (CALLBACK * LPFNDLLFUNC1)(DWORD, void*);
		static LPFNDLLFUNC1 DirtyHack = NULL;

		if (DirtyHack) {
			Console_Print("Run");
			try {
				DirtyHack(1, (void*)&y);
			} catch (int e) {
				Console_Print("error %x", e);
			}
			return;
		}

		//Console_Print("Load - Start");
		char filename[MAX_PATH];
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		char* pch = strrchr(filename, '\\') + 1;
		strcpy(pch, "d3d9.dll");

		HINSTANCE hDLL = LoadLibrary(filename);
		if (hDLL != NULL) {
			DirtyHack = (LPFNDLLFUNC1)GetProcAddress(hDLL, "DirtyHack");
			if (!DirtyHack) FreeLibrary(hDLL);
		}
		//Console_Print("Load - Done");
	}

	void CalculateSunPosition(int dayNumber, float latitude) {
		NiNode * sunNode = GetSunNiNode();
		if (!sunNode) return;

		float gameHour = GetGameHour();

		float solarZenith = 0.0f;
		float solarAzimuth = 0.0f;
		float axis = g_fAxialTilt;

		float JanDayNumber = dayNumber - 11.0f;
		if (JanDayNumber > 365.0f) JanDayNumber -= 365.0f;
		if (JanDayNumber < 1.0f) JanDayNumber += 365.0f;

		latitude = toRadians(latitude);
		float sinLatitude = sin(latitude);
		float cosLatitude = cos(latitude);

		// Calculate declination
		float declination = -toRadians(axis) * cos(toRadians((360.0f/365.0f) * (JanDayNumber + 10.0f)));
		float sinDeclination = sin(declination);
		float cosDeclination = cos(declination);

		// Calculate hour angle
		float hourAngle = toRadians(15.0f*(gameHour-12.0f));
		float cosHourAngle = cos(hourAngle);

		// Calculate solar zenith
		solarZenith = acos(sinLatitude*sinDeclination + cosLatitude*cosDeclination*cosHourAngle);
		float sinSolarZenith = sin(solarZenith);
		float cosSolarZenith = cos(solarZenith);

		// Calculate solar azimuth
		solarAzimuth = acos((sinDeclination*cosLatitude - cosHourAngle*cosDeclination*sinLatitude)/sinSolarZenith);
		if (hourAngle > 0.0f) solarAzimuth = -solarAzimuth;
		solarAzimuth = -solarAzimuth + PI/2; // Convert to Skyrim coordinate system
		float sinSolarAzimuth = sin(solarAzimuth);
		float cosSolarAzimuth = cos(solarAzimuth);

		// Convert to Cartesian coordinates
		float r = *g_fSunXExtreme;
		float x = r * sinSolarZenith * cosSolarAzimuth;
		float y = r * sinSolarZenith * sinSolarAzimuth;
		float z = r * cosSolarZenith;

		if (g_bEnablePrintDebug) {
			Console_Print("Declination %f, HourAngle %f, Azimuth %f, Zenith %f", toDegrees(declination), toDegrees(hourAngle), toDegrees(solarAzimuth), toDegrees(solarZenith));
			//Console_Print("SunPos x %f, y %f, z %f", x, y, z);
		}

		// Update position of the sun node
		sunNode->m_localTransform.pos.x = x;
		sunNode->m_localTransform.pos.y = y;
		sunNode->m_localTransform.pos.z = z;
/*
		// TestEclipse
		sunNode->m_localTransform.pos.x = 10*x;
		sunNode->m_localTransform.pos.y = 10*y;
		sunNode->m_localTransform.pos.z = 10*z;

		// Sun glare billboard node
		NiNode * sunBillboardNode = NULL; // NiBillboardNode
		Sky * sky = GetSky();
		if (sky) {
			Sun * sun = sky->sun;
			if (sun) {
				sunBillboardNode = reinterpret_cast<NiNode *>(sun->unk0C);
				sunBillboardNode->m_localTransform.scale = 0.0f;
			}
			Clouds * clouds = sky->clouds;
			if (clouds) {
				NiNode * cloudsNode = reinterpret_cast<NiNode *>(clouds->m_refCount);
				cloudsNode->m_localTransform.scale = 0.0f;
			}
		}
*/
		FixENBSun(y);
	}

	void UpdateDirectionalLight() {

		g_fGameHourNpcSchedule = GetGameHourNpcSchedule();

		// Update latitude & sunrise/sunset times for interiors here
		PlayerCharacter * player = (*g_thePlayer);
		static TESObjectCELL * currentCell = 0;
		if (IsInInterior(player)) {
			if (currentCell != player->parentCell) {
				// Check the player map worldspace to make sure player is properly loaded
				TESWorldSpace * worldSpace = reinterpret_cast<TESWorldSpace *>(player->pad238[89]); // 0x39C is mapWorldspace
				//Console_Print("player worldSpace %x, player parentCell = %x", worldSpace, player->parentCell);
				if (worldSpace) {
					g_fPlayerLatitude = GetCurrentLatitude();
					float latitude = g_fPlayerLatitude;
					if (latitude == *g_maxFloat) return;

					float gameDay = GetGameDay();
					float gameMonth = GetGameMonth();
					int dayNumber = DayNumberFromDate(gameDay, gameMonth);

					if (latitude >= -90.0f && latitude <= 90.0f) {
						if (g_bUpdateDaylightHours) {
							CalculateDaylightHours(dayNumber, latitude);
						}
					} else {
						g_fPlayerLatitude = -100.0f;
					}
					currentCell = player->parentCell;
					//Console_Print("currentCell = %x", currentCell);
				}
			}
		} else {
			if (currentCell) {
				//Console_Print("currentCell = 0");
				currentCell = 0;
			}
		}

		NiDirectionalLight * light = GetSunNiDirectionalLight();
		if (!light) return;

		float gameHour = GetGameHour();
		//float sunriseTime = GetSunriseTime();
		//float sunsetTime = GetSunsetTime();
		//float midDawnTwilight = (*g_sunriseDark + sunriseTime)/2;
		//float midDuskTwilight = (sunsetTime + *g_sunsetDark)/2;
		float x,y,z;

		float sunriseTime, sunsetTime, midDawnTwilight, midDuskTwilight;
		//if (g_bEnableENBFix) {
		//	sunriseTime = *g_sunriseEnd;
		//	sunsetTime = *g_sunsetBegin;
		//	midDawnTwilight = GetSunriseTime();
		//	midDuskTwilight = GetSunsetTime();
		//} else {
		sunriseTime = GetSunriseTime();
		sunsetTime = GetSunsetTime();
		midDawnTwilight = (*g_sunriseDark + sunriseTime)/2;
		midDuskTwilight = (sunsetTime + *g_sunsetDark)/2;
		//}


		// Light Direction

		// Night
		if (gameHour < midDawnTwilight || gameHour > midDuskTwilight) {
			// Update light using the Masser moon
			NiTriShape * masserShape = GetMasserNiTriShape();
			//PlayerCharacter * player = (*g_thePlayer);
			if (masserShape) {

				NiPoint3 moonPos;
				MatrixVectorMultiply(&moonPos, &(masserShape->m_parent->m_worldTransform.rot), &(masserShape->m_localTransform.pos));
				x = moonPos.x;
				y = moonPos.y;
				z = moonPos.z;


				// Position only uses world transform
				//light->m_worldTransform.pos.x = x;
				//light->m_worldTransform.pos.y = y;
				//light->m_worldTransform.pos.z = z;

				z += g_fMoonLightZOffset;


				// Set the directional light direction
				// Note: Just sets the x/y/z values, is not a valid rotation matrix
				NiMatrix33 * m = &(light->m_localTransform.rot);
				//Console_Print("m %f, %f, %f, %f, %f, %f, %f, %f, %f", m->data[0][0], m->data[0][1], m->data[0][2],
				//				m->data[1][0], m->data[1][1], m->data[1][2], m->data[2][0], m->data[2][1], m->data[2][2]);

				float max = sqrt(x*x + y*y + z*z);
				m->data[0][0] = -x/max;
				m->data[0][1] = 0;
				m->data[0][2] = 0;
				m->data[1][0] = -y/max;
				m->data[1][1] = 1;
				m->data[1][2] = 0;
				m->data[2][0] = -z/max;
				m->data[2][1] = 0;
				m->data[2][2] = 1;

				if (g_bEnablePrintDebug) {
					Console_Print("Masser position %f, %f, %f direction %f, %f, %f", x, y, z, -x/max, -y/max, -z/max);
				}
			}

		// Day
		} else {
			// Update light using the sun node
			NiNode * sunNode = GetSunNiNode();
			if (sunNode) {

				x = sunNode->m_localTransform.pos.x;
				y = sunNode->m_localTransform.pos.y;
				z = sunNode->m_localTransform.pos.z;

				// Position only uses world transform
				//light->m_worldTransform.pos.x = x;
				//light->m_worldTransform.pos.y = y;
				//light->m_worldTransform.pos.z = z;

				z += g_fSunLightZOffset;


				// Set the directional light direction
				// Note: Just sets the x/y/z values, is not a valid rotation matrix
				NiMatrix33 * m = &(light->m_localTransform.rot);
				//Console_Print("m %f, %f, %f, %f, %f, %f, %f, %f, %f", m->data[0][0], m->data[0][1], m->data[0][2],
				//				m->data[1][0], m->data[1][1], m->data[1][2], m->data[2][0], m->data[2][1], m->data[2][2]);

				float max = sqrt(x*x + y*y + z*z);
				m->data[0][0] = -x/max;
				m->data[0][1] = 0;
				m->data[0][2] = 0;
				m->data[1][0] = -y/max;
				m->data[1][1] = 1;
				m->data[1][2] = 0;
				m->data[2][0] = -z/max;
				m->data[2][1] = 0;
				m->data[2][2] = 1;

				if (g_bEnablePrintDebug) {
					Console_Print("Sun position %f, %f, %f direction %f, %f, %f", x, y, z, -x/max, -y/max, -z/max);
				}
			}
		}


		// Light percent calculation
		// Sets the light percent to 0 in the middle of twilight before 
		// switching light source between sun and moon (Masser)
		float lightPercent = 1.0f;
		NiColor * color = reinterpret_cast<NiColor *>(&(light->unkB4));
		NiColorA * colorA = reinterpret_cast<NiColorA *>(&(light->unkC0));

		// Night
		if (gameHour < midDawnTwilight || gameHour > midDuskTwilight) {
			// Twilight percent calculation
			if (gameHour > *g_sunriseDark && gameHour < sunriseTime) {
				lightPercent = 1.0f - (gameHour - *g_sunriseDark)/(midDawnTwilight - *g_sunriseDark);
			} else if (gameHour > sunsetTime && gameHour < *g_sunsetDark) {
				lightPercent = (gameHour - midDuskTwilight)/(*g_sunsetDark - midDuskTwilight);
			} else {
				lightPercent = 1.0f;
			}

			// Moon fade percent
			Sky * sky = GetSky();
			Moon * masser;
			if (sky) {
				masser = sky->masser;
			}
			if (!sky || !masser) {
				return;
			}
			float moonFadePercent = GetMoonLightPercent(masser, g_fMasserAngleFadeAlphaStart, g_fMasserAngleFadeAlphaEnd);

			// Moon phase light calculation
			float moonPhasePercent;
			UInt32 moonPhase = *reinterpret_cast<UInt32 *>(0x01B115F4);
			static UInt32 currentMoonPhase = 0;
			static int savedDaysPassed = -1;

			int daysPassed = static_cast<int>(GetGameDaysPassed());
			if (gameHour < 12) daysPassed -= 1;
			if (moonPhase != currentMoonPhase && daysPassed != savedDaysPassed) {
				currentMoonPhase = moonPhase;
				savedDaysPassed = daysPassed;
			}

			if (currentMoonPhase == 0) {
				moonPhasePercent = g_fMoonLightPercentFullMoon;
			} else if (currentMoonPhase == 1) {
				moonPhasePercent = g_fMoonLightPercentWaningGibbous;
			} else if (currentMoonPhase == 2) {
				moonPhasePercent = g_fMoonLightPercentLastQuarter;
			} else if (currentMoonPhase == 3) {
				moonPhasePercent = g_fMoonLightPercentWaningCrescent;
			} else if (currentMoonPhase == 4) {
				moonPhasePercent = g_fMoonLightPercentNewMoon;
			} else if (currentMoonPhase == 5) {
				moonPhasePercent = g_fMoonLightPercentWaxingCrescent;
			} else if (currentMoonPhase == 6) {
				moonPhasePercent = g_fMoonLightPercentFirstQuarter;
			} else if (currentMoonPhase == 7) {
				moonPhasePercent = g_fMoonLightPercentWaxingGibbous;
			} else {
				moonPhasePercent = 0;
			}

			float moonLightPercent = lightPercent * moonFadePercent * moonPhasePercent;
			if (g_bEnablePrintDebug) {
				Console_Print("Masser light percent %f %f %f : %f", lightPercent, moonFadePercent, moonPhasePercent, moonLightPercent);
			}

			color->r *= moonLightPercent;
			color->g *= moonLightPercent;
			color->b *= moonLightPercent;
			colorA->r *= moonLightPercent;
			colorA->g *= moonLightPercent;
			colorA->b *= moonLightPercent;

		// Day
		} else {

			if (gameHour > *g_sunriseDark && gameHour < sunriseTime) {
				lightPercent = (gameHour - midDawnTwilight)/(sunriseTime - midDawnTwilight);
			} else if (gameHour > sunsetTime && gameHour < *g_sunsetDark) {
				lightPercent = 1.0f - (gameHour - sunsetTime)/(midDuskTwilight - sunsetTime);
			} else {
				lightPercent = 1.0f;
			}

			if (g_bEnablePrintDebug) {
				Console_Print("Sun light percent %f", lightPercent);
			}

			color->r *= lightPercent;
			color->g *= lightPercent;
			color->b *= lightPercent;
			colorA->r *= lightPercent;
			colorA->g *= lightPercent;
			colorA->b *= lightPercent;
		}

		color->r *= g_sunEclipseAlpha;
		color->g *= g_sunEclipseAlpha;
		color->b *= g_sunEclipseAlpha;
		colorA->r *= g_sunEclipseAlpha;
		colorA->g *= g_sunEclipseAlpha;
		colorA->b *= g_sunEclipseAlpha;
	}


	// Replaces the game code that updates the sun position
	void UpdateSunPos() {

		float gameDay = GetGameDay();
		float gameMonth = GetGameMonth();
		int dayNumber = DayNumberFromDate(gameDay, gameMonth);

		//PlayerCharacter * player = (*g_thePlayer);
		//TESWorldSpace * worldSpace = reinterpret_cast<TESWorldSpace *>(player->pad238[89]); // 0x39C is mapWorldspace
		//Console_Print("player worldSpace2 %x, player parentCell = %x", worldSpace, player->parentCell);

		g_fPlayerLatitude = GetCurrentLatitude();
		float latitude = g_fPlayerLatitude;

		if (latitude >= -90.0f && latitude <= 90.0f) {
			if (g_bUpdateDaylightHours) {
				CalculateDaylightHours(dayNumber, latitude);
			}

			float gameHour = GetGameHour();
			//int fixENB = (g_bEnableENBFix && (gameHour < GetSunriseTime() || gameHour > GetSunsetTime()));
			if (g_bUpdateSunPosition == 0) {// || fixENB) {
				CalculateSunPositionVanilla();
			} else {
				CalculateSunPosition(dayNumber, latitude);
			}

			// If solar eclipse, recalculate to avoid bug with CalculateSunPositionVanilla()
			if (g_bUpdateDaylightHours) {
				if (g_isMasserEclipse || g_isSecundaEclipse) {
					CalculateDaylightHours(dayNumber, latitude, true);
				}
			}

			if (g_bUpdateStarsRotation) {
				CalculateStarsRotation(dayNumber, latitude);
			}
			CalculateMoonPosition();
			TestEclipse();

		} else {
			g_fPlayerLatitude = -100.0f;
			CalculateSunPositionVanilla();
		}
	}


	float GetGameHourMod() {
		return g_fGameHourNpcSchedule;
	}


	// Load ini file
	void loadIniFile() {
		// Load ini settings
		char filename[MAX_PATH];
		char * pch;
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		pch = strrchr(filename, '\\') + 1;
		strcpy(pch, ini_path);


		char resultString[255];

		g_bEnablePrintDebug = GetPrivateProfileIntA("Main", "bEnablePrintDebug", 0, filename);
		g_bUpdateDaylightHours = GetPrivateProfileIntA("Main", "bUpdateDaylightHours", 1, filename);
		g_bUpdateSunPosition = GetPrivateProfileIntA("Main", "bUpdateSunPosition", 1, filename);
		g_bUpdateNpcSchedules = GetPrivateProfileIntA("Main", "bUpdateNpcSchedules", 1, filename);
		g_bUpdateStarsRotation = GetPrivateProfileIntA("Main", "bUpdateStarsRotation", 1, filename);
		//g_bEnableENBFix = GetPrivateProfileIntA("Main", "bEnableENBFix", 1, filename);
		g_bUseExtendedMasserTextures = GetPrivateProfileIntA("Main", "bUseExtendedMasserTextures", 1, filename);
		g_bUseExtendedSecundaTextures = GetPrivateProfileIntA("Main", "bUseExtendedSecundaTextures", 1, filename);

		GetPrivateProfileString("Main", "fDefaultLatitude", "50.0", resultString, 255, filename);
		g_fDefaultLatitude = atof(resultString);
		GetPrivateProfileString("Main", "fLatitudeMult", "0.286", resultString, 255, filename);
		g_fLatitudeMult = atof(resultString);
		g_fLatitudeMult /= 4096;
		GetPrivateProfileString("Main", "fLatitudeOffset", "0.0", resultString, 255, filename);
		g_fLatitudeOffset = atof(resultString);
		GetPrivateProfileString("Main", "fAxialTilt", "23.439", resultString, 255, filename);
		g_fAxialTilt = atof(resultString);
		GetPrivateProfileString("Main", "fSolarNoonOffset", "1.0", resultString, 255, filename);
		g_fSolarNoonOffset = atof(resultString);

		GetPrivateProfileString("Main", "fNpcScheduleSunrise", "7.5", resultString, 255, filename);
		g_fNpcScheduleSunrise = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleSunset", "18.5", resultString, 255, filename);
		g_fNpcScheduleSunset = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleLinearRange", "1.0", resultString, 255, filename);
		g_fNpcScheduleLinearRange = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleLinearBase", "0.0", resultString, 255, filename);
		g_fNpcScheduleLinearBase = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleLinearMult", "1.0", resultString, 255, filename);
		g_fNpcScheduleLinearMult = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleLogBase", "1.0", resultString, 255, filename);
		g_fNpcScheduleLogBase = atof(resultString);
		GetPrivateProfileString("Main", "fNpcScheduleLogMult", "1.0", resultString, 255, filename);
		g_fNpcScheduleLogMult = atof(resultString);

		GetPrivateProfileString("Main", "fSunLightZOffset", "0.0", resultString, 255, filename);
		g_fSunLightZOffset = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightZOffset", "0.0", resultString, 255, filename);
		g_fMoonLightZOffset = atof(resultString);

		GetPrivateProfileString("Main", "fMasserRiseCycleTime", "25.0", resultString, 255, filename);
		g_fMasserRiseCycleTime = atof(resultString)/24.0f;
		GetPrivateProfileString("Main", "fSecundaRiseCycleTime", "21.0", resultString, 255, filename);
		g_fSecundaRiseCycleTime = atof(resultString)/24.0f;

		GetPrivateProfileString("Main", "fMoonLightPercentFullMoon", "1.0", resultString, 255, filename);
		g_fMoonLightPercentFullMoon = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentWaningGibbous", "0.5", resultString, 255, filename);
		g_fMoonLightPercentWaningGibbous = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentLastQuarter", "0.1", resultString, 255, filename);
		g_fMoonLightPercentLastQuarter = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentWaningCrescent", "0.0", resultString, 255, filename);
		g_fMoonLightPercentWaningCrescent = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentNewMoon", "0.0", resultString, 255, filename);
		g_fMoonLightPercentNewMoon = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentWaxingCrescent", "0.0", resultString, 255, filename);
		g_fMoonLightPercentWaxingCrescent = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentFirstQuarter", "0.1", resultString, 255, filename);
		g_fMoonLightPercentFirstQuarter = atof(resultString);
		GetPrivateProfileString("Main", "fMoonLightPercentWaxingGibbous", "0.5", resultString, 255, filename);
		g_fMoonLightPercentWaxingGibbous = atof(resultString);

		GetPrivateProfileString("Main", "fMasserAngleFadeRedStart", "-90.0", resultString, 255, filename);
		g_fMasserAngleFadeRedStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeRedEnd", "-90.0", resultString, 255, filename);
		g_fMasserAngleFadeRedEnd = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeGreenStart", "35.0", resultString, 255, filename);
		g_fMasserAngleFadeGreenStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeGreenEnd", "-10.0", resultString, 255, filename);
		g_fMasserAngleFadeGreenEnd = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeBlueStart", "45.0", resultString, 255, filename);
		g_fMasserAngleFadeBlueStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeBlueEnd", "0.0", resultString, 255, filename);
		g_fMasserAngleFadeBlueEnd = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeAlphaStart", "-90.0", resultString, 255, filename);
		g_fMasserAngleFadeAlphaStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserAngleFadeAlphaEnd", "-90.0", resultString, 255, filename);
		g_fMasserAngleFadeAlphaEnd = atof(resultString);

		GetPrivateProfileString("Main", "fSecundaAngleFadeRedStart", "-90.0", resultString, 255, filename);
		g_fSecundaAngleFadeRedStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeRedEnd", "-90.0", resultString, 255, filename);
		g_fSecundaAngleFadeRedEnd = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeGreenStart", "35.0", resultString, 255, filename);
		g_fSecundaAngleFadeGreenStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeGreenEnd", "-10.0", resultString, 255, filename);
		g_fSecundaAngleFadeGreenEnd = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeBlueStart", "45.0", resultString, 255, filename);
		g_fSecundaAngleFadeBlueStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeBlueEnd", "0.0", resultString, 255, filename);
		g_fSecundaAngleFadeBlueEnd = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeAlphaStart", "-90.0", resultString, 255, filename);
		g_fSecundaAngleFadeAlphaStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaAngleFadeAlphaEnd", "-90.0", resultString, 255, filename);
		g_fSecundaAngleFadeAlphaEnd = atof(resultString);

		GetPrivateProfileString("Main", "fMasserEclipseMoonFadeAngleStart", "24.0", resultString, 255, filename);
		g_fMasserEclipseMoonFadeAngleStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserEclipseMoonFadeAngleEnd", "18.0", resultString, 255, filename);
		g_fMasserEclipseMoonFadeAngleEnd = atof(resultString);
		GetPrivateProfileString("Main", "fMasserEclipseSunFadeAngleStart", "12.5", resultString, 255, filename);
		g_fMasserEclipseSunFadeAngleStart = atof(resultString);
		GetPrivateProfileString("Main", "fMasserEclipseSunFadeAngleEnd", "7.5", resultString, 255, filename);
		g_fMasserEclipseSunFadeAngleEnd = atof(resultString);

		GetPrivateProfileString("Main", "fSecundaEclipseMoonFadeAngleStart", "19.0", resultString, 255, filename);
		g_fSecundaEclipseMoonFadeAngleStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaEclipseMoonFadeAngleEnd", "13.0", resultString, 255, filename);
		g_fSecundaEclipseMoonFadeAngleEnd = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaEclipseSunFadeAngleStart", "7.5", resultString, 255, filename);
		g_fSecundaEclipseSunFadeAngleStart = atof(resultString);
		GetPrivateProfileString("Main", "fSecundaEclipseSunFadeAngleEnd", "2.5", resultString, 255, filename);
		g_fSecundaEclipseSunFadeAngleEnd = atof(resultString);
	}


	// Load latitudes file
	void loadLatitudesFile() {
		char filename[MAX_PATH];
		char * pch;
		GetModuleFileNameA(NULL, filename, MAX_PATH);
		pch = strrchr(filename, '\\') + 1;
		strcpy(pch, latitudes_path);

		std::ifstream infile(filename);
		std::string line;
		while (std::getline(infile, line)) {
			line = line.substr(0, line.find(';')); // Remove comments
			if (line.size() == 0) continue;

			int pos = line.find(' ');
			std::pair<std::string,float> d;
			d.first = line.substr(0, pos);
			d.second = atof(line.substr(pos+1).c_str());

			g_vLatitudeData.push_back(d);
		}

	}


	// New Papyrus functions
	float GetSunriseBegin(StaticFunctionTag *base) {
		return *g_sunriseBegin;
	}

	float GetSunriseEnd(StaticFunctionTag *base) {
		return *g_sunriseEnd;
	}

	float GetSunsetBegin(StaticFunctionTag *base) {
		return *g_sunsetBegin;
	}

	float GetSunsetEnd(StaticFunctionTag *base) {
		return *g_sunsetEnd;
	}


	float GetDawnBegin(StaticFunctionTag *base) {
		return *g_sunriseDark;
	}

	float GetDawnEnd(StaticFunctionTag *base) {
		return GetSunriseTime();
	}

	float GetDuskBegin(StaticFunctionTag *base) {
		return GetSunsetTime();
	}

	float GetDuskEnd(StaticFunctionTag *base) {
		return *g_sunsetDark;
	}

	float GetPlayerLatitude(StaticFunctionTag *base) {
		return g_fPlayerLatitude;
	}

	float GetMasserRiseTime(StaticFunctionTag *base) {
		return g_fMasserRiseTime;
	}

	float GetMasserRiseCycleTime(StaticFunctionTag *base) {
		return g_fMasserRiseCycleTime;
	}

	float GetSecundaRiseTime(StaticFunctionTag *base) {
		return g_fSecundaRiseTime;
	}

	float GetSecundaRiseCycleTime(StaticFunctionTag *base) {
		return g_fSecundaRiseCycleTime;
	}

	float GetMasserPositionX(StaticFunctionTag *base) {
		NiTriShape * masserShape = GetMasserNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!masserShape || !player) return 0;
		return (masserShape->m_worldTransform.pos.x - player->pos.x);
	}
	float GetMasserPositionY(StaticFunctionTag *base) {
		NiTriShape * masserShape = GetMasserNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!masserShape || !player) return 0;
		return (masserShape->m_worldTransform.pos.y - player->pos.y);
	}
	float GetMasserPositionZ(StaticFunctionTag *base) {
		NiTriShape * masserShape = GetMasserNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!masserShape || !player) return 0;
		return (masserShape->m_worldTransform.pos.z - player->pos.z);
	}

	float GetSecundaPositionX(StaticFunctionTag *base) {
		NiTriShape * secundaShape = GetSecundaNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!secundaShape || !player) return 0;
		return (secundaShape->m_worldTransform.pos.x - player->pos.x);
	}
	float GetSecundaPositionY(StaticFunctionTag *base) {
		NiTriShape * secundaShape = GetSecundaNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!secundaShape || !player) return 0;
		return (secundaShape->m_worldTransform.pos.y - player->pos.y);
	}
	float GetSecundaPositionZ(StaticFunctionTag *base) {
		NiTriShape * secundaShape = GetSecundaNiTriShape();
		PlayerCharacter * player = (*g_thePlayer);
		if (!secundaShape || !player) return 0;
		return (secundaShape->m_worldTransform.pos.z - player->pos.z);
	}

	UInt32 GetMasserEclipse(StaticFunctionTag *base) {
		return g_isMasserEclipse;
	}
	UInt32 GetSecundaEclipse(StaticFunctionTag *base) {
		return g_isSecundaEclipse;
	}

	bool RegisterFuncs(VMClassRegistry * registry) {

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSunriseBegin", "EveningStar", GetSunriseBegin, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSunriseEnd", "EveningStar", GetSunriseEnd, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSunsetBegin", "EveningStar", GetSunsetBegin, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSunsetEnd", "EveningStar", GetSunsetEnd, registry));

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetDawnBegin", "EveningStar", GetDawnBegin, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetDawnEnd", "EveningStar", GetDawnEnd, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetDuskBegin", "EveningStar", GetDuskBegin, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetDuskEnd", "EveningStar", GetDuskEnd, registry));

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetPlayerLatitude", "EveningStar", GetPlayerLatitude, registry));

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMasserRiseTime", "EveningStar", GetMasserRiseTime, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMasserRiseCycleTime", "EveningStar", GetMasserRiseCycleTime, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSecundaRiseTime", "EveningStar", GetSecundaRiseTime, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSecundaRiseCycleTime", "EveningStar", GetSecundaRiseCycleTime, registry));

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMasserPositionX", "EveningStar", GetMasserPositionX, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMasserPositionY", "EveningStar", GetMasserPositionY, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetMasserPositionZ", "EveningStar", GetMasserPositionZ, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSecundaPositionX", "EveningStar", GetSecundaPositionX, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSecundaPositionY", "EveningStar", GetSecundaPositionY, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, float>("GetSecundaPositionZ", "EveningStar", GetSecundaPositionZ, registry));

		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, UInt32>("GetMasserEclipse", "EveningStar", GetMasserEclipse, registry));
		registry->RegisterFunction(new NativeFunction0 <StaticFunctionTag, UInt32>("GetSecundaEclipse", "EveningStar", GetSecundaEclipse, registry));

		return true;
	}
}
