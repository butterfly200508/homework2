// ConsoleApplication2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>

using namespace std; // 使用標準命名空間

// 檢查運算式的括號是否對稱
bool isBalanced(const string& expression) {
	stack<char> s;//建立一個堆疊
    for (char ch : expression) {
        if (ch == '(') {
			s.push(ch);//將左括號放入堆疊
        }
        else if (ch == ')') {
			if (s.empty() || s.top() != '(') {//如果堆疊為空或堆疊頂部不是左括號
                return false;
            }
			s.pop();//將左括號從堆疊中移除
        }
    }
	return s.empty();//如果堆疊為空，則括號對稱
}

// 獲取運算子的優先級
int precedence(char op) {
	if (op == '+' || op == '-') return 1;//加減運算子優先級為1
	if (op == '*' || op == '/') return 2;//乘除運算子優先級為2
    return 0;
}

// 將中序運算式轉換為後序運算式
string infixToPostfix(const string& expression) {
    stack<char> s;
	string postfix;//後序運算式
    for (char ch : expression) {
        if (isdigit(ch)) {
			postfix += ch;//如果是數字，直接加入後序運算式
        }
        else if (ch == '(') {
			s.push(ch);//如果是左括號，直接加入堆疊
        }
        else if (ch == ')') {
			while (!s.empty() && s.top() != '(') {//如果是右括號，將堆疊中的運算子加入後序運算式
				postfix += s.top();//直到遇到左括號
				s.pop();//將左括號從堆疊中移除
            }
			s.pop();//將左括號從堆疊中移除
        }
        else {
			while (!s.empty() && precedence(s.top()) >= precedence(ch)) {//如果是運算子，將堆疊中的運算子加入後序運算式
				postfix += s.top();//直到堆疊頂部的運算子優先級小於當前運算子
				s.pop();//將堆疊頂部的運算子移除
            }
			s.push(ch);//將當前運算子加入堆疊
        }
    }
	while (!s.empty()) {//將堆疊中的運算子加入後序運算式
		postfix += s.top();//直到堆疊為空
		s.pop();//將堆疊頂部的運算子移除
    }
    return postfix;
}

// 計算後序運算式的結果
int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
			s.push(ch - '0');//如果是數字，將數字轉換為整數並加入堆疊
        }
        else {
			int val2 = s.top(); s.pop();//如果是運算子，從堆疊中取出兩個數字
			int val1 = s.top(); s.pop();//進行運算並將結果加入堆疊
            switch (ch) {
			case '+': s.push(val1 + val2); break;//根據運算子進行運算
			case '-': s.push(val1 - val2); break;//並將結果加入堆疊
			case '*': s.push(val1 * val2); break;//直到後序運算式遍歷完畢
			case '/': s.push(val1 / val2); break;//返回堆疊頂部的結果
            }
        }
    }
    return s.top();
}

int main() {
    string expression;
	char cont = 'Y';//控制是否繼續測試
    while (cont == 'Y' || cont == 'y') {
        cout << "請輸入運算式: ";
        cin >> expression;

        if (!isBalanced(expression)) {
            cout << expression << " 運算式的括號不對稱，無法繼續運算\n";
        }
        else {
			string postfix = infixToPostfix(expression);//檢查運算式的括號是否對稱
			int result = evaluatePostfix(postfix);//將中序運算式轉換為後序運算式並計算結果
            cout << expression << " 運算式的左右括號對稱\n";
            cout << expression << " 運算式的後序表式法為: " << postfix << "\n";
            cout << expression << " 運算式的運算結果為: " << result << "\n";
        }

        cout << "是否繼續測試? (Y/y 繼續, 其他鍵退出): ";
        cin >> cont;
    }
    return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案