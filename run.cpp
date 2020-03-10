#include <iostream>
#include "src/AirPort.hpp"
#include <thread>
using namespace std;
/****************************************************************************/
/********************** ��������� *******************************************/
/****************************************************************************/

int main(int argc, char **argv) {

	AirPort A, B, C;
	thread t1, t2, t3;
	while (1) {
		cout << "��Ҫ����ĸ������أ�" << endl;
		cout << "\t" << "����1: �������1" << endl;
		cout << "\t" << "����2: �������2" << endl;
		cout << "\t" << "����3: �������3" << endl;
		cout << "\t" << "����4: 3������һ����" << endl;
		int i;
		cin >> i;
		switch (i) {
		case 1:
			A.solution1();
			break;
		case 2:
			A.solution2();
			break;
		case 3:
			A.solution3();
			break;
		case 4:
			t1 = thread(&AirPort::solution1, ref(A));
			t2 = thread(&AirPort::solution2, ref(B));
			t3 = thread(&AirPort::solution3, ref(C));
			t1.join();
			t2.join();
			t3.join();
			break;
		default:
			cout << "���벻����Ҫ��" << endl;
			goto END;
		};
		cout << "..." << endl;
		cout << "complete!" << endl;
	END:	break;
	}
	cin.get();
	cin.get();
	return 0;
}

