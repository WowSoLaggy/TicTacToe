#include "stdafx.h"
#include "App.h"

#include "FieldPositions.h"

#include <LaggyDx/KeyboardState.h>
#include <LaggyDx/MouseState.h>
#include <TicTacToe/GameField.h>


void App::handleKeyboard(const Dx::KeyboardState& i_keyboardState)
{
  if (i_keyboardState.getPressedKeys().Escape)
  {
    d_stopSignal = true;
    return;
  }
}


void App::handleMouse(const Dx::MouseState& i_mouseState)
{
  if (i_mouseState.getLeftButtonState() == Dx::ButtonState::Pressed)
  {
    if (d_isPlayerTurn)
    {
      const int fieldIndex = getFieldIndex(
        i_mouseState.getMousePosition().x,
        i_mouseState.getMousePosition().y);
      if (fieldIndex != -1 && d_gameField->isFieldUnoccupied(fieldIndex))
      {
        d_gameField->setFieldState(fieldIndex, FieldState::Cross);
        setTurn(false);
        checkVictory();
      }
    }
  }
}
