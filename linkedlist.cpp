#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

// Insert node at beginning (Prepend)
void insertBeginning(Node*& head, int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->next = head;

    head = newNode;

    cout << "Node inserted at beginning!" << endl;
}

// Insert node at end (Append)
void insertEnd(Node*& head, int value)
{
    Node* newNode = new Node;

    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Display linked list
void display(Node* head)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    Node* temp = head;

    while (temp != nullptr)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

// Delete first node
void deleteFirst(Node*& head)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    Node* temp = head;
    head = head->next;

    delete temp;

    cout << "First node deleted successfully!" << endl;
}

// Delete last node
void deleteLast(Node*& head)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;

        cout << "Last node deleted successfully!" << endl;
        return;
    }

    Node* temp = head;

    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = nullptr;

    cout << "Last node deleted successfully!" << endl;
}

// Delete node by value
void deleteValue(Node*& head, int value)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    if (head->data == value)
    {
        Node* temp = head;
        head = head->next;

        delete temp;

        cout << "Node deleted successfully!" << endl;
        return;
    }

    Node* temp = head;

    while (temp->next != nullptr &&
           temp->next->data != value)
    {
        temp = temp->next;
    }

    if (temp->next == nullptr)
    {
        cout << "Value not found!" << endl;
        return;
    }

    Node* deleteNode = temp->next;
    temp->next = deleteNode->next;

    delete deleteNode;

    cout << "Node deleted successfully!" << endl;
}

// Main function
int main()
{
    Node* head = nullptr;
    int choice, value;

    do
    {
        cout << "\n--- LINKED LIST MENU ---" << endl;
        cout << "1. Insert at Beginning (Prepend)" << endl;
        cout << "2. Insert at End (Append)" << endl;
        cout << "3. Display List" << endl;
        cout << "4. Delete First Node" << endl;
        cout << "5. Delete Last Node" << endl;
        cout << "6. Delete Node by Value" << endl;
        cout << "7. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter value: ";
                cin >> value;

                insertBeginning(head, value);

                cout << "Updated Linked List: ";
                display(head);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;

                insertEnd(head, value);

                cout << "Node inserted at end!" << endl;
                cout << "Updated Linked List: ";
                display(head);
                break;

            case 3:
                cout << "Current Linked List: ";
                display(head);
                break;

            case 4:
                deleteFirst(head);

                cout << "Updated Linked List: ";
                display(head);
                break;

            case 5:
                deleteLast(head);

                cout << "Updated Linked List: ";
                display(head);
                break;

            case 6:
                cout << "Enter value to delete: ";
                cin >> value;

                deleteValue(head, value);

                cout << "Updated Linked List: ";
                display(head);
                break;

            case 7:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
        }

    } while (choice != 7);

    // Free remaining nodes
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
