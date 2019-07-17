#include "stdafx.h"
#include "App.h"

#include "Settings.h"

#include <TicTacToe/GameField.h>

#include <LaggyDx/IInputDevice.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>
#include <LaggyDx/MouseState.h>
#include <LaggySdk/Contracts.h>
#include <LaggySdk/HandleMessages.h>
#include <LaggySdk/Random.h>
#include <LaggySdk/Window.h>


void App::run()
{
  initialize();
  mainloop();
  dispose();
}


void App::initialize()
{
  Sdk::randomize();

  d_window = std::make_unique<Sdk::Window>(WindowWidth, WindowHeight, ApplicationName);
  d_renderDevice = Dx::IRenderDevice::create(d_window->getHWnd(), WindowWidth, WindowHeight);
  d_resourceController = Dx::IResourceController::create(ResourceFolder);

  loadResourceController();
  
  d_renderer2d = Dx::IRenderer2d::create(*d_renderDevice, *d_resourceController);
  d_inputDevice = Dx::IInputDevice::create(d_window->getHWnd());

  d_gameField = std::make_unique<GameField>();
  resetModel();

  d_viewModel = std::make_unique<ViewModel>(*d_resourceController, *d_gameField);
  resetViewModel();

  d_stopSignal = false;
  d_scorePlayer = 0;
  d_scoreAi = 0;

  setCursorToCenter();
  showWindow();
}

void App::dispose()
{
  disposeViewModel();

  disposeModel();

  disposeInputDevice();
  disposeRenderer2d();
  unloadResourceController();
  disposeResourceController();
  disposeRenderDevice();
  disposeWindow();
}

void App::mainloop()
{
  d_timer.start();
  double dt = 0;

  while (!stopMainloop())
  {
    dt = d_timer.restart();

    CONTRACT_EXPECT(d_inputDevice);
    CONTRACT_EXPECT(d_renderDevice);
    CONTRACT_EXPECT(d_renderer2d);

    const auto& keyboardState = d_inputDevice->checkKeyboard();
    handleKeyboard(keyboardState);
    const auto& mouseState = d_inputDevice->checkMouse();
    handleMouse(mouseState);

    checkLogic(dt);

    d_renderDevice->beginScene();
    d_renderer2d->beginScene();

    d_viewModel->render(*d_renderer2d, mouseState.getMousePosition());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    d_renderer2d->endScene();
    d_renderDevice->endScene();
  }
}


void App::showWindow()
{
  CONTRACT_EXPECT(d_window);
  d_window->show();
}

void App::disposeWindow()
{
  CONTRACT_EXPECT(d_window);
  d_window.reset();
}


bool App::stopMainloop()
{
  CONTRACT_EXPECT(d_inputDevice);
  if (!Sdk::handleMessages(std::bind(&Dx::IInputDevice::processMessage, std::ref(*d_inputDevice), std::placeholders::_1)))
    return true;

  return d_stopSignal;
}


void App::disposeInputDevice()
{
  CONTRACT_EXPECT(d_inputDevice);
  d_inputDevice.reset();
}


void App::disposeRenderDevice()
{
  CONTRACT_EXPECT(d_renderDevice);
  d_renderDevice.reset();
}


void App::loadResourceController()
{
  CONTRACT_EXPECT(d_renderDevice);
  CONTRACT_EXPECT(d_resourceController);
  d_resourceController->loadResources(*d_renderDevice);
}

void App::unloadResourceController()
{
  CONTRACT_EXPECT(d_resourceController);
  d_resourceController->unloadResources();
}

void App::disposeResourceController()
{
  CONTRACT_EXPECT(d_resourceController);
  d_resourceController.reset();
}


void App::disposeRenderer2d()
{
  d_renderer2d.reset();
}


void App::resetModel()
{
  CONTRACT_EXPECT(d_gameField);
  d_gameField->resetFields();

  d_isPlayerTurn = true;
  d_winState = WinState::NoWinner;
}

void App::disposeModel()
{
  d_gameField.reset();
}


void App::resetViewModel()
{
  d_viewModel->createInitial();
  d_viewModel->setTurn(d_isPlayerTurn);
  d_viewModel->setWinState(d_winState);
  d_viewModel->setScore(d_scorePlayer, d_scoreAi);
}

void App::disposeViewModel()
{
  d_viewModel.reset();
}


void App::setCursorToCenter()
{
  int posX = GetSystemMetrics(SM_CXSCREEN) / 2;
  int posY = GetSystemMetrics(SM_CYSCREEN) / 2;
  SetCursorPos(posX, posY);
}
