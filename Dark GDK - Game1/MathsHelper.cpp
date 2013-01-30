#include <MathsHelper.h> 

int MathsHelper::RoundToNearest(int value, int roundTo)
{
	bool isNegative = false;
	if(value < 0)
	{
		value = value * -1;
		isNegative = true;
	}
	int quotient = value/roundTo;
	int mod = value%roundTo;

	if(quotient == 0)
	{
		if((roundTo - value) <=(roundTo/2))
		{
			value = roundTo;
		}
		else
		{
			value = 0;
		}
	}
	else
	{
		if(mod <(roundTo/2))
		{
			value = value - mod;
		}
		else
		{
			value = value + (roundTo - mod);
		}
	}
	
	if(isNegative)
	{
		value = value * -1;
	}

	return value;
}


MathsHelper::MathsHelper()
{
}