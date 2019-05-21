#pragma once

#include <TicTacToe/TicTacToeFwd.h>

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/Sprite.h>


class ViewModel
{
public:
  ViewModel(const Dx::IResourceController& i_resourceController, const GameField& i_gameField);

  void createInitial();

  void render(Dx::IRenderer2d& i_renderer) const;

private:
  const Dx::IResourceController& d_resourceController;
  const GameField& d_gameField;

  Dx::Sprite d_spriteBackground;
  Dx::Sprite d_spriteField;
};
