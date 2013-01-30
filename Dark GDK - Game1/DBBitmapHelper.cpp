#include <Tetris.h>

DBBitmapHelper* DBBitmapHelper::_instance = 0;

void DBBitmapHelper::DrawBackground(Point topLeftGridPosition, int borderWidth, int sideBarWidth, int gridSquareLength, int gridLength, int gridWidth)
{
	dbSprite(backgroundID, 0 ,0 , DBHelper::GetInstance()->GetBackgroundImageID()); //set back ground
	dbSprite(borderID, topLeftGridPosition.x - borderWidth ,topLeftGridPosition.y - borderWidth, DBHelper::GetInstance()->GetBorderImageID( gridSquareLength,  gridWidth,  gridLength,  borderWidth)); //set back ground
	dbSprite(gridID, topLeftGridPosition.x ,topLeftGridPosition.y , DBHelper::GetInstance()->GetGridImageID( gridSquareLength,  gridWidth,  gridLength)); //set back ground
	dbSprite(sideBarID, topLeftGridPosition.x - borderWidth -sideBarWidth,topLeftGridPosition.y - borderWidth , DBHelper::GetInstance()->GetSideBarImageID( gridSquareLength,  gridLength,  borderWidth,  sideBarWidth)); //set back ground
	dbSprite(levelTextID,topLeftGridPosition.x - borderWidth -sideBarWidth+10,topLeftGridPosition.y - borderWidth+250,DBHelper::GetInstance()->GetLevelTextImageID()); //set level text image
	dbSprite(levelValueTextID,topLeftGridPosition.x - borderWidth -sideBarWidth + 10,topLeftGridPosition.y - borderWidth+275,DBHelper::GetInstance()->GetLevelValueTextImageID()); //set level value text image
	dbSprite(scoreTextID,topLeftGridPosition.x - borderWidth -sideBarWidth+10,topLeftGridPosition.y - borderWidth+5,DBHelper::GetInstance()->GetScoreTextImageID()); //set score text image
	dbSprite(scoreValueTextID,topLeftGridPosition.x - borderWidth -sideBarWidth+110,topLeftGridPosition.y - borderWidth+5,DBHelper::GetInstance()->GetScoreValueTextImageID()); //set score value text image
	dbSprite(nextTextID,topLeftGridPosition.x - borderWidth -sideBarWidth+10,topLeftGridPosition.y - borderWidth+100,DBHelper::GetInstance()->GetNextTextImageID()); //set next text image
	dbSprite(goalTextID,topLeftGridPosition.x - borderWidth -sideBarWidth+10,topLeftGridPosition.y - borderWidth+400,DBHelper::GetInstance()->GetGoalTextImageID()); //set goal text image
	dbSprite(goalValueTextID,topLeftGridPosition.x - Grid::GRID_BORDER_WIDTH -Grid::GRID_SIDEBAR_WIDTH+10,topLeftGridPosition.y - Grid::GRID_BORDER_WIDTH+425,DBHelper::GetInstance()->GetGoalValueTextImageID()); //set goal value text image
	dbSprite(startButtonID,850,100,DBHelper::GetInstance()->GetStartButtonImageID()); //set start button image
	dbSprite(restartButtonID,850,100,DBHelper::GetInstance()->GetRestartButtonImageID()); //set restart button image
	dbSprite(exitButtonID,850,160,DBHelper::GetInstance()->GetExitButtonImageID()); //set exit button image
	dbSprite(gameCompleteID,850,40,DBHelper::GetInstance()->GetGameCompleteImageID()); //set gamecomplete image
	dbSprite(gameOverID,850,40,DBHelper::GetInstance()->GetGameOverImageID()); //set game over image
	dbSprite(pauseTextID,850,40,DBHelper::GetInstance()->GetPauseTextImageID()); //set pauseText image
	dbSprite(resumeID, topLeftGridPosition.x ,topLeftGridPosition.y , DBHelper::GetInstance()->GetResumeImageID()); //set resume image
	
	//set sprite priorities
	dbSetSpritePriority(backgroundID,0);
	dbSetSpritePriority(gridID,1);
	dbSetSpritePriority(borderID,3);
	dbSetSpritePriority(sideBarID,4);
	dbSetSpritePriority(levelTextID,5);
	dbSetSpritePriority(levelValueTextID,5);
	dbSetSpritePriority(scoreTextID,6);
	dbSetSpritePriority(scoreValueTextID,6);
	dbSetSpritePriority(nextTextID,7);
	dbSetSpritePriority(goalTextID,8);
	dbSetSpritePriority(goalValueTextID,8);
	dbSetSpritePriority(startButtonID,9);
	dbSetSpritePriority(restartButtonID,-1);
	dbSetSpritePriority(exitButtonID,-1);
	dbSetSpritePriority(gameCompleteID,-1);
	dbSetSpritePriority(gameOverID,-1);
	dbSetSpritePriority(resumeID,-1);
	dbSetSpritePriority(pauseTextID,99);
}











DBBitmapHelper* DBBitmapHelper::GetInstance()
{
	if(_instance==0)
	{
		_instance = new DBBitmapHelper;
	}
	return _instance;
}



DBBitmapHelper::DBBitmapHelper()
{
	//assign Bitmap ID's
	borderID = DBHelper::GetInstance()->GetBitmapNumber();
	backgroundID = DBHelper::GetInstance()->GetBitmapNumber();
	gridID = DBHelper::GetInstance()->GetBitmapNumber();
	sideBarID = DBHelper::GetInstance()->GetBitmapNumber();
	levelTextID = DBHelper::GetInstance()->GetBitmapNumber();
	levelValueTextID = DBHelper::GetInstance()->GetBitmapNumber();
	nextTextID = DBHelper::GetInstance()->GetBitmapNumber();
	scoreTextID = DBHelper::GetInstance()->GetBitmapNumber();
	scoreValueTextID = DBHelper::GetInstance()->GetBitmapNumber();
	goalTextID = DBHelper::GetInstance()->GetBitmapNumber();
	goalValueTextID = DBHelper::GetInstance()->GetBitmapNumber();
	startButtonID = DBHelper::GetInstance()->GetBitmapNumber();	
	restartButtonID = DBHelper::GetInstance()->GetBitmapNumber();
	exitButtonID = DBHelper::GetInstance()->GetBitmapNumber();
	gameCompleteID = DBHelper::GetInstance()->GetBitmapNumber();
	gameOverID = DBHelper::GetInstance()->GetBitmapNumber();
	resumeID = DBHelper::GetInstance()->GetBitmapNumber();
	pauseTextID = DBHelper::GetInstance()->GetBitmapNumber();
	minBitmapID = DBHelper::GetInstance()->GetBitmapNumber();
	
}


void DBBitmapHelper::UpdateScore(int score, Point _topLeftGridPosition)
{
	Point size1;
	Point topLeftScoreValue;
	size1.x = 200;
	size1.y = 25;
	topLeftScoreValue.x = _topLeftGridPosition.x - Grid::GRID_BORDER_WIDTH - Grid::GRID_SIDEBAR_WIDTH+110;
	topLeftScoreValue.y = _topLeftGridPosition.y - Grid::GRID_BORDER_WIDTH+5;
	char scoreValueText[12];	
	//update score value
	itoa(score,scoreValueText,10);
	DBHelper::GetInstance()->UpdateValueTextImageID(scoreValueText,topLeftScoreValue, DBHelper::GetInstance()->GetScoreValueTextImageID(), scoreValueTextID, size1);
	//scoreValueTextID = DBHelper::GetInstance()->GetBitmapNumber();
	dbSprite(scoreValueTextID,topLeftScoreValue.x,topLeftScoreValue.y,DBHelper::GetInstance()->GetScoreValueTextImageID()); //set score value text image
}

void DBBitmapHelper::UpdateLevel(int level, Point _topLeftGridPosition)
{
	Point size2;
	Point topLeftLevelValue;
	size2.x = 50;
	size2.y = 25;
	topLeftLevelValue.x = _topLeftGridPosition.x - Grid::GRID_BORDER_WIDTH -Grid::GRID_SIDEBAR_WIDTH+10;
	topLeftLevelValue.y = _topLeftGridPosition.y - Grid::GRID_BORDER_WIDTH+275;
	//update level value
	char levelValueText[12];
	itoa(level,levelValueText,10);
	DBHelper::GetInstance()->UpdateValueTextImageID(levelValueText,topLeftLevelValue, DBHelper::GetInstance()->GetLevelValueTextImageID(), levelValueTextID, size2);
	dbSprite(levelValueTextID,topLeftLevelValue.x,topLeftLevelValue.y,DBHelper::GetInstance()->GetLevelValueTextImageID()); //set score value text image
}

void DBBitmapHelper::UpdateGoal(int goal, Point _topLeftGridPosition)
{
	Point size3;
	Point topLeftGoalValue;
	size3.x = 100;
	size3.y = 25;
	topLeftGoalValue.x = _topLeftGridPosition.x - Grid::GRID_BORDER_WIDTH -Grid::GRID_SIDEBAR_WIDTH+10;
	topLeftGoalValue.y = _topLeftGridPosition.y - Grid::GRID_BORDER_WIDTH+425;
	char goalValueText[12];
	//update goal value
	itoa(goal,goalValueText,10);
	DBHelper::GetInstance()->UpdateValueTextImageID(goalValueText,topLeftGoalValue, DBHelper::GetInstance()->GetGoalValueTextImageID(), goalValueTextID, size3);
	//goalValueTextID = DBHelper::GetInstance()->GetBitmapNumber();
	dbSprite(goalValueTextID, topLeftGoalValue.x, topLeftGoalValue.y,DBHelper::GetInstance()->GetGoalValueTextImageID()); //set goal value text image
}




bool DBBitmapHelper::IsStartButtonClicked()
{
	bool result = false;

	if (IsButtonClicked(startButtonID))
	{
		dbSetSpritePriority(startButtonID,-1);
		result = true;
	} 
	return result;     
}

bool DBBitmapHelper::IsReStartButtonClicked()
{
	bool result = false;
	
	if (IsButtonClicked(restartButtonID))
	{
		
		dbSetSpritePriority(restartButtonID,-1);
		result = true;
	} 
	return result;     
}

bool DBBitmapHelper::IsExitButtonClicked()
{
	bool result = false;
	
	if (IsButtonClicked(exitButtonID))
	{
		
		dbSetSpritePriority(exitButtonID,-1);
		result = true;
	} 
	return result;     
}

void DBBitmapHelper::ShowGameOverBitmaps(bool show)
{
	if(show)
	{
		dbSetSpritePriority(restartButtonID,99);
		dbSetSpritePriority(exitButtonID,99);
		dbSetSpritePriority(gameOverID,99);
		dbSetSpritePriority(pauseTextID,-1);
	}
	else
	{
		dbSetSpritePriority(restartButtonID,-1);
		dbSetSpritePriority(exitButtonID,-1);
		dbSetSpritePriority(gameOverID,-1);
		dbSetSpritePriority(pauseTextID,99);
	}     
}

void DBBitmapHelper::ShowGameCompleteBitmaps(bool show)
{
	if(show)
	{
		dbSetSpritePriority(restartButtonID,99);
		dbSetSpritePriority(exitButtonID,99);
		dbSetSpritePriority(gameCompleteID,99);
		dbSetSpritePriority(pauseTextID,-1);
	}
	else
	{
		dbSetSpritePriority(restartButtonID,-1);
		dbSetSpritePriority(exitButtonID,-1);
		dbSetSpritePriority(gameCompleteID,-1);
		dbSetSpritePriority(pauseTextID,99);
	}     
}

bool DBBitmapHelper::IsButtonClicked(int buttonID)
{
	int mouseX = dbMouseX();
	int mouseY = dbMouseY();
	int width = dbSpriteWidth(buttonID);
	int height = dbSpriteHeight(buttonID);
	int x = dbSpriteX(buttonID);
	int y = dbSpriteY(buttonID);
	bool result = false;
	bool inButtonArea = false;

	if (mouseX > x && mouseX <  (x + width))
	{
		if (mouseY > y && mouseY < (y + height))
		{
			inButtonArea = true;
			// The mouse is inside the button.
			// Now check for mouse clicks.
			if(dbMouseClick()==1)
			{
				//WindowsHelper::SetActiveCursor(LoadCursorFromFile("aero_arrow.cur"));
				return true;
			}
		}
	} 
	
	if(inButtonArea)
	{
		WindowsHelper::SetActiveCursor(LoadCursorFromFile("aero_link.cur"));
	}
	//else
	//{
	//	WindowsHelper::SetActiveCursor(LoadCursorFromFile("aero_arrow.cur"));
	//}
	return false; 
}


bool DBBitmapHelper::DeleteBitmapRange(int maxBitmapID)
{

	for(int i=minBitmapID; i<=maxBitmapID;  i++)
	{
		dbDeleteSprite(i);
	} 
	
	DBHelper::GetInstance()->SetBitmapNumber(minBitmapID);
	
	return true; 
}
void DBBitmapHelper::ShowResume(bool show)
{
	if(show)
	{
		dbSetSpritePriority(pauseTextID,-1);
		dbSetSpritePriority(resumeID,99);
	}
	else
	{
		dbSetSpritePriority(pauseTextID,99);
		dbSetSpritePriority(resumeID,-1);
	}
}