#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

void UsingMoneyMessage(int result, int money) {
	cout << result << "�� �Դϴ�!" << endl;
	cout << "���ݾ��� " << money << "000�� �Դϴ�." << endl;
	cout << endl;
}

int findRank(int lottery[7], int win[7]) {
	int result = 0;
	int cnt = 0;

	for (int i = 0; i < 6; i++) {
		if (binary_search(lottery, lottery + 6, win[i])) {
			cnt += 1;
		}
	}

	if (cnt == 6) {
		return 1;
	}
	else {
		if ((cnt == 5) & (binary_search(lottery + 6, lottery + 7, win[6]))) {
			return 2;
		}
		else if (cnt == 5) {
			return 3;
		}
		else {
			return 0;
		}
	}
}

bool checkNumber(int array[7], int num) {
	for (int i = 0; i < 7; i++) {
		if (array[i] == num) {
			return false;
		}
	}
	return true;
}

int main() {
	random_device numbers;
	mt19937 gen(numbers());
	uniform_int_distribution<int> dis(1, 45);

	int money, number;
	int i = 0;
	int result = 0;
	int win[7] = { 0, };
	int lottery[7] = { 0, };
	vector <long long> usingMoney[3];

	cout << "3�� �̻��� ��÷�� ���� ��� �ݾ��� ����մϴ�." << endl;
	cout << "�� ȸ���� �ִ� ��� �ݾ��� 1�� �Դϴ�." << endl;
	cout << endl;


	while ((result != 1) & (result != 2)) {
		i += 1;
		money = 0;

		for (int j = 0; j < 7; j++) {
			number = dis(gen);
			while (!checkNumber(win, number)) {
				number = dis(gen);
			}
			win[j] = number;
		}

		sort(win, win + 7);

		cout << i << "��° ��÷ ��ȣ : ";
		for (int j = 0; j < 7; j++) {
			if (j <= 5) {
				cout << win[j] << " ";
			}
			else {
				cout << "/ ���ʽ� ��ȣ : " << win[j] << endl;
			}
		}

		while (true) {
			money += 1;
			if (money > 100000) {
				cout << "�Ļ��Դϴ�. " << endl;
				cout << endl;
				break;
			}
			for (int k = 0; k < 7; k++) {
				number = dis(gen);
				while (!checkNumber(lottery, number)) {
					number = dis(gen);
				}
				lottery[k] = number;

			}
			result = findRank(lottery, win);
			if (result == 1) {
				UsingMoneyMessage(result, money);
				usingMoney[0].push_back(money);
				break;
			}
			else if (result == 2) {
				UsingMoneyMessage(result, money);
				usingMoney[1].push_back(money);
				break;
			}
			else if (result == 3) {
				UsingMoneyMessage(result, money);
				usingMoney[2].push_back(money);
				break;
			}
			else {
				continue;
			}
		}
	}
}