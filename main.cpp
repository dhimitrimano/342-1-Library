
#include "library.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

// forward delaration, defined in library-commands.cpp
void execute_commands(const string &filename);

void test1() {
  Library lib;
  stringstream ss;
  // NOLINTNEXTLINE - would normally use empty
  assert(lib.size() == 0);
  assert(lib.empty());
  ss << lib;
  assert(ss.str() == "[]");
  cout << "test1 complete" << endl;
}

void test2() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  assert(lib.size() == 1);
  assert(!lib.empty());
  assert(lib.at(0) == "Ulysses");
  assert(lib.front() == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Ulysses]");
  cout << "test2 complete" << endl;
}

void test3() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  lib.push_back("Gatsby");
  assert(lib.size() == 2);
  assert(lib.at(0) == lib.front());
  assert(lib.at(1) == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Ulysses, Gatsby]");

  lib.erase(0);
  assert(lib.front() == lib.back());
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Gatsby]");
  cout << "test3 complete" << endl;
}

void test4() {
  Library lib;
  stringstream ss;
  lib.push_back("Ulysses");
  lib.push_back("Gatsby");
  lib.insertAt(lib.size(), "Harry Potter");
  lib.insertAt(0, "Don Quixote");
  ss << lib;
  assert(ss.str() == "[Don Quixote, Ulysses, Gatsby, Harry Potter]");
  lib.erase(1);
  ss.str("");
  ss << lib;
  assert(ss.str() == "[Don Quixote, Gatsby, Harry Potter]");
  cout << "test4 complete" << endl;
}

void test5() {
  // assuming max_size() = 10
  Library lib;
  lib.size();
  stringstream ss;
  for (int i = 0; i < lib.max_size() - 1; i++) {
    lib.push_back("book " + to_string(i + 1));
  }
  lib.push_back("final book");
  cout << lib.size() << endl;
  lib.push_back("missingbk");
  ss.str("");
  ss << lib;
  assert(ss.str() == "[book 1, book 2, book 3, book 4, book 5, book 6, book 7, "
                     "book 8, book 9, final book]");
  lib.insertAt(7, "book -2");
  lib.erase(2);
  lib.at(9);
  lib.at(-1);
  lib.insertAt(7, "book -2");
  ss.str("");
  ss << lib;
  assert(ss.str() == "[book 1, book 2, book 4, book 5, book 6, book 7, book 8, "
                     "book -2, book 9, final book]");
  lib.erase(9);
  lib.insertAt(9, "vinyl booke");
  ss.str("");
  ss << lib;
  assert(ss.str() == "[book 1, book 2, book 4, book 5, book 6, book 7, book 8, "
                     "book -2, book 9, vinyl booke]");
  lib.erase(0);
  lib.insertAt(0, "the book");
  ss.str("");
  ss << lib;
  assert(ss.str() == "[the book, book 2, book 4, book 5, book 6, book 7, book "
                     "8, book -2, book 9, vinyl booke]");
  lib.erase(14);
  lib.insertAt(-4, "book at -4");

  cout << "test5 complete" << endl;
}

int main(int argc, char *argv[]) {
  test1();
  test2();
  test3();
  test4();
  test5();
  if (argc >= 1) {
    for (int i = 1; i < argc; ++i) {
      string commandFile = argv[i];
      cout << "*** Executing commands from " << commandFile << endl;
      execute_commands(commandFile);
    }
  }
  cout << "Done." << endl;
}
