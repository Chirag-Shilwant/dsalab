#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

typedef long long int ll;
#define deb(x) cout << #x << " " << x << endl;
#define debtwo(x,y) cout << #x << " " << x << ", " << #y << " " << y << endl;
#define FOR(i,j,x) for (int c = i; c < j; c++) cout << x[c] << " "; cout << endl;
#define mod 100000007

template <class dt>
class deque {
	dt* deq;
	int first, last, sz, rz;
public:
	deque() {
		first = -1;
		last = 0;
		sz = 0;
		rz = 512;
		deq = new dt[512];
	}

	deque(int n, dt val) {
		first = 0;
		last = n - 1;
		sz = n;
		rz = 2 * n;

		deq = new dt[2 * n];
		for (int i = 0; i < n; i++) deq[i] = val;
	}

	void push_front(dt val) {
		if ((first == 0 && last == rz - 1) || first == last + 1 || sz == 0) resize();
		if (first == -1) first = last = 0;
		else if (first == 0) first = rz - 1;
		else first = first - 1;
		deq[first] = val;
		sz++;
	}

	void pop_front() {
		if (first == last) first = last = -1;
		else if (first == rz - 1) first = 0;
		else first = first + 1;

		sz--;
	}

	void push_back(dt val) {
		if ((first == 0 && last == rz - 1) || first == last + 1 || sz == 0) resize();
		if (first == -1) first = last = 0;
		else if (last == rz - 1) last = 0;
		else last = last + 1;
		deq[last] = val;

		sz++;
	}

	void pop_back() {
		if (first == last) first = last = -1;
		else if (last == 0) last = rz - 1;
		else last = last - 1;

		sz--;
	}

	dt front() {
		return deq[first];
	}

	dt back() {
		return deq[last];
	}

	bool empty() {
		if (sz == 0) return 1;
		return 0;
	}

	int size() {
		return sz;
	}

	void clear() {
		delete[] deq;
		first = last = -1;
		sz = 0;
	}

	void resize(int x, dt d) {
		if (x > sz) {
			int t = sz;
			for (int i = 0; i < x - t; i++) {
				push_back(d);
			}
		}
		else {
			int t = sz;
			for (int i = 0; i < t - x; i++) {
				pop_back();
			}
		}
	}

	dt operator [](int n) {
		return deq[(n + first) % rz];
	}

	void resize() {
		dt* newdeq = sz != 0 ? new dt[2 * sz] : new dt[512];
		if (sz) {
			if (first > last) {
				copy(deq + first, deq + rz, newdeq);
				copy(deq, deq + last + 1, newdeq + (sz - first));
			}
			else copy(deq + first, deq + last + 1, newdeq);
			first = 0, last = sz - 1;
			rz = 2 * sz;
			delete [] deq;
		}
		else {
			first = -1;
			last = 0;
			rz = 512;
		}
		deq = newdeq;
	}

	void display() {
		if (!sz) return;
		if (first > last) {
			for (int i = first; i < rz; i++) cout << deq[i] << " ";
			for (int i = 0; i <= last; i++) cout << deq[i] << " ";
		}
		else	for (int i = first; i <= last; i++) cout << deq[i] << " ";
		cout << endl;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	deque<string> *deq = NULL;

	int t, c, n;

	string x;

	cin >> t;

	while (t--) {

		cin >> c;

		switch (c) {

		case 1: cin >> x;
			deq->push_front(x);
			deq->display();
			break;

		case 2: deq->pop_front();
			deq->display();
			break;

		case 3: cin >> x;
			deq->push_back(x);
			deq->display();
			break;

		case 4: deq->pop_back();
			deq->display();
			break;

		case 5: if (deq != NULL) delete deq;
			deq = new deque<string>();
			break;

		case 6: cin >> n >> x;
			if (deq != NULL) delete deq;
			deq = new deque<string>(n, x);
			deq-> display();
			break;

		case 7: cout << deq->front() << endl;
			break;

		case 8: cout << deq->back() << endl;
			break;

		case 9: if (deq->empty()) cout << "true" << endl;
			else cout << "false" << endl;
			break;

		case 10: cout << deq->size() << endl;
			break;

		case 11: cin >> n >> x;
			deq->resize(n, x);
			deq->display();
			break;

		case 12: deq->clear();
			break;

		case 13: cin >> n;
			cout << (*deq)[n] << endl;
			break;

		case 14: deq->display();
			break;

		default:
			break;
		}
	}


	delete deq;
	return 0;
}