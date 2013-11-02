#pragma once
#include "stdafx.h"
#include "Hand.h"

class RelitiveHand {
	thumb t;
	thumb t_out;
	finger fingers[5]; //one is actually a thumb
	uint32_t id;
	char package[14];
	Leap::Vector handXBasis;
	Leap::Vector handYBasis;
	Leap::Vector handZBasis;
	Leap::Vector handOrigin;

	Leap::Matrix handTransform;

public:
	RelitiveHand();
	void GetData(Leap::Frame frame);
	void PackageData();
	char * GetThumbData();
	void ThumbIK();

};