
#include<iostream>
using namespace std;
class Node
{
    public:
    int PRN;
    string Name;
    Node*next;
    Node(int p, string n)
    {
        PRN = p;
        Name = n;
        next = NULL;
    }
};
class Club_ISA
{
 Node*Head;
    public:
    Club_ISA()
    {
        Head = NULL;
    }
    Node*createNode()
    {
        int p;
        string n;
        cout<<"Enter PRN : ";
        cin>>p;
        cout<<"Enter Name : ";
        cin>>n;
        Node*newNode = new Node(p,n);
        return (newNode);
    }
    // Add President
    void addPresident()
    {
        Node*newNode = createNode();
        newNode->next=Head;

        Head = newNode;
    }
    // Add Secretary
    void addSecretary()
    {
        Node*newNode = createNode();
        if (Head == NULL)
            Head = newNode;
        else
        {
            Node*temp = Head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
             temp->next = newNode;
        }
    }
    // Add member after particular PRN 
    void addMember()
    {
        int search_PRN;
        cout<<"Enter PRN after which you have to add : ";
        cin>>search_PRN;

        Node*temp = Head;
        while(temp != NULL && temp->PRN != search_PRN)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            cout<<"PRN not found\n";
            return;
        }
        Node*newNode = createNode();
        newNode->next = temp->next;
        temp->next = newNode;
    }
    // Delete President
    void delPresident()
    {
        if (Head == NULL)
        {
            cout<<"Empty List\n";
            return;
        }
        Node*temp = Head;
        Head = Head->next;
        delete temp;
    }

    // Delete Secretary
    void delSecretary()
    {
        if (Head == NULL)
        {
            cout<<"Empty List\n";
            return;
        }
        if (Head->next == NULL)
        {
            delete Head;
            Head = NULL;
            return;
        }
        Node*temp = Head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }
    // Delete Member
    void delMember()
    {
        int search_PRN;
        cout<<"Enter PRN which you have to delete : ";
        cin>>search_PRN;
        if (Head == NULL)
        {
            cout<<"Empty List\n";
            return;
        }
        if (Head->PRN == search_PRN)
        {
            cout<<"Use Delete President for President\n";
            return;
        }
        Node*temp = Head;
        while (temp->next != NULL && temp->next->PRN != search_PRN)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            cout<<"PRN not found\n";
            return;
        }
        Node*delMember = temp->next;
        temp->next = delMember->next;
        delete delMember;
    }
    // Count
    void count()
    {
        int c = 0;
        Node*temp = Head;
        while (temp != NULL)
        {
            c++;
            temp = temp->next;
        }
        cout<<"Total Members : "<<c<<endl;
    }
    // Display
    void display()
    {
        Node*temp = Head;
        if (Head == NULL)
        {
            cout<<"List is Empty\n";
            return;
        }
        while (temp != NULL)
        {
            cout<<temp->PRN<<" "
                <<temp->Name<<endl;
      temp = temp->next;
        }
    }
    // Concatenate Two Lists
    void concatCLUB_ISA(Club_ISA &l2)
    {
        Node*temp1 = l2.Head;
        Node*temp = Head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = temp1;
        l2.Head = NULL;
    }
};
int main()
{
    Club_ISA*l;
    Club_ISA l1, l2;
    int ch1;
    X:
    cout<<"\n==== Select List ====\n";
    cout<<"1.Linked List for SY\n";
    cout<<"2.Linked List for TY\n";
    cout<<"Enter your choice : ";
    cin>>ch1;
    if (ch1 == 1)
    {
        l = &l1;
    }
    else if (ch1 == 2)
    {
        l = &l2;
    }
    else
    {
        cout<<"Invalid Choice\n";
    }
    // Menu
    int choice;
    do
    {
        cout<<"\n----- ISA CLUB MENU -----\n";
        cout<<"1. Add President\n";
        cout<<"2. Add Secretary\n";
        cout<<"3. Add Member\n";
        cout<<"4. Delete President\n";
        cout<<"5. Delete Secretary\n";
        cout<<"6. Delete Member\n";
        cout<<"7. Count Members\n";
        cout<<"8. Display Members\n";
        cout<<"9. Reselect List\n";
        cout<<"10.Concatenate\n"; 
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            l->addPresident();
            break;
            case 2:
            l->addSecretary();
            break;
            case 3:
            l->addMember();
            break;
            case 4:
            l->delPresident();
            break;
            case 5:
            l->delSecretary();
            break;
            case 6:
            l->delMember();
            break;
            case 7:
            l->count();
            break;
            case 8:
            l->display();
            break;
            case 9:
            goto X;
            break;
            case 10:
            l1.concatCLUB_ISA(l2);
            cout<<"Concatenated List :\n";
            l1.display();
            break;
            case 11:
            cout<<"Exiting Program...\n";
            break;
            default:
            cout<<"Invalid Choice\n";
        }
    } while (choice != 11);
    return 0;
}