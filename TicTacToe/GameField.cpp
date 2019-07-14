#include "stdafx.h"
#include "GameField.h"

#include <LaggySdk/Contracts.h>


namespace
{
  void checkIndexIsCorrect(int i_idx, const GameField& i_gameField)
  {
    CONTRACT_EXPECT(0 <= i_idx && i_idx < i_gameField.FieldSize);
  }

} // anonymous NS


GameField::GameField()
{
  resetFields();
}


int GameField::getIndex(int i_x, int i_y) const
{
  CONTRACT_EXPECT(0 <= i_x && i_x < Size);
  CONTRACT_EXPECT(0 <= i_y && i_y < Size);

  int index = i_x + i_y * Size;
  checkIndexIsCorrect(index, *this);

  return index;
}


bool GameField::isFieldOccupied(int i_idx) const
{
  checkIndexIsCorrect(i_idx, *this);
  return getFieldState(i_idx) != FieldState::Unoccupied;
}

bool GameField::isFieldOccupied(int i_x, int i_y) const
{
  return isFieldOccupied(getIndex(i_x, i_y));
}


bool GameField::isFieldUnoccupied(int i_idx) const
{
  checkIndexIsCorrect(i_idx, *this);
  return !isFieldOccupied(i_idx);
}

bool GameField::isFieldUnoccupied(int i_x, int i_y) const
{
  return isFieldUnoccupied(getIndex(i_x, i_y));
}


FieldState GameField::getFieldState(int i_idx) const
{
  checkIndexIsCorrect(i_idx, *this);
  return d_fields.at(i_idx);
}

FieldState GameField::getFieldState(int i_x, int i_y) const
{
  return getFieldState(getIndex(i_x, i_y));
}


void GameField::setFieldState(int i_idx, FieldState i_fieldState)
{
  checkIndexIsCorrect(i_idx, *this);
  d_fields.at(i_idx) = i_fieldState;
}

void GameField::setFieldState(int i_x, int i_y, FieldState i_fieldState)
{
  setFieldState(getIndex(i_x, i_y), i_fieldState);
}


void GameField::resetFields()
{
  for (auto& field : d_fields)
    field = FieldState::Unoccupied;
}

WinState GameField::getWinState() const
{
  auto checkOccupiedByTheSamePlayerIndices = [&](int i_ind1, int i_ind2, int i_ind3)
  {
    return isFieldOccupied(i_ind1) &&
      getFieldState(i_ind1) == getFieldState(i_ind2) &&
      getFieldState(i_ind1) == getFieldState(i_ind3);
  };

  auto getWinnerFromField = [&](int i_ind)
  {
    CONTRACT_EXPECT(isFieldOccupied(i_ind));
    return getFieldState(i_ind) == FieldState::Cross ? WinState::WinnerCross : WinState::WinnerToe;
  };

  const std::vector<std::vector<int>> IndicesToCheck {
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 },

    { 0, 3, 6 },
    { 1, 4, 7 },
    { 2, 5, 8 },

    { 0, 4, 8 },
    { 6, 4, 2 },
  };

  // Look for a winner

  for (const auto& indxList : IndicesToCheck)
  {
    if (checkOccupiedByTheSamePlayerIndices(indxList.at(0), indxList.at(1), indxList.at(2)))
      return getWinnerFromField(indxList.at(0));
  }

  // Check whether there is at least one unoccupied field to continue the game

  for (int idx = 0; idx < Size * Size; ++idx)
  {
    if (isFieldUnoccupied(idx))
      return WinState::NoWinner;
  }

  // No winner and no more unoccupied fields - report a draw

  return WinState::Draw;
}
