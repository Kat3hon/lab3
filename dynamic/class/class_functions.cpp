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

////////////////////////////////PRIVATE/////////////////////////////////////////////////////////////

bool logicalElement::signalString(const std::string& str) {
	if (str.length() != currsize)
		return false;
	for (size_t i = 0; i < currsize; ++i)
		if (str[i] != '1' and str[i] != '0' and str[i] != 'X')
			return false;
	return true;
}

// int logicalElement::isExistConnection(const clamp& clamp, const size_t from_clamp) {
// 	for (size_t i = 0; i < clamp.currConnections; ++i)
// 		if (clamp.connections[i] == from_clamp)
// 			return i+1;
// 	return -1;	
// }

// struct clamp logicalElement::createDefaultInputClamp(){
// 	clamp value;
// 	value.isInput = true;
// 	value.maxConnections = 1;
// 	return value;
// }

// struct clamp logicalElement::createDefaultOutputClamp() {
// 	clamp value;
// 	value.isInput = false;
// 	value.maxConnections = 3;
// 	return value;
// }

bool logicalElement:: is_equal_clamps(const clamp& first, const clamp& second) const {
	bool flag = false;
	bool signal = first.signal==second.signal;
	bool isInput = first.isInput==second.isInput;
	if (signal&&isInput)
		flag = true;
	bool currConnections = first.currConnections==second.currConnections;
	if (currConnections) {
		bool connections = true;
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
	clamp* tmp = new clamp[2];
	delete clamps;
	clamps = tmp;
	clamp value1(true);
	clamp value2(false);
	clamps[0] = value1;
	clamps[1] = value2;
	currsize++;
	currsize++;
}

logicalElement::logicalElement(size_t num_inputClamps, size_t num_outputClamps) {
	clamp* tmp = new clamp[num_inputClamps+num_outputClamps];
	delete clamps;
	clamps = tmp;
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
	clamp* tmp = new clamp[size];
	delete clamps;
	clamps = tmp;
	for (size_t i = 0; i < size; ++i) {
		currsize++;
		clamps[i] = specArr[i];
	}
}

//когда не подойдет конструктор по умолчанию? (или копирующий оператор =)

logicalElement::logicalElement(const logicalElement &other) {
	clamps = new clamp[other.currsize];
	//std::copy
	for (size_t i = 0; i < other.currsize; ++i)
		tmp[i] = other.clamps[i];
	clamps = tmp;
	currsize = other.currsize;
}

logicalElement::~logicalElement() {
	delete clamps;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//string, никакого ввода в методах

//перегрузить >>, ввод, там не будет вывода

void logicalElement::setSignal(const std::string& signals){
	if (!signalString(signals))
		throw std::invalid_argument("Invalid signal to set.");
	for (size_t i = 0; i < currsize; ++i) {
		clamps[i].signal = signals[i];
	}
}

std::ostream& operator>> (std::ostream &in, logicalElement& value) {
	std::cout << "asdasd\n";
	return in;
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

void logicalElement::setSignal(char value, size_t num) {
	if (num > currsize || num == 0)
		throw std::invalid_argument("Invalid clamp number");
	if (value != '1' and value != '0' and value != 'X')
		throw std::invalid_argument("Invalid value of signal");
	else clamps[num-1].signal = value;
}

char logicalElement::getSignal(size_t num) const {
	if (num == 0 || num > currsize)
		throw std::invalid_argument("Invalid clamp number");
	return clamps[num-1].signal;
}

size_t logicalElement::getCurrsize() const {
	return currsize;
}

// void logicalElement::addConnection(logicalElement& to_logElement, const size_t to_clamp, const size_t from_clamp) {
// 	if (from_clamp == 0 || from_clamp > currsize)
// 		throw std::invalid_argument("Invalid clamp number (from).");
// 	if (to_clamp == 0 || to_clamp > currsize)
// 		throw std::invalid_argument("Invalid clamp number (to).");
// 	if (to_clamp == from_clamp)
// 		throw std::invalid_argument("Can not connect clamp with itself.");

// 	if (clamps[from_clamp-1].currConnections == clamps[from_clamp-1].maxConnections ||
// 		to_logElement.clamps[to_clamp-1].currConnections == to_logElement.clamps[to_clamp-1].maxConnections)
// 		throw std::runtime_error("Can not add another connection, clamp's array of connections is already full!");

// 	clamps[from_clamp-1].connections[clamps[from_clamp-1].currConnections] = to_clamp;
// 	to_logElement.clamps[to_clamp-1].connections[to_logElement.clamps[to_clamp-1].currConnections] = from_clamp;
	
// 	(clamps[from_clamp-1].currConnections)++;
// 	(to_logElement.clamps[to_clamp-1].currConnections)++;

// 	to_logElement.clamps[to_clamp-1].signal = clamps[from_clamp-1].signal;
// }

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
	if (isInput == true)
		num_connection = 1;
	else num_connection = 3;					
}

void logicalElement::addConnection(logicalElement& other, const bool isInput) {
	if (&other == this)
		throw std::runtime_error("Can not connect the same elements");
	size_t clamp_from = 0, connection_from = 0;
	findEmptyConnection(clamp_from, connection_from, isInput);
	size_t flag;
	if (isInput == true)
		flag = 1;
	else flag = 3;
	if (connection_from == flag)
		throw std::runtime_error("The connecting element is already full.");
	size_t clamp_to = 0, connection_to = 0;
	other.findEmptyConnection(clamp_to, connection_to, !isInput);
	if (!isInput == true)
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

// void logicalElement::deleteConnection(logicalElement& to_logElement, const size_t from_clamp, const size_t num_clamp_from) {
// 	if (from_clamp == 0 || from_clamp > currsize)
// 		throw std::invalid_argument("Invalid clamp number (from).");
// 	if (clamps[from_clamp-1].currConnections < num_clamp_from)
// 		throw std::runtime_error("There is not that connection in that element.");
// 	int to_clamp = clamps[from_clamp-1].connections[num_clamp_from-1];
// 	int num_clamp_to = isExistConnection(to_logElement.clamps[to_clamp-1], from_clamp);
// 	if (num_clamp_to == -1)
// 		throw std::invalid_argument("That elements are not connected.");

// 	to_logElement.clamps[to_clamp-1].connections[num_clamp_to-1] = -1;
// 	for (size_t i = num_clamp_to-1; i < to_logElement.clamps[to_clamp-1].currConnections-1; ++i)
// 		to_logElement.clamps[to_clamp-1].connections[i] = to_logElement.clamps[to_clamp-1].connections[i+1];
// 	to_logElement.clamps[to_clamp-1].connections[to_logElement.clamps[to_clamp-1].currConnections-1] = -1;

// 	clamps[from_clamp-1].connections[num_clamp_from-1] = -1;
// 	for (size_t i = num_clamp_from-1; i < clamps[from_clamp-1].currConnections-1; ++i)
// 		clamps[from_clamp-1].connections[i] = clamps[from_clamp-1].connections[i+1];
// 	clamps[from_clamp-1].connections[clamps[from_clamp-1].currConnections-1] = -1;
	
// 	(clamps[from_clamp-1].currConnections)--;
// 	(to_logElement.clamps[to_clamp-1].currConnections)--;

// 	if (clamps[from_clamp-1].currConnections == 0)
// 		clamps[from_clamp-1].signal = 'X';
// 	if (to_logElement.clamps[to_clamp-1].currConnections == 0)
// 		clamps[to_clamp-1].signal = 'X';
// }

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

bool logicalElement::found (const size_t arr[], const size_t size, const size_t num_clamp_from) {
	for (size_t i = 0; i < size; ++i) {
		if (num_clamp_from == arr[i])
			return true;
	}	
	return false;
}

void logicalElement::deleteConnection(logicalElement& other) {
	if (&other == this)
		throw std::runtime_error("Can not disconnect the same elements");
	size_t clamp_from, connection_from, clamp_to, connection_to, flag = 0;				
	for (size_t i = 0; i < currsize; ++i)
		for (size_t k = 0; k < clamps[i].currConnections; ++k)
			for (size_t j = 0; j < other.currsize; ++j) {
				//auto found {std::find(std::begin(other.clamps[j].connections), std::end(other.clamps[j].connections), clamps[i].connections[k])};
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

void logicalElement::addClamp(clamp& value) {
	clamp* tmp = new clamp[currsize+1];
	for (size_t i = 0; i < currsize; ++i)
		tmp[i] = clamps[i];
	delete clamps;
	tmp[currsize] = value;
	currsize++;
	clamps = tmp;
}

/////////////////////////////////OPERATORS/////////////////////////////////////////////////

logicalElement& logicalElement::operator= (const logicalElement& other) {
	//перевыделять память, a=b, a=a два случая
	for (size_t i = 0; i < other.currsize; ++i)
		clamps[i] = other.clamps[i];
	currsize = other.currsize;
	return *this;
}

//перемещающий =

//std::copy клеммы

logicalElement logicalElement::operator+ (const logicalElement& other) const {
	logicalElement new_elem{*this};
	clamp* tmp = new clamp[new_elem.currsize+other.currsize];
	for (size_t i = 0; i < new_elem.currsize; ++i)
		tmp[i] = new_elem.clamps[i];
	delete new_elem.clamps;
	new_elem.clamps = tmp;
	for (size_t i = 0; i < other.currsize; ++i) {
		new_elem.clamps[new_elem.currsize+i].isInput = other.clamps[i].isInput;
		new_elem.clamps[new_elem.currsize+i].maxConnections = other.clamps[i].maxConnections;
		new_elem.clamps[new_elem.currsize+i].signal = other.clamps[i].signal;
		new_elem.clamps[new_elem.currsize+i].currConnections = other.clamps[i].currConnections;
		for (size_t j = 0; j < other.clamps[i].currConnections; ++j)
			new_elem.clamps[new_elem.currsize+i].connections[j] = other.clamps[i].connections[j];
	}
	new_elem.currsize += other.currsize;
	return new_elem;
}

logicalElement logicalElement::operator+ (const clamp& other) const {
	logicalElement new_elem{*this};
	clamp* tmp = new clamp[new_elem.currsize+1];
	for (size_t i = 0; i < new_elem.currsize; ++i)
		tmp[i] = new_elem.clamps[i];
	delete new_elem.clamps;
	new_elem.clamps = tmp;
	new_elem.clamps[new_elem.currsize].isInput = other.isInput;
	new_elem.clamps[new_elem.currsize].maxConnections = other.maxConnections;
	new_elem.clamps[new_elem.currsize].signal = other.signal;
	new_elem.clamps[new_elem.currsize].currConnections = other.currConnections;
	for (size_t j = 0; j < other.currConnections; ++j)
		new_elem.clamps[new_elem.currsize].connections[j] = other.connections[j];
	new_elem.currsize++;
	return new_elem;
}

logicalElement& logicalElement:: operator! () {
	for (size_t i = 0; i < currsize; ++i) {
		clamps[i].isInput = !(clamps[i].isInput);
		// for (size_t j = 0; j < clamps[i].currConnections; ++j)
		// 	deleteConnection(i);
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
	clamps = new clamp[currsize+other.currsize];
	for (size_t i = 0; i < other.currsize; ++i) {
		clamps[currsize+i].isInput = other.clamps[i].isInput;
		clamps[currsize+i].maxConnections = other.clamps[i].maxConnections;
		clamps[currsize+i].signal = other.clamps[i].signal;
		clamps[currsize+i].currConnections = other.clamps[i].currConnections;
		for (size_t j = 0; j < other.clamps[i].currConnections; ++j)
			clamps[currsize+i].connections[j] = other.clamps[i].connections[j];
	}
	currsize+=other.currsize;
	return *this;
}

logicalElement& logicalElement::operator+= (const clamp& other) {
	clamp* tmp = new clamp[currsize+1];
	for (size_t i = 0; i < currsize; ++i)
		tmp[i] = clamps[i];
	delete clamps;
	clamps = tmp;
	clamps[currsize].isInput = other.isInput;
	clamps[currsize].maxConnections = other.maxConnections;
	clamps[currsize].signal = other.signal;
	clamps[currsize].currConnections = other.currConnections;
	for (size_t j = 0; j < other.currConnections; ++j)
		clamps[currsize].connections[j] = other.connections[j];
	currsize++;
	return *this;
}

//ссылка на clamp, (не)констрант индексация

clamp logicalElement::operator[] (const size_t index) const {
	if (index >= currsize) 
		throw std::invalid_argument("Invalid index number.");
	return clamps[index];
}

clamp& logicalElement::operator[] (const size_t index) {
	if (index >= currsize) 
		throw std::invalid_argument("Invalid index number.");
	return clamps[index];
}
