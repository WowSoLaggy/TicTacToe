#include "stdafx.h"
#include "App.h"

#include <LaggyDx/KeyboardState.h>
#include <LaggyDx/MouseState.h>


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
  const std::string debugString =
    std::to_string(i_mouseState.getX()) + ", " +
    std::to_string(i_mouseState.getY());

  d_viewModel->setDebugString(debugString);
}
