#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include<vector>
using namespace std;
constexpr auto capMax = 1000;

double e = -1;

void afis(double valoare)
{
	if ((int)valoare == valoare)
	{
		cout << valoare;
	}
	else
	{
		cout << fixed;
		cout.precision(4);
		cout << valoare;
		cout.unsetf(ios_base::floatfield);
	}
}

class IstoricRezultate
{
private:
	const int idRez;
	static int countRez;//folosit pt definirea id-ului fiecarui istoric
	int dimIstoric;
	double* istoricRez;
public:
	IstoricRezultate() : idRez(countRez++)
	{
		dimIstoric = 0;
		istoricRez = nullptr;
	}
	IstoricRezultate(int dimIstoric, double* istoricRez) : idRez(countRez++)
	{
		this->dimIstoric = 0;
		this->istoricRez = nullptr;
		if (dimIstoric > 0 && istoricRez != nullptr)
		{
			this->dimIstoric = dimIstoric;
			this->istoricRez = new double[dimIstoric];
			for (int i = 0; i < dimIstoric; i++)
			{
				this->istoricRez[i] = istoricRez[i];
			}
		}
	}
	IstoricRezultate(const IstoricRezultate& ist) : idRez(ist.idRez)
	{
		this->dimIstoric = 0;
		this->istoricRez = nullptr;
		if (ist.dimIstoric > 0 && ist.istoricRez != nullptr)
		{
			this->dimIstoric = ist.dimIstoric;
			this->istoricRez = new double[ist.dimIstoric];
			for (int i = 0; i < ist.dimIstoric; i++)
			{
				this->istoricRez[i] = ist.istoricRez[i];
			}
		}
	}
	~IstoricRezultate()
	{
		if (istoricRez != nullptr)
		{
			delete[] istoricRez;
			istoricRez = nullptr;
		}
	}
	IstoricRezultate& operator=(const IstoricRezultate& ist)
	{
		if (this != &ist)
		{
			if (istoricRez != nullptr)
			{
				delete[] istoricRez;
				istoricRez = nullptr;
			}
			if (ist.dimIstoric > 0 && ist.istoricRez != nullptr)
			{
				this->dimIstoric = ist.dimIstoric;
				this->istoricRez = new double[ist.dimIstoric];
				for (int i = 0; i < ist.dimIstoric; i++)
				{
					this->istoricRez[i] = ist.istoricRez[i];
				}
			}
		}
		return *this;
	}

	int getIdRez()
	{
		return idRez;
	}
	int getDimIstoric()
	{
		return dimIstoric;
	}
	double* getIstoric()
	{
		if (dimIstoric > 0 && istoricRez != nullptr)
		{
			double* copie = new double[dimIstoric];
			for (int i = 0; i < dimIstoric; i++)
			{
				copie[i] = istoricRez[i];
			}
			return copie;
		}
	}
	void setIstoric(int dim, double* ist)
	{
		if (dim > 0 && ist != nullptr)
		{
			dimIstoric = dim;
			if (istoricRez != nullptr)
			{
				delete[] istoricRez;
			}
			istoricRez = new double[dim];
			for (int i = 0; i < dim; i++)
			{
				istoricRez[i] = ist[i];
			}
		}
	}

	double getLast()
	{
		double var = 0;
		for (int i = 0; i < dimIstoric; i++)
		{
			var = istoricRez[i];
		}
		return var;
	}

	void operator+=(double value)//adauga in vector istoric o valoare
	{
		double* copie = new double[dimIstoric + 1];
		for (int i = 0; i < dimIstoric; i++)
		{
			copie[i] = istoricRez[i];
		}
		copie[dimIstoric] = value;
		if (istoricRez != nullptr)
		{
			delete[] istoricRez;
		}
		dimIstoric++;
		istoricRez = new double[dimIstoric];
		for (int i = 0; i < dimIstoric; i++)
		{
			istoricRez[i] = copie[i];
		}
		delete[] copie;
	}

	void operator++()
	{
		double* copie = new double[dimIstoric + 1];
		for (int i = 0; i < dimIstoric; i++)
		{
			copie[i] = istoricRez[i];
		}
		copie[dimIstoric] = 0;
		if (istoricRez != nullptr)
		{
			delete[] istoricRez;
		}
		dimIstoric++;
		istoricRez = new double[dimIstoric];
		for (int i = 0; i < dimIstoric; i++)
		{
			istoricRez[i] = copie[i];
		}
		delete[] copie;
	}

	void operator++(int i)
	{
		double* copie = new double[dimIstoric + 1];
		for (int i = 0; i < dimIstoric; i++)
		{
			copie[i] = istoricRez[i];
		}
		copie[dimIstoric] = 0;
		if (istoricRez != nullptr)
		{
			delete[] istoricRez;
		}
		dimIstoric++;
		istoricRez = new double[dimIstoric];
		for (int i = 0; i < dimIstoric; i++)
		{
			istoricRez[i] = copie[i];
		}
		delete[] copie;
	}

	operator double()
	{
		double sum = 0;
		if (dimIstoric > 0 && istoricRez != nullptr)
		{
			for (int i = 0; i < dimIstoric; i++)
			{
				sum += istoricRez[i];
			}
		}
		return sum;
	}
	double& operator[](int index)
	{
		if (dimIstoric > 0 && istoricRez != nullptr)
		{
			if (index >= 0 && index < dimIstoric)
			{
				return istoricRez[index];
			}
		}
		return e;
	}

	friend ostream& operator<<(ostream& out, IstoricRezultate& ist);
	friend istream& operator>>(istream& in, IstoricRezultate& ist);
};
int IstoricRezultate::countRez = 0;
ostream& operator<<(ostream& out, IstoricRezultate& ist)
{
	if (ist.dimIstoric > 0 && ist.istoricRez != nullptr)
	{
		for (int i = 0; i < ist.dimIstoric; i++)
		{
			out << ist[i] << " ";
		}
	}
	return out;
}
istream& operator>>(istream& in, IstoricRezultate& ist)
{
	cout << "Dimensiune istoric:";
	int dim;
	in >> dim;
	if (dim > 0)
	{
		double* copie = new double[dim];
		for (int i = 0; i < dim; i++)
		{
			cout << "ist[" << i + 1 << "]=";
			in >> copie[i];
		}
		ist.setIstoric(dim, copie);
	}
	return in;
}

class StackChar
{
private:
	int varf;
	char stiva[1000];
public:
	StackChar()
	{
		varf = -1;//stiva goala
	}
	bool push(char caracter)
	{
		if (varf >= 1000 - 1)
		{
			//stackOverflow
			return false;
		}
		else
		{
			stiva[++varf] = caracter;
			//am adaugat valoarea in stack
			return true;
		}
	}
	char pop()
	{
		if (varf < 0)
		{
			//am iesit din stiva in jos
			return 0;
		}
		else
		{
			return stiva[varf--];
		}
	}
	char getVfStiva()
	{
		if (varf >= 0)
		{
			return stiva[varf];
		}
		else
		{
			return 0;//practic am iesit din stiva daca ajung aici
		}
	}
	bool eStivaGoala()
	{
		return varf < 0;
	}

	friend ostream& operator<<(ostream& out, StackChar& st);
	friend istream& operator>>(istream& in, StackChar& st);
};
ostream& operator<<(ostream& out, StackChar& st)
{
	out << "Elem din stiva:";
	while (!st.eStivaGoala())
	{
		out << st.pop();
	}
	return out;
}
istream& operator>>(istream& in, StackChar& st)
{
	cout << "Cate elem puneti in stiva:";
	int dim;
	in >> dim;
	char* copie = new char[dim + 1];
	for (int i = 0; i < dim; i++)
	{
		cout << "st[" << i + 1 << "]=";
		in >> copie[i];
	}
	for (int i = 0; i < dim; i++)
	{
		st.push(copie[i]);
	}
	return in;
}

class Stack
{
private:
	int varf;
	double stiva[capMax];
public:
	Stack()
	{
		varf = -1;//stiva goala
	}
	bool push(double valoare)
	{
		if (varf >= capMax - 1)
		{
			//stackOverflow
			return false;
		}
		else
		{
			stiva[++varf] = valoare;
			//am adaugat valoarea in stack
			return true;
		}
	}
	double pop()
	{
		if (varf < 0)
		{
			//am iesit din stiva in jos
			return 0;
		}
		else
		{
			return stiva[varf--];
		}
	}
	double getVfStiva()
	{
		if (varf >= 0)
		{
			return stiva[varf];
		}
		else
		{
			return 0;//practic am iesit din stiva daca ajung aici
		}
	}
	bool eStivaGoala()
	{
		return varf < 0;
	}

	friend ostream& operator<<(ostream& out, Stack& st);
	friend istream& operator>>(istream& in, Stack& st);
};
ostream& operator<<(ostream& out, Stack& st)
{
	out << "Elementele din stiva:";
	while (!st.eStivaGoala())
	{
		out << st.pop() << endl;
	}
	return out;
}
istream& operator>>(istream& in, Stack& st)
{
	cout << "Cate elem de introdus in stiva:";
	int dim;
	in >> dim;
	double* copie = new double[dim];
	for (int i = 0; i < dim; i++)
	{
		cout << "st[" << i + 1 << "]=";
		in >> copie[i];
	}
	for (int i = 0; i < dim; i++)
	{
		st.push(copie[i]);
	}
	return in;
}

class OperatieElementara
{
protected:
	double op1;
	double op2;
public:
	OperatieElementara()
	{
		op1 = 0;
		op2 = 0;
	}
	OperatieElementara(double op1, double op2)
	{
		this->op1 = op1;
		this->op2 = op2;
	}
	OperatieElementara(double op1)
	{
		this->op1 = op1;
		op2 = 0;
	}

	void setOp1(double op1)
	{
		this->op1 = op1;
	}
	void setOp2(double op2)
	{
		this->op2 = op2;
	}
	double getOp1()
	{
		return op1;
	}
	double getOp2()
	{
		return op2;
	}

	static int getOrdineOperatie(char semn)
	{
		if (semn == '+' || semn == '-')
		{
			return 1;
		}
		if (semn == '*' || semn == '/')
		{
			return 2;
		}
		if (semn == '^' || semn == '#')
		{
			return 3;
		}
		return 0;
	}

	virtual bool eOrdonata()
	{
		return op1 > op2;
	}

	virtual double execOperatie(char operat)
	{
		switch (operat)
		{
		case '+': return op1 + op2;
		case '-':return op1 - op2;
		case '*': return op1 * op2;
		case '/':return op1 / op2;
		case '^':return pow(op1, op2);
		case '#': return pow(op1, 1 / op2);
		}
		return -1;
	}

	bool operator>(OperatieElementara& op)
	{
		if (op1 > op.op2 && op2 > op.op2)
		{
			return true;
		}
		else
			return false;
	}
	bool operator<(OperatieElementara& op)
	{
		if (op1 < op.op2 && op2 < op.op2)
		{
			return true;
		}
		else
			return false;
	}
	bool operator>=(OperatieElementara& op)
	{
		if (op1 >= op.op2 && op2 >= op.op2)
		{
			return true;
		}
		else
			return false;
	}
	bool operator<=(OperatieElementara& op)
	{
		if (op1 <= op.op2 && op2 <= op.op2)
		{
			return true;
		}
		else
			return false;
	}

	friend ostream& operator<<(ostream& out, OperatieElementara op);
	friend istream& operator>>(istream& in, OperatieElementara& op);
};
ostream& operator<<(ostream& out, OperatieElementara op)
{
	out << "Operatia contine:" << op.getOp1() << "si " << op.getOp2();
	return out;
}
istream& operator>>(istream& in, OperatieElementara& op)
{
	double a;
	double b;
	cout << "Op1:";
	in >> a;
	cout << "Op2:";
	in >> b;
	op.setOp1(a);
	op.setOp2(b);
	return in;
}

class OperatieElementara3 : public OperatieElementara
{
protected:
	double op3;
public:
	OperatieElementara3() : OperatieElementara()
	{
		op3 = 0;
	}
	OperatieElementara3(double op1, double op2, double op3) : OperatieElementara(op1, op2)
	{
		this->op3 = op3;
	}

	void setOp3(double op3)
	{
		this->op3 = op3;
	}
	double getOp3()
	{
		return op3;
	}

	bool eOrdonata() override
	{
		bool ok = 0;
		if (op1 > op2 && op1 > op3);
		{
			ok = 1;
		}
		return ok;
	}

	vector<double> getAllOperanzi()
	{
		vector<double> vectorulOperanzilor;
		vectorulOperanzilor.push_back(op1);
		vectorulOperanzilor.push_back(op2);
		vectorulOperanzilor.push_back(op3);
		return vectorulOperanzilor;
	}

	double execOperatie(char operat) override
	{
		switch (operat)
		{
		case '+': return op1 + op2 + op3;
		case '-':return op1 - op2 - op3;
		case '*': return op1 * op2 * op3;
		case '/':return op1 / op2 / op3;
		case '^':return pow(pow(op1, op2), op3);
		case '#': return pow(op1, 1 / op2);//op3 nu are sens in radical
		}
		return -1;
	}
};
ostream& operator<<(ostream& out, OperatieElementara3 op)
{
	out << "Operatia contine:" << op.getOp1() << "si " << op.getOp2() << "si" << op.getOp3();
	return out;
}
istream& operator>>(istream& in, OperatieElementara3& op)
{
	double a;
	double b;
	double c;
	cout << "Op1:";
	in >> a;
	cout << "Op2:";
	in >> b;
	cout << "Op3:";
	in >> c;
	op.setOp1(a);
	op.setOp2(b);
	op.setOp3(a);
	return in;
}

class IntegritateEcuatie
{
private:
	string ecuatie;
	int dimensiune;
	char* ecuatieTransform;
public:
	IntegritateEcuatie()
	{
		ecuatie = "";
		dimensiune = 0;
		ecuatieTransform = nullptr;
	}
	IntegritateEcuatie(string ecuatie) : IntegritateEcuatie()
	{
		this->ecuatie = ecuatie;
		this->dimensiune = ecuatie.length();
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, ecuatie.c_str());
		}
	}
	~IntegritateEcuatie()
	{
		if (ecuatieTransform != nullptr)
		{
			delete[] ecuatieTransform;
			ecuatieTransform = nullptr;
		}
	}
	IntegritateEcuatie(const IntegritateEcuatie& i) : IntegritateEcuatie()
	{
		this->ecuatie = i.ecuatie;
		this->dimensiune = i.ecuatie.length();
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, i.ecuatie.c_str());
		}
	}
	IntegritateEcuatie& operator=(const IntegritateEcuatie& i)
	{
		if (this != &i)
		{
			if (ecuatieTransform != nullptr)
			{
				delete[] ecuatieTransform;
				ecuatieTransform = nullptr;
			}
			this->ecuatie = i.ecuatie;
			this->dimensiune = i.ecuatie.length();
			if (dimensiune > 0)
			{
				ecuatieTransform = new char[dimensiune + 1];
				strcpy_s(ecuatieTransform, dimensiune + 1, i.ecuatie.c_str());
			}
		}
		return *this;
	}

	void setEcuatie(string ecuatie)
	{
		if (ecuatie != "")
		{
			this->ecuatie = ecuatie;
			this->dimensiune = ecuatie.length();
		}
		if (ecuatieTransform != nullptr)
		{
			delete[] ecuatieTransform;
		}
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, ecuatie.c_str());
		}
	}
	string getEcuatie()
	{
		return ecuatie;
	}

	bool integritateOperatori()
	{
		int contOperator = 0;
		int contOperanzi = 0;
		int contorPuncte = 0;
		for (int i = 0; i < dimensiune; i++)
		{
			if (ecuatieTransform[i] == '+' || ecuatieTransform[i] == '-' || ecuatieTransform[i] == '/' || ecuatieTransform[i] == '#'
				|| ecuatieTransform[i] == '*' || ecuatieTransform[i] == '^')
			{
				contOperator++;
			}
		}
		int i = 0;
		int j = 0;
		int ok = 1;
		while (i < dimensiune)
		{
			if (isdigit(ecuatieTransform[i]) != 0 || ecuatieTransform[i] == '.')
			{
				if (ecuatieTransform[i] == '.')//daca gaseste o secventa de genu .10 e clar scris gresit
				{
					ok = 0;//din start plec cu premisa ca e gresit
				}
				contorPuncte = 0;
				j = i;//salvez pozitia inceputului de numar;
				while (isdigit(ecuatieTransform[j]) != 0 || ecuatieTransform[j] == '.')
				{
					if (ecuatieTransform[j] == '.')
					{
						contorPuncte++;
					}
					if (contorPuncte > 1)
					{
						ok = 0;//daca un nr contine mai mult de 
							   //2 puncte sigur e scris gresit ies fortat din while cu fals
					}
					j++;
				}
				if (ecuatieTransform[j - 1] == '.')
				{
					ok = 0;//de asemenea daca un nr se termina cv gen 10. + 3 sigur e gresit scris
				}
				contOperanzi++;
				i = j;
			}
			i++;
		}
		if (contOperator == contOperanzi - 1 && ok == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool integritateParanteze()
	{
		int count = 0;
		for (int i = 0; i < dimensiune; i++)
		{
			if (ecuatieTransform[i] == '(' || ecuatieTransform[i] == '[' || ecuatieTransform[i] == ')'
				|| ecuatieTransform[i] == ']')
			{
				count++;
			}
		}
		if (count % 2 != 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator!()
	{
		//!e returneaza true daca nu exita '/0'
		string check = "/0";
		if (ecuatie.find(check) != string::npos) //cu alte cuvinte daca e gasit check "pana la finalul" lui ecuatie
		{
			return false;
		}
		else
			return true;
	}
	bool operator()()
	{
		if (this->integritateOperatori() == true && this->integritateParanteze() == true)
		{
			return true;
		}
		else
			return false;
	}
	friend ostream& operator<<(ostream& out, IntegritateEcuatie ec);
	friend istream& operator>>(istream& in, IntegritateEcuatie& ec);
};
ostream& operator<<(ostream& out, IntegritateEcuatie ec)
{
	out << "Ecuatie:" << ec.ecuatie << " ";
	out << "Dim:" << ec.dimensiune;
	return out;
}
istream& operator>>(istream& in, IntegritateEcuatie& ec)
{
	cout << "Ecuatie:";
	string ecuatie;
	in >> ecuatie;
	ec.setEcuatie(ecuatie);
	return in;
}

class Ecuatie
{
private:
	string ecuatie;
	int dimensiune;
	char* ecuatieTransform;
public:
	Ecuatie()
	{
		ecuatie = "";
		dimensiune = 0;
		ecuatieTransform = nullptr;
	}
	//constructorul cu parametri primeste doar un string deoarece pe baza lui se initializeaza restul campurilor
	//pentru a asigura integritatea datelor
	Ecuatie(string ecuatie) : Ecuatie()
	{
		this->ecuatie = ecuatie;
		this->dimensiune = ecuatie.length();
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, ecuatie.c_str());
		}
	}
	~Ecuatie()
	{
		if (ecuatieTransform != nullptr)
		{
			delete[] ecuatieTransform;
			ecuatieTransform = nullptr;
		}
	}
	Ecuatie(const Ecuatie& i) : Ecuatie()
	{
		this->ecuatie = i.ecuatie;
		this->dimensiune = i.ecuatie.length();
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, i.ecuatie.c_str());
		}
	}
	Ecuatie& operator=(const Ecuatie& i)
	{
		if (this != &i)
		{
			if (ecuatieTransform != nullptr)
			{
				delete[] ecuatieTransform;
				ecuatieTransform = nullptr;
			}
			this->ecuatie = i.ecuatie;
			this->dimensiune = i.ecuatie.length();
			if (dimensiune > 0)
			{
				ecuatieTransform = new char[dimensiune + 1];
				strcpy_s(ecuatieTransform, dimensiune + 1, i.ecuatie.c_str());
			}
		}
		return *this;
	}

	//setEcuatie Si getEcuatie se comporta ca getter si setter pentru toate campurile 
	//deodata intrucat schimbarea lor individuala nu ar avea sens (ele depind permanent unele de celelalte)
	void setEcuatie(string ecuatie)
	{
		if (ecuatie != "")
		{
			this->ecuatie = ecuatie;
			this->dimensiune = ecuatie.length();
		}
		if (ecuatieTransform != nullptr)
		{
			delete[] ecuatieTransform;
		}
		if (dimensiune > 0)
		{
			ecuatieTransform = new char[dimensiune + 1];
			strcpy_s(ecuatieTransform, dimensiune + 1, ecuatie.c_str());
		}
	}
	string getEcuatie()
	{
		return ecuatie;
	}

	void operator--()
	{
		string auxStr = "";
		for (int i = 0; i < ecuatie.length(); i++)
		{
			if (ecuatie[i] != ' ')
			{
				auxStr += ecuatie[i];
			}
		}
		this->setEcuatie(auxStr);
	}
	void operator--(int i)
	{
		string auxStr = "";
		for (int i = 0; i < ecuatie.length(); i++)
		{
			if (ecuatie[i] != ' ')
			{
				auxStr += ecuatie[i];
			}
		}
		this->setEcuatie(auxStr);
	}

	double evalueazaEcuatia()
	{
		Stack valori;
		StackChar operatori;
		for (int i = 0; i < ecuatie.length(); i++)
		{
			if (ecuatie[i] == '(')
			{
				operatori.push(ecuatie[i]);
			}
			else
				if (isdigit(ecuatie[i]))
				{
					double val = 0;
					string auxStr = "";
					while (i < ecuatie.length() && (isdigit(ecuatie[i]) || ecuatie[i] == '.'))
					{
						auxStr = auxStr + ecuatie[i];//formez un numar
						i++;
					}
					val = stod(auxStr);
					valori.push(val);//bag nr in stiva
					i--;
				}
				else
					if (ecuatie[i] == ')')
					{
						while (!operatori.eStivaGoala() && operatori.getVfStiva() != '(')//cat timp stiva cu operatori si nu e )
						{
							double val2 = valori.getVfStiva();
							valori.pop();

							double val1 = valori.getVfStiva();
							valori.pop();

							char operand = operatori.getVfStiva();
							operatori.pop();

							OperatieElementara o(val1, val2);//behavior de calcul a unei operatii pe 2 operanzi e in clasa OperatieElementara

							valori.push(o.execOperatie(operand));
						}
						if (!operatori.eStivaGoala())//daca nu e stiva goala
						{
							operatori.pop();//arunc practic paranteza matching
						}
					}
					else
					{
						while (!operatori.eStivaGoala()
							&& OperatieElementara::getOrdineOperatie(operatori.getVfStiva()) >= OperatieElementara::getOrdineOperatie(ecuatie[i]))
						{
							double val2 = valori.getVfStiva();
							valori.pop();

							double val1 = valori.getVfStiva();
							valori.pop();

							char operand = operatori.getVfStiva();
							operatori.pop();

							OperatieElementara o(val1, val2);

							valori.push(o.execOperatie(operand));
						}
						operatori.push(ecuatie[i]);
					}
		}
		while (!operatori.eStivaGoala())
		{
			double val2 = valori.getVfStiva();
			valori.pop();

			double val1 = valori.getVfStiva();
			valori.pop();

			char operand = operatori.getVfStiva();
			operatori.pop();

			OperatieElementara o(val1, val2);

			valori.push(o.execOperatie(operand));
		}
		if ((int)valori.getVfStiva() == valori.getVfStiva() && valori.getVfStiva() == 0)
		{
			return abs(valori.getVfStiva());
		}
		else
		{
			return valori.getVfStiva();
		}
	}
	void configureazaPtCalcul()
	{
		for (int i = 0; i < ecuatie.length(); i++)
		{
			if (ecuatie[i] == '[')
			{
				ecuatie[i] = '(';
			}
			if (ecuatie[i] == ']')
			{
				ecuatie[i] = ')';
			}
		}
	}
	friend ostream& operator<<(ostream& out, Ecuatie ec);
	friend istream& operator>>(istream& in, Ecuatie& ec);
	friend bool operator==(Ecuatie& ec1, Ecuatie& ec2);
};
bool operator==(Ecuatie& ec1, Ecuatie& ec2)
{
	//folosit pt a vedea daca 2 ecuatii au acelasi rezultat
	bool ok = 1;
	if (ec1.evalueazaEcuatia() != ec2.evalueazaEcuatia())
	{
		ok = 0;
	}
	return ok;
}
ostream& operator<<(ostream& out, Ecuatie ec)
{
	out << "Ecuatia:" << ec.ecuatie << " ";
	out << "Dimensiunea:" << ec.dimensiune;
	return out;
}
istream& operator>>(istream& in, Ecuatie& ec)
{
	string ecuatie;
	cout << "Ecuatie?:";
	in >> ecuatie;
	ec.setEcuatie(ecuatie);
	return in;
}
ifstream& operator>>(ifstream& f, Ecuatie& ec)
{
	string ecuatie;
	getline(f, ecuatie);
	ec.setEcuatie(ecuatie);
	return f;
}

class InterfataCitire
{
public:
	virtual void citeste() = 0;
	virtual void scrie() = 0;
	virtual IstoricRezultate getIstoric() = 0;
	virtual void setIstoric(IstoricRezultate ist) = 0;
};
class CitireConsola : public InterfataCitire
{
private:
	IstoricRezultate ist;
public:
	void citeste()//citire ecuatii din consola
	{
		IstoricRezultate istoric;
		string ec;
		cout << "ecuatie:";
		cin >> ws;
		getline(cin, ec);
		IntegritateEcuatie e(ec);
		while (ec != "exit")
		{
			if (e.integritateOperatori() != false && e.integritateParanteze() != false && !e)//!e inseamna daca nu exista '/0' impartiri la 0
			{
				cout << "=" ;
				Ecuatie ecu(ec);
				ecu.configureazaPtCalcul();
				--ecu;//elimina spatiile
				afis(ecu.evalueazaEcuatia());
				cout << endl;

				istoric += ecu.evalueazaEcuatia();//functionalitatea de istoric concateneaza mereu ultimul rezultat valid
				cout << "ecuatie:(sau exit):";
				getline(cin, ec);
				e.setEcuatie(ec);

			}
			else
			{
				cout << "gresita..." << endl;
				cout << "ecuatie:(sau exit)";
				getline(cin, ec);
				e.setEcuatie(ec);
			}
		}
		ist = istoric;
	}
	void scrie()
	{
		cout << fixed;
		cout << ist;
		cout.unsetf(ios_base::floatfield);
		cout << "Gata afisarea" << endl;
	}
	IstoricRezultate getIstoric()
	{
		return ist;
	}
	void setIstoric(IstoricRezultate ist)
	{
		this->ist = ist;
	}
};
class CitireFisier : public InterfataCitire
{
protected:
	IstoricRezultate ist;
public:
	void citeste()
	{
		cout << "Cum se numeste fisierul?";
		string nume;
		cin >> nume;
		ifstream f;
		f.open(nume, ios::in);
		cout << "Preview rezultate(pt a fi salvate alegeti 'Da' in sectiunea de salvare istoric):" << endl;
		if (f.is_open())
		{
			IstoricRezultate istoric;
			string ec;
			getline(f, ec);
			IntegritateEcuatie e(ec);
			while (!f.eof())
			{
				if (e.integritateOperatori() != false && e.integritateParanteze() != false && !e)//!e inseamna daca nu exita '/0' impartiri la 0
				{
					Ecuatie ecu(ec);
					ecu.configureazaPtCalcul();
					--ecu;//elimina spatiile
					afis(ecu.evalueazaEcuatia());
					cout << endl;

					istoric += ecu.evalueazaEcuatia();//functionalitatea de istoric concateneaza mereu ultimul rezultat valid

					getline(f, ec);
					e.setEcuatie(ec);
				}
				else
				{
					cout << "gresita..." << endl;
					getline(f, ec);
					e.setEcuatie(ec);
				}
			}
			ist = istoric;
		}
		f.close();
	}
	void scrie()
	{
		ofstream g("outputEcuatii.txt",ios::out | ios::trunc);
		g << fixed;
		g << ist;
		g.unsetf(ios_base::floatfield);
		g.close();
		cout << "Rezultatele au fost depuse in fisier txt!" << endl;
	}
	IstoricRezultate getIstoric() {
		return ist;
	}
	void setIstoric(IstoricRezultate ist)
	{
		this->ist = ist;
	}
};
class CitireFisierBinar : public InterfataCitire
{
protected:
	IstoricRezultate ist;
	vector<double> istoricRezultateFB;
public:
	void citeste() 
	{
		cout << "Numele fis binar:";
		string nume;
		cin >> nume;
		ifstream f(nume, ios::in | ios::binary);
		vector<double> rezultate;
		if(f.is_open())
		while (!f.eof())
		{
			double valoare;
			f.read((char*)&valoare, sizeof(valoare));
			if(!f.eof())
			{
				rezultate.push_back(valoare);
				cout << fixed;
				cout << valoare << " ";
				cout.unsetf(ios_base::floatfield);
			}
		}
		f.close();
		cout << endl;
	}

	vector<double> getIstoricRezultateFB()
	{
		return istoricRezultateFB;
	}

	void scrie() 
	{
		ofstream g("outputEcuatiiBin.bin",ios::out | ios::binary |ios::trunc );
		for (int i = 0; i < ist.getDimIstoric(); i++)
		{
			g.write((char*)&ist[i], sizeof(ist[i]));
		}
		g.close();
		cout << "Rezultatele au fost depuse in fisier binar!" << endl;
	}
	IstoricRezultate getIstoric() {
		return ist;
	}
	void setIstoric(IstoricRezultate ist)
	{
		this->ist = ist;
	}
};

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		string actiune;
		actiune = "ok";
		IstoricRezultate istoric;
		InterfataCitire* interfata = nullptr;
		CitireConsola consola;
		CitireFisier fisier;
		CitireFisierBinar fisierBinar;
		while (actiune == "ok")
		{
			cout << "Citire din Fisier text(type F) sau din concola(type C):";
			int ok = 1;
			while (ok != 0)
			{
				char c;
				cin >> c;
				if (c == 'F' || c == 'f')//varianta de citire din fisier;
				{
					ok = 0;
					interfata = &fisier;
					interfata->citeste();
				}
				else
					if (c == 'C' || c == 'c')//varianta de citire din consola;
					{
						ok = 0;
						interfata = &consola;
						interfata->citeste();
					}
					else
						if (c == 'B' || c == 'b')//varianta de citire din fis binar se vor citi toate rezultatele anteriorare;
						{
							ok = 0;
							interfata = &fisierBinar;
							interfata->citeste();
						}
					else
					{
						cout << "Sursa Incorecta" << endl;
						cout << "Introdu sursa citire ecuatii:";
						cin >> c;
					}
			}
			cout << "Gata! Doriti istoric?(Da sau Nu):";
			string decizie;
			cin >> decizie;
			if (decizie == "Da" || decizie == "da" || decizie == "dA")
			{
				istoric = interfata->getIstoric();
				cout << "Afisare in Fisier text(type F), in concola(type C), in fisier binar(type B):";
				char c;
				cin >> c;
				if (c == 'C' || c == 'c')
				{
					interfata = &consola;
					interfata->setIstoric(istoric);
					interfata->scrie();
				}
				else
					if (c == 'F' || c == 'f')
					{
						interfata = &fisier;
						interfata->setIstoric(istoric);
						interfata->scrie();
					}
					else
						if (c == 'b' || c == 'B')
						{
							interfata = &fisierBinar;
							interfata->setIstoric(istoric);
							interfata->scrie();
						}
					else
					{
						cout << "nu s-a afisat istoricul..." << endl;
					}

			}
			cout << "Calculatorul a finalizat un ciclu de calcul!" << endl;
			cout << "Doriti sa reincepeti calculele?(type ok):";
			cin >> actiune;
			cout << string(100, '\n');
		}

		return 0;
	}
	else
		if (argc == 2)
		{
			string ec = argv[1];
			IntegritateEcuatie e(ec);
			if (e.integritateOperatori() != false && e.integritateParanteze() != false && !e)//!e inseamna daca nu exita '/0' impartiri la 0
			{
				Ecuatie ecu(ec);
				ecu.configureazaPtCalcul();
				--ecu;//elimina spatiile
				afis(ecu.evalueazaEcuatia());
			}
			else
			{
				cout << "gresita..." << endl;
				return 0;
			}
		}
		else
		{
			cout << "Prea multe argumente...";
			return 0;
		}

}