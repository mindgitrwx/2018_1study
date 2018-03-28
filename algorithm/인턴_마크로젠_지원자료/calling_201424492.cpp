#include <fstream>
#include <string>
#include <stack>
#include <queue>
using namespace std;
struct StringInt
{
	string Alphabet;
	int address;
};
int main()
{
	StringInt FuncName[10];
	queue<string> Funcs[10];
	int n, place[3];
	int exiAlpha = 0, AllAlpha = 1;
	string s[3] = { "NONE", "NONE", "NONE" };
	stack<int> recurseStack;
	bool recurseCheck[10] = { 0 };
	string word;
	int i, j;
	int count = 0;
	ifstream in("calling.inp"); ofstream out("calling.out");
	in >> n >> place[0] >> place[1] >> place[2];

	for (i = 0; i<n; i++){

		in >> FuncName[i].Alphabet;
		FuncName[i].address = i;

		do{
			in >> word;
			Funcs[i].push(word);
			if ("A" <= word && word <= "Z")
				exiAlpha = 1;
		} while (word.compare("$"));

		if (!exiAlpha) AllAlpha = 0;
		exiAlpha = 0;
	}
	if (AllAlpha) { out << "DEADLOCK"; return 0; }
	i = 0;
	while ((word = Funcs[i].front()).compare("$") || i){
		Funcs[i].pop();
		Funcs[i].push(word);
		if ("A" <= word && word <= "Z"){
			recurseCheck[i] = 1;
			recurseStack.push(i);
			for (j = 0; j < n; j++){
				if (FuncName[j].Alphabet == word){
					i = FuncName[j].address;
					break;
				}
			}
			if (recurseCheck[i]){ out << "DEADLOCK"; return 0; }
			continue;
		}
		else if (word == "$"){
			recurseCheck[recurseStack.top()] = 0;
			i = recurseStack.top();
			recurseStack.pop();
			continue;
		}
		else{
			count++;
			for (j = 0; j < 3; j++)
				if (count == place[j]) { s[j] = FuncName[i].Alphabet + "-" + word; break;}
		}
	}
	for (i = 0; i < 3; i++)
		out << s[i] << "\n";
	return 0;
}
