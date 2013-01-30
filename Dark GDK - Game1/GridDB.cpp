#include <tetris.h>

GridDB::GridDB(int p_gridSquareLength, int p_gridXNoOfSquares, int p_gridYNoOfSquares, Point topLeft)
{
	grd = new Grid(p_gridSquareLength, p_gridXNoOfSquares, p_gridYNoOfSquares, topLeft);
}


void GridDB::SetUpSquareArray()
{
	grd->SetUpSquareArray();
}

Point GridDB::GetGridTopLeft()
{
	return grd->GetGridTopLeft();
}

int GridDB::Update(GridSquare *tetronimoSquares)
{
	return grd->Update( tetronimoSquares);
}


int GridDB::GetGridXNoOfSquares()
{
	return grd->GetGridXNoOfSquares();
}
int GridDB::GetGridYNoOfSquares()
{
	return grd->GetGridYNoOfSquares();
}
int GridDB::GetGridSquareLength()
{
	return grd->GetGridSquareLength();
}

Grid *GridDB::GetGrid()
{
	return grd;
}