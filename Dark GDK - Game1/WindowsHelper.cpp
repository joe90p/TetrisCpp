#include <Tetris.h>

HCURSOR WindowsHelper::activeCursor = LoadCursorFromFile("aero_arrow.cur");
bool WindowsHelper::cursorOverride = false;

void WindowsHelper::SetActiveCursor(HCURSOR cursor)
{
	cursorOverride = true;
	activeCursor = cursor;
}

HCURSOR WindowsHelper::GetActiveCursor()
{
	return activeCursor;
}

void WindowsHelper::Refresh()
{
	if(!cursorOverride)
	{
		activeCursor = LoadCursorFromFile("aero_arrow.cur");
	}
	cursorOverride = false;
}