#include <iostream>
#include <string>
#include <ctime> // For date and time handling
using namespace std;

// Node structure for Linked List
struct BookNode {
    int bookId;
    string title;
    string author;
    string status;
    time_t issueDate; // Issue date
    time_t returnDate; // Last return date
    BookNode* next;

    BookNode(int id, string t, string a, string s) : bookId(id), title(t), author(a), status(s), issueDate(0), returnDate(0), next(nullptr) {}
};

// Library class using Linked List
class Library {
private:
    BookNode* head; // Head of the linked list

    // Helper function to calculate late fee
    double calculateLateFee(time_t returnDate) {
        time_t now = time(0); // Current time
        double diff = difftime(now, returnDate) / (60 * 60 * 24); // Difference in days
        if (diff > 0) {
            return diff * 10; // Rs. 10 per day late fee
        }
        return 0; // No late fee
    }

public:
    Library() : head(nullptr) {}

    // Add a book to the library
    void addBook(int bookId, string title, string author) {
        BookNode* newNode = new BookNode(bookId, title, author, "Available");
        if (!head) {
            head = newNode;
        } else {
            BookNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Book '" << title << "' (ID: " << bookId << ") added successfully!" << endl;
    }

    // Delete a book from the library
    void deleteBook(int bookId) {
        if (!head) {
            cout << "Library is empty!" << endl;
            return;
        }

        BookNode* temp = head;
        BookNode* prev = nullptr;

        // If the book to be deleted is the head
        if (temp && temp->bookId == bookId) {
            head = temp->next;
            delete temp;
            cout << "Book with ID " << bookId << " deleted successfully!" << endl;
            return;
        }

        // Search for the book to be deleted
        while (temp && temp->bookId != bookId) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Book with ID " << bookId << " not found!" << endl;
            return;
        }

        // Unlink the node from the linked list
        prev->next = temp->next;
        delete temp;
        cout << "Book with ID " << bookId << " deleted successfully!" << endl;
    }

    // Issue a book to a student
    void issueBook(int bookId, string studentName) {
        BookNode* book = findBook(bookId);
        if (!book) {
            cout << "Book ID not found!" << endl;
        } else if (book->status == "Issued") {
            cout << "Book is already issued!" << endl;
        } else {
            book->status = "Issued";
            book->issueDate = time(0); // Set issue date to current time
            book->returnDate = book->issueDate + (7 * 24 * 60 * 60); // Set return date to 7 days later
            cout << "Book '" << book->title << "' (ID: " << book->bookId << ") issued to " << studentName << "." << endl;
            cout << "Issue Date: " << ctime(&book->issueDate);
            cout << "Last Return Date: " << ctime(&book->returnDate);
        }
    }

    // Return a book to the library
    void returnBook(int bookId) {
        BookNode* book = findBook(bookId);
        if (!book) {
            cout << "Book ID not found!" << endl;
        } else if (book->status == "Available") {
            cout << "Book is not issued!" << endl;
        } else {
            book->status = "Available";
            double lateFee = calculateLateFee(book->returnDate);
            if (lateFee > 0) {
                cout << "Book '" << book->title << "' (ID: " << book->bookId << ") returned late. Late fee: Rs. " << lateFee << endl;
            } else {
                cout << "Book '" << book->title << "' (ID: " << book->bookId << ") returned on time. No late fee." << endl;
            }
            book->issueDate = 0;
            book->returnDate = 0;
        }
    }

    // Update book details
    void updateBook(int bookId) {
        BookNode* book = findBook(bookId);
        if (!book) {
            cout << "Book ID not found!" << endl;
            return;
        }

        cout << "Current Details of Book ID " << bookId << ":" << endl;
        cout << "Title: " << book->title << ", Author: " << book->author << endl;

        int choice;
        cout << "\nWhat do you want to update?" << endl;
        cout << "1. Title" << endl;
        cout << "2. Author" << endl;
        cout << "3. Both Title and Author" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character

        switch (choice) {
            case 1:
                cout << "Enter new Title: ";
                getline(cin, book->title);
                cout << "Title updated successfully!" << endl;
                break;

            case 2:
                cout << "Enter new Author: ";
                getline(cin, book->author);
                cout << "Author updated successfully!" << endl;
                break;

            case 3:
                cout << "Enter new Title: ";
                getline(cin, book->title);
                cout << "Enter new Author: ";
                getline(cin, book->author);
                cout << "Title and Author updated successfully!" << endl;
                break;

            default:
                cout << "Invalid choice! No updates made." << endl;
        }
    }

    // Display all books in the library
    void displayBooks() {
        if (!head) {
            cout << "No books in the library!" << endl;
        } else {
            cout << "\nLibrary Books:" << endl;
            BookNode* current = head;
            while (current) {
                cout << "ID: " << current->bookId << ", Title: " << current->title
                     << ", Author: " << current->author << ", Status: " << current->status << endl;
                if (current->status == "Issued") {
                    cout << "Issue Date: " << ctime(&current->issueDate);
                    cout << "Last Return Date: " << ctime(&current->returnDate);
                }
                current = current->next;
            }
        }
    }

    // Helper function to find a book by ID
    BookNode* findBook(int bookId) {
        BookNode* current = head;
        while (current) {
            if (current->bookId == bookId) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
};

int main() {
    Library library;
    int choice, bookId;
    string title, author, studentName;

    // Pre-add some books to the library
    library.addBook(101, "Python Programming", "John Doe");
    library.addBook(102, "C++ for Beginners", "Jane Smith");
    library.addBook(103, "Data Structures and Algorithms", "Robert Johnson");
    library.addBook(104, "Introduction to AI", "Emily Brown");

    while (true) {
        cout << "\n===== Library Management System =====" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Delete a Book" << endl;
        cout << "3. Issue a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. Display All Books" << endl;
        cout << "6. Update Book Details" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> bookId;
                cin.ignore(); // To ignore the newline character
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                library.addBook(bookId, title, author);
                break;

            case 2:
                cout << "Enter Book ID to delete: ";
                cin >> bookId;
                library.deleteBook(bookId);
                break;

            case 3:
                cout << "Enter Book ID: ";
                cin >> bookId;
                cin.ignore(); // To ignore the newline character
                cout << "Enter Student Name: ";
                getline(cin, studentName);
                library.issueBook(bookId, studentName);
                break;

            case 4:
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.returnBook(bookId);
                break;

            case 5:
                library.displayBooks();
                break;

            case 6:
                cout << "Enter Book ID to update: ";
                cin >> bookId;
                library.updateBook(bookId);
                break;

            case 7:
                cout << "Exiting the system. Thank you!" << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
