#include "poly.h"
#include <iostream >
int main() {
	//exemplul I1
	Poly p1 = { { 1, 1 },{ { 2, 0 },{ 0, 2 } } };
	Poly p2 = { { 1, 1 },{ { 2, 2 },{ 0, 1 } } };
	//exemplul I2
	Poly f1 = { { 1, 1 },{ { 2, 3 },{ 1, 0 } } };
	Poly f2 = { { 1 },{ { 0, 2 } } };
	//exemplul I3
	Poly d1 = { { 1, 1 },{ { 2, 0 },{ 0, 2 } } };
	Poly d2 = { { 1 },{ { 1, 1 } } };

	vector<Poly> G = { p1, p2 };
	Poly S, tmp;
	bool ok = true;
	for (int i = 0; i < G.size(); i++)
		for (int j = i + 1; j < G.size(); j++) {
			S.rem();
			S = Poly::S_polinomial(G[i], G[j]);
			for (int i = 0; i < G.size(); i++) {
				tmp = S % G[i];
				if (tmp.getCoef().size() == 0)
					ok = false;
			}
			if (S.getCoef().size() != 0 && ok == true)
				G.push_back(S);
		}
	cout << "Baza Groebner\n\n\n";
	for (int i = 0; i < G.size(); i++) {
		cout << "Polinom " << i + 1;
		cout << ":\nCoeficienti ";
		G[i].showCoef();
		cout << "\nGradele\n";
		G[i].showDeg();
		cout << "\n\n";
	}
	system("pause");
	return 0;
}