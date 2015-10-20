# Detecting OS
UNAME_S=$(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CC=g++-4.8
    GTEST_LL=-I /usr/local/opt/gtest/include/ -lgtest_main -lpthread
else
    ifeq ($(UNAME_S),Darwin)
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/opt/gtest/lib/ -lgtest_main -lgtest -lpthread
    else
        CC=g++
        GTEST_LL=-I /usr/local/opt/gtest/include/ -L /usr/local/lib/ -lgtest_main -lgtest -lpthread
    endif
endif

# Directories
LIB_DIR = ../lib
BIN_DIR = ../bin
TEST_DIR = .

# Test Cases
_TEST_CASES=$(patsubst $(TEST_DIR)/%,$(BIN_DIR)/%,$(wildcard $(TEST_DIR)/merge_sort_test.cpp))
TEST_CASES=$(patsubst %.cpp,%.test.o,$(_TEST_CASES))

# Compiler flags
CPPFLAGS = -Wall -g -I$(HEADER_DIR) -std=c++11
GTEST_CPPFLAGS = -Wall -g -I$(HEADER_DIR) -Wextra -pthread -std=gnu++0x


 #Rules for compiling and running all test cases in 'test folder'

$(BIN_DIR)/%.test.o: $(TEST_DIR)/set_test.cpp $(LIB_DIR)/proj_set.h $(BIN_DIR)/.dirstamp
	$(CC) $(GTEST_CPPFLAGS) $(GTEST_LL) -c $< -o $@

$(BIN_DIR)/set_test: $(TEST_CASES)
	$(CC) $(GTEST_CPPFLAGS) $^ $(GTEST_LL) -o $@

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR) && touch $@

# Phoney targets
.PHONY: clean
.PHONY: tests

tests: $(BIN_DIR)/set_test
	-@$(BIN_DIR)/set_test
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
