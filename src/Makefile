TARGET = smartcalc

NAME_GCOVTEST= gcov_s21_smartcalc
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OS = $(shell uname)
CONTROLLER = s21_smartcalc
NAME_TEST= test_s21_smartcalc
SRCS = s21_smartcalc.c

OBJS		= $(SRCS:.c=.o)

DIR_REPORT= ./report
DIR_INFO= ./info
FLAGS_GCOV= -fprofile-arcs -ftest-coverage
TESTDIR = tests
TEST = $(TESTDIR)/test_s21_smartcalc.c\

ifeq ($(OS), Linux)
	LDLIBS = -lcheck_pic -pthread -lrt -lm -lsubunit
	FLAGS_TESTS= -lcheck -lm -lsubunit
else
	LDLIBS = -lcheck -lm
	FLAGS_TESTS= -lcheck -lm -lsubunit
endif

$(CONTROLLER).o: $(CONTROLLER).c
	mkdir -p obj
	$(CC) -c $(CFLAGS) $(CONTROLLER).c $(LDLIBS) -o obj/$(CONTROLLER).o

debug:
	gcc -g -o debug_s $(SRCS) $(CFLAGS) $(LDLIBS)

test:
	@$(CC) -o $(NAME_TEST) $(SRCS) $(TEST) $(FLAGS_TESTS) $(CFLAGS)
	@./test_s21_smartcalc

gcov_report:
	@$(CC) -o $(NAME_GCOVTEST) $(SRCS) $(TEST) $(FLAGS_TESTS) $(CFLAGS) $(FLAGS_GCOV)
	@chmod +x *
	@./$(NAME_GCOVTEST)
	@rm -rf $(DIR_INFO) $(DIR_REPORT)
	@mkdir $(DIR_INFO) $(DIR_REPORT)
	@gcov ./* ./
	@mv *.gcno *.gcda *.gcov $(DIR_INFO)/
	@lcov -d $(DIR_INFO) -c -o $(DIR_INFO)/lcov.info
	@genhtml -o $(DIR_REPORT) $(DIR_INFO)/lcov.info
	@open $(DIR_REPORT)/index.html

install:
	@mkdir -p ../build
	@cd qt && qmake && make && make clean && rm -rf Makefile && mv smartcalc ../../build/$(TARGET)

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET) ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v1.0.tgz *
	@cd ../dist && rm -rf $(TARGET) README.md README_RUS.md
	@echo "The build was successfully archived"

dvi:
	@open ../README_RUS.md

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h */*.c */*.h
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n *.c *.h */*.c */*.h
	@rm -rf .clang-format
	@valgrind --tool=memcheck --leak-check=yes ./test_s21_smartcalc

clean:
	@rm -rf *.o *.a *.gcno *.gcda *.gcov $(NAME_TEST) $(NAME_GCOVTEST) $(DIR_INFO) $(DIR_REPORT)  

uninstall:
	@rm -rf ../build/smartcalc
	@echo "Uninstall completed successfully"