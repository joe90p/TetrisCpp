/*#ifndef TetronimoLowLevel_H
#define TetronimoLowLevel_H

#include <Grid.h>
#include <MathsHelper.h>


enum TetrisBlockType { Cyan = 1, Yellow = 2, Purple = 3, Green = 4, Red = 5, Blue = 6, Orange = 7 };

enum MoveType { Down = 1, Left = 2, Right = 3};


class TetronimoLowLevel
{
private:

	int origPosX;
	int origPosY;
	Grid *grid;
	bool canMoveLeft;
	bool canMoveRight;
	bool canMoveDown;
	Point GetPoint(int x, int y);
	void SetTurnAxis(float x, float y);	
public:
	
	void Move(MoveType movType);
	void Create1();
	void Create2();
	void Create3();
	void Create4();
	void Create5();
	void Create6();
	void Create7();
	Point turnAxis;
	TetronimoLowLevel(Grid *p_grid);
	TetrisBlockType blockType;
	Point points[5];
	void Turn(bool clockwise);
};
*/
//#endif /* TetronimoLowLevel_H */
