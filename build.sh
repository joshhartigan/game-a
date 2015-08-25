gcc -Wall -Wextra -Wformat -Wno-missing-braces -pedantic -Werror -std=gnu11 \
    -lncurses \
    src/*.c -o bin/game
