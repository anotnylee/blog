#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

static void MouseEvent_LeftButtonClick();
static void MouseEvent_RightButtonClick();
static void MouseEvent_AbsMove(unsigned int x, unsigned int y);

int main(int argc, char * argv[])
{
	do {
		int arrInts[3] = { 0, 0, 0 };
		SystemParametersInfo(SPI_GETMOUSE, 0, &arrInts[0], 0);
		printf("Parameters of Mouse Relative Move :[%u,%u]x[%u]\n", arrInts[0], arrInts[1], arrInts[2]);
	} while (0); // if NO 'while(0)' compilers of vs2015 will crash, report it to MS.

	do {
		const static float centerX = 500;
		const static float centerY = 500;
		const static float radius  = 150;
		const static float cPoints = 50;
		const static float PI = 3.141593f;
		const static float rad = 2.0f * PI / cPoints;
		for (int i = 0; i < cPoints; i++) {
			float x = centerX + (radius * static_cast<float>(sin(rad * i)));
			float y = centerY + (radius * static_cast<float>(cos(rad * i)));
			MouseEvent_AbsMove(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
			MouseEvent_LeftButtonClick();
			Sleep(100);
		}
	} while (0);
	
	return 0;
}

#define MOUSEEVENT_MOVE     (0x0001)
#define MOUSEEVENT_ABSOLUTE (0x8000)

void MouseEvent_LeftButtonClick()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN  | MOUSEEVENTF_LEFTUP | MOUSEEVENT_ABSOLUTE
		, 0 // ignored when click
		, 0 // ignored when click
		, 0, 0);
}

void MouseEvent_AbsMove(unsigned int x, unsigned y)
{
	unsigned int nDesktopX = 800;
	unsigned int nDesktopY = 600;
	do {
		nDesktopX = GetSystemMetrics(SM_CXSCREEN);
		nDesktopY = GetSystemMetrics(SM_CYSCREEN);
	} while (0);

	/*
	* Something about !ABSOLUTE
	* 1) you move mouse 10mm on your desktop slowly;
	* 2) you move back mouse 10mm on your desktop fast;
	* 3) Does the mouse go back to its original position?
	* 4) that is because Acceleration take effects.
	* 5) Acceleration algorithm reference 3 parameters, threshold1, threshold2, and level
	* 6) relative distance is [0, threshold1) and level != 0, x2
	* 7) relative distance is [threshold1, threshold2), and level == 2, x4
	* 8) Done of explanation.
	*/
	do {
		POINT pt; memset(&pt, 0, sizeof(pt));
		GetCursorPos(&pt);
		printf("pt.x=%u; pt.y=%u\n", pt.x, pt.y);
	} while (0);

	/*
	* About Parameters x & y
	* mouse move is between [0, 65535];
	* if you want to move by logical pixels of desktop, 
	* you need caculate map between (x/MaxXPixelsOfDesktop * 65535) or (y/MaxYPixelsOfDesktop * 65535)
	*/
	mouse_event( MOUSEEVENT_MOVE | MOUSEEVENT_ABSOLUTE
		, static_cast<unsigned int>(1.0f * x / nDesktopX * 65535)
		, static_cast<unsigned int>(1.0f * y / nDesktopY * 65536)
		, 0, 0);

	do {
		POINT pt; memset(&pt, 0, sizeof(pt));
		GetCursorPos(&pt);
		printf("pt.x=%u; pt.y=%u\n", pt.x, pt.y);
	} while (0);
}

void MouseEvent_RightButtonClick()
{
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP	| MOUSEEVENT_ABSOLUTE
		, 0 // ignored when click
		, 0 // ignored when click
		, 0, 0);
}