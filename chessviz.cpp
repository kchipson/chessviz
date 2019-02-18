 #include <iostream> 
 using namespace std;

void out_board_consol(char board[8][8]){ // Функция отрисовки доски
	int i,j;
	for (i=7; i>-1;i--){
		for (j=0; j<8;j++){
			cout<<board[i][j]<<"  ";
		}
		cout<<endl;
	}
}

int main(){ 
	int i,j; // for cycles 
	char board[8][8]= {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
					   {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
					   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					   {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
					   {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
					   {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

	out_board_consol(board);
	return 0;
}