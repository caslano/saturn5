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
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
*/