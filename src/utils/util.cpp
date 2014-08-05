#include "utils\util.h"
std::string util::itos(long num){
	std::ostringstream ss;
	ss << num;
	return ss.str();
}