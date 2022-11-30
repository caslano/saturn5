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
#include <boost/mpi/datatype.hpp>
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
  template<typename T> optional<int> count() const { return count_impl<T>(is_mpi_datatype<T>()); }

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

template<typename T> 
inline optional<int> status::count_impl(mpl::true_) const
{
  if (m_count != -1)
    return m_count;

  int return_value;
  BOOST_MPI_CHECK_RESULT(MPI_Get_count,
                         (&m_status, get_mpi_datatype<T>(T()), &return_value));
  if (return_value == MPI_UNDEFINED)
    return optional<int>();
  else
    /* Cache the result. */
    return m_count = return_value;
}

template<typename T> 
inline optional<int> status::count_impl(mpl::false_) const
{
  if (m_count == -1)
    return optional<int>();
  else
    return m_count;
}


} } // end namespace boost::mpi

#endif // BOOST_MPI_STATUS_HPP

/* status.hpp
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
*/