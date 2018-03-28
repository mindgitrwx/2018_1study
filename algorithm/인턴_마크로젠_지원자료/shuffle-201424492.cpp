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

		for (int i = 1; i <= Length; i++){     //  (i%k) �� 0�϶� PullOutAndBack ���� -> �� ī�尡 k�� �����° ��ġ�� ���� ��.
			if (!(i%k)) PullOutAndBack();      //  card�� ���� ���� �ڷ� �ְ� list�� currentCard�� �� ī�� �ٷ� ������ ī��� �ٲٴ� �۾� �ݺ�
			currentCard = next(currentCard);   //  ����ؼ� currentCard�� �����͸� �������� �̵�
		}
	}

	void PullOutAndBack()                                    // ' ' -> current card Pointer , " " -> temp card Pointer, ���� ���� k = 5�� ����, i = 5�϶�
	{                                                        // a b c  d  'e' f g h i
		tempIterator = prev(currentCard);                    // a b c "d" 'e' f g h i
		cardSet.splice(cardSet.end(), cardSet, currentCard); // a b c "d"     f g h i e  // cardset�� ������ cardset currentCard�� �Űܳ���
     	currentCard = tempIterator;                          // a b c 'd'     f g h i e
	}                                                        // a b c  d     'f'g h i e  // Shuffle���� next(currentCard)�� ��������
	void Cut(int i, int j){
		cutStart = cardSet.begin();
		cutEnd   = cardSet.begin();
		advance(cutStart, i-1);
		advance(cutEnd  , j  );
		cardSet.splice(cardSet.end(), cardSet, cutStart, cutEnd); // cardSet�� ����, (cardSet��, cutStart�� ��ġ����, cutEnd��ġ������) ī�带 �߶� ���̱�
	}

	void ReadFile(istream& in){
		int cardNum, impleN;
		int start, end, k;
		string imple;

		in >> cardNum >> impleN;
		for (int i = 1; i <= cardNum; i++) cardSet.push_back(i); // �������� �ʱ�ȭ
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
	void WriteFile(ostream& out){ //cardSet���� ������ ī���ȣ�� ��� ���
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
