#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

enum enBanKOpearation { ShowClientList = 1, AddNewClient, DeleteClient, UpdateClientInfo, FindClient, Transactions, ManageUsers, Logout};

enum enTransactions { Deposit = 1, Withdraw, TotalBalances, MainMenue};

enum enManageUsers {ShowUsersLiset = 1, AddNewUser, DeleteUser, UpdateUserInfo, FindUser, MainMenueUser};

struct sUser
{
    string UserName;
    string PassWord;
    short Permissions;

    bool operator == (const sUser& User) const { return(UserName == User.UserName & PassWord == User.PassWord && Permissions == User.Permissions); };

};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

string stringSwitch(enBanKOpearation Choise)
{
    switch (Choise)
    {
    case ShowClientList:
        return "Show Clients Liset?";
    case AddNewClient:
        return "Add New Clients?";
    case DeleteClient:
        return "Delete Clients?";
    case UpdateClientInfo:
        return "Update Clients Info?";
    case FindClient:
        return "Find Clients?";
    case Transactions:
        return "Transactions?";
    case ManageUsers:
        return "Manage Users?";
    default:
        break;
    }
}

bool GetPermission(short Permissions, short OnePer)
{
    return (Permissions & (1 << (OnePer - 1)));
}

short ReadPermissions()
{
    short Permaission = 0;
    char Chois = 'Y';
    cout << "Do you want to give full access? y/n? ";
    cin >> Chois;
    if (toupper(Chois) == 'Y')
        return -1;
    cout << "\nDo you want to give access to:\n";
    for (short i = 0; i < 7; i++)
    {
        cout << stringSwitch(enBanKOpearation(i + 1)) << " Y/N? ";
        cin >> Chois;
        if (toupper(Chois) == 'Y')
            Permaission = (Permaission | (1 << i));
    }

    return Permaission;
}


sUser ReadUserInfo()
{
    sUser User;
    cout << "Please enter User Name? ";
    getline(cin >> ws, User.UserName);
    cout << "Please enter Password? ";
    getline(cin, User.PassWord);
    return User;
}

sUser UpDateAUserInfo(sUser User)
{
    cout << "Please enter Password? ";
    getline(cin >> ws, User.PassWord);
    User.Permissions = ReadPermissions();
    return User;
}

bool FindUserByUserNameAndPassWord(sUser &User, vector <sUser> veUsers)
{
    for (sUser& U : veUsers)
    {
        if (U.UserName == User.UserName && U.PassWord == User.PassWord)
        {
            User = U;
            return true;
        }
            
    }
    return false;
}


void LoginScreen()
{
    
    cout << "------------------------------------\n";
    cout << "\tLoginScreen\n";
    cout << "------------------------------------\n";
}

vector <string> SplitEachWordInVector(string S1, string delim = " ")
{
    vector <string> veSplitString;
    short pos;
    string sWord;
    while ((pos = S1.find(delim)) != std::string::npos)
    {

        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            veSplitString.push_back(sWord);
        }
        S1.erase(0, pos + delim.length());
    }
    if (S1 != "")
        veSplitString.push_back(S1);
    return veSplitString;
}

sUser ConverUserLineToRecorde(string UserLine, string Separator = "#//#")
{
    sUser User;
    vector <string> veUserInfo = SplitEachWordInVector(UserLine, Separator);
    User.UserName = veUserInfo[0];
    User.PassWord = veUserInfo[1];
    User.Permissions = stoi(veUserInfo[2]);
    return User;
}

string ConverUserRecoordeToLine(sUser User, string Separator = "#//#")
{
    string UserLine = "";
    UserLine += User.UserName + Separator;
    UserLine += User.PassWord + Separator;
    UserLine += to_string(User.Permissions);
    return UserLine;
}

vector <sUser> LoadUsersInfoFile(string FileName)
{
    vector <sUser> veUsers;
    fstream UsersFile;
    UsersFile.open(FileName, ios::in);
    if (UsersFile.is_open())
    {
        string Line;
        sUser User;
        while (getline(UsersFile, Line))
        {
            User = ConverUserLineToRecorde(Line);
            veUsers.push_back(User);
        }
        UsersFile.close();
    }
    return veUsers;

}


sClient ConvertLineToRecorde(string stClinetRecord, string Seperator = "#//#")
{
    vector <string> veClientData = SplitEachWordInVector(stClinetRecord, Seperator);
    sClient Client;
    Client.AccountNumber = veClientData[0];
    Client.PinCode = veClientData[1];
    Client.Name = veClientData[2];
    Client.Phone = veClientData[3];
    Client.AccountBalance = stod(veClientData[4]);
    return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecorde(Line);
            vClient.push_back(Client);
        }
        MyFile.close();
    }
    return vClient;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

sClient UpDateaClient(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecorde = "";
    stClientRecorde += Client.AccountNumber + Seperator;
    stClientRecorde += Client.PinCode + Seperator;
    stClientRecorde += Client.Name + Seperator;
    stClientRecorde += Client.Phone + Seperator;
    stClientRecorde += to_string(Client.AccountBalance);

    return stClientRecorde;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream myF;
    myF.open(FileName, ios::out | ios::app);
    if (myF.is_open())
    {
        myF << stDataLine << endl;
        myF.close();
    }
}

string ReadClientAccountNumber(bool Displaine = false)
{
    string AccountNumber;

    if (Displaine)
        cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

bool FindClientBYAccountName(string AccountNumber, vector <sClient> veClients, sClient& FoundClient)
{

    for (sClient& Client : veClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            FoundClient = Client;
            return true;
        }

    }
    return false;
}

void AddaNewClient(vector <sClient>& veClient)
{
    sClient Client;
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";
        string AccountNumber = ReadClientAccountNumber(true);
        while (FindClientBYAccountName(AccountNumber, veClient, Client))
        {
            cout << "Client with [" << AccountNumber << "] already exists, Enter another Account Number? ";
            AccountNumber = ReadClientAccountNumber(false);
        }
        Client = UpDateaClient(AccountNumber);
        veClient.push_back(Client);
        AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');



}


void PrintRecorde(sClient Client)
{
    cout << "\n the following are the client details:\n";
    cout << "\n------------------------------------\n";
    cout << "\nAccountNumber: " << Client.AccountNumber;
    cout << "\nPinCode      : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccountBalance: " << Client.AccountBalance;
    cout << "\n------------------------------------\n";
}

void PrintRecorde(sUser User)
{
    cout << "\n the following are the User details:\n";
    cout << "\n------------------------------------\n";
    cout << "\nUser Name: " << User.UserName;
    cout << "\nPassword : " << User.PassWord;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n------------------------------------\n";
}


vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (!C.MarkForDelete)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }
        MyFile.close();
    }

    return vClients;
}

bool MarkClientForDeleteByAccountNumber(vector <sClient>& veClients, string AccountNumber)
{

    for (sClient& Client : veClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkForDelete = true;
            return true;
        }

    }
    return false;
}

void PrintClientsData(vector <sClient> veClients)
{

    cout << "\t\t\t\t\t Client List (" << veClients.size() << ") Client(s).\n";
    cout << "_____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number" << "| " << left << setw(10) << "Pin Code" << "| " << left << setw(40) << "Client Name" << "| " << left << setw(12) << "Phone" << "| " << left << setw(12) << "Balance ";
    cout << "\n";
    cout << "_____________________________________________________________________________________________\n\n";
    for (sClient& Client : veClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber << "| " << left << setw(10) << Client.PinCode << "| " << left << setw(40) << Client.Name << "| " << left << setw(12) << Client.Phone << "| " << left << setw(12) << Client.AccountBalance << endl;
    }
    cout << "_____________________________________________________________________________________________\n\n";

}

void PrintTotalBalances(vector <sClient> veClients)
{
    int Sum = 0;
    for (sClient C : veClients)
    {
        Sum += C.AccountBalance;
    }

    cout << "\t\t\t\t\t Client List (" << veClients.size() << ") Client(s).\n";
    cout << "_____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number" << "| "<< left << setw(40) << "Client Name" << "| " << left << setw(12) << "Balance ";
    cout << "\n";
    cout << "_____________________________________________________________________________________________\n\n";
    for (sClient& Client : veClients)
    {
        cout << "| " << left << setw(15) << Client.AccountNumber << "| " << left << setw(40) << Client.Name << "| "<< left << setw(12) << Client.AccountBalance << endl;
    }
    cout << "_____________________________________________________________________________________________\n\n";
    cout << "\t\t\t\t\t\t\t" << "Total Balances = " << Sum << endl;
}


void ShowMainMenueScreen()
{
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "==================================================\n";
    cout << "\t" << "[1] Show Client List.\n";
    cout << "\t" << "[2] Add New Client.\n";
    cout << "\t" << "[3] Delete Clietn.\n";
    cout << "\t" << "[4] Update Client Info.\n";
    cout << "\t" << "[5] Find Client.\n";
    cout << "\t" << "[6] Transactions.\n";
    cout << "\t" << "[7] Manage Users.\n";
    cout << "\t" << "[8] Logout.\n";
    cout << "==================================================\n";

}

void ShowUserMainMenueScreen()
{
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tManage Users Main Menue Screen\n";
    cout << "==================================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "==================================================\n";
    cout << "Choose what do you want ot do? [1 to 6]? ";
}

bool DeleteClientByAccountNumber(vector <sClient>& vClients)
{
    sClient Client;
    string AccountNumber = ReadClientAccountNumber(true);
    char Answer = 'n';
    if (FindClientBYAccountName(AccountNumber, vClients, Client))
    {
        PrintRecorde(Client);

        cout << "\n\nAre you sure you are want delete this client? y/n ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {

            MarkClientForDeleteByAccountNumber(vClients, AccountNumber);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted successfully.\n\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number(" << AccountNumber << ") is Not Found!\n\n";
        return false;
    }
    return false;
}

bool UpDataClientByAccountNumber(vector <sClient>& veClients, sClient Client)
{

    for (sClient& C : veClients)
    {
        if (Client.AccountNumber == C.AccountNumber)
        {
            C = Client;
            return true;
        }

    }
    return false;
}

bool UpDataClientToFile(vector <sClient>& vClients)
{
    sClient Client;
    string AccountNumber = ReadClientAccountNumber(true);
    char Answer = 'n';
    if (FindClientBYAccountName(AccountNumber, vClients, Client))
    {
        PrintRecorde(Client);

        cout << "\n\nAre you sure you are want Update this client? y/n ? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            Client = UpDateaClient(AccountNumber);
            UpDataClientByAccountNumber(vClients, Client);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Update successfully.\n\n";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number(" << AccountNumber << ") is Not Found!\n\n";
        return false;
    }
    return false;
}

void PrintScreen(enBanKOpearation BankOpearation)
{
    cout << "------------------------------------\n";
    cout << "\t";
    switch (BankOpearation)
    {
    case enBanKOpearation::AddNewClient:
        cout << "Add New Client ";
        break;
    case enBanKOpearation::DeleteClient:
        cout << "Delete Client ";
        break;
    case enBanKOpearation::UpdateClientInfo:
        cout << "Updaet Clietn Info";
        break;
    case enBanKOpearation::FindClient:
        cout << "Finde Client ";
        break;
    case enBanKOpearation::Transactions:
        cout << "Transactions Menue ";
        break;
    case enBanKOpearation::Logout:
        cout << "End Of Program :-) ";
        break;
    default:
        break;
    }
    if(BankOpearation != enBanKOpearation::Logout)
    cout << "Screen";
   
    cout << "\n------------------------------------\n";

}

void PrintScreen(enManageUsers Manage)
{
    cout << "------------------------------------\n";
    cout << "\t";
    switch (Manage)
    {
    case ShowUsersLiset:
        cout << "Show Users Liset ";
        break;
    case AddNewUser:
        cout << "Add User ";
        break;
    case DeleteUser:
        cout << "Delete User ";
        break;
    case UpdateUserInfo:
        cout << "Update User ";
        break;
    case FindUser:
        cout << "Find User ";
        break;
    default:
        break;
    }
    cout << "Screen\n";
    cout << "------------------------------------\n";

}

void printTransactionScreen(enTransactions Transaction)
{
    cout << "------------------------------------\n";
    cout << "\t";
    switch (Transaction)
    {
    case enTransactions::Deposit:
        cout << "Deposit ";
        break;
    case enTransactions::Withdraw:
        cout << "Withdraw ";
        break;
    case enTransactions::TotalBalances:
        cout << "Total Balances ";
        break;
    }

    cout << "Screen";

    cout << "\n------------------------------------\n";
}

bool FindAClient(vector <sClient>& vClients)
{
    string AccountNumber = ReadClientAccountNumber(true); 
    sClient Client;
    char Answer = 'n';
    if (FindClientBYAccountName(AccountNumber, vClients, Client))
    {
        cout << "\nThe Following are the client datails: \n";
        PrintRecorde(Client);
        return true;
    }
    else
    {
        cout << "\nClient with Account Number(" << AccountNumber << ") is Not Found!\n\n";
        return false;
    }
    return false;
}

void DisplayTransactionsMenue()
{
    cout << "\t" << "[1] Deposit.\n";
    cout << "\t" << "[2] Withdraw.\n";
    cout << "\t" << "[3] Total Balances.\n";
    cout << "\t" << "[4] Main Menue.\n";
    cout << "==================================================\n";
    cout << "Choose what do you want to do? [1 to 4] ?  ";
}

void Depositf(vector <sClient>& vClients)
{
    sClient Client;

    string AccountNumber = ReadClientAccountNumber(true);
    while (!FindClientBYAccountName(AccountNumber, vClients, Client))
    {
        cout << "Client with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber(true);
        cout << "\n";
    }
    PrintRecorde(Client);

    int DepositAmount;

    cout << "Please enter deposit amount? ";
    cin >> DepositAmount;

    char Answer;
    cout << " Are you sure you want perfrom this transaction? y/n ?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Client.AccountBalance += DepositAmount;
        UpDataClientByAccountNumber(vClients, Client);
        SaveCleintsDataToFile(ClientsFileName, vClients);
        cout << "Done successully, the new Balance is (" << Client.AccountBalance << ")\n";

    }
}

void Withdrawf(vector <sClient>& vClients)
{
    sClient Client;

    string AccountNumber = ReadClientAccountNumber(true);
    while (!FindClientBYAccountName(AccountNumber, vClients, Client))
    {
        cout << "Client with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber(true);
        cout << "\n";
    }
    PrintRecorde(Client);

    int WithdrawAmount;
    cout << "Please enter deposit amount? ";
    cin >> WithdrawAmount;

    while (WithdrawAmount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << "\n";
        cout << "Please enter deposit amount? ";
        cin >> WithdrawAmount;
    }
    

    char Answer;
    cout << " Are you sure you want perfrom this transaction? y/n ?";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Client.AccountBalance -= WithdrawAmount;
        UpDataClientByAccountNumber(vClients, Client);
        SaveCleintsDataToFile(ClientsFileName, vClients);
        cout << "\nDone successully, the new Balance is (" << Client.AccountBalance << ")\n\n";

    }
}


void Transactionsf(vector <sClient> & vClients)
{
    enTransactions Transaction;
    short RChois;
    do
    {
        system("cls");
        PrintScreen(enBanKOpearation::Transactions);
        DisplayTransactionsMenue();
        
        cin >> RChois;
         Transaction = enTransactions(RChois);
        system("cls");
        switch (Transaction)
        {
        case enTransactions::Deposit:
            printTransactionScreen(Transaction);
            Depositf(vClients);
            break;
        case enTransactions::Withdraw:
            printTransactionScreen(Transaction);
            Withdrawf(vClients);
            break;
        case enTransactions::TotalBalances:
            PrintTotalBalances(vClients);
            break;
        case enTransactions::MainMenue:
            return;
        default :
                return;
        }
        system("Pause");
    } while (Transaction != enTransactions::MainMenue);
    

}

void ShowUsersListScrean(vector <sUser> veUsers)
{
    cout << "\t\t\t\t\t Users List (" << veUsers.size() << ") User(s).\n";
    cout << "_____________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "User Name" << "| " << left << setw(40) << "Pass Word" << "| " << left << setw(12) << "Permissions ";
    cout << "\n";
    cout << "_____________________________________________________________________________________________\n\n";
    for (sUser & User : veUsers)
    {
        cout << "| " << left << setw(15) << User.UserName << "| " << left << setw(40) << User.PassWord << "| " << left << setw(12) << User.Permissions << endl;
    }
    cout << "_____________________________________________________________________________________________\n\n";
    
}

bool FindUserByUserName(string UserName, vector <sUser> veUsers)
{
    for (sUser& U : veUsers)
    {
        if (U.UserName == UserName)
            return true;
    }
    return false;
}

bool FindUserByUserName(sUser &User, vector <sUser> veUsers)
{
    for (sUser& U : veUsers)
    {
        if (U.UserName == User.UserName)
        {
            User = U;
            return true;
        }
            
    }
    return false;
}



void AddaNewUser(vector <sUser> &veUsers) 
{
    sUser User;
    char Chois = 'Y';
    do
    {
        cout << "Enter User name? ";
        getline(cin >> ws, User.UserName);
        while (FindUserByUserName(User.UserName, veUsers))
        {
            cout << "The User Name is Already exist, Try Enter another User name? ";
            getline(cin >> ws, User.UserName);
        }
        cout << "Enter Pass Word? ";
        getline(cin >> ws, User.PassWord);
        User.Permissions = ReadPermissions();
        veUsers.push_back(User);
        AddDataLineToFile(UsersFileName, ConverUserRecoordeToLine(User));
        cout << "User Added Successfully, do you want to Add More User? Y/N? \n";
        cin >> Chois;
    } while (toupper(Chois) == 'Y');

    }

void SaveUserVecotrToFile(vector <sUser>& veUsers, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (sUser U : veUsers)
        {
                DataLine = ConverUserRecoordeToLine(U);
                MyFile << DataLine << endl;
        }
        MyFile.close();
    }
}

void DeleteUserf(vector <sUser> &veUsers)
{
    sUser User;
    char c = 'Y';
    do
    {
        cout << "Enter User name? ";
        getline(cin >> ws, User.UserName);
        while (User.UserName == "Admin")
        {
            cout << "You Can not Delete This User, Try Enter another User name ";
            getline(cin >> ws, User.UserName);
        }
        while (!FindUserByUserName(User, veUsers))
        {
            cout << "The User Name is Not exist, Try Enter another User name? ";
            getline(cin >> ws, User.UserName);
        }
        PrintRecorde(User);
        char D;
        cout << "\nDo you want to delete the User? N/Y? ";
        cin >> D;
        if (toupper(D) == 'Y')
        {
            veUsers.erase(remove(veUsers.begin(), veUsers.end(), User), veUsers.end());
            SaveUserVecotrToFile(veUsers, UsersFileName);
            cout << "Delete User Successfully,";
        }
        cout << "Do You want to Delete Another User? ";
        cin >> c;
    } while (toupper(c) == 'Y');
    
}

void FindUserf(vector<sUser>& veUsers)
{
    sUser User;
    char D;
    do
    {
        cout << "Enter User name? ";
        getline(cin >> ws, User.UserName);
        while (!FindUserByUserName(User, veUsers))
        {
            cout << "The User Name is Not exist, Try Enter another User name? ";
            getline(cin >> ws, User.UserName);
        }
        PrintRecorde(User);
        cout << "Do you want to Find Another User? Y/N? ";
        cin >> D;
    } while (toupper(D) == 'Y');

}

void UpDateUserf(vector<sUser>& veUsers)
{
    sUser User;
    char c = 'Y';
    do
    {
        cout << "Enter User name? ";
        getline(cin >> ws, User.UserName);
        while (User.UserName == "Admin")
        {
            cout << "You Can not Delete This User, Try Enter another User name ";
            getline(cin >> ws, User.UserName);
        }
        while (!FindUserByUserName(User, veUsers))
        {
            cout << "The User Name is Not exist, Try Enter another User name? ";
            getline(cin >> ws, User.UserName);
        }
        PrintRecorde(User);
        char D;
        cout << "\nDo you want to Update the User? N/Y? ";
        cin >> D;
        if (toupper(D) == 'Y')
        {
            User = UpDateAUserInfo(User);
            for (sUser& U : veUsers)
            {
                if (U.UserName == User.UserName)
                    U = User;
            }
            SaveUserVecotrToFile(veUsers, UsersFileName);
            cout << "Update User Successfully,";
        }
        cout << "Do You want to Update Another User? ";
        cin >> c;
    } while (toupper(c) == 'Y');
}

void ManageUsersf()
{
    enManageUsers Choose;
    short ChoisNum;
    do
    {
        ShowUserMainMenueScreen();
        cin >> ChoisNum;

        Choose = enManageUsers(ChoisNum);
        vector <sUser> veUsers = LoadUsersInfoFile(UsersFileName);
        system("cls");
        switch (Choose)
        {
        case enManageUsers::ShowUsersLiset:
            PrintScreen(Choose);
            ShowUsersListScrean(veUsers);
            break;
        case enManageUsers::AddNewUser:
            PrintScreen(Choose);
            AddaNewUser(veUsers);
            break;
        case enManageUsers::DeleteUser:
            PrintScreen(Choose);
            DeleteUserf(veUsers);
            break;
        case enManageUsers::UpdateUserInfo:
            PrintScreen(Choose);
            UpDateUserf(veUsers);
            break;
        case enManageUsers::FindUser:
            PrintScreen(Choose);
            FindUserf(veUsers);
            break;
        case enManageUsers::MainMenueUser:
            return;
        default: 
            return;

        }
        system("Pause");

    } while (true);

}

void Bank(sUser User)
{
    enBanKOpearation choose;
    short RChois;
    do
    {
        ShowMainMenueScreen();

        cout << "Choose what do you want to do? [1 to 8]? ";

        cin >> RChois;
        choose = enBanKOpearation(RChois);
        if (!GetPermission(User.Permissions, RChois) && RChois < 8)
        {
            system("cls");
            cout << "-------------------------------------\n"
                << "Access Denied,\n"
                << "You dont Have Permission to do this,\n"
                << "Plese conact Your admin.\n"
                << "-------------------------------------\n";
            system("Pause");
            continue;
        }

        choose = enBanKOpearation(RChois);
        vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
        system("cls");
        switch (choose)
        {
        case enBanKOpearation::ShowClientList:
            PrintClientsData(vClient);
            break;
        case enBanKOpearation::AddNewClient:
            PrintScreen(choose);
            AddaNewClient(vClient);
            break;
        case enBanKOpearation::DeleteClient:
            PrintScreen(choose);
            DeleteClientByAccountNumber(vClient);
            break;
        case enBanKOpearation::UpdateClientInfo:
            PrintScreen(choose);
            UpDataClientToFile(vClient);
            break;
        case enBanKOpearation::FindClient:
            PrintScreen(choose);
            FindAClient(vClient);
            break;
        case enBanKOpearation::Transactions:
            Transactionsf(vClient);
            break;
        case enBanKOpearation::ManageUsers:
            ManageUsersf();
            break;
        case enBanKOpearation::Logout:
            return;
        default:
            return;
        }
        if(choose != enBanKOpearation::Transactions)
        system("Pause>0");
    } while (choose != enBanKOpearation::Logout);


}


void Login()
{
    
    do
    {
        system("cls");
        LoginScreen();
        sUser User = ReadUserInfo();
        vector <sUser> veUsers = LoadUsersInfoFile(UsersFileName);
        while (!FindUserByUserNameAndPassWord(User, veUsers))
        {
            system("cls");
            LoginScreen();
            cout << "Invalid User Name/Password\n";
            User = ReadUserInfo();
        }
        Bank(User);
    } while (true);
    
}

int main()
{
    Login();
}