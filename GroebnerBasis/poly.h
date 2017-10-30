#pragma once
#include <vector>
#include <algorithm> 
using namespace std;

class Poly {
	vector<int> coef;
	vector<vector<int>> deg;
public:
	Poly();
	Poly(const Poly&);
	void setCoef(vector<int>);
	Poly(vector<int>, vector<vector<int>>);
	void showDeg();
	void showCoef();
	Poly leaderMonomial();
	vector<vector<int>> getDeg();
	vector<int> getCoef();
	bool operator>=(Poly&);
	Poly& operator=(const Poly&);
	Poly operator*(Poly&);
	Poly operator%(Poly&);
	Poly operator-(Poly&);
	Poly operator+(Poly&);
	bool operator==(Poly&);
	Poly minus(Poly&);
	Poly monomialDivision(Poly&);
	static Poly lcmMonomial(Poly&, Poly&);
	static int lcmInt(int, int);
	static Poly S_polinomial(Poly&, Poly&);
	void rem();
	bool Poly::operator!=(Poly&);
};