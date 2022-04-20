#include "skse/PluginAPI.h"
#include "skse/SafeWrite.h"
#include "skse/skse_version.h"

#include "EveningStar.h"

static PluginHandle					g_pluginHandle = kPluginHandle_Invalid;
static SKSEPapyrusInterface         * g_papyrus = NULL;


const UInt32 kSunShadowHook = 0x005979D2;
const UInt32 kSunShadowReturn = 0x005979D8;

static _declspec(naked) void HookSunShadow(void)
{
	_asm
	{
		// overwritten code
		mov [eax+0x0C8], ecx

		pushad
		call EveningStar::UpdateDirectionalLight
		popad

		jmp kSunShadowReturn
	}
}


const UInt32 kSunPosHook = 0x0059759A;
const UInt32 kSunPosReturn = 0x005975A2;

static _declspec(naked) void HookSunPos(void)
{
	_asm
	{
		pushad
		call EveningStar::UpdateSunPos
		popad

		jmp kSunPosReturn
	}
}


const UInt32 kCheckMoonPhaseHook = 0x0058D824;
const UInt32 kCheckMoonPhaseReturn01 = 0x0058D858;
const UInt32 kCheckMoonPhaseReturn02 = 0x0058D8E3;

static _declspec(naked) void HookCheckMoonPhase(void)
{
	_asm
	{
		pushad
		push ebp // Moon*
		call EveningStar::UpdateCheckMoonPhase
		add esp, 4
		test eax, eax
		popad

		je skip
		jmp kCheckMoonPhaseReturn01
	skip:
		jmp kCheckMoonPhaseReturn02
	}
}


const UInt32 kSetMoonPhaseHook = 0x0058D86B;
const UInt32 kSetMoonPhaseReturn = 0x0058D873;

static _declspec(naked) void HookSetMoonPhase(void)
{
	_asm
	{
		// overwritten code
		mov ss:[esp+0x14], ecx

		pushad
		push ebp // Moon*
		call EveningStar::UpdateSetMoonPhase
		add esp, 4
		popad

		//mov edx, EveningStar::g_moonPhase
		//mov eax, ss:[edx*0x8+ebp+0x18]
		mov eax, EveningStar::g_moonPhaseTexture

		jmp kSetMoonPhaseReturn
	}
}


const UInt32 kSetMoonColorHook = 0x0058DADA;
const UInt32 kSetMoonColorReturn = 0x0058DADF;

static _declspec(naked) void HookSetMoonColor(void)
{
	_asm
	{
		pushad
		push ebp // Moon*
		call EveningStar::UpdateSetMoonColor
		add esp, 4
		popad

		// overwritten code
		mov esi, -2

		jmp kSetMoonColorReturn
	}
}


const UInt32 kSetGameHourAIPackagesHook = 0x005E207A;
const UInt32 kSetGameHourAIPackagesReturn = 0x005E207F;

static _declspec(naked) void HookSetGameHourAIPackages(void)
{
	_asm
	{
		call EveningStar::GetGameHourMod
		jmp kSetGameHourAIPackagesReturn
	}
}


const UInt32 kSetGameHourMerchantStatusHook = 0x0075E7A4;
const UInt32 kSetGameHourMerchantStatusReturn = 0x0075E7A9;

static _declspec(naked) void HookSetGameHourMerchantStatus(void)
{
	_asm
	{
		call EveningStar::GetGameHourMod
		jmp kSetGameHourMerchantStatusReturn
	}
}


extern "C"	{

	bool SKSEPlugin_Query(const SKSEInterface* skse, PluginInfo* info)	{
		//gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim\\SKSE\\EveningStar.log");
		//gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		//gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		//_MESSAGE("MyPluginScript");

		// populate info structure
		info->infoVersion =	PluginInfo::kInfoVersion;
		info->name =		"EveningStar";
		info->version =		1;

		// store plugin handle
		g_pluginHandle = skse->GetPluginHandle();

		if(skse->isEditor) {
			//_MESSAGE("loaded in editor, marking as incompatible");
			return false;
		} else if(skse->runtimeVersion != RUNTIME_VERSION_1_9_32_0) {
			//_MESSAGE("unsupported runtime version %08X", skse->runtimeVersion);
			return false;
		}

		// supported runtime version
		return true;
	}

	bool SKSEPlugin_Load(const SKSEInterface* skse)	{
		//_MESSAGE("MyScriptPlugin loaded");

		EveningStar::loadIniFile();
		EveningStar::loadLatitudesFile();

		g_papyrus = reinterpret_cast<SKSEPapyrusInterface*>(skse->QueryInterface(kInterface_Papyrus));

		//Check if the function registration was a success...
		bool btest = g_papyrus->Register(EveningStar::RegisterFuncs);

		//if (btest) {
		//	_MESSAGE("Register Succeeded");
		//}

		// Apply patches
		WriteRelJump(kSunPosHook, reinterpret_cast<UInt32>(HookSunPos));
		WriteRelJump(kSunShadowHook, reinterpret_cast<UInt32>(HookSunShadow));
		WriteRelJump(kCheckMoonPhaseHook, reinterpret_cast<UInt32>(HookCheckMoonPhase));
		WriteRelJump(kSetMoonPhaseHook, reinterpret_cast<UInt32>(HookSetMoonPhase));
		WriteRelJump(kSetMoonColorHook, reinterpret_cast<UInt32>(HookSetMoonColor));

		// Set moon alpha to 1.0 so moon is drawn, even when close to horizon
		SafeWrite16(0x0058D7E6, 0xE8D9);
		SafeWrite16(0x0058D7E8, 0x9090);
		SafeWrite8(0x0058D7EA, 0x90);

		// Disable code that sets the vanilla sun shadow rotation
		SafeWrite16(0x00597641, 0x9090);

		// Change the GameHour used by AI Packages
		WriteRelJump(kSetGameHourAIPackagesHook, reinterpret_cast<UInt32>(HookSetGameHourAIPackages));
		WriteRelJump(kSetGameHourMerchantStatusHook, reinterpret_cast<UInt32>(HookSetGameHourMerchantStatus));

		return true;
	}

};

