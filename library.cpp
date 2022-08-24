#include "library.h"
#include <iostream>

using namespace std;

static const int MAX = 10;
string books[MAX]; // NOLINT - need to use static storage duration
int filledSize = 0;
const string NULL_BOOK{"NULL_Book"}; // NOLINT - same as above

ostream &operator<<(ostream &out, const Library &lib) {
  out << "[";
  for (int i = 0; i < lib.size(); i++) {
    out << lib.at(i);
    if (i < lib.size() - 1) {
      out << ", ";
    }
  }
  out << "]";
  return out;
}

// Use the compiler generated constructor
Library::Library() = default;

// Return size
int Library::size() const { return filledSize; }

// Return maximum size
int Library::max_size() const { return MAX; }

// Test whether Library is empty
bool Library::empty() const { return filledSize == 0; }

// Access element
const string &Library::at(int n) const {
  if (n > -1 && n < MAX) {
    if (n < filledSize) {
      return books[n];
    }
    cerr << "illegal exception 1"
         << "\nerror: no book at location " << n << endl;
    return NULL_BOOK;
  }
  cerr << "illegal exception 2"
       << "\nerror: invalid location " << n
       << " is either less than zero or equal to or greater than the max size "
          "of "
       << MAX << endl;
  return NULL_BOOK;
}

// Access first element
const string &Library::front() const {
  if (filledSize == 0) {
    cerr << "illegal exception 3\nerror: library is empty\n";
    return NULL_BOOK;
  }
  return books[0];
}

// Access last element (public member function )
const string &Library::back() const {
  if (filledSize > 0) {
    return books[filledSize - 1];
  }
  cerr << "illegal exception 4\nerror: library is empty\n";
  return NULL_BOOK;
}

// Add element at the end
void Library::push_back(const string &book) {
  if (filledSize < MAX) {
    books[filledSize] = book;
    filledSize++;
  } else {
    cerr << "illegal exception 5"
         << "\nerror: library is full, so book " << book
         << " cannot be inserted\n";
  }
}

// Delete last
void Library::pop_back() {
  if (filledSize > 0) {
    books[filledSize - 1] = "";
    filledSize--;
  } else {
    cerr << "illegal exception 6\nerror: library is empty\n";
  }
}

// Erase element at location
void Library::erase(int n) {
  if (n > -1 && n < MAX) {
    if (n == filledSize - 1) {
      return pop_back();
    }
    if (n < filledSize - 1) {
      filledSize--;
      string temp;
      books[n] = "";
      for (int i = n; i < filledSize; i++) {
        books[i] = temp;
        temp = books[i];
        books[i] = books[i + 1];
      }
      books[filledSize] = "";
      for (int i = 0; i < filledSize; i++) {
        cout << i << ": " << books[i] << endl;
      }
    } else {
      cerr << "illegal exception 7"
           << "\nerror: no book at location " << n << endl;
    }
  } else {
    cerr << "illegal exception 8"
         << "\nerror: invalid location " << n
         << " is either less than zero or equal to or greater than the max "
            "size of "
         << MAX << endl;
  }
}

// Insert element at location, moves other elements as needed
void Library::insertAt(int n, const string &book) {
  if (n > -1 && n < MAX) {
    if (filledSize < MAX) {
      if (n == filledSize) {
        return push_back(book);
      }
      if (n < filledSize) {
        filledSize++;
        string temp;
        for (int i = filledSize - 1; i > n; i--) {
          books[i] = temp;
          temp = books[i];
          books[i] = books[i - 1];
        }
        books[n] = book;
      } else {
        cerr << "illegal exception 9"
             << "\nerror: size " << filledSize
             << " is greater than the max size of " << MAX << ", so book "
             << book << " cannot be inserted in location " << n << endl;
      }
    } else {
      cerr << "illegal exception 10"
           << "\nerror: location " << n << " is out of bounds, so book " << book
           << " cannot be inserted\n";
    }
  } else {
    cerr << "illegal exception 11"
         << "\nerror: invalid location " << n
         << " is either less than zero or equal to or greater than the max "
            "size of "
         << MAX << ", so book " << book << " cannot be inserted" << endl;
  }
};