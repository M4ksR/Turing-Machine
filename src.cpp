#include "src.h"

State::State(const std::string& n) {
  if (n.size() > 15) {
    throw std::invalid_argument("Error: invalid programm");
  }
  std::strncpy(name, n.c_str(), 15);
  name[15] = '\0';
}

bool State::operator==(const State& other) const {
  return std::strcmp(name, other.name) == 0;
}
bool State::operator!=(const State& other) const { return !(*this == other); }

Programm::Programm(const char* filename)
    : list(nullptr), size(0), capasity(20) {
  std::ifstream fin(filename);
  if (!fin) {
    throw std::runtime_error("Can not open file");
  }

  list = new Command[capasity];
  std::string str;
  while (getline(fin, str)) {
    size_t pos = str.find("->");

    if (pos == std::string::npos) {
      fin.close();
      delete[] list;
      throw std::invalid_argument("Error: invalid programm");
    }

    str.replace(pos, 2, " ");
    std::istringstream input(str);

    if (size == capasity) {
      Command* new_list = new Command[capasity * 2];

      for (size_t i = 0; i < size; ++i) {
        new_list[i] = list[i];
      }

      delete[] list;
      list = new_list;
      capasity <<= 1;
    }

    std::string OldState;
    char OldSym;
    std::string NewState;
    char NewSym;
    char CurrMove;

    input >> OldState >> OldSym >> NewState >> NewSym >> CurrMove;

    if ((OldSym != '0' && OldSym != '1') || (NewSym != '0' && NewSym != '1')) {
      fin.close();
      delete[] list;
      throw std::invalid_argument("Error: invalid programm");
    }

    if (CurrMove != 'L' && CurrMove != 'R' && CurrMove != 'N') {
      fin.close();
      delete[] list;
      throw std::invalid_argument("Error: invalid programm");
    }

    for (size_t i = 0; i < size; ++i) {
      if (list[i].getCurrState() == OldState &&
          list[i].getCurrSym() == OldSym) {
        fin.close();
        delete[] list;
        throw std::invalid_argument("Error: invalid programm");
      }
    }

    list[size++] = Command(OldState, OldSym, NewState, NewSym, CurrMove);
  }
  fin.close();
}

Programm::Programm(Programm&& other) noexcept
    : list(other.list), size(other.size), capasity(other.capasity) {
  other.list = nullptr;
  other.size = 0;
  other.capasity = 0;
}

Command Programm::get(const State& state, char sym) const {
  for (size_t i = 0; i < size; ++i) {
    if (state == list[i].getCurrState() && sym == list[i].getCurrSym()) {
      return list[i];
    }
  }
  return Command();
}

void Programm::swap(Programm& b) noexcept {
  std::swap(list, b.list);
  std::swap(size, b.size);
  std::swap(capasity, b.capasity);
}

Tape::Tape(size_t size, const char str[]) : tape(nullptr), TapeSize(size) {
  if (strlen(str) > TapeSize) {
    throw std::invalid_argument("Error: invalid tape maxsize");
  }
  tape = new char[TapeSize];
  for (size_t i = 0; i < TapeSize; ++i) {
    if (i < strlen(str)) {
      if (str[i] != '0' && str[i] != '1') {
        delete[] tape;
        throw std::invalid_argument("Error: invalid input data");
      }
      tape[i] = str[i];
    } else {
      tape[i] = '0';
    }
  }
}

Tape::Tape(const Tape& other) : tape(nullptr), TapeSize(other.TapeSize) {
  tape = new char[TapeSize];
  for (size_t i = 0; i < TapeSize; ++i) {
    tape[i] = other.tape[i];
  }
}

Tape::Tape(Tape&& other) noexcept : tape(other.tape), TapeSize(other.TapeSize) {
  other.tape = nullptr;
  other.TapeSize = 0;
}

Tape& Tape::operator=(const Tape& other) {
  if (this != &other) {
    Tape tmp(other);
    swap(tmp);
  }
  return *this;
}

Tape& Tape::operator=(Tape&& other) noexcept {
  if (this != &other) {
    delete[] tape;
    tape = other.tape;
    TapeSize = other.TapeSize;

    other.tape = nullptr;
    other.TapeSize = 0;
  }
  return *this;
}

void Tape::swap(Tape& other) noexcept {
  std::swap(tape, other.tape);
  std::swap(TapeSize, other.TapeSize);
}

void Tape::print(size_t pos) const {
  size_t j = TapeSize;
  for (size_t i = 0; i < TapeSize; ++i) {
    if ((*this)[pos + i] == '1') {
      j = i;
    }
  }
  if (j == TapeSize) {
    std::cout << '0' << std::endl;
    return;
  }
  for (size_t i = 0; i <= j; ++i) {
    std::cout << (*this)[pos + i];
  }
  std::cout << std::endl;
}
