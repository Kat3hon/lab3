#include "dialog.h"

int board_NS::process(board_NS::board& board) {
	board_NS::show(board);
    if (board.currsize == 0)
        return 0;
	std::cout << "Input a number of element to process:" << std::endl;
	size_t ans;
	try {
		io_NS::getIndex(ans);
		processing_element(board, ans-1);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;	
}

int board_NS::create(board_NS::board& board) {
	try {
		logicalElement new_element{};
		clamps_NS::create(board, new_element);
		push_element(new_element, board);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}

int board_NS::deleteEl(board_NS::board& board) {
	board_NS::show(board);
	std::cout << "Input a number of element to delete:" << std::endl;
	size_t ans;
	try {
		io_NS::getIndex(ans);
		delete_element(board, ans-1);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;	
}

int board_NS::show(board_NS::board& board) {
	std::cout << std::endl;
	if (board.currsize == 0) {
		std::cout << "The board is empty!" << std::endl;
		return 0;
	}
	for (size_t i = 0; i < board.currsize; ++i) {
		std::cout << "Logical element #" << i+1 << ":" << std::endl;
		std::cout << board.array[i] << std::endl;
	}
	return 0;
}