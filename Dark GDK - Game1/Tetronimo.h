/*#ifndef Tetronimo_H
#define Tetronimo_H

#include <Tetris.h>
#include <DarkGDK.h>

class Tetronimo
{
private:

	void Create1();
	void Create2();
	void Create3();
	void Create4();
	void Create5();
	void Create6();
	void Create7();
	int spritecount;
	int origPosX;
	int origPosY;
	Point turnAxis;
	Grid *grid;
	void SetTurnAxis(float x, float y);
	TetrisBlockType blockType;
	void dbSpriteWrap(int iID, Point p, int iImage);
	Point GetPoint(int x, int y);
	MathsHelper *mathHelp;
	TetronimoLowLevel *tetronimo_low;
public:
	Tetronimo(int spriteCount, Grid *p_grid);
	void Turn(bool clockwise);
	void Move(MoveType movType);
	void HardDrop();
	void UpdateMovement();
	void UpdateGrid();
	bool canMoveLeft ;
	bool canMoveRight;
	bool canMoveDown ;
	bool canTurnClockwise;
	bool canTurnAntiClockwise;
};
*/
//#endif /* Tetronimo_H */