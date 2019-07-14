#pragma once

#include <TicTacToe/TicTacToeFwd.h>

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class ViewModel
{
public:
  ViewModel(const Dx::IResourceController& i_resourceController, const GameField& i_gameField);

  void createInitial();

  void render(Dx::IRenderer2d& i_renderer, const Dx::MousePosition& i_mousePosition) const;

  void setTurn(bool i_isPlayerTurn);

private:
  bool d_isPlayerTurn;
  std::string d_turnString;

  const Dx::IResourceController& d_resourceController;
  const GameField& d_gameField;

  Dx::Sprite d_spriteBackground;
  Dx::Sprite d_spriteField;

  Dx::ResourceId d_fontId;

  Dx::ResourceId d_ticId;
  Dx::ResourceId d_tacId;
  Sdk::Vector2 d_ticSize;
  Sdk::Vector2 d_tacSize;
};
