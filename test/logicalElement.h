#pragma once
#include <iostream>
#include <math.h>
#include <limits>

typedef struct clamp { //default = input clamp
		bool isInput = true; //1 - input clamp, 0 - output clamp
		char signal = 'X'; //'1','0' or 'X' 
		int maxConnections;
		int currConnections = 0;
		int connections[3] = {-1}; 
} clamp; 

class logicalElement {
private:
	int currsize = 0;
	clamp clamps[N];

	clamp createDefaultInputClamp();
	clamp createDefaultOutputClamp();
	bool is_equal_clamps(const clamp& first, const clamp& second);
	int is_in_element(const clamp& other);
public:
	logicalElement();
	logicalElement(int num_inputClamps, int num_outputClamps);
	logicalElement(clamp specArr[], int size);
	logicalElement(const logicalElement &other);

	void setSignal();
	void setSignal(char value, int num);
	char getSignal(int num) const;
	int getCurrsize() const;
	void addConnection(int to_clamp, int from_clamp);
	void deleteConnection(int from_clamp);

	void addClamp(clamp& value);

	friend std::ostream& operator<< (std::ostream &c, const logicalElement& value);
	logicalElement& operator= (const logicalElement& other);
	logicalElement& operator+ (const logicalElement& other);
	logicalElement& operator+ (const clamp& other);
	logicalElement& operator- (const logicalElement& other);
	logicalElement& operator- (const clamp& other);
	logicalElement& operator! ();
	bool operator< (const logicalElement& other);
	bool operator> (const logicalElement& other);
	bool operator== (const logicalElement& other);
	bool operator!= (const logicalElement& other);
	bool operator<= (const logicalElement& other);
	bool operator>= (const logicalElement& other);
	void operator-- ();
	const logicalElement operator--() const;
	void operator+= (const logicalElement& other);
	void operator+= (const clamp& other);
	void operator-= (const logicalElement& other);
	void operator-= (const clamp& other);
	clamp operator[] (const int index) const;
};

void getChar(char& value);
void getRightSignal(char& value);