# Library Management System

A simple Library Management System that allows users to manage books, including adding, searching, viewing, modifying, and deleting books. This project includes both a Command-Line Interface (CLI) and a Graphical User Interface (GUI) version, allowing flexibility in how users interact with the application.

## Features

- **Add Books**: Users can add new books to the library.
- **Search by ISBN**: Quickly find books using their ISBN.
- **View All Books**: Display a list of all books in the library.
- **Modify Books**: Update the details of existing books.
- **Delete Books**: Remove books from the library.

## Prerequisites

### For CLI Version

- **Python**: Ensure Python is installed on your system (Python 3.x recommended).
- **Required Libraries**: Install the necessary Python libraries using pip:

  ```bash
  pip install json
  ```

### For GUI Version

- **C++ Compiler**: Ensure you have `g++` installed on your system.
- **FLTK Library**: You need to have the FLTK library installed. Instructions for installation can vary by OS:

  - **For Ubuntu/Debian**:

    ```bash
    sudo apt-get install libfltk1.3-dev
    ```

  - **For macOS** (using Homebrew):

    ```bash
    brew install fltk
    ```

## Running the Application

### CLI Version

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. Run the application:

   ```bash
   python main.py
   ```

3. Follow the on-screen prompts to manage your library.

### GUI Version

1. Clone the repository:

   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. Compile the GUI application:

   ```bash
   g++ main.cpp -o library_gui -lfltk
   ```

3. Run the GUI application:

   ```bash
   ./library_gui
   ```

4. Use the GUI to manage your library with a visual interface.

## Contributing

If you'd like to contribute to the project, please fork the repository and submit a pull request with your changes. Contributions are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- [FLTK](https://www.fltk.org/) - A cross-platform C++ GUI toolkit.
- [Python](https://www.python.org/) - Programming language used for the CLI version.
