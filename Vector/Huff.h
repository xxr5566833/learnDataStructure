#pragma once
#include "HuffChar.h"
#include "List.h"
#include "BinTree.h"
#include "Bitmap.h"
#define HuffTree BinTree<HuffChar>

typedef List<HuffTree*> HuffForest;

typedef Bitmap HuffCode;
