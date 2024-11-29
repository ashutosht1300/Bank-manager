
#include <iostream>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <iomanip>
using namespace std;

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;

  public:
    void input_details();
    void show_account() const;
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;
};

int getdata()
{
    int a;
    while (1)
    {
        cin >> a;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(120, '\n');
            cout << "invalid !\n";
        }
        else
            break;
    }
    cin.ignore(120, '\n');
    return a;
}

void account::input_details()
{
    cout << "\n\tEnter the Account No. : ";
    acno = getdata();
    cout << "\n\tPlease Enter the Name of the Account holder Here : ";
    cin.getline(name, 50);
    cout << "\n\tChoose Type of the Account  : \n\t1. Saving\t2. Current\n \t";
    string chtype;
retype:
    getline(cin, chtype);
    switch (chtype[0])
    {
    case '1':
    case 's':
    case 'S':
        type = 'S';
        break;
    case '2':
    case 'c':
    case 'C':
        type = 'C';
        break;
    default:
        cout << "\tChoose correct type ";
        goto retype;
    }

    cout << "\n\tEnter The Initial amount : ";
    deposit = getdata();
}

void account::show_account() const
{
    cout << "\n\tAccount No. : " << acno;
    cout << "\n\tAccount Holder Name : ";
    cout << name;
    cout << "\n\tType of Account : " << type;
    cout << "\n\tBalance amount : " << deposit;
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout <<setw(5)<<acno << setw(5) <<" ";
    cout<<setw(10);
    char nm[10];
    for(int i=0;i<10;++i)
        nm[i]=name[i];
    cout<< nm ;
    cout<< setw(5) << " " << type ;
    cout<< setw(5) << " " << deposit << endl;
}

int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

//------------------------main start------------------------
int main()
{
    string ch;
    int num;
    do
    {
        clrscr();
        cout << "\n\n\t\t======================\n";
        cout << "\t\tBANK MANAGEMENT SYSTEM";
        cout << "\n\t\t======================\n";

        cout << "\t\t   ::MAIN MENU::\n";
        cout << "\n\t1. NEW ACCOUNT";
        cout << "\n\t2. DEPOSIT AMOUNT";
        cout << "\n\t3. WITHDRAW AMOUNT";
        cout << "\n\t4. BALANCE ENQUIRY";
        cout << "\n\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t6. CLOSE AN ACCOUNT";
        cout << "\n\t7. MODIFY AN ACCOUNT";
        cout << "\n\t8. EXIT";
        cout << "\n\n\tSelect Your Option (1-8): ";
        getline(cin, ch);

        switch (ch[0])
        {
        case '1':
            write_account();
            break;

        case '2':
            clrscr();
            cout << "\n\n\tEnter The account No. : ";
            num = getdata();
            deposit_withdraw(num, 1);
            break;

        case '3':
            clrscr();
            cout << "\n\n\tEnter The account No. : ";
            num = getdata();
            deposit_withdraw(num, 2);
            break;

        case '4':
            clrscr();
            cout << "\n\n\tEnter The account No. : ";
            num = getdata();
            display_sp(num);
            break;

        case '5':
            display_all();
            break;

        case '6':
            clrscr();
            cout << "\n\n\tEnter The account No. : ";
            num = getdata();
            delete_account(num);
            break;

        case '7':
            clrscr();
            cout << "\n\n\tEnter The account No. : ";
            num = getdata();
            modify_account(num);
            break;

        case '8':
            clrscr();
            cout << "\n\n\tBrought To You By Ashutosh Tamrakar";
            break;

        default:
            system("color 4");
            cout << "\t\tWrong choice\n";
            system("color 7");
        }
        getch();
    } while (ch[0] != '8');
    return 0;
}
//--------------------------main end------------------

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("acc.txt",  ios::app);
    ac.input_details();
    outFile.write((char*)&ac, sizeof(account));
    outFile.close();
    cout << "\tdata entered successfully\n";
}

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("acc.txt");
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\tBALANCE DETAILS\n";
    while (inFile.read((char*)&ac, sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\n\tAccount number does not exist";
}

void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("acc.txt", ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read((char*)&ac, sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n\tEnter The New Details of account" << endl;
            ac.input_details();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur); //fncallat1353
            File.write((char*)&ac, sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\tRecord Not Found ";
}

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("acc.txt");
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat");
    inFile.seekg(0, ios::beg);
    while (inFile.read((char*)&ac, sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write((char*)&ac, sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("acc.txt");
    rename("Temp.dat", "acc.txt");
    cout << "\n\n"
         << n << " Record Deleted ..";
}

void display_all()
{
    clrscr();
    account ac;
    ifstream inFile;
    inFile.open("acc.txt");
    if (!inFile)
    {
        cout << "\tFile could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME      Type      Balance\n";
    cout << "====================================================\n";
    while (inFile.read((char*)&ac, sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("acc.txt",  ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read((char*)&ac, sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITSS AMOUNT";
                cout << "\n\n\tEnter The amount to be deposited: ";
                amt = getdata();
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\n\tEnter The amount to be withdraw: ";
                amt = getdata();
                int bal = ac.retdeposit() - amt;
                if (bal < 0)
                    cout << "Insufficience balance!";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * sizeof(account);
            File.seekp(pos, ios::cur); //fn1353
            File.write((char*)&ac, sizeof(account));
            cout << "\n\n\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\tRecord Not Found ";
}
