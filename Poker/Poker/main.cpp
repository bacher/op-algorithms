#include <fstream>

using namespace std;

int main() {
	ifstream f_in("poker.in");
	ofstream f_out("poker.out");

	long cards[5];
	f_in >> cards[0] >> cards[1] >> cards[2] >> cards[3] >> cards[4];
	f_in.close();


	int cards_count[14];
	memset(cards_count, 0, sizeof(cards_count));

	for(int i = 0; i < 5; ++i) {
		cards_count[cards[i]]++;
	}

	int max_card_count = 0;
	int sec_max_card_count = 0;

	long value;
	for(int i = 1; i < 14; ++i) {
		value = cards_count[i];
		if(max_card_count < value) {
			sec_max_card_count = max_card_count;
			max_card_count = value;
		} else if(sec_max_card_count < value) {
			sec_max_card_count = value;
		}
	}

	if(max_card_count == 5) f_out << "Impossible";
	else if(max_card_count == 4) f_out << "Four of a Kind";
	else if(max_card_count == 3 && sec_max_card_count == 2) f_out << "Full House";
	else if(max_card_count == 3) f_out << "Three of a Kind";
	else if(max_card_count == 2 && sec_max_card_count == 2) f_out << "Two Pairs";
	else if(max_card_count == 2) f_out << "One Pair";
	else {
		int series_lenght = 0;
		for(int i = 0; i < 14; ++i) {
			if(cards_count[i] == 1) {
				series_lenght++;
				if(series_lenght == 5) {
					f_out << "Straight";
					break;
				}
			}
			else series_lenght = 0;
		}
		if(series_lenght != 5) f_out << "Nothing";
	}

	return 0;
}