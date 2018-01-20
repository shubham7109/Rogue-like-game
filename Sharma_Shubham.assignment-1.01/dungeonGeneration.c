#include <stdio.h>
#include <stdlib.h> // For rand()
#include <stdbool.h> // For boolean variables

/*
	Author: Shubham Sharma
	netID: shubham@iastate.edu
	Course: COMS_327 
*/

// Defined some global variables
int ROWS = 21;
int COLS = 80;
char DUNGEON[21][80];
int failedRoomCreation =0;
int numberOfRooms =0;

// Function to display the dungeon to the console 
void printDungeon(){

	int i,j;

	// TOP BORDER
	for(i=0;i<COLS+2;i++){
		printf("-");
	}
	printf("\n");

	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			
			if(j == 0)
				printf("| "); // LEFT BORDER
			
			printf("%c", DUNGEON[i][j]);

			 if(j==(COLS-1))
				printf("|"); // RIGHT BORDER
		}
		printf("\n");
	}

	// BOTTOM BORDER
	for(i=0;i<COLS+2;i++){
		printf("-");
	}
	printf("\n\n");
}

int pickAnumber(int min, int max){

	int r;
    int range = 1 + max - min;
	int buckets = RAND_MAX / range;
	int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}
bool allClear(int roomWidth, int roomHeight, int roomPosition[2]){

	int i,j;
	// Check if the room overlaps with the existing room
	for(i=roomPosition[0]; i<=roomHeight; i++){
		for(j=roomPosition[1]; j<=roomWidth; j++){
			if(DUNGEON[i][j] == '.')
				printf("overlaps \n");
				return false;
		}
	}
	
	// Checks if the borders have no rooms
	// LEFT BORDER
	fosr(i=0; i<ROWS; i++){
		if(DUNGEON[i][0] == '.'){
			printf("Map left border\n");
			return false;
		}
	}
	// TOP BORDER
	for(i=0; i<COLS; i++){
		if(DUNGEON[0][i] == '.'){
			printf("Map top border\n");
			return false;
		}
	}// RIGHT BORDER
	for(i=0; i<ROWS; i++){
		if(DUNGEON[i][COLS-1] == '.'){
			printf("Map right border\n");
			return false;
		}
	}// BOTTOM BORDER
	for(int i=0; i<COLS; i++){
		if(DUNGEON[ROWS-1][i] == '.'){
			printf("Map bottom border\n");
			return false;
		}
	}

	// Checks if there a room adjacent to it
	// LEFT ADJACENT
	for(i=roomPosition[0]; i< roomPosition[0]+roomHeight; i++){
		if(DUNGEON[i][roomPosition[1]-1] == '.')
			printf("left adjacent\n");
			return false;
	}
	// TOP ADJACENT
	for(i=roomPosition[1]; i< roomPosition[1]+roomWidth; i++){
		if(DUNGEON[roomPosition[0]-1][i] == '.')
			printf("top adjacent\n");
			return false;
	}
	// RIGHT ADJACENT
	for(i=roomPosition[0]; i< roomPosition[0]+roomHeight; i++){
		if(DUNGEON[i][roomPosition[1]+1] == '.')
			printf("right adjacent\n");
			return false;
	}
	// BOTTOM ADJACENT
	for(i=roomPosition[1]; i< roomPosition[1]+roomWidth; i++){
		if(DUNGEON[roomPosition[0]+1][i] == '.')
			printf("bottom adjacent\n");
			return false;
	}


	return true;
}

void addTheRoom(int roomWidth, int roomHeight, int roomPosition[2])
{
	int i,j;
	printf("%d %d %d %d\n", roomWidth, roomHeight, roomPosition[0], roomPosition[1] );
	for(i=roomPosition[0]; i<roomHeight; i++){
		for(j=roomPosition[1]; j<roomWidth; j++){
			DUNGEON[i][j] = '.';
		}
	}

	printDungeon();

}
void generateRooms(){

	// The (0,0) / origin of the dungeon is the top left corner 
	int roomWidth;
	int roomHeight;
	// The top left position, where
	// index 0 = y coordinate
	// index 1 = x coordinate
	int roomPosition[2];

	// Checks if all the conditions are met while generating a room
	//bool eveythinChecksOut = false;
	

	while (failedRoomCreation < 1000){
		
		roomWidth = pickAnumber(3,79);
		roomHeight= pickAnumber(2,20);
		int roomXPosition = pickAnumber(1,73);
		int roomYPosition = pickAnumber(1,14);
		roomPosition[0] = roomYPosition;
		roomPosition[1] = roomXPosition;
		
		if (allClear(roomWidth,roomHeight,roomPosition) == true)
		{
			addTheRoom(roomWidth, roomHeight, roomPosition);
		}

		failedRoomCreation++;
	}

}


int main (int argc, char *argv[]) {     srand(time(NULL));
	
	int i,j;

	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			DUNGEON[i][j] = ' ';
		}
	}

	generateRooms();
	printDungeon();


	
	return 0;
}



