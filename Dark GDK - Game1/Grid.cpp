/*
Include
*/
#include <Tetris.h>
/*
END Include
*/

int Grid::blockNumber = 1;

/*
Construction
*/
Grid::Grid(int p_gridSquareLength, int p_gridXNoOfSquares, int p_gridYNoOfSquares, Point _topLeft)
{
	gridSquareLength = p_gridSquareLength;
	gridXNoOfSquares = p_gridXNoOfSquares;
	gridYNoOfSquares = p_gridYNoOfSquares;
	elementCount = 0;
	arrayAllocation = 0;
	squares = NULL;
	mathHelp = new MathsHelper();
	topLeft  = _topLeft;
}

/*
END Construction
*/

/*
Public Methods
*/
bool Grid::IsOccupied(int x, int y)
{
	return GetSquare(x,y).IsOccupied;
}

GridSquare Grid::GetSquare(int x, int y)
{
	int q = 0;
	for(q=0;q<(((gridXNoOfSquares + 2) * (gridYNoOfSquares + 1))-1);q++)
	{
		if(x == squares[q].x && y == squares[q].y)
		{
			break;
		}
	}
	return squares[q];
}

GridSquare *Grid::GetSquarePointer(int x, int y)
{
	//GridSquare gs = GetSquare(x, y);
	
	//return &gs;
	
	int q = 0;
	for(q=0;q<(((gridXNoOfSquares + 2) * (gridYNoOfSquares + 1))-1);q++)
	{
		if(x == squares[q].x && y == squares[q].y)
		{
			break;
		}
	}
	return &squares[q];
}

bool Grid::IsOccupied(Point p)
{
	return IsOccupied(p.x, p.y);
}

void Grid::SetUpSquareArray()
{
	int k = 0;
	int l = 0;
	for(k=-1;k<=gridXNoOfSquares;k++)
	{
		for(l=-1;l<=gridYNoOfSquares;l++)
		{
			GridSquare tSq;
			tSq.x = (k*gridSquareLength) + topLeft.x;
			tSq.y = (l*gridSquareLength) + topLeft.y;
			tSq.IsOccupied = (l==gridYNoOfSquares) || (k==-1) || k==(gridXNoOfSquares);
			AddToArray(tSq);

		}

	}

	int z = arrayAllocation;
}

Point Grid::GetPoint(int x, int y)
{
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

GridSquare Grid::GetNewSquare(int x, int y, bool isOccupied, int blockCount)
{
	GridSquare g;
	g.x = x;
	g.y = y;
	g.IsOccupied = isOccupied;
	g.blockNumber = blockCount;
	g.imageID = -1;
	return g;
}

GridSquare Grid::GetNewSquare(int x, int y, bool isOccupied, int blockCount, int imageID)
{
	GridSquare g;
	g = GetNewSquare(x, y, isOccupied, blockCount);
	g.imageID = imageID;
	return g;
}
int Grid::GetGridSquareLength()
{
	return gridSquareLength;
}
int Grid::GetGridXNoOfSquares()
{
	return gridXNoOfSquares;
}
int Grid::GetGridYNoOfSquares()
{
	return gridYNoOfSquares;
}
Point Grid::GetMovePointLeft(Point p)
{
	MovePointLeft(&p);
	return p;
}
Point Grid::GetMovePointVector(Point p, Point vector)
{
	MovePointVector(&p, vector);
	return p;
}
Point Grid::GetMovePointRight(Point p)
{
	MovePointRight(&p);
	return p;
}
Point Grid::GetMovePointDown(Point p)
{
	MovePointDown(&p);
	return p;
}

Point Grid::GetTurnPoint(Point p, bool clockwise, Point posChange)
{
	TurnPoint(&p, clockwise, posChange);
	return p;
}


int Grid::Update(GridSquare *tetronimoSquares)
{
	int i = 0;
	int q = 0;
	int completeLines;
	for(i=0;i<4;i++)
	{
		for(q=0;q<(((gridXNoOfSquares + 2) * (gridYNoOfSquares + 1))-1);q++)
		{
			if ( tetronimoSquares[i].x == squares[q].x && tetronimoSquares[i].y  == squares[q].y )
			{ 
				squares[q].IsOccupied = true;
				squares[q].blockNumber = tetronimoSquares[i].blockNumber;	
				squares[q].imageID = tetronimoSquares[i].imageID;	
			}
		}
	}
	
	completeLines = CompleteLineCheck();

	blockNumber++;
	
	return completeLines;
}


//Checks for completes lines, removes blocks from completed lines and if necessary moves 
//blocks on other, non-complete lines downn. 
int Grid::CompleteLineCheck()
{
	int y = 0;
	int x = 0;
	bool completeLine = true;
	int completeLineCount = 0;
	GridSquare * gsCurrent;
	GridSquare * gsBelow;
	
	//loop through the lines on the grid
	for(y=gridYNoOfSquares-1;y>=0;y--)
	{
		// loop through each column
		for(x=0;x<gridXNoOfSquares;x++)
		{
			if(!IsOccupied((gridSquareLength * x) + topLeft.x,(gridSquareLength * y) + topLeft.y))
			{
				completeLine = false;
			}
		}	
		//if the line does not contain any unoccupied gridsquares then
		//mark the grid squares in the current line as unoccupied without any blocks in them
		if(completeLine)
		{
			completeLineCount++;
			for(x=0;x<gridXNoOfSquares;x++)
			{
				dbDeleteSprite(GetSquare((gridSquareLength * x) + topLeft.x,(gridSquareLength * y) + topLeft.y).blockNumber);
				gsCurrent = GetSquarePointer((gridSquareLength * x) + topLeft.x,(gridSquareLength * y) + topLeft.y);
				gsCurrent->IsOccupied = false;
				gsCurrent->blockNumber = -1;
				
			}
		}
		else
		{
			//if the number of complete lines is greater than 0 then
			//copy the gridsquares blocknumber and occupied flag in the current line
			// to the line below the current line by *completeLineCount* lines.
			if(completeLineCount > 0)
			{
				for(x=0;x<gridXNoOfSquares;x++)
				{
					gsCurrent = GetSquarePointer((gridSquareLength * x) + topLeft.x,(gridSquareLength * y) + topLeft.y);
					gsBelow = GetSquarePointer((gridSquareLength * x) + topLeft.x, (gridSquareLength * (y + completeLineCount)) + topLeft.y);
					
					gsBelow->IsOccupied = gsCurrent->IsOccupied;
					gsBelow->blockNumber = gsCurrent->blockNumber;
					
					if(dbSpriteExist(gsCurrent->blockNumber))
					{
						dbSprite(gsCurrent->blockNumber,gsBelow->x, gsBelow->y, gsCurrent->imageID); 
					}
					gsCurrent->IsOccupied = false;
					gsCurrent->blockNumber = -1;
				}			
				
			}
		}
		//reset completeLine flag before looping into new line
		completeLine = true;
	}
	return completeLineCount;
}

/*
END Public Methods
*/


/*
Private Methods
*/
int Grid::AddToArray(GridSquare item)
{
	if(elementCount==arrayAllocation)
	{
		if(arrayAllocation==0)
			arrayAllocation = 3;
		else
			arrayAllocation++;

		void *tmp = realloc(squares, (arrayAllocation * sizeof(GridSquare)));

		if(!tmp)
		{
			//BUGGER!
			return (-1);
		}

		squares = (GridSquare*)tmp;
	}
	squares[elementCount] = item;
	elementCount++;
	return elementCount;
}



void Grid::MovePointLeft(Point *p)
{
	p->x = p->x - gridSquareLength;
}
//moves point by a vector ammount
void Grid::MovePointVector(Point *p, Point vector)
{
	p->x = p->x + vector.x;
	p->y = p->y + vector.y;
}
void Grid::MovePointRight(Point *p)
{
	p->x = p->x + gridSquareLength;
}
void Grid::MovePointDown(Point *p)
{
	p->y = p->y + gridSquareLength;
}

void Grid::TurnPoint(Point *p, bool clockwise, Point posChange)
{
	int dummy;

	//shift	
	p->x = p->x - posChange.x - topLeft.x;
	p->y = p->y - posChange.y - topLeft.y;

	//turn
	if(clockwise)
	{
		dummy = p->x;
		p->x = (-1 * p->y) - gridSquareLength;
		p->y = dummy;
	}
	else
	{
		dummy = p->x;
		p->x = p->y;
		p->y = (-1 * dummy) - gridSquareLength;
	}

	//shift back
	p->x = mathHelp->RoundToNearest((p->x + posChange.x + topLeft.x), gridSquareLength);
	p->y = mathHelp->RoundToNearest((p->y + posChange.y + topLeft.y), gridSquareLength);
}




Point Grid::GetGridTopLeft()
{
	return topLeft;
}

/*
END Private Methods
*/