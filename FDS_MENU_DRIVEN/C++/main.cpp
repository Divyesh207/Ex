/*
================================================================================
Department of AI-DS, DYPCOE, Akurdi, Pune
Fundamentals of Data Structures Laboratory (FDS Lab)
Integrated C++ Practicals Main Interface

This program provides a unified interactive main menu to access:
- Practical 4: Searching Algorithms (Linear Search, Binary Search)
- Practical 5: Sorting Algorithms (Selection, Insertion, Bubble, Quick)
- Practical 6: Online Library Management System (Sentinel & Indexed Sequential Search,
                                                Insertion & Shell Sort)

Note: Practical 3 (String Operations) is implemented in Python under:
      FDS_MENU_DRIVEN/Python/practical_3.py
================================================================================
*/

#define INTEGRATED_MAIN

// Include individual practical implementation modules
#include "practical_4.cpp"
#include "practical_5.cpp"
#include "practical_6.cpp"

#include <iostream>
#include <limits>

// Safe input buffer cleaner for the main menu
static void clearMainMenuInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to invoke Practical 4 Menu
void runPractical4() {
    PR4::practical4_menu();
}

// Function to invoke Practical 5 Menu
void runPractical5() {
    PR5::practical5_menu();
}

// Function to invoke Practical 6 Menu
void runPractical6() {
    PR6::practical6_menu();
}

int main() {
    int choice;
    do {
        std::cout << "\n====================================\n";
        std::cout << "        FDS PRACTICALS - C++\n";
        std::cout << "====================================\n";
        std::cout << "1. Practical 4 - Searching\n";
        std::cout << "2. Practical 5 - Sorting\n";
        std::cout << "3. Practical 6 - Library Management\n";
        std::cout << "4. Exit\n";
        std::cout << "====================================\n";
        std::cout << "Enter your choice (1-4): ";

        if (!(std::cin >> choice)) {
            std::cout << "\n[Error] Invalid input! Please enter a number between 1 and 4.\n";
            clearMainMenuInput();
            continue;
        }

        switch (choice) {
            case 1:
                runPractical4();
                break;
            case 2:
                runPractical5();
                break;
            case 3:
                runPractical6();
                break;
            case 4:
                std::cout << "\nExiting FDS Practicals Application. Best of luck for your exam!\n";
                break;
            default:
                std::cout << "\n[Error] Invalid option! Please select between 1 and 4.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

