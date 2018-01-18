#include <stdio.h>
#include <stdbool.h> // For the boolean method

/*
	Author: Shubham Sharma
	netID: shubham@iastate.edu
	Course: COMS_327 
	Took inspiration on the recursive approach from this website
 	https://leetcode.com/problems/n-queens/description/
*/

// Global variable to count the amount of solutions found
int count=0;

// Global variables to make sure that this code can work in any dimension
// THEY SHOULD HAVE THE SAME VALUE, (since a chessboard is a square).
int ROWS = 8;
int COLS = 8;


// Checks if the given position is valid for the current board
bool checkValidPosition(int row, int col, char boardQueens[ROWS][COLS])
{
	// No need to check two as it is performed in the recursiveCheck() method
	int i=row, j=col;
	
	// If it exceeds the desired length
	if(row >= ROWS)
		return false;
	//Checks diagonal 1
	while(i>=0 && j>=0)
	{
		if(boardQueens[i][j] == 'q')
			return false;
		
		i--;
		j--;
	}
	i=row; 
	j=col;
	
	// Checks diagonal 2
	while(i>=0 && j<COLS)
	{
		if(boardQueens[i][j] == 'q')
			return false;
		 i--;
		 j++;
	}
	i=0;
	
	// Check column
	while(i<row)
	{
		if(boardQueens[i][col] == 'q')
			return false;
		i++;
	}
	
	// Hence, it should be a valid position
	return true;
}


// The recursive method to find all the solutions for the N-Queens problem
void recursiveCheck (int row, int col, char boardQueens[ROWS][COLS])
{
	int intSolution[ROWS] , temp=0, pos =0, i=0,j=0;
	// Since there are 26 letters in the English alphabet,
	char charSolution[26] = "abcdefghijklmnopqrstuvwxyz";
	
	// Recursive loop to find valid positions of the queen
	for(i=0; i<ROWS; i++)
	{
		// Find all positions for the queen
		if(checkValidPosition(row, i, boardQueens))
		{
			boardQueens[row][i] = 'q';
			recursiveCheck(row+1, 0,boardQueens);
			boardQueens[row][i] = '-';
		}
		
	}
	
	
	if(col == 0 && row == ROWS)
	{
		for(i=0; i<ROWS; i++)
		{
			for(j=0; j<COLS;j++)
			{
				if(boardQueens[i][j] == 'q')
				{
					// Numeric solution of the chessboard
					intSolution[temp] = j;
					temp++; 
				}
			}
		}
		
		// Prints the desired solution is the specified format
		for(i=0; i<ROWS; i++)
		{
			printf("%c", charSolution[i]);
			printf("%d", intSolution[i]+1);
		}
		printf("\n");
		
		
		// Prints the visual representation of the solution for more clarification
		for(i=0; i<ROWS; i++)
		{
			for(j=0; j< COLS; j++)
			{
				printf("%c ", boardQueens[i][j]);
			}
			printf("\n");
		}
		// Counts the total number of solutions found
		count++;		
		printf("Solution number: %d", count);
		printf("\n \n");    

		
	}
}

int main (int argc, char *argv[])
{
	// Initialize and declare the some variables for the main method.
	int i,j; i=0; j=0;
	char boardQueens[ROWS][COLS];
	
	// Default template to be used for an empty board
	// Where an empty position is denoted by '-'
	// And a queen position is denoted by 'q'
	for(i=0; i< ROWS; i++)
	{
		for(j=0; j< COLS; j++)
		{
			boardQueens[i][j] = '-'; 
		}
	}
	
	// The recursive method to find all the solutions for the N-Queens problem
	recursiveCheck(0,0,boardQueens);
	
	// Prints the total number of solutions found for the board dimensions (now 8,8)
	printf("\n The total number of solutions found: %d \n",count);
	
	
	return 0;
}
