#pragma once

#include<stdlib.h>
#include<map>
#include"GameObject.h"

class GOList {
public:
	map<std::string, GameObject*> GOList;
};

class SoundList {
public:
	map<std::string, uint32_t> SoundList;
};