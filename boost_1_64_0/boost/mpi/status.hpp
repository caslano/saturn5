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
g7qfCiC1fNMCdGdRx5GDQByhoGZp9VHBitqiv9WHoNJxDXAMYjsamNE2VnGoKJiRf3TyaJvs7fFhN1JzIwkrzjljIPp61NF6GPjR0EAizBy2BC6Ro8NOqpSqlXrs8buiewXlqE+Xuzb/yTjqUEoqD/uDA/KBTyTrlgbdHBKbmNSsqH95SpggXggfV8fghvxsY16Lgv5SEpvEDwLWgSGvoiq2CfC38WEujj+ooewAjue82Tmbmz1hYDQJxM6QxdkpuPO5ochDY7bH4keCkhI0wormMOl4jnWXmGwDj1Dk7gbedt7HGYH9QOf499YZl52o7bpw0k7ObzmJ6yWFZA+LjY2U33Yq52ERb+dz8fv39ObmG8gGTwWuI74V6ydsLP3LFeL6G5Qmm05HAr73FEAkBS9v8HE5mERVjel6UTCA1jsMZsEhT1UyLq/Gr/AE0B3kj06yVnAFd2XflUPO3SzJ00GmFR2fYIMkKPn4aSe2UDZOqjRVguacrKugHThrq66e0hMPSXFvgdsvcV8KqjzCM2KeCxrtinU8t6H6PKh9GeTB4tX5d6eH4WUO4Q==
*/