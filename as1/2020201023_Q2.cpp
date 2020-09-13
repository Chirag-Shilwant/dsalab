#include <iostream>
#include <climits>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long int ll;
#define deb(x) cout << #x << " " << x << endl;
#define debtwo(x,y) cout << #x << " " << x << ", " << #y << " " << y << endl;
#define debarr(arr) for (auto i : arr) cout << i; cout << endl;
#define mod 100000007
#define maxval 2147483648

void rtz(string& a) {
	a.erase(0, min(a.find_first_not_of('0'), a.size() - 1));
}


bool ispos(string a) {
	rtz(a);
	if (a[0] != '-') return true;
	return false;
}

void removeneg(string& a) {
	if (!ispos(a)) a.erase(0, 1);
}

bool isodd(string a) {
	reverse(a.begin(), a.end());

	if (a[0] == '1' || a[0] == '3' || a[0] == '5' || a[0] == '7' || a[0] == '9') return true;
	return false;
}

bool cmp(string a, string b)
{
	rtz(a);
	rtz(b);

	int n1 = a.length(), n2 = b.length();

	if (!ispos(a) && ispos(b)) return true;
	if (!ispos(b) && ispos(a)) return false;

	removeneg(a);
	removeneg(b);
	if (n1 < n2) return true;
	if (n2 < n1) return false;

	for (int i = 0; i < n1; i++) {
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}

	return false;
}


string mul(string a, string b) {
	rtz(a);
	rtz(b);
	bool isneg = false;
	if (!ispos(a) && !ispos(b)) {removeneg(a); removeneg(b);}
	else {
		if (!ispos(a)) {removeneg(a); isneg = true;}
		if (!ispos(b)) {removeneg(b); isneg = true;}
	}
	if (b.length() > a.length()) return mul(b, a);

	string arr(a.length() + b.length(), '0');

	for (int i = b.size() - 1; i >= 0; i--) {
		int c = 0, j = a.size() - 1;
		for (j; j >= 0; j--) {
			int m = (b[i] - '0') * (a[j] - '0');
			int nval = m + c + (arr[i + j + 1] - '0');
			arr[i + j + 1] = ((nval) % 10) + 48;
			c = nval / 10;
		}
		if (c) arr[i + j + 1] = c + 48;
	}
	rtz(arr);
	if (isneg) arr.insert(0, "-");

	return arr;
}

string sub(string a, string b);

string add(string a, string b) {
	rtz(a);
	rtz(b);

	if (!ispos(a) && !ispos(b)) {
		removeneg(a);
		removeneg(b);
		return "-" + add(b, a);
	}
	if (!ispos(a)) {
		removeneg(a);
		if (a == b) return "0";
		if (cmp(a, b))return sub(b, a);
		else return "-" + sub(a, b);
	}
	if (!ispos(b)) {
		removeneg(b);
		if (a == b) return "0";
		if (cmp(a, b))return sub(a, b);
		else return sub(a, b);
	}
	if (b.length() > a.length()) return add(b, a);

	string arr(a.length() + 1, '0');

	b = string( a.length() - b.length(), '0').append(b);

	int c = 0, i = a.size() - 1;

	for (i; i >= 0; i--) {
		int s = a[i] - '0' + b[i] - '0' + c;
		arr[i + 1] = (s % 10) + 48;
		c = (s / 10);
	}
	if (c) arr[0] = c + 48;

	rtz(arr);
	return arr;
}

string sub(string a, string b) {
	rtz(a);
	rtz(b);
	if (a == b) return "0";
	if (!ispos(a) && !ispos(b)) {
		removeneg(a);
		removeneg(b);
		if (cmp(a, b)) return sub(b, a);
		else return "-" + sub(a, b);
	}
	if (!ispos(a)) {
		removeneg(a);
		if (a == b) return "0";
		if (cmp(a, b))return "-" + add(a, b);
		else return "-" + add(a, b);
	}
	if (!ispos(b)) {
		removeneg(b);
		return add(a, b);
	}
	if (cmp(a, b)) return "-" + sub(b, a);

	string arr(a.length(), '0');

	b = string( a.length() - b.length(), '0').append(b);

	int br = 0, i = a.size() - 1;

	for (i; i >= 0; i--) {
		int s = 10 + (a[i] - '0') - (b[i] - '0') - br;
		if ((int)(a[i] - '0') - br < (int)b[i] - '0') br = 1;
		else br = 0;
		arr[i] = (s % 10) + 48;
	}

	rtz(arr);
	return arr;
}

string div(string a, ll b)
{
	string res;

	ll pos = 0;
	ll tmp = a[pos] - '0';
	while (tmp < b) tmp = tmp * 10 + (a[++pos] - '0');

	while (a.size() > pos) {
		res += (tmp / b) + '0';
		tmp = (tmp % b) * 10 + a[++pos] - '0';
	}

	if (res.length() == 0) return "0";

	return res;
}

string divby2(string a)
{
	string res (a.length(), '0');

	bool f = 0;
	for (int i = 0; i < a.length(); i++) {
		if (f) {
			res[i] = ((a[i] - '0') + 10) / 2 + 48;
			if (a[i] % 2) f = 1;
			else f = 0;
		}
		else {
			res[i] = ((a[i] - '0') / 2) + 48;
			if (a[i] % 2) f = 1;
			else f = 0;
		}
	}
	rtz(res);
	return res;
}

string addone(string a) {
	int n = a.length();
	if (a[n - 1] != '9') {
		a[n - 1] = a[n - 1] + 1;
		return a;
	}
	int i;
	for (i = n - 1; i >= 0; i--) {
		if (a[i] == '9') a[i] = '0';
		else break;
	}
	if (i >= 0) a[i] = a[i] + 1;
	else a.insert(0, "1");
	return a;
}

void fact(string a) {
	ll lim = stoi(a);

	string res = "1";

	for (int i = 2; i <= lim; i++) {
		res = mul(res, to_string(i));
	}
	cout << res << endl;
}

void exp(string a, string b) {
	ll n = stoi(b);

	bool negate = (a[0] == '-' && (n & 1)) ? true : false;

	if (a[0] == '-') a = a.substr(1, a.length() - 1);

	string res = "1";
	while (n > 0) {
		if (n & 1) res = mul(res, a);
		a = mul(a, a);
		n /= 2;
	}
	if (negate) cout << "-";
	cout << res;
}

string gcd(string a, string b) {
	if (a == b) return a;

	if (a == "0") return b;

	if (b == "0") return a;

	bool isAodd = isodd(a);
	bool isBodd = isodd(b);

	if (!isAodd && !isBodd) return mul("2", gcd(divby2(a), divby2(b)));
	else if (!isAodd && isBodd) return gcd(divby2(a), b);
	else if (isAodd && !isBodd) return gcd(a, divby2(b));

	if (cmp(a, b)) return gcd(sub(b, a), a);
	return gcd(sub(a, b), b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int choice, q;
	string a, b;

	cin >> q;

	while (q--) {
		cin >> choice;

		switch (choice) {
		case 1:
			cin >> a >> b;
			exp(a, b);
			cout << endl;
			break;
		case 2:
			cin >> a >> b;
			if (cmp(a, b)) cout << gcd(b, a) << endl;
			else cout << gcd(a, b) << endl;
			break;
		case 3:
			cin >> a;
			fact(a);
			cout << endl;
			break;
		}
	}

}
