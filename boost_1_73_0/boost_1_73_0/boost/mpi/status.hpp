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
EgMSEsyWfWlOdWxkH03z7zknoS2T7/l93LNsCAo5W6AVBmOX+DjANKbsSyuUGjMSqPRD4uX17VkYfSGNXvQ38gPyEbIq6EGYDN9hquw6ML8LCJFW3s2ABWV2taLDwNf6DwoT7cBtdj24g7xqIEekXlK2GDDuZcOeRWlcGgYb/RL1oHVIzoY+FdLN+9cTw72OKSo4YaFapMpu6UT/0rfNlhPPUTyuRfkBn5Cxm6S3ZIU5zoAVkHPKLnmucHfPhitsCvkaymth5LrwuJmgbFpRWy9cXXGO0pdf+AVQSwMECgAAAAgALWdKUgAJV1HxAAAAkQEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDQyVVQFAAG2SCRgVVE9T8MwEN39K6wi1Ml4YEBCJksLEhIDEhIsXSz70pzq2Mg+mubfc05CWybf8/u4Z9kQFHK2QCMMxjbxcYBxSNmXRig1ZCRQ6YfEy+vbszD6Qho962/kB+QjZFXQgzAZvsNY2WVgfhMQIi28mwALyuRqRIuBr/UfFCbanttsOnAHedVADkidpGwxYNzLHXtmpXGp7230c9Sj1iE5G7pUSN++f20Z7nVMUcEJC9UiVXZHJ/qXvt6tOfEcxeNSlB/wCRnbUXpLVpjjBFgB
*/