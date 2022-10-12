#include "logicalElement.h"

void getChar(char& value) {
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Wrong type!");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file! Breaking...");
	}
}

void getRightSignal(char& value) {
	std::cout << "The signal can be: 1 or 0 or X." << std::endl << "Input signal:" << std::endl;
	char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		errmsg = "Wrong answer. Try again.";
		getChar(value);
	} while (value != '1' and value != '0' and value != 'X');
}

////////////////////////////////PRIVATE/////////////////////////////////////////////////////////////

struct clamp logicalElement::createDefaultInputClamp(){
	clamp value;
	value.isInput = true;
	value.maxConnections = 1;
	return value;
}

struct clamp logicalElement::createDefaultOutputClamp() {
	clamp value;
	value.isInput = false;
	value.maxConnections = 3;
	return value;
}

bool logicalElement:: is_equal_clamps(const clamp& first, const clamp& second) {
	bool flag = false;
	bool signal = first.signal==second.signal;
	bool isInput = first.isInput==second.isInput;
	if (signal&&isInput)
		flag = true;
	bool currConnections = first.currConnections==second.currConnections;
	if (currConnections) {
		bool connections = true;
		for (int i = 0; i < first.currConnections; ++i) {
			connections = first.connections[i]==second.connections[i]; 
			if (!connections)
				return false;
		}
	}	
	else return false;	
	return flag;
}

int logicalElement:: is_in_element(const clamp& other) {
	for (int i = 0; i < currsize; ++i) {
		if(is_equal_clamps(clamps[i], other))
			return i;
	}
	return -1;	
}

///////////////////////////////CONSTRUCTORS///////////////////////////////////////////////////

logicalElement::logicalElement() { //inventor
	if (N < 2)
		throw std::invalid_argument("Invalid number of clamps");
	clamps[0] = createDefaultInputClamp();
	clamps[1] = createDefaultOutputClamp();
	currsize++;
	currsize++;
}

logicalElement::logicalElement(int num_inputClamps, int num_outputClamps) {
	if (num_inputClamps+num_outputClamps >= N || N <= 0 || num_inputClamps <= 0 || num_outputClamps <= 0)  {
		throw std::invalid_argument("Invalid number of clamps");
	}
	for (int i = 0; i < num_inputClamps; ++i) {
		clamps[i] = createDefaultInputClamp();
		currsize++;
	}
	for (int i = num_inputClamps; i < num_inputClamps+num_outputClamps; ++i) {
		currsize++;
		clamps[i] = createDefaultOutputClamp();
	}
}

logicalElement::logicalElement(clamp specArr[], int size) {
	if (size > N || N <= 0)
		throw std::invalid_argument("Invalid number of clamps");
	for (int i = 0; i < size; ++i) {
		currsize++;
		clamps[i] = specArr[i];
	}
}

logicalElement::logicalElement(const logicalElement &other) {
	for (int i = 0; i < other.currsize; ++i)
		this->clamps[i] = other.clamps[i];
	this->currsize = other.currsize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void logicalElement::setSignal(){
	for (int i = 0; i < currsize; ++i) {
		std::cout << "Status of clamps #" << i+1 << " (old) = " << clamps[i].signal << std::endl;
		std::cout << "New signal of clamp #" << i+1 << " would be... (0, 1 or X)" << std::endl;
		char value;
		getRightSignal(value);
		clamps[i].signal = value;
	}
}

// void logicalElement::show() const{
// 	for (int i = 0; i < currsize; ++i) {
// 		std::cout << "The clamp #" << i+1 << ":" << std::endl;
// 		if (clamps[i].isInput)
// 			std::cout << "type = input" << std::endl;
// 		else std::cout << "type = output" << std::endl;
// 		std::cout << "signal = " << clamps[i].signal << std::endl;
// 		for (int j = 0; j < clamps[i].currConnections; ++j)
// 			std::cout << "connection #" << j+1 << ": " << clamps[i].connections[j] << std::endl;
// 		std::cout << std::endl;
// 	}
// }

std::ostream& operator<< (std::ostream &c, const logicalElement& value) {
	for (int i = 0; i < value.currsize; ++i) {
		c << "The clamp #" << i+1 << ":" << std::endl;
		if (value.clamps[i].isInput)
			c << "type = input" << std::endl;
		else c << "type = output" << std::endl;
		c << "signal = " << value.clamps[i].signal << std::endl;
		for (int j = 0; j < value.clamps[i].currConnections; ++j)
			c << "connection #" << j+1 << ": " << value.clamps[i].connections[j] << std::endl;
		c << std::endl;
	}
	return c;
}

void logicalElement::setSignal(char value, int num) {
	if (num <= 0 || num > currsize)
		throw std::invalid_argument("Invalid clamp number");
	if (value != '1' and value != '0' and value != 'X')
		throw std::invalid_argument("Invalid value of signal");
	else clamps[num-1].signal = value;
}

char logicalElement::getSignal(int num) const {
	if (num <= 0 || num > currsize)
		throw std::invalid_argument("Invalid clamp number");
	return clamps[num-1].signal;
}

int logicalElement::getCurrsize() const {
	return currsize;
}

void logicalElement::addConnection(int to_clamp, int from_clamp) {
	if (from_clamp <= 0 || from_clamp > currsize)
		throw std::invalid_argument("Invalid clamp number (from)");
	if (to_clamp <= 0 || to_clamp > currsize)
		throw std::invalid_argument("Invalid clamp number (to)");
	if (to_clamp == from_clamp)
		throw std::invalid_argument("Can not connect clamp with itself");

	if (clamps[from_clamp-1].currConnections == clamps[from_clamp-1].maxConnections ||
		clamps[to_clamp-1].currConnections == clamps[to_clamp-1].maxConnections)
		throw std::runtime_error("Can not add another connection");

	clamps[from_clamp-1].connections[clamps[from_clamp-1].currConnections] = to_clamp;
	clamps[to_clamp-1].connections[clamps[to_clamp-1].currConnections] = from_clamp;
	
	(clamps[from_clamp-1].currConnections)++;
	(clamps[to_clamp-1].currConnections)++;

	clamps[to_clamp-1].signal = clamps[from_clamp-1].signal;
}

void logicalElement::deleteConnection(int from_clamp) {
	if (clamps[from_clamp-1].currConnections == 0)
		throw std::runtime_error("Can not delete connection, that is already not exist");
	int to_clamp = clamps[from_clamp-1].connections[clamps[from_clamp-1].currConnections-1];
	clamps[to_clamp-1].connections[clamps[to_clamp-1].currConnections] = -1;
	clamps[from_clamp-1].connections[clamps[from_clamp-1].currConnections] = -1;

	(clamps[from_clamp-1].currConnections)--;
	(clamps[to_clamp-1].currConnections)--;

	if (clamps[from_clamp-1].currConnections == 0)
		clamps[from_clamp-1].signal = 'X';
	if (clamps[to_clamp-1].currConnections == 0)
		clamps[to_clamp-1].signal = 'X';
}

void logicalElement::addClamp(clamp& value) {
	if (currsize == N)
		throw std::invalid_argument("Can not add a clamp");
	clamps[currsize] = value;
	currsize++;
}

/////////////////////////////////OPERATORS/////////////////////////////////////////////////

logicalElement& logicalElement::operator= (const logicalElement& other) {
	for (int i = 0; i < other.currsize; ++i)
		this->clamps[i] = other.clamps[i];
	this->currsize = other.currsize;
	return *this;
}

logicalElement& logicalElement::operator+ (const logicalElement& other) {
	logicalElement new_elem{*this};
	if (new_elem.currsize+other.currsize >= N)
		throw std::invalid_argument("Too many clamps to add");
	for (int i = 0; i < other.currsize; ++i) {
		new_elem.clamps[new_elem.currsize+i+1].isInput = other.clamps[i].isInput;
		new_elem.clamps[new_elem.currsize+i+1].maxConnections = other.clamps[i].maxConnections;
		new_elem.clamps[new_elem.currsize+i+1].signal = other.clamps[i].signal;
		new_elem.clamps[new_elem.currsize+i+1].currConnections = other.clamps[i].currConnections;
		for (int j = 0; j < other.clamps[i].currConnections; ++j)
			new_elem.clamps[new_elem.currsize+i+1].connections[j] = other.clamps[i].connections[j];
		(new_elem.currsize)++;
	}
	return new_elem;
}

logicalElement& logicalElement::operator+ (const clamp& other) {
	logicalElement new_elem{*this};
	if (new_elem.currsize+1 >= N)
		throw std::invalid_argument("Can not add another clamp");
	(new_elem.currsize)++;
	new_elem.clamps[new_elem.currsize].isInput = other.isInput;
	new_elem.clamps[new_elem.currsize].maxConnections = other.maxConnections;
	new_elem.clamps[new_elem.currsize].signal = other.signal;
	new_elem.clamps[new_elem.currsize].currConnections = other.currConnections;
	for (int j = 0; j < other.currConnections; ++j)
		new_elem.clamps[new_elem.currsize].connections[j] = other.connections[j];
	return new_elem;
}

logicalElement& logicalElement::operator- (const logicalElement& other) {
	logicalElement new_elem{*this};
	if (new_elem.currsize-other.currsize < 0)
		throw std::invalid_argument("Too many clamps to substract");
	for (int i = 0; i < other.currsize; --i) {
		int place = is_in_element(other.clamps[i]);
		if (place == -1)
			continue;
		else {
			for (int j = place; j < new_elem.currsize-1; ++j)
				new_elem.clamps[j] = new_elem.clamps[j+1];
			(new_elem.currsize)--;
		}
	}
	return new_elem;
}

logicalElement& logicalElement:: operator- (const clamp& other) {
	logicalElement new_elem{*this};
	if (new_elem.currsize-1 < 0)
		throw std::invalid_argument("Can not substract a clamp");
	int place = is_in_element(other);
	if (place != -1) {
		for (int j = place; j < new_elem.currsize-1; ++j)
			new_elem.clamps[j] = new_elem.clamps[j+1];
		(new_elem.currsize)--;
	}
	return new_elem;	
}

logicalElement& logicalElement:: operator! () {
	for (int i = 0; i < currsize; ++i) {
		clamps[i].isInput = !(clamps[i].isInput);
		for (int j = 0; j < clamps[i].currConnections; ++j)
			deleteConnection(i);
		clamps[i].currConnections = 0;
		if (clamps[i].isInput)
			clamps[i].maxConnections = 1;
		else clamps[i].maxConnections = 3;
		if (clamps[i].signal == '0')
			clamps[i].signal = '1';
		else clamps[i].signal = '0';
	}
	return *this;
}

bool logicalElement:: operator< (const logicalElement& other) {
	if (this->currsize < other.currsize)
		return true;
	return false;
}

bool logicalElement:: operator> (const logicalElement& other) {
	if (this->currsize > other.currsize)
		return true;
	return false;
}

bool logicalElement:: operator== (const logicalElement& other) {
	if (this->currsize != other.currsize)
		return false;
	for (int i = 0; i < this->currsize; ++i)
		if(!(is_equal_clamps(this->clamps[i], other.clamps[i])))
			return false;
	return true;
}

bool logicalElement:: operator!= (const logicalElement& other) {
	if (this->currsize!=other.currsize)
		return true;
	for (int i = 0;i < this->currsize; ++i)
		if(!(is_equal_clamps(this->clamps[i], other.clamps[i])))
			return true;
	return false;
}

bool logicalElement:: operator<= (const logicalElement& other) {
	bool less, equal;
	if (this->currsize < other.currsize)
		return true;
	less = false;
	equal = true;
	if (this->currsize != other.currsize)
		equal = false;
	else {
		for (int i = 0; i < this->currsize; ++i) {
			if(!(is_equal_clamps(this->clamps[i], other.clamps[i]))) {
				equal = false;
				break;
			}	
		}
	}	
	return less||equal;
}

bool logicalElement:: operator>= (const logicalElement& other) {
	bool greater, equal;
	if (this->currsize > other.currsize)
		return true;
	greater = false;
	equal = true;
	if (this->currsize != other.currsize)
		equal = false;
	else {
		for (int i = 0; i < this->currsize; ++i) {
			if(!(is_equal_clamps(this->clamps[i], other.clamps[i]))) {
				equal = false;
				break;
			}	
		}
	}	
	return greater||equal;
}

void logicalElement::operator-- () {
	if (currsize == 0)
		throw std::runtime_error("Can not substract an element without any clamps");
	(currsize)--;
}

const logicalElement logicalElement::operator--() const {
	if (currsize == 0)
		throw std::runtime_error("Can not substract an element without any clamps");
	logicalElement other{*this};
	(other.currsize)--;
	return other;
}

void logicalElement::operator+= (const logicalElement& other) {
	if (this->currsize+other.currsize >= N)
		throw std::invalid_argument("Too many clamps to add");
	for (int i = 0; i < other.currsize; ++i) {
		this->clamps[this->currsize+i+1].isInput = other.clamps[i].isInput;
		this->clamps[this->currsize+i+1].maxConnections = other.clamps[i].maxConnections;
		this->clamps[this->currsize+i+1].signal = other.clamps[i].signal;
		this->clamps[this->currsize+i+1].currConnections = other.clamps[i].currConnections;
		for (int j = 0; j < other.clamps[i].currConnections; ++j)
			this->clamps[this->currsize+i+1].connections[j] = other.clamps[i].connections[j];
		(this->currsize)++;
	}
}

void logicalElement::operator+= (const clamp& other) {
	if (this->currsize+1 >= N)
		throw std::invalid_argument("Can not add another clamp");
	(this->currsize)++;
	this->clamps[this->currsize].isInput = other.isInput;
	this->clamps[this->currsize].maxConnections = other.maxConnections;
	this->clamps[this->currsize].signal = other.signal;
	this->clamps[this->currsize].currConnections = other.currConnections;
	for (int j = 0; j < other.currConnections; ++j)
		this->clamps[this->currsize].connections[j] = other.connections[j];
}

void logicalElement::operator-= (const logicalElement& other) {
	if (this->currsize-other.currsize < 0)
		throw std::invalid_argument("Too many clamps to substract");
	for (int i = 0; i < other.currsize; --i) {
		int place = is_in_element(other.clamps[i]);
		if (place == -1)
			continue;
		else {
			for (int j = place; j < this->currsize-1; ++j)
				this->clamps[j] = this->clamps[j+1];
			(this->currsize)--;
		}
	}
}

void logicalElement:: operator-= (const clamp& other) {
	if (this->currsize-1 < 0)
		throw std::invalid_argument("Can not substract a clamp");
	int place = is_in_element(other);
	if (place != -1) {
		for (int j = place; j < this->currsize-1; ++j)
			this->clamps[j] = this->clamps[j+1];
		(this->currsize)--;
	}	
}

clamp logicalElement::operator[] (const int index) const {
	if (index < 0 || index >= this->currsize) 
		throw std::invalid_argument("Invalid index");
	return this->clamps[index];
}
