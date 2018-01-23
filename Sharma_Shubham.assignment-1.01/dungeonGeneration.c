#include <stdio.h>
#include <time.h>
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
int roomInformation[10][4];
int roomEdgeInformation[10][2];
int centroid[2];
int storedRoomInformation[10][4];
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
				printf("|"); // LEFT BORDER
			
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

	// For roomPosition[]
	// index 0 = y coordinate
	// index 1 = x coordinate
	int i,j;
	// Check if the room overlaps with the existing room
	for(i=roomPosition[0]; i<=roomPosition[0]+roomHeight; i++){
		for(j=roomPosition[1]; j<=roomPosition[1]+roomWidth; j++){
			if(DUNGEON[i][j] == '.'){
				//printf("overlaps \n");
				return false;
			}
				
		}
	}
	
	// Checks if the borders have no rooms
	// LEFT BORDER
	for(i=0; i<ROWS; i++){
		if(DUNGEON[i][0] == '.'){
			//printf("Map left border\n");
			return false;
		}
	}
	// TOP BORDER
	for(i=0; i<COLS; i++){
		if(DUNGEON[0][i] == '.'){
			//printf("Map top border\n");
			return false;
		}
	}// RIGHT BORDER
	for(i=0; i<ROWS; i++){
		if(DUNGEON[i][COLS-1] == '.'){
			//printf("Map right border\n");
			return false;
		}
	}// BOTTOM BORDER
	for(i=0; i<COLS; i++){
		if(DUNGEON[ROWS-1][i] == '.'){
			//printf("Map bottom border\n");
			return false;
		}
	}
	if(roomPosition[0] <= 0 || roomPosition[1] <= 0 ||(roomPosition[0]+roomHeight) >= (ROWS-1) || (roomPosition[1]+roomWidth >= (COLS-1))){
		return false;
	}

	// Checks if there a room adjacent to it
	// LEFT ADJACENT
	for(i=roomPosition[0]; i< roomPosition[0]+roomHeight; i++){
		if(DUNGEON[i][roomPosition[1]-1] == '.'){
			//printf("left adjacent\n");
			return false;
		}
			
	}
	// TOP ADJACENT
	for(i=roomPosition[1]; i< roomPosition[1]+roomWidth; i++){
		if(DUNGEON[roomPosition[0]-1][i] == '.'){
			//printf("top adjacent\n");
			return false;
		}
			
	}
	// RIGHT ADJACENT
	for(i=roomPosition[0]; i< roomPosition[0]+roomHeight; i++){
		if(DUNGEON[i][roomPosition[1]+1] == '.'){
			//printf("right adjacent\n");
			return false;
		}
			
	}
	// BOTTOM ADJACENT
	for(i=roomPosition[1]; i< roomPosition[1]+roomWidth; i++){
		if(DUNGEON[roomPosition[0]+1][i] == '.'){
			//printf("bottom adjacent\n");
			return false;
		}
			
	}


	return true;
}

void addTheRoom(int roomWidth, int roomHeight, int roomPosition[2]){
	int i,j;
	
	for(i=roomPosition[0]; i<roomHeight+roomPosition[0]; i++){
		for(j=roomPosition[1]; j<roomWidth+roomPosition[1]; j++){
			DUNGEON[i][j] = '.';
		}
	}

	//printDungeon();
}

void generateRooms(){

	// The (0,0) / origin of the dungeon is the top left corner 
	int roomWidth;
	int roomHeight;
	// The top left position, where
	// index 0 = y coordinate
	// index 1 = x coordinate
	int roomPosition[2];
	//Decides how many rooms to create
	int maxRooms;
	maxRooms = pickAnumber(5,10);
	

	// Checks if all the conditions are met while generating a room
	while (failedRoomCreation < 2000){
		
		roomWidth = pickAnumber(3,30);
		roomHeight= pickAnumber(2,10);
		int roomXPosition = pickAnumber(1,73);
		int roomYPosition = pickAnumber(1,14);
		roomPosition[0] = roomYPosition;
		roomPosition[1] = roomXPosition;
		
		if (allClear(roomWidth,roomHeight,roomPosition) == true && numberOfRooms < maxRooms)
		{
			addTheRoom(roomWidth, roomHeight, roomPosition);
			roomInformation[numberOfRooms][0] = roomWidth;
			roomInformation[numberOfRooms][1] = roomHeight;
			roomInformation[numberOfRooms][2] = roomPosition[0];
			roomInformation[numberOfRooms][3] = roomPosition[1];
			numberOfRooms++;
			
		}

		failedRoomCreation++;
	}
}

int getRoomInformationVlaue(int leftIndex, int rightIndex){

	int value = roomInformation[leftIndex][rightIndex];
	return value;
}

void generateRoomEdge(){

	int i,j;
	// Pickes a side such a top, bottom, left or right

	for(i=0; i<numberOfRooms; i++)
	{
		int xPosition = getRoomInformationVlaue(i,3);
		int yPosition = getRoomInformationVlaue(i,2);
		roomEdgeInformation[i][0] = pickAnumber(yPosition,(yPosition-1)+getRoomInformationVlaue(i,1));
		roomEdgeInformation[i][1] = pickAnumber(xPosition,(xPosition-1)+getRoomInformationVlaue(i,0));
	}

}


// Generates corridors across the dungeon
void generateCorridors(){

	int i,j;
	int corridorXPosition, corridorYPosition;
	bool isNegX = false, isNegY = false;
	int roomNumber;
	corridorXPosition = roomEdgeInformation[0][1];
	corridorYPosition = roomEdgeInformation[0][0];
	int tries =0;

	for(i=0; i<numberOfRooms-1; i++){
		j = i+1; // Where i is the room1 and j is the next room
		int diffX =9;
		int diffY =9;
		while( diffY != 0 || diffX != 0)
		{

			diffY = corridorYPosition - roomEdgeInformation[j][0];
			diffX = corridorXPosition - roomEdgeInformation[j][1];
			
			
			if (DUNGEON[corridorYPosition][corridorXPosition] != '.'){
				/*
				printf("This is a space: corridorXPosition:%d corridorYPosition:%d DUNGEON[corridorYPosition][corridorYPosition]:[%c].\n",
					corridorXPosition,corridorYPosition,DUNGEON[corridorYPosition][corridorXPosition]);
				*/
				DUNGEON[corridorYPosition][corridorXPosition] = '#';
				//printDungeon();
			}


			// Move closer to position
			if(diffX < 0)
				corridorXPosition++;
			else if (diffX > 0)
				corridorXPosition--;

			if(diffY < 0)
				corridorYPosition++;
			else if(diffY > 0)
				corridorYPosition--;

		}
	}



}


int main (int argc, char *argv[]) {     
	
	srand(time(NULL));
	int i,j;

	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			DUNGEON[i][j] = ' ';
		}
	}


	generateRooms();
	generateRoomEdge();
	generateCorridors();
	/*
	for(i=0; i<numberOfRooms; i++)
	{
		DUNGEON[roomEdgeInformation[i][0]][roomEdgeInformation[i][1]] = i + '0';
	}*/
	printDungeon();

	return 0;
}

