#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class Address
{
    char locality[50];
    char city[50];
    char state[50];
    int pincode;

public:
    void getAddress()
    {
        cout << "\nEnter address : ";
        cout << "\n------------------------\n";
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
        cout << "\nAddress : " << locality << " , " << city << " , " << state << " , Pincode - " << pincode << endl;
    }
};

class Bank
{
    int accno;
    char name[50];
    long long int mobno;
    Address address;
    float balance;
    char type[10];

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
    cout << "\n\nEnter your name : ";
    cin >> name;
    cout << "\n\nEnter your mobile number : ";
    cin >> mobno;
    address.getAddress();
    cout << "\n\nEnter account type : ";
    cin >> type;
    cout << "\n\nEnter initial account balance : ";
    cin >> balance;

    cout << "\n***********************************";
    cout << "\nACCOUNT CREATED!";
    cout << "\n***********************************";
}

void Bank::displayAccountDetails()
{
    cout << "\nAccount No. : " << accno;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nMobile Number : " << mobno;
    address.showAddress();
    cout << "\nType of Account : " << type;
    cout << "\nAvailable Balance : " << balance;
}

void Bank::modifyDetails()
{
    int ch;
    char choice;

    do
    {
        cout << "\nMODIFY YOUR DETAILS ";
        cout << "\n------------------------------\n";
        cout << "\n1. Name";
        cout << "\n2. Mobile Number";
        cout << "\n3. Address";
        cout << "\n\nEnter your choice : ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "\nEnter Name : ";
            cin >> name;
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
        cout << "\nGo back to MENU again? (y/n)" << endl;
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}

void Bank::depositAmt(int amt)
{
    balance += amt;
    cout << "\nAvailable Balance : " << balance << endl;
}

void Bank::withdrawAmt(int amt)
{
    balance -= amt;
    cout << "\nAvailable Balance : " << balance << endl;
}

void Bank::report()
{
    cout << accno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << balance << endl;
}

int Bank::returnAccno()
{
    return accno;
}

int Bank::returnBal()
{
    return balance;
}

void write_Bank();
void display_sp(int);
void modifyDetails_Bank(int);
void delete_Bank(int);
void display_all();
void balance_withwithdrawAmt(int, int);

int main()
{
    int ch;
    int num;
    do
    {
        cout << "\n*************************\n";
        cout << "BANK MANAGEMENT SYSTEM";
        cout << "\n*************************\n";

        cout << "\nMAIN MENU :-";
        cout << "\n1. Create an account";
        cout << "\n2. Deposit amount";
        cout << "\n3. Withdraw amount";
        cout << "\n7. Modify Account Details";
        cout << "\n6. Close account";
        cout << "\n4. BALANCE ENQUIRY";
        cout << "\n5. ALL Bank HOLDER LIST";
        cout << "\n8. EXIT";
        cout << "\n\nEnter your choice (1-8): ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            write_Bank();
            break;
        case 2:
            cout << "\n\nEnter The Bank No. : ";
            cin >> num;
            balance_withwithdrawAmt(num, 1);
            break;
        case 3:
            cout << "\n\nEnter The Bank No. : ";
            cin >> num;
            balance_withwithdrawAmt(num, 2);
            break;
        case 4:
            cout << "\n\nEnter The Bank No. : ";
            cin >> num;
            display_sp(num);
            break;
        case 5:
            display_all();
            break;
        case 6:
            cout << "\n\nEnter The Bank No. : ";
            cin >> num;
            delete_Bank(num);
            break;
        case 7:
            cout << "\n\nEnter The Bank No. : ";
            cin >> num;
            modifyDetails_Bank(num);
            break;
        case 8:
            cout << "\n\nBrought To You By code-projects.org";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();

    } while (ch != 8);

    return 0;
}

void write_Bank()
{
    Bank b;
    ofstream fo;
    fo.open("account.dat", ios::binary | ios::app);

    b.createAccount();
    fo.write((char *)&b, sizeof(b));
    fo.close();
}

void display_sp(int n)
{
    Bank ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("Bank.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank)))
    {
        if (ac.returnAccno() == n)
        {
            ac.displayAccountDetails();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nBank number does not exist";
}

void modifyDetails_Bank(int n)
{
    bool found = false;
    Bank ac;
    fstream File;
    File.open("Bank.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank));
        if (ac.returnAccno() == n)
        {
            ac.displayAccountDetails();
            cout << "\n\nEnter The New Details of Bank" << endl;
            ac.modifyDetails();
            int pos = (-1) * static_cast<int>(sizeof(Bank));
            File.seekp(pos, ios::cur); //fncallat1353
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank));
            cout << "\n\nRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nRecord Not Found ";
}

void delete_Bank(int n)
{
    Bank ac;
    ifstream inFile;
    ofstream fo;
    inFile.open("Bank.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    fo.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank)))
    {
        if (ac.returnAccno() != n)
        {
            fo.write(reinterpret_cast<char *>(&ac), sizeof(Bank));
        }
    }
    inFile.close();
    fo.close();
    remove("Bank.dat");
    rename("Temp.dat", "Bank.dat");
    cout << "\n\nRecord Deleted ..";
}

void display_all()
{
    system("CLS");
    Bank ac;
    ifstream inFile;
    inFile.open("Bank.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\nBank HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Bank)))
    {
        ac.report();
    }
    inFile.close();
}

void balance_withwithdrawAmt(int n, int option)
{
    int amt;
    bool found = false;
    Bank ac;
    fstream File;
    File.open("Bank.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(Bank));
        if (ac.returnAccno() == n)
        {
            ac.displayAccountDetails();
            if (option == 1)
            {
                cout << "\n\nTO balanceSS AMOUNT";
                cout << "\n\nEnter The amount to be balanceed: ";
                cin >> amt;
                ac.depositAmt(amt);
            }
            if (option == 2)
            {
                cout << "\n\nTO WITHwithdrawAmt AMOUNT";
                cout << "\n\nEnter The amount to be withwithdrawAmt: ";
                cin >> amt;
                int bal = ac.returnBal() - amt;
                if (bal < 0)
                    cout << "Insufficience balance";
                else
                    ac.withdrawAmt(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur); //fn1353
            File.write(reinterpret_cast<char *>(&ac), sizeof(Bank));
            cout << "\n\nRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\nRecord Not Found ";
}
