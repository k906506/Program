#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// ����� ����ϴ� Ŭ����
class Message {
private:
	string workMenu = "n:���� ������, p:���� ������, i:����, d:����, c:����, s:ã��, t:���� �� ����";
	string workSpace = "---------------------------------------------------------------------------------------------";
	int temp = 0;

public:
	void printLineAndMenu() {	// �޴��� �������� �Բ� ���
		cout << workMenu << "\n" << workSpace << endl;
	}
	void printInput() {	// �Է� �޼��� ���
		cout << "�Է� : " << endl;
	}
	void printLine() {	// ������ ���
		cout << workSpace << endl;
	}
	void consoleMessage(string message) {	// message�� �����ٰ� �Բ� ���
		cout << message << "\n" << workSpace << endl;
	}
	void consoleErrorMessage() {	// error �޼����� �����ٰ� �Բ� ���
		cout << "The input value is invalid." << "\n" << workSpace << endl;
	}

	// ���� �������� ����ϴ� �Լ�
	void printPrevPage(vector <string> textLine, int& lineIndex, bool& firstPage, bool& lastPage) {
		if (lineIndex >= 20) {	// 21��° �ٺ����� ���
			lineIndex -= 20;
			for (int i = lineIndex; i < lineIndex + 20; i++) {
				cout << setw(2) << i + 1 << "| " << textLine[i] << endl;
				if (i == 0) {
					firstPage = true;
				}
			}
		}
		else {	// 20��° �ٱ����� ���
			temp = lineIndex - 20;	// ���̸� �����ϱ� ���� ����
			lineIndex = 0;
			for (int i = lineIndex; i < lineIndex + 20 + temp; i++) {
				cout << setw(2) << i + 1 << "| " << textLine[i] << endl;
				if (i == 0) {
					firstPage = true;
				}
			}
		}
		lastPage = false;
		cout << workSpace << endl;
	}

	// ���� �������� ����ϴ� �Լ�
	void printNextPage(vector <string> textLine, int& lineIndex, bool& firstPage, bool& lastPage) {
		if (lineIndex < (int)textLine.size() - 20) { // ������ �������� ������ ������ �������� ���
			lineIndex += 20;
		}
		for (int i = lineIndex; i < lineIndex + 20; i++) {
			cout << setw(2) << i + 1 << "| " << textLine[i] << endl;
			if (i == textLine.size() - 1) {	// ������ ���� ���
				lastPage = true;
				break;
			}
		}
		firstPage = false;
		cout << workSpace << endl;
	}

	// ���� �������� ����ϴ� �Լ�
	void printPage(vector <string> textLine, int& lineIndex, bool& lastPage) {
		for (int i = lineIndex; i < lineIndex + 20; i++) {
			cout << setw(2) << i + 1 << "| " << textLine[i] << endl;
			if (i == textLine.size() - 1) { // ������ ���� ���
				lastPage = true;
				break;
			}
		}
		cout << workSpace << endl;
	}
};

// Ư�� ��ɿ� ���� �Է� ���� �����ϴ� Ŭ����
class evaluateParameter {
public:
	bool evaluatePrevNextParameter(string userWork) {	// ����, ���������� (p, n)
		if (userWork.size() == 1) {	// p, n�� 1���ھ��� �Էµ��� ���� ok
			return true;	// ��������
		}
		else {
			return false;	// ����������
		}
	}

	bool evaluateInsertParameter(string& userWork) {		// ���� (i)
		if (userWork.size() >= 8) {	// i ( 1 , 2 , a ) - �ּ� ���� 8
			userWork.erase(userWork.begin());
			if ((userWork[0] == '(') & (userWork[userWork.size() - 1] == ')')) {	// ��ȣ�� �ѷ��ο� �ִ� ��쿡�� ok
				for (int i = 0; i < (int)userWork.size(); i++) {
					if (userWork[i] == ' ') {	// ������ ������ ����
						return false; // ����������
					}
				}
				return true;	// ��������
			}
			else {
				return false;	// ����������
			}
		}
		else {
			return false;	// ����������
		}
	}

	bool evaluateDeleteParameter(string& userWork) {		// ���� (d)
		if (userWork.size() >= 6) {	// d ( 1 , 2 ) - �ּ� ���� 6
			userWork.erase(userWork.begin());
			if ((userWork[0] == '(') & (userWork[userWork.size() - 1] == ')')) {	// ��ȣ�� �ѷ��ο� �ִ� ��쿡��  ok
				for (int i = 0; i < (int)userWork.size(); i++) {
					if (userWork[i] == ' ') {	// ������ ������ ����
						return false;	// ����������
					}
				}
				return true;	// ��������
			}
			else {
				return false;	// ����������
			}
		}
		else {
			return false;	// ����������
		}
	}

	bool evaluateChangeParameter(string& userWork) {		// ���� (c)
		if (userWork.size() >= 6) {	// c ( a , b ) - �ּ� ���� 6
			userWork.erase(userWork.begin());
			if ((userWork[0] == '(') & (userWork[userWork.size() - 1] == ')')) {	// ��ȣ�� �ѷ��ο� �ִ� ��쿡�� ok
				for (int i = 0; i < (int)userWork.size(); i++) {
					if (userWork[i] == ' ') {	// ������ ������ ����
						return false;	// ����������
					}
				}
				return true;	// ��������
			}
			else {
				return false;	// ����������
			}
		}
		else {
			return false;	// ����������
		}
	}

	bool evaluateSearchParameter(string& userWork) {		// �˻� (s)
		if (userWork.size() >= 4) {	// s ( a ) - �ּ� ���� 4
			userWork.erase(userWork.begin());
			if ((userWork[0] == '(') & (userWork[userWork.size() - 1] == ')')) {	// ��ȣ�� �ѷ��ο� �ִ� ��쿡�� ok
				for (int i = 0; i < (int)userWork.size(); i++) {
					if (userWork[i] == ' ') {	// ������ ������ ����
						return false;	// ����������
					}
				}
				return true;	// ��������
			}
			else {
				return false;	// ����������
			}
		}
		else {
			return false;	// ����������
		}
	}
};

// Ư�� ��ɿ� ���� �Է� ���� �ʿ��׸� �и��ϴ� Ŭ����
class splitParameter {
private:
	string stringBuffer;
public:
	vector <string> findThreeParameter(string userWork) {	// �Է����ڰ� 3�� �� ��
		userWork = userWork.replace(userWork.find("("), 1, "");		// ( ����
		userWork = userWork.replace(userWork.find(")"), 1, "");		// ) ����

		stringstream s(userWork);
		vector <string> inputUser;
		while (getline(s, stringBuffer, ',')) {		// ���ڿ��� ,�� �и�
			inputUser.push_back(stringBuffer);
		}
		return inputUser;	// �и��� ���ڿ��� ����
	}
	vector <string> findTwoParameter(string userWork) {	// �Է����ڰ� 2�� �� ��
		userWork = userWork.replace(userWork.find("("), 1, "");		// ( ����
		userWork = userWork.replace(userWork.find(")"), 1, "");		// ) ����

		stringstream s(userWork);
		vector <string> inputUser;
		while (getline(s, stringBuffer, ',')) {		// ���ڿ��� ,�� �и�
			inputUser.push_back(stringBuffer);
		}
		return inputUser;	// �и��� ���ڿ��� ����
	}
	string findOneParameter(string userWork) {	// �Է����ڰ� 1�� �� ��
		userWork = userWork.replace(userWork.find("("), 1, "");		// ( ����	
		userWork = userWork.replace(userWork.find(")"), 1, "");		// ) ����
		return userWork;	// ( ) �� ���ŵ� ���ڿ��� ����
	}
};

// �ʿ信 ���� ������ �°� ���ڸ� �����ϴ� Ŭ���� ( �ܾ� ���� > ���� ���� / ���� ���� > �ܾ� ���� / ���� ���� > 1����Ʈ ���� / 75����Ʈ ���� )
class invertText {
public:
	vector <string> changeWordToString(vector <vector<string>> textWord) {	// �ܾ� ������ ���� ������
		vector <string> textLine;
		string text;
		for (int i = 0; i < (int)textWord.size(); i++) {	// �Ű������� ���� textWord��ŭ �ݺ����� ������
			text = "";
			for (int j = 0; j < (int)textWord[i].size(); j++) {
				text += textWord[i][j];
				text += ' ';	// �ܾ�� ' '�� �߰��Ѵ�
			}
			textLine.push_back(text);	// �� ���� �ϼ��Ǹ� textline�� �����Ѵ�
		}
		return textLine;
	}

	vector<vector<string>> changeStringToWord(vector <string> textLine) {	// ���� ������ �ܾ� ������
		vector <vector <string>> changeStringToWord(textLine.size());
		string stringBuffer;
		for (int i = 0; i < (int)textLine.size(); i++) {	// �Ű������� ���� textLine��ŭ �ݺ����� ������
			string inputString = textLine[i];	// (lineIndex-1)��° �� ���ڿ��� ����
			stringstream s(inputString);
			while (getline(s, stringBuffer, ' ')) {		// ' '���� ���ڿ��� �и��Ѵ�
				changeStringToWord[i].push_back(stringBuffer);
			}
		}
		return changeStringToWord;
	}

	vector <char> changeStringToChar(vector<string> textline) {	// ���� ������ 1����Ʈ ������
		vector <char> textWord;
		for (int i = 0; i < (int)textline.size(); i++) {
			for (int j = 0; j < int(textline[i].size()); j++) {
				textWord.push_back(textline[i][j]);
			}
		}
		return textWord;
	}

	vector <string> arrangeText(vector<char> textWord) {	// 75����Ʈ ������ ����
		int lineIndex = 0;
		int byteIndex = -1;
		int putNextWordCount = 0;
		bool eofFile = false;
		string sentence;
		string putNextWord;
		vector <string> textLine;
		for (int i = 0; i < (int)textWord.size(); i++) {
			if (textWord[i] != '\n') {
				sentence += textWord[i];
				byteIndex++;
			}
			if (i == textWord.size() - 1) {
				eofFile = true;
			}
			if (textWord[i] == '\n') {
				textLine.push_back(sentence);
				lineIndex++;	// ���� �� vector�� ���� �� �ְ� index + 1
				byteIndex = -1;	// 75byte�� �� �� �ְ� byteIndex�� �ٽ� �ʱ�ȭ
				sentence = ""; // ���ڿ� �ʱ�ȭ
			}
			if (((byteIndex % 75 == 0) & (byteIndex != 0)) || eofFile == true) {
				if ((textWord[i] == ' ') || (eofFile == true)) {	// 75��° ���ڰ� ������ ���
					textLine.push_back(sentence);
					lineIndex++;	// ���� �� vector�� ���� �� �ְ� index + 1
					byteIndex = -1;	// 75byte�� �� �� �ְ� byteIndex�� �ٽ� �ʱ�ȭ
					sentence = ""; // ���ڿ� �ʱ�ȭ
				}
				else {	// 75��°�� ������ ���
					for (int j = i; j >= 0; j--) {
						if (textWord[j] == ' ') {
							break;
						}
						putNextWord += textWord[j];	// ���� �ٷ� �̵���ų �ܾ ������ ����
						putNextWordCount++;
					}
					reverse(putNextWord.begin(), putNextWord.end());	// �ܾ ������ ���·� ����
					sentence = sentence.substr(0, 76 - putNextWordCount);	// �߸� �ܾ ������ ������ ����
					textLine.push_back(sentence);	// ������ vector�� ����
					lineIndex++;	// ���� �� vector�� ���� �� �ְ� index + 1
					sentence = "";	// ���ڿ� �ʱ�ȭ
					sentence = putNextWord;	// ���� �������� �̵���ų �ܾ�
					byteIndex = putNextWordCount - 1;
					putNextWord = "";
					putNextWordCount = 0;
				}
			}
		}
		return textLine;
	}
};

// Ư�� ����� �����ϴ� Ŭ����
class textWork {
private:
	int checkIndex;
	int findCount;

public:
	int insertWord(int lineIndex, int wordIndex, int pageNumber, int eofFile, string word, vector<vector <string>>& textWord) {	// ?��° ���� ?��° �ڿ� �ܾ� ����
		if (((lineIndex > 0 + pageNumber * 20) & (lineIndex <= 20 + pageNumber * 20)) & (wordIndex > 0) & (lineIndex <= eofFile)) {
			if ((wordIndex - 1 < (int)textWord[lineIndex - 1].size()) & (wordIndex >= 1) & (word.size() <= 75)) {
				textWord[lineIndex - 1].insert(textWord[lineIndex - 1].begin() + wordIndex, word);
				return 0;
			}
			else {
				return -1;	// ����������
			}
		}
		else {
			return -1;	// ����������
		}
	}

	int deleteWord(int lineIndex, int wordIndex, int pageNumber, int eofFile, vector<vector <string>>& textWord) {	// ?��° ���� ?��° �ܾ� ����
		if (((lineIndex > 0 + pageNumber * 20) & (lineIndex <= 20 + pageNumber * 20)) & (wordIndex > 0) & (lineIndex <= eofFile)) {
			if ((wordIndex - 1 < (int)textWord[lineIndex - 1].size()) & (wordIndex >= 1)) {
				textWord[lineIndex - 1].erase(textWord[lineIndex - 1].begin() + (wordIndex - 1));
				return 0;
			}
			else {
				return -1;	// ����������
			}
		}
		else {
			return -1;	// ����������
		}
	}

	int changeWord(string word1, string word2, vector <string>& textLine) {	// word1�� word2�� ����
		findCount = 0;
		for (int i = 0; i < (int)textLine.size(); i++) {
			checkIndex = textLine[i].find(word1);
			if (checkIndex != string::npos) {
				findCount += 1;
				textLine[i] = textLine[i].replace(checkIndex, word1.size(), word2);
			}
		}
		if (findCount != 0) {
			return 0;	// ��������
		}
		else {
			return -1;	// ����������
		}
	}

	int findStringReturnIndex(vector <string> textLine, string findWord) {	// findWord�� Ž��
		for (int i = 0; i < (int)textLine.size(); i++) {
			if (textLine[i].find(findWord) != string::npos) {
				return i;	// index �� ����
			}
		}
		return -1;	// ����������
	}
};

int main() {
	Message message;
	evaluateParameter checkPara;
	splitParameter splitPara;
	textWork textwork;
	invertText inverttext;
	vector <char> textWord;
	vector <string> textLine;
	string userWork;
	string inputWord;
	vector <string> inputUser;
	vector <vector <string>> stwWord;
	vector <string> wtsString;
	vector <char> stcChar;
	string findWord;
	int word;
	int changeWordCheck;
	int temp = 0;
	int lineIndex = 0;
	int wordIndex = 0;
	int pageNumber = 0;
	int eofFile = 0;
	bool firstPage = false;
	bool lastPage = false;

	ifstream in("test.txt");

	while ((word = in.get()) != EOF) {
		textWord.push_back(word);
	}

	textLine = inverttext.arrangeText(textWord);
	eofFile = textLine.size();
	message.printPage(textLine, lineIndex, lastPage);
	message.printLineAndMenu();

	message.printInput();
	getline(cin, userWork);
	message.printLine();

	firstPage = true;

	while (userWork[0] != 't') {
		switch (userWork[0]) {
		case 'n':	// ���� ������ ���
			if (checkPara.evaluatePrevNextParameter(userWork)) {
				if (!lastPage) {
					message.printNextPage(textLine, lineIndex, firstPage, lastPage);
					pageNumber++;
				}
				else {
					message.consoleMessage("This is the Last Page");
					firstPage = false;
				}
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			else {
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			break;

		case 'p':	// ���� ������ ���
			if (checkPara.evaluatePrevNextParameter(userWork)) {
				if (!firstPage) {
					message.printPrevPage(textLine, lineIndex, firstPage, lastPage);
					pageNumber--;
				}
				else {
					message.consoleMessage("This is the First Page");
					lastPage = false;
				}
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			else {
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			break;

		case 'i':	// ����
			if (checkPara.evaluateInsertParameter(userWork)) {
				inputUser = splitPara.findThreeParameter(userWork);
				temp = lineIndex;
				try {
					lineIndex = stoi(inputUser[0]);
					wordIndex = stoi(inputUser[1]);
				}
				catch (invalid_argument) {
					lineIndex = temp;
					message.consoleErrorMessage();
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
					break;
				}
				inputWord = inputUser[2];
				stwWord = inverttext.changeStringToWord(textLine);
				if (textwork.insertWord(lineIndex, wordIndex, pageNumber, eofFile, inputWord, stwWord) == 0) {	// ���������� ����
					wtsString = inverttext.changeWordToString(stwWord);	// �ܾ� ������ ���� ������
					stcChar = inverttext.changeStringToChar(wtsString);	// ���� ������ 1����Ʈ ������
					textLine = inverttext.arrangeText(stcChar);	// 75����Ʈ ������
					eofFile = textLine.size();
					lineIndex = temp;
					message.printPage(textLine, lineIndex, lastPage);
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
				else {	// �ٽ�
					lineIndex = temp;
					message.consoleErrorMessage();
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
			}
			else {
				lineIndex = temp;
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			break;

		case 'd':	// ����
			if (checkPara.evaluateDeleteParameter(userWork)) {
				inputUser = splitPara.findTwoParameter(userWork);
				temp = lineIndex;
				try {
					lineIndex = stoi(inputUser[0]);
					wordIndex = stoi(inputUser[1]);
				}
				catch (invalid_argument) {
					lineIndex = temp;
					message.consoleErrorMessage();
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
				stwWord = inverttext.changeStringToWord(textLine);	// ���� ������ �ܾ� ������
				if (textwork.deleteWord(lineIndex, wordIndex, pageNumber, eofFile, stwWord) == 0) {	// ���������� ����
					wtsString = inverttext.changeWordToString(stwWord);	// �ܾ� ������ ���� ������
					stcChar = inverttext.changeStringToChar(wtsString);	// ���� ������ 1����Ʈ ������
					textLine = inverttext.arrangeText(stcChar);	// 75����Ʈ ������
					eofFile = textLine.size();
					lineIndex = temp;
					message.printPage(textLine, lineIndex, lastPage);
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
				else {
					lineIndex = temp;
					message.consoleErrorMessage();
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
			}
			else {
				lineIndex = temp;
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			break;

		case 'c':	// ����
			if (checkPara.evaluateChangeParameter(userWork)) {
				inputUser = splitPara.findTwoParameter(userWork);
				changeWordCheck = textwork.changeWord(inputUser[0], inputUser[1], textLine);
				if (changeWordCheck == 0) {
					stcChar = inverttext.changeStringToChar(textLine);	// ���� ������ 1����Ʈ ������
					textLine = inverttext.arrangeText(stcChar);	// 75����Ʈ ������
					message.printPage(textLine, lineIndex, lastPage);
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
				else {
					message.consoleMessage("No Exist Word");
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
			}
			else {
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();
			}
			break;

		case 's':	// ã�� (�Ϸ�)
			if (checkPara.evaluateSearchParameter(userWork)) {
				findWord = splitPara.findOneParameter(userWork);
				temp = lineIndex;
				lineIndex = textwork.findStringReturnIndex(textLine, findWord);
				if (lineIndex != -1) {
					message.printPage(textLine, lineIndex, lastPage);
					if (lineIndex >= 20) {
						firstPage = false;
					}
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
				else {
					lineIndex = temp;
					message.consoleMessage("No Exist Word");
					message.printLineAndMenu();
					message.printInput();
					getline(cin, userWork);
					message.printLine();
				}
			}
			else {
				message.consoleErrorMessage();
				message.printLineAndMenu();
				message.printInput();
				getline(cin, userWork);
				message.printLine();;
			}
			break;

		default:// ���� - ���Է�
			message.consoleErrorMessage();
			message.printLineAndMenu();
			message.printInput();
			getline(cin, userWork);
			message.printLine();
			break;
		}
	}

	ofstream out("test.txt");	// ���� ����
	for (int i = 0; i < (int)textLine.size(); i++) {
		out << textLine[i];
	}
}