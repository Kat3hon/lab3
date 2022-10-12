#include "dialog.h"

void io::getInt(int& value) {
	std::cin >> value;
	if (std::cin.fail()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::invalid_argument("Wrong type.");
	}
	if (std::cin.eof()) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		throw std::runtime_error("End of file! Breaking...");
	}
	return;
}

void io::setType(clamp& clamp, const int i) {
	std::cout << "The clamp #" << i+1 << " is input(1) or output(0):" << std::endl;
	int ans;
	char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		errmsg = "Wrong answer. Try again.";
		getInt(ans);
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

void io::setSignal(clamp& clamp, const int i) {
	std::cout << "Starting an input of signal of clamp #" << i+1 << "..." << std::endl;
	char value;
	getRightSignal(value);
	clamp.signal = value;
}

void io::setClamp(clamp& clamp, const int i) {
	setType(clamp, i);
	setSignal(clamp, i);
}

void io::setArray(clamp array[], const int size) {
	for (int i = 0; i < size; ++i)
		setClamp(array[i], i);
}



