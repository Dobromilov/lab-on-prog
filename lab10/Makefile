.PHONY=clean
# Указываем компилятор
CC = gcc
CFLAGS = -Wall -Wextra

# Файлы проекта
SRCS = main.c functions.c
OBJS = $(SRCS:.c=.o)
TARGET = prog_5

# Сборка программы
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
#gcc -Wall -Wextra -o prog_5 main.o functions.o


# Компиляция object-файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка временных файлов
clean:
	rm -f $(OBJS) $(TARGET)
