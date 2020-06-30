#include<bits/stdc++.h>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MAXMOVES 526

int SIDE; // length of the side of the board
int MINES; // number of mines in the board

// function to check if the move is valid or not
bool isValid(int row, int col)
{
	if((row >= 0 && row < SIDE) && (col >= 0 && col < SIDE))
		return true;
	else
		return false; 
}

// function to check if the selected cell has a mine or not
bool isMine(int row, int col, char board[][MAXSIDE])
{
	if(board[row][col] == '*')
		return true;
	else
		return false;
}

// function to get the user's move
void getMove(int *x, int *y)
{
	cout << "Enter your move in (row, column) ----> ";
	scanf ("%d %d", x, y);
	return;
}

// function to print the current gameplay board
void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;
	cout << "     ";
	for(i = 0; i < SIDE; i++)
		cout << " " << i;
	cout << endl;
	for(i = 0; i < SIDE; i++)
	{
		cout << "     " << i;
		for(j = 0; j < SIDE; j++)
			cout << " " << myBoard[i][j];
		cout << endl;
	}
}

// function to count the number of mines in adjacent cells
int countMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE])
{
	int i, count = 0;
	
    /* 
        Count all the mines in the 8 adjacent 
        cells 
  
            N.W   N   N.E 
               \  |  / 
                \ | / 
            W----Cell----E 
                / | \ 
               /  |  \ 
            S.W   S   S.E 
  
        Cell-->Current Cell (row, col) 
        N -->  North        (row-1, col) 
        S -->  South        (row+1, col) 
        E -->  East         (row, col+1) 
        W -->  West         (row, col-1) 
        N.E--> North-East   (row-1, col+1) 
        N.W--> North-West   (row-1, col-1) 
        S.E--> South-East   (row+1, col+1) 
        S.W--> South-West   (row+1, col-1) 
    */
    
    // 1st Neighbour (North)
    
    // First check if the row is valid
    if(isValid(row - 1, col) == true)
    {
    	if(isMine(row - 1, col, realBoard) == true)
    		count++;
	}
	
	// 2nd Neighbour (South)
    
    // First check if the row is valid
    if(isValid(row + 1, col) == true)
    {
    	if(isMine(row + 1, col, realBoard) == true)
    		count++;
	}
	
	// 3rd Neighbour (East)
	
	// First check if the row is valid
    if(isValid(row, col + 1) == true)
    {
    	if(isMine(row, col + 1, realBoard) == true)
    		count++;
	}
	
	// 4th Neighbour (West)
	
	// First check if the row is valid
    if(isValid(row, col - 1) == true)
    {
    	if(isMine(row, col - 1, realBoard) == true)
    		count++;
	}
	
	// 5th Neighbour (North - East)
	
	// First check if the row is valid
    if(isValid(row - 1, col + 1) == true)
    {
    	if(isMine(row - 1, col + 1, realBoard) == true)
    		count++;
	}
	
	// 6th Neighbour (North - West)
	
	// First check if the row is valid
    if(isValid(row - 1, col - 1) == true)
    {
    	if(isMine(row - 1, col - 1, realBoard) == true)
    		count++;
	}
	
	// 7th Neighbour (South - East)
	
	// First check if the row is valid
    if(isValid(row + 1, col + 1) == true)
    {
    	if(isMine(row + 1, col + 1, realBoard) == true)
    		count++;
	}
	
	// 8th Neighbour (South - West)
	
	// First check if the row is valid
    if(isValid(row + 1, col - 1) == true)
    {
    	if(isMine(row + 1, col - 1, realBoard) == true)
    		count++;
	}
	
	return count;
}

// recursive function to play the minesweeper game
bool playMinesweeperUtil(char  myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int *movesLeft)
{
	// base condition
	if(myBoard[row][col] != '-')
		return false;
		
	int i, j;
	
	// you will lose if you click a mine
	if(realBoard[row][col] == '*')
	{
		myBoard[row][col] = '*';
		
		for(i = 0; i < MINES; i++)
			myBoard[mines[i][0]][mines[i][1]] = '*';
		
		printBoard(myBoard);
		cout << endl << "You Lost" << endl;
		return true;
	}
	
	else
	{
		// calculate the number of adjacent mines and put them
		int count = countMines(row, col, mines, realBoard);
		(*movesLeft)--;
		
		myBoard[row][col] = count + '0';
		
		if(!count)
		{
			 /* 
        	Recur for all 8 adjacent cells
  
            	N.W   N   N.E 
            	   \  |  / 
            	    \ | / 
            	W----Cell----E 
            	    / | \ 
            	   /  |  \ 
            	S.W   S   S.E 
  
        	Cell-->Current Cell (row, col) 
        	N -->  North        (row-1, col) 
        	S -->  South        (row+1, col) 
        	E -->  East         (row, col+1) 
        	W -->  West         (row, col-1) 
        	N.E--> North-East   (row-1, col+1) 
        	N.W--> North-West   (row-1, col-1) 
        	S.E--> South-East   (row+1, col+1) 
        	S.W--> South-West   (row+1, col-1) 
    		*/
    
    		// 1st Neighbour (North)
    
    		// First check if the row is valid
    		if(isValid(row - 1, col) == true)
		    {
		    	if(isMine(row - 1, col, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col, movesLeft);
			}
			
			// 2nd Neighbour (South)
		    
		    // First check if the row is valid
		    if(isValid(row + 1, col) == true)
		    {
		    	if(isMine(row + 1, col, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col, movesLeft);
			}
			
			// 3rd Neighbour (East)
			
			// First check if the row is valid
		    if(isValid(row, col + 1) == true)
		    {
		    	if(isMine(row, col + 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row, col + 1, movesLeft);
			}
			
			// 4th Neighbour (West)
			
			// First check if the row is valid
		    if(isValid(row, col - 1) == true)
		    {
		    	if(isMine(row, col - 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row, col - 1, movesLeft);
			}
			
			// 5th Neighbour (North - East)
			
			// First check if the row is valid
		    if(isValid(row - 1, col + 1) == true)
		    {
		    	if(isMine(row - 1, col + 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
			}
			
			// 6th Neighbour (North - West)
			
			// First check if the row is valid
		    if(isValid(row - 1, col - 1) == true)
		    {
		    	if(isMine(row - 1, col - 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
			}
			
			// 7th Neighbour (South - East)
			
			// First check if the row is valid
		    if(isValid(row + 1, col + 1) == true)
		    {
		    	if(isMine(row + 1, col + 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
			}
			
			// 8th Neighbour (South - West)
			
			// First check if the row is valid
		    if(isValid(row + 1, col - 1) == true)
		    {
		    	if(isMine(row + 1, col - 1, realBoard) == false)
		    		playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
			}			
		}
		return false;
	}
}

// function to place the mines randomly in the board
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE * MAXSIDE];
	memset(mark, false, sizeof(mark));
	
	// to place all the mines randomly
	for(int i = 0; i < MINES; )
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;
		
		// if no mine is placed at a position
		// then place it
		if(mark[random] == false)
		{
			mines[i][0] = x; // row indes of the mine
			mines[i][1] = y; // column index of the mine
			
			// place the mine
			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
}

// function to initiate the game
void initiateGame(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	// so that the same combination does not arise
	srand(time(NULL));
	
	// assign all the cells as mine free
	for(int i = 0; i < SIDE; i++)
	{
		for(int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}
}

// to know the location of all the mines before hand (cheating)
void cheatMinesweeper(char realBoard[][MAXSIDE])
{
	cout << "The mines are located at: " << endl;
	printBoard(realBoard);
}

// function to replace the mine from (row, col) and put it in the vacant place
void replaceMine(int row, int col, char board[][MAXSIDE])
{
	for(int i = 0; i < SIDE; i++)
	{
		for(int j = 0; j < SIDE; j++)
		{
			// find the location which is not having a mine and put a mine there
			if(board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
			}
		}
	}
}

// function to play the minesweeper game
void playMinesweeper()
{
	bool gameOver = false; // initially the game is not over
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
	
	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; // stores the x and y coordinates of all mines
	
	initiateGame(realBoard, myBoard);
	
	// places the mines randomly
	placeMines(mines, realBoard);
	
	/* If you want to cheat and know the position of all the mines before hand
	 then uncomment the function  call 
	 
	 cheatMinesweeper(realBoard);
	*/
	 
	int currentMoveIndex = 0;
	while(gameOver == false)
	{
		cout << "Current status of the board: " << endl;
		printBoard(myBoard);
		getMove(&x, &y);
		
		// if it is the first move of the game
		if(currentMoveIndex == 0)
		{
			if(isMine(x, y, realBoard) == true)
				replaceMine(x, y, realBoard);
		}
		currentMoveIndex++;
		
		gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);
		
		if((gameOver == false) && (movesLeft == 0))
		{
			cout << endl << "You Won" << endl;
			gameOver = true;
		}
	}
}

// function to choose the difficulty level of the game
void chooseDifficultyLevel()
{
	/* 
    --> BEGINNER = 9 * 9 Cells and 10 Mines 
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines 
    --> ADVANCED = 24 * 24 Cells and 99 Mines 
    */
    
    int level;
    cout << "Enter the difficulty level" << endl;
    cout << "Enter 0  for BEGINNER (9 * 9 Cells and 10 Mines)" << endl;
    cout << "Enter 1  for INTERMEDIATE (16 * 16 Cells and 40 Mines)" << endl;
    cout << "Enter 2  for ADVANCED (25 * 25 Cells and 99 Mines)" << endl;
    
    cin >> level;
    
    if(level == BEGINNER)
    {
    	SIDE = 9;
    	MINES = 10;
	}
	
	if(level == INTERMEDIATE)
    {
    	SIDE = 16;
    	MINES = 40;
	}
	
	if(level == ADVANCED)
    {
    	SIDE = 24;
    	MINES = 99;
	}
}

// Driver Code
int main()
{
	chooseDifficultyLevel();
	
	playMinesweeper();
	
	return 0;
}
