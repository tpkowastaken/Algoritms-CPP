#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
  char donut[][6] = {
    "  ______",
    " /      \\",
    "/        \\",
    "\\        /",
    " \\______/"
  };
  char blank[][6] = {
    "        ",
    "        ",
    "        ",
    "        ",
    "        "
  };
  int i;

  while (1) {
    for (i = 0; i < 4; i++) {
      printf("%s\n%s\n%s\n%s\n%s\n", donut[0], donut[1], donut[2], donut[3], donut[4]);
      sleep(1);
      printf("\033[A\033[A\033[A\033[A\033[A"); // move cursor up 5 lines
      printf("%s\n%s\n%s\n%s\n%s\n", blank[0], blank[1], blank[2], blank[3], blank[4]); // overwrite previous donut with blank lines
    }
  }

  return 0;
}
