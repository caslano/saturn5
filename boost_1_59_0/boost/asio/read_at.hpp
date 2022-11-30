//
// read_at.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_READ_AT_HPP
#define BOOST_ASIO_READ_AT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/error.hpp>

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
# include <boost/asio/basic_streambuf_fwd.hpp>
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/**
 * @defgroup read_at boost::asio::read_at
 *
 * @brief The @c read_at function is a composed operation that reads a certain
 * amount of data at the specified offset before returning.
 */
/*@{*/

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read_at(d, 42, boost::asio::buffer(data, size)); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read_at(
 *     d, 42, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read_at(d, 42,
 *     boost::asio::buffer(data, size), ec); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read_at(
 *     d, 42, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    boost::system::error_code& ec);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's read_some_at function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To read into a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::read_at(d, 42, boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32)); @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's read_some_at function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncRandomAccessReadDevice, typename MutableBufferSequence,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read_at(
 *     d, 42, b,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncRandomAccessReadDevice, typename Allocator>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::read_at(
 *     d, 42, b,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncRandomAccessReadDevice, typename Allocator>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's read_some_at function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition);

/// Attempt to read a certain amount of data at the specified offset before
/// returning.
/**
 * This function is used to read a certain number of bytes of data from a
 * random access device at the specified offset. The call will block until one
 * of the following conditions is true:
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the SyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param b The basic_streambuf object into which the data will be read.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's read_some_at function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes read. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncRandomAccessReadDevice, typename Allocator,
    typename CompletionCondition>
std::size_t read_at(SyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/
/**
 * @defgroup async_read_at boost::asio::async_read_at
 *
 * @brief The @c async_read_at function is a composed asynchronous operation
 * that reads a certain amount of data at the specified offset.
 */
/*@{*/

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. It is an
 * initiating function for an @ref asynchronous_operation, and always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the AsyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device. Although the buffers object may be copied as necessary, ownership of
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
 * boost::asio::async_read_at(d, 42, boost::asio::buffer(data, size), handler);
 * @endcode
 * See the @ref buffer documentation for information on reading into multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read_at(
 *     d, 42, buffers,
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
 * if they are also supported by the @c AsyncRandomAccessReadDevice type's
 * async_read_some_at operation.
 */
template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d, uint64_t offset,
    const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. It is an
 * initiating function for an @ref asynchronous_operation, and always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
 *
 * @li The supplied buffers are full. That is, the bytes transferred is equal to
 * the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * @param d The device from which the data is to be read. The type must support
 * the AsyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param buffers One or more buffers into which the data will be read. The sum
 * of the buffer sizes indicates the maximum number of bytes to read from the
 * device. Although the buffers object may be copied as necessary, ownership of
 * the underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's async_read_some_at function.
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
 * @code boost::asio::async_read_at(d, 42,
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
 * if they are also supported by the @c AsyncRandomAccessReadDevice type's
 * async_read_some_at operation.
 */
template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. It is an
 * initiating function for an @ref asynchronous_operation, and always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the AsyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
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
 * @code boost::asio::async_read_at(
 *     d, 42, b,
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
 * if they are also supported by the @c AsyncRandomAccessReadDevice type's
 * async_read_some_at operation.
 */
template <typename AsyncRandomAccessReadDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. It is an
 * initiating function for an @ref asynchronous_operation, and always returns
 * immediately. The asynchronous operation will continue until one of the
 * following conditions is true:
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_read_some_at function.
 *
 * @param d The device from which the data is to be read. The type must support
 * the AsyncRandomAccessReadDevice concept.
 *
 * @param offset The offset at which the data will be read.
 *
 * @param b A basic_streambuf object into which the data will be read. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the completion handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the read operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_read_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the read operation is complete. A non-zero
 * return value indicates the maximum number of bytes to be read on the next
 * call to the device's async_read_some_at function.
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
 * if they are also supported by the @c AsyncRandomAccessReadDevice type's
 * async_read_some_at operation.
 */
template <typename AsyncRandomAccessReadDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/read_at.hpp>

#endif // BOOST_ASIO_READ_AT_HPP

/* read_at.hpp
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
*/