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
592KeBTnvAa6oxV2EdRZ7Qkmtfoe3PPv+5DGiXzc5X+QUVwUEKHXGfo5nRcY4Su5xch0lLcnq2urmXvt837rzOPJmNrJmf1PT/Dnzz4mfBU33qK7n514ulYzSrF3j0xMPQlQkrhf6GadSXq+KP/w9XG8SvTnj6OLT0uhXEnWxROb/JfKCFHVfMxx018fX3pwxKjmOMxOblE1a41nCKtlnsHiq08Oe0xTLZTpkeWWoOii5CVOP3jDvijJGTHMfA5PtBYoLrJDyYy94QYE9RFO9opBc73qjl4iI3EvQeN2lAZSHNCTbQ/p+oeGP3HQam/mdpzGUrbUVDK8wmJBjI1kQWFo9T6VkjcleCF6+2+Av4Oo9Uc8Pf/0H+sjMuhxq8RHNwGhIjHcoYjiMnutUhlYjdy1XBiBqpXAB301QUrqo5lx9/Oqr4J4sU5qw8rn7ZP4Bt9hAGdiFTiKE7i+maW1PAQhbfywhS6XhrC7jjDiKJSWSCUnmkN4u6PA9t2fg54UiSu4dg8S0DFjJ3qAOtLdksjSTKS9H0UZcgyK1e/QtzlDmTRuFjkoQ3BGfQ==
*/