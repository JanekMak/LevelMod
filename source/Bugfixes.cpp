#include "pch.h"
#include "Bugfixes.h"

void FixRenderBugs()
{
	//const DWORD renderjmpAddr1 = 0x004f4ba9;
	const BYTE renderjmp1[] = { 0xE9, 0x10, 0xB6, 0xF0, 0xFF };
	DWORD old;
	VirtualProtect((void*)0x004f4ba9, sizeof(renderjmp1), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004f4ba9, renderjmp1, sizeof(renderjmp1));
	//VirtualProtect((void*)0x004f4ba9, sizeof(renderjmp1), old, &old);
	const BYTE renderFix1[] = { 0x85, 0xD2, 0x0F, 0x84, 0x10, 0x4A, 0x0F, 0x00, 0x89, 0x0A, 0x8B, 0x48, 0x10, 0xE9, 0xDE, 0x49, 0x0F, 0x00 };
	VirtualProtect((void*)0x004001be, sizeof(renderFix1), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004001be, renderFix1, sizeof(renderFix1));
	//VirtualProtect((void*)0x004001be, sizeof(renderFix1), old, &old);

	VirtualProtect((void*)0x004FEE77, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004FEE77 = 0x008A9000;// (DWORD)&RenderFix;
	//VirtualProtect((void*)0x004FEE77, 4, old, &old);

	VirtualProtect((void*)0x004FEEA4, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004FEEA4 = 0x008A9000;//(DWORD)&RenderFix;
	//VirtualProtect((void*)0x004FEEA4, 4, old, &old);


	VirtualProtect((void*)0x004FEEAF, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004FEEAF = 0x008A9000;//(DWORD)&RenderFix;
	//VirtualProtect((void*)0x004FEEAF, 4, old, &old);

	VirtualProtect((void*)0x004FEEC6, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004FEEC6 = 0x008A9000;//(DWORD)&RenderFix;
	//VirtualProtect((void*)0x004FEEC6, 4, old, &old);

	VirtualProtect((void*)0x004FF050, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004FF050 = 0x008A9000;//(DWORD)&RenderFix;
	//VirtualProtect((void*)0x004FF050, 4, old, &old);

	/*DWORD Old = 0x0090b048;
	for (DWORD i = 0; i < 1024; i++)
	{
		*(DWORD*)(RenderFix + i * 4) = *(DWORD*)(old + i * 4);
	}*/

	/*for (DWORD i = 0; i < 4096; i++)
	{
		RenderFix[i] = 0;
	}*/

}

void FixVertBugs()
{
	const BYTE vertjmp1[] = { 0xE9, 0x8A, 0xD6, 0xF5, 0xFF, 0x90, 0x90, 0x90 };
	DWORD old;
	VirtualProtect((void*)0x004A2C39, sizeof(vertjmp1), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004A2C39, vertjmp1, sizeof(vertjmp1));
	//VirtualProtect((void*)0x004A2C39, sizeof(vertjmp1), old, &old);
	const BYTE vertfix1[116] = {
	  0xD9, 0x85, 0x60, 0x87, 0x00, 0x00, 0xD8, 0x5C, 0x24, 0x14, 0xDF, 0xE0, 0x25, 0x00, 0x41, 0x00, 0x00, 0x75, 0x0A, 0x8B, 0x85, 0x60, 0x87, 0x00, 0x00, 0x89, 0x44, 0x24, 0x14, 0x8B, 0x44, 0x24, 0x10, 0x8B, 0x4C, 0x24, 0x14, 0xE9, 0x4F, 0x29, 0x0a, 0x00,
	  0x31, 0xFF, 0xD9, 0x85, 0x60, 0x86, 0x00, 0x00, 0xD8, 0x25, 0x38, 0x03, 0x40, 0x00, 0x6A, 0x00, 0x6A, 0x08, 0x6A, 0x00, 0x8B, 0xCD, 0xD9, 0x9D, 0x60, 0x86, 0x00, 0x00, 0xD9, 0x85, 0x70, 0x86, 0x00, 0x00, 0xD8, 0x25, 0x38, 0x03, 0x40, 0x00, 0xD9, 0x9D, 0x70, 0x86, 0x00, 0x00, 0xE8, 0x5B, 0xF9, 0x09, 0x00, 0x84, 0xC0, 0x0F, 0x85, 0xFC, 0x28, 0x0A, 0x00, 0x47, 0x83, 0xFF, 0x0C, 0x7C, 0xC1, 0xE9, 0x5B, 0x2A, 0x0A, 0x00, 0x00, 0x00, 0x40, 0x40
	};
	VirtualProtect((void*)0x004002c8, sizeof(vertfix1), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004002c8, vertfix1, sizeof(vertfix1));
	//VirtualProtect((void*)0x004002c8, sizeof(vertfix1), old, &old);
	const BYTE vertjmp2[] = { 0x0F, 0x84, 0xC9, 0xD6, 0xF5, 0xFF };
	VirtualProtect((void*)0x004A2C23, sizeof(vertjmp2), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004A2C23, vertjmp2, sizeof(vertjmp2));
	//VirtualProtect((void*)0x004A2C23, sizeof(vertjmp2), old, &old);
	/*const BYTE vertfix2 [] = {0x31, 0xFF, 0xD9, 0x85, 0x60, 0x86, 0x00, 0x00, 0xD8, 0x25, 0x38, 0x03, 0x40, 0x00, 0x6A, 0x00, 0x6A, 0x08, 0x6A, 0x00, 0x8B, 0xCD, 0xD9, 0x9D, 0x60, 0x86, 0x00, 0x00, 0xD9, 0x85, 0x70, 0x86, 0x00, 0x00, 0xD8, 0x25, 0x38, 0x03, 0x40, 0x00, 0xD9, 0x9D, 0x70, 0x86, 0x00, 0x00, 0xE8, 0x5B, 0xF9, 0x09, 0x00, 0x84, 0xC0, 0x0F, 0x85, 0xFC, 0x28, 0x0A, 0x00, 0x47, 0x83, 0xFF, 0x0C, 0x7C, 0xC1, 0xE9, 0x5B, 0x2A, 0x0A, 0x00, 0x00, 0x00, 0x40, 0x40};
	VirtualProtect((void*)0x004002F2, sizeof(vertfix2), PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)0x004002F2, vertfix2, sizeof(vertfix2));*/
	const DWORD b = 0x0058EA10;
	VirtualProtect((void*)b, 4, PAGE_EXECUTE_READWRITE, &old);
	*(float*)b = 36.0f;
	//VirtualProtect((void*)b, 4, old, &old);
	/*const DWORD c = 0x004A2BDD;
	VirtualProtect((void*)c, 1, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)c = 0x4B;*/
}

//Limit chat message to 149 characters, to prevent crashing
void FixChatHook(char* chatText)
{
	/*chatText[0] = 0x00;
	chatText[1] = 0x00;*/
	if (chatText && strlen(chatText) > 149)
	{
		chatText[0] = 0x00;
		chatText[1] = 0x00;
		chatText[148] = 0x00;
		chatText[149] = 0x00;
	}
}

void FixChat()
{
	DWORD old;
	
	
	
	VirtualProtect((VOID*)0x004558FB, 5, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x004558FB = 0x5011468D;
	*(BYTE*)0x004558FF = 0x90;
	//VirtualProtect((VOID*)0x004558FB, 5, old, &old);

	VirtualProtect((VOID*)0x00455912, 4, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x00455912 = (DWORD)FixChatHook - 0x00455916;
	//VirtualProtect((VOID*)0x00455912, 4, old, &old);
}

void FixQBParsing()
{
	DWORD old;
	VirtualProtect((void*)0x0042B2CC, 1, PAGE_EXECUTE_READWRITE, &old);
	*(BYTE*)0x0042B2CC = 8;
	//VirtualProtect((void*)0x0042B2CC, 1, old, &old);
	VirtualProtect((void*)0x0042B2D4, 5, PAGE_EXECUTE_READWRITE, &old);
	*(DWORD*)0x0042B2D4 = 0x04408BC3;
	*(BYTE*)0x0042B2D8 = 0xC3;
	//VirtualProtect((void*)0x0042B2D4, 5, old, &old);
}