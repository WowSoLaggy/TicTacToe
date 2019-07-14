#include "stdafx.h"
#include "FieldPositions.h"

#include <LaggySdk/Contracts.h>


int getFieldIndex(int i_x, int i_y)
{
  const int xLine0 = 50;
  const int xLine1 = 174;
  const int xLine2 = 290;
  const int xLine4 = 410;

  const int yLine0 = 40;
  const int yLine1 = 164;
  const int yLine2 = 310;
  const int yLine4 = 440;

  if (i_x < xLine0 || xLine4 < i_x || i_y < yLine0 || yLine4 < i_y)
    return -1;

  if (i_y < yLine1)
  {
    if (i_x < xLine1)
      return 0;
    else if (i_x < xLine2)
      return 1;
    else
      return 2;
  }
  else if (i_y < yLine2)
  {
    if (i_x < xLine1)
      return 3;
    else if (i_x < xLine2)
      return 4;
    else
      return 5;
  }
  else
  {
    if (i_x < xLine1)
      return 6;
    else if (i_x < xLine2)
      return 7;
    else
      return 8;
  }

  CONTRACT_ASSERT(false);
}


Sdk::Vector2 getIndexOffset(int i_index)
{
  CONTRACT_EXPECT(0 <= i_index && i_index < 9);

  static const std::array<float, 3> x{ 65, 187, 305 };
  static const std::array<float, 3> y{ 62, 195, 330 };

  return { x.at(i_index % 3), y.at(i_index / 3) };
}
