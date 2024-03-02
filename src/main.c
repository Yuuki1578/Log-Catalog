#include <stdio.h>
#include <string.h>

#define COL "\e[1;36m"
#define DEF "\e[0m"
#define BUFFMAX 65535
#define EDIT "-e"
#define DEL "-d"
#define ADD "-a"
#define GET "-l"

int main(int argc, char **argv) {

  if (argc == 1) {
    puts("You must either specify the file or mode you want use");
    puts("Looking for help? type \'log --help\'");
    return 1;
  }

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

    else {
      perror("Error ");
      return 1;
    }
  }

  else if (argc == 3 && (argv[1] != NULL && argv[2] != NULL) &&
           strcmp(argv[2], EDIT) == 0) {

    char buffer[BUFFMAX], edit[BUFFMAX], ftmp_n[1024];
    int edit_l, current_l;
    FILE *fpath, *ftmp;

    strcpy(ftmp_n, "temp.");
    strcat(ftmp_n, argv[1]);

    fpath = fopen(argv[1], "r");
    ftmp = fopen(ftmp_n, "w");

    if (fpath == NULL || ftmp == NULL) {
      perror("Error ");
      return 1;
    }

    printf("Which line : ");
    scanf("%i", &edit_l);
    getchar();
    printf("Input string : ");
    fgets(edit, BUFFMAX, stdin);

    int ftmp_l = 1;
    while (fgets(buffer, BUFFMAX, fpath)) {
      if (ftmp_l != edit_l) {
        fputs(buffer, ftmp);
        ftmp_l++;
      }

      else if (ftmp_l == edit_l) {
        fputs(edit, ftmp);
        ftmp_l++;
      }
    }

    fclose(fpath);
    fclose(ftmp);

    rename(ftmp_n, argv[1]);
  }

  else if (argc == 3 && (argv[1] != NULL && argv[2] != NULL) && strcmp(argv[2], DEL) == 0) {
      char buffer[BUFFMAX], ftmp_n[1024];
      int delete_l, current_l;
      FILE *fpath, *ftmp;

      strcpy(ftmp_n, "temp.");
      strcat(ftmp_n, argv[1]);

      fpath = fopen(argv[1], "r");
      ftmp = fopen(ftmp_n, "w");

      if (fpath == NULL || ftmp == NULL) {
        perror("Error ");
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
    perror("Something went wrong here ");
    return 1;
  }

  return 0;
}