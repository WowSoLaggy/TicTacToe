#pragma once

#include "ViewModel.h"

#include <TicTacToe/TicTacToeFwd.h>

#include <LaggyDx/IInputDevice.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/Window.h>
#include <LaggySdk/Timer.h>


class App
{
public:
  App();
  void run();

private:
  // GAME LOGIC

  bool d_isPlayerTurn;
  int d_scorePlayer;
  int d_scoreAi;
  double d_aiTurnTime;
  double d_victoryTime;
  WinState d_winState = WinState::NoWinner;
  void setTurn(bool i_isPlayerTurn);
  void setWinState(WinState i_winState);
  void checkLogic(double i_dt);
  void checkVictory();
  void startNewGame();

  // NOT GAME LOGIC

  Sdk::Timer d_timer;
  std::unique_ptr<Sdk::Window> d_window;
  std::unique_ptr<Dx::IInputDevice> d_inputDevice;
  std::unique_ptr<Dx::IRenderDevice> d_renderDevice;
  std::unique_ptr<Dx::IResourceController> d_resourceController;
  std::unique_ptr<Dx::IRenderer2d> d_renderer2d;
  std::unique_ptr<GameField> d_gameField;
  std::unique_ptr<ViewModel> d_viewModel;

  bool d_stopSignal;
  void mainloop();
  bool stopMainloop();
  
  void handleKeyboard(const Dx::KeyboardState& i_keyboardState);
  void handleMouse(const Dx::MouseState& i_mouseState);
  
  void resetModel();
  void resetViewModel();

  void setCursorToCenter();
};
