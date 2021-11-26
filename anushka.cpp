#include <iostream>
#include <fstream>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <string.h>
using namespace std;

int generateAccno();
void writeAccount();
void readAccount(int, int);
void modifyAccount(int, int);
void deleteAccount(int, int);
void displayAll();
void updateBalance(int, int, int);
void writeTransaction(int, double, int);
void showTransactionHistory(int, int);

class Address
{
    char locality[50];
    char city[50];
    char state[50];
    int pincode;

public:
    void getAddress()
    {
        cout << "\n-----------------------";
        cout << "\nEnter locality : ";
        cin >> locality;
        cout << "\nEnter city : ";
        cin >> city;
        cout << "\nEnter state : ";
        cin >> state;
        cout << "\nEnter pincode : ";
        cin >> pincode;
    }

    void showAddress()
    {
        locality[0] = toupper(locality[0]);
        city[0] = toupper(city[0]);
        state[0] = toupper(state[0]);

        cout << "\nAddress : " << locality << " , " << city << " , " << state << " , Pincode - " << pincode;
    }
};

class Transaction
{
    char type[15];
    double amt;
    int accno;

public:
    void enter(int accno, double amt, int choice)
    {
        this->accno = accno;
        this->amt = amt;

        if (choice == 1)
        {
            strcpy(type, "Deposit");
        }
        else if (choice == 2)
        {
            strcpy(type, "Withdrawal");
        }
    }

    void display()
    {

        cout << "\n"
             << accno << setw(15) << type << setw(15) << amt;
    }
};

class Bank
{
    int accno;
    int pin;
    char firstName[30], lastName[30];
    long long int mobno;
    Address address;
    double balance;
    char accType[10];

public:
    void createAccount();
    void displayAccountDetails();
    void modifyDetails();
    void depositAmt(int amt);
    void withdrawAmt(int amt);
    void report();
    int returnAccno();
    int returnBal();
    int returnPIN();
};

void Bank::createAccount()
{
    accno = generateAccno();
    cout << "\n\nEnter your First Name : ";
    cin >> firstName;
    cout << "\n\nEnter your Last Name : ";
    cin >> lastName;
    cout << "\n\nEnter your mobile number : ";
    cin >> mobno;
    cout << "\nEnter address : ";
    address.getAddress();
    cout << "\n\nEnter account type : ";
    cin >> accType;
    cout << "\n\nEnter initial account balance : ";
    cin >> balance;
    cout << "\n\n\nEnter your security pin : ";
    cin >> pin;

    cout << "\n***********************************";
    cout << "\nACCOUNT CREATED!";
    cout << "\nYour account number is : " << accno;
    cout << "\n***********************************";
}

void Bank::displayAccountDetails()
{
    cout << "\n-------------------------------------------";
    cout << "\nAccount No. : " << accno;
    cout << "\nAccount Holder Name : ";
    cout << firstName << " " << lastName;
    cout << "\nMobile number : " << mobno;
    address.showAddress();
    cout << "\nAccount type : " << accType;
    cout << "\n-------------------------------------------";
    cout << "\nAvailable Balance : " << balance;
    cout << "\n-------------------------------------------";
}

void Bank::modifyDetails()
{
    int ch;
    char choice;

    do
    {
        cout << "\nMODIFY YOUR DETAILS ";
        cout << "\n-----------------------------";
        cout << "\n1. Name";
        cout << "\n2. Mobile number";
        cout << "\n3. Address";
        cout << "\n\nEnter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "\nEnter First Name : ";
            cin >> firstName;
            cout << "\nEnter Last Name : ";
            cin >> lastName;
            break;
        case 2:
            cout << "\nEnter Mobile number : ";
            cin >> mobno;
            break;
        case 3:
            cout << "\nEnter Address : ";
            address.getAddress();
            break;

        default:
            cout << "\nINVALID CHOICE!";
            break;
        }
        cout << "\nDo you want to modify again? (y/n) : ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}

void Bank::depositAmt(int amt)
{
    balance += amt;
    cout << "\n------------------------------------------";
    cout << "\nAvailable Balance : " << balance;
    cout << "\n------------------------------------------";
}

void Bank::withdrawAmt(int amt)
{
    balance -= amt;
    cout << "\n------------------------------------------";
    cout << "\nAvailable Balance : " << balance;
    cout << "\n------------------------------------------";
}

void Bank::report()
{
    cout << accno << setw(15) << firstName << setw(15) << lastName << setw(15) << accType << setw(15) << balance << endl;
}

int Bank::returnAccno()
{
    return accno;
}

int Bank::returnBal()
{
    return balance;
}

int Bank::returnPIN()
{
    return pin;
}

int main()
{
    int ch, acc, pin;
    do
    {
        cout << "\n*************************\n";
        cout << "BANK MANAGEMENT SYSTEM";
        cout << "\n*************************\n";

        cout << "\nMAIN MENU :-";
        cout << "\n1. Create an account";
        cout << "\n2. Deposit amount";
        cout << "\n3. Withdraw amount";
        cout << "\n4. Check balance";
        cout << "\n5. Display All Bank Holders List";
        cout << "\n6. Close an account";
        cout << "\n7. Modify account details";
        cout << "\n8. Show Transaction History";
        cout << "\n9. EXIT";
        cout << "\n\nEnter your choice (1-9): ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            updateBalance(acc, 1, pin);
            break;
        case 3:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            updateBalance(acc, 2, pin);
            break;
        case 4:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            readAccount(acc, pin);
            break;
        case 5:
            displayAll();
            break;
        case 6:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            deleteAccount(acc, pin);
            break;
        case 7:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            modifyAccount(acc, pin);
            break;

        case 8:
            cout << "\n\nEnter accno : ";
            cin >> acc;
            cout << "\n\nEnter pin : ";
            cin >> pin;
            showTransactionHistory(acc, pin);
            break;
        case 9:
            cout << "\n*********************************\n";
            cout << "THANK YOU, SEE YOU NEXT TIME!";
            cout << "\n*********************************\n";
            break;
        default:
            cout << "\n\nINVALID CHOICE!";
        }

        cin.ignore();
        cout << "\nPress any key to continue..." << endl;
        cin.get();

    } while (ch != 9);

    return 0;
}

int generateAccno()
{
    srand(time(0));

    Bank b;
    int flag = 0, n;
    do
    {
        flag = 0;
        n = rand() % 10000 + 1000;

        ifstream fin("accounts.dat", ios::binary);
        while (fin.read((char *)&b, sizeof(b)))
        {
            if (b.returnAccno() == n)
            {
                flag = 1;
                break;
            }
        }
        fin.close();

    } while (flag);

    return n;
}

void writeAccount()
{
    Bank b;
    ofstream fout("accounts.dat", ios::binary | ios::app);

    b.createAccount();
    fout.write((char *)&b, sizeof(b));
    fout.close();
}

void readAccount(int n, int pin)
{
    Bank b;
    int flag = 0;
    ifstream fin("accounts.dat", ios::binary | ios::in);

    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";

        return;
    }

    while (fin.read((char *)&b, sizeof(b)))
    {
        if (b.returnAccno() == n && b.returnPIN() == pin)
        {
            flag = 1;
            b.displayAccountDetails();
        }
    }

    fin.close();

    if (!flag)
    {
        cout << "\n*****************************";
        cout << "\nINVALID DETAILS!";
        cout << "\n*****************************";
        ;
    }
}

void modifyAccount(int n, int pin)
{
    int found = 0;
    Bank b;

    fstream fin("accounts.dat", ios::binary | ios::in | ios::out);

    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }

    while (fin.read((char *)&b, sizeof(b)) && !found)
    {
        if (b.returnAccno() == n)
        {
            found = 1;

            b.displayAccountDetails();

            cout << "\n\nEnter the new details : ";
            b.modifyDetails();

            int pos = (-1) * (sizeof(b));
            fin.seekp(pos, ios::cur);

            fin.write((char *)&b, sizeof(b));
            cout << "\n*****************************";
            cout << "\nRecord Updated";
            cout << "\n*****************************";
        }
    }

    fin.close();

    if (!found)
    {
        cout << "\n*****************************";
        cout << "\nINVALID DETAILS!!!!";
        cout << "\n*****************************";
    }
}

void deleteAccount(int n, int pin)
{
    Bank b;
    ifstream fin;
    ofstream fout;
    int flag = 0;

    fin.open("accounts.dat", ios::binary);
    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }

    fout.open("temp.dat", ios::binary);

    fin.seekg(0, ios::beg);

    while (fin.read((char *)&b, sizeof(b)))
    {
        if (b.returnAccno() != n)
        {
            fout.write((char *)&b, sizeof(b));
        }
        else if (b.returnAccno() == n && b.returnPIN() == pin)
        {
            flag = 1;
        }
    }

    fin.close();
    fout.close();

    if (flag)
    {
        remove("accounts.dat");
        rename("Temp.dat", "accounts.dat");

        cout << "\n*****************************";
        cout << "\nRecord Deleted";
        cout << "\n*****************************";
    }
    else
    {
        remove("Temp.dat");
        cout << "\n*****************************";
        cout << "\nINVALID DETAILS!";
        cout << "\n*****************************";
    }
}

void displayAll()
{
    Bank b;
    ifstream fin;
    fin.open("accounts.dat", ios::binary);

    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }

    cout << "\n\nBank Holder List\n\n";
    cout << "=======================================================================\n";
    cout << " A/c no." << setw(15) << "First Name" << setw(15) << "Last Name" << setw(15) << "accType" << setw(15) << "Balance\n";
    cout << "=======================================================================\n";
    while (fin.read((char *)&b, sizeof(b)))
    {
        b.report();
    }
    fin.close();
}

void updateBalance(int n, int choice, int pin)
{
    int found = 0;
    double amt;
    Bank b;

    fstream fin("accounts.dat", ios::binary | ios::in | ios::out);
    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }

    while (!fin.eof() && !found)
    {
        fin.read((char *)&b, sizeof(b));
        if (b.returnAccno() == n && b.returnPIN() == pin)
        {
            found = 1;

            b.displayAccountDetails();
            if (choice == 1)
            {
                cout << "\n\nEnter The amount to be deposit : ";
                cin >> amt;
                b.depositAmt(amt);
            }
            if (choice == 2)
            {
                cout << "\n\nEnter The amount to be withdrawn : ";
                cin >> amt;

                int bal = b.returnBal() - amt;
                if (bal < 0)
                {
                    cout << "\n*****************************";
                    cout << "\nInsufficient Balance!";
                    cout << "\n*****************************";
                    return;
                }
                else
                    b.withdrawAmt(amt);
            }

            int pos = (-1) * (sizeof(b));
            fin.seekp(pos, ios::cur);
            fin.write((char *)&b, sizeof(b));

            cout << "\n\nRecord Updated!";

            writeTransaction(n, amt, choice);
        }
    }
    fin.close();

    if (!found)
    {
        cout << "\n*****************************";
        cout << "\nRecord Not found ";
        cout << "\n*****************************";
    }
}

void writeTransaction(int accno, double amt, int choice)
{
    string filename = to_string(accno);
    filename = filename + ".dat";
    ofstream fout(filename, ios ::binary | ios::app);

    Transaction t;
    t.enter(accno, amt, choice);

    fout.write((char *)&t, sizeof(t));
}

void showTransactionHistory(int n, int pin)
{
    int found = 0;
    Bank b;
    ifstream fin("accounts.dat", ios::binary | ios::in);
    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }

    while (!fin.eof() && !found)
    {
        fin.read((char *)&b, sizeof(b));
        if (b.returnAccno() == n && b.returnPIN() == pin)
        {
            found = 1;
            break;
        }
    }
    fin.close();

    if (!found)
    {
        cout << "\n*****************************";
        cout << "\nRecord Not found ";
        cout << "\n*****************************";
    }
    else
    {
        Transaction t;

        string filename = to_string(n);
        filename = filename + ".dat";
        ifstream ftrans_In(filename, ios::binary | ios::in);
        cout << "\nAccno" << setw(15) << "Type" << setw(15) << "Amount";
        cout << "\n=============================================\n";

        while (ftrans_In.read((char *)&t, sizeof(t)))
        {
            t.display();
        }
        cout << endl;
    }
}