//
// write_at.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WRITE_AT_HPP
#define BOOST_ASIO_WRITE_AT_HPP

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
 * @defgroup write_at boost::asio::write_at
 *
 * @brief The @c write_at function is a composed operation that writes a
 * certain amount of data at a specified offset before returning.
 */
/*@{*/

/// Write all of the supplied data at the specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * device.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write_at(d, 42, boost::asio::buffer(data, size)); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write_at(
 *     d, offset, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers);

/// Write all of the supplied data at the specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * device.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write_at(d, 42,
 *     boost::asio::buffer(data, size), ec); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write_at(
 *     d, offset, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    boost::system::error_code& ec);

/// Write a certain amount of data at a specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * device.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's write_some_at function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write_at(d, 42, boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32)); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition);

/// Write a certain amount of data at a specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * device.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's write_some_at function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncRandomAccessWriteDevice, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Write all of the supplied data at the specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write_at(
 *     d, 42, b,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncRandomAccessWriteDevice, typename Allocator>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b);

/// Write all of the supplied data at the specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write_at(
 *     d, 42, b,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncRandomAccessWriteDevice, typename Allocator>
std::size_t write_at(SyncRandomAccessWriteDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec);

/// Write a certain amount of data at a specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's write_some_at function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncRandomAccessWriteDevice, typename Allocator,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d, uint64_t offset,
    basic_streambuf<Allocator>& b, CompletionCondition completion_condition);

/// Write a certain amount of data at a specified offset before returning.
/**
 * This function is used to write a certain number of bytes of data to a random
 * access device at a specified offset. The call will block until one of the
 * following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * write_some_at function.
 *
 * @param d The device to which the data is to be written. The type must support
 * the SyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's write_some_at function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncRandomAccessWriteDevice, typename Allocator,
    typename CompletionCondition>
std::size_t write_at(SyncRandomAccessWriteDevice& d, uint64_t offset,
    basic_streambuf<Allocator>& b, CompletionCondition completion_condition,
    boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/
/**
 * @defgroup async_write_at boost::asio::async_write_at
 *
 * @brief The @c async_write_at function is a composed asynchronous operation
 * that writes a certain amount of data at the specified offset before
 * completion.
 */
/*@{*/

/// Start an asynchronous operation to write all of the supplied data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_write_some_at function, and is known as a <em>composed operation</em>.
 * The program must ensure that the device performs no <em>overlapping</em>
 * write operations (such as async_write_at, the device's async_write_some_at
 * function, or any other composed operations that perform writes) until this
 * operation completes. Operations are overlapping if the regions defined by
 * their offsets, and the numbers of bytes to write, intersect.
 *
 * @param d The device to which the data is to be written. The type must support
 * the AsyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of
 * the handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code
 * boost::asio::async_write_at(d, 42, boost::asio::buffer(data, size), handler);
 * @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d, uint64_t offset,
    const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

/// Start an asynchronous operation to write a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_write_some_at function, and is known as a <em>composed operation</em>.
 * The program must ensure that the device performs no <em>overlapping</em>
 * write operations (such as async_write_at, the device's async_write_some_at
 * function, or any other composed operations that perform writes) until this
 * operation completes. Operations are overlapping if the regions defined by
 * their offsets, and the numbers of bytes to write, intersect.
 *
 * @param d The device to which the data is to be written. The type must support
 * the AsyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param buffers One or more buffers containing the data to be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's async_write_some_at function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::async_write_at(d, 42,
 *     boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32),
 *     handler); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to write all of the supplied data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_write_some_at function, and is known as a <em>composed operation</em>.
 * The program must ensure that the device performs no <em>overlapping</em>
 * write operations (such as async_write_at, the device's async_write_some_at
 * function, or any other composed operations that perform writes) until this
 * operation completes. Operations are overlapping if the regions defined by
 * their offsets, and the numbers of bytes to write, intersect.
 *
 * @param d The device to which the data is to be written. The type must support
 * the AsyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b A basic_streambuf object from which data will be written. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the handler is called.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncRandomAccessWriteDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

/// Start an asynchronous operation to write a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. The function call
 * always returns immediately. The asynchronous operation will continue until
 * one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the device's
 * async_write_some_at function, and is known as a <em>composed operation</em>.
 * The program must ensure that the device performs no <em>overlapping</em>
 * write operations (such as async_write_at, the device's async_write_some_at
 * function, or any other composed operations that perform writes) until this
 * operation completes. Operations are overlapping if the regions defined by
 * their offsets, and the numbers of bytes to write, intersect.
 *
 * @param d The device to which the data is to be written. The type must support
 * the AsyncRandomAccessWriteDevice concept.
 *
 * @param offset The offset at which the data will be written.
 *
 * @param b A basic_streambuf object from which data will be written. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_write_some_at operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the device's async_write_some_at function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
 *   std::size_t bytes_transferred
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncRandomAccessWriteDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d, uint64_t offset,
    basic_streambuf<Allocator>& b, CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/write_at.hpp>

#endif // BOOST_ASIO_WRITE_AT_HPP

/* write_at.hpp
tDT1aPz/NtGjhe4Tnfj1nCc7NroxSIfk3k0S6Ylq3cami/gx6QapWwDW7PngbAV0HvO9c49d9a3G8TXRgqkp6jZ/VkTfOR6PJbxTTp1D5zR1e6PV2KcJZ5zxeQQ9D6bxefB58wyYD8wH5tPPx9h3o9NxtmEKxc3NM77xom2SflzEF0iT51jj5F7Eg+MnCx44T12VxFX9np3bRtvGzciZeZ5z5ShnZrFsf36qNtdsducaxmuy4tCNxpG39P+5vxVxHunAY6XPFeb5OY1bZwI6nzmLbeNZLPXCXCNWc2ys3midxXY2qzjWXhw077uY+hX3mb/m/P04a35lGgLSYtsXYnv/sdTFrHJ1MbJerMae7xSx7qYiLqvxgY01FhvO65OGbVzzC5DfHJ+q3X9bTLsgjt+OiTb6EktW54Iyv52vFPFZUv+5ti8vvjefq90l8j0XYX6KWtfDyU4nJXBSOWAcrk9g/c3LppZMLqp0jXQOdQy2W3cd06j8hfuqu6nLery0vWAR6h5y/2zoliLeQdolfDUmbT4CsYsYZluXq+Nr8B6uVaRr+byl93Sxtf/gOBbeAVii2i+2/YbmR7Kxhn1Xqe/enqu6P9eGz/X31vV1X/cbPBr2+f+pX23DtDWBrXyHLRynlDmi+3FNR9gDsR/0GMwVSzidNHOeNb8rXM70WnSazGkBaZHjPqtnXH32bi9mo98GYqh2VyhZwk2kfdt99yVd7NekAwYnBWAqf1D/NCEda29cpvNs0Kr1YT0Xl7CfdO4TpWzBIvjB2HEEe5tGn/P9NqCbiNLHxzRmf+CeNZdbXd+ANZmObZT09tuT60r4J2n8ST3+OO5Mh0oP/34snxHOOj6dQMrRC/Db27eGY4aEJ9f6TWH1dWF9x5TwdNKpwkNh3vfmezbiehL1fsXc/W3j54vWs/LeyapPBeLOezd8zi6xuCLsuyPo+ooN+r1Wf3t6ZRVLUNU9GIvoXyyibmZufKf/rjIbjUHRKF5ssN/u67/TEefAo/XbaPnFBt/nvv47HfG9j9bvvV3+0vsoVlVYOYUYClHy31u/vrVBnxO1co3gb1n53GH9Bx9bwsWkoafL2ijYPM8vbXu6HebeOu8n8X7Hkv3Gz5+JuZFD31klfJo0LXVQmFmf9bPaj3CKtjFJrcOwZQxfnPepwRLyW0sYfkYPRI/myh0ufjNp1KSRgjDh0cB9t//1X+WPY+b8ErouKOH6ndIuCqv6gaSsMsp17Jkcp6Vy1X7xiNvM6du9rn+Vat+uaaZfnDy6yzmO7wz2PZWy3HAJA+dL3RQWquPte0oJzyS9SvIqLPw+Qi3WzY4SvkKaFB4aM/YI6n6Xp1PdzfhZkyZup3wze55Twu9ISy6wxu50M8tscfHkSAl9Jo2kMM+/EYnPI4Bf7OwEzh5u5f43wftDjj9PO25oEiPs25+TrpAyNKbjvB75eXDIXYeBF5Swm7ThmdZcEYDreM613/MSOM/xE8t5snvY+IkNj52956UlfI50pV2exk3/9SeNTlx4sE37XlzCO0m32zwCcSgsvF5DF5XwBlL/LounD69fr4ELS/gwadTmEYhDYeH16ntJCeeRbrR52niUer2QZZFSz1L10jhJY7G1cay19s/h9gPGx0a8qpMZLeEhpIuFt4XNc21MR5tb6z43318zX+m7m68t4Y+kkWfLuyrMm6c4R7GPF2+szlN1fW1svBfiiEaNUVZHBtbzwFFr+2xVb6Zt53S7uH7sNruekr1zq4R7blWizVpqIlmd295SwuNJ9zzHZ7fvYleRUiPSX0GY5FdnACwDE+JPTD8X29uGvXxuB597PPeHZ5Vbq3Xtq2MjviuBXf3KF5ltn7U=
*/