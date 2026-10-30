# Function to input a matrix
def input_matrix(rows, cols):
    matrix = []
    for i in range(rows):
        row = []
        for j in range(cols):
            value = int(input("Enter element: "))
            row.append(value)
        matrix.append(row)
    return matrix
 
# Function to display a matrix
def display_matrix(matrix):
    for row in matrix:
        print(row)
 
# Function for matrix addition
def addition(A, B):
    result = []
    for i in range(len(A)):
        row = []
        for j in range(len(A[0])):
            row.append(A[i][j] + B[i][j])
        result.append(row)
    return result
 
# Function for matrix subtraction
def subtraction(A, B):
    result = []
    for i in range(len(A)):
        row = []
        for j in range(len(A[0])):
            row.append(A[i][j] - B[i][j])
        result.append(row)
    return result
 
# Function for matrix multiplication
def multiplication(A, B):
    result = []
    for i in range(len(A)):
        row = []
        for j in range(len(B[0])):
            total = 0
            for k in range(len(B)):
                total = total + A[i][k] * B[k][j]
            row.append(total)
        result.append(row)
    return result
 
# Function for transpose
def transpose(A):
    result = []
    for j in range(len(A[0])):
        row = []
        for i in range(len(A)):
            row.append(A[i][j])
        result.append(row)
    return result
 
# Input size of first matrix
r1 = int(input("Enter rows of first matrix: "))
c1 = int(input("Enter columns of first matrix: "))
print("Enter elements of first matrix:")
A = input_matrix(r1, c1)
 
# Input size of second matrix
r2 = int(input("Enter rows of second matrix: "))
c2 = int(input("Enter columns of second matrix: "))
print("Enter elements of second matrix:")
B = input_matrix(r2, c2)
 
# Display matrices
print("\nFirst Matrix:")
display_matrix(A)
print("Second Matrix:")
display_matrix(B)
 
# Addition and subtraction require same dimensions
if r1 == r2 and c1 == c2:
    print("\nAddition of matrices:")
    display_matrix(addition(A, B))
    print("Subtraction of matrices:")
    display_matrix(subtraction(A, B))
else:
    print("\nAddition and subtraction not possible.")
 
# Multiplication requires columns of A = rows of B
if c1 == r2:
    print("\nMultiplication of matrices:")
    display_matrix(multiplication(A, B))
else:
    print("\nMultiplication not possible.")
 
# Transpose of first matrix
print("\nTranspose of first matrix:")
display_matrix(transpose(A))
 
# Transpose of second matrix
print("Transpose of second matrix:")
display_matrix(transpose(B))
