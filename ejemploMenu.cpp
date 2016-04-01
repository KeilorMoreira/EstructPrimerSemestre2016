    #include <stdio.h>
    #include <conio.h>
    #include <stdlib.h>

    #define ESCAPE_KEY 27


    int main(void)
    {

       int c;

       while ((c = getch()) != ESCAPE_KEY)
       {
          if (c == 0)
          {
             printf("0, ");
             fflush(stdout);
             c = getch();
          }

          printf("%d\n", c);
       }

       return EXIT_SUCCESS;
    }
