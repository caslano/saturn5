//
// read.hpp
// ~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

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
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

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
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

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
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

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
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncReadStream,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_mutable_buffer_sequence<MutableBufferSequence>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, buffers,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
 */
template <typename AsyncReadStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * remains valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, b,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
 */
template <typename AsyncReadStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * remains valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncReadStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type));

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read(
 *     s, buffers,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
 */
template <typename AsyncReadStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Start an asynchronous operation to read a certain amount of data from a
/// stream.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions is
 * true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes copied into the
 *                                           // buffers. If an error occurred,
 *                                           // this will be the  number of
 *                                           // bytes successfully transferred
 *                                           // prior to the error.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncReadStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncReadStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read(AsyncReadStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncReadStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/read.hpp>

#endif // BOOST_ASIO_READ_HPP

/* read.hpp
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
*/