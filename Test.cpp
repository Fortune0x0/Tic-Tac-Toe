#include <iostream>
using namespace std;
char board[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int Array_size = 9;
char human = 'X';
char ai = 'O';
void AssignAiPlays();
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


void restart_game() {
	for (int i = 0; i < Array_size; ++i) {
		board[i] = (i + 1) + '0';
	}
	AssignAiPlays();
}

pair <int, int> miniMax2(char player, bool isMaximaxing, int previous) {
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
		cout << "Would you like to play again Y/N" << endl;
		char choice;
		cin >> choice;
		if (choice == 'Y') {
			restart_game();
		}
		else {
			exit(0);
		}
	}
	int pick;
	cout << "                                         Pick your move: ";
	cin >> pick;
	while (board[pick - 1] == human || board[pick - 1] == ai) {
		cout << "Cannot pick illegal moves" << endl;
		cout << "                                         Pick your move: ";
		cin >> pick;
	}
	board[pick - 1] = human;
	
	char game_state = checkWinner();
	if (game_state == 'o') {
		pair <int, int> Ai = re_evaluate();
		cout << "Ai (" << Ai.first << ",  " << Ai.second << ")" << endl;
		board[Ai.second] = ai;
	}
	
	
	AssignAiPlays();
}


int main() {
		
	AssignAiPlays();
}