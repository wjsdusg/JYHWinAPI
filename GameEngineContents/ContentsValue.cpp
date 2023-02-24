#include "ContentsValue.h"

float4 ContentsValue::MapSize = { 600,520 };
int ContentsValue::TileSize = 40;
int ContentsValue::XTileNum = static_cast<int>(MapSize.x / TileSize);
int ContentsValue::YTileNum = static_cast<int>(MapSize.y / TileSize);
