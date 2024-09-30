#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

const string DATA_FILE = "library_data.txt";

// Book class definition
class Book {
public:
    string isbn;
    string title;
    string author;
    string year;

    Book() {}
    Book(string isbn, string title, string author, string year)
        : isbn(isbn), title(title), author(author), year(year) {}

    // Convert book to string for saving in file
    string to_string() {
        return isbn + "," + title + "," + author + "," + year;
    }

    // Display the book details
    void display() {
        cout << "ISBN: " << isbn << ", Title: " << title << ", Author: " << author << ", Year: " << year << endl;
    }
};

// Global structures to store books
unordered_map<string, Book> books_by_isbn;
vector<Book> books_list; // Sorted list for binary search

// Function declarations
void load_data();
void save_data();
int binary_search(string title);
void add_book();
void search_by_isbn();
void search_by_title();
void view_books();
void modify_book();
void delete_book();

// Save data to the file
void save_data() {
    ofstream file(DATA_FILE);
    for (Book& book : books_list) {
        file << book.to_string() << endl;
    }
    file.close();
    cout << "Data saved successfully!" << endl;
}

// Load data from the file
void load_data() {
    ifstream file(DATA_FILE);
    if (!file.is_open()) {
        cout << "No existing data found. Starting fresh!" << endl;
        return;
    }

    books_list.clear();
    books_by_isbn.clear();
    string line, isbn, title, author, year;
    while (getline(file, line)) {
        size_t pos1 = line.find(",");
        size_t pos2 = line.find(",", pos1 + 1);
        size_t pos3 = line.find(",", pos2 + 1);

        isbn = line.substr(0, pos1);
        title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        year = line.substr(pos3 + 1);

        Book book(isbn, title, author, year);
        books_list.push_back(book);
        books_by_isbn[isbn] = book;
    }
    file.close();
    cout << "Data loaded successfully!" << endl;
}

// Binary search by title
int binary_search(string title) {
    int low = 0, high = books_list.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (books_list[mid].title == title) {
            return mid;
        }
        else if (books_list[mid].title < title) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

// Add a new book
void add_book() {
    string isbn, title, author, year;
    cout << "Enter ISBN: ";
    cin >> isbn;
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Publication Year: ";
    cin >> year;

    Book new_book(isbn, title, author, year);
    books_list.push_back(new_book);
    books_by_isbn[isbn] = new_book;

    sort(books_list.begin(), books_list.end(), [](Book a, Book b) {
        return a.title < b.title;
    });

    save_data();
    cout << "Book added successfully!" << endl;
}

// Search for a book by ISBN
void search_by_isbn() {
    string isbn;
    cout << "Enter ISBN to search: ";
    cin >> isbn;
    if (books_by_isbn.find(isbn) != books_by_isbn.end()) {
        books_by_isbn[isbn].display();
    }
    else {
        cout << "Book not found!" << endl;
    }
}

// Search for a book by title using binary search
void search_by_title() {
    string title;
    cout << "Enter Title to search: ";
    cin.ignore();
    getline(cin, title);

    int index = binary_search(title);
    if (index != -1) {
        books_list[index].display();
    }
    else {
        cout << "Book not found!" << endl;
    }
}

// View all books
void view_books() {
    if (books_list.empty()) {
        cout << "No books available!" << endl;
        return;
    }
    for (Book& book : books_list) {
        book.display();
    }
}

// Modify a book by ISBN
void modify_book() {
    string isbn;
    cout << "Enter ISBN of the book to modify: ";
    cin >> isbn;

    if (books_by_isbn.find(isbn) != books_by_isbn.end()) {
        Book& book = books_by_isbn[isbn];
        string new_title, new_author, new_year;
        cout << "Enter new Title (current: " << book.title << "): ";
        cin.ignore();
        getline(cin, new_title);
        cout << "Enter new Author (current: " << book.author << "): ";
        getline(cin, new_author);
        cout << "Enter new Publication Year (current: " << book.year << "): ";
        cin >> new_year;

        book.title = new_title;
        book.author = new_author;
        book.year = new_year;

        sort(books_list.begin(), books_list.end(), [](Book a, Book b) {
            return a.title < b.title;
        });

        save_data();
        cout << "Book modified successfully!" << endl;
    }
    else {
        cout << "Book not found!" << endl;
    }
}

// Delete a book by ISBN
void delete_book() {
    string isbn;
    cout << "Enter ISBN of the book to delete: ";
    cin >> isbn;

    if (books_by_isbn.find(isbn) != books_by_isbn.end()) {
        books_by_isbn.erase(isbn);
        books_list.erase(remove_if(books_list.begin(), books_list.end(), [&](Book& b) {
            return b.isbn == isbn;
        }), books_list.end());

        save_data();
        cout << "Book deleted successfully!" << endl;
    }
    else {
        cout << "Book not found!" << endl;
    }
}

// Main function for the menu-driven system
int main() {
    load_data();

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ISBN\n";
        cout << "3. Search Book by Title\n";
        cout << "4. View All Books\n";
        cout << "5. Modify Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            add_book();
            break;
        case 2:
            search_by_isbn();
            break;
        case 3:
            search_by_title();
            break;
        case 4:
            view_books();
            break;
        case 5:
            modify_book();
            break;
        case 6:
            delete_book();
            break;
        case 7:
            exit(0);
        default:
            cout << "Invalid option. Try again!" << endl;
        }
    }

    return 0;
}

