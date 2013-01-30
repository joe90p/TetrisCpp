#ifndef Grid_H
#define Grid_H

/*#include <DarkGDK.h>

#include <Tetris.h>

typedef struct
{
	float x;
	float y;
} Point;

typedef struct
{
	int x;
	int y;
	bool IsOccupied;
} GridSquare;

class Grid
{
private:
	
	int elementCount;
	int arrayAllocation;
	void MovePointLeft(Point *p);
	void MovePointRight(Point *p);
	void MovePointDown(Point *p);
	void TurnPoint(Point *p, bool clockwise, Point posChange);
	MathsHelper *mathHelp;
public:
	int gridSquareLength;
	GridSquare *squares;
	Grid(int p_gridSquareLength, int p_gridXNoOfSquares, int p_gridYNoOfSquares);
	void SetUpSquareArray();
	int AddToArray(GridSquare item);
	int gridXNoOfSquares;
	int gridYNoOfSquares;
	bool IsOccupied(int x, int y);
	bool IsOccupied(Point p);
	Point GetTurnPoint(Point p, bool clockwise, Point posChange);
	Point GetMovePointLeft(Point p);
	Point GetMovePointRight(Point p);
	Point GetMovePointDown(Point p);
	void Update(Tetronimo *t);
	
};
*/
//#endif /* Grid_H */