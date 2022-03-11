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