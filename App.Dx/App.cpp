#include "stdafx.h"
#include "App.h"

#include "Settings.h"

#include <LaggyDx/IInputDevice.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggySdk/HandleMessages.h>
#include <LaggySdk/Window.h>


void App::run()
{
  initialize();
  mainloop();
  dispose();
}


void App::initialize()
{
  createWindow();
  createRenderDevice();
  createInputDevice();
  showWindow();

  d_stopSignal = false;
}

void App::dispose()
{
  disposeInputDevice();
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

    d_renderDevice->beginScene();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    d_renderDevice->endScene();
  }
}


void App::createWindow()
{
  d_window = std::make_shared<Sdk::Window>();
  d_window->create(WindowWidth, WindowHeight, ApplicationName);
}

void App::showWindow()
{
  d_window->show();
}

void App::disposeWindow()
{
  d_window->dispose();
  d_window.reset();
}


bool App::stopMainloop()
{
  if (!Sdk::handleMessages(std::bind(&Dx::IInputDevice::processMessage, std::ref(*d_inputDevice), std::placeholders::_1)))
    return true;

  return d_stopSignal;
}


void App::createInputDevice()
{
  d_inputDevice = Dx::IInputDevice::create();
  d_inputDevice->initialize();
}

void App::disposeInputDevice()
{
  d_inputDevice->dispose();
  d_inputDevice.reset();
}


void App::createRenderDevice()
{
  d_renderDevice = Dx::IRenderDevice::create();
  d_renderDevice->initialize(d_window->getHWnd(), WindowWidth, WindowHeight);
}

void App::disposeRenderDevice()
{
  d_renderDevice->dispose();
  d_renderDevice.reset();
}
