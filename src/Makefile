PROJECT_NAME = s21_simple_navigator
CXX = g++
STD = -std=c++17
CFLAG = -Wall -Wextra -Werror -pedantic
CLANG_FORMAT ?= clang-format
O_DIR = ./obj
TEST_FILES = ./Tests/GraphTest.cc
FILES = $(O_DIR)/s21_graph.a $(O_DIR)/s21_graph_algorithms.a

all: clean obj_dir console

obj_dir:
	mkdir -p $(O_DIR)

s21_graph.o: clean
	$(CXX) -c $(STD) $(CFLAG) ./Models/src/Graph/Graph.cc -o $(O_DIR)/s21_graph.o

s21_graph.a: s21_graph.o
	ar rcs $(O_DIR)/s21_graph.a $(O_DIR)/s21_graph.o

s21_graph_algorithms.o: s21_graph.a
	$(CXX) -c $(STD) $(CFLAG) ./Models/src/Graph/GraphAlgorithms.cc -o $(O_DIR)/s21_graph_algorithms.o

s21_tsm.o: clean
	$(CXX) -c $(STD) $(CFLAG) ./Models/src/Graph/Tsm.cc -o $(O_DIR)/s21_tsm.o

s21_graph_algorithms.a: s21_graph_algorithms.o s21_tsm.o
	ar rcs $(O_DIR)/s21_graph_algorithms.a $(O_DIR)/s21_graph_algorithms.o $(O_DIR)/s21_tsm.o

console: clean obj_dir s21_graph.a s21_graph_algorithms.a
	$(CXX) $(STD) $(CFLAG) main.cc ./Controllers/src/Controller.cc ./Views/src/View.cc $(O_DIR)/s21_graph.a $(O_DIR)/s21_graph_algorithms.a -o s21_simple_navigator
	./s21_simple_navigator

test: s21_graph_algorithms.a
	$(CXX) $(STD) -o all_tests $(TEST_FILES) $(GTEST) $(FILES)
	./all_tests

leaks: test
	CK_FORK=no leaks --atExit -- ./all_tests

clean:
	@rm -rf $(O_DIR)/*.o
	@rm -rf *.out

clean_all:
	@rm -rf *.o
	@rm -rf *.a
	@rm -rf $(O_DIR)/*.o
	@rm -rf $(O_DIR)/*.a
	@rm -rf *.out
	@rm -rf s21_simple_navigator
	@rm -rf all_tests

check:
	@find Controllers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -n --style=Google

correct:
	@find Controllers -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Models -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Views -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google
	@find Tests -name '*cc' -o -name '*.h' -type f | xargs $(CLANG_FORMAT) -i --style=Google

rebuild: clean_all all
