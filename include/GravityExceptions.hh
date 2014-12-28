#ifndef _GRAVITYEXCEPTIONS_H_
#define _GRAVITYEXCEPTIONS_H_

#include <stdexcept>

struct GravityException : public std::runtime_error{
  using std::runtime_error::runtime_error;
};

struct IncompatibleSizesException : public GravityException{
  using GravityException::GravityException;
};

#endif /* _GRAVITYEXCEPTIONS_H_ */
