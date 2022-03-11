//
// read_at.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
 * data from a random access device at the specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
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
 * that they remain valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncRandomAccessReadDevice, typename MutableBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d, uint64_t offset,
    const MutableBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
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
 * that they remain valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
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
 */
template <typename AsyncRandomAccessReadDevice,
    typename MutableBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, const MutableBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
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
 * remains valid until the handler is called.
 *
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::async_read_at(
 *     d, 42, b,
 *     boost::asio::transfer_all(),
 *     handler); @endcode
 */
template <typename AsyncRandomAccessReadDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessReadDevice::executor_type));

/// Start an asynchronous operation to read a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously read a certain number of bytes of
 * data from a random access device at the specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
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
 * remains valid until the handler is called.
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
 * @param handler The handler to be called when the read operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
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
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncRandomAccessReadDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) ReadHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessReadDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
    void (boost::system::error_code, std::size_t))
async_read_at(AsyncRandomAccessReadDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(ReadHandler) handler
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