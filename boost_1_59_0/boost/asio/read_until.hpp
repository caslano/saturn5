//
// read_until.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_READ_UNTIL_HPP
#define BOOST_ASIO_READ_UNTIL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <string>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/regex_fwd.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# include <boost/asio/basic_streambuf_fwd.hpp>
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  char (&has_result_type_helper(...))[2];

  template <typename T>
  char has_result_type_helper(T*, typename T::result_type* = 0);

  template <typename T>
  struct has_result_type
  {
    enum { value = (sizeof((has_result_type_helper)((T*)(0))) == 1) };
  };
} // namespace detail

/// Type trait used to determine whether a type can be used as a match condition
/// function with read_until and async_read_until.
template <typename T>
struct is_match_condition
{
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true if the type may be used as a match condition.
  static const bool value;
#else
  enum
  {
    value = boost::asio::is_function<
        typename boost::asio::remove_pointer<T>::type>::value
      || detail::has_result_type<T>::value
  };
#endif
};

/**
 * @defgroup read_until boost::asio::read_until
 *
 * @brief The @c read_until function is a composed operation that reads data
 * into a dynamic buffer sequence, or into a streambuf, until it contains a
 * delimiter, matches a regular expression, or a function object indicates a
 * match.
 */
/*@{*/

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a newline is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), '\n');
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers, char delim,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    char delim, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a CR-LF sequence is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), "\r\n");
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Read data into a dynamic buffer sequence until some part of the data it
/// contains matches a regular expression.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains some data
 * that matches a regular expression. The call will block until one of the
 * following conditions is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the
 * regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains data that matches the regular expression, the function returns
 * immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the substring that matches the regular expression.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a CR-LF sequence is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), boost::regex("\r\n"));
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until some part of the data it
/// contains matches a regular expression.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains some data
 * that matches a regular expression. The call will block until one of the
 * following conditions is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the
 * regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains data that matches the regular expression, the function returns
 * immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the substring that matches the regular expression. Returns 0
 * if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Read data into a dynamic buffer sequence until a function object indicates a
/// match.

/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until a user-defined match condition function object, when applied
 * to the data contained in the dynamic buffer sequence, indicates a successful
 * match. The call will block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<typename DynamicBuffer_v1::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @returns The number of bytes in the dynamic_buffer's get area that
 * have been fully consumed by the match function.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the function object.
 * An application will typically leave that data in the dynamic buffer sequence
 * for a subsequent read_until operation to examine.

 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To read data into a dynamic buffer sequence until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::const_buffers_1> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * std::string data;
 * boost::asio::read_until(s, data, match_whitespace);
 * @endcode
 *
 * To read data into a @c std::string until a matching character is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * std::string data;
 * boost::asio::read_until(s, data, match_char('a'));
 * @endcode
 */
template <typename SyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition,
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until a function object indicates a
/// match.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until a user-defined match condition function object, when applied
 * to the data contained in the dynamic buffer sequence, indicates a successful
 * match. The call will block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<DynamicBuffer_v1::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area that
 * have been fully consumed by the match function. Returns 0 if an error
 * occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the function object.
 * An application will typically leave that data in the dynamic buffer sequence
 * for a subsequent read_until operation to examine.
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 */
template <typename SyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, '\n');
 * std::istream is(&b);
 * std::string line;
 * std::getline(is, line); @endcode
 * After the @c read_until operation completes successfully, the buffer @c b
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    boost::system::error_code& ec);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, "\r\n");
 * std::istream is(&b);
 * std::string line;
 * std::getline(is, line); @endcode
 * After the @c read_until operation completes successfully, the buffer @c b
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim);

/// Read data into a streambuf until it contains a specified delimiter.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains the specified delimiter. The call will block
 * until one of the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains the
 * delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond the delimiter. An application will typically leave
 * that data in the streambuf for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim, boost::system::error_code& ec);

#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Read data into a streambuf until some part of the data it contains matches
/// a regular expression.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains some data that matches a regular expression.
 * The call will block until one of the following conditions is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains data that
 * matches the regular expression, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the substring that matches the regular expression.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a streambuf until a CR-LF sequence is encountered:
 * @code boost::asio::streambuf b;
 * boost::asio::read_until(s, b, boost::regex("\r\n"));
 * std::istream is(&b);
 * std::string line;
 * std::getline(is, line); @endcode
 * After the @c read_until operation completes successfully, the buffer @c b
 * contains the data which matched the regular expression:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr);

/// Read data into a streambuf until some part of the data it contains matches
/// a regular expression.
/**
 * This function is used to read data into the specified streambuf until the
 * streambuf's get area contains some data that matches a regular expression.
 * The call will block until one of the following conditions is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the streambuf's get area already contains data that
 * matches the regular expression, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area up to and including
 * the substring that matches the regular expression. Returns 0 if an error
 * occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    boost::system::error_code& ec);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Read data into a streambuf until a function object indicates a match.
/**
 * This function is used to read data into the specified streambuf until a
 * user-defined match condition function object, when applied to the data
 * contained in the streambuf, indicates a successful match. The call will
 * block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @returns The number of bytes in the streambuf's get area that have been fully
 * consumed by the match function.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the function object. An application
 * will typically leave that data in the streambuf for a subsequent read_until
 * operation to examine.
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To read data into a streambuf until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::streambuf::const_buffers_type> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * boost::asio::streambuf b;
 * boost::asio::read_until(s, b, match_whitespace);
 * @endcode
 *
 * To read data into a streambuf until a matching character is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * boost::asio::streambuf b;
 * boost::asio::read_until(s, b, match_char('a'));
 * @endcode
 */
template <typename SyncReadStream, typename Allocator, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, MatchCondition match_condition,
    typename constraint<is_match_condition<MatchCondition>::value>::type = 0);

/// Read data into a streambuf until a function object indicates a match.
/**
 * This function is used to read data into the specified streambuf until a
 * user-defined match condition function object, when applied to the data
 * contained in the streambuf, indicates a successful match. The call will
 * block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the streambuf's get area that have been fully
 * consumed by the match function. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the streambuf may contain
 * additional data beyond that which matched the function object. An application
 * will typically leave that data in the streambuf for a subsequent read_until
 * operation to examine.
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 */
template <typename SyncReadStream, typename Allocator, typename MatchCondition>
std::size_t read_until(SyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename constraint<is_match_condition<MatchCondition>::value>::type = 0);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a newline is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), '\n');
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers, char delim,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter character.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    char delim, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a CR-LF sequence is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), "\r\n");
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until it contains a specified
/// delimiter.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains the specified
 * delimiter. The call will block until one of the following conditions is
 * true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains the delimiter, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param delim The delimiter string.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the delimiter. Returns 0 if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond the delimiter. An application will
 * typically leave that data in the dynamic buffer sequence for a subsequent
 * read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Read data into a dynamic buffer sequence until some part of the data it
/// contains matches a regular expression.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains some data
 * that matches a regular expression. The call will block until one of the
 * following conditions is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the
 * regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains data that matches the regular expression, the function returns
 * immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the substring that matches the regular expression.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent read_until operation to examine.
 *
 * @par Example
 * To read data into a @c std::string until a CR-LF sequence is encountered:
 * @code std::string data;
 * std::size_t n = boost::asio::read_until(s,
 *     boost::asio::dynamic_buffer(data), boost::regex("\r\n"));
 * std::string line = data.substr(0, n);
 * data.erase(0, n); @endcode
 * After the @c read_until operation completes successfully, the string @c data
 * contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c b as
 * follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c read_until operation.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until some part of the data it
/// contains matches a regular expression.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until the dynamic buffer sequence's get area contains some data
 * that matches a regular expression. The call will block until one of the
 * following conditions is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the
 * regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the dynamic buffer sequence's get area already
 * contains data that matches the regular expression, the function returns
 * immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param expr The regular expression.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area up to
 * and including the substring that matches the regular expression. Returns 0
 * if an error occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent read_until operation to examine.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr, boost::system::error_code& ec,
    typename constraint<
        is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Read data into a dynamic buffer sequence until a function object indicates a
/// match.

/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until a user-defined match condition function object, when applied
 * to the data contained in the dynamic buffer sequence, indicates a successful
 * match. The call will block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<typename DynamicBuffer_v2::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @returns The number of bytes in the dynamic_buffer's get area that
 * have been fully consumed by the match function.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the function object.
 * An application will typically leave that data in the dynamic buffer sequence
 * for a subsequent read_until operation to examine.

 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To read data into a dynamic buffer sequence until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::const_buffers_1> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * std::string data;
 * boost::asio::read_until(s, data, match_whitespace);
 * @endcode
 *
 * To read data into a @c std::string until a matching character is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * std::string data;
 * boost::asio::read_until(s, data, match_char('a'));
 * @endcode
 */
template <typename SyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition,
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Read data into a dynamic buffer sequence until a function object indicates a
/// match.
/**
 * This function is used to read data into the specified dynamic buffer
 * sequence until a user-defined match condition function object, when applied
 * to the data contained in the dynamic buffer sequence, indicates a successful
 * match. The call will block until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function. If the match condition function object already indicates
 * a match, the function returns immediately.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers A dynamic buffer sequence into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<DynamicBuffer_v2::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes in the dynamic buffer sequence's get area that
 * have been fully consumed by the match function. Returns 0 if an error
 * occurred.
 *
 * @note After a successful read_until operation, the dynamic buffer sequence
 * may contain additional data beyond that which matched the function object.
 * An application will typically leave that data in the dynamic buffer sequence
 * for a subsequent read_until operation to examine.
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 */
template <typename SyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition>
std::size_t read_until(SyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition, boost::system::error_code& ec,
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/
/**
 * @defgroup async_read_until boost::asio::async_read_until
 *
 * @brief The @c async_read_until function is a composed asynchronous operation
 * that reads data into a dynamic buffer sequence, or into a streambuf, until
 * it contains a delimiter, matches a regular expression, or a function object
 * indicates a match.
 */
/*@{*/

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains the delimiter, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area up to and including the delimiter.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond the delimiter. An application
 * will typically leave that data in the dynamic buffer sequence for a
 * subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a newline is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data, '\n', handler); @endcode
 * After the @c async_read_until operation completes successfully, the buffer
 * @c data contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers, char delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains the delimiter, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area up to and including the delimiter.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond the delimiter. An application
 * will typically leave that data in the dynamic buffer sequence for a
 * subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a CR-LF sequence is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data, "\r\n", handler); @endcode
 * After the @c async_read_until operation completes successfully, the string
 * @c data contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the string @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until some part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains some
 * data that matches a regular expression. It is an initiating function for an
 * @ref asynchronous_operation, and always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the regular
 * expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains data that matches
 * the regular expression, this asynchronous operation completes immediately.
 * The program must ensure that the stream performs no other read operations
 * (such as async_read, async_read_until, the stream's async_read_some
 * function, or any other composed operations that perform reads) until this
 * operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param expr The regular expression.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer
 *   // sequence's get area up to and including the
 *   // substring that matches the regular expression.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a CR-LF sequence is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data,
 *     boost::regex("\r\n"), handler); @endcode
 * After the @c async_read_until operation completes successfully, the string
 * @c data contains the data which matched the regular expression:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the match,
 * so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the string @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until a function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until a user-defined match condition function object, when
 * applied to the data contained in the dynamic buffer sequence, indicates a
 * successful match. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the match condition function object already indicates a match, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<typename DynamicBuffer_v1::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area that have been fully consumed by the match
 *   // function. O if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the function
 * object. An application will typically leave that data in the dynamic buffer
 * sequence for a subsequent async_read_until operation to examine.
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To asynchronously read data into a @c std::string until whitespace is
 * encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::const_buffers_1> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * std::string data;
 * boost::asio::async_read_until(s, data, match_whitespace, handler);
 * @endcode
 *
 * To asynchronously read data into a @c std::string until a matching character
 * is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * std::string data;
 * boost::asio::async_read_until(s, data, match_char('a'), handler);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * It is an initiating function for an @ref asynchronous_operation, and always
 * returns immediately. The asynchronous operation will continue until one of
 * the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the streambuf's get area already contains the delimiter, this asynchronous
 * operation completes immediately. The program must ensure that the stream
 * performs no other read operations (such as async_read, async_read_until, the
 * stream's async_read_some function, or any other composed operations that
 * perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the completion handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the delimiter.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond the delimiter. An application will typically
 * leave that data in the streambuf for a subsequent async_read_until operation
 * to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     std::string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, '\n', handler); @endcode
 * After the @c async_read_until operation completes successfully, the buffer
 * @c b contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * It is an initiating function for an @ref asynchronous_operation, and always
 * returns immediately. The asynchronous operation will continue until one of
 * the following conditions is true:
 *
 * @li The get area of the streambuf contains the specified delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the streambuf's get area already contains the delimiter, this asynchronous
 * operation completes immediately. The program must ensure that the stream
 * performs no other read operations (such as async_read, async_read_until, the
 * stream's async_read_some function, or any other composed operations that
 * perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the completion handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the delimiter.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond the delimiter. An application will typically
 * leave that data in the streambuf for a subsequent async_read_until operation
 * to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a newline is encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     std::string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, "\r\n", handler); @endcode
 * After the @c async_read_until operation completes successfully, the buffer
 * @c b contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a streambuf until some
/// part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains some data that matches a
 * regular expression. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li A substring of the streambuf's get area matches the regular expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the streambuf's get area already contains data that matches the regular
 * expression, this asynchronous operation completes immediately. The program
 * must ensure that the stream performs no other read operations (such as
 * async_read, async_read_until, the stream's async_read_some function, or any
 * other composed operations that perform reads) until this operation
 * completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read. Ownership of
 * the streambuf is retained by the caller, which must guarantee that it remains
 * valid until the completion handler is called.
 *
 * @param expr The regular expression.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area up to and including the substring
 *   // that matches the regular. expression.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond that which matched the regular expression. An
 * application will typically leave that data in the streambuf for a subsequent
 * async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a streambuf until a CR-LF sequence is
 * encountered:
 * @code boost::asio::streambuf b;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::istream is(&b);
 *     std::string line;
 *     std::getline(is, line);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, b, boost::regex("\r\n"), handler); @endcode
 * After the @c async_read_until operation completes successfully, the buffer
 * @c b contains the data which matched the regular expression:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c std::getline then extracts the data up to and including the
 * newline (which is discarded), so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r' } @endcode
 * The remaining data is left in the buffer @c b as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a streambuf until a
/// function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until a user-defined match condition function object, when applied
 * to the data contained in the streambuf, indicates a successful match. It is
 * an initiating function for an @ref asynchronous_operation, and always
 * returns immediately. The asynchronous operation will continue until one of
 * the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the match condition function object already indicates a match, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A streambuf object into which the data will be read.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<basic_streambuf<Allocator>::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the streambuf's get
 *   // area that have been fully consumed by the
 *   // match function. O if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond that which matched the function object. An
 * application will typically leave that data in the streambuf for a subsequent
 * async_read_until operation to examine.
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To asynchronously read data into a streambuf until whitespace is encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::streambuf::const_buffers_type> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * boost::asio::streambuf b;
 * boost::asio::async_read_until(s, b, match_whitespace, handler);
 * @endcode
 *
 * To asynchronously read data into a streambuf until a matching character is
 * found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * boost::asio::streambuf b;
 * boost::asio::async_read_until(s, b, match_char('a'), handler);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename Allocator, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<is_match_condition<MatchCondition>::value>::type = 0);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains the delimiter, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area up to and including the delimiter.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond the delimiter. An application
 * will typically leave that data in the dynamic buffer sequence for a
 * subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a newline is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data, '\n', handler); @endcode
 * After the @c async_read_until operation completes successfully, the buffer
 * @c data contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the buffer @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers, char delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The get area of the dynamic buffer sequence contains the specified
 * delimiter.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains the delimiter, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area up to and including the delimiter.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond the delimiter. An application
 * will typically leave that data in the dynamic buffer sequence for a
 * subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a CR-LF sequence is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data, "\r\n", handler); @endcode
 * After the @c async_read_until operation completes successfully, the string
 * @c data contains the delimiter:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the
 * delimiter, so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the string @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until some part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains some
 * data that matches a regular expression. It is an initiating function for an
 * @ref asynchronous_operation, and always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li A substring of the dynamic buffer sequence's get area matches the regular
 * expression.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the dynamic buffer sequence's get area already contains data that matches
 * the regular expression, this asynchronous operation completes immediately.
 * The program must ensure that the stream performs no other read operations
 * (such as async_read, async_read_until, the stream's async_read_some
 * function, or any other composed operations that perform reads) until this
 * operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param expr The regular expression.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer
 *   // sequence's get area up to and including the
 *   // substring that matches the regular expression.
 *   // 0 if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the regular
 * expression. An application will typically leave that data in the dynamic
 * buffer sequence for a subsequent async_read_until operation to examine.
 *
 * @par Example
 * To asynchronously read data into a @c std::string until a CR-LF sequence is
 * encountered:
 * @code std::string data;
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size)
 * {
 *   if (!e)
 *   {
 *     std::string line = data.substr(0, n);
 *     data.erase(0, n);
 *     ...
 *   }
 * }
 * ...
 * boost::asio::async_read_until(s, data,
 *     boost::regex("\r\n"), handler); @endcode
 * After the @c async_read_until operation completes successfully, the string
 * @c data contains the data which matched the regular expression:
 * @code { 'a', 'b', ..., 'c', '\r', '\n', 'd', 'e', ... } @endcode
 * The call to @c substr then extracts the data up to and including the match,
 * so that the string @c line contains:
 * @code { 'a', 'b', ..., 'c', '\r', '\n' } @endcode
 * After the call to @c erase, the remaining data is left in the string @c data
 * as follows:
 * @code { 'd', 'e', ... } @endcode
 * This data may be the start of a new line, to be extracted by a subsequent
 * @c async_read_until operation.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until a function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until a user-defined match condition function object, when
 * applied to the data contained in the dynamic buffer sequence, indicates a
 * successful match. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The match condition function object returns a std::pair where the second
 * element evaluates to true.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. If
 * the match condition function object already indicates a match, this
 * asynchronous operation completes immediately. The program must ensure that
 * the stream performs no other read operations (such as async_read,
 * async_read_until, the stream's async_read_some function, or any other
 * composed operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param match_condition The function object to be called to determine whether
 * a match exists. The signature of the function object must be:
 * @code pair<iterator, bool> match_condition(iterator begin, iterator end);
 * @endcode
 * where @c iterator represents the type:
 * @code buffers_iterator<typename DynamicBuffer_v2::const_buffers_type>
 * @endcode
 * The iterator parameters @c begin and @c end define the range of bytes to be
 * scanned to determine whether there is a match. The @c first member of the
 * return value is an iterator marking one-past-the-end of the bytes that have
 * been consumed by the match function. This iterator is used to calculate the
 * @c begin parameter for any subsequent invocation of the match condition. The
 * @c second member of the return value is true if a match has been found, false
 * otherwise.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the read completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // The number of bytes in the dynamic buffer sequence's
 *   // get area that have been fully consumed by the match
 *   // function. O if an error occurred.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the function
 * object. An application will typically leave that data in the dynamic buffer
 * sequence for a subsequent async_read_until operation to examine.
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, std::size_t) @endcode
 *
 * @note The default implementation of the @c is_match_condition type trait
 * evaluates to true for function pointers and function objects with a
 * @c result_type typedef. It must be specialised for other user-defined
 * function objects.
 *
 * @par Examples
 * To asynchronously read data into a @c std::string until whitespace is
 * encountered:
 * @code typedef boost::asio::buffers_iterator<
 *     boost::asio::const_buffers_1> iterator;
 *
 * std::pair<iterator, bool>
 * match_whitespace(iterator begin, iterator end)
 * {
 *   iterator i = begin;
 *   while (i != end)
 *     if (std::isspace(*i++))
 *       return std::make_pair(i, true);
 *   return std::make_pair(i, false);
 * }
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * std::string data;
 * boost::asio::async_read_until(s, data, match_whitespace, handler);
 * @endcode
 *
 * To asynchronously read data into a @c std::string until a matching character
 * is found:
 * @code class match_char
 * {
 * public:
 *   explicit match_char(char c) : c_(c) {}
 *
 *   template <typename Iterator>
 *   std::pair<Iterator, bool> operator()(
 *       Iterator begin, Iterator end) const
 *   {
 *     Iterator i = begin;
 *     while (i != end)
 *       if (c_ == *i++)
 *         return std::make_pair(i, true);
 *     return std::make_pair(i, false);
 *   }
 *
 * private:
 *   char c_;
 * };
 *
 * namespace asio {
 *   template <> struct is_match_condition<match_char>
 *     : public boost::true_type {};
 * } // namespace asio
 * ...
 * void handler(const boost::system::error_code& e, std::size_t size);
 * ...
 * std::string data;
 * boost::asio::async_read_until(s, data, match_char('a'), handler);
 * @endcode
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the @c AsyncReadStream type's
 * @c async_read_some operation.
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_match_condition<MatchCondition>::value
    >::type = 0,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/read_until.hpp>

#endif // BOOST_ASIO_READ_UNTIL_HPP

/* read_until.hpp
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
*/