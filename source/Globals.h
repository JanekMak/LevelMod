#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H
#include "Script.h"
#include "QBKey.h"
#include "CXBOXController.h"
#include "_Math.h"

//--------Spine and Acid--------
enum TransferType
{
	ACID, BANK, SPINE
};
namespace Slerp
{
	extern bool transfer;
	extern bool landing;
	extern bool m_began_frame_in_transfer;
	extern bool slerping;
	extern Matrix start;
	extern Matrix end;
	extern Matrix old;
	extern float duration;
	extern float radians;
	extern float timer;
	extern D3DXVECTOR3 axis;
	extern Vertex vel;
	extern Vertex facing;
	extern float height;
	extern Vertex goal;
	//
	extern Vertex last;
	extern float lerp;
	extern bool inAcid;
	extern bool vert;
	extern bool addedvel;
	extern bool landed;
	extern bool OnGround;
	extern bool OnGrind;
	extern bool done;
	extern bool trying;
	extern float value;
	extern bool wallplant;
	extern DWORD m_last_wallplant_time_stamp;
	extern Vertex realVelocity;
	extern TransferType type;
	extern Vertex targetNormal;
	extern D3DXVECTOR4 target_normal;

	extern float speed;
};
//--------Spine and Acid--------

//--------XINPUT--------
namespace XINPUT
{
	extern bool vibrating;
	extern XINPUT_VIBRATION vibration;
	extern DWORD vibrationFrames;
	extern CXBOXController* Player1;
};
//--------XINPUT--------

//--------Game States--------
namespace GameState
{
	EXTERN extern bool GotSuperSectors;
};
//--------Game States--------

//--------Functions callable from script--------
bool NotScript(CStruct* pStruct, CScript* pScript);
bool GetZAngle(CStruct* pParams, CScript* pScript);
bool GetSkaterLook(CStruct* pParams, CScript* pScript);
bool LeaveObserveMode(CStruct* pParams, CScript* pScript);
bool EnterObserveMode(CStruct* pParams, CScript* pScript);
bool ObserveNext(CStruct* pParams, CScript* pScript);
bool StoreSkaterPos(CStruct* pParams, CScript* pScript);
bool GetSkaterPos(CStruct* pParams, CScript* pScript);
bool GetSpeedScript(CStruct* pParams, CScript* pScript);
bool WallplantTimeGreaterThan(CStruct* pParams, CScript* pScript);
bool CreatePair(CStruct* pStruct, CScript* pScript);
bool GrafStarted(CStruct* pStruct, CScript* pScript);
bool AddToGlobal(CStruct* pStruct, CScript* pScript);
bool SubToGlobal(CStruct* pStruct, CScript* pScript);
bool FreezeCamera(CStruct* pStruct, CScript* pScript);
bool UnfreezeCamera(CStruct* pStruct, CScript* pScript);
bool ChangeString(CStruct* pStruct, CScript* pScript);
bool strstr(CStruct* pStruct, CScript* pScript);
bool ChangeParamToUnnamedScript(CStruct* pStruct, CScript* pScript);
bool KillMovingObjectScript(CStruct* pStruct, CScript* pScript);
bool MoveObjectScript(CStruct* pStruct, CScript* pScript);

bool IsOptionOn(CStruct* pStruct, CScript* pScript);
bool GetParamScript(CStruct* pStruct, CScript* pScript);
bool LM_GotParamScript(CStruct* pStruct, CScript* pScript);
bool SetOption(CStruct* pStruct, CScript* pScript);
bool ToggleOption(CStruct* pStruct, CScript* pScript);
bool GetOptionText(CStruct* pStruct, CScript* pScript);
bool AddOption(CStruct* pStruct, CScript* pScript);
//--------Functions callable from script--------

//--------Functions NOT callable from script--------
void AddVibration(CStruct* pStruct, CScript* pScript);
bool SetTagLimit(CStruct* pStruct, CScript* pScript);
void NotGood(DWORD checksum, CScript* pScript);
bool TestForAcid(CStruct* pParams, CScript* pScript);
//--------Functions NOT callable from script--------

//--------depricated--------
bool Kill3DGrass(CStruct* params, CScript* pScript);
bool UpdateLevelModSettings(CStruct* params, CScript* pScript);
bool ToggleHookDebugMessages(CStruct* pStruct, CScript* pScript);
bool UnhookDebugMessages(CStruct* pStruct, CScript* pScript);
bool CreateConsole(CStruct* pStruct, CScript* pScript);
bool HideConsole(CStruct* pStruct, CScript* pScript);
bool HookDebugMessages(CStruct* pStruct, CScript* pScript);
bool SetMemoryPoolSize(CStruct* pStruct, CScript* pScript);
bool GetMemoryPoolSize(CStruct* pStruct, CScript* pScript);
bool GetMemoryPoolSizeText(CStruct* pStruct, CScript* pScript);
bool UpdateSpineText(CStruct* pStruct, CScript* pScript);
bool PreWallplantScript(CStruct* pParams, CScript* pScript);
bool WallplantScript(CStruct* pParams, CScript* pScript);
bool UsingNewMenu(CStruct* pStruct, CScript* pScript);
bool UsingSoundFix(CStruct* pStruct, CScript* pScript);
bool UsingTeleFix(CStruct* pStruct, CScript* pScript);
bool ToggleNewMenu(CStruct* pStruct, CScript* pScript);
bool CounterIsOn(CStruct* pStruct, CScript* pScript);
bool ToggleGrafCounter(CStruct* pStruct, CScript* pScript);
bool ToggleTeleFix(CStruct* pStruct, CScript* pScript);
bool ToggleSoundFix(CStruct* pStruct, CScript* pScript);
bool GetMotd(CStruct* pStruct, CScript* pScript);
bool CallWithNoNameScript(CStruct* pStruct, CScript* pScript);
//--------depricated--------


//--------Naked Functions--------
//Gets executed when you call a script that doesn't exist
void __cdecl NotGood_naked();
//Gets executed whenever game generates a checksum
void Checksum_naked();
//Gets executed when game opens a level file
void Fopen_naked();
//Gets executed at begining of frame
void BeganTransferCheck_naked();
//Currently not yet added
void handle_post_transfer_limit_overrides_naked();
//Gets executed when landing
void ResetTransfer_naked();
//Gets executed when "hit" a wall
void airhook_naked();
//Gets executed when state is AIR, this one is used to check if you want to spine/acid/bank
void MaybeAcid_naked();
//Gets executed when state is AIR, this one is used to reset the lerping matrix while spine/acid/bank
void CheckForTransfer_naked();
//Don't remember when this gets executed...
void ResetTransferVel_naked();
//Gets executed when state is AIR, this one is used to lerp the skater in spine/acid/bank
void Slerp_naked();
//Gets executed when state is GROUND
void OnGround_naked();
//Gets executed when Vibration script is called
void __cdecl HookVibrate_naked();

//depricated
void TestForAcid_naked();
//--------Naked Hooked Functions--------


//--------Non Naked Hooked Functions--------
DWORD GrindParamHook(char* str, int unk);
//--------Non Naked Hooked Functions--------

//--------Function hooking--------
//XINPUT
void HookVibrate();
void HookControls();
//BugFixes and physics control
void FixSpineFlag();
//--------Function hooks--------

//--------Game Functions--------
EXTERN DWORD _GetCurrentTime();
//--------Game Functions--------
#endif