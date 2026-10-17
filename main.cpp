#include "turingmachine.h"

int main(int argc, char* argv[]) {
  if (argc != 4 && argc != 5) {
    std::cout << "Error: invalid input data" << std::endl;
    return 0;
  }

  size_t TapeSize = std::stoi(argv[2]);
  unsigned long long MaxTact = std::stoull(argv[3]);

  std::string lenta;
  if (argc == 5) {
    std::ifstream file_lenta(argv[4]);
    if (!file_lenta) {
      std::cout << "Error: invalid input data" << std::endl;
      return 0;
    }
    getline(file_lenta, lenta);
    file_lenta.close();
  }

  try {
    Programm prog(argv[1]);
    Tape tape(TapeSize, lenta.c_str());
    TuringMachine MT(prog);

    unsigned long long res = MT.calc(tape, MaxTact);
    if (res > MaxTact) {
      std::cout << "Not applicable" << std::endl;
      return 0;
    }

    if (argc == 4) {
      std::cout << res << std::endl;
      tape.print(MT.getpos());
    }
    if (argc == 5) {
      tape.print(MT.getpos());
    }

  } catch (const std::exception& error) {
    std::cout << error.what() << std::endl;
  }
  return 0;
}
