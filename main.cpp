#include "dialog.h"

int main() {
	std::cout << "Let's start!" << std::endl << std::endl;
	size_t rc;
	const char* msgs[] = {"\n0.Quit", "1.Create new logical element",
						"2.Delete logical element", "3.Process logical element",
						"4.Show all elements"};
	const int Nmsgs = sizeof(msgs)/sizeof(msgs[0]);
	board_NS::board main_board;
	int (*fptr[])(board_NS::board&) = {nullptr, board_NS::create, board_NS::deleteEl, 
						board_NS::process, board_NS::show};								
	while (rc = dialog(msgs, Nmsgs))
		if(fptr[rc](main_board))
			break;
	std::cout << "That is all! End..." << std::endl;
	return 0;						
}
