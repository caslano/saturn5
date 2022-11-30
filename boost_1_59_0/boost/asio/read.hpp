//
// read.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_READ_HPP
#define BOOST_ASIO_READ_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/error.hpp>

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# include <boost/asio/basic_streambuf_fwd.hpp>
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/**
 * @defgroup read boost::asio::read
 *
 * @brief The @c read function is a composed operation that reads a certain
 * amount of data from a stream before returning.
 */
/*@{*/

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read(s, boost::asio::buffer(data, size)); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncReadStream, typename MutableBufferSequence>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read(s, boost::asio::buffer(data, size), ec); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncReadStream, typename MutableBufferSequence>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read(s, boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32)); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename SyncReadStream, typename MutableBufferSequence,
  typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncReadStream, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncReadStream, typename DynamicBuffer_v1>
std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncReadStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, b,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, b,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncReadStream, typename Allocator>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncReadStream, typename Allocator,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncReadStream, typename DynamicBuffer_v2>
std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Attempt to read a certain amount of data from a stream before returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * stream. The call will block until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * read_some function.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the SyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's read_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncReadStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t read(SyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/*@}*/
/**
 * @defgroup async_read boost::asio::async_read
 *
 * @brief The @c async_read function is a composed asynchronous operation that
 * reads a certain amount of data from a stream before completion.
 */
/*@{*/

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream. Although the buffers object may be copied as necessary, ownership of
 * the underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code
 * boost::asio::async_read(s, boost::asio::buffer(data, size), handler);
 * @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, buffers,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
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
template <typename AsyncReadStream, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * stream. Although the buffers object may be copied as necessary, ownership of
 * the underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's async_read_some function.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::async_read(s,
 *     boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32),
 *     handler); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
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
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, buffers,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
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
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's async_read_some function.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
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
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A basic_streambuf object into which the data will be read. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the completion handler is called.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, b,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
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
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The supplied buffer is full (that is, it has reached maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param b A basic_streambuf object into which the data will be read. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's async_read_some function.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, buffers,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
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
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
 *
 * @li The specified dynamic buffer sequence is full (that is, it has reached
 * maximum size).
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_read_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other read operations (such
 * as async_read, the stream's async_read_some function, or any other composed
 * operations that perform reads) until this operation completes.
 *
 * @param s The stream from which the data is to be read. The type must support
 * the AsyncReadStream concept.
 *
 * @param buffers The dynamic buffer sequence into which the data will be read.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the stream's async_read_some function.
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
 *   // Number of bytes copied into the buffers. If an error
 *   // occurred, this will be the number of bytes successfully
 *   // transferred prior to the error.
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
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/read.hpp>

#endif // BOOST_ASIO_READ_HPP

/* read.hpp
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
*/