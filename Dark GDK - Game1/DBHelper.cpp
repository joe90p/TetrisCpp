#include <tetris.h>

DBHelper* DBHelper::_instance = 0;


int DBHelper::GetImageNumber()
{
	int result = imageNumber;
	imageNumber++;
	if(imageNumber==DUMMY_IMAGE_ID)
	{
		imageNumber++;
	}
	return result;
}

DBHelper::DBHelper()
{
	bitmapNumber = 1;
	imageNumber = 1;
	//set initial imageID values to -1
	_blockCyanImageID = -1;
	_blockYellowImageID = -1;
	_blockPurpleImageID = -1;
	_blockGreenImageID = -1;
	_blockRedImageID = -1;
	_blockBlueImageID = -1;
	_blockOrangeImageID = -1;
	_blockGreyImageID = -1;
	_backgroundImageID = -1;	
	_gridImageID = -1;
	_borderImageID = -1;
	_sideBarImageID = -1;
	_scoreTextImageID = -1;	
	_scoreValueTextImageID = -1;	
	_nextTextImageID = -1;
	_levelTextImageID = -1;
	_levelValueTextImageID = -1;
	_goalTextImageID = -1;
	_goalValueTextImageID = -1;
	_startButtonImageID= -1;
	_restartButtonImageID = -1;
	_exitButtonImageID = -1;
	_gamecompleteImageID = -1;
	_gameoverImageID = -1;
	_resumeImageID = -1;
	_pauseTextImageID = -1;
	//Get Text Images here as seeting them up requires clearing the screen
	GetScoreTextImageID();	
	GetScoreValueTextImageID();
	GetNextTextImageID();
	GetLevelTextImageID();
	GetLevelValueTextImageID();
	GetGoalTextImageID();
	GetGoalValueTextImageID();
	

}

//
//Public Methods
//
DBHelper* DBHelper::GetInstance()
{
	if(_instance==0)
	{
		_instance = new DBHelper;
	}
	return _instance;
}

int DBHelper::GetBitmapNumber()
{
	int result = bitmapNumber;
	bitmapNumber++;
	if(bitmapNumber==DUMMY_BITMAP_ID)
	{
		bitmapNumber++;
	}
	return result;
}

void DBHelper::SetBitmapNumber(int value)
{
	bitmapNumber = value;
}



void DBHelper::SetupGridImage(int gridSquareLength, int gridWidth, int gridLength)
{
	dbCreateBitmap(DUMMY_IMAGE_ID, 300, 500);
	dbInk(dbRGB(14,14,14),dbRGB(14,14,14)); //set ink for foreground and background to dark grey
	dbBox(0,0,(gridWidth*gridSquareLength),(gridLength *gridSquareLength)); //draw box
	dbInk(dbRGB(0,0,0),dbRGB(0,0,0)); //set ink for foreground and background to black
	//Draw grid lines
	for(int i=0; i<gridWidth + 1; i++)
	{
		dbBox((i*gridSquareLength)-1,0,(i*gridSquareLength)+2, (gridLength *gridSquareLength));
	}
	for(int i=0; i<gridLength + 1; i++)
	{
		dbBox(0,(i*gridSquareLength)-1,gridWidth*gridSquareLength,(i*gridSquareLength)+2);
	}
	_gridImageID = GetImageNumber();
	dbGetImage(_gridImageID,0,0,250, 500);
	dbSetCurrentBitmap(0); //put drawing operations back to screen	
}


void DBHelper::SetupBorderImage(int gridSquareLength, int gridWidth, int gridLength, int borderWidth)
{
	int width = (gridSquareLength * gridWidth) + (borderWidth * 2);
	int height = (gridSquareLength * gridLength) + (borderWidth * 2);
	
	dbCreateBitmap(DUMMY_IMAGE_ID, width, height);
	
	dbInk(dbRGB(0,0,0),dbRGB(0,0,0)); //set ink for foreground and background to dark grey
	dbBox(0,0,width,height); //draw box
	dbInk(dbRGB(255,0,255),dbRGB(255,0,255)); //set ink for foreground and background to dark grey
	dbBox(borderWidth,borderWidth,width-borderWidth,height-borderWidth); //draw box
	_borderImageID = GetImageNumber();
	dbGetImage(_borderImageID,0,0,width, height);
	dbSetCurrentBitmap(0); //put drawing operations back to screen	
}



void DBHelper::SetupSideBarImage(int gridSquareLength, int gridLength, int borderWidth, int sideBarWidth)
{
	int height = (gridSquareLength * gridSquareLength) + (2*borderWidth);
	dbCreateBitmap(DUMMY_IMAGE_ID, sideBarWidth, height);
	dbInk(dbRGB(0,0,0),dbRGB(0,0,0)); //set ink for foreground and background to black
	dbBox(0,0,sideBarWidth,height); //draw box
	_sideBarImageID = GetImageNumber();
	dbGetImage(_sideBarImageID,0,0,sideBarWidth, height);
	dbSetCurrentBitmap(0); //put drawing operations back to screen	
}


//Get Image ID's

int DBHelper::GetBlockCyanImageID()
{
	if(_blockCyanImageID==-1)
	{
		_blockCyanImageID = GetImageNumber();
		dbLoadImage("block_cyan.bmp", _blockCyanImageID);
	}
	return _blockCyanImageID;
}

int DBHelper::GetBlockYellowImageID()
{
	if(_blockYellowImageID==-1)
	{
		_blockYellowImageID = GetImageNumber();
		dbLoadImage("block_yellow.bmp", _blockYellowImageID);
	}
	return _blockYellowImageID;
}

int DBHelper::GetBlockPurpleImageID()
{
	if(_blockPurpleImageID==-1)
	{
		_blockPurpleImageID = GetImageNumber();
		dbLoadImage("block_purple.bmp", _blockPurpleImageID);
	}
	return _blockPurpleImageID;
}
int DBHelper::GetBlockGreenImageID()
{
	if(_blockGreenImageID==-1)
	{
		_blockGreenImageID = GetImageNumber();
		dbLoadImage("block_green.bmp", _blockGreenImageID);
	}
	return _blockGreenImageID;
}
int DBHelper::GetBlockRedImageID()
{
	if(_blockRedImageID==-1)
	{
		_blockRedImageID = GetImageNumber();
		dbLoadImage("block_red.bmp", _blockRedImageID);
	}
	return _blockRedImageID;
}
int DBHelper::GetBlockBlueImageID()
{
	if(_blockBlueImageID==-1)
	{
		_blockBlueImageID = GetImageNumber();
		dbLoadImage("block_blue.bmp", _blockBlueImageID);
	}
	return _blockBlueImageID;
}
int DBHelper::GetBlockOrangeImageID()
{
	if(_blockOrangeImageID==-1)
	{
		_blockOrangeImageID = GetImageNumber();
		dbLoadImage("block_orange.bmp", _blockOrangeImageID);
	}
	return _blockOrangeImageID;
}
int DBHelper::GetBlockGreyImageID()
{
	if(_blockGreyImageID==-1)
	{
		_blockGreyImageID = GetImageNumber();
		dbLoadImage("block_grey.bmp", _blockGreyImageID);
	}
	return _blockGreyImageID;
}
int DBHelper::GetBackgroundImageID()
{
	if(_backgroundImageID==-1)
	{
		_backgroundImageID = GetImageNumber();
		dbLoadImage("background.jpg", _backgroundImageID);
	}
	return _backgroundImageID;
}




int DBHelper::GetGridImageID(int gridSquareLength, int gridWidth, int gridLength)
{
	if(_gridImageID==-1)
	{
		SetupGridImage( gridSquareLength,  gridWidth,  gridLength);
	}
	return _gridImageID;
}

int DBHelper::GetBorderImageID(int gridSquareLength, int gridWidth, int gridLength, int borderWidth)
{
	if(_borderImageID==-1)
	{
		SetupBorderImage( gridSquareLength,  gridWidth,  gridLength,  borderWidth);
	}
	return _borderImageID;
}

int DBHelper::GetSideBarImageID(int gridSquareLength, int gridLength, int borderWidth, int sideBarWidth)
{
	if(_sideBarImageID==-1)
	{
		SetupSideBarImage( gridSquareLength,  gridLength,  borderWidth,  sideBarWidth);
	}
	return _sideBarImageID;
}

int DBHelper::GetScoreTextImageID()
{
	if(_scoreTextImageID==-1)
	{
		char scoreText[12];
		sprintf(scoreText, "Score:");
		_scoreTextImageID = GetImageNumber();
		SetupSpriteFromText(100,40,scoreText,_scoreTextImageID);
	}
	return _scoreTextImageID;
}

int DBHelper::GetScoreValueTextImageID()
{
	if(_scoreValueTextImageID==-1)
	{
		char scoreValueText[12];
		sprintf(scoreValueText, "0");
		_scoreValueTextImageID = GetImageNumber();
		SetupSpriteFromText(200,25,scoreValueText,_scoreValueTextImageID);
	}
	return _scoreValueTextImageID;
}
int DBHelper::GetGoalValueTextImageID()
{
	if(_goalValueTextImageID==-1)
	{
		char goalValueText[12];
		sprintf(goalValueText, "10"); //really bad
		_goalValueTextImageID = GetImageNumber();
		SetupSpriteFromText(100,25,goalValueText,_goalValueTextImageID);
	}
	return _goalValueTextImageID;
}

int DBHelper::GetNextTextImageID()
{
	if(_nextTextImageID==-1)
	{
		char nextText[12];
		sprintf(nextText, "Next:");
		_nextTextImageID = GetImageNumber();
		SetupSpriteFromText(100,40,nextText,_nextTextImageID);
	}
	return _nextTextImageID;
}



int DBHelper::GetLevelTextImageID()
{
	if(_levelTextImageID==-1)
	{
		char levelText[12];
		sprintf(levelText, "Level:");
		_levelTextImageID = GetImageNumber();
		SetupSpriteFromText(100,40,levelText,_levelTextImageID);
	}
	return _levelTextImageID;
}

int DBHelper::GetLevelValueTextImageID()
{
	if(_levelValueTextImageID == -1)
	{
		char levelValueText[12];
		sprintf(levelValueText, "0");
		_levelValueTextImageID = GetImageNumber();
		SetupSpriteFromText(50,25,levelValueText,_levelValueTextImageID);
	}
	return _levelValueTextImageID;
}
int DBHelper::GetGoalTextImageID()
{
	if(_goalTextImageID==-1)
	{
		char goalText[12];
		sprintf(goalText, "Goal:");
		_goalTextImageID = GetImageNumber();
		SetupSpriteFromText(100,40,goalText,_goalTextImageID);
	}
	return _goalTextImageID;
}




int DBHelper::GetStartButtonImageID()
{
	if(_startButtonImageID==-1)
	{
		_startButtonImageID = GetImageNumber();
		dbLoadImage("start.bmp", _startButtonImageID);
		
	}
	return _startButtonImageID;
}

int DBHelper::GetRestartButtonImageID()
{
	if(_restartButtonImageID==-1)
	{
		_restartButtonImageID = GetImageNumber();
		dbLoadImage("restart.bmp", _restartButtonImageID);
		
	}
	return _restartButtonImageID;
}
int DBHelper::GetExitButtonImageID()
{
	if(_exitButtonImageID==-1)
	{
		_exitButtonImageID = GetImageNumber();
		dbLoadImage("exit.bmp", _exitButtonImageID);
		
	}
	return _exitButtonImageID;
}
int DBHelper::GetGameCompleteImageID()
{
	if(_gamecompleteImageID==-1)
	{
		_gamecompleteImageID = GetImageNumber();
		dbLoadImage("gamecomplete.bmp", _gamecompleteImageID);
		
	}
	return _gamecompleteImageID;
}
int DBHelper::GetGameOverImageID()
{
	if(_gameoverImageID==-1)
	{
		_gameoverImageID = GetImageNumber();
		dbLoadImage("gameover.bmp", _gameoverImageID);
		
	}
	return _gameoverImageID;
}

int DBHelper::GetResumeImageID()
{
	if(_resumeImageID==-1)
	{
		_resumeImageID = GetImageNumber();
		dbLoadImage("resume.bmp", _resumeImageID);
		
	}
	return _resumeImageID;
}
int DBHelper::GetPauseTextImageID()
{
	if(_pauseTextImageID==-1)
	{
		_pauseTextImageID = GetImageNumber();
		dbLoadImage("pausetext.bmp", _pauseTextImageID);
		
	}
	return _pauseTextImageID;
}
void DBHelper::SetupSpriteFromText(int x, int y, char *text, int imageID)
{
	char* mt = "Manga Temple";
	dbCLS();
	dbInk(dbRGB(16,77,98),dbRGB(16,77,98)); //set ink for foreground and background to dark grey
	dbSetTextFont(mt,1);
	dbSetTextSize ( 28 );
	dbText(0,0,text);
	dbGetImage(imageID,0, 0, x, y, true);
	delete[] mt;
}

void DBHelper::UpdateValueTextImageID(char *text, Point topLeft,int imageID, int oldBitmpNumber, Point size)
{
	char* mt = "Manga Temple";
	dbInk(dbRGB(0,0,0),dbRGB(0,0,0)); //set ink for foreground and background to black
	dbBox(topLeft.x,topLeft.y,topLeft.x+size.x,topLeft.y+size.y); //draw box
	dbInk(dbRGB(16,77,98),dbRGB(16,77,98)); //set ink for foreground and background to dark grey
	//dbSetTextFont(mt, 1); // prob don't need this
	dbSetTextSize (28);
	dbText(topLeft.x,topLeft.y, text);
	dbGetImage(imageID,topLeft.x, topLeft.y, topLeft.x + size.x, topLeft.y + size.y, true);
	delete[] mt;
}
