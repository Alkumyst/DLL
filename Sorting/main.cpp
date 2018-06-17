#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <chrono>


template <class T>
class Node {
public:
    Node(const T &e = T(), Node *n = NULL, Node *p = NULL) : element(e), next(n), previous(p) {}    //constructor that will create a double node with element type T, a pointer for next and previous set to NULL
    ~Node() {}                                                                                      //deconstructor
    T element;                                                                                      //element type declaration
    Node *next;                                                                                     //next node pointer
    Node *previous;                                                                                 //previous node pointer
};

template <class T>
class Iterator {
public:
    Iterator(Node<T> *node = NULL) : actNode(node) {}                   //constructor
    ~Iterator() {                                                       //deconstructor, sets each node to null
        if (actNode == NULL) {                                          //if the node is null
            actNode = NULL;                                             //set to null
        }
    }
    Node<T> *nextNode() {                                               //get next node function
        if (actNode == NULL) {                                          //if node is null
            return NULL;                                                //return null
        }
        actNode = actNode->next;                                        //actNode becomes next node
        return actNode;                                                 //return actNode
    }
    Node<T> *prevNode() {                                               //get previous node function
        if (actNode == NULL) {                                          //if node is null
            return NULL;                                                //return null
        }
        actNode = actNode->previous;                                    //actNode becomes previous node
        return actNode;                                                 //return actNode
    }
private:
    Node<T> *actNode;                                                //pointer to actual node for iterator
};

template <class T>                                                  //templated class
class DLList {                                                      //doubly linked list class
public:
    DLList() {                                                      //constructor
        head = new Node<T>();                                       //creates head node
        tail = new Node<T>();                                       //creates tail node
    }
    ~DLList() {                                                     //deconstructor
        Clear();                                                    //run clear function
        delete head;                                                //delete head node
        delete tail;                                                //delete tail node
    }
    bool isEmpty() {                                                //isEmpty function
        return (head->next == NULL);                                //returns true if the node next to head is null, false if it contains data
    }
    void Insert(T &e) {                                             //insert function
        if (isEmpty()) {                                            //if list is empty
            Node<T> *newNode = new Node<T>(e);                      //create new node
            head->next = newNode;                                   //set newNode to the node next to the head
            tail->previous = newNode;                               //set newNode to node previous to tail
        }
        else {                                                      //if list already contains data
            Node<T> *actLast = tail->previous;                      //create actual last node, set from node previous to tail
            Node<T> *newNode = new Node<T>(e, NULL, actLast);       //create new node
            actLast->next = newNode;                                //actual last node's next is set to newNode
            tail->previous = newNode;                               //tail's previous node is set to newNode
        }
    }
    bool Delete(Node<T> *r) {                                       //delete function
        if (isEmpty()) {                                            //if list is empty
            return false;                                           //return false
        }
        if (r == NULL) {                                            //if r (address from find function) is null
            return false;                                           //return false
        }
        else {                                                      //if r is not null and list had data
            Node<T> *aftRem = r->next;                              //create after remove node, set to node next to r
            Node<T> *befRem = r->previous;                          //create before remove node, set to node previous to r
            if (aftRem == NULL) {                                   //if aftRem is null
                tail->previous = befRem;                            //set node previous to tail to befRem
            }
            else {                                                  //if aftRem is not null
                aftRem->previous = befRem;                          //set node previous to aftRem to befRem
            }
            if (befRem == NULL) {                                   //if befRem is null
                head->next = aftRem;                                //set node next to head to aftRem
            }
            else {                                                  //if befRem is not null
                befRem->next = aftRem;                              //set node next to befRem to aftRem
            }
            delete r;                                               //delete r
            return true;                                            //return true
        }
    }
    void Clear() {                                                  //clear function
        int count = 0;                                              //create count variable set to 0 initially
        while (tail->previous != NULL) {                            //while the node previous to tail is not null
            Node<T> *rem = tail->previous;                          //create remove node, set to node previous to tail
            tail->previous = rem->previous;                         //set node previous to tail, to node previous to rem
            delete rem;                                             //delete rem
            count++;                                                //increase count
        }
        std::cout << "Cleared " << count << " nodes" << std::endl;  //inform user of how many nodes were deleted
    }
    Iterator<T> *getItHead() {                                      //iterator getHead function
        Iterator<T> *i = new Iterator<T>(head);                     //create iterator i set to head
        return i;                                                   //return i
    }
    Iterator<T> *getItTail() {                                      //iterator getTail function
        Iterator<T> *i = new Iterator<T>(tail);                     //create iterator i set to tail
        return i;                                                   //return i
    }
    Node<T>* Find(T &value) {                                       //find function
        Node<T> *tempNode = head;                                   //create tempNode set to head
        while (tempNode != NULL) {                                  //while tempNode is not null
            if (tempNode->element == value) {                       //if the element of tempNode is found
                return tempNode;                                    //return tempNode
            }
            tempNode = tempNode->next;                              //iterate through the list
        }
        std::cout << "The value was not found or the list is empty" << std::endl;   //inform user value was not found
        return NULL;                                                                //return null
    }
    void InsertionSort () {                                                             //insertion sort function
        Node<T> *mark;                                                                  //marker node
        Node<T> *curr;                                                                  //current node
        for (mark = head->next; mark != nullptr; mark = mark->next) {                   //for loop, start marker next to head, as long as marker is not null, move marker to the next
            T temp = mark->element;                                                     //templated temp variable set to value of marker
            curr = mark;                                                                //current set to marker
            while (curr->previous != nullptr && curr->previous->element >= temp) {      //while current's previous is not null and current previous value is greater than or equal to the temp value
                curr->element = curr->previous->element;                                //value of current is set to the value of the node previous to current
                curr = curr->previous;                                                  //current node is set to previous
            }
            curr->element = temp;                                                       //set value of current node to the value of temp
        }
    }
    Node<T>* GetHead() {                                            //get head function
        return head;                                                //return head
    }
    
private:
    Node<T> *head;                                                  //list head
    Node<T> *tail;                                                  //list tail
};


template <class T>                                              //templated function
void Swap (T* a, T* b) {                                        //variable swap function
    T temp = *a;                                                //temp variable of type T is set to parameter a
    *a = *b;                                                    //parameter a is set to parameter b
    *b = temp;                                                  //parameter b is set to temp
}
template <class T>                                              //templated function
Node<T> *LastNode(DLList<T> *root) {                            //function to find the last node in list
    Node<T> *last = root->GetHead();                            //last node created and set to head of list
    while (last != NULL) {                                      //while last is not null
        if (last->next == nullptr) {                            //if the next node is null
            return last;                                        //return last
        }
        last = last->next;                                      //iterate through the list
    }
    std::cout << "There was an error :: lastNode is NULL" << std::endl;         //inform user of error
    return NULL;                                                                //return null
}
template <class T>                                                                      //templated function
Node<T>* Partition (Node<T> *nextNode, Node<T> *last) {                                 //partition function
    T temp = last->element;                                                             //temp variable set to value of last node
    Node<T> *tempNode = nextNode->previous;                                             //temp node set to the previous node of nextNode
    for (Node<T> *tempNext = nextNode; tempNext != last; tempNext = tempNext->next) {   //while tempNext is not the last node
        if (tempNext->element <= temp) {                                                //if the value of tempNext is less than or equal to temp
            tempNode = (tempNode == NULL)? nextNode : tempNode->next;                   //sets tempNode, if null, its nextNode, if not, move next
            Swap(&(tempNode->element), &(tempNext->element));                           //swap values
            
        }
    }
    tempNode = (tempNode == NULL)? nextNode : tempNode->next;                           //sets tempNode, if null, its nextNode, if not, move next
    Swap(&(tempNode->element), &(last->element));                                       //swap values
    return tempNode;                                                                    //return tempNode
}

template <class T>                                                                      //templated function
void _quickSort(DLList<T>* list, Node<T> *last)                                         //_quickSort internal function. Parameters are DLL and Node
{
    Node<T> *iteration = list->GetHead();                                               //iteration node created and set to list head
    if (last != NULL && iteration->next != last && iteration != last->next)             //if last is not null and the next node of iteration is not last node and if iteration does not equal node next to last
    {
        Node<T> *p = Partition(iteration, last);                                        //partition node created
        _quickSort(list, p->previous);                                                  //run this sort function again
        if (p->next != nullptr) {                                                       //if partition next is not null
            _quickSort(p->next, last);                                                  //run overloaded sort function
        } else {                                                                        //debug else due to sorting error
            std::cout<<"test2";
        }
    }
}
template <class T>                                                                      //templated function
void _quickSort(Node<T>* nextPart, Node<T> *last)                                       //overloaded _quickSort internal function. Parameters are Node and Node
{
    if (nextPart->next != nullptr) {                                                    //if nextPart next is not null
        if (last != NULL && nextPart->next != last && nextPart != last->next)           //if last is not null and the next node of nextPart is not last node and if nextPart does not equal node next to last
        {
            Node<T> *p = Partition(nextPart, last);                                     //partition node created
            _quickSort(nextPart, p->previous);                                          //run overloaded sort function
            if (p->next != nullptr) {                                                   //if partition next is not null
                _quickSort(p->next, last);                                              //run this sort function again
            } else {                                                                    //debug else due to sorting error
                std::cout<<"test";
            }
        }
    }
}
template <class T>                                              //templated function
void QuickSort(DLList<T> *head)                                 //main quickSort function
{
    Node<T> *last = LastNode(head);                             //find last node
    _quickSort(head, last);                                     //call the recursive QuickSort
}


int main() {
    char menu = ' ';                                    //menu variable
    DLList<int> *intList = new DLList<int>();           //list
    DLList<int> *testList = new DLList<int>();          //test list
    int value;                                          //input value
    char foo;                                           //junk value
    int testFoo;                                        //test value
    
    while (menu != '0') {                                                                               //while menu is not 0
        std::cout << std::endl << "~~~~~~~~~~ MENU ~~~~~~~~~~" << std::endl;                            //display menu options
        std::cout << "1 - Insert number" << std::endl;
        std::cout << "2 - Insert from file" << std::endl;
        std::cout << "3 - Remove number" << std::endl;
        std::cout << "4 - View list" << std::endl;
        std::cout << "5 - Find number" << std::endl;
        std::cout << "6 - Insertion Sort" <<std::endl;
        std::cout << "7 - QuickSort(WIP, has 1 known bug)" <<std::endl;
        std::cout << "8 - Run Test" <<std::endl;
        std::cout << "0 - Quit program" << std::endl;
        std::cout << "Please enter a command: ";
        std::cin >> menu;                                                                               //menu input
        switch (menu) {                                                                                 //menu switch statement
            case '0':                                                                                   //case 0 - exit program
                break;                                                                                  //break case
            case '1':                                                                                   //case 1 - insert value
                std::cout << "\nInsert an int: ";
                std::cin >> value;                                                                      //user input
                intList->Insert(value);                                                                 //insert value to list
                break;                                                                                  //break case
            case '2': {                                                                                 //case 2 - insert from file
                char importMenu = ' ';
                
                while (importMenu != '0') {
                    std::cout << std::endl << "~~~~~~~~~~ IMPORT MENU ~~~~~~~~~~" << std::endl;         //display file input menu options
                    std::cout << "1 - Insert num10.dat" << std::endl;
                    std::cout << "2 - Insert num100.dat" << std::endl;
                    std::cout << "3 - Insert num1000.dat" << std::endl;
                    std::cout << "4 - Insert num10000.dat" << std::endl;
                    std::cout << "5 - Insert num100000.dat" << std::endl;
                    std::cout << "6 - Insert num1000000.dat" <<std::endl;
                    std::cout << "7 - Insert listImport.dat" <<std::endl;
                    std::cout << "0 - Exit Import" << std::endl;
                    std::cout << "Please enter a command: ";
                    std::cin >> importMenu;                                                             //menu input
                    switch (importMenu) {                                                               //menu switch statement
                        case '0':                                                                       //case 0 - exit program
                            break;                                                                      //break case
                        case '1': {                                                                     //case 1 - import num10.dat
                            std::ifstream fileIn ("num10.dat");                                         //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '2': {                                                                     //case 2 - import num100.dat
                            std::ifstream fileIn ("num100.dat");                                        //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '3': {                                                                     //case 3 - import num1000.dat
                            std::ifstream fileIn ("num1000.dat");                                       //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '4': {                                                                     //case 4 - import num10000.dat
                            std::ifstream fileIn ("num10000.dat");                                      //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '5': {                                                                     //case 5 - import num10000.dat
                            std::ifstream fileIn ("num100000.dat");                                     //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '6': {                                                                     //case 6 - import num1000000.dat
                            std::ifstream fileIn ("num1000000.dat");                                    //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        case '7': {                                                                     //case 7 - import listImport.dat (custom list for user)
                            std::ifstream fileIn ("listImport.dat");                                    //open file for data import
                            std::string line;                                                           //string variable
                            if (fileIn.is_open()) {                                                     //if the file is open
                                while (std::getline(fileIn, line)) {                                    //while getline recives data
                                    value = std::stoi(line);                                            //convert string to int
                                    intList->Insert(value);                                             //insert value to list
                                }
                                fileIn.close();                                                         //close file
                            }
                            importMenu = '0';                                                           //exit import switch
                            break;                                                                      //break case
                        }
                        default:                                                                        //default case
                            std::cout << "\nInvalid input" << std::endl;                                //inform user of invalid input
                            break;
                    }
                }
                break;                                                                                  //break case
            }
            case '3': {                                                                                 //case 3 - remove value
                std::cout << "\nWhat int do you wish to remove: ";
                std::cin >> value;                                                                      //user input
                Node<int> *tempFind = intList->Find(value);                                             //create a temp variable set to address of value to remove
                if (tempFind == NULL) {                                                                 //if temp value is null
                    std::cout << "\nThe value was not found or the list is empty" << std::endl;         //inform user value was not found
                }
                else {                                                                                  //if temp value is not null
                    if (intList->Delete(tempFind)) {                                                    //run delete, if return true:
                        std::cout << "\nThe int was removed" << std::endl;                              //inform user value was removed
                    }
                    else {                                                                              //if delete returns false
                        std::cout << "\nERROR" << std::endl;                                            //inform user of error
                    }
                }
                break;                                                                                  //break case
            }
            case '4':                                                                                   //case 4 - display list
                if (intList->isEmpty()) {                                                               //if list is empty
                    std::cout << "\nList is empty" << std::endl;                                        //inform user
                }
                else {                                                                                  //if list contains data
                    Iterator<int> *i = intList->getItHead();                                            //create iterator set to head
                    Node<int> *list;                                                                    //create node pointer
                    std::cout <<"\nYour list consists of:"<< std::endl;
                    while ((list = i->nextNode()) != NULL) {                                            //while there is soemthing next in the list
                        std::cout << list->element << std::endl;                                        //display list
                    }
                    delete i;                                                                           //delete iterator
                    delete list;                                                                        //delete list
                }
                break;                                                                                  //break case
            case '5': {                                                                                 //case 5 - find address for value
                std::cout << "\nWhat int do you wish to find: ";
                std::cin >> value;                                                                      //user input
                Node<int> *found = intList->Find(value);                                                //create found node, run find function
                if (found != NULL) {                                                                    //if found node is not null
                    std::cout << "The address for " << value << " is: " << found << std::endl;          //inform user of data
                }
                break;                                                                                  //break case
            }
            case '6': {                                                                                                                                                                                 //case 6 - Insertion Sorting
                auto startTime = std::chrono::high_resolution_clock::now();                                                                                                                             //store start time
                intList->InsertionSort();                                                                                                                                                               //sort using insertion method
                auto currentTime = std::chrono::high_resolution_clock::now();                                                                                                                           //store time after sort
                std::cout << "\nList was sorted by insertion method in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - startTime).count() << " nanoseconds" << std::endl;      //display time it took for sort function to run
                break;                                                                                                                                                                                  //break case
            }
            case '7': {                                                                                                                                                                                 //case 7 - QuickSort
                auto startTime = std::chrono::high_resolution_clock::now();                                                                                                                             //store start time
                QuickSort(intList);                                                                                                                                                                     //sort using QuickSort
                auto currentTime = std::chrono::high_resolution_clock::now();                                                                                                                           //store time after sort
                std::cout << "\nList was sorted by insertion method in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - startTime).count() << " nanoseconds" << std::endl;      //display time it took for sort function to run
                break;                                                                                                                                                                                  //break case
            }
            case '8': {                                                                                 //case 6 - testing
                assert (testList->isEmpty() == true);                                                   //assert that test list is empty
                std::cout << "\nConstructor working successfully" << std::endl;
                testFoo = 2;                                                                            //set testFoo to 2
                std::cout << "\nInserting '2' to test list\n";
                testList->Insert(testFoo);                                                              //insert testFoo
                testFoo = 4;                                                                            //set testFoo to 4
                std::cout << "Inserting '4' to test list\n";
                testList->Insert(testFoo);                                                              //insert testFoo
                testFoo = 6;                                                                            //set testFoo to 6
                std::cout << "Inserting '6' to test list\n";
                testList->Insert(testFoo);                                                              //insert testFoo
                testFoo = 8;                                                                            //set testFoo to 8
                std::cout << "Inserting '8' to test list\n";
                testList->Insert(testFoo);                                                              //insert testFoo
                testFoo = 10;                                                                           //set testFoo to 10
                std::cout << "Inserting '10' to test list\n";
                testList->Insert(testFoo);                                                              //insert testFoo
                assert (testList->isEmpty() == false);                                                  //assert that test list is not empty
                std::cout << "Insert working successfully\n" << std::endl;
                std::cout << "Displaying full list: ";
                Iterator<int> *i = testList->getItHead();                                           //create iterator set to head
                Node<int> *list;                                                                    //create node pointer
                std::cout <<"\nYour list consists of:"<< std::endl;
                while ((list = i->nextNode()) != NULL) {                                            //while there is soemthing next in the list
                    std::cout << list->element << std::endl;                                        //display list
                }
                delete i;                                                                           //delete iterator
                delete list;                                                                        //delete list
                std::cout << "\nRemoving head, tail, and middle of list:";
                testFoo = 2;
                Node<int> *tempFindTest = testList->Find(testFoo);                                      //create a temp variable set to address of value to remove
                if (tempFindTest == NULL) {                                                             //if temp value is null
                    std::cout << "\nThe value was not found or the list is empty" << std::endl;         //inform user value was not found
                }
                else {                                                                                  //if temp value is not null
                    if (testList->Delete(tempFindTest)) {                                               //run delete, if return true:
                        std::cout << "\nThe head was removed sucessfully" << std::endl;                 //inform user value was removed
                    }
                    else {                                                                              //if delete returns false
                        std::cout << "\nERROR" << std::endl;                                            //inform user of error
                    }
                }
                testFoo = 10;
                Node<int> *temp2FindTest = testList->Find(testFoo);                                     //create a temp variable set to address of value to remove
                if (temp2FindTest == NULL) {                                                            //if temp value is null
                    std::cout << "\nThe value was not found or the list is empty" << std::endl;         //inform user value was not found
                }
                else {                                                                                  //if temp value is not null
                    if (testList->Delete(temp2FindTest)) {                                              //run delete, if return true:
                        std::cout << "The tail was removed sucessfully" << std::endl;                   //inform user value was removed
                    }
                    else {                                                                              //if delete returns false
                        std::cout << "\nERROR" << std::endl;                                            //inform user of error
                    }
                }
                testFoo = 6;
                Node<int> *temp3FindTest = testList->Find(testFoo);                                     //create a temp variable set to address of value to remove
                if (temp3FindTest == NULL) {                                                            //if temp value is null
                    std::cout << "\nThe value was not found or the list is empty" << std::endl;         //inform user value was not found
                }
                else {                                                                                  //if temp value is not null
                    if (testList->Delete(temp3FindTest)) {                                              //run delete, if return true:
                        std::cout << "The middle was removed sucessfully" << std::endl;                 //inform user value was removed
                    }
                    else {                                                                              //if delete returns false
                        std::cout << "\nERROR" << std::endl;                                            //inform user of error
                    }
                }
                std::cout << "\nDisplaying full list: ";
                Iterator<int> *i2 = testList->getItHead();                                           //create iterator set to head
                Node<int> *list2;                                                                    //create node pointer
                std::cout <<"\nYour list consists of:"<< std::endl;
                while ((list2 = i2->nextNode()) != NULL) {                                           //while there is soemthing next in the list
                    std::cout << list2->element << std::endl;                                        //display list
                }
                delete i2;                                                                           //delete iterator2
                delete list2;                                                                        //delete list2
                
                break;
            }
            default:                                                                                    //default case - if user enters invalid input
                std::cout << "\nInvalid input" << std::endl;                                            //inform user of invalid input
                break;                                                                                  //break case
        }
    }
    std::cout << "\nThanks for using this program" << std::endl << std::endl;                           //thank user for using program
    std::cout << "Please enter a character to exit: ";                                                  //inform user to enter a value to exit
    std::cin>>foo;                                                                                      //user input to exit
    return 0;
}


