// karatsuba multiplication for large numbers
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int makeLenPowOf2(string& s1, string& s2) {
	int n1 = s1.size(), n2 = s2.size();
	int max = n1 > n2 ? n1 : n2;
	int pow = 1;
	while (pow < max)
		pow <<= 1;

	s1.insert(0, pow - n1, '0');
	s2.insert(0, pow - n2, '0');
	return pow;
}

void popZeros(string& s) {
	int n = s.size();
	while (n > 1 && s[0] == '0')
		s.erase(s.begin()), --n;
}

string add(string& s1, string& s2) {
	string res;
	string::reverse_iterator it1b = s1.rbegin(), it1e = s1.rend();
	string::reverse_iterator it2b = s2.rbegin(), it2e = s2.rend();
	bool carry = false;
	while (it1b != it1e && it2b != it2e) {
		int d = *it1b + *it2b + carry - 2 * '0';
		if (d > 9)
			carry = true, d %= 10;
		else
			carry = false;

		res.push_back(d + '0');
		++it1b;
		++it2b;
	}
	while (it1b != it1e) {
		int d = *it1b + carry - '0';
		if (d > 9)
			carry = true, d %= 10;
		else
			carry = false;

		res.push_back(d + '0');
		++it1b;
	}
	while (it2b != it2e) {
		int d = *it2b + carry - '0';
		if (d > 9)
			carry = true, d %= 10;
		else
			carry = false;

		res.push_back(d + '0');
		++it2b;
	}

	if (carry)
		res.push_back('1');
	
	reverse(res.begin(), res.end());
	return res;
}

string sub(string& s1, string& s2) {
	s2.insert(0, s1.size() - s2.size(), '0');
	// 9's complement
	for (char& c : s2)
		c = '9' - c + '0';

	// + 1 = 10's complement
	string one = "1";
	s2 = add(s2, one);
	string res = add(s1, s2);
	res.erase(res.begin());
	popZeros(res);
	return res;
}

string kmul(string& s1, string& s2, int size) {
	if (size == 1) {
		return to_string(stoi(s1) * stoi(s2));
	} else {
		int mid = size / 2;
		string a(s1, 0, mid);
		string b(s1, mid, mid);
		string c(s2, 0, mid);
		string d(s2, mid, mid);
		
		string aplusb = add(a, b);
		string cplusd = add(c, d);
		int n = makeLenPowOf2(aplusb, cplusd);
		string apbcpd = kmul(aplusb, cplusd, n);
		
		string ac = kmul(a, c, mid);
		string bd = kmul(b, d, mid);
		string acplusbd = add(ac, bd);
		
		// (a + b) * (c + d) - (ac + bd)
		string adplusbc = sub(apbcpd, acplusbd);
		
		// 10^n * ac + 10^n/2 * adplusbc + bd
		ac.append(size, '0');
		adplusbc.append(mid, '0');
		string t = add(ac, adplusbc);
		
		return add(t, bd);
	}
}

int main() {
	string a, b;
	cout << "Enter 2 numbers: ";
	cin >> a >> b;
	int n = makeLenPowOf2(a, b);
	string ans = kmul(a, b, n);
	popZeros(ans);
	cout << "Their multiplication is: " << ans << endl;
}
