//
// read_until.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<is_match_condition<MatchCondition>::value>::type* = 0);

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
    typename enable_if<is_match_condition<MatchCondition>::value>::type* = 0);

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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
 * std::string n = boost::asio::read_until(s,
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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
        is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
 * specified delimiter. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers, char delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until some part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains some
 * data that matches a regular expression. The function call always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
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
 * that they remain valid until the handler is called.
 *
 * @param expr The regular expression.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until a function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until a user-defined match condition function object, when
 * applied to the data contained in the dynamic buffer sequence, indicates a
 * successful match. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the function
 * object. An application will typically leave that data in the dynamic buffer
 * sequence for a subsequent async_read_until operation to examine.
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
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * The function call always returns immediately. The asynchronous operation
 * will continue until one of the following conditions is true:
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
 * valid until the handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, char delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

/// Start an asynchronous operation to read data into a streambuf until it
/// contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains the specified delimiter.
 * The function call always returns immediately. The asynchronous operation
 * will continue until one of the following conditions is true:
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
 * valid until the handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a streambuf until some
/// part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until the streambuf's get area contains some data that matches a
 * regular expression. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * valid until the handler is called.
 *
 * @param expr The regular expression.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b, const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a streambuf until a
/// function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified
 * streambuf until a user-defined match condition function object, when applied
 * to the data contained in the streambuf, indicates a successful match. The
 * function call always returns immediately. The asynchronous operation will
 * continue until one of the following conditions is true:
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the streambuf may
 * contain additional data beyond that which matched the function object. An
 * application will typically leave that data in the streambuf for a subsequent
 * async_read_until operation to examine.
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
 */
template <typename AsyncReadStream, typename Allocator, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s,
    boost::asio::basic_streambuf<Allocator>& b,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<is_match_condition<MatchCondition>::value>::type* = 0);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
 *
 * @param delim The delimiter character.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers, char delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until it contains a specified delimiter.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains the
 * specified delimiter. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
 *
 * @param delim The delimiter string.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_STRING_VIEW_PARAM delim,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if defined(BOOST_ASIO_HAS_BOOST_REGEX) \
  || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until some part of its data matches a regular expression.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until the dynamic buffer sequence's get area contains some
 * data that matches a regular expression. The function call always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
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
 * that they remain valid until the handler is called.
 *
 * @param expr The regular expression.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    const boost::regex& expr,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)
       // || defined(GENERATING_DOCUMENTATION)

/// Start an asynchronous operation to read data into a dynamic buffer sequence
/// until a function object indicates a match.
/**
 * This function is used to asynchronously read data into the specified dynamic
 * buffer sequence until a user-defined match condition function object, when
 * applied to the data contained in the dynamic buffer sequence, indicates a
 * successful match. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note After a successful async_read_until operation, the dynamic buffer
 * sequence may contain additional data beyond that which matched the function
 * object. An application will typically leave that data in the dynamic buffer
 * sequence for a subsequent async_read_until operation to examine.
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
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename MatchCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_until(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    MatchCondition match_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_match_condition<MatchCondition>::value
        && is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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