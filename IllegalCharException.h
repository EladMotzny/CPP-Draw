#include <iostream>
#include <initializer_list>
#include <cassert>
#include <stdexcept>
#include <string>
#pragma once

class IllegalCharException: public std::exception{
public:
    IllegalCharException(const char c){
        illigalChar = c;
    }
    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the char* lies
     *                 with the caller.
     */
    explicit IllegalCharException(const char* message) : msg_(message)
      {
      }

 
    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit IllegalCharException(const std::string& message):
      msg_(message)
      {}
 

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~IllegalCharException() throw (){}


    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
    virtual const char* what() const throw (){
       return msg_.c_str();
    }

    const std::string theChar() const{
       char s[] = {this->illigalChar};
       std::string str(s, sizeof(s));
       return str;
    }

protected:
    /** Error message.
     */
    std::string msg_;
    char illigalChar;
};