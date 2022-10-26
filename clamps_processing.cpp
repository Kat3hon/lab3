#include "dialog.h"

void clamps_NS::create(board_NS::board& board, logicalElement& currElement) {
	std::cout << std::endl << "Create:\n1.Invertor (default, has 1 input clamp and 1 ouput clamp)" << std::endl;
    std::cout << "2.By the numbers of input and output clamps." << std::endl;
    std::cout << "3.By the array of clamps (you will create it firstly)." << std::endl << std::endl;
	size_t ans;
	io_NS::getIndex(ans);
	switch(ans) {
		case 1: {
			logicalElement elem{};
			currElement = elem;
			return;
		}	
		case 2:{
			size_t input, output;
			std::cout << "Input the number of input-clamps:" << std::endl;
			io_NS::getIndex(input);
			std::cout << "Input the number of output-clamps:" << std::endl;
			io_NS::getIndex(output);
			logicalElement elem{input, output};	
			currElement = elem;
			return;
		}	
		case 3:{
			size_t size;
			std::cout << "Input the size of an array of clamps:" << std::endl;
			io_NS::getIndex(size);
			struct clamp array[size];
			io_NS::setArray(array, size);
			logicalElement elem{array, size};
			currElement = elem;
			return;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return;
	}
	return;
}

void clamps_NS::signal(board_NS::board& board, logicalElement& currElement) {
	std::cout << std::endl << "Create:\n1.Set all signals in logical element (or reset them)" << std::endl;
    std::cout << "2.Set some signal of a clamp (or reset it)" << std::endl;
    std::cout << "3.Get a signal of a clamp" << std::endl;
    std::cout << "4.Invert all signals (signal '1'-> signal '0' and signal '0'-> signal '1')" << std::endl << std::endl;
	size_t ans;
	io_NS::getIndex(ans);	
	switch(ans) {
		case 1:{
			std::cout << currElement;
			std::cout << "Input a string of new signals (without any spaces or other separators):" << std::endl; 
			std::string signals;
			io_NS::getSignal(signals);
			currElement.setSignal(signals);
			return;
		}	
		case 2:{ 
			char signal;
			size_t number;
			std::cout << currElement;
			std::cout << "Input a number of clamp:" << std::endl;
			io_NS::getIndex(number);
			std::cout << "Input a signal (it can be only '1', '0' or 'X'):" << std::endl;
			io_NS::getRightSignal(signal);	
			currElement.setSignal(signal, number);
			return;
		}	
		case 3:{
			size_t number;
			std::cout << currElement;
			std::cout << "Input a number of clamp:" << std::endl;
			io_NS::getIndex(number);
			char ans = currElement.getSignal(number);
			std::cout << "Signal of clamp#" << number << " is:" << ans << std::endl; 
			return;
		}	
		case 4: {
			std::cout << currElement << "Invert:" << std::endl;
			std::cout << !currElement;
		}
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return;
	}
	return;
}

void clamps_NS::connection(board_NS::board& board, logicalElement& currElement) {
	std::cout << std::endl << "Create:\n1.Add a new connection\n2.Delete a connection" << std::endl;
	size_t ans;
	io_NS::getIndex(ans);	
	switch(ans) {
		case 1:{
            std::cout << "Correction:" << std::endl << "Adding a new connection means to connect the FIRST FREE clamp of a current element";
            std::cout << "to a FIRST FREE clamp of an element, that you choose." << std::endl;
            std::cout << "So be careful with a signal, that the second element will get. I hope you enjoy that concept of connecting." << std::endl;
            std::cout << "if not, do not forget to write about it! :)" << std::endl << std::endl;
			board_NS::show(board);
			size_t element;
            std::cout << "Input number of the logical element, which you want to connect with a current element:" << std::endl;
			io_NS::getIndex(element);
			if (element >= board.currsize)
				throw std::invalid_argument("Invalid number of logical element, the board has less elements");
			size_t flag;
			bool isInput;
			std::cout << "Connect that element to input (1) or to output (0) clamps:" << std::endl;
			io_NS::getIndex(flag);
			if (flag != 1 && flag != 0)
				throw std::invalid_argument("Invalid type of clamp. Clamp can be only input (1) or output (0).");
			if (flag == 1)
				isInput = true;
			else isInput = false;
			currElement.addConnection(board.array[element-1], isInput);
			return;
		}	
		case 2:{
            std::cout << "Correction:" << std::endl << "Deleting a connection means to delete the connection of FIRST FREE clamp to";
            std::cout << "to the FIRST FREE clamp of element, that you choose. Therefore, if there are several connections";
            std::cout << "between elements, the very first connection will be deleted." << std::endl;
            std::cout << "So be careful not to mix up a deletation. I hope you enjoy that concept of deleting." << std::endl;
            std::cout << "if not, do not forget to write about it! :)";
			board_NS::show(board);
			size_t element;
			std::cout << "Input a number of the logical element, which is connected to a current one (if elements are not connected, it will be an exception):" << std::endl;
			io_NS::getIndex(element);
			if (element >= board.currsize)
				throw std::invalid_argument("Invalid number of logical element, the board has less elements");
			currElement.deleteConnection(board.array[element-1]);
			return;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return;
	}
}


void clamps_NS::show(board_NS::board& board, logicalElement& currElement) {
	std::cout << currElement;
	return;
}

void clamps_NS::clamp(board_NS::board& board, logicalElement& currElement) {
	std::cout << "1.Add a clamp to a current logical element (with method)" << std::endl;
    std::cout << "2.Add a clamp to a current logical element (with operator +)\n3.Show a clamp" << std::endl << std::endl;
	size_t ans;
	io_NS::getIndex(ans);	
	switch(ans) {
		case 1:{
			struct clamp new_clamp;
			io_NS::setClamp(new_clamp, currElement.getCurrsize());
			currElement.addClamp(new_clamp);
			return;
		}	
		case 2:{ 
			struct clamp new_clamp;
			io_NS::setClamp(new_clamp, currElement.getCurrsize());
			currElement+=new_clamp;
			return;
		}	
		case 3:{
			size_t number;
			std::cout << currElement;
			std::cout << "Input a number of clamp:" << std::endl;
			io_NS::getIndex(number);
			clamps_NS::show_clamp(currElement, number);
			return;
		}	
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return;
	}
	return;
}

void clamps_NS::compare(board_NS::board& board, logicalElement& currElement) {
	board_NS::show(board);
	std::cout << "Input a number of a logical element to compare to a current one:" << std::endl;
	size_t ans;
	io_NS::getIndex(ans);
	if (ans >= board.currsize)
		throw std::invalid_argument("Invalid number of logicalElement, the board has less elements.");
	if (currElement == board.array[ans])
		std::cout << "They are equal." << std::endl;
	else std::cout << "They are different." << std::endl;
}

void clamps_NS::sum(board_NS::board& board, logicalElement& currElement) {
	std::cout << "1.Change a current logical element with sum of two another elements\n" << std::endl;
    std::cout << "2.Change a current logical element with a sum of another elements and a clamp" << std::endl;
    std::cout << "3.Add a logical element to a current one" << std::endl << std::endl;
	size_t ans;
	io_NS::getIndex(ans);	
	switch(ans) {
		case 1:{
			board_NS::show(board);
			size_t first, second;
			std::cout << "Input number of the first logical element to add:" << std::endl;
			io_NS::getIndex(first);
			std::cout << "Input number of the second logical element to add:" << std::endl;
			io_NS::getIndex(second);
			if (first >= board.currsize || second >= board.currsize)
				throw std::invalid_argument("Invalid number of logicalElement (first or second), the board has less elements.");
			currElement = board.array[first] + board.array[second];
			return;
		}	
		case 2:{ 
			board_NS::show(board);
			size_t first;
			std::cout << "Input number of the first logical element to add:" << std::endl;
			io_NS::getIndex(first);
			if (first >= board.currsize)
				throw std::invalid_argument("Invalid number of logicalElement, the board has less elements.");
			struct clamp new_clamp;
			io_NS::setClamp(new_clamp, currElement.getCurrsize());
			currElement = board.array[first] + new_clamp;
			return;
		}	
		case 3:{
			board_NS::show(board);
			size_t first;
			std::cout << "Input number of the first logical element to add:" << std::endl;
			io_NS::getIndex(first);
			if (first >= board.currsize)
				throw std::invalid_argument("Invalid number of logicalElement, the board has less elements.");
			currElement+=board.array[first];
			return;
		}
		default:
			std::cout << "Wrong option. Try again." << std::endl;
			return;
	}
	return;
}