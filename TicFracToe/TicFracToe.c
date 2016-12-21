// TicFracToe.c
// alphaBuild
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

void printGrid();
void printGuide();
void resetArray(int array[]);
int checkForWin(int array[]);
void getInput(char input[]);
void instruct(int number, char player);
void currentGrid(char grid);
int playerMove(char player, int space, int grid[]);
int gridNumAssign(char grid);
void printSubGrids(int TopLeft[], int TopCntr[], int TopRght[], int MidLeft[], int MidCntr[], int MidRght[], int LowLeft[], int LowCntr[], int LowRght[]);


int main(int argc, char *argv[]){
	//Initialize arrays
	int TopLeft[9], TopCntr[9], TopRght[9];
	int MidLeft[9], MidCntr[9], MidRght[9];
	int LowLeft[9], LowCntr[9], LowRght[9];
	int MainBoard[9];
	//Set all arrays to empty
	resetArray(TopLeft);
	resetArray(TopCntr);
	resetArray(TopRght);
	resetArray(MidLeft);
	resetArray(MidCntr);
	resetArray(MidRght);
	resetArray(LowLeft);
	resetArray(LowCntr);
	resetArray(LowRght);
	resetArray(MainBoard);

	char input[1]; //This will be used by the getInput function 
	char grid = '\n'; //used to keep track of active grid
	int winner = 0; //Keeps track of winner of game (0 = active game, 1 = X, 2 = O).
	char player = 'X'; //curret player, X goes first
	int moveComplete = 0;
	int gridSelected = 0;
	int space = 0;

	initscr(); // Initialize the window
	noecho(); // Don't echo any keypresses
	curs_set(FALSE); // Don't display a cursor
	printGrid(); //Print playing grid
	printGuide(); //Print playing guide	
	refresh(); //Commit changes to screen

	//This is the loop where the game is played
	while(winner == 0){//THIS IS THE MAIN LOOP. THIS IS IT. THERE IS A MAIN LOOP AND IT IS THIS ONE RIGHT HERE. LOOK FOR THIS LONG COMMENT.
		while(gridSelected == 0){//This loops if there isn't an active grid
			instruct(1, player);//Tell the player to choose a grid
			getInput(input);//Player chooses a grid
			if(MainBoard[gridNumAssign(input[0])] == 0){ //Determines if that grid has been won yet
				grid = input[0];
				currentGrid(grid);
				refresh();
				gridSelected = 1;
			}
			
		}
		moveComplete = 0;
		while(moveComplete == 0){		
			currentGrid(grid);
			refresh();
			instruct(2, player); //tells player to make their move
			getInput(input); //Player chooses a space
			space = input[0]; //space is assigned to variable
			switch(gridNumAssign(grid)){
				case 0: 
					if(playerMove(player, gridNumAssign(space), TopLeft) == 1){
						moveComplete = 1;
						break;
					}
				case 1: 
					if(playerMove(player, gridNumAssign(space), TopCntr) == 1){
						moveComplete = 1;
						break;
					}
				case 2: 
					if(playerMove(player, gridNumAssign(space), TopRght) == 1){
						moveComplete = 1;
						break;
					}
				case 3: 
					if(playerMove(player, gridNumAssign(space), MidLeft) == 1){
						moveComplete = 1;
						break;
					}
				case 4: 
					if(playerMove(player, gridNumAssign(space), MidCntr) == 1){
						moveComplete = 1;
						break;
					}
				case 5: 
					if(playerMove(player, gridNumAssign(space), MidRght) == 1){
						moveComplete = 1;
						break;
					}
				case 6: 
					if(playerMove(player, gridNumAssign(space), LowLeft) == 1){
						moveComplete = 1;
						break;
					}
				case 7: 
					if(playerMove(player, gridNumAssign(space), LowCntr) == 1){
						moveComplete = 1;
						break;
					}

				case 8: 
					if(playerMove(player, gridNumAssign(space), LowRght) == 1){
						moveComplete = 1;
						break;
					}		
			}
			
			printSubGrids(TopLeft, TopCntr, TopRght, MidLeft, MidCntr, MidRght, LowLeft, LowCntr, LowRght);

			//This block of code checks all board for win conditions including the main board
			MainBoard[0] = checkForWin(TopLeft);
			MainBoard[1] = checkForWin(TopCntr);
			MainBoard[2] = checkForWin(TopRght);
			MainBoard[3] = checkForWin(MidLeft);
			MainBoard[4] = checkForWin(MidCntr);
			MainBoard[5] = checkForWin(MidRght);
			MainBoard[6] = checkForWin(LowLeft);
			MainBoard[7] = checkForWin(LowCntr);
			MainBoard[8] = checkForWin(LowRght);
			
			winner = checkForWin(MainBoard);
			
			refresh();
			moveComplete = 1; //end turn

			//swap active player
			if(player == 'X'){
				player = 'O';
			}
			else if(player == 'O'){
				player = 'X';
			}
			
			//Assign grid for next move
			if(MainBoard[gridNumAssign(space)] == 0){
				grid = space;
				gridSelected = 1;
			}
			else{
				gridSelected = 0;
			}
			refresh();
		}
	}

	sleep(10);
	endwin(); //Exit Ncurses
	return 0;
}

int playerMove(char player, int space, int grid[]){
	int mark = 0;
	if(player == 'X'){
		mark = 1;
	}
	else if(player == 'O'){
		mark = 2;
	}
	
	if(grid[space] == 0){ //spot is empty
		grid[space] = mark; //mark spot for player
		return 1; //marked successfully
	}
	else{
		return 0; //marking failed as space was occupied
	}
}

void instruct(int number, char player){ //Takes instruction number and current player
	int i; //variable used to clear lines
	switch(number){
		case 0: //Clear instruction line
			for(i=0;i<100;i++){
				mvprintw(17, i, " ");
			}
			refresh();
			break;
		case 1: //Tell $PLAYER to choose a grid to play on
			for(i=0;i<100;i++){
				mvprintw(17, i, " ");
			}
			mvprintw(17, 2, "%c: Choose a sub-grid to play on.", player);
			refresh();
			break;
		case 2: //Tell $PLAYER to make their move
			for(i=0;i<100;i++){
				mvprintw(17, i, " ");
			}
			mvprintw(17, 2, "%c: Make make your move.", player);
			refresh();
			break;

	}
}

void currentGrid(char grid){
	int i;
	for(i=0;i<30;i++){
		mvprintw(21, i, " ");
	}
	if(grid == 'q'){
		mvprintw(21, 2, "Upper Left");
	}
	else if(grid == 'w'){
		mvprintw(21, 2, "Upper Center");
	}
	else if(grid == 'e'){
		mvprintw(21, 2, "Upper Right");
	}
	else if(grid == 'a'){
		mvprintw(21, 2, "Middle Left");
	}
	else if(grid == 's'){
		mvprintw(21, 2, "Middle Center");
	}
	else if(grid == 'd'){
		mvprintw(21, 2, "Middle Right");
	}
	else if(grid == 'z'){
		mvprintw(21, 2, "Lower Left");
	}
	else if(grid == 'x'){
		mvprintw(21, 2, "Lower Center");
	}
	else if(grid == 'c'){
		mvprintw(21, 2, "Lower Right");
	}
	else{
		mvprintw(21, 2, "Something's Broken.");
	}
}

int gridNumAssign(char grid){
	int gridNum;
	//These statements translate the grid character into a number
	if(grid == 'q'){
		gridNum = 0;
	}
	else if(grid == 'w'){
		gridNum = 1;
	}
	else if(grid == 'e'){
		gridNum = 2;
	}
	else if(grid == 'a'){
		gridNum = 3;
	}
	else if(grid == 's'){
		gridNum = 4;
	}
	else if(grid == 'd'){
		gridNum = 5;
	}
	else if(grid == 'z'){
		gridNum = 6;
	}
	else if(grid == 'x'){
		gridNum = 7;
	}
	else if(grid == 'c'){
		gridNum = 8;
	}
	
	//This part checks if that grid has been won yet.
	//It returns 0 if nobody has won it, 1 if X has it, and 2 if O has it.
	return(gridNum);
}


void getInput(char input[]){//Should only return one of the follwoing: q, w, e, a, s, d, z, x, c.
	int inputGood = 0; //Declares that a good input hasn't been received yet
	char temp = '0', tempTwo = '0'; //These two variables are used as a buffer
	char validInputs[9] = {'q','w','e','a','s','d','z','x','c'}; //acceptable inputs
	int i = 0;
	while(inputGood == 0){
		temp = getch(); //get current input from keyboard
	
		while(temp != '\n'){ //If there isn't a newline character ('enter' key)
			tempTwo = temp; //Adjust buffer
			mvprintw(24, 17, "%c ", tempTwo);
			for(i=0;i<9;i++){
				if(tempTwo == validInputs[i]){
					mvprintw(24, 19, "(valid input)      ");
					break;
				}
				if(i==8 && tempTwo != validInputs[8]){
					mvprintw(24, 19, "(NOT valid input)");
				}
			}
			temp = getch();	//Check for character
		}
		for(i=0;i<8;i++){
			if(tempTwo == validInputs[i]){
				inputGood = 1;
				input[0] = tempTwo;
				break;
			}
		}	

	}
}


void printGrid(){
	int i;
	//First two loops print vertical lines
	for(i=1;i<=15;i++){
		mvprintw(i, 5, "|");
	}
	for(i=1;i<=15;i++){
		mvprintw(i, 11, "|");
	}
	//Second two loops print horizontal lines
	for(i=1;i<=15;i++){
		mvprintw(5, i, "-");
	}
	for(i=1;i<=15;i++){
		mvprintw(11, i, "-");
	}
	//Last few statements place a + at the intersections
	mvprintw(5, 5, "+");
	mvprintw(5, 11, "+");
	mvprintw(11, 5, "+");
	mvprintw(11, 11, "+");
	//set up lines on bottom of the screen
	mvprintw(20, 2, "Current Grid:");
	mvprintw(24, 2, "Current Input:");
	refresh(); //commit changes to the screen
}

void printGuide(){
	//prints guide in upper right corner
	mvprintw(2, 18, "*GUIDE*");
	mvprintw(4, 18, " Q|W|E ");
	mvprintw(5, 18, " -+-+- ");
	mvprintw(6, 18, " A|S|D ");
	mvprintw(7, 18, " -+-+- ");
	mvprintw(8, 18, " Z|X|C ");


}

void resetArray(int array[]){
	int i;
	for(i=0;i<9;i++){
		array[i] = 0;
	}
}

int checkForWin(int array[]){
	//return 1 if X wins
	//return 2 if O wins
	//return 0 if no winner
	
	if(array[4] == 1){
		if(array[1] == 1 && array[7] == 1){
			return 1;
		}
		if(array[3] == 1 && array[5] == 1){
			return 1;
		}
		if(array[2] == 1 && array[6] == 1){
			return 1;
		}
		if(array[0] == 1 && array[8] == 1){
			return 1;
		}
	}

	if(array[0] == 1){
		if(array[1] == 1 && array[2] == 1){
			return 1;
		}
		if(array[3] == 1 && array[6] == 1){
			return 1;
		}
	}

	if(array[8] == 1){
		if(array[2] == 1 && array[5] == 1){
			return 1;
		}
		if(array[7] == 1 && array [6] == 1){
			return 1;
		}
	}

	if(array[4] == 2){
		if(array[1] == 2 && array[7] == 2){
			return 2;
		}
		if(array[3] == 2 && array[5] == 2){
			return 2;
		}
		if(array[2] == 2 && array[6] == 2){
			return 2;
		}
		if(array[0] == 2 && array[8] == 2){
			return 2;
		}
	}

	if(array[0] == 1){
		if(array[1] == 2 && array[2] == 2){
			return 2;
		}
		if(array[3] == 2 && array[6] == 2){
			return 2;
		}
	}

	if(array[8] == 1){
		if(array[2] == 2 && array[5] == 2){
			return 2;
		}
		if(array[7] == 2 && array [6] == 2){
			return 2;
		}
	}
	
	return 0;
}

void printSubGrids(int TopLeft[], int TopCntr[], int TopRght[], int MidLeft[], int MidCntr[], int MidRght[], int LowLeft[], int LowCntr[], int LowRght[]){
	int i = 0;
	
	//I know this is a horrible function. I should have done this whole thing differently, and I apologize to anyone to looks at the following 300 lines.
	
	
	//Print Top Left
	for(i=0;i<3;i++){
		if(TopLeft[i] == 0){
			mvprintw(1, 1+i, " ");
		}
		if(TopLeft[i] == 1){
			mvprintw(1, 1+i, "X");
		}
		if(TopLeft[i] == 2){
			mvprintw(1, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopLeft[i+3] == 0){
			mvprintw(2, 1+i, " ");
		}
		if(TopLeft[i+3] == 1){
			mvprintw(2, 1+i, "X");
		}
		if(TopLeft[i+3] == 2){
			mvprintw(2, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopLeft[i+6] == 0){
			mvprintw(3, 1+i, " ");
		}
		if(TopLeft[i+6] == 1){
			mvprintw(3, 1+i, "X");
		}
		if(TopLeft[i+6] == 2){
			mvprintw(3, 1+i, "O");
		}
	}
	//Print Top Center
	for(i=0;i<3;i++){
		if(TopCntr[i] == 0){
			mvprintw(1, 7+i, " ");
		}
		if(TopCntr[i] == 1){
			mvprintw(1, 7+i, "X");
		}
		if(TopCntr[i] == 2){
			mvprintw(1, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopCntr[i+3] == 0){
			mvprintw(2, 7+i, " ");
		}
		if(TopCntr[i+3] == 1){
			mvprintw(2, 7+i, "X");
		}
		if(TopCntr[i+3] == 2){
			mvprintw(2, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopCntr[i+6] == 0){
			mvprintw(3, 7+i, " ");
		}
		if(TopCntr[i+6] == 1){
			mvprintw(3, 7+i, "X");
		}
		if(TopCntr[i+6] == 2){
			mvprintw(3, 7+i, "O");
		}
	}
	//Print Top Right
	for(i=0;i<3;i++){
		if(TopRght[i] == 0){
			mvprintw(1, 13+i, " ");
		}
		if(TopRght[i] == 1){
			mvprintw(1, 13+i, "X");
		}
		if(TopRght[i] == 2){
			mvprintw(1, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopRght[i+3] == 0){
			mvprintw(2, 13+i, " ");
		}
		if(TopRght[i+3] == 1){
			mvprintw(2, 13+i, "X");
		}
		if(TopRght[i+3] == 2){
			mvprintw(2, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(TopRght[i+6] == 0){
			mvprintw(3, 13+i, " ");
		}
		if(TopRght[i+6] == 1){
			mvprintw(3, 13+i, "X");
		}
		if(TopRght[i+6] == 2){
			mvprintw(3, 13+i, "O");
		}
	}
	//Print Middle Left
	for(i=0;i<3;i++){
		if(MidLeft[i] == 0){
			mvprintw(7, 1+i, " ");
		}
		if(MidLeft[i] == 1){
			mvprintw(7, 1+i, "X");
		}
		if(MidLeft[i] == 2){
			mvprintw(7, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidLeft[i+3] == 0){
			mvprintw(8, 1+i, " ");
		}
		if(MidLeft[i+3] == 1){
			mvprintw(8, 1+i, "X");
		}
		if(MidLeft[i+3] == 2){
			mvprintw(8, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidLeft[i+6] == 0){
			mvprintw(9, 1+i, " ");
		}
		if(MidLeft[i+6] == 1){
			mvprintw(9, 1+i, "X");
		}
		if(MidLeft[i+6] == 2){
			mvprintw(9, 1+i, "O");
		}
	}
	//Print Middle Center
	for(i=0;i<3;i++){
		if(MidCntr[i] == 0){
			mvprintw(7, 7+i, " ");
		}
		if(MidCntr[i] == 1){
			mvprintw(7, 7+i, "X");
		}
		if(MidCntr[i] == 2){
			mvprintw(7, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidCntr[i+3] == 0){
			mvprintw(8, 7+i, " ");
		}
		if(MidCntr[i+3] == 1){
			mvprintw(8, 7+i, "X");
		}
		if(MidCntr[i+3] == 2){
			mvprintw(8, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidCntr[i+6] == 0){
			mvprintw(9, 7+i, " ");
		}
		if(MidCntr[i+6] == 1){
			mvprintw(9, 7+i, "X");
		}
		if(MidCntr[i+6] == 2){
			mvprintw(9, 7+i, "O");
		}
	}
	//Print Middle Right
	for(i=0;i<3;i++){
		if(MidRght[i] == 0){
			mvprintw(7, 13+i, " ");
		}
		if(MidRght[i] == 1){
			mvprintw(7, 13+i, "X");
		}
		if(MidRght[i] == 2){
			mvprintw(7, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidRght[i+3] == 0){
			mvprintw(8, 13+i, " ");
		}
		if(MidRght[i+3] == 1){
			mvprintw(8, 13+i, "X");
		}
		if(MidRght[i+3] == 2){
			mvprintw(8, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(MidRght[i+6] == 0){
			mvprintw(9, 13+i, " ");
		}
		if(MidRght[i+6] == 1){
			mvprintw(9, 13+i, "X");
		}
		if(MidRght[i+6] == 2){
			mvprintw(9, 13+i, "O");
		}
	}
	//Print Bottom Left
	for(i=0;i<3;i++){
		if(LowLeft[i] == 0){
			mvprintw(13, 1+i, " ");
		}
		if(LowLeft[i] == 1){
			mvprintw(13, 1+i, "X");
		}
		if(LowLeft[i] == 2){
			mvprintw(13, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowLeft[i+3] == 0){
			mvprintw(14, 1+i, " ");
		}
		if(LowLeft[i+3] == 1){
			mvprintw(14, 1+i, "X");
		}
		if(LowLeft[i+3] == 2){
			mvprintw(14, 1+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowLeft[i+6] == 0){
			mvprintw(15, 1+i, " ");
		}
		if(LowLeft[i+6] == 1){
			mvprintw(15, 1+i, "X");
		}
		if(LowLeft[i+6] == 2){
			mvprintw(15, 1+i, "O");
		}
	}
	//Print Bottom Center
	for(i=0;i<3;i++){
		if(LowCntr[i] == 0){
			mvprintw(13, 7+i, " ");
		}
		if(LowCntr[i] == 1){
			mvprintw(13, 7+i, "X");
		}
		if(LowCntr[i] == 2){
			mvprintw(13, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowCntr[i+3] == 0){
			mvprintw(14, 7+i, " ");
		}
		if(LowCntr[i+3] == 1){
			mvprintw(14, 7+i, "X");
		}
		if(LowCntr[i+3] == 2){
			mvprintw(14, 7+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowCntr[i+6] == 0){
			mvprintw(15, 7+i, " ");
		}
		if(LowCntr[i+6] == 1){
			mvprintw(15, 7+i, "X");
		}
		if(LowCntr[i+6] == 2){
			mvprintw(15, 7+i, "O");
		}
	}
	//Print Bottom Right
	for(i=0;i<3;i++){
		if(LowRght[i] == 0){
			mvprintw(13, 13+i, " ");
		}
		if(LowRght[i] == 1){
			mvprintw(13, 13+i, "X");
		}
		if(LowRght[i] == 2){
			mvprintw(13, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowRght[i+3] == 0){
			mvprintw(14, 13+i, " ");
		}
		if(LowRght[i+3] == 1){
			mvprintw(14, 13+i, "X");
		}
		if(LowRght[i+3] == 2){
			mvprintw(14, 13+i, "O");
		}
	}
	for(i=0;i<3;i++){
		if(LowRght[i+6] == 0){
			mvprintw(14, 13+i, " ");
		}
		if(LowRght[i+6] == 1){
			mvprintw(14, 13+i, "X");
		}
		if(LowRght[i+6] == 2){
			mvprintw(14, 13+i, "O");
		}
	}
}		
