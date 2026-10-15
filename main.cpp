#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <chrono>

using namespace std;

// --- 1. ENTITY MODEL ---
struct Book {
    string isbn;
    string title;
    string author;
    string category;
    bool isBorrowed;
    string patronId;
    string dueDate;

    Book() : isbn(""), title(""), author(""), category("General"), isBorrowed(false), patronId("N/A"), dueDate("N/A") {}
    Book(string id, string t, string auth, string cat)
        : isbn(id), title(t), author(auth), category(cat), isBorrowed(false), patronId("N/A"), dueDate("N/A") {}
};

// --- 2. LINKED LIST ENGINE ---
struct Node {
    Book data;
    Node* next;
    Node(Book b) : data(b), next(nullptr) {}
};

class LinkedListEngine {
private:
    Node* head;
    int size;
public:
    LinkedListEngine() : head(nullptr), size(0) {}
    ~LinkedListEngine() { clear(); }

    bool isEmpty() const { return head == nullptr; }
    int getSize() const { return size; }

    void insertAtTail(const Book& book) {
        Node* newNode = new Node(book);
        if (isEmpty()) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) current = current->next;
            current->next = newNode;
        }
        size++;
    }

    bool deleteByISBN(const string& isbn) {
        if (isEmpty()) return false;
        if (head->data.isbn == isbn) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->data.isbn != isbn) {
            current = current->next;
        }
        if (current->next == nullptr) return false;
        Node* target = current->next;
        current->next = target->next;
        delete target;
        size--;
        return true;
    }

    bool updateBook(const string& isbn, const string& newTitle, const string& newAuthor, const string& newCategory) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.isbn == isbn) {
                current->data.title = newTitle;
                current->data.author = newAuthor;
                current->data.category = newCategory;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void displayCatalog() const {
        if (isEmpty()) {
            cout << "\n[Catalog is currently empty.]\n";
            return;
        }
        cout << "\n=========================================================================\n";
        cout << "                        LIBRARY BOOK CATALOG                             \n";
        cout << "=========================================================================\n";
        cout << left << setw(12) << "ISBN" << setw(22) << "Title" << setw(18) << "Author" << setw(15) << "Category" << setw(10) << "Status" << "\n";
        cout << "-------------------------------------------------------------------------\n";
        Node* current = head;
        while (current != nullptr) {
            cout << left << setw(12) << current->data.isbn
                      << setw(22) << current->data.title
                      << setw(18) << current->data.author
                      << setw(15) << current->data.category
                      << setw(10) << (current->data.isBorrowed ? "Borrowed" : "Available") << "\n";
            current = current->next;
        }
        cout << "=========================================================================\n";
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        size = 0;
    }

    Book* toDynamicArray() const {
        if (isEmpty()) return nullptr;
        Book* arr = new Book[size];
        Node* current = head;
        int i = 0;
        while (current != nullptr) {
            arr[i++] = current->data;
            current = current->next;
        }
        return arr;
    }
};

// --- 3. STACK ENGINE ---
struct StackNode {
    Book data;
    StackNode* next;
    StackNode(Book b) : data(b), next(nullptr) {}
};

class StackEngine {
private:
    StackNode* topNode;
public:
    StackEngine() : topNode(nullptr) {}
    ~StackEngine() { clear(); }

    bool isEmpty() const { return topNode == nullptr; }

    void push(const Book& book) {
        StackNode* newNode = new StackNode(book);
        newNode->next = topNode;
        topNode = newNode;
    }

    Book pop() {
        if (isEmpty()) {
            cout << "\n[Error: Stack Underflow! No returned books to process.]\n";
            return Book();
        }
        StackNode* temp = topNode;
        Book poppedBook = temp->data;
        topNode = topNode->next;
        delete temp;
        return poppedBook;
    }

    void displayStack() const {
        if (isEmpty()) {
            cout << "\n[Return Drop Stack is empty.]\n";
            return;
        }
        cout << "\n=========================================================================\n";
        cout << "                     RECENTLY RETURNED BOOKS (LIFO STACK)                \n";
        cout << "=========================================================================\n";
        cout << left << setw(12) << "ISBN" << setw(25) << "Title" << setw(20) << "Patron ID" << "\n";
        cout << "-------------------------------------------------------------------------\n";
        StackNode* current = topNode;
        while (current != nullptr) {
            cout << left << setw(12) << current->data.isbn << setw(25) << current->data.title << setw(20) << current->data.patronId << "\n";
            current = current->next;
        }
        cout << "=========================================================================\n";
    }

    void clear() {
        while (!isEmpty()) pop();
    }
};

// --- 4. QUEUE ENGINE ---
struct QueueNode {
    string patronId;
    string isbn;
    string requestDate;
    QueueNode* next;
    QueueNode(string pId, string bIsbn, string date) : patronId(pId), isbn(bIsbn), requestDate(date), next(nullptr) {}
};

class QueueEngine {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
public:
    QueueEngine() : frontNode(nullptr), rearNode(nullptr) {}
    ~QueueEngine() { clear(); }

    bool isEmpty() const { return frontNode == nullptr; }

    void enqueue(string patronId, string isbn, string date) {
        QueueNode* newNode = new QueueNode(patronId, isbn, date);
        if (isEmpty()) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "\n[Error: Queue Underflow! No active reservations in line.]\n";
            return;
        }
        QueueNode* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "\n[Reservation Queue is currently empty.]\n";
            return;
        }
        cout << "\n=========================================================================\n";
        cout << "                   BOOK RESERVATION QUEUE (FIFO LINE)                    \n";
        cout << "=========================================================================\n";
        cout << left << setw(18) << "Patron ID" << setw(15) << "Book ISBN" << setw(20) << "Request Date" << "\n";
        cout << "-------------------------------------------------------------------------\n";
        QueueNode* current = frontNode;
        while (current != nullptr) {
            cout << left << setw(18) << current->patronId << setw(15) << current->isbn << setw(20) << current->requestDate << "\n";
            current = current->next;
        }
        cout << "=========================================================================\n";
    }

    void clear() {
        while (!isEmpty()) dequeue();
    }
};

// --- 5. SEARCH & SORT ENGINE ---
class SearchSortEngine {
public:
    static int linearSearch(const Book arr[], int n, string targetISBN, long long& comparisons) {
        comparisons = 0;
        for (int i = 0; i < n; i++) {
            comparisons++;
            if (arr[i].isbn == targetISBN) return i;
        }
        return -1;
    }

    static int binarySearch(const Book arr[], int n, string targetISBN, long long& comparisons) {
        comparisons = 0;
        int low = 0, high = n - 1;
        while (low <= high) {
            comparisons++;
            int mid = low + (high - low) / 2;
            if (arr[mid].isbn == targetISBN) return mid;
            if (arr[mid].isbn < targetISBN) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    static void bubbleSort(Book arr[], int n, long long& comparisons, long long& swaps) {
        comparisons = 0; swaps = 0;
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                comparisons++;
                if (arr[j].isbn > arr[j + 1].isbn) {
                    Book temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
                    swaps++; swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    static void selectionSort(Book arr[], int n, long long& comparisons, long long& swaps) {
        comparisons = 0; swaps = 0;
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                comparisons++;
                if (arr[j].isbn < arr[minIdx].isbn) minIdx = j;
            }
            if (minIdx != i) {
                Book temp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = temp;
                swaps++;
            }
        }
    }

    static void insertionSort(Book arr[], int n, long long& comparisons, long long& swaps) {
        comparisons = 0; swaps = 0;
        for (int i = 1; i < n; i++) {
            Book key = arr[i];
            int j = i - 1;
            while (j >= 0) {
                comparisons++;
                if (arr[j].isbn > key.isbn) {
                    arr[j + 1] = arr[j]; swaps++; j--;
                } else break;
            }
            arr[j + 1] = key;
        }
    }
};

// --- 6. BENCHMARKING SUITE ---
class BenchmarkingSuite {
public:
    static void runBenchmarkSuite() {
        int testSizes[] = {100, 1000, 10000, 50000};
        cout << "\n=========================================================================================================\n";
        cout << "                                  AUTOMATED BENCHMARKING SUITE REPORT                                    \n";
        cout << "=========================================================================================================\n";
        cout << left << setw(18) << "Algorithm" << setw(12) << "Size (N)" << setw(16) << "Comparisons" << setw(14) << "Swaps" << setw(18) << "Time (ms)" << setw(12) << "Big-O" << "\n";
        cout << "---------------------------------------------------------------------------------------------------------\n";

        for (int s = 0; s < 4; s++) {
            int n = testSizes[s];
            Book* originalData = new Book[n];
            for (int i = 0; i < n; i++) originalData[i] = Book("ISBN" + to_string(n - i), "Title", "Author", "Gen");

            // Bubble Sort
            {
                Book* workArr = new Book[n];
                for (int i = 0; i < n; i++) workArr[i] = originalData[i];
                long long c = 0, sw = 0;
                auto start = chrono::high_resolution_clock::now();
                SearchSortEngine::bubbleSort(workArr, n, c, sw);
                auto end = chrono::high_resolution_clock::now();
                double el = chrono::duration<double, milli>(end - start).count();
                cout << left << setw(18) << "Bubble Sort" << setw(12) << n << setw(16) << c << setw(14) << sw << setw(18) << fixed << setprecision(3) << el << setw(12) << "O(n^2)" << "\n";
                delete[] workArr;
            }
            // Selection Sort
            {
                Book* workArr = new Book[n];
                for (int i = 0; i < n; i++) workArr[i] = originalData[i];
                long long c = 0, sw = 0;
                auto start = chrono::high_resolution_clock::now();
                SearchSortEngine::selectionSort(workArr, n, c, sw);
                auto end = chrono::high_resolution_clock::now();
                double el = chrono::duration<double, milli>(end - start).count();
                cout << left << setw(18) << "Selection Sort" << setw(12) << n << setw(16) << c << setw(14) << sw << setw(18) << fixed << setprecision(3) << el << setw(12) << "O(n^2)" << "\n";
                delete[] workArr;
            }
            // Insertion Sort
            {
                Book* workArr = new Book[n];
                for (int i = 0; i < n; i++) workArr[i] = originalData[i];
                long long c = 0, sw = 0;
                auto start = chrono::high_resolution_clock::now();
                SearchSortEngine::insertionSort(workArr, n, c, sw);
                auto end = chrono::high_resolution_clock::now();
                double el = chrono::duration<double, milli>(end - start).count();
                cout << left << setw(18) << "Insertion Sort" << setw(12) << n << setw(16) << c << setw(14) << sw << setw(18) << fixed << setprecision(3) << el << setw(12) << "O(n^2)" << "\n";
                delete[] workArr;
            }
            delete[] originalData;
            cout << "---------------------------------------------------------------------------------------------------------\n";
        }
    }
};

// --- 7. MAIN CONTROLLER ---
int main() {
    LinkedListEngine catalog;
    StackEngine returnStack;
    QueueEngine reservationQueue;
    int choice = 0;

    do {
        cout << "\n=========================================================================\n";
        cout << "            SMART LIBRARY TRANSACTION & ARCHIVAL SYSTEM                  \n";
        cout << "=========================================================================\n";
        cout << " [1] Add Book (Catalog)\n [2] Delete Book by ISBN\n [3] Update Book Details\n [4] Display Catalog\n";
        cout << " [5] Search Book (Linear vs Binary)\n [6] Enqueue Reservation\n [7] Process Reservation\n";
        cout << " [8] Push Returned Book\n [9] Process Returned Book\n [10] Run Benchmark Suite\n [11] Exit\n";
        cout << "=========================================================================\n";
        cout << "Enter choice (1-11): ";

        if (!(cin >> choice)) {
            cout << "\n[Error: Invalid input type.]\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                string isbn, title, author, category;
                cout << "ISBN: "; cin >> isbn;
                cout << "Title: "; cin >> title;
                cout << "Author: "; cin >> author;
                cout << "Category: "; cin >> category;
                catalog.insertAtTail(Book(isbn, title, author, category));
                cout << "[Success: Book added.]\n";
                break;
            }
            case 2: {
                string isbn; cout << "ISBN to delete: "; cin >> isbn;
                if (catalog.deleteByISBN(isbn)) cout << "[Success: Deleted.]\n";
                else cout << "[Error: Not found.]\n";
                break;
            }
            case 3: {
                string isbn, title, author, category;
                cout << "ISBN to update: "; cin >> isbn;
                cout << "New Title: "; cin >> title;
                cout << "New Author: "; cin >> author;
                cout << "New Category: "; cin >> category;
                if (catalog.updateBook(isbn, title, author, category)) cout << "[Success: Updated.]\n";
                else cout << "[Error: Not found.]\n";
                break;
            }
            case 4:
                catalog.displayCatalog();
                break;
            case 5: {
                if (catalog.isEmpty()) { cout << "[Catalog empty.]\n"; break; }
                string target; cout << "Target ISBN: "; cin >> target;
                int n = catalog.getSize();
                Book* arr = catalog.toDynamicArray();
                long long lc = 0, bc = 0;
                int lIdx = SearchSortEngine::linearSearch(arr, n, target, lc);
                long long d1 = 0, d2 = 0;
                SearchSortEngine::insertionSort(arr, n, d1, d2);
                int bIdx = SearchSortEngine::binarySearch(arr, n, target, bc);
                cout << "Linear Search: " << (lIdx != -1 ? "Found" : "Not Found") << " (Comps: " << lc << ")\n";
                cout << "Binary Search: " << (bIdx != -1 ? "Found" : "Not Found") << " (Comps: " << bc << ")\n";
                delete[] arr;
                break;
            }
            case 6: {
                string pId, isbn, date;
                cout << "Patron ID: "; cin >> pId;
                cout << "ISBN: "; cin >> isbn;
                cout << "Date: "; cin >> date;
                reservationQueue.enqueue(pId, isbn, date);
                reservationQueue.displayQueue();
                break;
            }
            case 7:
                reservationQueue.dequeue();
                reservationQueue.displayQueue();
                break;
            case 8: {
                string isbn, title, pId;
                cout << "ISBN: "; cin >> isbn;
                cout << "Title: "; cin >> title;
                cout << "Patron ID: "; cin >> pId;
                Book b(isbn, title, "Unknown", "General");
                b.patronId = pId;
                returnStack.push(b);
                returnStack.displayStack();
                break;
            }
            case 9:
                returnStack.pop();
                returnStack.displayStack();
                break;
            case 10:
                BenchmarkingSuite::runBenchmarkSuite();
                break;
            case 11:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 11);

    return 0;
}
