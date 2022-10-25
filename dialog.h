#include "dynamic/main/logicalElement.h"

size_t dialog(const char* msgs[], size_t Nmsgs);

namespace board_NS {
	struct board {
		static const size_t size = 10;
		logicalElement array[size];
		size_t currsize = 0;
	};
	
	int create(board& board);
	int deleteEl(board& board);
	int process(board& board);
	int show(board& board);

	void delete_element(board& board, size_t ans);
	void push_element(logicalElement& new_element, board& board);
	void processing_element(board& board, size_t ans);
};

namespace clamps_NS {
	void create(board_NS::board& board, logicalElement& currElement);
	void signal(board_NS::board& board, logicalElement& currElement);
	void connection(board_NS::board& board, logicalElement& currElement);
	void show(board_NS::board& board, logicalElement& currElement);
	void clamp(board_NS::board& board, logicalElement& currElement);
	void compare(board_NS::board& board, logicalElement& currElement);
	void sum(board_NS::board& board, logicalElement& currElement);

	void show_clamp(const logicalElement& currElement, size_t number);
}

namespace io_NS {
	void getIndex(size_t& value);
	void setType(clamp& clamp, size_t i);
	void setSignal(clamp& clamp, size_t i);
	void setClamp(clamp& clamp, size_t i);
	void setArray(clamp array[], size_t size); 

	void getSignal(std::string& str);
	void getRightSignal(char& str);
};