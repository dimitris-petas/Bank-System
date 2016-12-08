
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <vector>


using namespace std;

class Account
{
protected:
 char* name;
 char* surname;
 char* afm;
 char* account_number;
 float balance;

public:

 Account(char* name, char* surname, char* afm, char* account_number, float balance)
 {
 //this->name = name; --> OXI antigrafi pointers
 //to sosto einai:
 this->name = new char[strlen(name)+1];
 strcpy(this->name, name);

 this->surname = new char[strlen(surname)+1];
 strcpy(this->surname, surname);

 this->afm = new char[strlen(afm)+1];
 strcpy(this->afm, afm);

 this->account_number = new char[strlen(account_number)+1];
 strcpy(this->account_number, account_number);

 this->balance = balance;
 }

 Account()
 {
 //this->name = "N/A"; --> OXI
 this->name = new char[4]; // To "N/A" xreiazetai 4 chars
 strcpy(this->name, "N/A");

 this->surname = new char[4];
 strcpy(this->surname, "N/A");

 this->afm = new char[4];
 strcpy(this->afm, "N/A");

 this->account_number = new char[4];
 strcpy(this->account_number, "N/A");

 this->balance = 0;
 }

 Account(Account& acc)
 {
 //this->name = acc.name; --> OXI antigrafi pointers
 //to sosto einai:
 this->name = new char[strlen(acc.name)+1];
 strcpy(this->name, acc.name);

 this->surname = new char[strlen(acc.surname)+1];
 strcpy(this->surname, acc.surname);

 this->afm = new char[strlen(acc.afm)+1];
 strcpy(this->afm, acc.afm);

 this->account_number = new char[strlen(acc.account_number)+1];
 strcpy(this->account_number, acc.account_number);

 this->balance = acc.balance;
 }

 Account& operator=(Account& acc)
 {
 //this->name = acc.name; --> OXI antigrafi pointers
 //to sosto einai:
 delete[] this->name;
 this->name = new char[strlen(acc.name)+1];
 strcpy(this->name, acc.name);

 delete[] this->surname;
 this->surname = new char[strlen(acc.surname)+1];
 strcpy(this->surname, acc.surname);

delete[] this->afm;
 this->afm = new char[strlen(acc.afm)+1];
 strcpy(this->afm, acc.afm);

 delete[] this->account_number;
 this->account_number = new char[strlen(acc.account_number)+1];
 strcpy(this->account_number, acc.account_number);

 this->balance = acc.balance;

 return *this;
 }

 virtual float getBalance() = 0;
 virtual void display() = 0;
 virtual void deposit(float amount) = 0;
 virtual void withdraw(float amount) = 0;

 char* getAccountNumber()
 {
 return account_number;
 }
};

class SavingsAccount : public Account
{
protected:
 float interest;
public:

 SavingsAccount(char* name, char* surname, char* afm, char* account_number, float balance, float interest)
 : Account(name, surname, afm, account_number, balance)
 {
 this->interest = interest;
 }

 SavingsAccount() : Account()
 {
 this->interest = 0;
 }

 //Kaloume prwta ton copy constructor ths Account class
 SavingsAccount(SavingsAccount& acc):Account(acc)
 {
 //meta antigrafoume ta epipleon pedia
 this->interest = acc.interest;
 }

 SavingsAccount& operator=(SavingsAccount& acc)
 {
 //Kaloume prwta ton assignment operator ths Account class
 Account::operator=(acc);

 //meta antigrafoume ta epipleon pedia
 this->interest = acc.interest;
 }

 /*
 //Enallaktiki ylopoiisi tou assignment operator
 SavingsAccount& operator=(SavingsAccount& acc)
 {
 delete[] this->name;
 this->name = new char[strlen(acc.name)+1];
 strcpy(this->name, acc.name);

 delete[] this->surname;
 this->surname = new char[strlen(acc.surname)+1];
 strcpy(this->surname, acc.surname);

 delete[] this->afm;
 this->afm = new char[strlen(acc.afm)+1];
 strcpy(this->afm, acc.afm);

 delete[] this->account_number;
 this->account_number = new char[strlen(acc.account_number)+1];
 strcpy(this->account_number, acc.account_number);

 this->balance = acc.balance;

 this->interest = acc.interest;
 }
 */
 void deposit(float amount)
 {
 balance += amount * (1 + interest / 100);
 }

 void withdraw(float amount)
 {
 if (amount > balance)
 cout << "problem" << endl;
 else
 balance -= amount;
 }

 float getBalance()
 {
 return balance;
 }

 void display()
 {
 cout << "Onoma: " << name << " " << surname << endl;
 cout << "Ar. logariasmou: " << account_number << endl;
 cout << "Ypoloipo: " << balance << endl;
 cout << "Epitokio: " << interest << endl;
 }


};

class CheckingAccount : public Account
{
 float commission;
public:

 CheckingAccount(char* name, char* surname, char* afm, char* account_number, float balance, float commission)
 : Account(name, surname, afm, account_number, balance)
 {
 this->commission = commission;
 }

 CheckingAccount() : Account()
 {
 this->commission = 0;
 }

 CheckingAccount(CheckingAccount& acc):Account(acc)
 {
 this->commission = acc.commission;
 }

 CheckingAccount& operator=(CheckingAccount& acc)
 {
 Account::operator=(acc);
 this->commission = acc.commission;
 }

 void deposit(float amount)
 {
 balance += amount * (1 - commission / 100);
 }

 void withdraw(float amount)
 {
 if (amount > balance)
 cout << "problem" << endl;
 else
 balance -= amount * (1 + commission / 100);
 }

 float getBalance()
 {
 return balance;
 }

 void display()
 {
 cout << "Onoma: " << name << " " << surname << endl;
 cout << "Ar. logariasmou: " << account_number << endl;
 cout << "Ypoloipo: " << balance << endl;
 cout << "Promitheia: " << commission << endl;
 }

};

class OverdraftAccount : public Account
{
 float commission;
 float maxOverdraft;
public:

 OverdraftAccount(char* name, char* surname, char* afm, char* account_number, float balance, float commission,
float maxOverdraft )
 : Account(name, surname, afm, account_number, balance)
 {
 this->commission = commission;
 this->maxOverdraft = maxOverdraft;
 }
 OverdraftAccount() : Account()
 {
 this->commission = 0;
 this->maxOverdraft = 0;
 }

 OverdraftAccount(OverdraftAccount& acc):Account(acc)
 {
 this->commission = acc.commission;
 this->maxOverdraft = acc.maxOverdraft;
 }

 OverdraftAccount& operator=(OverdraftAccount& acc)
 {
 Account::operator=(acc);
 this->commission = acc.commission;
 this->maxOverdraft = acc.maxOverdraft;
 }

 void deposit(float amount)
 {
 balance += amount * (1 - commission / 100);
 }

 void withdraw(float amount)
 {
 if (amount > balance + maxOverdraft)
 cout << "problem" << endl;
 else
 balance -= amount * (1 + commission / 100);
 }

 float getBalance()
 {
 return balance;
 }

 void display()
 {
 cout << "Onoma: " << name << " " << surname << endl;
 cout << "Ar. logariasmou: " << account_number << endl;
 cout << "Ypoloipo: " << balance << endl;
 cout << "Promitheia: " << commission << endl;
 cout << "Poso yperanalipsis: " << maxOverdraft << endl;
 }
 };

void print_central_menu()
{
 cout << "Epiloges: " << endl;
 cout << "1: Eisagogi neou logariasmou " << endl;
 cout << "2: Emfanisi olwn twn logariasmwn " << endl;
 cout << "3: Synallagi " << endl;
 cout << "0: Exodos " << endl;
}

void print_synallagi_menu()
{
 cout << "Epiloges synallagwn: " << endl;
 cout << "1: Katathesi " << endl;
 cout << "2: Analipsi " << endl;
 cout << "3: Emfanisi ypoloipou " << endl;
}

int main(int argc, char* argv[])
{
 //o vector gia tin apothikeusi olwn twn logariasmwn
 vector<Account*> v;

 //Prosorines metablites gia diavasma apo to pliktrologio
 char name[100], surname[200], afm[10], account_number[20];
 int selection;
 float balance, interest, commission, overdraft;
 float poso;

 print_central_menu();

 while(cin >> selection)
 {
 cin.ignore();

 switch(selection)
 {
 case 0:
 cout << "Exiting..." << endl;
 return 0;

 case 1:
 cout << "Epilekste typo logariasmou (1:Savings, 2:Checking, 3:Overdraft) -->";
 cin >> selection;
 cin.ignore();
 cout << "Eponymo: " ;
 cin.getline(surname, 200);
 cout << "Onoma: " ;
 cin.getline(name, 100);
 cout << "AFM: " ;
 cin.getline(afm, 10);
 cout << "Ar. logariasmou: " ;
 cin.getline(account_number, 10);
 cout << "Arxiko ypoloipo: " ;
 cin >> balance;
 if(selection == 1)
 {
 cout << "Epitokio: ";
 cin >> interest;
 cin.ignore();

 v.push_back(new SavingsAccount(name, surname, afm, account_number, balance, interest));
 cout << "O logariasmos dimiourgithike" << endl;
 }
 else if(selection == 2)
 {
 cout << "Promitheia: ";
 cin >> commission;
 cin.ignore();

 v.push_back(new CheckingAccount(name, surname, afm, account_number, balance, commission));
 cout << "O logariasmos dimiourgithike" << endl;
 }
 else if(selection == 3)
 {
 cout << "Epitokio: ";
 cin >> interest;
 cout << "Poso yperanalipsis: ";
 cin >> overdraft;
 cin.ignore();

 v.push_back(new OverdraftAccount(name, surname, afm, account_number, balance,interest,
overdraft));
 cout << "O logariasmos dimiourgithike" << endl;
 }
 else
 cout << "Lathos epilogi!" << endl;

break;


 case 2:
 cout << "-----Analysi logariasmwn----" << endl;

 for(int i =0; i<v.size(); i++)
 {
 cout << "Logariasmos n." << i+1 << ": " << endl;
 v[i]->display();
 }

 break;

 case 3:
 print_synallagi_menu();
 cin >> selection;
 cin.ignore();

 cout << "Doste arithmo logariasmou: " << endl;
 cin.getline(account_number, 20);

 int found = 0;
 switch(selection)
 {
 case 1:
 cout << "Doste poso katathesis: " << endl;
 cin >> poso;
 cin.ignore();

 for(int i =0; i<v.size(); i++)
 {
 //anazitisi logariasmou
 //char temp[20] = v[i]->getAccountNumber();
 if(strcmp(v[i]->getAccountNumber(), account_number) == 0)
 {
 v[i]->deposit(poso);
 found = 1;
 cout << "H katathesi egine epityxws" << endl;
 cout << "Neo ypoloipo:" << v[i]->getBalance() << endl;
 break;
 }
 }
 if(found == 0)
 cout << " O logariasmos den vrethike" << endl;
 break;

 case 2:
 cout << "Doste poso analipsis: " << endl;
 cin >> poso;
 cin.ignore();

 for(int i =0; i<v.size(); i++)
 {
 //anazitisi logariasmou
 if(strcmp(v[i]->getAccountNumber(), account_number) == 0)
 {
 v[i]->withdraw(poso);
 found = 1;
 cout << "H analipsi egine epityxws" << endl;
 cout << "Neo ypoloipo:" << v[i]->getBalance() << endl;
 break;
 }
 }
 if(found == 0)
 cout << " O logariasmos den vrethike" << endl;
 break;

 case 3:
 for(int i =0; i<v.size(); i++)
 {
 //anazitisi logariasmou
 if(strcmp(v[i]->getAccountNumber(), account_number) == 0)
 {
 found = 1;
 cout << "To ypoloipo einai: " << v[i]->getBalance() << endl;
 }
 }
 if(found == 0)
 cout << " O logariasmos den vrethike" << endl;
 break;

 }

 break;
 }

 print_central_menu();
 }
system("PAUSE");
 return 0;
}


