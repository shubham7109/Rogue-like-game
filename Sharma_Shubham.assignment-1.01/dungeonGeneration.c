#include <stdio.h>
#include <time.h> // For srand() to truly get a random value
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
int numberOfRooms =0; // Keeps track of the number of rooms generated
int roomInformation[10][4]; // Keeps track of the info of each room
int roomEdgeInformation[10][2]; // Keeps track of the points corridors reach


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

// Picks a number between the bounds with the bounds included in the range
int pickAnumber(int min, int max){

	// This function was inspired from a code on StackOverflow
	int r;
    int range = 1 + max - min;
	int buckets = RAND_MAX / range;
	int limit = buckets * range;
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

// Checks if the room can spawn in the given information of the room
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

	// No flags raised, hence a room can spawn in the given position
	return true;
}

// Inserts the room in the dungeon using the given information
void addTheRoom(int roomWidth, int roomHeight, int roomPosition[2]){
	int i,j;
	
	for(i=roomPosition[0]; i<roomHeight+roomPosition[0]; i++){
		for(j=roomPosition[1]; j<roomWidth+roomPosition[1]; j++){
			DUNGEON[i][j] = '.';
		}
	}
}

// Generates min 5 rooms in the dungeon following the assignment specs
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

// Returns the information of the room (like width/height)
int getRoomInformationVlaue(int leftIndex, int rightIndex){
	int value = roomInformation[leftIndex][rightIndex];
	return value;
}

// Generates edge points for the corridors to connect across the rooms
void generateRoomEdge(){

	int i;
	// Pickes a side such a top, bottom, left or right

	for(i=0; i<numberOfRooms; i++)
	{
		int xPosition = getRoomInformationVlaue(i,3);
		int yPosition = getRoomInformationVlaue(i,2);
		roomEdgeInformation[i][0] = pickAnumber(yPosition,(yPosition-1)+getRoomInformationVlaue(i,1));
		roomEdgeInformation[i][1] = pickAnumber(xPosition,(xPosition-1)+getRoomInformationVlaue(i,0));
	}
}

// Generates all corridors across the dungeon following assignment specs
void generateCorridors(){

	int i,j;
	int corridorXPosition, corridorYPosition;
	corridorXPosition = roomEdgeInformation[0][1];
	corridorYPosition = roomEdgeInformation[0][0];

	for(i=0; i<numberOfRooms-1; i++){
		j = i+1; // Where i is the room1 and j is the next room
		int diffX =9;
		int diffY =9;
		while( diffY != 0 || diffX != 0)
		{
			diffY = corridorYPosition - roomEdgeInformation[j][0];
			diffX = corridorXPosition - roomEdgeInformation[j][1];
			
			if (DUNGEON[corridorYPosition][corridorXPosition] != '.'){
				DUNGEON[corridorYPosition][corridorXPosition] = '#';
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

// The main function of the code
int main (int argc, char *argv[]) {     
	
	// To ensure the code is truly random
	srand(time(NULL));
	int i,j;

	// Creates a blank dungeon
	for(i=0; i<ROWS; i++){
		for(j=0; j<COLS; j++){
			DUNGEON[i][j] = ' ';
		}
	}

	// The brains of the code
	generateRooms();
	generateRoomEdge();
	generateCorridors();

	// Prints the final DUNGEON
	printDungeon();

	return 0;
}

