// demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string.h>
#include<vector>
#include<regex>
#include<sstream>
using namespace std;
/*
分割字符串
*/
vector<string> c_split(const char* in, const char* delim) {
	regex re{ delim };
	return vector<string> {
		cregex_token_iterator(in, in + strlen(in), re, -1),
			cregex_token_iterator()
	};
}
/*
计算连续乘除式
*/
double fun1(string str) {
	vector<char> operators;
	vector<string> nums;
	const char* c_str = str.data();
	nums = c_split(c_str, "[*/]");
	for (int i = 0; i < str.size(); i++) {

		if (c_str[i] == '*' || c_str[i] == '/') {
			operators.push_back(c_str[i]);
		}
	}
	if ((operators.empty())) {
		return atof(c_str);
	}
	double result = atof(nums.at(0).data());
	for (int i = 0; i < operators.size(); i++) {
		if (operators.at(i) == '*') {
			result = result * atof(nums.at(i + 1).data());
		}
		else {
			result = result / atof(nums.at(i + 1).data());
		}
	}
	return result;
}
/*
计算连续加减式
*/
double fun2(string str) {
	vector<char> operators;
	vector<string> nums;
	const char* c_str = str.data();
	int p = 0;
	for (int i = 1; i < str.size(); i++) {
		if ((str.at(i) == '+' || str.at(i) == '-') && (str.at(i - 1) >= '0' && str.at(i - 1) <= '9')) {
			operators.push_back(str.at(i));
			nums.push_back(str.substr(p,i-p));
			p = i + 1;
		}
	}
	nums.push_back(str.substr(p,str.size()-1));
	if ((operators.empty())) {
		return fun1(str);
	}
	double result = fun1(nums.at(0));
	for (int i = 0; i < operators.size(); i++) {
		if (operators.at(i) == '+') {
			result = result + fun1(nums.at(i + 1));
		}
		else {
			result = result - fun1(nums.at(i + 1));
		}
	}
	return result;
}
/*
递归去除括号
检测最内部的括号，传入fun2进行加减计算
*/
string fun(string str) {
	const char* c = str.data();
	int p = 0, q = 0;
	for (int i = 0; i < str.size(); i++) {
		if (c[i] == '(') {
			p = i;
		}
	}

	for (int i = p; i < str.size(); i++) {
		if (c[i] == ')') {
			q = i;
			break;
		}
	}
	if (p == 0&&q==0) {
		return to_string(fun2(str));
	}
	string stepstr = str.substr(p + 1, q - p - 1);
	double stepresult = fun2(stepstr);
	string str1 = str.substr(0, p);
	string str2 = str.substr(q + 1, str.size() - (q + 1));
	ostringstream mstream;
	mstream << str1 << to_string(stepresult) << str2;
	return fun(mstream.str());
}
int main(int argc, char* argv[])
{
	while (1) {
		string expression;
		cout << "请输入运算表达式" << endl;
		cin >> expression;
		cout << fun(expression)<<endl;
	}

}
