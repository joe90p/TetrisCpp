// Dark GDK - The Game Creators - www.thegamecreators.com

// the wizard has created a very simple project that uses Dark GDK
// it contains the basic code for a GDK application

// whenever using Dark GDK you must ensure you include the header file
#include <tetris.h>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <globstruct.h>


void Initialise();
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

MathsHelper mh;

WNDPROC gdkProc;


LRESULT CALLBACK myProc ( HWND wnd, UINT msg, WPARAM w, LPARAM l )
{
   switch ( msg )
   {
      case WM_SETCURSOR:
      {
			SetCursor(WindowsHelper::GetActiveCursor());
			return true;
      }
      case WM_MOUSEMOVE:
      {
			CallWindowProc ( gdkProc, wnd, msg, w, l );
			SetCursor(WindowsHelper::GetActiveCursor());
			return 0;
      }
      default:
         if ( gdkProc )
            return CallWindowProc ( gdkProc, wnd, msg, w, l );
         else
            return DefWindowProc ( wnd, msg, w, l );
   }
   
   return DefWindowProc ( wnd, msg, w, l ); //or anything you want...
}

void DarkGDK ( void )
{
	gdkProc = (WNDPROC) SetWindowLong(g_pGlob->hWnd ,GWL_WNDPROC, (LONG)myProc);
	//WindowsHelper::activeCursor = LoadCursorFromFile("aero_link.cur");
	bool started = false;
	Point topLeftGridPosition;
	Initialise();
	//set top left position of grid	
	topLeftGridPosition.x = mh.RoundToNearest((SCREEN_WIDTH/2) -125, Grid::GRID_SQUARE_LENGTH) ;
	topLeftGridPosition.y = mh.RoundToNearest((SCREEN_HEIGHT/2) -290, Grid::GRID_SQUARE_LENGTH) ;
	DBBitmapHelper::GetInstance()->DrawBackground(topLeftGridPosition, Grid::GRID_BORDER_WIDTH, Grid::GRID_SIDEBAR_WIDTH, Grid::GRID_SQUARE_LENGTH, Grid::GRID_HEIGHT, Grid::GRID_WIDTH);	
	Game *gm = new Game(topLeftGridPosition);
	// our main loop
	while ( LoopGDK ( ) )
	{
		WindowsHelper::Refresh();
		if(started)
		{
			gm->Go();
		}
		else
		{
			dbSync();
			started = DBBitmapHelper::GetInstance()->IsStartButtonClicked();
		}
	}	
	// return back to windows
	return;
}

void Initialise()
{
	dbSetDisplayMode(SCREEN_WIDTH,SCREEN_HEIGHT,32);
	dbSetImageColorKey(255,0,255);
	
	// Turn on fullscreen mode
	dbSetWindowLayout(0, 0, 1);
	dbMaximizeWindow();
	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	
	dbDrawSpritesFirst();
	
	//seed randomness
	srand ( time(NULL) );
}