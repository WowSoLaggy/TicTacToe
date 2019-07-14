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

  d_fontId = d_resourceController.getResourceId("MyFont.spritefont");
}


void ViewModel::render(Dx::IRenderer2d& i_renderer) const
{
  i_renderer.renderSprite(d_spriteBackground);
  i_renderer.renderSprite(d_spriteField);
  i_renderer.renderText(d_turnString, d_fontId, { 470, 50 });
  i_renderer.renderText(d_debugString, d_fontId, { 0, 0 });
}


void ViewModel::setDebugString(std::string i_debugString)
{
  d_debugString = std::move(i_debugString);
}

void ViewModel::setTurn(bool i_isPlayerTurn)
{
  d_isPlayerTurn = i_isPlayerTurn;
  d_turnString = d_isPlayerTurn ? "Player turn" : "Mighty AI turn";
}
