CXX = g++
CXXFLAGS = -std=c++17 -g -fprofile-arcs -ftest-coverage
CXXWITHCOVERAGEFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage

LINKFLAGS = -lgtest -lpthread -lgmock

TEST_DIR = test

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

SRC_DIR = src
OBJ_DIR = objs
GTEST_DIR = test

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint

PROGRAM = chess
PROGRAM_TEST = testChess
PROGRAM_TEST_ERRORS = $(PROGRAM_TEST)_errors
PROGRAM_TEST_ERROR1 = $(PROGRAM_TEST)_error1
PROGRAM_TEST_ERROR2 = $(PROGRAM_TEST)_error2
PROGRAM_TEST_ERROR3 = $(PROGRAM_TEST)_error3

DOCS_DIR = docs

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

.PHONY: all
all: $(PROGRAM_TEST) memcheck static style

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ *.o $(SRC)/*.o $(TEST_SRC)/*.o \
	$(PROGRAM_TEST) $(PROGRAM_TEST_ERROR1) $(PROGRAM_TEST_ERROR2) $(PROGRAM_TEST_ERROR3) \
	$(DOCS_DIR) obj bin *.gc* .objs \
	$(COVERAGE_RESULTS) $(COVERAGE_DIR)

.PHONY: clean-temp
clean-temp:
	rm -rf *~ \#* .\#* \
	${SRC_DIR}/*~ ${SRC_DIR}/\#* ${SRC_DIR}/.\#* \
	${GTEST_DIR}/*~ ${GTEST_DIR}/\#* ${GTEST_DIR}/.\#* \
	${SRC_INCLUDE}/*~ ${SRC_INCLUDE}/\#* ${SRC_INCLUDE}/.\#* \
	${PROJECT_SRC_DIR}/*~ ${PROJECT_SRC_DIR}/\#* ${PROJECT_SRC_DIR}/.\#* \
	${DESIGN_DIR}/*~ ${DESIGN_DIR}/\#* ${DESIGN_DIR}/.\#* \
	*.gcov *.gcda *.gcno 

# To do build tests

$(PROGRAM_TEST_ERRORS): $(PROGRAM_TEST_ERROR1) $(PROGRAM_TEST_ERROR2) $(PROGRAM_TEST_ERROR3)

$(PROGRAM_TEST): Chess.o testMain.o  testChess.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) testMain.o testChess.o Chess.o $(LINKFLAGS)

$(PROGRAM_TEST_ERROR1): $(OBJ_DIR)/ChessError1.o testMain.o  testChess.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST_ERROR1) $(INCLUDE) $(OBJ_DIR)/ChessError1.o  testMain.o  testChess.o $(LINKFLAGS)

$(PROGRAM_TEST_ERROR2): $(OBJ_DIR)/ChessError2.o testMain.o  testChess.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST_ERROR2) $(INCLUDE) $(OBJ_DIR)/ChessError2.o testMain.o  testChess.o $(LINKFLAGS)

$(PROGRAM_TEST_ERROR3): $(OBJ_DIR)/ChessError3.o testMain.o  testChess.o
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST_ERROR3) $(INCLUDE) $(OBJ_DIR)/ChessError3.o testMain.o  testChess.o $(LINKFLAGS)

Chess.o: $(SRC_DIR)/Chess.cpp $(SRC_INCLUDE)/Chess.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Chess.cpp -o Chess.o -I $(SRC_INCLUDE)

testMain.o: $(TEST_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/main.cpp -o testMain.o -I $(SRC_INCLUDE)

testChess.o: $(TEST_DIR)/Chess.cpp
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/Chess.cpp -o testChess.o -I $(SRC_INCLUDE)


# To do run tests
.PHONY: tests
tests: $(PROGRAM_TEST) $(PROGRAM_TEST_ERRORS)
# 	./$(PROGRAM_TEST)
# 	./$(PROGRAM_TEST_ERROR1)
# 	./$(PROGRAM_TEST_ERROR2)
# 	./$(PROGRAM_TEST_ERROR3)

# To do memory leak checking
.PHONY: memcheck
memcheck: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes ./$(PROGRAM_TEST) --error-exitcode=1


# To perform the code coverage checks
coverage: ${PROGRAM_TEST}
	./${PROGRAM_TEST}
	# Determine code coverage
	${LCOV} --capture --gcov-tool ${GCOV} --directory . --output-file ${COVERAGE_RESULTS}
	# Only show code coverage for the source code files (not library files)
	${LCOV} --extract ${COVERAGE_RESULTS} */*/*/${SRC_DIR}/* -o \
	${COVERAGE_RESULTS}
	#Generate the HTML reports
	genhtml ${COVERAGE_RESULTS} --output-directory ${COVERAGE_DIR}
	#Remove all of the generated files from gcov
	make clean-temp

