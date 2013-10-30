#include "stdafx.h"
#include "AbsoluteHand.h"

void AbsoluteHand::GetData(Leap::Frame frame)
{
	for(short int i = 0; i<frame.hands().count();i++)
	{
		Leap::Hand hand = frame.hands()[i];
		for(short int n = 0; n < hand.fingers().count(); n++)
		{

		}
	}
}