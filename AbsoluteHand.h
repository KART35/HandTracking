#pragma once
#include "stdafx.h"
#include "RelitiveHand.h"
#include "Hand.h"

class AbsoluteHand {

public:
	AbsoluteHand();
	AbsoluteHand(RelitiveHand h);

	void GetData(Leap::Frame frame);

};