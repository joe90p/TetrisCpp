/*
Include
*/
#include <Tetris.h>
/*
END Include
*/


/*
Construction
*/
Tetronimo::Tetronimo(Grid *p_grid)
{
	int random = Initialise(p_grid);
	Create(spawnPosX, spawnPosY, random);
}
Tetronimo::Tetronimo(Grid *p_grid, int origPosX, int origPosY)
{
	int random = Initialise(p_grid);
	Create(origPosX, origPosY, random);
}
int Tetronimo::Initialise(Grid *p_grid)
{
	grid = p_grid;
	canMoveLeft = true;
	canMoveRight = true;
	canMoveDown = false;
	Point gridTopLeft = grid->GetGridTopLeft();
	int random = rand();
	random = random%7;
	random++;
	switch(random)
	{
	case 1:
		spawnPosX = (4*grid->GetGridSquareLength()) + gridTopLeft.x;
		spawnPosY = -grid->GetGridSquareLength() + gridTopLeft.y;
		break;
	case 2:
		spawnPosX = (3*grid->GetGridSquareLength()) + gridTopLeft.x;
		spawnPosY = gridTopLeft.y;
		break;
	case 3:
		spawnPosX = 3*grid->GetGridSquareLength() + gridTopLeft.x;
		spawnPosY = gridTopLeft.y;
		break;
	case 4:
		spawnPosX = (3 *grid->GetGridSquareLength()) + gridTopLeft.x;
		spawnPosY = (-1 *grid->GetGridSquareLength()) + gridTopLeft.y;
		break;
	case 5:
		spawnPosX = (3 *grid->GetGridSquareLength()) + gridTopLeft.x;
		spawnPosY = gridTopLeft.y;
		break;
	case 6:
		spawnPosX = 3*grid->GetGridSquareLength() + gridTopLeft.x;
		spawnPosY = gridTopLeft.y;
		break;
	case 7:
		spawnPosX = (3*grid->GetGridSquareLength()) + gridTopLeft.x;
		spawnPosY = -1 *grid->GetGridSquareLength() + gridTopLeft.y;
		break;
	}
	return random;
}



void Tetronimo::Create(int x, int y, int random)
{
	
	switch(random)
	{
	case 1:
		Create1(x, y);
		break;
	case 2:
		Create2(x, y);
		break;
	case 3:
		Create3(x, y);
		break;
	case 4:
		Create4(x, y);
		break;
	case 5:
		Create5(x, y);
		break;
	case 6:
		Create6(x, y);
		break;
	case 7:
		Create7(x, y);
		break;
	}
	
	UpdateMovement();
}


/*
END Construction
*/

/*
Public Methods
*/

void Tetronimo::Turn(bool clockwise)
{
	int i = 0;
	Point posChange;
	Point p;
	Point topLeft = grid->GetGridTopLeft();
	//turn
	for(i=0;i<4;i++)
	{
		if(i==0)
		{
			posChange.x = squares[i].x + turnAxis.x - topLeft.x;
			posChange.y = squares[i].y + turnAxis.y - topLeft.y;;
		}

		p = grid->GetTurnPoint(grid->GetPoint(squares[i].x, squares[i].y), clockwise, posChange);
		squares[i].x = p.x;
		squares[i].y = p.y;
		if(i==0)
		{
			SetTurnAxis(+posChange.x - squares[i].x + topLeft.x, +posChange.y - squares[i].y + topLeft.y);
		}
	}
	UpdateMovement();
}



void Tetronimo::Move(MoveType movType)
{
	int i = 0;
	Point p;
	for(i=0;i<4;i++)
	{
		switch(movType)
		{
		case Left:
			p = grid->GetMovePointLeft(grid->GetPoint(squares[i].x, squares[i].y));
			squares[i].x = p.x;
			squares[i].y = p.y;
			break;
		case Right:
			p = grid->GetMovePointRight(grid->GetPoint(squares[i].x, squares[i].y));
			squares[i].x = p.x;
			squares[i].y = p.y;
			break;
		case Down:
			p = grid->GetMovePointDown(grid->GetPoint(squares[i].x, squares[i].y));
			squares[i].x = p.x;
			squares[i].y = p.y;
			break;
		}

	}
	UpdateMovement();
}





bool Tetronimo::GetCanMoveLeft()
{
	return canMoveLeft;
}
bool Tetronimo::GetCanMoveRight()
{
	return canMoveRight;
}
bool Tetronimo::GetCanMoveDown()
{
	return canMoveDown;
}
bool Tetronimo::GetCanTurnClockwise()
{
	return canTurnClockwise;
}
bool Tetronimo::GetCanTurnAntiClockwise()
{
	return canTurnAntiClockwise;
}

Point * Tetronimo::GetPoints()
{
	int i;
	for(i=0;i<4;i++)
	{
		points[i] = grid->GetPoint(squares[i].x, squares[i].y);
	}
	return points;

}

GridSquare * Tetronimo::GetSquares()
{
	return squares;

}

int Tetronimo::GetImageID()
{
	return imageID;

}

/*
END Public Methods
*/

/*
Private Methods
*/
//The "O" Tetronimo
void Tetronimo::Create1(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint(grid->GetGridSquareLength(), grid->GetGridSquareLength());
	imageID = DBHelper::GetInstance()->GetBlockYellowImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX, origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);

}

//The "I" Tetronimo
void Tetronimo::Create2(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint(2*grid->GetGridSquareLength(), 0);
	imageID = DBHelper::GetInstance()->GetBlockCyanImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + (2*grid->GetGridSquareLength()), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + (3*grid->GetGridSquareLength()), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);

}


//The "L" Tetronimo
void Tetronimo::Create3(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint((3 *(grid->GetGridSquareLength()/2.0f)), grid->GetGridSquareLength()/2.0f);
	imageID = DBHelper::GetInstance()->GetBlockOrangeImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY , false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX +(2* grid->GetGridSquareLength()), origPosY , false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX +(2* grid->GetGridSquareLength()), origPosY - grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);

}


//The "J" tetronimo
void Tetronimo::Create4(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint((3*grid->GetGridSquareLength())/2.0f, (3*grid->GetGridSquareLength())/2.0f);
	imageID = DBHelper::GetInstance()->GetBlockBlueImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX, origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + (2 *grid->GetGridSquareLength()), origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);

}

//The "T" tetronimo
void Tetronimo::Create5(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint(((3*grid->GetGridSquareLength())/2.0f), grid->GetGridSquareLength()/2.0f);
	imageID = DBHelper::GetInstance()->GetBlockPurpleImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY - grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + (2*grid->GetGridSquareLength()), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
}



// The "S" tetronimo
void Tetronimo::Create6(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint(3 *((grid->GetGridSquareLength())/2.0f), grid->GetGridSquareLength()/2.0f);
	imageID = DBHelper::GetInstance()->GetBlockGreenImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY - grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + (2*grid->GetGridSquareLength()), origPosY - grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
}


//The "Z" Tetronimo
void Tetronimo::Create7(int origPosX, int origPosY)
{
	turnAxis = grid->GetPoint((3*grid->GetGridSquareLength())/2.0f, (3*grid->GetGridSquareLength())/2.0f);
	imageID = DBHelper::GetInstance()->GetBlockRedImageID();
	squares[0] = grid->GetNewSquare(origPosX, origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[1] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY, false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[2] = grid->GetNewSquare(origPosX + grid->GetGridSquareLength(), origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
	squares[3] = grid->GetNewSquare(origPosX + (2*grid->GetGridSquareLength()), origPosY + grid->GetGridSquareLength(), false, DBHelper::GetInstance()->GetBitmapNumber(), imageID);
}






void Tetronimo::SetTurnAxis(float x, float y)
{
	turnAxis.x = x;
	turnAxis.y = y;
}


void Tetronimo::UpdateMovement()
{
	int i = 0;
	canMoveLeft = true;
	canMoveRight = true;
	canMoveDown = true;
	canTurnClockwise = true;
	canTurnAntiClockwise = true;
	canMoveDown = true;
	canMoveToSpawningPosition = true;
	Point posChange;
	Point gridTopLeft = grid->GetGridTopLeft();
	Point vector;

	for(i=0;i<4;i++)
	{
		//Turning Test

		//See where square would be after clockwise
		//and anti-clockwise rotations.
		if(i==0)
		{
			posChange.x = squares[i].x + turnAxis.x - gridTopLeft.x;
			posChange.y = squares[i].y + turnAxis.y - gridTopLeft.y;
		}

		if(grid->IsOccupied(grid->GetTurnPoint(grid->GetPoint(squares[i].x, squares[i].y), true, posChange)))
		{
			canTurnClockwise = false;
		}
		
		if(grid->IsOccupied(grid->GetTurnPoint(grid->GetPoint(squares[i].x, squares[i].y), false, posChange)))
		{
			canTurnAntiClockwise = false;
		}

		//END Turning test

		if(grid->IsOccupied(grid->GetMovePointDown(grid->GetPoint(squares[i].x, squares[i].y))))
		{
			canMoveDown = false;
		}

		if(grid->IsOccupied(grid->GetMovePointLeft(grid->GetPoint(squares[i].x, squares[i].y))))
		{
			canMoveLeft = false;
		}
		
		if(grid->IsOccupied(grid->GetMovePointRight(grid->GetPoint(squares[i].x, squares[i].y))))
		{
			canMoveRight = false;
		}
		
		//Can Move to Spawning Pos
		if(i==0)
		{
			vector = grid->GetPoint(spawnPosX - squares[i].x,spawnPosY -  squares[i].y);
		}
		if(grid->IsOccupied(grid->GetMovePointVector(grid->GetPoint(squares[i].x, squares[i].y), vector)))
		{
 			canMoveToSpawningPosition = false;
		}
		
	}
}




bool Tetronimo::CanMoveToSpawningPosition()
{
	UpdateMovement();
	return canMoveToSpawningPosition;
}
void Tetronimo::MoveToSpawningPosition()
{
	Move(spawnPosX, spawnPosY);
}
void Tetronimo::Move(int x, int y)
{
	int i = 0;
	Point p;
	Point vector;
	for(i=0;i<4;i++)
	{
		if(i==0)
		{
			vector = grid->GetPoint(x - squares[i].x,y -  squares[i].y);
		}
		p = grid->GetMovePointVector(grid->GetPoint(squares[i].x, squares[i].y), vector);
		squares[i].x = p.x;
		squares[i].y = p.y;
	}
	UpdateMovement();
}
/*
END Private Methods
*/