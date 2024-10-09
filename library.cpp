#include <iostream>
#include <string>
using namespace std;

// Struct to represent each book in the library
struct Book {
    int id;
    string title;
    string author;
    bool isBorrowed;
    Book* left;
    Book* right;
};

// Struct to represent a user (using a linked list)
struct User {
    int userId;
    string name;
    int borrowedBookId;
    User* next;
};

// Function to create a new book node
Book* createBook(int id, string title, string author) {
    Book* newBook = new Book();
    newBook->id = id;
    newBook->title = title;
    newBook->author = author;
    newBook->isBorrowed = false;
    newBook->left = nullptr;
    newBook->right = nullptr;
    return newBook;
}

// Function to insert a book into the binary search tree (BST)
Book* insertBook(Book* root, int id, string title, string author) {
    if (root == nullptr) {
        return createBook(id, title, author);
    }
    if (title < root->title) {
        root->left = insertBook(root->left, id, title, author);
    } else {
        root->right = insertBook(root->right, id, title, author);
    }
    return root;
}

// In-order traversal of BST to display the catalog
void displayBooks(Book* root) {
    if (root == nullptr) return;
    displayBooks(root->left);
    cout << "Book ID: " << root->id << ", Title: " << root->title << ", Author: " << root->author
         << ", Status: " << (root->isBorrowed ? "Borrowed" : "Available") << endl;
    displayBooks(root->right);
}

// Function to search a book by title
Book* searchBookByTitle(Book* root, string title) {
    if (root == nullptr || root->title == title) {
        return root;
    }
    if (title < root->title) {
        return searchBookByTitle(root->left, title);
    }
    return searchBookByTitle(root->right, title);
}

// Function to search a book by its ID (new function)
Book* searchBookByID(Book* root, int id) {
    if (root == nullptr || root->id == id) {
        return root;
    }
    if (id < root->id) {
        return searchBookByID(root->left, id);
    }
    return searchBookByID(root->right, id);
}

// Function to add a new user to the linked list
User* addUser(User* head, int userId, string name) {
    User* newUser = new User();
    newUser->userId = userId;
    newUser->name = name;
    newUser->borrowedBookId = -1;
    newUser->next = head;
    return newUser;
}

// Function to find a user by ID
User* findUser(User* head, int userId) {
    User* current = head;
    while (current != nullptr && current->userId != userId) {
        current = current->next;
    }
    return current;
}

// Function for borrowing a book
void borrowBook(Book* root, User* head, int userId, string title) {
    Book* book = searchBookByTitle(root, title);
    if (book == nullptr) {
        cout << "Book not found in the catalog!" << endl;
        return;
    }
    if (book->isBorrowed) {
        cout << "Book is already borrowed by someone else!" << endl;
        return;
    }
    User* user = findUser(head, userId);
    if (user == nullptr) {
        cout << "User not found!" << endl;
        return;
    }
    book->isBorrowed = true;
    user->borrowedBookId = book->id;
    cout << "Book borrowed successfully by " << user->name << "!" << endl;
}

// Function for returning a borrowed book (updated)
void returnBook(Book* root, User* head, int userId) {
    User* user = findUser(head, userId);
    if (user == nullptr || user->borrowedBookId == -1) {
        cout << "No borrowed book found for this user!" << endl;
        return;
    }

    Book* book = searchBookByID(root, user->borrowedBookId); // Use ID-based search here
    if (book == nullptr) {
        cout << "Book not found!" << endl;
        return;
    }

    book->isBorrowed = false;
    user->borrowedBookId = -1;
    cout << "Book returned successfully!" << endl;
}

// Main function with a simple menu-driven interface
int main() {
    Book* library = nullptr; // Root of the BST for books
    User* users = nullptr;   // Head of the linked list for users

    // Pre-load some users
    users = addUser(users, 101, "Alice");
    users = addUser(users, 102, "Bob");
    users = addUser(users, 103, "Charlie");

    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add a new book\n";
        cout << "2. Display all books\n";
        cout << "3. Search for a book by title\n";
        cout << "4. Borrow a book\n";
        cout << "5. Return a book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore(); // Ignore newline character
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                library = insertBook(library, id, title, author);
                cout << "Book added successfully!\n";
                break;
            }
            case 2:
                cout << "\n--- Displaying All Books ---\n";
                displayBooks(library);
                break;
            case 3: {
                string title;
                cin.ignore(); // Ignore newline character
                cout << "Enter book title to search: ";
                getline(cin, title);
                Book* book = searchBookByTitle(library, title);
                if (book != nullptr) {
                    cout << "Book found: ID: " << book->id << ", Author: " << book->author
                         << ", Status: " << (book->isBorrowed ? "Borrowed" : "Available") << endl;
                } else {
                    cout << "Book not found!" << endl;
                }
                break;
            }
            case 4: {
                int userId;
                string title;
                cout << "Enter your user ID: ";
                cin >> userId;
                cin.ignore(); // Ignore newline character
                cout << "Enter book title to borrow: ";
                getline(cin, title);
                borrowBook(library, users, userId, title);
                break;
            }
            case 5: {
                int userId;
                cout << "Enter your user ID: ";
                cin >> userId;
                returnBook(library, users, userId);
                break;
            }
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
