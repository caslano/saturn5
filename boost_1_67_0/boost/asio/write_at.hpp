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
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
*/