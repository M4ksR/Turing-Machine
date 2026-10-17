#include "turingmachine.h"

unsigned long long TuringMachine::calc(Tape& tape,
                                       unsigned long long maxsteps) {
  unsigned long long counter = 0;
  while (counter < maxsteps) {
    char sym = tape[pos];
    Command com = prog.get(curr_state, sym);
    if (!com.iscreated()) {
      return counter;
    }
    tape[pos] = com.getNewSym();
    curr_state = com.getNewState();
    if (com.getmove() == 'R') {
      pos = (pos + 1) % tape.getsize();
    }
    if (com.getmove() == 'L') {
      pos = (pos - 1 + tape.getsize()) % tape.getsize();
    }
    ++counter;
  }
  if (!prog.get(curr_state, tape[pos]).iscreated()) {
    return counter;
  }
  return maxsteps + 1;
}
