#include <stdio.h>
//! malloc ve free fonksiyonlari icin ekledim
#include <cstdlib>
#include "Poly.h"
#include <stdlib.h>
#include <ctype.h>

//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {
	PolyNode* head = NULL;
	while (*expr) {
		// Find the sign of the term
		char sign = '+';
		if (*expr == '+' || *expr == '-') {
			sign = *expr;
			expr++;
		}
		// Read the coefficient
		double coef = 0;
		if (*expr == 'x') {
			coef = 1.0;
		}
		else {
			char* endptr;
			coef = strtod(expr, &endptr);
			expr = endptr;
		}
		// Find the exponent
		int exp = 0;
		if (*expr == 'x') {
			if (*(expr + 1) == '^') {
				expr += 2;
				exp = atoi(expr);
			}
			else {
				exp = 1;
			}
		}
		PolyNode* node = (PolyNode*)malloc(sizeof(PolyNode));
		node->coef = (sign == '+') ? coef : -coef;
		node->exp = exp;
		node->next = head;
		head = node;
		// Find the next term
		while (*expr && *expr != '+' && *expr != '-') {
			expr++;
		}
	}
	return head;
}

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
	// Fill this in
	PolyNode* tempo;
	//! poly'nin ici tamamen bosalana kadar donguyu devam ettiriyor
	while (poly != NULL) {
		//! poly'nin mevcut biriminin adresini gecici ogeye atiyoruz. boylece free dedikten sonra hala islem yapabilecegimiz bir poly kalsin
		tempo = poly;
		//! poly'i ilerletiyoruz ve onceki kismi tempo ile siliyoruz
		poly = poly->next;
		//! free kullanma nedenim yukarida malloc kullanmam
		free(tempo);
	}
} // end-DeletePoly
	
//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode *head, double coef, int exp){
	// Fill this in
	
	// yeni node eger ayni uslu sayý yoksa en sona atiliyor, eger gerekirse uslere gore siralamali hale cevirebilirim

	//! new'i hata vermemesi için ekliyoruz. new olmazsa sadece pointer olusturulsmus oluyor isaret edilen nesne olmasý icin de new PolyNode ekleniyor. 
	PolyNode* addedNode = new PolyNode;
	addedNode->coef = coef;
	addedNode->exp = exp;
	addedNode->next = NULL;
	//! verilecek polinomun baslangýc adresini tutan gecici deger. ana polinomu bozmamak amaclý 
	PolyNode* tempo = head;
	//! ayni uslu sayi bulunmasi durumuna karsi. birdaha ayni node eklenmesin diye
	bool found = false;
	if (tempo == NULL) {
		addedNode->next = head;
		head = addedNode;
		return head;
	}
	//! sona gelene kadar icinde geziyor
	while (tempo->next != NULL) {
		//! ayni usse sahip sayi var mi diye bakiyor
		if (tempo->exp == exp) {
			//! var ise kendi katsayisi ile eklencek olaninkini topluyor
			tempo->coef += coef;
			//! node eklendigi icin foundu true yapiyor
			found = true;
			delete addedNode;
		}
		tempo = tempo->next;
	}
	//! eger ayni usslu yok ise sona ekliyor
	if (!found) {
		addedNode->next = tempo->next;
		tempo->next = addedNode;
	}
	//! buradaki NULL deðerini head ile deðistirdim ama dogru mu yaptým bilmiyorum
	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* result = NULL;
	PolyNode* current1 = poly1;
	PolyNode* current2 = poly2;
	PolyNode* current3 = NULL;
	PolyNode* newNode = NULL;

	while (current1 != NULL || current2 != NULL) {
		// Create a new node to store the sum of terms
		newNode = (PolyNode*)malloc(sizeof(PolyNode));
		newNode->next = NULL;

		// If either polynomial is exhausted, use the other polynomial's term
		if (current1 == NULL) {
			newNode->coef = current2->coef;
			newNode->exp = current2->exp;
			current2 = current2->next;
		}
		else if (current2 == NULL) {
			newNode->coef = current1->coef;
			newNode->exp = current1->exp;
			current1 = current1->next;
		}
		else {
			// Add coefficients if exponents match
			if (current1->exp == current2->exp) {
				newNode->coef = current1->coef + current2->coef;
				newNode->exp = current1->exp;
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->exp > current2->exp) {
				newNode->coef = current1->coef;
				newNode->exp = current1->exp;
				current1 = current1->next;
			}
			else {
				newNode->coef = current2->coef;
				newNode->exp = current2->exp;
				current2 = current2->next;
			}
		}

		// Add the newNode to the result polynomial
		if (result == NULL) {
			result = newNode;
			current3 = result;
		}
		else {
			current3->next = newNode;
			current3 = newNode;
		}
	}

	return result;
}

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* result = NULL;
	PolyNode* current1 = poly1;
	PolyNode* current2 = poly2;
	PolyNode* current3 = NULL;
	PolyNode* newNode = NULL;

	while (current1 != NULL || current2 != NULL) {
		// Create a new node to store the sum of terms
		newNode = (PolyNode*)malloc(sizeof(PolyNode));
		newNode->next = NULL;

		// If either polynomial is exhausted, use the other polynomial's term
		if (current1 == NULL) {
			newNode->coef = current2->coef;
			newNode->exp = current2->exp;
			current2 = current2->next;
		}
		else if (current2 == NULL) {
			newNode->coef = current1->coef;
			newNode->exp = current1->exp;
			current1 = current1->next;
		}
		else {
			// Add coefficients if exponents match
			if (current1->exp == current2->exp) {
				newNode->coef = current1->coef - current2->coef;
				newNode->exp = current1->exp;
				current1 = current1->next;
				current2 = current2->next;
			}
			else if (current1->exp > current2->exp) {
				newNode->coef = current1->coef;
				newNode->exp = current1->exp;
				current1 = current1->next;
			}
			else {
				newNode->coef = current2->coef;
				newNode->exp = current2->exp;
				current2 = current2->next;
			}
		}

		// Add the newNode to the result polynomial
		if (result == NULL) {
			result = newNode;
			current3 = result;
		}
		else {
			current3->next = newNode;
			current3 = newNode;
		}
	}

	return result;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode *Multiply(PolyNode *poly1, PolyNode *poly2){
	// Fill this in
	return NULL;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode *poly, double x){
	// Fill this in
	return 0;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
    PolyNode* derivative = NULL;
    PolyNode* current = poly;

    while (current != NULL) {
        if (current->exp != 0) {
            PolyNode* new_node = (PolyNode*)malloc(sizeof(PolyNode));
            new_node->coef = current->coef * current->exp;
            new_node->exp = current->exp - 1;
            new_node->next = derivative;
            derivative = new_node;
        }
        current = current->next;
    }

    return derivative;
}

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode *poly, int x1, int x2){
	// Fill this in	
} //end-Plot
