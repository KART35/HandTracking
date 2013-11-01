#include "stdafx.h"

#include <boost\asio.hpp>
#define BUFFSIZE 15
using namespace Leap;
using namespace boost::asio;


class SerialWriter
{ 
	Controller          leapCont;
	Config              leapConf;
	io_service          asio_serv;
	Frame				frame;
	int64_t             lastFrame;
	streambuf			buf;
public:
	SerialWriter(std::string COM);
	int loop();
	void process();
	void getHandData();
	serial_port     ser;
};
