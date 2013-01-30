/*
Include
*/
#include <Tetris.h>
/*
END Include
*/


/*
Consruction
*/
TetronimoDB::TetronimoDB(Grid *p_grid)
{
	tetronimo = new Tetronimo(p_grid);
	for(int q=0;q<4;q++)
	{
		dbSpriteWrap(tetronimo->GetSquares()[q], tetronimo->GetImageID());
	}
}

void TetronimoDB::MoveToSpawningPosition()
{
	tetronimo->MoveToSpawningPosition();
		for(int q=0;q<4;q++)
	{
		dbSpriteWrap(tetronimo->GetSquares()[q], tetronimo->GetImageID());
	}
}

bool TetronimoDB::CanMoveToSpawningPosition()
{
	return tetronimo->CanMoveToSpawningPosition();
}

int TetronimoDB::GetImageID()
{
	return tetronimo->GetImageID();
}

TetronimoDB::TetronimoDB(Grid *p_grid, int origPosX, int origPosY)
{
	tetronimo = new Tetronimo(p_grid, origPosX, origPosY);
	for(int q=0;q<4;q++)
	{
		dbSpriteWrap(tetronimo->GetSquares()[q], tetronimo->GetImageID());
	}
}

/*
END Consruction
*/

/*
Public Methods
*/
void TetronimoDB::Turn(bool clockwise)
{
	tetronimo->Turn(clockwise);
	for(int q=0;q<4;q++)
	{
		dbSpriteWrap(tetronimo->GetSquares()[q], tetronimo->GetImageID());
	}
}

void TetronimoDB::Move(MoveType movType)
{
	tetronimo->Move(movType);
	for(int q=0;q<4;q++)
	{
		dbSpriteWrap(tetronimo->GetSquares()[q], tetronimo->GetImageID());
	}
}

void TetronimoDB::HardDrop()
{
	while(tetronimo->GetCanMoveDown())
	{
		Move(Down);
	}	
}



bool TetronimoDB::GetCanMoveLeft()
{
	return tetronimo->GetCanMoveLeft();
}
bool TetronimoDB::GetCanMoveRight()
{
	return tetronimo->GetCanMoveRight();
}
bool TetronimoDB::GetCanMoveDown()
{
	return tetronimo->GetCanMoveDown();
}
bool TetronimoDB::GetCanTurnClockwise()
{
	return tetronimo->GetCanTurnClockwise();
}
bool TetronimoDB::GetCanTurnAntiClockwise()
{
	return tetronimo->GetCanTurnAntiClockwise();
}
/*
END Public Methods
*/
/*
Private Methods
*/
void TetronimoDB::dbSpriteWrap(int iID, Point p, int iImage)
{
	dbSprite(iID, p.x, p.y, iImage);
}

void TetronimoDB::dbSpriteWrap(GridSquare g, int iImage)
{
	dbSprite(g.blockNumber, g.x, g.y, iImage);
}


Point * TetronimoDB::GetPoints()
{
	return tetronimo->GetPoints();
	
}

GridSquare * TetronimoDB::GetSquares()
{
	return tetronimo->GetSquares();
	
}


/*
END Private Methods
*/