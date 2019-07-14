#include "stdafx.h"
#include "ViewModel.h"

#include "FieldPositions.h"
#include "Settings.h"

#include <LaggyDx/IRenderer2d.h>
#include <LaggyDx/MouseState.h>
#include <LaggyDx/ResourceController.h>
#include <LaggyDx/TextureResource.h>
#include <LaggySdk/Vector.h>
#include <TicTacToe/GameField.h>


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

  d_ticId = d_resourceController.getResourceId("Tic.dds");
  d_tacId = d_resourceController.getResourceId("Tac.dds");

  d_ticSize = getSize(d_resourceController, d_ticId);
  d_tacSize = getSize(d_resourceController, d_tacId);
}


void ViewModel::render(Dx::IRenderer2d& i_renderer, const Dx::MousePosition& i_mousePosition) const
{
  // BACKGROUND

  i_renderer.renderSprite(d_spriteBackground);
  i_renderer.renderSprite(d_spriteField);

  // OCCUPIED FIELDS

  auto drawField = [&](int i_idx, bool i_cross)
  {
    i_renderer.renderSprite({
      i_cross ? d_tacId : d_ticId,
      getIndexOffset(i_idx),
      i_cross ? d_tacSize : d_ticSize });
  };

  for (int idx = 0; idx < d_gameField.FieldSize; ++idx)
  {
    const auto fieldState = d_gameField.getFieldState(idx);
    if (fieldState != FieldState::Unoccupied)
      drawField(idx, fieldState == FieldState::Cross);
  }

  // SELECTED FIELD

  if (d_isPlayerTurn)
  {
    const int fieldIndex = getFieldIndex(i_mousePosition.x, i_mousePosition.y);
    if (fieldIndex != -1 && d_gameField.isFieldUnoccupied(fieldIndex))
      drawField(fieldIndex, true);
  }

  i_renderer.renderText(d_turnString, d_fontId, { 470, 50 });

  // DEBUG

  /*const std::string debugString =
    std::to_string(i_mousePosition.x) + ", " +
    std::to_string(i_mousePosition.y) + " (" +
    std::to_string(fieldIndex) + ")";
  i_renderer.renderText(debugString, d_fontId, { 0, 0 });*/
}


void ViewModel::setTurn(bool i_isPlayerTurn)
{
  d_isPlayerTurn = i_isPlayerTurn;
  d_turnString = d_isPlayerTurn ? "Player turn" : "Mighty AI turn";
}
