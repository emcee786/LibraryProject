#include <iostream>
#include <vector>
#include <set>
using std::string;
using std::vector;
using std::cin;
using std::cout;

using namespace std;

struct user; //user strunct initialisation

// Struct for Library books
struct book{
    int isbn, quantity;
    string title;
    vector<user> borrowedBy;

    book(){
        isbn = 100;
        quantity = 0;
        title = "untitled";
    }

};

struct user {
    int id;
    string name;
    vector<book> borrowed;
    vector<book> returned;

    user(){
        name = "untitled";
    }
};

vector<book> vtr;  // Global Vector for storing all books
vector<user> users; // Global Vector for storing all books
int currentUserID = 0;

// Adds new user to system
user addUser() {
    user newUser;
    newUser.id = currentUserID;
    cout << "New user ID is: " << newUser.id <<"\n";
    cin.ignore();
    ++currentUserID;
    cout << "Please enter a new user name: \n";
    getline(cin, newUser.name);
    
    cout << "\n User added. \n";
    users.push_back(newUser);
    return newUser;
}

// Prints all users i database
void printUsers(){ 
    if(users.empty())
        cout << "\nSorry, no users exist in the database.";
    else
        for (int count = 0; count < users.size(); count++)                           //For Loop to Display All Products
            {
                cout << "\nID: " << users[count].id << "\nName: " << users[count].name << "\n";
            }
        cout << endl;
}

//Adds new book struct to vector
book addBook() { 
        book newBook;
        cin.ignore();
        cout << "Please enter the book title: \n";
        getline(cin, newBook.title);
        cout << "Please enter the ISBN for the book: \n";
        cin >> newBook.isbn;
        cout << "Please enter the quantity of the book in stock: \n";
        cin >> newBook.quantity;
        
        vtr.push_back(newBook);
        return newBook;
}

// Prints all books on hand
void printBooks(){ 
    if(vtr.empty())
        cout << "\nSorry, no books exist in the database.";
    else
        for (int count = 0; count < vtr.size(); count++)                           //For Loop to Display All Products
            {
                cout << "\nISBN: " << vtr[count].isbn << "\nTitle: " << vtr[count].title << "\nQuantity in stock: " << vtr[count].quantity << "\n";
            }
        cout << endl;
}

// To be used when borrowing or returning a book;
book searchISBN(){
    book toBorrow;
    int searchISBN;
    bool found = false;
    cout << "Please enter the book ISBN: \n";
    cin >> searchISBN;

    for (int count = 0; count < vtr.size(); count++) {
        int currentISBN = vtr[count].isbn;
        if (currentISBN ==  searchISBN) { 
            found = true;
            toBorrow.isbn = vtr[count].isbn; 
            toBorrow.title = vtr[count].title;
            toBorrow.quantity = vtr[count].quantity;

            cout << "Match: " << vtr[count].isbn << " " << vtr[count].title << "\n";
        }
    } 
        if (found == false) {
        cout << "No matches found, try again.\n";
    }
    return toBorrow;
}

user findUser(){
    user borrower;
    int userSearchID;
    bool found = false;
    cout << "Please enter the user's ID number: \n";
    cin >> userSearchID;

    for (int count = 0; count < users.size(); count++) {
        int currentUserID = users[count].id;
        if (currentUserID ==  userSearchID) { 
            found = true;
            borrower = users[count];
            cout << "Match: " << users[count].id << " " << users[count].name << "\n";
        }
    } 
        if (found == false) {
        cout << "No matches found, try again.\n";
    }
    return borrower;
}

//converts to lower case for search comparison
string toLowerCase(string data){
    string lowerData = data;
    for (int i = 0; i < lowerData.length(); i++) {
        lowerData[i] = tolower(lowerData[i]);
        //cout << "Lower case: " << lowerData;
    }
    return lowerData;
}



// Searches book by title prefix, returns all that match
book searchBook() {
    book foundBook;
    string searchPrefix;
    bool noMatches = true;
    int stringLength;
    cout << "Please enter the first three letters of the book you're searching for: \n"; //case sensitive - would need to add a setlower function 
    cin >> searchPrefix;
    toLowerCase(searchPrefix);
    stringLength = searchPrefix.length();
    

    for (int count = 0; count < vtr.size(); count++) {
        string currentTitle = toLowerCase(vtr[count].title);
        if (currentTitle.length() >= stringLength) { //Checks that the title is at least as long as the prefix
            if (searchPrefix == currentTitle.substr(0, stringLength)){
                noMatches = false;
                cout << "Book found: " << vtr[count].isbn << " " << vtr[count].title << "\n";
                foundBook = vtr[count];
            }
        }
    } 
    if (noMatches) {
        cout << "Not available, try again.\n";
    }

    return foundBook;
}

void listBorrowerHistory(){
    book checkedBook = searchBook();
    cout << checkedBook.isbn << " " << checkedBook.title << " has been borrowed by: \n";
    for (int i = 0; i < checkedBook.borrowedBy.size(); i++){
        cout << checkedBook.borrowedBy[i].name << "\n";
    }
}

// Takes titles for vector into an array and sorts alphabetically
void alphaBookSort(){
    int size;
    string alphaTitles[size], temp;
    size = vtr.size();
    for (int count = 0; count < size; count++) {
        alphaTitles[count] = vtr[count].title;
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (alphaTitles[i] > alphaTitles[j]){
                temp = alphaTitles[i];
                alphaTitles[i] = alphaTitles[j];
                alphaTitles[j] = temp;
            }
        }
    }  cout << "Titles in alphatical order: \n";

    for (int i = 0; i < size; ++i) {
            cout << i+1 << ". " << alphaTitles[i] << "\n";
        }
}

// Sorts book in order of ISBN
void ISBNBookSort(){
    vector <book> copy = vtr;
    book temp;
    
    for (int i = 0; i < copy.size(); ++i) {                         //For Loop to Display All Products
        for (int j = i + 1; j < copy.size(); ++j) {
            if (copy[i].isbn > copy[j].isbn) {
                temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }    cout << "Titles in ISBN order: \n";

    for (int i = 0; i < copy.size(); ++i) {
            cout << i+1 << ". " <<copy[i].isbn << ": " << copy[i].title << "\n";
        }
}

// Adds book to the user's book vector, decreases quantity in global vector
user borrowBook(user borrower){
    book available = searchISBN();
    char confirm;

    if (available.title != "untitled" && available.quantity > 0){
        cout << "Would you like to borrow this book? Y/N \n";
        cin >> confirm;
        if (confirm == 'Y' || 'y') {
            available.quantity = 1;
            borrower.borrowed.push_back(available);
            users[borrower.id].borrowed = borrower.borrowed;         
            for (int i = 0; i < borrower.borrowed.size(); ++i){
            cout << borrower.name << " has borrowed: ";
            cout << "\nISBN: " << borrower.borrowed[i].isbn << " Title: " << borrower.borrowed[i].title << " Quantity: " << borrower.borrowed[i].quantity << "\n";
            // TEST CODE: cout << users[borrower.id].borrowed[i].isbn << " " << users[borrower.id].borrowed[i].title << "  DID IT WORK";
            }

            for (int i = 0; i < vtr.size(); ++i){
                if (vtr[i].isbn == available.isbn) {
                    vtr[i].quantity -= 1;
                    vtr[i].borrowedBy.push_back(borrower);
                }
            }   
        }
    }
    else {
        cout << "** This book is currently out of stock **\n";
    }
    
    return borrower;
}

void returnBook(){
    int inputID;
    cout << "Please enter the user's ID\n";
    cin >> inputID;
    int returnISBN;
    book returnedBook;      
    cout << "Books on loan for " << users[inputID].name << "\n";
    for (int i = 0; i < users[inputID].borrowed.size(); ++i) {
        cout << "ISBN: " << users[inputID].borrowed[i].isbn << " Title: " << users[inputID].borrowed[i].title << " Quantity: " << users[inputID].borrowed[i].quantity;
        }
        
        cout << "\nPlease enter the ISBN of the book you would like to return: \n";
        cin >> returnISBN;
        // If quantity is zero, book has already been returned
        for (int i = 0; i < users[inputID].borrowed.size(); ++i) {  
            if (returnISBN == users[inputID].borrowed[i].isbn && users[inputID].borrowed[i].quantity == 0){
            cout << "You have already returned this book\n";
            }
            else if (returnISBN == users[inputID].borrowed[i].isbn && users[inputID].borrowed[i].quantity > 0){
                returnedBook = users[inputID].borrowed[i];
                users[inputID].borrowed[i].quantity -= 1;
                users[inputID].returned.push_back(returnedBook);
                cout << users[inputID].borrowed[i].isbn << " - " << users[inputID].borrowed[i].title << " has been returned\n";
                    for (int count = 0; count < vtr.size(); count++) {
                        if (returnISBN == vtr[count].isbn) {
                            vtr[count].quantity += 1;
                            cout << vtr[count].title << " has now been returned. Thank you.\n";                        }
                    }
                }    
            }

        }
    
//} 


void printMenu(){
    bool menuOpen = true;
    int selection = 0;

    cout <<"        *** MENU ***\n";
    cout <<"    1. Add book\n"; //Done
    cout <<"    2. Search books by prefix\n"; //Done
    cout <<"    3. Print who borrowed the book by name\n";
    cout <<"    4. Print Library in ISBN numeric order\n";
    cout <<"    5. Print Library in alphabetical order\n";
    cout <<"    6. Add user\n";
    cout <<"    7. User borrow book\n";
    cout <<"    8. User return book\n";
    cout <<"    9. Print users\n";
    cout <<"    10. Print books\n";
    cout <<"    11. Exit\n";
        
    while (menuOpen) {
        cout <<"    \nEnter your selection (1-11):";
        cin >> selection;

    
        switch (selection) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                listBorrowerHistory();
                break;
            case 4:
                ISBNBookSort();
                break;
            case 5:
                alphaBookSort();
                break;
            case 6:
                addUser();
                break;
            case 7: {
                user borrower = findUser();
                borrowBook(borrower);
                break;
                }
            case 8: 
                returnBook();
                break; 
            case 9:
                printUsers();
                break;
            case 10:
                printBooks();
                break;
            case 11:
                cout << "Thank you! Good bye \n\n";
            default: 
                cout << "Library error";
        }
    }
}

int main(){
    printMenu();
      
    return 0;
}