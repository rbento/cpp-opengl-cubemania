// Copyright (c) Rodrigo Bento. All Rights Reserved.

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <windows.h>

#include <sstream>
#include <string>

using namespace std;

class Logger
{
public:

	static void outputd(const string& marker, double value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputf(const string& marker, float value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputl(const string& marker, long value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputi(const string& marker, int value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputc(const string& marker, char value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputcs(const string& marker, const char* value) 
	{
		stringstream output;
		output << value;
		log(marker, output.str());
	}

	static void outputs(const string& marker, const string& value) 
	{
		log(marker, value);
	}

	static void outputs(const string& marker, const string& text, const string& value) 
	{
		stringstream output;
		output << text << ": " << value;
		log(marker, output.str());
	}

	static void outputs(const string& marker, const string& text, const int value) 
	{
		stringstream output;
		output << text << ": " << value;
		log(marker, output.str());
	}

	static void msg(const string& message) 
	{
		log("msg", message);
	}

private:

	static void log(const string& marker, const string& value) 
	{
		return;
		//stringstream output;
		//output << marker << ": " << value << endl;
		//OutputDebugStringA(output.str().c_str());
		//output.clear();
	}
};

#endif