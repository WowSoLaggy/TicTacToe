#pragma once

#include <TicTacToe/GameField.h>

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class ViewModel
{
public:
  ViewModel(const Dx::IResourceController& i_resourceController, const GameField& i_gameField);

  void createInitial();

  void render(Dx::IRenderer2d& i_renderer, const Dx::MousePosition& i_mousePosition) const;

  void setTurn(bool i_isPlayerTurn);
  void setWinState(WinState i_winState);
  void setScore(int i_scorePlayer, int i_scoreAi);

private:
  bool d_isPlayerTurn;
  WinState d_winState;
  std::string d_statusString;
  std::string d_scoreString;
  
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
