#include "stdafx.h"
#include "App.h"

#include <TicTacToe/GameField.h>
#include <LaggySdk/Contracts.h>


void App::setTurn(bool i_isPlayerTurn)
{
  d_isPlayerTurn = i_isPlayerTurn;
  d_viewModel->setTurn(d_isPlayerTurn);
}

void App::checkLogic(double i_dt)
{
  if (d_isPlayerTurn)
  {
    d_aiTurnTime = 0;
    return;
  }

  d_aiTurnTime += i_dt;
  if (d_aiTurnTime < 1)
    return;

  std::vector<int> freeFields;
  for (int idx = 0; idx < d_gameField->FieldSize; ++idx)
  {
    if (d_gameField->isFieldUnoccupied(idx))
      freeFields.push_back(idx);
  }

  CONTRACT_EXPECT(freeFields.size() > 0);

  const int idx = std::rand() % freeFields.size();
  d_gameField->setFieldState(freeFields.at(idx), FieldState::Toe);

  setTurn(true);
}
