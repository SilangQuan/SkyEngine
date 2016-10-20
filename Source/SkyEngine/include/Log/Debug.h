#pragma once

#include <iostream>  
#include <iomanip>  
#include <fstream>  
#include <string>  
#include <cstdlib>  
#include <stdint.h>  
#include <sstream>
#include <vector>

#include "Math/Vector2.h"  
#include "Math/Vector3.h"  
#include "Math/Quaternion.h"  
#include "Math/Matrix.h"
#include "Core/Color.h"
//#include "Log.h"
#include "MessageLogContext.h"

enum LogType
{
	Info,
	Warning,
	Error,
	Default,
};

class Debug
{
public:
	struct Stream {
		Stream():ss(), space(true), context() {}
		Stream(std::string *s) :ss(""), space(true), context(){}
		std::ostringstream ss;
		bool space;
		MessageLogContext context;
		LogType logType;
	} *stream;

	Debug() : stream(new Stream()) {}
	inline Debug(std::string *s) : stream(new Stream(s)) {}


	Debug(const Debug& r)
	{
		stream = new Stream();
		stream->space = r.stream->space;
		stream->context.copy(r.stream->context);
		stream->logType = r.stream->logType;
	}


	~Debug();
	inline Debug &operator<<(bool t) { stream->ss<<(t ? "true" : "false"); return maybeSpace(); }
	inline Debug &operator<<(float t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(double t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(int t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(int64_t t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(char t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(signed short t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(unsigned short t) { stream->ss << t; return maybeSpace(); }
	inline Debug &operator<<(std::string s) { stream->ss << s; return maybeSpace(); }
	inline Debug &operator<<(const char* c) {
		//cout << "fuck" << endl;
		stream->ss << c; return maybeSpace(); 
	}
	inline Debug &operator<<(Vector2 vec) { stream->ss << "(" << vec.x <<","<< vec.y<<")"; return maybeSpace(); }
	inline Debug &operator<<(Vector3 vec) { stream->ss << "(" << vec.x << "," << vec.y <<"," << vec.z << ")"; return maybeSpace(); }
	inline Debug &operator<<(Vector4 vec) { stream->ss << "(" << vec.x << "," << vec.y << "," << vec.z <<","<< vec.w << ")"; return maybeSpace(); }

	inline Debug &operator<<(Quaternion q) { stream->ss << "(" << q.x << "," << q.y << "," << q.z << "," << q.w << ")"; return maybeSpace(); }
	inline Debug &operator<<(Color c) { stream->ss << "(" << c.a << "," << c.r << "," << c.g << "," << c.b << ")"; return maybeSpace(); }


	inline Debug &space() { stream->space = true; stream->ss << ' '; return *this; }
	inline Debug &nospace() { stream->space = false; return *this; }
	inline Debug &maybeSpace() { if (stream->space) stream->ss << ' '; return *this; }

	inline Debug &operator<<(Matrix4x4 m) 
	{
		stream->ss << "(";
		for (int i = 0; i < 16; i++)
		{
			stream->ss << " " << m[i];
		}
		stream->ss << ")";
		 return maybeSpace();
	}

	template <typename T>
	inline Debug &operator<<(const std::vector<T> &vec)
	{
		stream->ss << '(';
		for (int i = 0; i < vec.size(); ++i) {
			stream->ss << vec.at(i);
			stream->ss << ", ";
		}
		stream->ss << ')';
		return maybeSpace();
	}

	void LogToConsole(LogType type, const MessageLogContext &context, std::string logBuffer);

private:
	static Debug* _instance;
};

