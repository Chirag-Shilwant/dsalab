#include <iostream>
#include <climits>
#include <iomanip>
#include <cmath>
using namespace std;

typedef long long int ll;
#define deb(x) cout << #x << " " << x << endl;
#define debtwo(x,y) cout << #x << " " << x << ", " << #y << " " << y << endl;
#define mod 100000007

template<typename dt>
struct node {
	dt data;
	node* next;
};

template <class dt>
class stack {
	struct node<dt>* top;
	int len;
public:

	stack() {
		top = NULL;
		len = 0;
	}

	void push(dt val) {
		node<dt>* temp = new node<dt>();
		temp->data = val;
		temp->next = top;
		top = temp;
		len++;
	}

	dt pop() {
		dt res = top->data;
		node<dt>* tmp = top;
		top = tmp->next;
		free(tmp);
		len--;
		return res;
	}

	dt topval() {
		return top->data;
	}

	int size() {
		return len;
	}

	bool empty() {
		if (!top) return true;
		return false;
	}
};

stack<double> nums = *(new stack<double>);
stack<char> ops = *(new stack<char>);

int err() {
	cout << "Invalid input";
	return 0;
}

void calc() {
	double b = nums.pop();
	double a;
	if (!nums.empty()) a = nums.pop();
	char op = ops.pop();

	if (op == '+') nums.push(a + b);
	if (op == '-') nums.push(a - b);
	if (op == '*') nums.push(a * b);
	if (op == '/') nums.push(a / b);
	if (op == '%') nums.push(fmod(a, b));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);


	string s;
	cin >> s;

	for (int i = 0; i < s.length(); i++) {

		if (isdigit((int)s[i]) || s[i] == '.' || (s[i] == '-' && (i == 0 || s[i - 1] == '('))) {
			string no = "";

			if (s[i] == '-') no += s[i++];
			while (i < s.length() && ((s[i] < 58 && s[i] > 47) || s[i] == '.')) no += s[i++];

			double val = stod(no);
			nums.push(val);

			i--;
		}

		else {
			if (ops.empty() || s[i] == '(' || ((s[i] == '*' || s[i] == '/' || s[i] == '%') && (ops.topval() == '+' || ops.topval() == '-'))) ops.push(s[i]);

			else if (s[i] == ')') {
				while (!ops.empty() && ops.topval() != '(') calc();
				if (ops.empty()) return err();
				ops.pop();
			}

			else {
				bool prec = (s[i] == '+' || s[i] == '-' || ((s[i] == '*' || s[i] == '/' || s[i] == '%') && (ops.topval() == '*' || ops.topval() == '/' || ops.topval() == '%'))) ? true : false;
				while (!ops.empty() && ops.topval() != '(' && prec) {
					calc();
					if (!ops.empty())prec = (s[i] == '+' || s[i] == '-' || ((s[i] == '*' || s[i] == '/' || s[i] == '%') && (ops.topval() == '*' || ops.topval() == '/' || ops.topval() == '%'))) ? true : false;
				}
				ops.push(s[i]);
			}
		}
	}

	while (!ops.empty()) calc();

	cout << fixed << setprecision(5) << nums.pop() << endl;
}