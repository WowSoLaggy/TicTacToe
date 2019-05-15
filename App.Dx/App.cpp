#include "stdafx.h"
#include "App.h"

#include "Settings.h"

#include <LaggyDx/IInputDevice.h>
#include <LaggyDx/IRenderDevice.h>
#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/IResourceController.h>
#include <LaggySdk/Contracts.h>
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
  createResourceController();
  loadResourceController();
  createRenderer2d();
  createInputDevice();
  showWindow();

  createViewModel();
  resetViewModel();

  d_stopSignal = false;
}

void App::dispose()
{
  disposeViewModel();

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

    CONTRACT_EXPECT(d_renderDevice);
    CONTRACT_EXPECT(d_renderer2d);
    d_renderDevice->beginScene();
    d_renderer2d->beginScene();

    d_viewModel->render(*d_renderer2d);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    d_renderer2d->endScene();
    d_renderDevice->endScene();
  }
}


void App::createWindow()
{
  d_window = std::make_shared<Sdk::Window>();
  CONTRACT_ENSURE(d_window);
  d_window->create(WindowWidth, WindowHeight, ApplicationName);
}

void App::showWindow()
{
  CONTRACT_EXPECT(d_window);
  d_window->show();
}

void App::disposeWindow()
{
  CONTRACT_EXPECT(d_window);
  d_window->dispose();
  d_window.reset();
}


bool App::stopMainloop()
{
  CONTRACT_EXPECT(d_inputDevice);
  if (!Sdk::handleMessages(std::bind(&Dx::IInputDevice::processMessage, std::ref(*d_inputDevice), std::placeholders::_1)))
    return true;

  return d_stopSignal;
}


void App::createInputDevice()
{
  d_inputDevice = Dx::IInputDevice::create();
  CONTRACT_ENSURE(d_inputDevice);
  d_inputDevice->initialize();
}

void App::disposeInputDevice()
{
  CONTRACT_EXPECT(d_inputDevice);
  d_inputDevice->dispose();
  d_inputDevice.reset();
}


void App::createRenderDevice()
{
  d_renderDevice = Dx::IRenderDevice::create();
  CONTRACT_ENSURE(d_renderDevice);

  d_renderDevice->initialize(d_window->getHWnd(), WindowWidth, WindowHeight);
  CONTRACT_ENSURE(d_renderDevice->isInitialized());
}

void App::disposeRenderDevice()
{
  CONTRACT_EXPECT(d_renderDevice);
  d_renderDevice->dispose();
  d_renderDevice.reset();
}


void App::createResourceController()
{
  d_resourceController = Dx::IResourceController::create();
  CONTRACT_ENSURE(d_resourceController);
  d_resourceController->initialize(ResourceFolder);
}

void App::loadResourceController()
{
  CONTRACT_EXPECT(d_renderDevice);
  CONTRACT_EXPECT(d_renderDevice->isInitialized());
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
  d_resourceController->dispose();
  d_resourceController.reset();
}


void App::createRenderer2d()
{
  CONTRACT_EXPECT(d_renderDevice);
  CONTRACT_EXPECT(d_resourceController);
  d_renderer2d = Dx::IRenderer2d::create(*d_renderDevice, *d_resourceController);
  CONTRACT_ENSURE(d_renderer2d);
}

void App::disposeRenderer2d()
{
  d_renderer2d.reset();
}


void App::createViewModel()
{
  CONTRACT_EXPECT(d_resourceController);
  d_viewModel = std::make_shared<ViewModel>(*d_resourceController);
}

void App::resetViewModel()
{
  d_viewModel->createInitial();
}

void App::disposeViewModel()
{
  d_viewModel.reset();
}
