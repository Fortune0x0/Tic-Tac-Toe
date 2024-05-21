#include <iostream>
#include <vector>
using namespace std;
char board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int Array_size = 9;
char human = 'X';
char ai = 'O';
int plays = 0;
void Screen() {
	int counter = 0;
	int index = 0;
	for (int i = 1; i <= 3; ++i) {
		index = counter * 3;
		cout << "                                        \n";
		cout << "\t\t\t\t\t ";
		for (int j = index; j < i * 3; ++j) {
			if (j == i * 3 - 1) {
				cout << "____" << board[j] << "___";
			}
			else {
				cout << "____" << board[j] << "___|";
			}


		}
		++counter;
		cout << endl << endl;
	}

}
char checkWinner() {
	/*board[0] = human;
	board[1] = human;
	board[2] = human;*/
	int k = 3;
	const int Winners[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
	for (auto winner : Winners) {
		if (board[winner[0]] == board[winner[1]] && board[winner[2]] == board[winner[0]]) {
			return board[winner[0]];
		}
	}
	for (int i = 0; i < Array_size; ++i) {
		if (board[i] - '0' == i + 1) {
			return 'o';
		}
	}

	return '\0';
}





int miniMax(char player, bool isMaximaxing, int score) {
	char check = checkWinner();
	if (check == human) {		
		return 1;
	}
	if (check == ai) {
		return -1;
	}
	if (check == '\0') {
		return 0;
	}
	if (isMaximaxing) {
		int bestscore = -1000;
		for (int i = 0; i < Array_size; ++i) {
			if (board[i] != ai && board[i] != human) {
				board[i] = '2';
				
				int score = miniMax(ai, false, 0);
				board[i] = (i + 1) + '0';
				bestscore = max(score, bestscore);
				/*if (score > bestscore) {
					bestscore = score;
				}*/
			}
		}
		return bestscore;
	}
	if (!isMaximaxing) {
		int bestscore = 1000;
		for (int i = 0; i < Array_size; ++i) {
			if (board[i] != ai && board[i] != human) {
				board[i] = '1';
				int score = miniMax(ai, true, 0);
				board[i] = (i + 1) + '0';
				bestscore = min(score, bestscore);
				/*if (score < bestscore) {
					bestscore = score;
				}*/
			}
		}
		return bestscore;
	}
}













pair <int, int> miniMax2(char player, bool isMaximaxing, int previous) {
	/*Screen();
	cout << endl;*/
	char check = checkWinner();
	pair<int, int> score = make_pair(1,0);
	if (check == human) {
		score.first = 1;
		return score;;
	}
	if (check == ai) {
		score.first = -1;
		return score;
	}
	if (check == '\0') {
		score.first = 0;
		return score;
	}
	if (isMaximaxing) {
		int bestscore = -1000;
		int index = 0;
		
		for (int i = 0; i < Array_size; ++i) {
			if (board[i] != ai && board[i] != human) {
				board[i] = player;
				pair<int, int>score = miniMax2(ai, false, 0);
				board[i] = (i + 1) + '0';
				//bestscore = max(score, bestscore);
				if (score.first > bestscore) {
					bestscore = score.first;
					index = i;
				}
			}
		}
		pair<int, int> final = make_pair(bestscore, index);
		return final;
	}
	if (!isMaximaxing) {
		int bestscore = 1000;
		int index = 0;
		for (int i = 0; i < Array_size; ++i) {
			if (board[i] != ai && board[i] != human) {
				board[i] = player;
				pair<int,int >score = miniMax2(human, true, 0);
				board[i] = (i + 1) + '0';
				if (score.first < bestscore) {
					bestscore = score.first;
					index = i;
				}
			}
		}
		pair<int, int> final = make_pair(bestscore, index);
		return final;
	}
}

pair<int, int> re_evaluate() {
	pair<int, int> Ai = miniMax2(ai, false, 0);
	const int Winners[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
	for (auto winner : Winners) {
		if (board[winner[0]] == board[winner[1]] && board[winner[0]] == ai && board[winner[2]] != human) {
			Ai.second = winner[2];
		}
		if (board[winner[0]] == board[winner[2]] && board[winner[0]] == ai && board[winner[1]] != human) {
			Ai.second = winner[1];
		}
		if (board[winner[2]] == board[winner[1]]  && board[winner[1]] == ai && board[winner[0]] != human) {
			Ai.second = winner[0];
		}
	}
	return Ai;
}
void AssignAiPlays() {
	Screen();
	char Winner = checkWinner();
	if (Winner != 'o') {
		if (Winner == '\0') {
			cout << "It was a Draw" << endl;
		}
		else {
			cout << Winner << " won the game!" << endl;
		}
		exit(0);
	}
	int pick;
	cout << "                                         Pick your move: ";
	cin >> pick;
	board[pick - 1] = human;
	//cout << "previousboar: " << board[8] << endl;
	//nt Ai = miniMax(ai, true, 0);
	pair <int, int> Ai = re_evaluate();
	//pair <int, int> Ai = miniMax2(ai, false, 0);
	cout << "Ai was: " << Ai.second << endl; //It returns size of array
	board[Ai.second] = ai;


	AssignAiPlays();
}


int main() {


//board[2] = human;
//board[4] = ai;


	
	
	AssignAiPlays();
	
	//check_Winner_2();
	//AssignAiPlays();

	//checkBestMoves(human);

	//cout << a << endl;
	//cout << checkWinner();
}