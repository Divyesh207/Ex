# Function for Linear Search
def linear_search(arr, target):
    # Check each element one by one
    for i in range(len(arr)):
        if arr[i] == target:
            return True
    return False
 
# Function for Binary Search
def binary_search(arr, target):
    # Binary search works on sorted array
    low = 0
    high = len(arr) - 1
 
    while low <= high:
        mid = (low + high) // 2
 
        if arr[mid] == target:
            return True
        elif arr[mid] < target:
            # Search in right half
            low = mid + 1
        else:
            # Search in left half
            high = mid - 1
    return False
 
# Take employee IDs as input
n = int(input("Enter number of employees: "))
employee_ids = []
 
# Store employee IDs in random order
for i in range(n):
    emp_id = int(input("Enter employee ID: "))
    employee_ids.append(emp_id)
 
# Display original array
print("\nEmployee IDs:", employee_ids)
 
# Search employee using Linear Search
target = int(input("\nEnter employee ID to search: "))
if linear_search(employee_ids, target):
    print("Employee attended the training (Linear Search)")
else:
    print("Employee did not attend the training (Linear Search)")
 
# Sort the array for Binary Search
employee_ids.sort()
print("\nSorted Employee IDs:", employee_ids)
 
# Search employee using Binary Search
if binary_search(employee_ids, target):
    print("Employee attended the training (Binary Search)")
else:
    print("Employee did not attend the training (Binary Search)")
