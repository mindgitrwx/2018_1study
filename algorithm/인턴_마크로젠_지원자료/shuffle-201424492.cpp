#include <fstream>
#include <string>
#include <list>
using namespace std;

class Card
{
private:
	list<int> cardSet;
	list<int>::iterator cutStart, cutEnd, currentCard, tempIterator, it;

public:

	void Shuffle(int k, int Length){
		currentCard = cardSet.begin();

		for (int i = 1; i <= Length; i++){     //  (i%k) 가 0일때 PullOutAndBack 수행 -> 즉 카드가 k의 배수번째 위치에 있을 때.
			if (!(i%k)) PullOutAndBack();      //  card를 한장 빼서 뒤로 넣고 list의 currentCard를 뺀 카드 바로 앞으로 카드로 바꾸는 작업 반복
			currentCard = next(currentCard);   //  계속해서 currentCard의 포인터를 다음으로 이동
		}
	}

	void PullOutAndBack()                                    // ' ' -> current card Pointer , " " -> temp card Pointer, 밑의 예는 k = 5라 가정, i = 5일때
	{                                                        // a b c  d  'e' f g h i
		tempIterator = prev(currentCard);                    // a b c "d" 'e' f g h i
		cardSet.splice(cardSet.end(), cardSet, currentCard); // a b c "d"     f g h i e  // cardset의 끝에다 cardset currentCard를 옮겨놓기
     	currentCard = tempIterator;                          // a b c 'd'     f g h i e
	}                                                        // a b c  d     'f'g h i e  // Shuffle에서 next(currentCard)를 거쳤을때
	void Cut(int i, int j){
		cutStart = cardSet.begin();
		cutEnd   = cardSet.begin();
		advance(cutStart, i-1);
		advance(cutEnd  , j  );
		cardSet.splice(cardSet.end(), cardSet, cutStart, cutEnd); // cardSet의 끝에, (cardSet의, cutStart의 위치부터, cutEnd위치까지의) 카드를 잘라 붙이기
	}

	void ReadFile(istream& in){
		int cardNum, impleN;
		int start, end, k;
		string imple;

		in >> cardNum >> impleN;
		for (int i = 1; i <= cardNum; i++) cardSet.push_back(i); // 오름차순 초기화
		for (int i = 0; i < impleN; i++){

			in >> imple;
			if  (imple == "Shuffle"){
				in >> k;
				Shuffle(k,cardNum);
			}
			else if (imple == "Cut"){
				in >> start >> end;
				Cut(start, end);
			}

		}
	}
	void WriteFile(ostream& out){ //cardSet에서 각각의 카드번호를 모두 출력
		for (it = cardSet.begin(); it != cardSet.end(); it++)
			out << (*it) << "\n";
	}
};

int main()
{
	ifstream in ("shuffle.inp");
	ofstream out("shuffle.out");

	Card card;

	card.ReadFile(in);
	card.WriteFile(out);

	return 0;
}
