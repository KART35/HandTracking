#pragma once
#include "stdafx.h"
#include "AbsoluteHand.h"
#include "Hand.h"

class RelitiveHand {
	thumb t;
	finger fingers[5]; //one is actually a thumb
	uint32_t id;

	Leap::Vector handXBasis;
	Leap::Vector handYBasis;
	Leap::Vector handZBasis;
	Leap::Vector handOrigin;

	Leap::Matrix handTransform;

public:
	RelitiveHand();
	RelitiveHand(AbsoluteHand h);
	void GetData(Leap::Frame frame);


};