# Take number of students as input
Student = int(input("Enter number of students: "))
 
# Create a list to store marks
Marks = []
 
# Store marks of all students in the list
for i in range(Student):
    m = int(input("Enter marks (-1 for absent): "))
    Marks.append(m)
 
# Function to count absent students
def absent_cnt():
    Count = 0
    for i in Marks:
        # -1 represents an absent student
        if i == -1:
            Count += 1
    print("Absent students:", Count)
 
# Function to calculate average marks
def average_std():
    Total = 0
    Count = 0
    for i in Marks:
        if i != -1:
            Total += i
            Count += 1
 
    # Check if any student is present
    if Count == 0:
        print("Average: 0")
    else:
        Average = Total / Count
        print("Average:", Average)
 
# Function to find maximum marks
def maximum_std():
    Maximum = -1
    for i in Marks:
        # Ignore absent students
        if i != -1:
            if i > Maximum:
                Maximum = i
    print("Maximum score:", Maximum)
 
# Function to find minimum marks
def minimum_std():
    Minimum = 101
    for i in Marks:
        # Ignore absent students
        if i != -1:
            if i < Minimum:
                Minimum = i
    print("Minimum score:", Minimum)
 
# Call all the functions
absent_cnt()
average_std()
maximum_std()
minimum_std()
