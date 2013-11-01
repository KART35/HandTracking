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




//*fingers are ordered from thumb to pinkie.


SerialWriter::SerialWriter(std::string COM): ser(asio_serv)
{
	lastFrame = 0;
	try{
		ser.open(COM);

		ser.set_option(serial_port_base::baud_rate(11520));
	} 
	catch(boost::system::system_error e) {
		std::cout<< "Boost error: "<<e.what()<<std::endl;
	}
	catch(std::runtime_error e) {
		std::cout<<"std::runtime error: "<<e.what()<<std::endl;
	}
	catch(std::exception e) {
		std::cout<<e.what()<<std::endl;
	}
}

//FIXME: close file handles before program 
//   exit to avoid BSOD on system shutdown

//TODO: allow for tracking of multiple digits
// each hand will reqire 7 channels minimum

int SerialWriter::loop()
{
	while(1){
		if(leapCont.isConnected()) 
		{
			while(1)
			{
				if(!leapCont.isConnected()){//if we lose connection, pause processing and wait for reconnect.
					break;
				}
				frame = leapCont.frame(); //get the latest frame
				if(frame.id() != lastFrame)     //same frame? skip processing.
				{
					this->process();
				}
			}
		}
		else
		{
			std::cout<<"INFO: Leap not found, waiting for connection."<<std::endl;
			Sleep(1000); 
		}
	}
	return 0;
}

void SerialWriter::process()
{
	
/*
	//std::cout << leftmostY << "   " <<leftmostX<<"   "<<leftmostZ<<std::endl;
	leftmostX = abs(215 +(-1*leftmostX));

	if((leftmostY!=0) && (leftmostX !=0)){	
		unsigned char buf[BUFFSIZE];
		buf[0]=(unsigned int)leftmostY>>24;  //prepare values for transmission
		buf[1]=(unsigned int)leftmostY>>16;  //should probably restructure this 
		buf[2]=(unsigned int)leftmostY>>8;   //to use loops
		buf[3]=(unsigned int)leftmostY;
		buf[4] = '\0';
		buf[5]=(unsigned int)leftmostX>>24;
		buf[6]=(unsigned int)leftmostX>>16;
		buf[7]=(unsigned int)leftmostX>>8;
		buf[8]=(unsigned int)leftmostX;
		buf[9]='\0';
		buf[10]=(unsigned int)leftmostZ>>24;
		buf[11]=(unsigned int)leftmostZ>>16;
		buf[12]=(unsigned int)leftmostZ>>8;
		buf[13]=(unsigned int)leftmostZ;
		buf[14]='\n';
#ifndef NON_DEBUG
		for(int i = 0; i<=BUFFSIZE-1; i++){
			std::cout << (int)buf[i]<<" ";
		}
		std::cout <<std::endl;
#endif //NON_DEBUG
		try{
			boost::asio::write(ser, boost::asio::buffer(buf, sizeof(char[BUFFSIZE]))); //send data
		}
		catch(boost::system::system_error e) {
			std::cout<< "Boost error: "<<e.what()<<std::endl;
		}
		catch(std::runtime_error e) {
			std::cout<<"std::runtime error: "<<e.what()<<std::endl;
		}
		catch(std::exception e) {
			std::cout<<e.what()<<std::endl;
		}
		
	}
	*/
}

