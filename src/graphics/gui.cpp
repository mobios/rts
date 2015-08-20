#include "graphics/gui.h"

void gui::flat::fontEngine::setup()
{
	std::vector<std::string> fontfiles;
	util::populateFromDirectory(fontfiles, "resources/*.bff", false);
}