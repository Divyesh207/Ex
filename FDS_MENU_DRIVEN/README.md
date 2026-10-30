# Fundamentals of Data Structures (FDS) Laboratory
**Department of AI-DS, DYPCOE, Akurdi, Pune**
**Semester III | B.Tech Artificial Intelligence & Data Science**

---

## 📁 Project Structure

```text
FDS_MENU_DRIVEN/
│
├── Python/
│   └── practical_3.py       # PR3: String Operations (Python)
│
└── C++/
    ├── practical_4.cpp      # PR4: Searching Algorithms (C++)
    ├── practical_5.cpp      # PR5: Sorting Algorithms (C++)
    ├── practical_6.cpp      # PR6: Online Library Management System (C++)
    └── main.cpp             # Integrated Main Menu (PR4, PR5, PR6)
```

---

## 🚀 How to Run the Programs

### 1. Practical 3 (Python)
Navigate to the directory and run:
```bash
python Python/practical_3.py
```

### 2. C++ Practicals

#### Option A: Run Unified Application (`main.cpp`)
To access PR4, PR5, and PR6 through the common master menu:
```bash
cd C++
g++ main.cpp -o main.exe
./main.exe
```

#### Option B: Run Any Practical Standalone
Each `.cpp` file can also be compiled and executed directly as an independent program:

* **Practical 4 (Searching):**
  ```bash
  cd C++
  g++ practical_4.cpp -o practical_4.exe
  ./practical_4.exe
  ```

* **Practical 5 (Sorting):**
  ```bash
  cd C++
  g++ practical_5.cpp -o practical_5.exe
  ./practical_5.exe
  ```

* **Practical 6 (Library Management):**
  ```bash
  cd C++
  g++ practical_6.cpp -o practical_6.exe
  ./practical_6.exe
  ```

---

## 📋 Practicals Summary & Algorithms

### PR3 – String Operations (Python)
* **File:** `Python/practical_3.py`
* **Features:**
  1. Count vowels and consonants (excludes spaces and symbols).
  2. Reverse individual words without changing their order.
  3. Find the longest word (handles punctuation).
  4. Display original string.
  5. Exit.

### PR4 – Searching Algorithms (C++)
* **File:** `C++/practical_4.cpp`
* **Features:**
  1. Store employee IDs in an array in random order.
  2. **Linear Search:** Searches the original unordered array element-by-element ($O(n)$).
  3. **Binary Search:** Operates on a sorted copy of the array ($O(\log n)$), keeping the original array preserved.
  4. Displays whether the employee attended the training program.

### PR5 – Sorting Algorithms (C++)
* **File:** `C++/practical_5.cpp`
* **Features:**
  * Stores student percentages using floating-point numbers (`float`).
  * Manual implementations of:
    1. **Selection Sort:** $O(n^2)$ time, in-place.
    2. **Insertion Sort:** $O(n^2)$ time, adaptive, in-place.
    3. **Bubble Sort:** $O(n^2)$ time, with early termination optimization.
    4. **Quick Sort:** $O(n \log n)$ average time, Lomuto partition scheme.
  * Displays both original and sorted arrays.
  * Preserves original data across all algorithm selections.
  * Displays Top 5 scores.

### PR6 – Online Library Management System (C++)
* **File:** `C++/practical_6.cpp`
* **Book Attributes:** Book ID, Title, Author, Publication Year, Category.
* **Searching Algorithms:**
  1. **Sentinel Search by Book ID:** Eliminates loop bounds checking using a sentinel value.
  2. **Sentinel Search by Title:** Case-insensitive string sentinel search.
  3. **Indexed Sequential Search by Book ID:** Uses a structured index table with block size 3 on sorted data, followed by sequential search in the identified block.
  4. **Indexed Sequential Search by Title:** Two-tier indexed search on book titles.
* **Sorting Algorithms:**
  1. Insertion Sort by Title, Year, Author.
  2. Shell Sort by Title, Year, Author (diminishing gap $gap = n/2, gap /= 2$).
* **Library Operations:** Add book (with duplicate ID validation), Display all books, Display total count.

---

## 🎯 Viva Questions & Concepts

1. **What is Sentinel Search and why is it faster than Linear Search?**
   * *Answer:* Regular linear search does two checks per iteration: `i < n` and `arr[i] == key`. Sentinel search places the target value at the end of the array, eliminating the `i < n` boundary check in every iteration and halving the condition checks inside the loop.

2. **How does Indexed Sequential Search work?**
   * *Answer:* It divides a sorted array into blocks and maintains an auxiliary Index Table storing the highest key of each block along with block bounds. Searching first checks the Index Table to pinpoint the target block, then performs sequential search only within that block.

3. **Why do we need a sorted copy for Binary Search in PR4?**
   * *Answer:* Binary Search fundamentally requires sorted data to apply divide-and-conquer. To avoid corrupting or altering the original chronological order of attendees, we clone the array and sort only the clone.

4. **What is Shell Sort and how is it related to Insertion Sort?**
   * *Answer:* Shell Sort is a generalized and optimized version of Insertion Sort that allows exchanges of entries that are far apart using a diminishing gap sequence. As the gap shrinks to 1, the array becomes nearly sorted, which is the best-case scenario for Insertion Sort ($O(n)$).

5. **Why is in-place sorting preferred?**
   * *Answer:* In-place algorithms sort the list without requiring significant additional memory ($O(1)$ auxiliary space), making them memory efficient.

