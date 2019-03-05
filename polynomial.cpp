
//A polynomial is implemented using a linked list.  Only non-zero coefficients are included in linked list.
//Implment member functions operator+ , operator* , and add term
//You have to use the main function and print_linked_list provided to you.

#include <iostream>
using namespace std;
class term {
public:
int power;
int coef;
term * next;
term() { next = nullptr; }
term(int c, int p) { power = p; coef = c; next = nullptr; }
};

class polynomial {
public:
int num_terms;
term * head;
polynomial() { num_terms = 0; head = nullptr; }

void add_term(int c, int p);
//If the polynomial does not contain a term with power p,
//then add this new term.
//If the polynomial contains a term with power p,
//then add c to the existing coef.

polynomial operator+(polynomial P);
polynomial operator*(polynomial P);
void print_polynomial();
};



void polynomial::print_polynomial() {
cout << endl;
term * p = head;
while (p != nullptr) {
cout << p->coef << " " << p->power << "   ";
p = p->next;
}
}
///////////////////////////////////////////////////////////////////////////
//If the polynomial does not contain a term with power p,
//then add this new term.
//If the polynomial contains a term with power p,
//then add c to the existing coef.
//////////////////////////////////////////////////////////////////////////

void polynomial::add_term(int c, int p){ 
 if (c == 0) { return;}
 
 if (head == nullptr){ 
  term *node = new term(c, p);
  head = node;
  num_terms++;
  return;
  }
  
 term *p1 = head;
 term *p2 = head;
 
 while (p1 != nullptr){	
  if (p1->power == p){  
   p1->coef = p1->coef+c;
   
   if (p1->coef == 0){ 
    if (head == p1){
    head = p1->next;}
    else{
      p2->next = p1->next;
      }
  delete p1; 
  num_terms--;
    }
   return;
   }		
   
  if (p1->power < p){
   term *p3 = new term(c, p);
   p3->next = p1;
   num_terms++;
   if (p1 == head){
    head = p3;
   }
    else {
    p2->next = p3;
    }
    return;
   }
    p2 = p1;
    p1 = p1->next;
}
 term *p3 = new term(c, p);
 num_terms++;
 p2->next = p3;
}

//'*' operator -Scan through 2 polynomials and multiply coefficients and add up powers
polynomial polynomial::operator*(polynomial P){
polynomial polyprod;
if(P.num_terms == 0 )

&& if (this->num_terms == 0) {return polyprod;}
else if (this->num_terms == 0) {return P;}
else if (P.num_terms == 0) { return *this; }

term * poly1 = this->head;
term *poly2 = P.head;

for (int i = 0; i < this->num_terms; i++)
{ poly2 = P.head;
  for (int j = 0; j < P.num_terms; j++){
  polyprod.add_term((poly1->coef * poly2->coef), (poly1->power + poly2->power));
  poly2 = poly2->next;}
  poly1 = poly1->next;
}
return polyprod;}

//'+' operator 

polynomial polynomial::operator+(polynomial P){
polynomial polysum;
term *pfirst = this->head;
term *psecond = P.head;

if(pfirst = nullptr) {  polysum = psecond;}
if(psecond = nullptr) {  polysum = pfirst;}

while (pfirst != nullptr){
 polysum.add_term(pfirst->coef, pfirst->power);
 pfirst = pfirst->next;
 }
 
while (psecond != nullptr){
  polysum.add_term(psecond->coef, psecond->power);
  psecond = psecond->next; }
 return polysum;
}

int main() {
polynomial p1, p2, p3, p4, p5, p6;
int num_t;
cout << "Enter numer of terms" << endl;
cin >> num_t;
cout << "Enter all terms" << endl;
for (int i = 0; i < num_t; i++) { //You don't need to check for input error
int c, p;
cin >> c >> p;
p1.add_term(c, p);
}
p1.print_polynomial();
cout << endl;
cout << "Enter numer of terms" << endl;
cin >> num_t;
cout << "Enter all terms" << endl;
for (int i = 0; i < num_t; i++) { //You don't need to check for input error
int c, p;
cin >> c >> p;
p2.add_term(c, p);
}
p2.print_polynomial();
p3 = p1 + p2;
p3.print_polynomial();
p4 = p1 * p2;
p4.print_polynomial();
getchar();
getchar();
return 0;
}

/*
//An example screenshot is given below:
//Different cases may be used during grading

Enter numer of terms
3
Enter all terms
2 2 1 1 4 0

2 2   1 1   4 0
Enter numer of terms
2
Enter all terms
-6 1 3 0

-6 1   3 0
2 2   -5 1   7 0
-12 3   -21 1   12 0
*/


