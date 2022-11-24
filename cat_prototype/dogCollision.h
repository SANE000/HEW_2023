#pragma once

#include "dog.h"
#include "block.h"
#include "blockpreview.h"

void UpdateDogCollision();

bool DogCollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);