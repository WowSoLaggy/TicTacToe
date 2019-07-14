#pragma once

#include "ViewModel.h"

#include <TicTacToe/TicTacToeFwd.h>

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/SdkFwd.h>
#include <LaggySdk/Timer.h>


class App
{
public:
  void run();

private:
  bool d_stopSignal;
  bool stopMainloop();

  void initialize();
  void mainloop();
  void dispose();

  std::shared_ptr<Sdk::Window> d_window;
  void createWindow();
  void showWindow();
  void disposeWindow();

  std::shared_ptr<Dx::IInputDevice> d_inputDevice;
  void createInputDevice();
  void disposeInputDevice();
  void handleInput(const Dx::KeyboardState& i_keyboardState);

  std::shared_ptr<Dx::IRenderDevice> d_renderDevice;
  void createRenderDevice();
  void disposeRenderDevice();

  std::shared_ptr<Dx::IResourceController> d_resourceController;
  void createResourceController();
  void loadResourceController();
  void unloadResourceController();
  void disposeResourceController();

  std::shared_ptr<Dx::IRenderer2d> d_renderer2d;
  void createRenderer2d();
  void disposeRenderer2d();

  std::shared_ptr<GameField> d_gameField;
  void createModel();
  void resetModel();
  void disposeModel();

  std::shared_ptr<ViewModel> d_viewModel;
  void createViewModel();
  void resetViewModel();
  void disposeViewModel();

  Sdk::Timer d_timer;
};
