#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

int generateAccno();
void writeAccount();
void readAccount(int);
void modifyAccount(int);
void deleteAccount(int);
void display_all();
void updateBalance(int, int);
void transactionHistory(int);

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

class Bank
{
    int accno;
    char firstName[30], lastName[30];
    long long int mobno;
    Address address;
    float balance;
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
    cout << "\n\nEnter account account type : ";
    cin >> accType;
    cout << "\n\nEnter initial account balance : ";
    cin >> balance;

    cout << "\n***********************************";
    cout << "\nACCOUNT CREATED!";
    cout << "\nYour account number is : " << accno;
    cout << "\n***********************************";
}

void Bank::displayAccountDetails()
{
    cout << "\nAccount No. : " << accno;
    cout << "\nAccount Holder Name : ";
    cout << firstName<<" "<<lastName;
    cout << "\nMobile Number : " << mobno;
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
        cout << "\n2. Mobile Number";
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
            cout << "\nEnter Mobile Number : ";
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
        cout << "\nDo you want to modify again? (y/n)";
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
    cout << accno << setw(10) << " " << firstName << setw(10) << lastName << setw(10) << " " << accType << setw(6) << balance << endl;
}

int Bank::returnAccno()
{
    return accno;
}

int Bank::returnBal()
{
    return balance;
}

int main()
{
    int ch, num;
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
        cout << "\n5. ALL Bank HOLDER LIST";
        cout << "\n6. Close an account";
        cout << "\n7. Modify account details";
        cout << "\n8. EXIT";
        cout << "\n\nEnter your choice (1-8): ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "\n\nEnter accno : ";
            cin >> num;
            updateBalance(num, 1);
            break;
        case 3:
            cout << "\n\nEnter accno : ";
            cin >> num;
            updateBalance(num, 2);
            break;
        case 4:
            cout << "\n\nEnter accno : ";
            cin >> num;
            readAccount(num);
            break;
        case 5:
            display_all();
            break;
        case 6:
            cout << "\n\nEnter accno : ";
            cin >> num;
            deleteAccount(num);
            break;
        case 7:
            cout << "\n\nEnter accno : ";
            cin >> num;
            modifyAccount(num);
            break;
        case 8:
            cout << "\n*********************************\n";
            cout << "THANK YOU, SEE YOU NEXT TIME!";
            cout << "\n*********************************\n";
            return;
            break;
        default:
            cout << "\n\nINVALID CHOICE!";
        }
        cin.ignore();
        cout << "\nPress any key to continue..." << endl;
        cin.get();

    } while (ch != 8);

    return 0;
}
void transactionHistory(int)
{
}

int generateAccno()
{
    Bank b;
    int flag = 0, n;
    do
    {
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

void readAccount(int n)
{
    Bank b;
    int flag = 0;
    ifstream fin("accounts.dat", ios::binary);

    if (!fin)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";

        return;
    }

    while (fin.read((char *)&b, sizeof(b)))
    {
        if (b.returnAccno() == n)
        {
            b.displayAccountDetails();
            flag = 1;
        }
    }

    fin.close();

    if (!flag)
    {
        cout << "\n*****************************";
        cout << "\nBank number does not exist!";
        cout << "\n*****************************";
        ;
    }
}

void modifyAccount(int n)
{
    int found = 0;
    Bank b;

    fstream fio("accounts.dat", ios::binary | ios::in | ios::out);

    if (!fio)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        return;
    }
    while (!fio.eof() && !found)
    {
        fio.read((char *)&b, sizeof(b));

        if (b.returnAccno() == n)
        {
            b.displayAccountDetails();

            cout << "\n\nEnter The New Details of Bank";
            b.modifyDetails();

            int pos = (-1) * (sizeof(b));
            fio.seekp(pos, ios::cur);

            fio.write((char *)&b, sizeof(b));
            cout << "\n*****************************";
            cout << "\nRecord Updated";
            cout << "\n*****************************";

            found = 1;
        }
    }

    fio.close();

    if (!found)
    {
        cout << "\n*****************************";
        cout << "\nRecord Not found!!!!";
        cout << "\n*****************************";
    }
}

void deleteAccount(int n)
{
    Bank b;
    ifstream fin;
    ofstream fout;

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
    }

    fin.close();
    fout.close();

    remove("accounts.dat");
    rename("Temp.dat", "accounts.dat");

    cout << "\n*****************************";
    cout << "\nRecord Deleted";
    cout << "\n*****************************";
}

void display_all()
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

    cout << "\n\nBank HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           accType  Balance\n";
    cout << "====================================================\n";
    while (fin.read((char *)&b, sizeof(b)))
    {
        b.report();
    }
    fin.close();
}

void updateBalance(int n, int choice)
{
    int amt, found = 0;
    Bank b;

    fstream fio("accounts.dat", ios::binary | ios::in | ios::out);
    if (!fio)
    {
        cout << "\n*****************************";
        cout << "\nFILE NOT found !!!";
        cout << "\n*****************************";
        ;
        return;
    }
    while (!fio.eof() && found == false)
    {
        fio.read((char *)&b, sizeof(b));
        if (b.returnAccno() == n)
        {
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
            fio.seekp(pos, ios::cur);
            fio.write((char *)&b, sizeof(b));

            cout << "\n\nRecord Updated";

            found = 1;
        }
    }
    fio.close();

    if (!found)
    {
        cout << "\n*****************************";
        cout << "\nRecord Not found ";
        cout << "\n*****************************";
        ;
    }
}
