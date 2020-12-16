// Copyright (C) 2005-2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file exception.hpp
 *
 *  This header provides exception classes that report MPI errors to
 *  the user and macros that translate MPI error codes into Boost.MPI
 *  exceptions.
 */
#ifndef BOOST_MPI_EXCEPTION_HPP
#define BOOST_MPI_EXCEPTION_HPP

#include <boost/mpi/config.hpp>
#include <exception>
#include <cassert>
#include <string>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

namespace boost { namespace mpi {

/** @brief Catch-all exception class for MPI errors.
 *
 * Instances of this class will be thrown when an MPI error
 * occurs. MPI failures that trigger these exceptions may or may not
 * be recoverable, depending on the underlying MPI
 * implementation. Consult the documentation for your MPI
 * implementation to determine the effect of MPI errors.
 */
class BOOST_MPI_DECL exception : public std::exception
{
 public:
  /**
   * Build a new @c exception exception.
   *
   *   @param routine The MPI routine in which the error
   *   occurred. This should be a pointer to a string constant: it
   *   will not be copied.
   *
   *   @param result_code The result code returned from the MPI
   *   routine that aborted with an error.
   */
  exception(const char* routine, int result_code);

  virtual ~exception() throw();

  /**
   * A description of the error that occurred. 
   */
  virtual const char * what () const throw ()
  {
    return this->message.c_str();
  }

  /** Retrieve the name of the MPI routine that reported the error. */
  const char* routine() const { return routine_; }

  /**
   * @brief Retrieve the result code returned from the MPI routine
   * that reported the error.
   */
  int result_code() const { return result_code_; }

  /**
   * @brief Returns the MPI error class associated with the error that
   * triggered this exception.
   */
  int error_class() const 
  { 
    int result;
    MPI_Error_class(result_code_, &result);
    return result;
  }

 protected:
  /// The MPI routine that triggered the error
  const char* routine_;

  /// The failed result code reported by the MPI implementation.
  int result_code_;

  /// The formatted error message
  std::string message;
};

/**
 * Call the MPI routine MPIFunc with arguments Args (surrounded by
 * parentheses). If the result is not MPI_SUCCESS, use
 * boost::throw_exception to throw an exception or abort, depending on
 * BOOST_NO_EXCEPTIONS.
 */
#define BOOST_MPI_CHECK_RESULT( MPIFunc, Args )                         \
 {                                                                      \
   int _check_result = MPIFunc Args;                                    \
   assert(_check_result == MPI_SUCCESS);                                \
   if (_check_result != MPI_SUCCESS)                                    \
     boost::throw_exception(boost::mpi::exception(#MPIFunc,   \
                                                             _check_result)); \
 }

} } // end namespace boost::mpi

#endif // BOOST_MPI_EXCEPTION_HPP


/* exception.hpp
VuZ3SzSIxf5dFXLnTp3j3tqg0m7AxrmjGAJGKDGEwIp8lFglIGlAwCBv9qGgQXNqiDqfA50jH8dnLS942MycbyL+MGSXUPilNE2OOwh9HESLZmrRfZRCbLv1ezpjHvo/ZsxH+VHvH3wR+XHMiB/4MttiNCXuj6gIVyTmx1BjwljEwvCXfjhhxAM+qAf/k/j++CZX0KZdukGpI9/jIHuYzcv8hm8pqvyC/jg5hgomnuJ8QK0gJEoJy+7SQ2+uVwQDvGXUnmxh1NWOEm95Byxhz3eK/MhbGOiPs3hRGkMZ/LffVWIO+K7dbmo9P7o9+mVZo4iYe2/XKS32WlEazk8xxT98NGGKV70k2/uuEu96WEAaLaDSKlQEWWN1XgWm4ZJ7CGx+vYdDWZ8NK19CWV/4YeFzupJUbNfDE8+SHJlrEniTXdAdBbLT7jTxs4NCB+XuMoKIZ/NNtxE1yFQrMmkOiSfFEX0O6YKY4aNfVS3iafbPu42Wuu6SCnOoqL2Kx+Csb7hMyvwupNjQ2sZTi6AyWIxpKGB+CgU0cVV65i2GFFCE7yHclT18NrqmnwF8G9h78EP/kbDNxvuwt4Fg5XiKgnEe/e5bVFDOdwr1K8NZxn5uYzmM3V2OY+dl07yRxs4TjWMvgP/2uxxA490SvLA8fqyDpfv1dP9xO9j7pI/d3DMGuo/nO1uw71DPWNluwrd71v1IvuJOIzre7Nca/GMwPrtBMgeDMj4U+KilZ1YfFqWoD1+ro0Hya45j1AQGV6J31703wRs9N4XdFdEnPM8ExuoPVK9EqGpOo34/9QEWMc+PoVNrJFr6DJOC+4XfE/ru4vyyWOhP9nANPgG0pDx2R04jBiOJ6ROlN3snNbiCK4Chm3kAq0wDWFI+eMeF9GKkF5JWZdH78TCFRL6+A4f/XH+gpphe93NItKXYnbDewNqJPhDdEb06czdvpfFjsxWpzYb+Yb9remq7H8TXWMpwWYAuFGcSumWDrDyMXjmdhnnzFkyjuJvZwwug0us7Ci/SawnJv8+SPaLzV3rCw008PvY1GhApmFlBYZskI+M36z9HqeTv+CdzE2SdXydS89LDbtq6JsXlHrLzKjZC745+UHHMe+wkguWZNtKkQH5OukfJzyv4ZTnKJvXnjDYlPxeLi0FC7e9Zr3ousfMBuCLWWf/QqLLs1kZr7lKNDrFLlud9ygfNIfpxKDT115j6abeNs1A9EXpu1rpYX63VF+uIOYuG8JJkaaDXjmFwUQ1Z1hrUcumXrWax6BvU1pN3KrFdpr/cx019zpRTMHwVOiyuUUomTfOjVa9bBRLolZ8/K2Fr26wIvUL6TDGMzAVsdvgTYoqu3irGBi7T9aLeaC13mpfvTcbLNdVXqOZdqvlvf9AgQGg+ej61HWuRtnWP6Uyj+fOSms+Nfo4KnCA+DX/utWDrwUJlF7LnmYLQP86tUSL/Sbucs4I8tzf08vyacgnQbKRdVV2UknZ3zQySnQ6WPh/ZZh7DxdFiYw30JeWcjbGXn3GFXj63ZirFeA/d7QSfEe33QNRgu8R6PmF6MuLxXvsw+dOH2HMykOQ3jos7RSigr5FmCQ7L4DN25UMPP5kHWYdfbuzBH89oWfDjVYgx7aBAJ9rDT06ibMLlYPAdVRVX4W7PIL7nqc1rFV9ocCVnwKLsygJjmTOY/dGqHMFtt1VUKHhxsAp8rJdH+JnMG8TJ8sQdFkV0pXgqMcQ7KCdkBz/7AaGy2TA7zzrmm/cPnrXbDHVn2AHVibO9uFOqeKjMuUYZyq6WFmsuxscF/SPdLzuW+AfXscVcZdv76SWkcK7djOUokr8dg9RfiD4IDI9J5jLF3P86Rfh1csBPiDk=
*/