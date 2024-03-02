/*
  The LogCatalog text editor
  C/Clang version 17.0.6
  Target aarch64-unknown-linux-android24
  Thread model posix
*/

// Standard library
#include <stdio.h>
#include <string.h>

// Local header
#include "include/error.h"
#include "include/help.h"

// Line colors
#define COL "\e[1;36m"
#define DEF "\e[0m"

// User defined constants
#define BUFFMAX 65535
#define EDIT "-e"
#define DEL "-d"
#define ADD "-a"
#define GET "-l"

// Main function that take maximum 3 - 4 arguments
int main(int argc, char **argv) {

  // if the argc is only 1
  // it will display error messages that defined in include/error.h
  // and return 1 to the main function
  if (argc == 1) {
    // Error text if argc is only 1
    printf("%s", msg_err_argc1());
    return 1;
  }

  // or if the argc is 2 and argv[1] / argc 2 is not a null pointer
  // this scope will read the file and the line number too
  else if (argc == 2 && argv[1] != NULL) {
    FILE *file;
    if ((file = fopen(argv[1], "r")) != NULL) {
      char buffer[BUFFMAX];
      int i = 1;
      while (fgets(buffer, BUFFMAX, file)) {
        printf("%s%i %s%s", COL, i, DEF, buffer);
        i++;
      }
      fclose(file);
    }

    // if FILE *file is a null pointer
    // it will display the error messages and return 1
    else {
      // Error text if *file is a NULL pointer
      return 1;
    }
  }

  // or if argc == 3 and both, argv[1] & argv[2] is not a null pointer
  // and if argv[2] & constants EDIT are equals
  // this scope will edit a spesific line from user input
  // using scanf() function from stdio.h
  // see the documentation in manpages
  // "man stdio.h"
  else if (argc == 3 && (argv[1] != NULL && argv[2] != NULL) &&
           strcmp(argv[2], EDIT) == 0) {

    char buffer[BUFFMAX], edit[BUFFMAX], ftmp_n[1024]; // ftmp_n = file temporary name
    int edit_l; // edit_l = edit line, current line is the begining of the file line
    FILE *fpath, *ftmp; // create a double FILE pointer

    strcpy(ftmp_n, "temp."); // adding const char * "temp." to ftmp_n, it will give a name to a file that begin with temp.
    strcat(ftmp_n, argv[1]); // then push argv[1] string to ftmp_n

    fpath = fopen(argv[1], "r"); // it open and read the path that specified in argv[1]
    ftmp = fopen(ftmp_n, "w"); // just the same, but it open the temp.argv[1]

    // if one of these file is null
    // it will display messages and return 1
    if (fpath == NULL || ftmp == NULL) {
      // Error text if both, fpath and ftmp is a NULL pointer
      return 1;
    }

    // user interactive input
    printf("Which line : ");
    scanf("%i", &edit_l);
    getchar(); // prevent '\n' in fgets()
    printf("Input string : ");
    fgets(edit, BUFFMAX, stdin);

    int ftmp_l = 1; // line iterator
    while (fgets(buffer, BUFFMAX, fpath)) { // buffer in file per line
      if (ftmp_l != edit_l) {
        fputs(buffer, ftmp);
        ftmp_l++; // line is increased
      }

      // if iterator and edit line is same
      // it will push string from fgets() input to ftmp
      else if (ftmp_l == edit_l) {
        fputs(edit, ftmp);
        ftmp_l++;
      }
    }

    // close the file
    fclose(fpath);
    fclose(ftmp);

    // rename the file to argv[1]
    // it will automatically remove the older
    rename(ftmp_n, argv[1]);
  }

  else if (argc == 3 && (argv[1] != NULL && argv[2] != NULL) &&
           strcmp(argv[2], DEL) == 0) {
    char buffer[BUFFMAX], ftmp_n[1024];
    int delete_l, current_l;
    FILE *fpath, *ftmp;

    strcpy(ftmp_n, "temp.");
    strcat(ftmp_n, argv[1]);

    fpath = fopen(argv[1], "r");
    ftmp = fopen(ftmp_n, "w");

    if (fpath == NULL || ftmp == NULL) {
      // Error text if both, fpath and ftmp is a NULL pointer
      return 1;
    }

    printf("Which line : ");
    scanf("%i", &delete_l);

    int ftmp_l = 1;
    while (fgets(buffer, BUFFMAX, fpath)) {
      if (ftmp_l != delete_l) {
        fputs(buffer, ftmp);
        ftmp_l++;
      }

      else if (ftmp_l == delete_l) {
        ftmp_l++;
        continue;
      }
    }

    fclose(fpath);
    fclose(ftmp);

    rename(ftmp_n, argv[1]);
  }

  else {
    // Error text for return 1 (SIGKILL) error code 1
    return 1;
  }

  return 0;
}
