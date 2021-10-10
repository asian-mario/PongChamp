#pragma once

#include<stdlib.h>
#include<map>
#include"GameObject.h"

class GOList {
public:
	map<std::string, GameObject*> GOList;
};