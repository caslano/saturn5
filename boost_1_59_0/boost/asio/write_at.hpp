//
// write_at.hpp
// ~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
 * data to a random access device at a specified offset. It is an initiating
 * function for an @ref asynchronous_operation, and always returns immediately.
 * The asynchronous operation will continue until one of the following
 * conditions is true:
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
 * that they remain valid until the completion handler is called.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the write completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
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
 * To write a single data buffer use the @ref buffer function as follows:
 * @code
 * boost::asio::async_write_at(d, 42, boost::asio::buffer(data, size), handler);
 * @endcode
 * See the @ref buffer documentation for information on writing multiple
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
 * if they are also supported by the @c AsyncRandomAccessWriteDevice type's
 * async_write_some_at operation.
 */
template <typename AsyncRandomAccessWriteDevice, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d, uint64_t offset,
    const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

/// Start an asynchronous operation to write a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. It is an initiating
 * function for an @ref asynchronous_operation, and always returns immediately.
 * The asynchronous operation will continue until one of the following
 * conditions is true:
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
 * that they remain valid until the completion handler is called.
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the write completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
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
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::async_write_at(d, 42,
 *     boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32),
 *     handler); @endcode
 * See the @ref buffer documentation for information on writing multiple
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
 * if they are also supported by the @c AsyncRandomAccessWriteDevice type's
 * async_write_some_at operation.
 */
template <typename AsyncRandomAccessWriteDevice,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to write all of the supplied data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. It is an initiating
 * function for an @ref asynchronous_operation, and always returns immediately.
 * The asynchronous operation will continue until one of the following
 * conditions is true:
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
 * remains valid until the completion handler is called.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the write completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
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
 * if they are also supported by the @c AsyncRandomAccessWriteDevice type's
 * async_write_some_at operation.
 */
template <typename AsyncRandomAccessWriteDevice, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d,
    uint64_t offset, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncRandomAccessWriteDevice::executor_type));

/// Start an asynchronous operation to write a certain amount of data at the
/// specified offset.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a random access device at a specified offset. It is an initiating
 * function for an @ref asynchronous_operation, and always returns immediately.
 * The asynchronous operation will continue until one of the following
 * conditions is true:
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
 * remains valid until the completion handler is called.
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the write completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
 * @code void handler(
 *   // Result of operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes written from the buffers. If an error
 *   // occurred, this will be less than the sum of the buffer sizes.
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
 * if they are also supported by the @c AsyncRandomAccessWriteDevice type's
 * async_write_some_at operation.
 */
template <typename AsyncRandomAccessWriteDevice,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncRandomAccessWriteDevice::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write_at(AsyncRandomAccessWriteDevice& d, uint64_t offset,
    basic_streambuf<Allocator>& b, CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
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