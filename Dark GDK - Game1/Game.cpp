#include <tetris.h>



Game::Game(Point topLeftGridPosition)
{
	_topLeftGridPosition = topLeftGridPosition;
	Init();
}

void Game::Go()
{
		double theta;
		switch(_state)
		{
		case InPlay:
			
			theta = (double)(NUMBER_OF_LEVELS - 1 -level)/(double)(NUMBER_OF_LEVELS-1);
			timerPeriod = MIN_TIMER_PERIOD + (int)(MAX_TIMER_PERIOD)*(1 - sin(acos(theta)));
			lastMoveDown = false;
			hasMoved = false; 
			timerStart = dbTimer();
			stationaryTimerStart = dbTimer(); 
			elapsedTime = 0; 
			stationaryTime = 0; 
			hasHardDropped=false; 
			originallyLanded = !t->GetCanMoveDown();
			
			//PauseCheck();

			//-----Has the tetronimo landed?-----//
			//Enter "move loops" dependents on whether tetronimo has landed
			if(!originallyLanded)
			{
				while(elapsedTime < timerPeriod && !lastMoveDown)
				{
					ParseAndMove(&lastMoveDown, t, &hasMoved, &hasHardDropped);
					dbSync();
					elapsedTime = dbTimer() - timerStart;
				}
			}
			else
				//Tetronimo has landed
			{
				while(elapsedTime < ((5*timerPeriod)/2) && !lastMoveDown && stationaryTime <= timerPeriod) 
				{
					ParseAndMove(&lastMoveDown, t, &hasMoved, &hasHardDropped);
					dbSync();
					//if tetronimo has moved reset the moveTimerStrat
					if(hasMoved)
					{
						stationaryTimerStart = dbTimer();
						hasMoved = false;
					}
					elapsedTime = dbTimer() - timerStart;
					stationaryTime = dbTimer() - stationaryTimerStart;
				}
			}
			//END-----Has the tetronimo landed?-----//

			//-----Parse Results from Move loops-----//
			//Determine how we left the above loops. And move/lock/do nothing the tetronimo as appropriate
			if(hasHardDropped)
			{
				LockAndSpawnNew(g, t, t_Next);
			}
			else
			{
				if(!lastMoveDown)
				{
					if(!originallyLanded)
					{
						if(t->GetCanMoveDown()) 
						{
							if(_state!=Paused)
							{
								t->Move(Down);
							}
						}
					}
					else
					{
						if(stationaryTime > timerPeriod)
						{
							if(!t->GetCanMoveDown()) 
								// the tetronimo has landed
							{
								LockAndSpawnNew(g, t, t_Next);
							}
							else
							{
								//move tetronimo down
								if(_state!=Paused)
								{
									t->Move(Down);
								}
							}
						}
						else
						{
							//enter another (shorter) move loop. Which can be broken when the piece lands
							elapsedTime = 0;
							timerStart = dbTimer();
							while(elapsedTime < timerPeriod && t->GetCanMoveDown() && !lastMoveDown)
							{
								ParseAndMove(&lastMoveDown, t, &hasMoved, &hasHardDropped);
								dbSync();
								elapsedTime = dbTimer() - timerStart;
							}
							if(!t->GetCanMoveDown())
							{
								LockAndSpawnNew(g, t, t_Next);
							}
						}
					}
				}
			}
			//END -----Parse Results from Move loops-----//
		break;
		
		case Complete:
			DBBitmapHelper::GetInstance()->ShowGameCompleteBitmaps(true);
			if(DBBitmapHelper::GetInstance()->IsReStartButtonClicked())
			{
				Init();
				DBBitmapHelper::GetInstance()->UpdateScore(score, _topLeftGridPosition);		
				DBBitmapHelper::GetInstance()->UpdateGoal(goal, _topLeftGridPosition);
				DBBitmapHelper::GetInstance()->UpdateLevel(level, _topLeftGridPosition);
				DBBitmapHelper::GetInstance()->ShowGameCompleteBitmaps(false);
			}
			if(DBBitmapHelper::GetInstance()->IsExitButtonClicked())
			{
				exit(0);
			}
			dbSync();
		break;
		case Over:
			DBBitmapHelper::GetInstance()->ShowGameOverBitmaps(true);
			if(DBBitmapHelper::GetInstance()->IsReStartButtonClicked())
			{
				Init();
				DBBitmapHelper::GetInstance()->UpdateScore(score, _topLeftGridPosition);		
				DBBitmapHelper::GetInstance()->UpdateGoal(goal, _topLeftGridPosition);
				DBBitmapHelper::GetInstance()->UpdateLevel(level, _topLeftGridPosition);
				DBBitmapHelper::GetInstance()->ShowGameOverBitmaps(false);
			}
			if(DBBitmapHelper::GetInstance()->IsExitButtonClicked())
			{
				exit(0);
			}
			dbSync();
		break;
		case Paused:
			PauseCheck();
			dbSleep(20);
		break;
		}
		
}



void Game::LockAndSpawnNew(GridDB *g, TetronimoDB *t, TetronimoDB *t_Next)
{
	int numCompleteLines = g->Update(t->GetSquares());
	int scoreAppend;
	int multiplier;
	*t = *t_Next;
	
	
	t->MoveToSpawningPosition();
	*t_Next = TetronimoDB(g->GetGrid(),NEXTPIECE_X,NEXTPIECE_Y);
	
	if(!t->CanMoveToSpawningPosition())
	{
		_state = Over;
	}
	
	for(int i=0;i<4;i++)
	{
		dbSetSpritePriority(t_Next->GetSquares()[i].blockNumber, 9);
	}
	for(int i=0;i<4;i++)
	{
		dbSetSpritePriority(t->GetSquares()[i].blockNumber, 2);
	}
	if(numCompleteLines>0)
	{
		switch(numCompleteLines)
		{
			case 1:
			multiplier = 40;
			break;
			case 2:
			multiplier = 100;
			break;
			case 3:
			multiplier = 300;
			break;
			case 4:
			multiplier = 1200;
			break;
		}
		
		scoreAppend = multiplier * (level +1);
		numLines = numLines + numCompleteLines;
		level = numLines/NUMBER_LINES_PER_LEVEL;
		goal = NUMBER_LINES_PER_LEVEL - numLines%NUMBER_LINES_PER_LEVEL;
		score = score + scoreAppend;
		
		if(numLines >= (NUMBER_LINES_PER_LEVEL * NUMBER_OF_LEVELS))
		{
			_state = Complete;
		}
		
		DBBitmapHelper::GetInstance()->UpdateScore(score, _topLeftGridPosition);		
		DBBitmapHelper::GetInstance()->UpdateGoal(goal, _topLeftGridPosition);
		
		if(_state == Complete)
		{
			DBBitmapHelper::GetInstance()->DeleteBitmapRange(t_Next->GetSquares()[3].blockNumber);			
		}
		else
		{
			DBBitmapHelper::GetInstance()->UpdateLevel(level, _topLeftGridPosition);
		}
	}
	if(_state == Over)
	{
		DBBitmapHelper::GetInstance()->DeleteBitmapRange(t_Next->GetSquares()[3].blockNumber);
	}
}



void Game::ParseAndMove(bool*lastMoveDown, TetronimoDB *t, bool *hasMoved, bool *hasHardDropped)
{
	int input = ParseInput();

	switch(input)
	{
	case SCANCODE_RIGHT:
		if (t->GetCanMoveRight())
		{
			t->Move(Right);
			*lastMoveDown = false;
			*hasMoved = true;
		}
		break;
	case SCANCODE_LEFT:
		if (t->GetCanMoveLeft())
		{
			t->Move(Left);
			*lastMoveDown = false;
			*hasMoved = true;
		}
		break;
	case SCANCODE_UP:
		if (t->GetCanTurnClockwise())
		{
			t->Turn(true);
			*lastMoveDown = false;
			*hasMoved = true;
		}
		break;
	case SCANCODE_Z:
		if (t->GetCanTurnAntiClockwise())
		{	
			t->Turn(false);
			*lastMoveDown = false;
			*hasMoved = true;
		}
		break;
	case SCANCODE_X:
		if (t->GetCanTurnClockwise() )
		{	
			t->Turn(true);
			*lastMoveDown = false;
			*hasMoved = true;
		}
		break;
	case SCANCODE_DOWN:
		if (t->GetCanMoveDown())
		{	
			t->Move(Down);
			*lastMoveDown = true;
			*hasMoved = true;
		}
		break;
	case SCANCODE_SPACEBAR:
		if (t->GetCanMoveDown())
		{	
			t->HardDrop();
			*lastMoveDown = true;
			*hasHardDropped = true;
		}
		break;
	default:
		break;
	}
}





int Game::ParseInput()
{
	
	int result = -1;
	if(PauseCheck())
	{
		return result;
	}

	//If keys are up then reset the repeatcounts and the down flags for the keys
	//-------------------------------------------------------------------------
	if (!dbUpKey())
	{
		upKeyDown = false;
	}
	if (dbKeyState (SCANCODE_SPACEBAR)!=1)
	{
		spaceBarDown = false;
	}
	if (dbKeyState (SCANCODE_X)!=1)
	{
		xKeyDown = false;
	}
	if (dbKeyState (SCANCODE_Z)!=1)
	{
		zKeyDown = false;
	}
	if (!dbLeftKey())
	{
		leftRepeatCount = 0;
	}
	if (!dbRightKey())
	{
		rightRepeatCount = 0;
	}
	if (!dbDownKey())
	{
		downRepeatCount = 0;
	}
	//-------------------------------------------------------------------------
	if (dbRightKey())
	{
		if(ActionHeldKeyPress(&rightRepeatCount))
		{
			result = SCANCODE_RIGHT;
		}
		rightRepeatCount++;
	}
	if (dbLeftKey())
	{
		if(ActionHeldKeyPress(&leftRepeatCount))
		{
			result = SCANCODE_LEFT;
		}
		leftRepeatCount++;
	}
	if (dbDownKey())
	{	
		if(ActionHeldKeyPress(&downRepeatCount))
		{
			result = SCANCODE_DOWN;
		}
		downRepeatCount++;
	}
	if (dbUpKey() && !upKeyDown)
	{
		upKeyDown = true;
		result =SCANCODE_UP;
	}

	if (dbKeyState (SCANCODE_Z)==1 && !zKeyDown)
	{	
		zKeyDown = true;
		result =SCANCODE_Z;
	}
	if (dbKeyState (SCANCODE_X)==1 && !xKeyDown)
	{	
		xKeyDown = true;
		result = SCANCODE_X;
	}
	if (dbKeyState (SCANCODE_SPACEBAR)==1 && !spaceBarDown)
	{	
		spaceBarDown = true;
		result = SCANCODE_SPACEBAR;
	}
	return result;

}




bool Game::PauseCheck()
{
	GameState newState;
	bool result = false;
	if (dbKeyState (SCANCODE_P)!=1)
	{
		pKeyDown = false;
	}
	if (dbKeyState (SCANCODE_P)==1 && !pKeyDown)
	{	
		pKeyDown = true;
		if(_state==InPlay)
		{
			DBBitmapHelper::GetInstance()->ShowResume(true);
			newState=Paused;
		}
		if(_state==Paused)
		{
			DBBitmapHelper::GetInstance()->ShowResume(false);
			newState=InPlay;
		}
		_state = newState;
		result = true;
	}
	return result;
}
//Determines if a piece should be moved based on how
//long the corresponding key has been pressed down
bool Game::ActionHeldKeyPress( int*repeatCount)
{
	return (*repeatCount==0 || (*repeatCount%3==0 && *repeatCount>10));
}

void Game::Init()
{
	timerPeriod = 750; // the measurement of time used to detrmine time limits for moves
	timerStart = 0; //used to measure the elapsed time
	elapsedTime = 0; //stores elapsed time
	stationaryTimerStart = 0; //used to measure stationaryTime
	stationaryTime = 0; //how long tetronimo has remained stationary
	input; //what sort of input has been received from player
	lastMoveDown; //indicates if last move, moved tetronimo down
	hasMoved = false; //indicates if tetronimo has moved
	originallyLanded; //indicates if tetronimo was originally landed on initial entry into loop
	hasHardDropped = false; //has tetronimo been hard dropped
	//complete = false;	
	_state = InPlay;
	level = 0;
	score = 0;
	goal = 10;
	numLines = 0;
	//Down flags and repeat counts for keys
	//------------------------------------------------
	//bool upKeyDown = false;
	//bool spaceBarDown = false;
	//bool zKeyDown = false;
	//bool xKeyDown = false;
	//pKeyDown = false;
	//int leftRepeatCount = 0;
	//int rightRepeatCount = 0;
	//int downRepeatCount = 0;
	//------------------------------------------------
	
	
	//set up grid
	g = new GridDB(Grid::GRID_SQUARE_LENGTH, Grid::GRID_WIDTH, Grid::GRID_HEIGHT, _topLeftGridPosition);
	g->SetUpSquareArray();

	//set up tetronimo
	t = new TetronimoDB(g->GetGrid());
	t_Next = new TetronimoDB(g->GetGrid(), NEXTPIECE_X,NEXTPIECE_Y);
	for(int i=0;i<4;i++)
	{
		dbSetSpritePriority(t_Next->GetSquares()[i].blockNumber, 9);
	}
	for(int i=0;i<4;i++)
	{
		dbSetSpritePriority(t->GetSquares()[i].blockNumber, 2);
	}
}