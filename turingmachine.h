#pragma once

#include "src.h"

class TuringMachine {
 private:
  Programm& prog;
  State curr_state;
  size_t pos;

 public:
  TuringMachine(Programm& p) : prog(p), curr_state(p.getstate()), pos(0) {}

  unsigned long long calc(Tape&, unsigned long long);
  size_t getpos() const { return pos; }
};
