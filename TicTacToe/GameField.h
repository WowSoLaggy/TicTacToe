#pragma once

#include <array>


enum class FieldState
{
  Unoccupied,
  Cross,
  Toe,
};

enum class WinState
{
  NoWinner,     // No winner so far, but there are free fields
  Draw,         // No winner, and no free fields
  WinnerToe,    // Toe is a winner
  WinnerCross,  // Cross is a winner
};


class GameField
{
public:
  static constexpr int Size = 3;
  static constexpr int FieldSize = Size * Size;

public:
  GameField();

  bool isFieldOccupied(int i_idx) const;
  bool isFieldOccupied(int i_x, int i_y) const;

  bool isFieldUnoccupied(int i_idx) const;
  bool isFieldUnoccupied(int i_x, int i_y) const;

  FieldState getFieldState(int i_idx) const;
  FieldState getFieldState(int i_x, int i_y) const;

  void setFieldState(int i_idx, FieldState i_fieldState);
  void setFieldState(int i_x, int i_y, FieldState i_fieldState);

  void resetFields();
  WinState getWinState() const;

private:
  std::array<FieldState, FieldSize> d_fields;

  int getIndex(int i_x, int i_y) const;
};
