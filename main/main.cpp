#include "dialog.h"

int main() {
	std::cout << "Let's start!" << std::endl << std::endl;
	int rc;
	const char* msgs[] = {"\n0.Quit", 
			"1.Create logical element", 
			"2.Change signal in logical element", 
			"3.Change connection in logical element", 
			"4.Show clamps in logical element", 
			"5.Add clamp to logical element"};
	const int Nmsgs = sizeof(msgs)/sizeof(msgs[0]);
	int (*fptr[])(logicalElement&) = {nullptr, dialog::create, dialog::signal, dialog::connection,
										dialog::show, dialog::clamp};
	logicalElement log_element {};									
	while (rc = dialog::dialog(msgs, Nmsgs))
		if(fptr[rc](log_element))
			break;
	std::cout << "That is all! End..." << std::endl;
	return 0;						
}
