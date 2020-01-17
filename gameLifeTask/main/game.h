enum GameState
{
  Preparing,
  Playing
};

class Game
{
public :
Game (int BoardSize)
{
  boardSize = BoardSize;
  fillBoard();
}

void updateBoard()
{
for (int i = 0; i < boardSize; i++)
  for(int j = 0; j < boardSize; j++)
  {
    bufferBoard[i][j] = checkTile(i,j);
  }


  for (int a = 0; a < boardSize; a++)
    for (int b = 0 ; b < boardSize; b++)
      board[a][b] = bufferBoard[a][b];
}

void fillBoard(){ 
  for (int i =0; i < boardSize; i++)
    for (int j = 0; j < boardSize; j++)
    {
      board[i][j] = false;        
    }
    board [2][0] = true;
    board [2][1] = true;
    board [2][2] = true;
    board [0][1] = true;
    board [1][2] = true;
}

bool bufferBoard[8][8];
bool board[8][8];

private:

bool checkTile(int i, int j)
{
  int neighbours = 0;
   for (int x = i -1; x < i+2; x++)
    for (int y = j -  1; y < j+2; y++)
    {
      if (x ==i && y ==j) continue;
      
      if(board[(x+boardSize) % boardSize][(y+boardSize) % boardSize])
        neighbours++;
    }
    
    if(board[i][j])
    {
      return ((neighbours > 1) && (neighbours < 4));
    }
    else
      return (neighbours == 3);
      
}

private :
int boardSize; 
};
