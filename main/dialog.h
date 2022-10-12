#include "logicalElement.h"

namespace dialog {
	int create(logicalElement&);
	int signal(logicalElement&);
	int connection(logicalElement&); 
	int show(logicalElement&);
	int clamp(logicalElement&);

	int dialog(const char* msgs[], int Nmsgs);
};

namespace io {
	void getInt(int& value);
	void setType(clamp& clamp, const int i);
	void setSignal(clamp& clamp, const int i);
	void setClamp(clamp& clamp, const int i);
	void setArray(clamp array[], const int size); 
};