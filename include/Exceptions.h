#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <stdexcept>

/**
* Exception for selecting off the board.
*/
class invalid_location_error: public std::runtime_error {
 public:
    /**
    * @param errMessage An error message.
    */
    explicit invalid_location_error(const char* errMessage) :
        std::runtime_error(errMessage) {
    }
};

/**
* Exception for selecting other player's piece.
*/
class invalid_piece_error: public std::runtime_error {
 public:
    /**
    * @param errMessage An error message.
    */
    explicit invalid_piece_error(const char* errMessage) :
        std::runtime_error(errMessage) {
    }
};

/**
* Exception for selecting a location with no piece.
*/
class no_piece_error: public std::runtime_error {
 public:
    /**
    * @param errMessage An error message.
    */
    explicit no_piece_error(const char* errMessage) :
        std::runtime_error(errMessage) {
    }
};

#endif // EXCEPTIONS_H_INCLUDED
