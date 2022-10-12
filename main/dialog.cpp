#include "dialog.h"

int dialog::dialog(const char* msgs[], int size) {
	int rc;
	do {
		for (int i = 0; i < size; ++i)
			std::cout << msgs[i] << std::endl;
		std::cout << std::endl;
		try {
			io::getInt(rc);
		}
		catch(const std::exception& ex) {
			std::cout << ex.what() << std::endl;
			return 0;
		}
	} while (rc < 0 || rc >= size);
	return rc;
}

int dialog::create(logicalElement& tmp) {
	std::cout << std::endl << "Create:\n1.1.Invertor(default)\n1.2.Input and output clamps\n1.3.Array of clamps" << std::endl << std::endl;
	int ans;
	try {
		io::getInt(ans);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 0;
	}	
	switch(ans) {
		case 1: {
			logicalElement elem{};
			tmp = elem;
			return 0;
		}	
		case 2:{
			int input, output;
			try {
				std::cout << "Input the number of input-clamps:" << std::endl;
				io::getInt(input);
				std::cout << "Input the number of output-clamps:" << std::endl;
				io::getInt(output);
				logicalElement elem{input, output};	
				tmp = elem;
			}	
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		case 3:{
			int size;
			try {
				std::cout << "Input the size of array of clamps:" << std::endl;
				io::getInt(size);
				struct clamp array[size];
				io::setArray(array, size);
				logicalElement elem{array, size};
				tmp = elem;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return 0;
	}
	return 0;
}

int dialog::signal(logicalElement& tmp) {
	std::cout << std::endl << "Create:\n2.1.Set all signals in logical element\n2.2.Set a signal of a clamp\n2.3.Get a signal of a clamp" << std::endl;
	int ans;
	try {
		io::getInt(ans);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 0;
	}	
	switch(ans) {
		case 1:{
			try {
				std::cout << tmp;
				tmp.setSignal();
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		case 2:{ 
			char signal;
			int number;
			try {
				std::cout << tmp;
				std::cout << "Input a number of clamp:" << std::endl;
				io::getInt(number);
				getRightSignal(signal);	
				tmp.setSignal(signal, number);
			}	
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		case 3:{
			int number;
			try {
				std::cout << tmp;
				std::cout << "Input a number of clamp:" << std::endl;
				io::getInt(number);
				char ans = tmp.getSignal(number);
				std::cout << "Signal of clamp#" << number << " is:" << ans << std::endl; 
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return 0;
	}
	return 0;
}

int dialog::connection(logicalElement& tmp) {
	std::cout << std::endl << "Create:\n3.1.Add a new connection\n3.2.Delete a connection" << std::endl;
	int ans;
	try {
		io::getInt(ans);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return 0;
	}	
	switch(ans) {
		case 1:{
			int from, to;
			try {
				std::cout << tmp;
				std::cout << "Input a number of clamp, which you want to connect to another clamp:" << std::endl;
				io::getInt(from);
				std::cout << "Input a number clamp, which you want to be connected with what clamp:" << std::endl;
				io::getInt(to);
				tmp.addConnection(to, from);
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		case 2:{
			int from;
			try {
				std::cout << tmp;
				std::cout << "Input a number of clamp, which latest connection you want to delete:" << std::endl;
				io::getInt(from);
				tmp.deleteConnection(from);
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
			return 0;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return 0;
	}
}

int dialog::show(logicalElement& tmp) {
	std::cout << tmp;
	return 0;
}

int dialog::clamp(logicalElement& tmp) {
	struct clamp new_clamp;
	try {
		io::setClamp(new_clamp, tmp.getCurrsize());
		tmp.addClamp(new_clamp);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
