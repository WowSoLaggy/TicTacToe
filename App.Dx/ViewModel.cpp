#include "stdafx.h"
#include "ViewModel.h"

#include "Settings.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/ResourceController.h>
#include <LaggyDx/TextureResource.h>
#include <LaggySdk/Vector.h>


namespace
{
  Sdk::Vector2 getSize(const Dx::IResourceController& i_resourceController, Dx::ResourceId i_resourceId)
  {
    const auto& resourceController = dynamic_cast<const Dx::ResourceController&>(i_resourceController);
    return resourceController.getTextureResource(i_resourceId).getSize();
  }
} // anonymous NS


ViewModel::ViewModel(const Dx::IResourceController& i_resourceController, const GameField& i_gameField)
  : d_resourceController(i_resourceController)
  , d_gameField(i_gameField)
{
}


void ViewModel::createInitial()
{
  d_spriteBackground = {
    d_resourceController.getResourceId("Background.dds"),
    { 0, 0 },
    { WindowWidth, WindowHeight }
  };

  const auto GameFieldOffset = 25;
  const auto gameFieldResourceId = d_resourceController.getResourceId("GameField.dds");
  d_spriteField = {
    gameFieldResourceId,
    { GameFieldOffset, GameFieldOffset },
    getSize(d_resourceController, gameFieldResourceId)
  };
}


void ViewModel::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.renderSprite(d_spriteBackground);
  i_renderer.renderSprite(d_spriteField);
}
