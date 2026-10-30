"""
================================================================================
Department of AI-DS, DYPCOE, Akurdi, Pune
Fundamentals of Data Structures Laboratory (FDS Lab)
Practical No. 03: String Operations

Problem Statement:
Implement a menu-driven Python program to compute following operations on string:
1. Count the number of vowels and consonants from the input string.
2. Reverse the words in the string without changing their order.
3. Find the longest word in the string.
4. Display the original string.
5. Exit.
================================================================================
"""

def count_vowels_and_consonants(text):
    """
    Counts the total number of vowels and consonants in the given text.
    Vowels: A, E, I, O, U (case-insensitive)
    Consonants: All other alphabetic letters.
    Non-alphabetic characters (spaces, digits, symbols) are excluded.
    """
    vowels_set = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'}
    vowel_count = 0
    consonant_count = 0
    
    for ch in text:
        if ch.isalpha():
            if ch in vowels_set:
                vowel_count += 1
            else:
                consonant_count += 1
                
    return vowel_count, consonant_count


def reverse_words_preserving_order(text):
    """
    Reverses each individual word in the string while keeping
    the word order identical.
    Example: 'Hello World' -> 'olleH dlroW'
    """
    # Split text into words based on spaces
    words = text.split()
    reversed_words = []
    
    for word in words:
        # Reverse characters of the word manually
        reversed_word = ""
        for ch in word:
            reversed_word = ch + reversed_word
        reversed_words.append(reversed_word)
        
    return " ".join(reversed_words)


def find_longest_word(text):
    """
    Finds and returns the longest word in the string along with its length.
    Punctuation at word boundaries is stripped for accurate word length.
    """
    words = text.split()
    if not words:
        return "", 0
    
    longest = ""
    punctuation = ".,!?;:\"'()[]{}"
    
    for word in words:
        # Strip common punctuation from edges
        clean_word = word.strip(punctuation)
        if len(clean_word) > len(longest):
            longest = clean_word
            
    return longest, len(longest)


def practical_3_menu():
    """
    Interactive menu-driven interface for Practical 3.
    """
    print("=" * 60)
    print("         PRACTICAL 3: STRING OPERATIONS (PYTHON)")
    print("=" * 60)
    
    user_string = input("Enter the initial string: ").strip()
    while not user_string:
        print("String cannot be empty! Please enter a valid string.")
        user_string = input("Enter the initial string: ").strip()
    
    while True:
        print("\n" + "=" * 60)
        print("                    PRACTICAL 3 MENU")
        print("=" * 60)
        print("1. Count vowels and consonants")
        print("2. Reverse individual words without changing their order")
        print("3. Find the longest word")
        print("4. Display the original string")
        print("5. Exit")
        print("=" * 60)
        
        choice = input("Enter your choice (1-5): ").strip()
        
        if choice == '1':
            vowels, consonants = count_vowels_and_consonants(user_string)
            print("\n--- Result: Vowel & Consonant Count ---")
            print(f"Original String : \"{user_string}\"")
            print(f"Number of Vowels     : {vowels}")
            print(f"Number of Consonants : {consonants}")
            print(f"Total Alphabets      : {vowels + consonants}")
            
        elif choice == '2':
            reversed_result = reverse_words_preserving_order(user_string)
            print("\n--- Result: Words Reversed (Preserving Order) ---")
            print(f"Original String : \"{user_string}\"")
            print(f"Reversed Words  : \"{reversed_result}\"")
            
        elif choice == '3':
            longest, length = find_longest_word(user_string)
            print("\n--- Result: Longest Word ---")
            print(f"Original String : \"{user_string}\"")
            if longest:
                print(f"Longest Word    : \"{longest}\"")
                print(f"Length of Word  : {length} character(s)")
            else:
                print("No valid word found in the string.")
                
        elif choice == '4':
            print("\n--- Original String ---")
            print(f"\"{user_string}\"")
            
        elif choice == '5':
            print("\nExiting Practical 3. Thank you!")
            break
            
        else:
            print("\n[Error] Invalid choice! Please select a number between 1 and 5.")


if __name__ == "__main__":
    practical_3_menu()

