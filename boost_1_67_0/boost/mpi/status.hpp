// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file status.hpp
 *
 *  This header defines the class @c status, which reports on the
 *  results of point-to-point communication.
 */
#ifndef BOOST_MPI_STATUS_HPP
#define BOOST_MPI_STATUS_HPP

#include <boost/mpi/config.hpp>
#include <boost/optional.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace mpi {

class request;
class communicator;

/** @brief Contains information about a message that has been or can
 *  be received.
 *
 *  This structure contains status information about messages that
 *  have been received (with @c communicator::recv) or can be received
 *  (returned from @c communicator::probe or @c
 *  communicator::iprobe). It permits access to the source of the
 *  message, message tag, error code (rarely used), or the number of
 *  elements that have been transmitted.
 */
class BOOST_MPI_DECL status
{
 public:
  status() : m_count(-1) { }
  
  status(MPI_Status const& s) : m_status(s), m_count(-1) {}

  /**
   * Retrieve the source of the message.
   */
  int source() const { return m_status.MPI_SOURCE; }

  /**
   * Retrieve the message tag.
   */
  int tag() const { return m_status.MPI_TAG; }

  /**
   * Retrieve the error code.
   */
  int error() const { return m_status.MPI_ERROR; }

  /**
   * Determine whether the communication associated with this object
   * has been successfully cancelled.
  */
  bool cancelled() const;

  /**
   * Determines the number of elements of type @c T contained in the
   * message. The type @c T must have an associated data type, i.e.,
   * @c is_mpi_datatype<T> must derive @c mpl::true_. In cases where
   * the type @c T does not match the transmitted type, this routine
   * will return an empty @c optional<int>.
   *
   * @returns the number of @c T elements in the message, if it can be
   * determined.
   */
  template<typename T> optional<int> count() const;

  /**
   * References the underlying @c MPI_Status
   */
  operator       MPI_Status&()       { return m_status; }

  /**
   * References the underlying @c MPI_Status
   */
  operator const MPI_Status&() const { return m_status; }

 private:
  /**
   * INTERNAL ONLY
   */
  template<typename T> optional<int> count_impl(mpl::true_) const;

  /**
   * INTERNAL ONLY
   */
  template<typename T> optional<int> count_impl(mpl::false_) const;

 public: // friend templates are not portable

  /// INTERNAL ONLY
  mutable MPI_Status m_status;
  mutable int m_count;

  friend class communicator;
  friend class request;
};


} } // end namespace boost::mpi

#endif // BOOST_MPI_STATUS_HPP

/* status.hpp
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
*/