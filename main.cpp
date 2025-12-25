#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

#define CLR_RESET  "\033[0m"
#define CLR_BORDER "\033[38;5;208m"
#define CLR_TITLE  "\033[1;38;5;220m"
#define CLR_SELECT "\033[1;38;5;46m"

char getch() {
  char buf = 0;
  struct termios old = {0};
  tcgetattr(0, &old);
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  tcsetattr(0, TCSANOW, &old);
  read(0, &buf, 1);
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  tcsetattr(0, TCSADRAIN, &old);
  return buf;
}
void moveCursor(int row, int col) {
  cout << "\033[" << row << ";" << col << "H";
}
void clearLine() {
  cout << "\033[K";
}

const string menuList[] = {
  "Celcius -> Fahrenheit",
  "Celcius -> Kelvin",
  "Celcius -> Reamur",
  "Fahrenheit -> Celcius",
  "Fahrenheit -> Kelvin",
  "Fahrenheit -> Reamur",
  "Kelvin -> Celcius",
  "Kelvin -> Fahrenheit",
  "Kelvin -> Reamur",
  "Reamur -> Celcius",
  "Reamur -> Fahrenheit",
  "Reamur -> Kelvin",
  "Quit"
};

const int menuCount = sizeof(menuList) / sizeof(menuList[0]);

int termWidth() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col > 0 ? w.ws_col : 80;
}

int main() {
  int selected = 0;
  char key;
  double lastInput = 0;
  double lastResult = 0;
  string lastUnit = "-";

  cout << "\033[2J";

  while (true) {
    moveCursor(1, 1);

    int width = termWidth();
    int leftW = width / 2 - 1;
    int rightW = width - leftW - 3;

    cout << CLR_BORDER << "┌";
    for (int i = 0; i < leftW; i++) cout << "─";
    cout << "┬";
    for (int i = 0; i < rightW; i++) cout << "─";
    cout << "┐" << CLR_RESET << "\n";

    cout << CLR_BORDER << "│" << CLR_RESET << "  Menu Konversi Suhu";
    for (int i = 0; i < leftW - 21; i++) cout << " ";
    cout << CLR_BORDER << "│" << CLR_RESET << "  Operasi Konversi";
    for (int i = 0; i < rightW - 18; i++) cout << " ";
    cout << "\n";

    cout << CLR_BORDER << "│" << CLR_RESET << "  ──────────────────────────";
    for (int i = 0; i < leftW - 28; i++) cout << " ";
    cout << CLR_BORDER << "│" << CLR_RESET;
    for (int i = 0; i < rightW; i++) cout << " ";
    cout << "\n";

    for (int i = 0; i < menuCount; i++) {
      cout << CLR_BORDER << "│" << CLR_RESET << " ";
      if (i == selected)
        cout << CLR_SELECT << "👉 " << menuList[i] << CLR_RESET;
      else
        cout << "   " << menuList[i];

      int pad = leftW - 3 - menuList[i].length();
      while (pad-- > 0) cout << " ";

      cout << CLR_BORDER << "│" << CLR_RESET;

      if (i == 0)
        cout << "  Pilihan : " << menuList[selected];
      else if (i == 1)
        cout << "  Input   : " << lastInput;
      else if (i == 2)
        cout << "  ----------------------------------";
      else if (i == 3)
        cout << "  Hasil   : " << lastResult << " " << lastUnit;

      cout << "\n";
    }

    cout << CLR_BORDER << "│" << CLR_RESET;
    for (int i = 0; i < leftW; i++) cout << " ";
    cout << CLR_BORDER << "│" << CLR_RESET;
    for (int i = 0; i < rightW; i++) cout << " ";
    cout << "\n";

    cout << CLR_BORDER << "│" << CLR_RESET;
    for (int i = 0; i < leftW; i++) cout << " ";
    cout << CLR_BORDER << "│" << CLR_RESET << "  Enter = Hitung | q = Keluar";
    for (int i = 0; i < rightW - 26; i++) cout << " ";
    cout << "\n";

    cout << CLR_BORDER << "└";
    for (int i = 0; i < leftW; i++) cout << "─";
    cout << "┴";
    for (int i = 0; i < rightW; i++) cout << "─";
    cout << "┘" << CLR_RESET << "\n";

    key = getch();

    if (key == '\033') {
      getch();
      switch (getch()) {
        case 'A': selected = (selected - 1 + menuCount) % menuCount; break;
        case 'B': selected = (selected + 1) % menuCount; break;
      }
    } else if (key == '\n') {
      if (selected == menuCount - 1) break;
      moveCursor(15, leftW + 6);
      clearLine();
      cout << "Masukkan nilai: ";
      cin >> lastInput;
      switch (selected) {
        case 0: lastResult = (lastInput * 9/5) + 32; lastUnit="F"; break;
        case 1: lastResult = lastInput + 273.15; lastUnit="K"; break;
        case 2: lastResult = lastInput * 4/5; lastUnit="R"; break;
        case 3: lastResult = (lastInput - 32) * 5/9; lastUnit="C"; break;
        case 4: lastResult = (lastInput - 32) * 5/9 + 273.15; lastUnit="K"; break;
        case 5: lastResult = (lastInput - 32) * 4/9; lastUnit="R"; break;
        case 6: lastResult = lastInput - 273.15; lastUnit="C"; break;
        case 7: lastResult = (lastInput - 273.15) * 9/5 + 32; lastUnit="F"; break;
        case 8: lastResult = (lastInput - 273.15) * 4/5; lastUnit="R"; break;
        case 9: lastResult = lastInput * 5/4; lastUnit="C"; break;
        case 10: lastResult = (lastInput * 9/4) + 32; lastUnit="F"; break;
        case 11: lastResult = (lastInput * 5/4) + 273.15; lastUnit="K"; break;
      }
    } else if (key == 'q' || key == 'Q') {
      break;
    }
  }

  cout << CLR_RESET << "\n";
  return 0;
}
