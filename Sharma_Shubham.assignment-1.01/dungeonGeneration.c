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
int roomInformation[][4];
int roomEdgeInformation[][2];
int centroid[2];

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
	printf("roomWidth:%d roomHeight:%d yPosition:%d xPosition:%d\n", roomWidth, roomHeight, roomPosition[0], roomPosition[1] );
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
	
	printf("numberOfRooms: %d",numberOfRooms );
	printf(" maxRooms: %d\n",maxRooms );

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
	printf("numberOfRooms: %d",numberOfRooms );
	printf(" maxRooms: %d\n",maxRooms );
}

// Returns which roomNumber the given position is at
int positionsRoomNumber(int row, int col){
	
	int i,j;

	if (DUNGEON[row][col] != '.'){
		return -1;
	}
	
	int roomPosition[2] = {row,col};

	// if its at the border
	if(roomPosition[0] <= 0 || roomPosition[1] <= 0 ||(roomPosition[0]) >= (ROWS-1) || (roomPosition[1] >= (COLS-1))){
		return -2;
	}

	for(i=0; i< numberOfRooms; i++){
		// Checks X bounds
		if(roomInformation[i][3] <= col && (roomInformation[i][3]+roomInformation[i][0]-1) >= col) {

			printf("enters the loop\n");
			// Checks Y bounds
			if(roomInformation[i][2] <= row && (roomInformation[i][2]+roomInformation[i][1]-1) >= row){
				return i;
			}
		}
	}

	return -1;
}


void generateRoomEdge(){

	int i,j;
	// Pickes a side such a top, bottom, left or right
	int side;
	int xPosition;
	int yPosition;

	for(i=0; i<numberOfRooms; i++)
	{
		side = pickAnumber(1,4);
		// Left side
		if(side == 1){
		xPosition = roomInformation[i][3];
		yPosition = pickAnumber(roomInformation[i][2],roomInformation[i][2]+roomInformation[i][1]-1);
		}
		//Top Side
		if(side == 2){
		xPosition = pickAnumber(roomInformation[i][3],roomInformation[i][3]+roomInformation[i][0]-1);
		yPosition = roomInformation[i][2];
		}
		//Right Side
		if(side == 3){
		xPosition = roomInformation[i][3] + roomInformation[i][0]-1;
		yPosition = pickAnumber(roomInformation[i][2],roomInformation[i][2]+roomInformation[i][1]-1);
		}
		//Bottom Side
		if(side == 4){
		xPosition = pickAnumber(roomInformation[i][3],roomInformation[i][3]+roomInformation[i][0]-1);
		yPosition = roomInformation[i][2] + roomInformation[i][1]-1;
		}
		roomEdgeInformation[i][1] = xPosition;
		roomEdgeInformation[i][0] = yPosition;
		printf("%d: Side picked:%d numberOfRooms:%d xPosition:%d yPosition:%d\n",i,side,numberOfRooms,xPosition, yPosition);
	}
/*
		for(i=0; i<numberOfRooms; i++){
		DUNGEON[roomEdgeInformation[i][0]][roomEdgeInformation[i][1]] = i+'0';
		}

		printDungeon();

*/
}


// Generates corridors across the dungeon
void generateCorridors(){

	int i,j;
	int diffX, diffY;
	int corridorXPosition, corridorYPosition;
	bool isNegX = false, isNegY = false;
	corridorXPosition = roomEdgeInformation[0][1];
	corridorYPosition = roomEdgeInformation[0][0];
	int tries =0;
	for(i=0; i<numberOfRooms-1; i++){
		j = i+1; // Where i is the room1 and j is the next room

		while(positionsRoomNumber(corridorYPosition,corridorXPosition) != i && tries < 10)
		{
			corridorXPosition = roomEdgeInformation[i][1];
			corridorYPosition = roomEdgeInformation[i][0];
			diffY = roomEdgeInformation[i][0] - roomEdgeInformation[j][0];
			diffX = roomEdgeInformation[i][1] - roomEdgeInformation[j][1];
			
			// TODO
			// DO I REALLY NEEEEED THIS ?
			if (diffX < 0){
				isNegX = true;
			}
			if(diffY < 0){
				isNegY = true;
			}
			// TILL HERE ^^^^^



			int roomNumber = positionsRoomNumber(corridorYPosition, corridorXPosition);
			printf("i:%d tries:%d corridorXPosition:%d corridorYPosition:%d diffX:%d diffY:%d roomNumber:%d\n",i,tries,corridorXPosition,corridorYPosition,diffX,diffY,roomNumber);
		
			if (roomNumber == -1){
				printf("Enters if statement\n");
				DUNGEON[corridorYPosition][corridorXPosition] = '#';
				printDungeon();
			}

			if(roomNumber == -2){
				printf("DONT GO THERE!!!\n");
				// The corridor is going to the borders
			}

						// Move closer to position
			if(diffX < 0)
				corridorXPosition++;
			else
				corridorXPosition--;

			if(diffY < 0)
				corridorYPosition++;
			else
				corridorYPosition--;
			
			tries++;
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
/*
	int roomPosition[2] = {2,20};
	bool ret = allClear(12,6,roomPosition);
	if(ret){
		addTheRoom(12,6,roomPosition);
	}
	else{
		printf("Incorrect!\n");
	}
	

	roomPosition[0] = 10;
	roomPosition[1] = 17;
	ret = allClear(3, 3,roomPosition);
	if(ret){
		addTheRoom(3,3,roomPosition);
	}
	else
		printf("Incorrect!\n");
	
	printDungeon();
	numberOfRooms = 2;
	roomInformation[0][0] = 12;
	roomInformation[0][1] = 6;
	roomInformation[0][2] = 2;
	roomInformation[0][3] = 20;

	roomInformation[1][0] = 3;
	roomInformation[1][1] = 3;
	roomInformation[1][2] = 10;
	roomInformation[1][3] = 17;

	printf("%d\n",positionsRoomNumber(4,21) );

*/

	generateRooms();
	printDungeon();
	for(i=0; i<numberOfRooms; i++){
		printf("%d: roomWidth:%d roomHeight:%d yPosition:%d xPosition:%d\n",i,roomInformation[i][0],roomInformation[i][1],roomInformation[i][2],roomInformation[i][3]);
	}


	generateRoomEdge();
	printDungeon();
	generateCorridors();
	printDungeon();

	return 0;
}

