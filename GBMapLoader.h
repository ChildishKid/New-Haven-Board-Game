#pragma once
#include "GBMaps.h"

namespace GBMapLoader {
	
	void save(GBMaps* gameBoard, string fileName);
	GBMaps* load(string fileName);
};

