#include <iostream>
using namespace std;

class Vector
{
	private:
		int n;
		int *p;
	
	public:
		Vector();
		Vector (int n);
		Vector (const Vector &v);
		~Vector();
	
		int getN();
		int getElement(int poz);
		int * getSir();

		void setN(int n);
		void setElement (int poz, int e);
		void setSir(float * p);

		void citire();
		void afisare();

		int suma();
		int maxim(int&);
		void ord_cresc();
		int produs_scalar(Vector &v);

		friend void interclasare(Vector &v1, Vector &v2, Vector &v3);
		friend istream &operator>> (istream &stream, Vector &v);
		friend ostream &operator<< (ostream &sttream, Vector&v);

		Vector operator+(const Vector&);
		Vector operator=(const Vector&);

		int operator*(const Vector&);
		int& operator[](const int index);

	friend class Matrice;
};

class Matrice
{
	private:
		int n, m;
		Vector **vectors;

	public:
		Matrice(int m, int n);

		int getN();
		int getM();
		int getElement(int linie, int coloana);
		Vector& getLine(int index);

		void setN(int n);
		void setM(int m);
		void setVector(int linie, Vector vec);
		void setElement(int linie, int coloana, int element);

		friend istream &operator>> (istream &stream, Matrice &v);
		friend ostream &operator<< (ostream &sttream, const Matrice &v);

		Matrice operator+(const Matrice& m);
		Matrice &operator =(const Matrice &ob);
};

Vector::Vector(){}

Vector::Vector(int n)
{
    this->n=n;
    this->p=new int[n];
    for(int i=0; i<n; i++)
    {
        this->p[i]=0;
    }
}
Vector::Vector(const Vector &v)
{
    this->n = v.n;
    this->p=new int[this->n];
    for(int i=0; i<this->n; i++)
    {
        this->p[i]=v.p[i];
    }
}
Vector::~Vector()
{
    n=0;
    if(p!=0)
        delete p;
}
int Vector::getN(){
    return this->n;
}
void Vector::setN(int n){
    this->n = n;
}
int Vector::getElement(int poz){
    return this->p[poz];
}
void Vector::setElement(int poz, int e){
    this->p[poz] = e;
}

Vector& Matrice::getLine(int index)
{
	return *(vectors[index]);
}


istream& operator>>(istream& in, Vector&v)
{
	cout << "Numar de elemente : ";
    in>>v.n;
    v.p=new int[v.n+1];
	for (int i = 0; i < v.n; i++)
	{
		cout << "Elementul " << i << " : ";
		in >> v.p[i];
	}

    return in;
}
ostream& operator<<(ostream &out, Vector&v)
{
    for(int i=0; i < v.n; i++)
        out<<v.p[i] << " " ;
    return out;
}

/*void Vector::citire()
{
    int i;
//cin>>n;
//p=new float [n];
    cout<<"introduceti elementele vectorului:"<<endl;
    for(i=0; i<n; i++)
    {
        cin>>p[i];
    }
}*/

void Vector::afisare()
{
    int i;
    for(i=0; i<n; i++)
    {
        cout<<p[i]<<" ";
    }
    cout<<endl;
}//float vector::getElement() const {
// return n;



int Vector::suma()
{
    int i, s=0;
    for(i=0; i<n; i++)
        s+=p[i];
    return s;
}

int Vector::maxim(int& poz)
{
    int m;
    m=p[0];
    for(int i=1; i<n; i++)
		if (p[i] > m)
		{
			m = p[i];
			poz = i;
		}

    return m;
}

int Vector::produs_scalar(Vector &v)
{
    if(this->n != v.n){
        return -999999;
    }
    int s = 0;
    for(int i = 0; i <this->n; i++){
        s+=this->p[i]*v.p[i];
    }
    return s;
}

void Vector::ord_cresc()
{
    //ordonarea elem. unui vector fol. metoda bubblesort
    int i,aux,k;
    do
    {
        k=1;
        for(i=0; i<=n-1; i++)
            if(p[i]>p[i+1])
            {
                aux=p[i];
                p[i]=p[i+1];
                p[i+1]=aux;
                k=0;
            }
    }
    while(k==0);
}

void interclasare(Vector &v1, Vector &v2, Vector &v3)
{
    int i=0,j=0,k=0,l;
    while( (i<=v1.n) && (j<=v2.n) )
        if(v1.p[i]<v2.p[j])
        {
            v3.p[k]=v1.p[i];
            i++;
            k++;
        }
        else
        {
            v3.p[k]=v2.p[j];
            j++;
            k++;
        }
    if(i<=v1.n)
        for(l=i; l<v1.n; l++)
            v3.p[l++]=v1.p[l];
    else
        for(l=j; l<v2.n; l++)
            v3.p[l++]=v2.p[l];
}

//caz special cand index e < 0 sau > n
int& Vector::operator[](const int index)
{
	return p[index];
}

int Vector::operator*(const Vector& v)
{
	if (this->n != v.n){
		return -999999;
	}
	int s = 0;
	for (int i = 0; i <this->n; i++){
		s += this->p[i] * v.p[i];
	}
	return s;
}

Vector Vector::operator+(const Vector& v)
{
	Vector result(this->n);

	for (int i = 0; i < this->n; ++i)
	{
		result[i] = this->p[i] + v.p[i];
	}

	return result;
}


Vector Vector::operator=(const Vector& v)
{
	if (this == &v)
	{
		return *(this);
	}

	this->n = v.n;

	delete[] p;
	this->p = new int[this->n];
	
	for (int i = 0; i < n; ++i)
	{
		this->p[i] = v.p[i];
	}

	return *this;
}

Matrice::Matrice(int m, int n){
    this->n = n;
    this->m = m;
	this->vectors = new Vector*[m];
    for(int i = 0; i<m; i++){
		this->vectors[i] = new Vector(n);
    }
}
int Matrice::getM(){
    return this->m;
}
void Matrice::setM(int m){
    this->m = m;
}
int Matrice::getN(){
    return this->n;
}

void Matrice::setN(int n){
    this->n = n;
}

ostream& operator<<(ostream &out, const Matrice &m)
{
	out << "Numar de linii : " << m.m << endl;
	out << "Numar de coloane : " << m.n << endl;

	for (int i = 0; i < m.m; ++i)
	{
		out << *(m.vectors[i]) << " ";
		out << endl;
	}

	return out;
}

//numarul de linii/coloane din input trebuie sa corespunda cu size-ul dat in constructor.Poti da resize aici daca vrei(stergi vectors si apoi aloci iar cu m,n citite)
//pentru fiecare linie o sa iti ceara iar numarul de elemente pt ca foloseste operatorul din clasa Vector.
istream& operator>>(istream&in, Matrice &m)
{
	cout << "Numar de linii : ";
	in >> m.m;

	cout << "Numar de coloane : ";
	in >> m.n;

	for (int i = 0; i < m.m; ++i)
	{
		cout << "Linia " << i << endl;
		in >> *(m.vectors[i]);
	}

	return in;
}

Matrice Matrice::operator+(const Matrice& m)
{
	Matrice result(this->m, this->n);

	for (int i = 0; i < this->m; ++i)
	{
		*(result.vectors[i]) = *(m.vectors[i]) + *(vectors[i]);
	}

	return result;
}


//void Matrice::setVector(int linie, Vector v){
//    this->vectors[linie] = v;
//}
//
//int Matrice::getElement(int linie, int coloana){
//    return this->vectors[linie].getElement(coloana);
//}
//
//void Matrice::setElement(int linie, int coloana, int elemenet){
//    this->vectors[linie].setElement(coloana, elemenet);
//}

/*void Matrice::suma(Matrice matrice){
    /*if(this->m != matrice.m || this->n != matrice.n){
        return -9999999;
    }
    Matrice matriceRezultat = Matrice(this->m, this->n);
    for(int i = 0; i<this->m; i++){
        for(int j =0; j < this->n; j++){
            int element = this->vectors[i].getElement(j) + m.vectors[i].getElement(j);
            matrice.setElement(i, j, element);
        }
    }
    for(int i = 0; i< matriceRezultat.m; i++){
        for(int j = 0; j < matriceRezultat.n; j++){
            cout<< matriceRezultat.getElement(i,j);
        }
    }
    //return matriceRezultat;
}*/

/*matrice::matrice(const matrice &ob)
{
    n=ob.n;
    n=ob.m;
    a=new int*[n];
    for(int i=0; i<n; i++)
        a[i]=new int[m];
    for(int j=0; j<m; j++)
        return *this;
}*/

bool isSolution(Matrice& m, Vector& v1, Vector& v2)
{
	for (int i = 0; i < m.getM(); ++i)
	{
		if (m.getLine(i) * v1 != v2[i])
		{
			return false;
		}
	}

	return true;
}

int main()
{

	Matrice a(2, 2);
	Vector x(2), c(2);
	cin >> a;
	cin >> x;
	cin >> c;
	
	cout << isSolution(a, x, c);

	return 0;


}
