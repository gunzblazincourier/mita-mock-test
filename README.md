# Background
The Application Under Test (AUT) is a simplified version of the game of chess. This application uses a Model-View-Controller architecture, and we were required to test the Controller of this application.

# Procedure
This application is tested using mocking. For this, GoogleTest was used (specifically the gMock library) to create mock classes for Model and View, and use them to create a test for the controller. This test simulates  full game of this chess and checks if mentioned expectations for the mock methods are met. Such expectations include how many times the method is called, when it is called and whether it returns the right value.

# Mutants
If any expectation fails, the test fails. In this application, the test passes since the game runs as intended, but if the code mutates, the test should fail. If it does not, the test is flawed. Fortunately, we were able to detect what all three mutations provided by running the test with each mutation active and checking where and how the test fails. The three mutations are as follows:

1) Board is not drawn (Board::draw() expected but never called)
2) Invalid move is not detected (ChessUI::InvalidMove() expected but never called)
3) Game does not end (ChessUI::gameOver() expected but never called)

# Compile-and-Run Instructions
- Enter the project directory through a terminal
- Execute 'make testChess' which will create the executable for the main untouched code
- Execute 'make testChess_errors' which will create three executables for each applied mutation
- Run the main executable and the three faulty ones
- The test 'ChessTest.CanPlayGame' should pass for the main binary and fail for the other three binaries due to the errors mentioned in the 'Mutations' section.