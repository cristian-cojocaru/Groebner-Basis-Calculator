#include "poly.h"
#include <iostream>
#include <numeric>

using namespace std;

Poly::Poly() {}
Poly::Poly(const Poly& p) {
	coef = p.coef;
	deg = p.deg;
}

Poly::Poly(vector<int> _coef, vector<vector<int>> _deg) {
	coef = _coef;
	deg = _deg;
}

void Poly::setCoef(vector<int> _coef) {
	coef = _coef;
}

void Poly::showDeg() {
	for (vector<int> i : deg) {
		for (int j : i)
			cout << j << " ";
		cout << '\n';
	}
}

void Poly::showCoef() {
	for (int i = 0; i < coef.size(); i++)
		cout << coef[i] << " ";
}

vector<vector<int>> Poly::getDeg() {
	return deg;
}

vector<int> Poly::getCoef() {
	return coef;
}

//intoarce monomul maximal al unui polinom
Poly Poly::leaderMonomial() {
	int maxim, k = 0, index = -1;
	vector<vector<int>> tmpDeg = this->deg;
	vector<int> tmpCoef = this->coef;
	while (tmpDeg.size() > 1) {
		maxim = -1;
		for (vector<int> i : tmpDeg)
			if (i[k] > maxim)
				maxim = i[k];
		for (int i = 0; i < tmpDeg.size(); i++)
			if (tmpDeg[i][k] != maxim) {
				tmpDeg.erase(tmpDeg.begin() + i);
				tmpCoef.erase(tmpCoef.begin() + i);
				i--;
			}
		if (tmpDeg.size() > 1)
			k++;
	}
	Poly* leader = new Poly({ tmpCoef }, { tmpDeg });
	return *leader;
}

//compara doua polinoame dupa monomul maximal
bool Poly::operator>=(Poly& p) {
	vector<vector<int>> lmp1 = this->leaderMonomial().getDeg();
	vector<vector<int>> lmp2 = p.leaderMonomial().getDeg();

	if (lmp1[0].size() == 0 || lmp2[0].size() == 0)
		return false;
	for (int i = 0; i < lmp1[0].size(); i++)
		if (lmp1[0][i] < lmp2[0][i])
			return false;
		else if (lmp1[0][i]>lmp2[0][i])
			return true;
	return true;
}

//operatorul de atribuire
Poly& Poly::operator=(const Poly& p) {
	if (this == &p)
		return *this;
	this->coef = p.coef;
	this->deg = p.deg;
	return (*this);
}

//verifica daca doua polinoame sunt egale
bool Poly::operator==(Poly& p) {
	if (this->coef == p.coef && this->deg == p.deg)
		return true;
	return false;
}

//cel mai mic multiplu comun dintre doi intregi
int Poly::lcmInt(int a, int b) {
	int aa = a, bb = b;
	while (a != b) {
		if (a > b)
			a = a - b;
		if (a < b)
			b = b - a;
	}
	return (aa*bb) / a;
}

//calculeaza cel mai mic multiplu comun dintre
//monoamele maximale a doua polinoame 
Poly Poly::lcmMonomial(Poly& p, Poly& q) {
	Poly lm1 = p.leaderMonomial();
	Poly lm2 = q.leaderMonomial();
	Poly* lcm = new Poly();

	int length1, length2;
	length1 = lm1.deg[0].size();
	length2 = lm2.deg[0].size();

	lcm->coef.push_back(lcmInt(lm1.coef[0], lm2.coef[0]));
	if (length1 > length2) {
		lcm->deg = lm1.deg;
		for (int i = 0; i < length2; i++)
			if (lcm->deg[0][i] < lm2.deg[0][i])
				lcm->deg[0][i] = lm2.deg[0][i];
	}
	else {
		lcm->deg = lm2.deg;
		for (int i = 0; i < length1; i++)
			if (lcm->deg[0][i] < lm1.deg[0][i])
				lcm->deg[0][i] = lm1.deg[0][i];
	}
	return *lcm;
}
//inmulteste doua polinoame
Poly Poly::operator*(Poly& p) {
	Poly* multiplication = new Poly();
	vector<int> *tmpCoef = new vector<int>();
	for (int i = 0; i < this->deg.size(); i++)
		for (int j = 0; j < p.deg.size(); j++) {
			vector<int> *tmpDeg = new vector<int>();
			for (int k = 0; k<this->deg[i].size(); k++)
				tmpDeg->push_back
				(this->deg[i][k] +
					p.deg[j][k]);
			multiplication->deg.push_back(*tmpDeg);
			tmpCoef->push_back
			(this->coef[i]
				* p.coef[j]);
		}
	multiplication->coef = *tmpCoef;

	//elimina duplicatele
	for (int i = 0; i < multiplication->deg.size(); i++)
		for (int j = i + 1; j < multiplication->deg.size() - 1; j++)
			if (multiplication->deg[i] == multiplication->deg[j]) {
				multiplication->coef[i] += multiplication->coef[j];
				multiplication->deg.erase(multiplication->deg.begin() + j);
				multiplication->coef.erase(multiplication->coef.begin() + j);
				j--;
			}
	return (*multiplication);
}

//imparte doua monoame
Poly Poly::monomialDivision(Poly& p) {
	Poly* quotient = new Poly();
	Poly lm1 = this->leaderMonomial();
	Poly lm2 = p.leaderMonomial();
	vector<int> tmp;
	for (int i = 0; i < lm1.deg[0].size(); i++)
		if (lm1.deg[0][i] >= lm2.deg[0][i])
			tmp.push_back(lm1.deg[0][i] - lm2.deg[0][i]);
		else
			return { { 0 },{ { 0 } } };

	quotient->deg.push_back(tmp);
	quotient->coef.push_back
	(lm1.coef[0] / lm2.coef[0]);
	return *quotient;
}
//diferenta a doua polinoame
Poly Poly::operator-(Poly& p) {
	Poly* result = new Poly();
	bool ok; int index1 = 0, index2 = 0;
	for (int i = 0; i < this->deg.size(); i++) {
		ok = false;
		for (int j = 0; j < p.deg.size(); j++) {
			if (this->deg[i] == p.deg[j]) {
				ok = true;
				index1 = i;
				index2 = j;
			}
		}
		if (ok) {
			result->deg.push_back
			(this->deg[index1]);
			result->coef.push_back
			(this->coef[index1] -
				p.coef[index2]);
			this->deg.erase
			(this->deg.begin()
				+ index1);
			this->coef.erase
			(this->coef.begin()
				+ index1);
			p.deg.erase(p.deg.begin() + index2);
			p.coef.erase(p.coef.begin() + index2);
		}
		else {
			result->deg.push_back
			(this->deg[index1]);
			result->coef.push_back
			(this->coef[index1]);
			this->deg.erase
			(this->deg.begin() + index1);
			this->coef.erase
			(this->coef.begin() + index1);
		}
		i--;
	}

	if (p.deg.size() != 0)
		for (int i = 0; i < p.deg.size(); i++) {
			result->coef.push_back(-p.coef[i]);
			result->deg.push_back(p.deg[i]);
		}

	for (int i = 0; i<result->coef.size(); i++)
		if (result->coef[i] == 0) {
			result->coef.erase(result->coef.begin() + i);
			result->deg.erase(result->deg.begin() + i);
		}
	return *result;
}

//suma a doua polinoame
Poly Poly::operator+(Poly& p) {
	Poly* result = new Poly();
	bool ok = false; int index1 = 0, index2 = 0;
	for (int i = 0; i < this->deg.size(); i++) {
		ok = false;
		for (int j = 0; j < p.deg.size(); j++) {
			if (this->deg[i] == p.deg[j]) {
				ok = true;
				index1 = i;
				index2 = j;
			}
		}
		if (ok) {
			result->deg.push_back(this->deg[index1]);
			result->coef.push_back(this->coef[index1] + p.coef[index2]);

			this->deg.erase(this->deg.begin() + index1);
			this->coef.erase(this->coef.begin() + index1);
			p.deg.erase(p.deg.begin() + index2);
			p.coef.erase(p.coef.begin() + index2);
			i--;

		}
		else {

			result->deg.push_back(this->deg[index1]);
			result->coef.push_back(this->coef[index1]);
			this->deg.erase(this->deg.begin() + index1);
			this->coef.erase(this->coef.begin() + index1);
			i--;
		}
	}

	if (p.deg.size() != 0)
		for (int i = 0; i < p.deg.size(); i++) {
			result->coef.push_back(p.coef[i]);
			result->deg.push_back(p.deg[i]);
		}
	return *result;
}



//calculeaza S-polinomul a doua polinoame
Poly Poly::S_polinomial(Poly& p, Poly& q) {
	Poly tmp;
	tmp = lcmMonomial(p, q).monomialDivision(p.leaderMonomial())*p
		- lcmMonomial(p, q).monomialDivision(q.leaderMonomial())*q;
	for (int i = 0; i<tmp.coef.size(); i++)
		if (tmp.coef[i] == 0) {
			tmp.coef.erase(tmp.coef.begin() + i);
			tmp.deg.erase(tmp.deg.begin() + i);
			i--;
		}
	return tmp;
}

//construieste polinomul nul
void Poly::rem() {
	this->coef.clear();
	this->deg.clear();
}

//verifica daca doua polinoame sunt diferite
bool Poly::operator!=(Poly& p) {
	if (this->coef != p.coef || this->deg != p.deg)
		return true;
	return false;
}
//calculeaza restul impartirii a doua polinoame
Poly Poly::operator%(Poly& p) {
	Poly reminder = *this;
	Poly lm1 = reminder.leaderMonomial();
	Poly lm2 = p.leaderMonomial();
	Poly impartire, reminderPrec;
	while (lm1.coef.size()>0 && lm1 >= lm2 && reminderPrec != reminder) {
		impartire = lm1.monomialDivision(lm2);
		reminderPrec = reminder;
		reminder = reminder - (impartire*p);
		for (int i = 0; i<reminder.coef.size(); i++)
			if (reminder.coef[i] == 0) {
				reminder.coef.erase(reminder.coef.begin() + i);
				reminder.deg.erase(reminder.deg.begin() + i);
			}
		lm1 = reminder.leaderMonomial();
	}
	return reminder;
}