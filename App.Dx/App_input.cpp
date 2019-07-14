#include "stdafx.h"
#include "App.h"

#include <LaggyDx/KeyboardState.h>


void App::handleInput(const Dx::KeyboardState& i_keyboardState)
{
  if (i_keyboardState.pressed.Escape)
  {
    d_stopSignal = true;
    return;
  }
}
