#include "dialog.h"

void io_NS::getIndex(size_t& value) {
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Invalid input argument. You should input a size_t value.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file!");
	}
	return;
}

void io_NS::getSignal(std::string& str) {
	std::cin >> str;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Invalid input argument. You should input a string value.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file!");
	}
}

void io_NS::getRightSignal(char& str) {
	std::cin >> str;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Invalid type of input. You should input a char value.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file!");
	}
	if (str != 'X' and str != '1' and str != '0')
		throw std::invalid_argument("Invalid signal. A signal can be only '1', '0' or 'X' (undefined).");
}

void clamps_NS::show_clamp(const logicalElement& currElement, size_t number) {
	if (number-1 >= currElement.getCurrsize())
		throw std::invalid_argument("Invalid clamp number, current element has less clamps.");
	std::cout << "The clamp #" << number << ":" << std::endl;
	if (currElement[number-1].isInput)
		std::cout << "type = input" << std::endl;
	else std::cout << "type = output" << std::endl;
	std::cout << "signal = " << currElement[number-1].signal << std::endl;
	for (size_t j = 0; j < currElement[number-1].currConnections; ++j)
		std::cout << "connection #" << j+1 << ": " << currElement[number-1].connections[j] << std::endl;
	std::cout << std::endl;
}

void io_NS::setType(clamp& clamp, const size_t i) {
	std::cout << "The clamp #" << i+1 << " is input(1) or output(0):";
	size_t ans;
	char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		errmsg = "Wrong answer. Try again.";
		getIndex(ans);
	} while (ans != 1 and ans != 0);
	if (ans == 1) {
		clamp.isInput = true;
		clamp.maxConnections = 1;
	}
	else {
		clamp.isInput = false;
		clamp.maxConnections = 3;
	}
}	

void io_NS::setSignal(clamp& clamp, const size_t i) {
	std::cout << "Starting an input of a signal of clamp #" << i+1 << " (reminder: it can only be '1', '0' or 'X')..." << std::endl;
	char value;
	getRightSignal(value);
	clamp.signal = value;
}

void io_NS::setClamp(clamp& clamp, const size_t i) {
	setType(clamp, i);
	setSignal(clamp, i);
}

void io_NS::setArray(clamp array[], const size_t size) {
	for (size_t i = 0; i < size; ++i)
		setClamp(array[i], i);
}

void board_NS::delete_element(board& board, const size_t ans) {
	if (ans >= board.currsize)
		throw std::invalid_argument("Invalid number of logical element, the board has less elements.");
	for (size_t j = 0; j!= ans && j < board.array[ans].getCurrsize(); ++j) {
		try {
            board.array[ans].deleteConnection(board.array[j]);
        }
        catch (const std::exception& ex) {
            continue;
        }
	}	
	(board.currsize)--;
}

void board_NS::push_element(logicalElement& new_element, board& board) {
	if (board.size == board.currsize)
		throw std::runtime_error("Can not add another logical element, array of logical elements is full!");
	board.array[board.currsize] = new_element;
	(board.currsize)++;
}

void board_NS::processing_element(board& board, const size_t ans){
	if (ans >= board.currsize) 
		throw std::invalid_argument("Invalid number of logical element, the board has less elements.");
	size_t rc;
	const char* msgs[] = {"\n0.Quit", 
			"1.Create a new logical element instead of current element",
			"2.Change a signal in a current logical element",
			"3.Change a connection in a current logical element",
			"4.Show clamps in a current logical element", 
			"5.Add a clamp to a current logical element or show one",
			"6.Compare a current logical element to another",
			"7.Change a current logical element with sum (with options)"};	
	const int Nmsgs = sizeof(msgs)/sizeof(msgs[0]);
	void (*fptr[])(board_NS::board&, logicalElement&) = {nullptr, clamps_NS::create, clamps_NS::signal, clamps_NS::connection,
										clamps_NS::show, clamps_NS::clamp, clamps_NS::compare, clamps_NS::sum};					
	do {
		rc = dialog(msgs, Nmsgs);
		if (rc == 0)
			break;
		fptr[rc](board, board.array[ans]);		
	} while (rc!=0);
}

size_t dialog(const char* msgs[], size_t size) {
	size_t rc;
    char* msg = "";
	do {
        std::cout << msg;
        msg = "Invalid answer\n";
		for (size_t i = 0; i < size; ++i)
			std::cout << msgs[i] << std::endl;
		std::cout << std::endl;
		try {
			io_NS::getIndex(rc);
		}
		catch(const std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return -1;
		}
	} while (rc >= size);
	return rc;
}
