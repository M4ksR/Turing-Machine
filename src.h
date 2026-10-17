#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class State {
 private:
  char name[16];  // название состояния
 public:
  State() { name[0] = '\0'; }
  State(const std::string& n);

  //геттеры
  const char* getname() const { return name; }

  // операторы
  bool operator==(const State& other) const;
  bool operator!=(const State& other) const;
};

class Command {
 private:
  State curr_state;  // текущее состояние
  char curr_symbol;  // текущий символ
  State new_state;   // новое состояние
  char new_symbol;   // новый символ
  char move;         // переход L R N
  bool created;      // существование объекта

 public:
  Command() : curr_symbol('0'), new_symbol('0'), move('N'), created(false) {}
  Command(const State& currS, char currN, const State& newS, char newN, char m)
      : curr_state(currS),
        curr_symbol(currN),
        new_state(newS),
        new_symbol(newN),
        move(m),
        created(true) {}

  // геттеры
  const State& getCurrState() const { return curr_state; }
  const State& getNewState() const { return new_state; }
  char getCurrSym() const { return curr_symbol; }
  char getNewSym() const { return new_symbol; }
  char getmove() const { return move; }
  bool iscreated() const { return created; }
};

class Programm {
 private:
  Command* list;    // список команд
  size_t size;      // количество команд
  size_t capasity;  // выделенный объем

  void swap(Programm&) noexcept;

 public:
  Programm() : list(nullptr), size(0), capasity(0) {}
  Programm(const char* filename);
  Programm(Programm&& other) noexcept;
  ~Programm() { delete[] list; }

  // геттеры
  size_t getsize() const { return size; }
  size_t getcapasity() const { return capasity; }
  const State& getstate() const { return list[0].getCurrState(); }
  Command get(const State& state, char sym) const;

  // операторы
  Programm& operator=(Programm&& other) noexcept {
    swap(other);
    return *this;
  }
};

class Tape {
 private:
  char* tape;       // лента
  size_t TapeSize;  // размер ленты

  void swap(Tape&) noexcept;

 public:
  Tape(size_t size, const char str[]);
  ~Tape() { delete[] tape; }

  Tape(const Tape& other);
  Tape(Tape&& other) noexcept;
  Tape& operator=(const Tape& other);
  Tape& operator=(Tape&& other) noexcept;

  // геттеры
  size_t getsize() const { return TapeSize; }
  void print(size_t pos) const;

  // операторы
  char& operator[](size_t index) { return tape[index % TapeSize]; }
  const char& operator[](size_t index) const { return tape[index % TapeSize]; }
};
