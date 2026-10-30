/*
================================================================================
Department of AI-DS, DYPCOE, Akurdi, Pune
Fundamentals of Data Structures Laboratory (FDS Lab)
Practical No. 06: Online Library Management System (C++)

Problem Statement:
Develop a backend system for an online library maintaining a database of books,
where each book has attributes:
- Book ID
- Title
- Author
- Publication Year
- Category

Implement:
Searching:
1. Sentinel Search by Book ID
2. Sentinel Search by Title
3. Indexed Sequential Search by Book ID
4. Indexed Sequential Search by Title

Sorting:
1. Insertion Sort by Title
2. Insertion Sort by Publication Year
3. Insertion Sort by Author
4. Shell Sort by Title
5. Shell Sort by Publication Year
6. Shell Sort by Author

Additional Operations:
- Add a book
- Display all books
- Display total book count

Requirements:
- All searching and sorting algorithms implemented manually without built-in functions.
- Preserve complete book records during all sorting passes.
- Proper handling of invalid inputs and empty library conditions.
================================================================================
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cctype>

namespace PR6 {

const int MAX_BOOKS = 100;
const int BLOCK_SIZE = 3; // Block size for Indexed Sequential Search

// Book Structure
struct Book {
    int id;
    std::string title;
    std::string author;
    int year;
    std::string category;
};

// Index entry for Indexed Sequential Search by Book ID
struct IdIndexEntry {
    int key;        // Highest Book ID in this block
    int startIndex; // Starting index in the array
    int endIndex;   // Ending index in the array
};

// Index entry for Indexed Sequential Search by Title
struct TitleIndexEntry {
    std::string key; // Highest Title in this block
    int startIndex;  // Starting index in the array
    int endIndex;    // Ending index in the array
};

// Utility to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Convert string to lower case for case-insensitive comparison
std::string toLowerString(const std::string &str) {
    std::string lower = str;
    for (size_t i = 0; i < lower.length(); i++) {
        lower[i] = std::tolower(static_cast<unsigned char>(lower[i]));
    }
    return lower;
}

// Case-insensitive string comparison:
// Returns <0 if a < b, 0 if a == b, >0 if a > b
int compareCaseInsensitive(const std::string &a, const std::string &b) {
    std::string la = toLowerString(a);
    std::string lb = toLowerString(b);
    if (la < lb) return -1;
    if (la > lb) return 1;
    return 0;
}

// Copy array of books to protect original library order
void copyBookArray(const Book src[], Book dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// Display a single book's details
void printBookDetails(const Book &b) {
    std::cout << "  --------------------------------------------------\n";
    std::cout << "  Book ID          : " << b.id << "\n";
    std::cout << "  Title            : " << b.title << "\n";
    std::cout << "  Author           : " << b.author << "\n";
    std::cout << "  Publication Year : " << b.year << "\n";
    std::cout << "  Category         : " << b.category << "\n";
    std::cout << "  --------------------------------------------------\n";
}

// Display all books in tabular format
void displayAllBooks(const Book books[], int n) {
    if (n == 0) {
        std::cout << "\n[Info] The library is currently empty. No books to display.\n";
        return;
    }

    std::cout << "\n" << std::string(98, '=') << "\n";
    std::cout << std::left 
              << std::setw(8)  << "Book ID"
              << std::setw(32) << "Title"
              << std::setw(24) << "Author"
              << std::setw(10) << "Year"
              << std::setw(24) << "Category" << "\n";
    std::cout << std::string(98, '-') << "\n";

    for (int i = 0; i < n; i++) {
        std::cout << std::left 
                  << std::setw(8)  << books[i].id
                  << std::setw(32) << (books[i].title.length() > 30 ? books[i].title.substr(0, 29) + "." : books[i].title)
                  << std::setw(24) << (books[i].author.length() > 22 ? books[i].author.substr(0, 21) + "." : books[i].author)
                  << std::setw(10) << books[i].year
                  << std::setw(24) << books[i].category << "\n";
    }
    std::cout << std::string(98, '=') << "\n";
    std::cout << "Total Books: " << n << "\n";
}

// Check if a book ID is already present
bool isIdDuplicate(const Book books[], int n, int id) {
    for (int i = 0; i < n; i++) {
        if (books[i].id == id) return true;
    }
    return false;
}

// Add a new book
void addBook(Book books[], int &n) {
    if (n >= MAX_BOOKS) {
        std::cout << "[Error] Library storage is full! Cannot add more books.\n";
        return;
    }

    Book newBook;
    std::cout << "\n--- Add New Book ---\n";

    // Read ID with validation
    while (true) {
        std::cout << "Enter Book ID (positive integer): ";
        if (std::cin >> newBook.id && newBook.id > 0) {
            if (isIdDuplicate(books, n, newBook.id)) {
                std::cout << "[Error] Book ID " << newBook.id << " already exists! Please use a unique ID.\n";
            } else {
                break;
            }
        } else {
            std::cout << "[Error] Invalid input! Enter a positive integer for Book ID.\n";
            clearInputBuffer();
        }
    }
    clearInputBuffer(); // Consume newline

    // Read Title
    while (true) {
        std::cout << "Enter Book Title: ";
        std::getline(std::cin, newBook.title);
        if (!newBook.title.empty()) break;
        std::cout << "[Error] Title cannot be empty.\n";
    }

    // Read Author
    while (true) {
        std::cout << "Enter Author Name: ";
        std::getline(std::cin, newBook.author);
        if (!newBook.author.empty()) break;
        std::cout << "[Error] Author cannot be empty.\n";
    }

    // Read Publication Year
    while (true) {
        std::cout << "Enter Publication Year (e.g. 1900 - 2026): ";
        if (std::cin >> newBook.year && newBook.year >= 1000 && newBook.year <= 2100) {
            break;
        } else {
            std::cout << "[Error] Invalid year! Please enter a 4-digit valid year.\n";
            clearInputBuffer();
        }
    }
    clearInputBuffer();

    // Read Category
    while (true) {
        std::cout << "Enter Category (e.g. Computer Science, AI, Mathematics): ";
        std::getline(std::cin, newBook.category);
        if (!newBook.category.empty()) break;
        std::cout << "[Error] Category cannot be empty.\n";
    }

    books[n] = newBook;
    n++;
    std::cout << ">> Book \"" << newBook.title << "\" (ID: " << newBook.id << ") added successfully!\n";
}

// -----------------------------------------------------------------------------
// SEARCHING ALGORITHMS
// -----------------------------------------------------------------------------

// 1. Sentinel Search by Book ID
// Eliminates the loop index boundary check arr[i] < n by setting target at last element.
int sentinelSearchById(Book books[], int n, int targetId) {
    if (n == 0) return -1;

    // Check if the target is already the last element
    Book last = books[n - 1];

    // Place sentinel at the end of the array
    books[n - 1].id = targetId;

    int i = 0;
    while (books[i].id != targetId) {
        i++;
    }

    // Restore the original last element
    books[n - 1] = last;

    // If sentinel was found before the last element, or if last element was indeed target
    if (i < n - 1 || last.id == targetId) {
        return i; // Found at index i
    }
    return -1; // Not found
}

// 2. Sentinel Search by Title
int sentinelSearchByTitle(Book books[], int n, const std::string &targetTitle) {
    if (n == 0) return -1;

    Book last = books[n - 1];

    // Place targetTitle as sentinel
    books[n - 1].title = targetTitle;

    int i = 0;
    while (compareCaseInsensitive(books[i].title, targetTitle) != 0) {
        i++;
    }

    // Restore last element
    books[n - 1] = last;

    if (i < n - 1 || compareCaseInsensitive(last.title, targetTitle) == 0) {
        return i;
    }
    return -1;
}

// Helper: Manual Insertion Sort by Book ID (used to prepare array for Indexed Sequential Search)
void sortBooksById(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Helper: Manual Insertion Sort by Title (used to prepare array for Indexed Sequential Search)
void sortBooksByTitle(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareCaseInsensitive(arr[j].title, key.title) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Indexed Sequential Search by Book ID
int indexedSequentialSearchById(const Book books[], int n, int targetId) {
    if (n == 0) return -1;

    // Step 1: Create a sorted copy of the books array by Book ID
    Book sortedBooks[MAX_BOOKS];
    copyBookArray(books, sortedBooks, n);
    sortBooksById(sortedBooks, n);

    // Step 2: Build the Index Table
    IdIndexEntry indexTable[MAX_BOOKS];
    int numBlocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int b = 0; b < numBlocks; b++) {
        indexTable[b].startIndex = b * BLOCK_SIZE;
        indexTable[b].endIndex = (b + 1) * BLOCK_SIZE - 1;
        if (indexTable[b].endIndex >= n) {
            indexTable[b].endIndex = n - 1;
        }
        // Key represents the maximum Book ID in this block
        indexTable[b].key = sortedBooks[indexTable[b].endIndex].id;
    }

    // Display the Index Table for examination / viva clarity
    std::cout << "\n--- Constructed Index Table (Block Size = " << BLOCK_SIZE << ") ---\n";
    std::cout << std::left << std::setw(10) << "Block"
              << std::setw(15) << "Index Range"
              << std::setw(20) << "Max ID (Key)" << "\n";
    std::cout << std::string(45, '-') << "\n";
    for (int b = 0; b < numBlocks; b++) {
        std::cout << std::left << std::setw(10) << b
                  << "[" << indexTable[b].startIndex << ".." << indexTable[b].endIndex << "]"
                  << std::setw(8) << " "
                  << std::setw(20) << indexTable[b].key << "\n";
    }

    // Step 3: Search the Index Table sequentially to find candidate block
    int targetBlock = -1;
    for (int b = 0; b < numBlocks; b++) {
        if (targetId <= indexTable[b].key) {
            targetBlock = b;
            break;
        }
    }

    if (targetBlock == -1) {
        std::cout << ">> Target ID " << targetId << " exceeds the highest ID in the Index Table.\n";
        return -1;
    }

    std::cout << ">> Target ID belongs to Block " << targetBlock 
              << " (Indices " << indexTable[targetBlock].startIndex 
              << " to " << indexTable[targetBlock].endIndex << ").\n";

    // Step 4: Perform Sequential Search within the identified block
    int start = indexTable[targetBlock].startIndex;
    int end = indexTable[targetBlock].endIndex;

    for (int i = start; i <= end; i++) {
        if (sortedBooks[i].id == targetId) {
            std::cout << ">> Target found in Block " << targetBlock << " at sorted index " << i << ".\n";
            printBookDetails(sortedBooks[i]);
            return i;
        }
        if (sortedBooks[i].id > targetId) {
            break; // Stop early because block is sorted
        }
    }

    return -1;
}

// 4. Indexed Sequential Search by Title
int indexedSequentialSearchByTitle(const Book books[], int n, const std::string &targetTitle) {
    if (n == 0) return -1;

    // Step 1: Create a sorted copy of the books array by Title
    Book sortedBooks[MAX_BOOKS];
    copyBookArray(books, sortedBooks, n);
    sortBooksByTitle(sortedBooks, n);

    // Step 2: Build the Title Index Table
    TitleIndexEntry indexTable[MAX_BOOKS];
    int numBlocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int b = 0; b < numBlocks; b++) {
        indexTable[b].startIndex = b * BLOCK_SIZE;
        indexTable[b].endIndex = (b + 1) * BLOCK_SIZE - 1;
        if (indexTable[b].endIndex >= n) {
            indexTable[b].endIndex = n - 1;
        }
        indexTable[b].key = sortedBooks[indexTable[b].endIndex].title;
    }

    // Display Index Table
    std::cout << "\n--- Constructed Title Index Table (Block Size = " << BLOCK_SIZE << ") ---\n";
    std::cout << std::left << std::setw(8) << "Block"
              << std::setw(15) << "Index Range"
              << std::setw(30) << "Max Title (Key)" << "\n";
    std::cout << std::string(55, '-') << "\n";
    for (int b = 0; b < numBlocks; b++) {
        std::cout << std::left << std::setw(8) << b
                  << "[" << indexTable[b].startIndex << ".." << indexTable[b].endIndex << "]"
                  << std::setw(6) << " "
                  << std::setw(30) << indexTable[b].key << "\n";
    }

    // Step 3: Search the Index Table
    int targetBlock = -1;
    for (int b = 0; b < numBlocks; b++) {
        if (compareCaseInsensitive(targetTitle, indexTable[b].key) <= 0) {
            targetBlock = b;
            break;
        }
    }

    if (targetBlock == -1) {
        std::cout << ">> Target Title exceeds alphabetical range of the Index Table.\n";
        return -1;
    }

    std::cout << ">> Target Title belongs to Block " << targetBlock 
              << " (Indices " << indexTable[targetBlock].startIndex 
              << " to " << indexTable[targetBlock].endIndex << ").\n";

    // Step 4: Sequential Search inside target block
    int start = indexTable[targetBlock].startIndex;
    int end = indexTable[targetBlock].endIndex;

    for (int i = start; i <= end; i++) {
        if (compareCaseInsensitive(sortedBooks[i].title, targetTitle) == 0) {
            std::cout << ">> Target found in Block " << targetBlock << " at sorted index " << i << ".\n";
            printBookDetails(sortedBooks[i]);
            return i;
        }
        if (compareCaseInsensitive(sortedBooks[i].title, targetTitle) > 0) {
            break;
        }
    }

    return -1;
}

// -----------------------------------------------------------------------------
// SORTING ALGORITHMS
// -----------------------------------------------------------------------------

// 1. Insertion Sort by Title (Alphabetical)
void insertionSortByTitle(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareCaseInsensitive(arr[j].title, key.title) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 2. Insertion Sort by Publication Year (Ascending / Chronological)
void insertionSortByYear(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].year > key.year) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 3. Insertion Sort by Author (Alphabetical)
void insertionSortByAuthor(Book arr[], int n) {
    for (int i = 1; i < n; i++) {
        Book key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareCaseInsensitive(arr[j].author, key.author) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Shell Sort by Title (Alphabetical)
// Uses diminishing increments (gap = n/2, gap /= 2)
void shellSortByTitle(Book arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Book temp = arr[i];
            int j;
            for (j = i; j >= gap && compareCaseInsensitive(arr[j - gap].title, temp.title) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 5. Shell Sort by Publication Year (Ascending / Chronological)
void shellSortByYear(Book arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Book temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].year > temp.year; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// 6. Shell Sort by Author (Alphabetical)
void shellSortByAuthor(Book arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Book temp = arr[i];
            int j;
            for (j = i; j >= gap && compareCaseInsensitive(arr[j - gap].author, temp.author) > 0; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Practical 6 Interactive Menu
void practical6_menu() {
    // Preloaded initial library books for immediate testing
    Book library[MAX_BOOKS] = {
        {105, "Data Structures Using C++", "D. S. Malik", 2014, "Computer Science"},
        {102, "Introduction to Algorithms", "Thomas Cormen", 2009, "Algorithms"},
        {108, "Clean Code", "Robert C. Martin", 2008, "Software Engineering"},
        {101, "The C++ Programming Language", "Bjarne Stroustrup", 2013, "Programming"},
        {106, "Design Patterns", "Erich Gamma", 1994, "Software Engineering"},
        {103, "Artificial Intelligence", "Stuart Russell", 2020, "AI & ML"}
    };
    int bookCount = 6;

    int choice;
    do {
        std::cout << "\n============================================================\n";
        std::cout << "      PRACTICAL 6: ONLINE LIBRARY MANAGEMENT SYSTEM (C++)\n";
        std::cout << "============================================================\n";
        std::cout << "--- BOOK OPERATIONS ---\n";
        std::cout << " 1. Add New Book\n";
        std::cout << " 2. Display All Books\n";
        std::cout << " 3. Display Total Book Count\n";
        std::cout << "\n--- SEARCHING ALGORITHMS ---\n";
        std::cout << " 4. Sentinel Search by Book ID\n";
        std::cout << " 5. Sentinel Search by Title\n";
        std::cout << " 6. Indexed Sequential Search by Book ID\n";
        std::cout << " 7. Indexed Sequential Search by Title\n";
        std::cout << "\n--- SORTING ALGORITHMS ---\n";
        std::cout << " 8. Insertion Sort by Title\n";
        std::cout << " 9. Insertion Sort by Publication Year\n";
        std::cout << "10. Insertion Sort by Author\n";
        std::cout << "11. Shell Sort by Title\n";
        std::cout << "12. Shell Sort by Publication Year\n";
        std::cout << "13. Shell Sort by Author\n";
        std::cout << "\n14. Return to Main Menu\n";
        std::cout << "============================================================\n";
        std::cout << "Enter your choice (1-14): ";

        if (!(std::cin >> choice)) {
            std::cout << "[Error] Invalid input! Please enter a valid number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                addBook(library, bookCount);
                break;
            }
            case 2: {
                displayAllBooks(library, bookCount);
                break;
            }
            case 3: {
                std::cout << "\n>> Total books currently in library: " << bookCount << "\n";
                break;
            }
            case 4: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                int searchId;
                std::cout << "\nEnter Book ID to search (Sentinel Search): ";
                while (!(std::cin >> searchId)) {
                    std::cout << "Invalid input! Enter positive integer Book ID: ";
                    clearInputBuffer();
                }

                int index = sentinelSearchById(library, bookCount, searchId);
                std::cout << "\n--- Sentinel Search Result (by ID) ---\n";
                if (index != -1) {
                    std::cout << "[FOUND] Book found at index " << index << " in library records:\n";
                    printBookDetails(library[index]);
                } else {
                    std::cout << "[NOT FOUND] No book with ID " << searchId << " exists in the library.\n";
                }
                break;
            }
            case 5: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                clearInputBuffer();
                std::string searchTitle;
                std::cout << "\nEnter Book Title to search (Sentinel Search): ";
                std::getline(std::cin, searchTitle);

                int index = sentinelSearchByTitle(library, bookCount, searchTitle);
                std::cout << "\n--- Sentinel Search Result (by Title) ---\n";
                if (index != -1) {
                    std::cout << "[FOUND] Book found at index " << index << " in library records:\n";
                    printBookDetails(library[index]);
                } else {
                    std::cout << "[NOT FOUND] No book with title \"" << searchTitle << "\" found.\n";
                }
                break;
            }
            case 6: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                int searchId;
                std::cout << "\nEnter Book ID to search (Indexed Sequential Search): ";
                while (!(std::cin >> searchId)) {
                    std::cout << "Invalid input! Enter positive integer Book ID: ";
                    clearInputBuffer();
                }

                int index = indexedSequentialSearchById(library, bookCount, searchId);
                std::cout << "\n--- Indexed Sequential Search Result (by ID) ---\n";
                if (index != -1) {
                    std::cout << "[FOUND] Successfully retrieved book with ID " << searchId << "!\n";
                } else {
                    std::cout << "[NOT FOUND] Book with ID " << searchId << " not found in library.\n";
                }
                break;
            }
            case 7: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                clearInputBuffer();
                std::string searchTitle;
                std::cout << "\nEnter Book Title to search (Indexed Sequential Search): ";
                std::getline(std::cin, searchTitle);

                int index = indexedSequentialSearchByTitle(library, bookCount, searchTitle);
                std::cout << "\n--- Indexed Sequential Search Result (by Title) ---\n";
                if (index != -1) {
                    std::cout << "[FOUND] Successfully retrieved book with title \"" << searchTitle << "\"!\n";
                } else {
                    std::cout << "[NOT FOUND] Book with title \"" << searchTitle << "\" not found in library.\n";
                }
                break;
            }
            case 8: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                insertionSortByTitle(temp, bookCount);
                std::cout << "\n--- Books Sorted by Title (Insertion Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 9: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                insertionSortByYear(temp, bookCount);
                std::cout << "\n--- Books Sorted by Publication Year (Insertion Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 10: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                insertionSortByAuthor(temp, bookCount);
                std::cout << "\n--- Books Sorted by Author (Insertion Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 11: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                shellSortByTitle(temp, bookCount);
                std::cout << "\n--- Books Sorted by Title (Shell Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 12: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                shellSortByYear(temp, bookCount);
                std::cout << "\n--- Books Sorted by Publication Year (Shell Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 13: {
                if (bookCount == 0) {
                    std::cout << "[Warning] Library is empty!\n";
                    break;
                }
                Book temp[MAX_BOOKS];
                copyBookArray(library, temp, bookCount);
                shellSortByAuthor(temp, bookCount);
                std::cout << "\n--- Books Sorted by Author (Shell Sort) ---\n";
                displayAllBooks(temp, bookCount);
                break;
            }
            case 14: {
                std::cout << "\nReturning to Main Menu...\n";
                break;
            }
            default: {
                std::cout << "[Error] Invalid choice! Please select an option between 1 and 14.\n";
                break;
            }
        }
    } while (choice != 14);
}

} // namespace PR6

#ifndef INTEGRATED_MAIN
int main() {
    PR6::practical6_menu();
    return 0;
}
#endif

