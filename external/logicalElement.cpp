#include "logicalElement.h"

clamp::clamp(const bool input_flag) {
	isInput = input_flag;
	if (isInput)
		maxConnections = 1;
	else maxConnections = 3;
}

clamp::clamp(){
	isInput = true;
	if (isInput)
		maxConnections = 1;
	else maxConnections = 3;
}

bool clamp::isEqualConnections(const size_t arr1[], const size_t arr2[], const size_t size) {
    for (size_t i = 0; i < size; ++i)
        if (arr1[i] != arr2[i])
            return false;
    return true;
}

bool clamp::operator==(const clamp& other) {
    if (isInput == other.isInput && signal == other.signal && currConnections == other.currConnections && isEqualConnections(connections, other.connections, currConnections))
        return true;
    return false;
}

////////////////////////////////PRIVATE/////////////////////////////////////////////////////////////

bool logicalElement::signalString(const std::string& str) const {
	if (str.length() != currsize)
		return false;
	for (size_t i = 0; i < currsize; ++i)
		if (str[i] != '1' and str[i] != '0' and str[i] != 'X')
			return false;
	return true;
}

bool logicalElement:: is_equal_clamps(const clamp& first, const clamp& second) const {
	bool flag = false;
	bool signal = first.signal==second.signal;
	bool isInput = first.isInput==second.isInput;
	if (signal&&isInput)
		flag = true;
	bool currConnections = first.currConnections==second.currConnections;
	if (currConnections) {
		bool connections;
		for (size_t i = 0; i < first.currConnections; ++i) {
			connections = first.connections[i]==second.connections[i]; 
			if (!connections)
				return false;
		}
	}	
	else return false;	
	return flag;
}

int logicalElement:: is_in_element(const clamp& other) const {
	for (size_t i = 0; i < currsize; ++i) {
		if(is_equal_clamps(clamps[i], other))
			return i;
	}
	return -1;	
}

///////////////////////////////CONSTRUCTORS///////////////////////////////////////////////////

logicalElement::logicalElement() { //invertor
#ifdef dynamic
    clamps = new clamp[2];
#endif
	clamp value1(true);
	clamp value2(false);
	clamps[0] = value1;
	clamps[1] = value2;
	currsize++;
	currsize++;
}

logicalElement::logicalElement(size_t num_inputClamps, size_t num_outputClamps) {
#ifdef dynamic
    clamps = new clamp[num_inputClamps+num_outputClamps];
#else
    if (num_inputClamps+num_outputClamps >= N)  {
		throw std::invalid_argument("Invalid number of clamps");
	}
#endif
	for (size_t i = 0; i < num_inputClamps; ++i) {
		clamp value(true);
		clamps[i] = value;
		currsize++;
	}
	for (size_t i = num_inputClamps; i < num_inputClamps+num_outputClamps; ++i) {
		currsize++;
		clamp value(false);
		clamps[i] = value;
	}
}

logicalElement::logicalElement(clamp specArr[], size_t size) {
#ifdef dynamic
    clamps = new clamp[size];
#else
	if (size > N)
		throw std::invalid_argument("Invalid number of clamps");
#endif
	for (size_t i = 0; i < size; ++i) {
		currsize++;
		clamps[i] = specArr[i];
	}
}

//копирующий
logicalElement::logicalElement(const logicalElement &other) {
#ifdef dynamic
    clamps = new clamp[other.currsize];
#endif
	for (size_t i = 0; i < other.currsize; ++i)
		clamps[i] = other.clamps[i];
	currsize = other.currsize;
}
#ifdef dynamic
//перемещающий
logicalElement::logicalElement(logicalElement&& other) {
    currsize = other.currsize;
    clamps = other.clamps;
    other.currsize = 0;
    other.clamps = nullptr;
}

logicalElement:: ~logicalElement() {
    delete[] clamps;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////

void logicalElement::setSignal(const std::string& signals){
	if (!signalString(signals))
		throw std::invalid_argument("Invalid signal to set. Whole signal can only consist '1', '0' or 'X' signals.");
	for (size_t i = 0; i < currsize; ++i) {
		clamps[i].signal = signals[i];
	}
}

std::ostream& operator<< (std::ostream &out, const logicalElement& value) {
	for (size_t i = 0; i < value.currsize; ++i) {
		out << "The clamp #" << i+1 << ":" << std::endl;
		if (value.clamps[i].isInput)
			out << "type = input" << std::endl;
		else out << "type = output" << std::endl;
		out << "signal = " << value.clamps[i].signal << std::endl;
		for (size_t j = 0; j < value.clamps[i].currConnections; ++j)
			out << "connection #" << j+1 << ": " << value.clamps[i].connections[j] << std::endl;
		out << std::endl;
	}
	return out;
}

std::istream& operator>> (std::istream &in, logicalElement& value) {
    logicalElement new_elem(5,0);
    std::string buf;
    in >> buf;
    new_elem.setSignal(buf);
    value = new_elem;
    return in;
}

void logicalElement::setSignal(char value, size_t num) {
	if (num > currsize || num == 0)
		throw std::invalid_argument("Invalid clamp number, the board has less elements (or perhaps you input '0' as an amount).");
	if (value != '1' and value != '0' and value != 'X')
		throw std::invalid_argument("Invalid value of signal. A signal can be '1', '0' or 'X'.");
	else clamps[num-1].signal = value;
}

char logicalElement::getSignal(size_t num) const {
	if (num == 0 || num > currsize)
		throw std::invalid_argument("Invalid clamp number, the board has less elements (or perhaps you input '0' as an amount).");
	return clamps[num-1].signal;
}

size_t logicalElement::getCurrsize() const {
	return currsize;
}

void logicalElement::findEmptyConnection(size_t& num_clamp, size_t& num_connection, const bool isInput) {
	for (size_t i = 0; i < currsize; ++i){
		for (size_t j = 0; j < clamps[i].maxConnections; ++j) {
			if (clamps[i].isInput == isInput && clamps[i].connections[j] == 0) {
				num_clamp = i;
				num_connection = j;
				return;
			}
		}					
	}	
	if (isInput)
		num_connection = 1;
	else num_connection = 3;					
}

void logicalElement::addConnection(logicalElement& other, const bool isInput) {
	if (&other == this)
		throw std::runtime_error("Can not connect the same elements.");
	size_t clamp_from = 0, connection_from = 0;
	findEmptyConnection(clamp_from, connection_from, isInput);
	size_t flag;
	if (isInput)
		flag = 1;
	else flag = 3;
	if (connection_from == flag)
		throw std::runtime_error("The connecting element is already full.");
	size_t clamp_to = 0, connection_to = 0;
	other.findEmptyConnection(clamp_to, connection_to, !isInput);
	if (!isInput)
		flag = 1;
	else flag = 3;
	if (connection_to == flag)
		throw std::runtime_error("The attachable element is already full.");
	
	other.clamps[clamp_to].signal = clamps[clamp_from].signal;
	other.clamps[clamp_to].connections[connection_to] = clamp_from+1;
	clamps[clamp_from].connections[connection_from] = clamp_to+1;

	(clamps[clamp_from].currConnections)++;
	(other.clamps[clamp_to].currConnections)++;
}

void logicalElement::shift (const size_t connection, const size_t clamp) {
	for (size_t i = connection; i < clamps[clamp].currConnections-1; ++i) {
		clamps[clamp].connections[i] = clamps[clamp].connections[i+1];
	}
	clamps[clamp].connections[clamps[clamp].currConnections-1] = 0;
}

void logicalElement::emptyCase(const size_t clamp) {
	if (clamps[clamp].currConnections == 0)
		clamps[clamp].signal = 'X';
}

bool logicalElement::found (const size_t arr[], const size_t size, const size_t num_clamp_from) const {
	for (size_t i = 0; i < size; ++i) {
		if (num_clamp_from == arr[i])
			return true;
	}	
	return false;
}

void logicalElement::deleteConnection(logicalElement& other) {
	if (&other == this)
		throw std::runtime_error("Can not disconnect the same elements.");
	size_t clamp_from, connection_from, clamp_to, connection_to, flag = 0;				
	for (size_t i = 0; i < currsize; ++i)
		for (size_t k = 0; k < clamps[i].currConnections; ++k)
			for (size_t j = 0; j < other.currsize; ++j) {
				if (j+1 == clamps[i].connections[k] && found(other.clamps[j].connections, other.clamps[j].currConnections, i+1)) {
					clamp_from = i;
					connection_from = k;
					clamp_to = j;
					connection_to = clamps[i].connections[k]-1;
					flag = 1;
					break;
				}
			}	
	if (flag == 0)
		throw std::runtime_error("These two elements are not connected.");

	shift(connection_from, clamp_from);
	other.shift(connection_to, clamp_to);

	(clamps[clamp_from].currConnections)--;
	(other.clamps[clamp_to].currConnections)--;

	emptyCase(clamp_from);
	other.emptyCase(clamp_to);
}

#ifdef dynamic
void logicalElement::resize(const size_t new_size) {
    clamp* tmp = new clamp[new_size];
    std::copy(clamps, clamps+currsize, tmp);
    delete[] clamps;
    clamps = tmp;
}
#endif

void logicalElement::addClamp(clamp& value) {
#ifdef dynamic
    resize(currsize+1);
#else
	if (currsize == N)
		throw std::invalid_argument("Can not add a clamp");
#endif
    clamps[currsize] = value;
	currsize++;
}

/////////////////////////////////OPERATORS/////////////////////////////////////////////////

//копирующий
logicalElement& logicalElement::operator= (const logicalElement& other) {
    if (&other == this) return *this;
#ifdef dynamic
    delete[] clamps;
    clamps = new clamp[other.currsize];
#endif
    std::copy(other.clamps, other.clamps + other.currsize, clamps);
	currsize = other.currsize;
	return *this;
}

#ifdef dynamic
//перемещающий
logicalElement& logicalElement::operator=(logicalElement &&other) {
    if (&other == this) return *this;
    delete[] clamps;
    clamps = other.clamps;
    currsize = other.currsize;
    other.currsize = 0;
    other.clamps = nullptr;
    return *this;
}
#endif

logicalElement logicalElement::operator+ (const logicalElement& other) const {
	logicalElement new_elem(*this);
#ifdef dynamic
    new_elem.resize(new_elem.currsize+other.currsize);
#else
	if (new_elem.currsize+other.currsize >= N)
		throw std::invalid_argument("Too many clamps to add.");
#endif
    std::copy(other.clamps,other.clamps+other.currsize,new_elem.clamps + new_elem.currsize);
    new_elem.currsize += other.currsize;
	return new_elem;
}

logicalElement logicalElement::operator+ (const clamp& other) const {
	logicalElement new_elem(*this);
#ifdef dynamic
    new_elem.resize(new_elem.currsize+1);
#else
	if (new_elem.currsize+1 >= N)
		throw std::invalid_argument("Can not add another clamp.");
#endif
    new_elem.clamps[new_elem.currsize] = other;
	new_elem.currsize++;
	return new_elem;
}

logicalElement& logicalElement:: operator! () {
	for (size_t i = 0; i < currsize; ++i) {
		clamps[i].isInput = !(clamps[i].isInput);
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

bool logicalElement:: operator== (const logicalElement& other) const {
	if (currsize != other.currsize)
		return false;
	for (size_t i = 0; i < currsize; ++i)
		if(!(is_equal_clamps(clamps[i], other.clamps[i])))
			return false;
	return true;
}

bool logicalElement:: operator!= (const logicalElement& other) const {
	if (currsize!=other.currsize)
		return true;
	for (size_t i = 0;i < currsize; ++i)
		if(!(is_equal_clamps(clamps[i], other.clamps[i])))
			return true;
	return false;
}

logicalElement& logicalElement::operator+= (const logicalElement& other) {
#ifdef dynamic
    resize(currsize+other.currsize);
#else
	if (currsize+other.currsize >= N)
		throw std::invalid_argument("Too many clamps to add.");
#endif
    std::copy(other.clamps, other.clamps + other.currsize, clamps+currsize);
    currsize+=other.currsize;
	return *this;
}

logicalElement& logicalElement::operator+= (const clamp& other) {
#ifdef dynamic
    resize(currsize+1);
#else
    if (currsize+1 >= N)
		throw std::invalid_argument("Can not add another clamp.");
#endif
    clamps[currsize] = other;
	currsize++;
	return *this;
}

const clamp& logicalElement::operator[] (const size_t index) const {
	if (index >= currsize) 
		throw std::invalid_argument("Invalid index number. Current element has less clamps.");
	std::cout << "const index" << std::endl;
	return clamps[index];
}

clamp& logicalElement::operator[] (const size_t index) {
	if (index >= currsize) 
		throw std::invalid_argument("Invalid index number. Current element has less clamps.");
	std::cout << "not const index" << std::endl;
	return clamps[index];
}
