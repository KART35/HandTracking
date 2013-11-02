#include "stdafx.h"
#include "RelitiveHand.h"

void RelitiveHand::GetData(Leap::Frame frame)
{
	for(short int i = 0; i<frame.hands().count();i++)
	{
		Leap::Hand hand = frame.hands()[i];
		id = hand.id();
		handXBasis =  hand.palmNormal().cross(hand.direction()).normalized();
        handYBasis = -hand.palmNormal();
        handZBasis = -hand.direction();
        handOrigin =  hand.palmPosition();
        handTransform = Leap::Matrix(handXBasis, handYBasis, handZBasis, handOrigin);
        handTransform = handTransform.rigidInverse();
		for(short int n = 0; n < hand.fingers().count(); n++)
		{
			Leap::Finger fi = hand.fingers()[n];
			Leap::Vector transPos =handTransform.transformPoint(fi.tipPosition());
			Leap::Vector transDir =handTransform.transformDirection(fi.direction());
			fingers[n].id = fi.id();
			fingers[n].pos = transPos.angleTo(hand.direction());
		}
		//which finger is the thumb?
		//we need some extra data for it.
		uint32_t thumbId;
		if(hand.palmNormal().angleTo(Leap::Vector::down()) <= 1.57f) //not palm up
		{
			if(hand.id()==frame.hands().leftmost().id()) //leftmost hand?
			{
				thumbId=hand.fingers().rightmost().id(); // rightmost digit is a thumb
				break;
			} 
			else if (hand.id()==frame.hands().rightmost().id()) //rightmost hand?
			{
				thumbId=hand.fingers().leftmost().id();  // leftmost digit is a thumb
				break;
			} 
			else 
			{
				//not much doing here
			} 
		}
		else //if not down, then up.
		{ 
			if(hand.id()==frame.hands().leftmost().id()) //leftmost hand?
			{
				thumbId=hand.fingers().leftmost().id(); // leftmost digit is a thumb
				break;
			} 
			else if (hand.id()==frame.hands().rightmost().id()) //rightmost hand?
			{
				thumbId=hand.fingers().rightmost().id();  // rightmost digit is a thumb
				break;
			} 
			else 
			{

			}
		}
		this->t.id = thumbId; //now, copy the data
		this->t.x = hand.finger(thumbId).stabilizedTipPosition().x;
		this->t.y = hand.finger(thumbId).stabilizedTipPosition().y;
		this->t.z = hand.finger(thumbId).stabilizedTipPosition().z;
	}
}

void RelitiveHand::PackageData()
{
	uint8_t finger_pack[4];
	ThumbIK();
	//TODO: thumb

	for(char i,k = 0; i<=4; i++)
	{
		float fingerPos = this->fingers[i].pos;
		finger_pack[k]= abs(fingerPos); //max value should only be 180
		k++;
		k++;
		finger_pack[k]=~i; //BIN_NOT(index) for the delimiters
	}
}

void RelitiveHand::ThumbIK()
{
	return;
}

char * RelitiveHand::GetThumbData(){
return 0;
}