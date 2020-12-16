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
//9kbzURPb6VTI+l307+fdMzyb932fir1c5/G5J/b3nKRn/beMyy5U+ywZtrm4/rvpv8e7dt/u+35a+05bc8Zhv/7yT/XmP7XbY++fdmGz0W2/r76gYH+ZH3FRhHnPwnytwjeVRUafx9BU0mGvTCamPLV7RMAJvw0S8fkkzA9rbZxm+frT+TbPRZa5sPu2y/o7bf19n4ZbntdzG9/wt4q0UEphXuApWHwD3y8odynsTNG7XLZmS0UXpQ0mkjAtJ7tWHFVnU0z027U8um5QHdQnw6Qy1f3mWz8mDS7kEyx/FptH1by/f69M1TpOXsx5W6ojleswcmc7x8P0xgoxIyURlgl82zZK8HukDjzug/Jpk/oH1WOcB7sfxKNZujWYR9wlO6RYrq8gXKkRSsttYdRMZKyKFu1+rfc+mnq597b1frU53GqkC18ZW51F8qpvNxVQiattl0gP0crXxCtfTwjKsFXhp/Hxh1U1fSQHbNPwjlf3NPx+UFxymX2fyn9vGFhXH9FZ9wfKHu1E8zPlD/uxd/uvolq7pan+qQhvPEJV0YX4D9y3ldGF+A57+qk/EtqDQuufuDro8vlP/org86H1/A8eJLO/KPVywB//jwy9A/jis+r9U3GNcD8ErjuVVJHk9P4oxIX2PsVaJCgbsH7Rlc6dGxg8R1RXoZvbgArgOn+7GMv5r1qCrjz2cozbE10Y2k0+U0uNDmIconWl9J/1tsjWc1vjobe7Jxa/l61nU2umr7RcrCbaCFRaZEaiPHGt5aYocm1M7Ye03vk21qnOpT5N0IWt1ScYlmNCGkePkGDI/lzLPvVJmLMsAyZ0MuehnuqU6Hx5c2TOwe7ROZyU3eTE2uiFKTCSizAdrYBFMeNHYCaHyxN9lcwJ39IjVUKfwwwKR656p6WdAdN6nZAL4aw6QZSLVx7HmCp4dLUac2VhrTFqnVdj3v2z55+2e7b6v9P7BJxGQVVcAHXoT5enOpk/ovQn0iaCb5jgaFv49a9HFbgC63I11uBbqUEbgQun5FoT3beG4ucmwGCT0fbVP5aJsK1M/C8MsMBJmAIHx8g4KQuC7Sz5gblkrErYDyVheZNaOVuya3hgrUt/aLFoa3mrBuIVjfMWEVc8dJ/W+zigtyg1ZUkqw4PKOg5jc8GDI9QOQqC39T8EI3l/HiYuIMIkSQCBHkuT1BI+Ync+R7PbWnOhSrChE982EeV1yhyUKS8xAQx/GchuP53m3W+SmcAarMFr5Ecw//bzf/bzv/bzP+j5AGVMDK3uZWVvY2Vny2wfMjxt+n4YC/f7cSUbvq63bBUEdGyDjfBGPT+3rhlG97YRZXGOBOCJOtg68Qn38TjQg8au+KHsXLYaxiBxMLbCTa2AwQI3wBLvhERvCcxf5Ho6xCfRm3TLUP983ucNUOiExgZl0J1QiFe65jebPVQ4/mV4qjcwcMgFFtHEP1C0CY9ItMYdQvo3pfUvXuhHqE4Xlw1WilsSSqGp4jqDzO6zdgGHMTyLxbFEqv1te96kJv9Ksga/ZXGTeSsPWT4BrnQa1yP7wDiabrPhgVxucsdh0TPlWMz+WEz4+vZXzaYSwIE8+FqpndhF427fIBk82MnKPYcHe1MXYhsSE/1Iyy+Dzr8CxQML9JMPcAWxpVxq7pGsu7IUOYdxQx/J7Y9CB55XbHpoYU+3D7wDbEJhlG/im0UQ2uiIk1u6N1vP3J3TuhXoBfjrVqsyETXRzRwkiUMbuRMPvtPMasuxsgTozcRHkMkxd/2A+8mxZWxmZPbCpmQ59jVYKW8ZWTURbuhW5tkdmGY0+9POHLMu4DwvVQ2Dr0F6nGV6q+5S/FEsZ5ZeiX2Ud29T6yq/uFY1Q=
*/