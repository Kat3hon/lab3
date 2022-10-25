#pragma once
#include <iostream>
#include <math.h>
#include <limits>
#include <string>

struct clamp { //default = input clamp
		bool isInput; //1 - input clamp, 0 - output clamp
		char signal = 'X'; //'1','0' or 'X' 
		size_t maxConnections; //1 if input clamp else 0
		size_t currConnections = 0;
		size_t connections[3] = {0}; 
		clamp(const bool input_flag);
		clamp();
}; 

class logicalElement {
private:
	size_t currsize = 0;
#ifndef dynamic
	static const size_t N = 10;
	clamp clamps[N];
#elif
    clamp* clamps;
#endif
	void findEmptyConnection(size_t& num_clamp, size_t& num_connection, const bool isInput);
	void shift (const size_t connection, const size_t clamp);
	void emptyCase(const size_t clamp);
	bool signalString(const std::string& str);
	bool is_equal_clamps(const clamp& first, const clamp& second) const;
	int is_in_element(const clamp& other) const;
	bool found (const size_t arr[], const size_t size, const size_t num_clamp_from);

public:
	logicalElement();
	logicalElement(size_t num_inputClamps, size_t num_outputClamps);
	logicalElement(clamp specArr[], size_t size);
	logicalElement(const logicalElement &other);
#ifdef dynamic
    ~logicalElement();
#endif

	void setSignal(const std::string& signals);
	void setSignal(char value, size_t num);
	char getSignal(size_t num) const;
	size_t getCurrsize() const;
	void addConnection(logicalElement& other, const bool isInput);
	void deleteConnection(logicalElement& other);
	void deleteConnection();

	void addClamp(clamp& value);

	friend std::ostream& operator>> (std::ostream &in, logicalElement& value);
	friend std::ostream& operator<< (std::ostream &out, const logicalElement& value);
	logicalElement& operator= (const logicalElement& other);
	logicalElement operator+ (const logicalElement& other) const;
	logicalElement operator+ (const clamp& other) const;
	logicalElement& operator! ();
	bool operator== (const logicalElement& other) const;
	bool operator!= (const logicalElement& other) const;
	logicalElement& operator+= (const logicalElement& other);
	logicalElement& operator+= (const clamp& other);
	clamp operator[] (const size_t index) const;
	clamp& operator[] (const size_t index);
};