#ifndef Tetris_H
#define Tetris_H

#include <stdlib.h>
#include <MathsHelper.h>
#include <DarkGDK.h>
#include <windows.h>

enum MoveType { Down = 1, Left = 2, Right = 3};

enum GameState { InPlay = 1, Over = 2, Complete = 3, Paused=4};

typedef struct
{
	float x;
	float y;
} Point;

class DBHelper
{
private:
	int _blockCyanImageID;
	int _blockYellowImageID;
	int _blockPurpleImageID;
	int _blockGreenImageID;
	int _blockRedImageID;
	int _blockBlueImageID;
	int _blockOrangeImageID;
	int _blockGreyImageID;
	int _backgroundImageID;
	int _gridImageID;
	int _borderImageID;
	int _sideBarImageID;
	int _scoreTextImageID;	
	int _scoreValueTextImageID;
	int _nextTextImageID;
	int _levelTextImageID;
	int _levelValueTextImageID;
	int _goalTextImageID;
	int _goalValueTextImageID;
	int _startButtonImageID;
	int _restartButtonImageID;
	int _exitButtonImageID;
	int _gamecompleteImageID;
	int _gameoverImageID;
	int _resumeImageID;
	int _pauseTextImageID;
	int bitmapNumber;
	int imageNumber;
	void SetupGridImage(int gridSquareLength, int gridWidth, int gridLength);
	void SetupBorderImage(int gridSquareLength, int gridWidth, int gridLength, int borderWidth);
	void SetupSideBarImage(int gridSquareLength, int gridLength, int borderWidth, int sideBarWidth);
	void SetupSpriteFromText(int x, int y, char *text, int imageID);
	static DBHelper* _instance;
	DBHelper();
	int GetImageNumber();
	static const int DUMMY_IMAGE_ID = 99;
	static const int DUMMY_BITMAP_ID = 99;
public:
	int GetBitmapNumber();
	static DBHelper* GetInstance();
	int GetBlockCyanImageID();
	int GetBlockYellowImageID();
	int GetBlockPurpleImageID();
	int GetBlockGreenImageID();
	int GetBlockRedImageID();
	int GetBlockBlueImageID();
	int GetBlockOrangeImageID();
	int GetBlockGreyImageID();
	int GetBackgroundImageID();
	int GetGridImageID(int gridSquareLength, int gridWidth, int gridLength);
	int GetBorderImageID(int gridSquareLength, int gridWidth, int gridLength, int borderWidth);
	int GetSideBarImageID(int gridSquareLength, int gridLength, int borderWidth, int sideBarWidth);
	int GetScoreTextImageID();	
	int GetNextTextImageID();
	int GetLevelTextImageID();
	int GetLevelValueTextImageID();
	int GetGoalTextImageID();	
	int GetGoalValueTextImageID();
	int GetScoreValueTextImageID();
	int GetRestartButtonImageID();
	int GetExitButtonImageID();	
	int GetGameCompleteImageID();
	int GetGameOverImageID();
	int GetResumeImageID();
	int GetPauseTextImageID();
	void UpdateValueTextImageID(char *text, Point topLeft,int imageID, int oldBitmpNumber, Point size);
	int GetStartButtonImageID();
	void SetBitmapNumber(int value);
	
};

typedef struct
{
	int x;
	int y;
	bool IsOccupied;
	int blockNumber;
	int imageID;
} GridSquare;

class Grid
{
private:
	int elementCount;
	int arrayAllocation;
	void MovePointLeft(Point *p);
	void MovePointRight(Point *p);
	void MovePointDown(Point *p);
	void MovePointVector(Point *p, Point vector);
	void TurnPoint(Point *p, bool clockwise, Point posChange);
	MathsHelper *mathHelp;
	int gridSquareLength;
	GridSquare *squares;
	int gridXNoOfSquares;
	int gridYNoOfSquares;
	int AddToArray(GridSquare item);
	GridSquare GetSquare(int x, int y);
	GridSquare *GetSquarePointer(int x, int y);
	static int blockNumber;
	int CompleteLineCheck();
	Point topLeft;

public:
	Grid(int p_gridSquareLength, int p_gridXNoOfSquares, int p_gridYNoOfSquares, Point topLeft);
	void SetUpSquareArray();	
	int GetGridXNoOfSquares();
	int GetGridYNoOfSquares();
	bool IsOccupied(int x, int y);
	bool IsOccupied(Point p);
	Point GetTurnPoint(Point p, bool clockwise, Point posChange);
	Point GetMovePointLeft(Point p);
	Point GetMovePointRight(Point p);
	Point GetMovePointDown(Point p);
	Point GetMovePointVector(Point p, Point vector);
	int Update(GridSquare *tetronimoSquares);
	Point GetPoint(int x, int y);
	GridSquare GetNewSquare(int x, int y, bool isOccupied, int blockCount);
	int GetGridSquareLength();
	GridSquare GetNewSquare(int x, int y, bool isOccupied, int blockCount, int imageID);
	Point Grid::GetGridTopLeft();
	int GetImageNumber();
	static const int GRID_WIDTH = 10;
    static const int GRID_HEIGHT = 20;
	static const int GRID_SQUARE_LENGTH = 25;
	static const int GRID_BORDER_WIDTH = 30;
	static const int GRID_SIDEBAR_WIDTH = 100;
};

class GridDB
{
private:
	Grid *grd;
public:
	GridDB(int p_gridSquareLength, int p_gridXNoOfSquares, int p_gridYNoOfSquares, Point topLeft);
	void SetUpSquareArray();
	int Update(GridSquare *tetronimoSquares);
	int GetGridXNoOfSquares();
	int GetGridYNoOfSquares();
	int GetGridSquareLength();
	Grid * GetGrid();
	Point GetGridTopLeft();
	int GetImageNumber();
};



class Tetronimo
{
private:	
	Grid *grid;
	bool canMoveLeft;
	bool canMoveRight;
	bool canMoveDown;
	bool canTurnClockwise;
	bool canTurnAntiClockwise;		
	bool canMoveToSpawningPosition;
	Point turnAxis;
	Point points[5];
	GridSquare squares[5];
	int imageID;
	void Create1(int origPosX, int origPosY);
	void Create2(int origPosX, int origPosY);
	void Create3(int origPosX, int origPosY);
	void Create4(int origPosX, int origPosY);
	void Create5(int origPosX, int origPosY);
	void Create6(int origPosX, int origPosY);
	void Create7(int origPosX, int origPosY);
	void SetTurnAxis(float x, float y);	
	void UpdateMovement();
	int Initialise(Grid *p_grid);
	void Create(int x, int y, int random);
	int spawnPosX;
	int spawnPosY;
public:	
	Tetronimo(Grid *p_grid);
	Tetronimo(Grid *p_grid, int origPosX, int origPosY);
	void Move(MoveType movType);
	void Turn(bool clockwise);	
	int GetImageID();
	Point* GetPoints();
	GridSquare* GetSquares();
	bool GetCanMoveLeft();
	bool GetCanMoveRight();
	bool GetCanMoveDown();
	bool GetCanTurnClockwise();
	bool GetCanTurnAntiClockwise();
	void MoveToSpawningPosition();
	void Move(int x, int y);
	bool CanMoveToSpawningPosition();
};

class TetronimoDB
{
private:
	int spritecount;
	void dbSpriteWrap(int iID, Point p, int iImage);
	void dbSpriteWrap(GridSquare g, int iImage);
	Tetronimo *tetronimo;
public:
	TetronimoDB(Grid *p_grid);
	TetronimoDB(Grid *p_grid, int origPosX, int origPosY);
	void Turn(bool clockwise);
	void Move(MoveType movType);
	void HardDrop();
	Point * GetPoints();
	GridSquare * GetSquares();
	bool GetCanMoveLeft();
	bool GetCanMoveRight();
	bool GetCanMoveDown();
	bool GetCanTurnClockwise();
	bool GetCanTurnAntiClockwise();
	void MoveToSpawningPosition();
	int GetImageID();
	bool CanMoveToSpawningPosition();
};


class Game
{
private:
	int timerPeriod; // the measurement of time used to detrmine time limits for moves
	int timerStart; //used to measure the elapsed time
	int elapsedTime; //stores elapsed time
	int stationaryTimerStart; //used to measure stationaryTime
	int stationaryTime; //how long tetronimo has remained stationary
	int input; //what sort of input has been received from player
	bool lastMoveDown; //indicates if last move, moved tetronimo down
	bool hasMoved; //indicates if tetronimo has moved
	bool originallyLanded; //indicates if tetronimo was originally landed on initial entry into loop
	bool hasHardDropped; //has tetronimo been hard dropped
	//bool complete;
	int numLines;
	int score;
	int level;
	int goal;
	GridDB *g;
	TetronimoDB *t; 
	TetronimoDB *t_Next;
	void LockAndSpawnNew(GridDB *g, TetronimoDB *t, TetronimoDB *t_Next);
	void ParseAndMove(bool*lastMoveDown, TetronimoDB *t, bool *hasMoved, bool *hasHardDropped);
	Point _topLeftGridPosition;
	int ParseInput();
	static const int SCANCODE_SPACEBAR = 57;
	static const int SCANCODE_DOWN = 80;
	static const int SCANCODE_UP = 72;
	static const int SCANCODE_LEFT = 75;
	static const int SCANCODE_RIGHT = 77;
	static const int SCANCODE_X = 45;
	static const int SCANCODE_Z = 44;
	static const int SCANCODE_P = 25;
	bool upKeyDown;
	bool spaceBarDown;
	bool zKeyDown;
	bool xKeyDown;
	bool pKeyDown;
	int leftRepeatCount;
	int rightRepeatCount;
	int downRepeatCount;
	bool ActionHeldKeyPress( int*repeatCount);
	void Init();
	GameState _state;
	bool PauseCheck();
public:
	Game(Point topLeftGridPosition);
	void Go();
	static const int NEXTPIECE_X = 430;
	static const int NEXTPIECE_Y = 230;
	static const int NUMBER_LINES_PER_LEVEL = 5;
	static const int NUMBER_OF_LEVELS = 10;
	static const int MIN_TIMER_PERIOD = 200;
	static const int MAX_TIMER_PERIOD = 925;
};

class DBBitmapHelper
{
private:
	static DBBitmapHelper* _instance;
	DBBitmapHelper();
	int borderID;
	int backgroundID;
	int gridID;
	int sideBarID;
	int levelTextID;
	int nextTextID;	
	int scoreTextID;
	int goalTextID;
	int scoreValueTextID;
	int levelValueTextID;
	int goalValueTextID;
	int startButtonID;
	int minBitmapID;
	int restartButtonID;
	int exitButtonID;
	int gameCompleteID;
	int gameOverID;
	int resumeID;
	int pauseTextID;
	bool IsButtonClicked(int buttonID);
public:
	static DBBitmapHelper* GetInstance();
	void DrawBackground(Point topLeftGridPosition, int borderWidth, int sideBarWidth, int gridSquareLength, int gridLength, int gridWidth);
	void UpdateScore(int score, Point _topLeftGridPosition);
	void UpdateLevel(int level, Point _topLeftGridPosition);
	void UpdateGoal(int goal, Point _topLeftGridPosition);
	bool IsStartButtonClicked();
	bool DeleteBitmapRange(int maxBitmapID);
	void ShowGameOverBitmaps(bool show);
	void ShowGameCompleteBitmaps(bool show);
	bool IsReStartButtonClicked();
	bool IsExitButtonClicked();
	void ShowResume(bool show);
};

class WindowsHelper
{
private:
	static HCURSOR activeCursor;
	static bool cursorOverride;
public:
	
	static HCURSOR GetActiveCursor();
	static void SetActiveCursor(HCURSOR cursor);
	static void WindowsHelper::Refresh();
};
#endif /* Tetris_H */