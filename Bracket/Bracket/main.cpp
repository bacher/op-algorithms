#include <fstream>

using namespace std;

int main() {
	ifstream f_in("bracket.in");
	ofstream f_out("bracket.out");

	long bracket_count;
	f_in >> bracket_count;

	//// [2012-10-04]
	//// NOTE:
	//// Использовал концепцию стека, но реализовал за место него обычный массив.
	//// Плюсы:
	////  - Размер в памяти занимает существенно меньше
	////  - Адресация просисходит быстрее
	////  - Код получился намного наглядее и понятнее
	////
	char *bracket_stack = new char[bracket_count];
	int bracket_stack_index = -1;

	char bracket;
	bool success = true;
	for(int i = 0; i < bracket_count; ++i) {
		f_in >> bracket;
		if(bracket == '(' || bracket == '[' || bracket == '{') bracket_stack[++bracket_stack_index] = bracket;
		else if(bracket_stack_index >= 0) {
				 if(bracket == ')' && bracket_stack[bracket_stack_index] == '(') bracket_stack_index--;
			else if(bracket == ']' && bracket_stack[bracket_stack_index] == '[') bracket_stack_index--;
			else if(bracket == '}' && bracket_stack[bracket_stack_index] == '{') bracket_stack_index--;
			else {
				success = false; break;
			}
		} else {
			success = false; break;
		}
	}
	f_in.close();

	if(bracket_stack_index != -1) {
		f_out << "No";
	} else {
		f_out << (success ? "Yes" : "No");
	}
	f_out.close();
	return 0;
}