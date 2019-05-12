#include <TicTacToe/GameField.h>

#include <chrono>
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


static constexpr int Width = 80;
static constexpr int Height = 22;


void resetPosition()
{
  HANDLE hCon;
  COORD cPos;

  hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  cPos.Y = 2;
  cPos.X = 0;
  SetConsoleCursorPosition(hCon, cPos);
}

void cleanConsole()
{
  // Get the Win32 handle representing standard output.
  // This generally only has to be done once, so we make it static.
  static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD topLeft = { 0, 0 };

  // std::cout uses a buffer to batch writes to the underlying console.
  // We need to flush that to the console because we're circumventing
  // std::cout entirely; after we clear the console, we don't want
  // stale buffered text to randomly be written out.
  std::cout.flush();

  // Figure out the current width and height of the console window
  if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
    // TODO: Handle failure!
    abort();
  }
  DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

  DWORD written;

  // Flood-fill the console with spaces to clear it
  FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

  // Reset the attributes of every character to the default.
  // This clears all background colour formatting, if any.
  FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

  // Move the cursor back to the top left for the next sequence of writes
  SetConsoleCursorPosition(hOut, topLeft);
}

void redrawField(const GameField& i_gameField)
{
  auto getChar = [&](int i_x, int i_y)
  {
    if (i_gameField.getFieldState(i_x, i_y) == FieldState::Cross)
      return 'X';
    else if (i_gameField.getFieldState(i_x, i_y) == FieldState::Toe)
      return 'O';
    else
      return ' ';
  };

  cleanConsole();

  std::cout << "-=-=-=-=- TIC-TAC-TOE GAME -=-=-=-=-" << std::endl << std::endl;

  for (int y = 0; y < i_gameField.Size; ++y)
  {
    for (int x = 0; x < i_gameField.Size; ++x)
    {
      std::cout << ' ' << getChar(x, y) << ' ';
      if (x < i_gameField.Size - 1)
        std::cout << "|";
    }

    if (y < i_gameField.Size - 1)
      std::cout << std::endl << "-----------" << std::endl;
  }

  std::cout << std::endl << std::endl;
}

int getIndexForAiTurn(const GameField& i_gameField)
{
  std::vector<int> freeInds;

  for (int ind = 0; ind < i_gameField.FieldSize; ++ind)
  {
    if (i_gameField.isFieldUnoccupied(ind))
      freeInds.push_back(ind);
  }

  return freeInds.at(std::rand() % freeInds.size());
}


int main()
{
  std::srand((unsigned int)time(nullptr));

  GameField gameField;

  bool isPlayerTurn = true;
  const FieldState playerState = isPlayerTurn ? FieldState::Cross : FieldState::Toe;
  const FieldState aiState = !isPlayerTurn ? FieldState::Cross : FieldState::Toe;

  WinState winState = WinState::NoWinner;
  while (winState == WinState::NoWinner)
  {
    if (isPlayerTurn)
    {
      redrawField(gameField);

      std::cout << "  Your turn! Select field in [1-9]:" << std::endl;
      
      int index = 0;
      bool inputIsCorrect = false;
      do
      {
        std::string input;
        std::getline(std::cin, input);
        std::stringstream(input) >> index;
        --index;

        inputIsCorrect =
          0 <= index && index < gameField.FieldSize &&
          gameField.getFieldState(index) == FieldState::Unoccupied;

        if (!inputIsCorrect)
          std::cout << "  Please select a free field [1-9]:" << std::endl;

      } while (!inputIsCorrect);

      gameField.setFieldState(index, playerState);
    }
    else
    {
      redrawField(gameField);

      std::cout << "  Mighty AI turn, please wait...";

      std::this_thread::sleep_for(std::chrono::seconds(1));

      int index = getIndexForAiTurn(gameField);
      gameField.setFieldState(index, aiState);
    }

    isPlayerTurn = !isPlayerTurn;
    winState = gameField.getWinState();
  }

  redrawField(gameField);

  if (winState == WinState::Draw)
    std::cout << "Draw!";
  else if ((winState == WinState::WinnerCross) == (playerState == FieldState::Cross))
    std::cout << "You win!";
  else
    std::cout << "Mighty AI win!";

  std::cout << std::endl << " " << std::endl << "Press any key to exit...";
  _getch();

  return 0;
}
