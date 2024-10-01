#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;

const string DATA_FILE = "library_data.txt";

class Book {
public:
    string isbn;
    string title;
    string author;
    string year;

    Book() {}
    Book(string isbn, string title, string author, string year)
        : isbn(isbn), title(title), author(author), year(year) {}

    string to_string() const {  // This function must be const
        return "ISBN: " + isbn + ", Title: " + title + ", Author: " + author + ", Year: " + year;
    }
};

// Global data structures
unordered_map<string, Book> books_by_isbn;
vector<Book> books_list;

// Function to load data from the file
void load_data() {
    ifstream file(DATA_FILE);
    if (!file.is_open()) {
        cout << "No existing data found. Starting fresh!" << endl;
        return;
    }

    books_list.clear();
    books_by_isbn.clear();
    string isbn, title, author, year;
    while (getline(file, isbn, ',') && getline(file, title, ',') && getline(file, author, ',') && getline(file, year)) {
        Book book(isbn, title, author, year);
        books_list.push_back(book);
        books_by_isbn[isbn] = book;
    }
    file.close();
}

// Function to save data to the file
void save_data() {
    ofstream file(DATA_FILE);
    for (const auto& book : books_list) {
        file << book.isbn << "," << book.title << "," << book.author << "," << book.year << endl;
    }
    file.close();
}

// Function to add a new book
void add_book(string isbn, string title, string author, string year) {
    Book new_book(isbn, title, author, year);
    books_list.push_back(new_book);
    books_by_isbn[isbn] = new_book;

    sort(books_list.begin(), books_list.end(), [](Book a, Book b) {
        return a.title < b.title;
    });

    save_data();
}

// Function to search for a book by ISBN
string search_by_isbn(string isbn) {
    if (books_by_isbn.find(isbn) != books_by_isbn.end()) {
        return books_by_isbn[isbn].to_string();
    }
    return "Book not found!";
}

// Function to view all books
string view_books() {
    if (books_list.empty()) {
        return "No books available!";
    }

    string output;
    for (const auto& book : books_list) {
        output += book.to_string() + "\n";
    }
    return output;
}

// GUI Components
Fl_Input* isbn_input;
Fl_Input* title_input;
Fl_Input* author_input;
Fl_Input* year_input;
Fl_Multiline_Output* output_display;

// Callback for adding a book
void add_book_cb(Fl_Widget*, void*) {
    string isbn = isbn_input->value();
    string title = title_input->value();
    string author = author_input->value();
    string year = year_input->value();

    if (isbn.empty() || title.empty() || author.empty() || year.empty()) {
        output_display->value("All fields are required!");
        return;
    }

    add_book(isbn, title, author, year);
    output_display->value(("Book added:\n" + title).c_str());

    // Clear inputs after adding
    isbn_input->value("");
    title_input->value("");
    author_input->value("");
    year_input->value("");
}

// Callback for viewing all books
void view_books_cb(Fl_Widget*, void*) {
    string all_books = view_books();
    output_display->value(all_books.c_str());
}

// Main function
int main(int argc, char** argv) {
    load_data();  // Load existing data on start

    Fl_Window* window = new Fl_Window(400, 400, "Library Management System");

    isbn_input = new Fl_Input(100, 30, 200, 30, "ISBN:");
    title_input = new Fl_Input(100, 70, 200, 30, "Title:");
    author_input = new Fl_Input(100, 110, 200, 30, "Author:");
    year_input = new Fl_Input(100, 150, 200, 30, "Year:");

    Fl_Button* add_button = new Fl_Button(100, 200, 100, 30, "Add Book");
    add_button->callback(add_book_cb);

    Fl_Button* view_button = new Fl_Button(220, 200, 100, 30, "View Books");
    view_button->callback(view_books_cb);

    output_display = new Fl_Multiline_Output(20, 250, 360, 100);
    output_display->wrap(1);

    window->end();
    window->show(argc, argv);
    return Fl::run();
}

