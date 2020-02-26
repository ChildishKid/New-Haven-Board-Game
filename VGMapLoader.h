#pragma once
#include "VGMap.h"

namespace VGMapLoader {

	void save(VGMap* gameboard, string fileName);

	VGMap* load(string fileName);
}