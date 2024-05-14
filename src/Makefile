CC = g++ -std=c++17
CPPFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lgtest -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LIB = s21_matrix_oop.a
SOURCES = s21_matrix_oop.cpp
OBJECTS = $(addprefix obj/,$(SOURCES:.cpp=.o))
TESTFILES = ./tests/test.cpp

all: s21_matrix_oop.a test gcov_report

test: s21_matrix_oop.a
	$(CC) tests/test.cpp -c -o test_gcov.o
	$(CC) $(CPPFLAGS) s21_matrix_oop.cpp test_gcov.o -o $@ $(LDFLAGS) --coverage
	./test

s21_matrix_oop.a: $(OBJECTS) 
	ar -src $@ $(OBJECTS)
	ranlib $@

gcov_obj/%.o: %.cpp
	-mkdir gcov_obj
	$(CC) $(GCOVFLAGS) -c $< -o $@

obj/%.o: %.cpp
	-mkdir obj
	$(CC) $(CPPFLAGS) -c $< -o $@

stylecheck: 
	clang-format -style=google -n tests/*.cpp 
	clang-format -style=google -n s21_matrix_oop.* 

apply_style: 
	clang-format -style=google -i tests/*.cpp 
	clang-format -style=google -i s21_matrix_oop.* 

gcov_report: test 
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml test.info --output-directory report
	open ./report/index.html

valgrind: clean test
	CK_FORK=no valgrind --vgdb=no --log-file="valgrind.log" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean:
	rm -rf ./gcov_obj ./obj
	rm -rf s21_matrix_oop*.a
	rm -rf test report
	rm -f test.*
	rm -f *.gc*
	rm -f *.o
	rm -f *.log
	rm -f test_single