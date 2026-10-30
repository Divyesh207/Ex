# Function for Selection Sort
def selection_sort(arr):
    for i in range(len(arr)):
        min_index = i
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_index]:
                min_index = j
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr
 
# Function for Insertion Sort
def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j = j - 1
        arr[j + 1] = key
    return arr
 
# Function for Bubble Sort
def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(0, len(arr) - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return arr
 
# Function for Quick Sort
def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[-1]
    left = []
    right = []
    for i in arr[:-1]:
        if i <= pivot:
            left.append(i)
        else:
            right.append(i)
    return quick_sort(left) + [pivot] + quick_sort(right)
 
# Take number of students as input
n = int(input("Enter number of students: "))
percentage = []
 
# Store percentage of students
for i in range(n):
    marks = float(input("Enter percentage: "))
    percentage.append(marks)
 
# Display original array
print("\nOriginal percentages:", percentage)
 
# Create copies for each sorting algorithm
selection = percentage.copy()
insertion = percentage.copy()
bubble = percentage.copy()
 
# Apply Selection Sort
selection_sort(selection)
print("\nSelection Sort:", selection)
 
# Apply Insertion Sort
insertion_sort(insertion)
print("Insertion Sort:", insertion)
 
# Apply Bubble Sort
bubble_sort(bubble)
print("Bubble Sort:", bubble)
 
# Apply Quick Sort
quick = quick_sort(percentage)
print("Quick Sort:", quick)
