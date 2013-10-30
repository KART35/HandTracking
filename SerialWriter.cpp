// SerialWriter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialWriter.h"



int _tmain(int argc, _TCHAR* argv[])
{
	std::string prt(argv[1]);
	std::string baud(argv[2]);
	std::string port(prt.begin(), prt.end());
	SerialWriter serialWriter(port);
	if(serialWriter.ser.is_open() ==false) return-1;
	return serialWriter.loop();
	
}

