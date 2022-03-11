//
// write.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WRITE_HPP
#define BOOST_ASIO_WRITE_HPP

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
 * @defgroup write boost::asio::write
 *
 * @brief The @c write function is a composed operation that writes a certain
 * amount of data to a stream before returning.
 */
/*@{*/

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * stream.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write(s, boost::asio::buffer(data, size)); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncWriteStream, typename ConstBufferSequence>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * stream.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write(s, boost::asio::buffer(data, size), ec); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncWriteStream, typename ConstBufferSequence>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * stream.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::write(s, boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32)); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers One or more buffers containing the data to be written. The sum
 * of the buffer sizes indicates the maximum number of bytes to write to the
 * stream.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncWriteStream, typename ConstBufferSequence,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncWriteStream, typename DynamicBuffer_v1>
std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncWriteStream, typename DynamicBuffer_v1>
std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncWriteStream, typename DynamicBuffer_v1,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, b,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncWriteStream, typename Allocator>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b);

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, b,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncWriteStream, typename Allocator>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    boost::system::error_code& ec);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param b The basic_streambuf object from which data will be written.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncWriteStream, typename Allocator,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition, boost::system::error_code& ec);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all()); @endcode
 */
template <typename SyncWriteStream, typename DynamicBuffer_v2>
std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Write all of the supplied data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes transferred.
 *
 * @note This overload is equivalent to calling:
 * @code boost::asio::write(
 *     s, buffers,
 *     boost::asio::transfer_all(), ec); @endcode
 */
template <typename SyncWriteStream, typename DynamicBuffer_v2>
std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @returns The number of bytes transferred.
 *
 * @throws boost::system::system_error Thrown on failure.
 */
template <typename SyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Write a certain amount of data to a stream before returning.
/**
 * This function is used to write a certain number of bytes of data to a stream.
 * The call will block until one of the following conditions is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * write_some function.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the SyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Successfully written data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's write_some function.
 *
 * @param ec Set to indicate what error occurred, if any.
 *
 * @returns The number of bytes written. If an error occurs, returns the total
 * number of bytes successfully transferred prior to the error.
 */
template <typename SyncWriteStream, typename DynamicBuffer_v2,
    typename CompletionCondition>
std::size_t write(SyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition, boost::system::error_code& ec,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/*@}*/
/**
 * @defgroup async_write boost::asio::async_write
 *
 * @brief The @c async_write function is a composed asynchronous operation that
 * writes a certain amount of data to a stream before completion.
 */
/*@{*/

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
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
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code
 * boost::asio::async_write(s, boost::asio::buffer(data, size), handler);
 * @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename AsyncWriteStream, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied buffers has been written. That is, the
 * bytes transferred is equal to the sum of the buffer sizes.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
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
 *   // Result of latest async_write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's async_write_some function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * To write a single data buffer use the @ref buffer function as follows:
 * @code boost::asio::async_write(s,
 *     boost::asio::buffer(data, size),
 *     boost::asio::transfer_at_least(32),
 *     handler); @endcode
 * See the @ref buffer documentation for information on writing multiple
 * buffers in one go, and how to use it with arrays, boost::array or
 * std::vector.
 */
template <typename AsyncWriteStream,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called. Successfully written
 * data is automatically consumed from the buffers.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called. Successfully written
 * data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's async_write_some function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
        && !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type* = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param b A basic_streambuf object from which data will be written. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the handler is called.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type));

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied basic_streambuf has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param b A basic_streambuf object from which data will be written. Ownership
 * of the streambuf is retained by the caller, which must guarantee that it
 * remains valid until the handler is called.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's async_write_some function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li An error occurred.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called. Successfully written
 * data is automatically consumed from the buffers.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. The function call always returns immediately. The
 * asynchronous operation will continue until one of the following conditions
 * is true:
 *
 * @li All of the data in the supplied dynamic buffer sequence has been written.
 *
 * @li The completion_condition function object returns 0.
 *
 * This operation is implemented in terms of zero or more calls to the stream's
 * async_write_some function, and is known as a <em>composed operation</em>. The
 * program must ensure that the stream performs no other write operations (such
 * as async_write, the stream's async_write_some function, or any other composed
 * operations that perform writes) until this operation completes.
 *
 * @param s The stream to which the data is to be written. The type must support
 * the AsyncWriteStream concept.
 *
 * @param buffers The dynamic buffer sequence from which data will be written.
 * Although the buffers object may be copied as necessary, ownership of the
 * underlying memory blocks is retained by the caller, which must guarantee
 * that they remain valid until the handler is called. Successfully written
 * data is automatically consumed from the buffers.
 *
 * @param completion_condition The function object to be called to determine
 * whether the write operation is complete. The signature of the function object
 * must be:
 * @code std::size_t completion_condition(
 *   // Result of latest async_write_some operation.
 *   const boost::system::error_code& error,
 *
 *   // Number of bytes transferred so far.
 *   std::size_t bytes_transferred
 * ); @endcode
 * A return value of 0 indicates that the write operation is complete. A
 * non-zero return value indicates the maximum number of bytes to be written on
 * the next call to the stream's async_write_some function.
 *
 * @param handler The handler to be called when the write operation completes.
 * Copies will be made of the handler as required. The function signature of the
 * handler must be:
 * @code void handler(
 *   const boost::system::error_code& error, // Result of operation.
 *
 *   std::size_t bytes_transferred           // Number of bytes written from the
 *                                           // buffers. If an error occurred,
 *                                           // this will be less than the sum
 *                                           // of the buffer sizes.
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 */
template <typename AsyncWriteStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteHandler>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
    typename enable_if<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type* = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/write.hpp>

#endif // BOOST_ASIO_WRITE_HPP

/* write.hpp
6sk1ZXiHNq3S32rF9uOccr8iTn6Ea0UPZxeXveAmN6HYtXm6TOYwmZVym/fe9QnYubDL0TT1p7yoXyiEHzmVDSOvlnEJrFRMTELSz7L2uBe53SUFPybTzqkj4fTn5TFTYjFlaMDkEMTNhE2+i7SQ2O51o5yXgJw0lfMUROCkrM9qF5FGuia4Vk9L/XXERBUVNRWVougJpBbbw9qZ9+n30vXEBWdZRtc6fRv30r6KFqDzAkDG0Jmmm2TyqH7+7dvewk3oOPJXXpvUGz13D0/mVipTIVXjKSSM7OJCgcaZO3ncjGJ+x3690rAzTr5b7JqxwON6LiR2+G/GAtqfd9+Co21gMqFBFG9NETkaWZcOn3QiJUgx8RCZmoZj2gxq7LOxMypElu+a1DA84Ch5RvcxqfuOGxpbs4QxV3REEh1eh+SdZ1/rQSVSCSRsAghtGCzSBtOm3YJ7w94ZJ68sbuC1FCIpeSw6s70oUceo1c/SJ1MqzY3++ko4GhfUck/7EkWtrxw6z7X4QM4x7ib+jnb8LK/vDJHs1g91VDWlBmjZWSnORO7P3QfIei+9IW7VuqUf2WYPG8Uh3Wavm06h76ktNY7ENTPIDNFcjvtVxqZuwyYjFUcEZnFDNVGE8Kdjdm0J7dVlI8DKOZqTK11ZRKU4HbY9yiqZNSda+q0Z0gMXf0uuSZzADwBSpA+WUd4utauTXZnZ2A2mbN0yGKcQplgsJ5aMEF5N1kwYXkfWpxXWqQHkJwpQqeE88H8k0vQnSJfWwyHMPbZau70X5SXcjGRv8JFv/5msvMvg4az95y0tzoFzaD0UBmfg2q0qNYw6Bu4EU4NNYhEnHP5vUyz2OqXskfGmWTSQAU0rFzGHvWplKobAPIse4U4Br3UcZWJLlc8yvOKX/bBiBb2uJuHjfGURdoBWoONmTc6k9drulZOgj36LvjvFaTAsZ5PpAGquckguMgrykTwy8EP1yXujbyhF41qzZ4LCtrl7SzSjjMq08IedJXZWcZV5BdeBcpEiT5OsTPwS04vKB5Lp8kegIeBzMb01exj9HYqqjeqw+rOLh3ejta037JX7xtBsGTNoGIoO3kO0JVldqFQbooOvt+B9WLT5fNsjsWwHUS31KE//55vGC8QsYXk5KyAoZHh6wTVPpvVBgrGvUbuBGM75kLsi/0WLaDjQsnNxY2TUS8C7sVgOH8tIjAwsPoAFMLiRpZkfwDGJMYkX3ttbmhA+JKmjJqY8ACk8WTM5LCQjA2t8cBDE2ORI38BI37TM0LS08J0iswaIgqUCnhgKviIwoyappiijBqcinBGrojogoWMGSG6I2Mrqy0qV39SU1tQVHw0KDH68f/pFSRUStnV0VhRfXNdvehLYMUivCRH+raSberovVW1jG0h4EtBYsbHFhRBE8FhSWpGVtLWY7xK4QKTlXX04JINjRGMk4Hr60HqbH4HWwZbV1sFVlUBBVryF3R+w2Ntam1B70JB60Ho7u9A63pwfloDVgJbBwRXB1dSVgID1Px1SFDcu+KRQxPFgCR0s8UlByGUTT4hGBhdGohPDIOSbM1QQflpyAEjgoV2h/95w1cXNofwDBYH4B/QFe2sAyNUxAJaNHACQvf8DgCRABQgJBvQXfPmPv6D8v3z5if/kzeFxOEEAKDcAAVIC4d6SerBzoLGzt7H5ScGtp62zrcGTkw0fD5MhCw+h+UVlgSdTVgoYgPfrZIr19SEdiU2+F3D5LAkM9431Taw+rIIaf0Z/WmdZ40ONExnYXJdN/cSfnFb8jh+tEF/0ksA52CG2Oi340ENCUqKSQ0TQEqNikMZHJxKSj8Z0SLCtc27wGUrEc7CzBaQZ+UAmpSlhQVljXUFh8bGIXvNuH4lK/QGSqMfXt/fjOii5h50/Okgl8cW0zMCIxGfY/Wo2hAj8aIjG6ky+NpSptamnpQ9PVWXxwUgdqMadKCAZG1lAvy352ja+3W+BP2iLXx+na9s38QoRcGLbuoqa9AMpohVlY28FffQ1LqGoW0fHp28APRv2DQrMMn3sbpHdbHV3zcF2cfJuaxO394bB33STqGNoKciGPbVf94bJJ3Rwj6RVOc3VLtFoU3IoLNgsqxl3dmo0LIMMd6qaDGuZFZ8llmkG7CIl2UCpG1nHQNJq6VoAAiz90wckkACllHGdZKI5ejdn8gujOzID6O8Urpbxr5QvJXolxqqGPM9KjkYLOBD3WgoS673qsqy0Er3OLJXWrkyz5p3S43efW6LM44IBcwSzHkPXDxtom0ZJri6hE3e2aEinJHHkBrd6HoMl91dOK8zXNip6nmQujKZzdJ9CYhIjznKhzFqWPCFZNKUgWTI/znTDxsx04uBPZ2W/72y9LbFcTm0m5/oO+gdWQY22lKkqN9ryVlcqVl2tLiKVM9Lnhxk1Ddfk1JRrqSSYQzC21Lcr1Jyqqk5ukSmPrjnAgshlliXKadp65BzMjAMJ7/cPwVLO7hGim31mEwsohdhR0auNsvqbkJ/NWJGzNCVD7ll3cZJORLbPVDfSgVh3C2KEpsGiN0llcHiMpmeMiSiAuCi+ECvzEMmzOomXnLJaIhP53LROMzrTRqhtpb0Q8ws3Dso8a1eKOt5mdKLHKhpYFrDB4kxUmTObQR41kDJz8QtIGMyZ4hnTPMT4ikTjjDKyaF+LI5frXzcI9vX5IQNsqCMx4hcx7le5dh8uvpr36gexpn64QR5yGSqL1yhSVucaz1dyCQwjutDWt9DnHqWLmt2bXR7TZfp4u5StGr4SpTgrsujx9rwbh6TD2hjpLnVeoVT4Lho2nERdX4hQXHMkl1YARW/c5ibMipU2T+6m0a4ZJus2emekHKczXme0weiGqdoQz+m5B6omIEXaqHGZcwi8O+5SBzwytJ5bZyZCkvF1dzjT4TRx+MtY9VAK8TqFpRdSqJR0oWgg6gaZTE2tNsKgYxA41XZ4H0AxqYkv7lYfJQd++K/NgwaVcy3Xkp+wPJ9yiZ2IR5LYFLriSshdeOfooUb0bmmGbZ+z+NZ2pVQp7QyKLBpp2tBH95ZTp854VhtRDlS9CzAOPXKDRZoxrHoqgbCVeX1SrvL3FDQ7mXngthYFtJFr2ifHbLUM1mZXpczCKyohSgymtSupKLG5WSXebt5yijD2oRb2zYwttXZRezXRz10axffGwxszdlUZfr1abPw6CTcR25PAL6AEtS7xHbJgyzpazue0gzfRguMa2F1I4p/KBoVq+cp7Nm0K9ID8X3ZUoTZ6orvus91W0YW1nxYGZXq1AvMY6Lz7ucApEaiPdTYDd60qAvMkPfjGl7YpabK0WhUofsvJTDXKK8tX9zp1fMiXQ7yxX1zmKewICoy5x44yEounU9ZtdYA5roM1J1PQ5MZEc0AZ13m8CIhicS1OSM824BDyASVTzcqa6GQ8qngJVDbKVYpu9g8ufFWBd3r0J66CM5eTn0gXvTZAGnXofQr+PWd9AhiQNIuONP92PTQ+1UWEkmqrkAkbBAWsD4Q/qN+iv+Zlq34fXlXM7mC3kzssXosXQ1evQEtM6w4Hz1TGQzl3O0GMQadjy7cNLe4pO0iacsOmSjfGneSePgRjTMlNgnbPU4gECK1BqZVK+InBCa1D7Y4iNO8hVeUUh0AWPe9dKngK1mmbPxkHfY3Siy/aXoKmcVGwa90Q4+zhtjbAmurSepwmOmGsfFn025fkuZPXJzJVaWSfM+IK8QXKmngYq2DXUbVjUfHN11mL2hAg/hcktj7ntGJUVsE0VnYwYTPeXMIa/WJGGuPki4ga871ZYKTwucDTx71T1Ew+WtALeGjQc4evWA0RfMxDxeeBwPeKkcMPeSbt0Bc6F9SSeNKKJoFx6xtDcHOVGeKqVwGKXGYMoXTxYrYRm8e4Ss0FaSUy3NdEMFemI0MvMYw+MUX2fYh8PJBB3x1Ilttov7x01PDMmKyGm8ByByrtfmAcS7mFSW5DJ1y8LjTkp/yZ/fgzM98Z8+ENBO+SsrEwR+yEsFflDmpHKmlT12Biou2Y6ajO4qYgcZexgCSJYPH+rqiE7vS0/3hJy4ynkBSRrcQeQCqLVVv4hayxefIeoSZmQJXfu414oPJIHGUiyrSgBGE3F51AODHpYQiZgX/MgcOzPkRuKENLhDyrzAaiTvZ4X/qyekCGQ3ctFW8uL7aqG8O6VcHJroE0mhjlI70CiQVtnsqqRN7qQHcB6lK9Ng/P4eTohc/xSXTXXpaKUn2+8DJP2e4ljYh5NfK2HHarAE2YGiLQJqwRSWhyOMpqLB7ClRmx3ilANDrHiOoXujh+lqnKFLT4qPWkiyx2VlD5rq/e77IR03Zv3M9H90L75g00MuFIZVtkDpcrLyA/NskXQJj0HWVO4xQfuohe6hHI/oXbQJTudCmNLIv8sJS+0MTMsa8dDYH4H4caGpELxFV2KRm1VAdHwkoIMohKoFmbkXPxpCTk0zNors7TqLX/i/hCVQdmLDuKLYsnJi7jVDNbKHajKDgxBgrjwBHE4Fze/BzVjLU0bUaIWklj2zphU1ctVi47qv8aGqAXldwnzGWkhneMzrWa/HfayGm69I786vDtq7FMouE5kiqXyhaRw9w+pGWZQfgcEf2ebQ82QbU4QzXxRA4DU/Jw1R31qIT4OIKTlA9OeHFUjpKwgWsh50NCI/nJ6G/P0bH7l/3KtnoeH+AZ2oOjXJ8vK6Rk7RI/rt5qsIv+RoCc3pA8MCwlS4kkf4uVu5ekOApm3Zl2TyRdlaLLi+OpsPEPUyyNbG031VxF09mCyD8LQ4zORv5Unw663MEemwIZc+52SIlc5J0qQ3PHQUUk7ascnYjTRB731vtLx54kRY6sRDKzAHVGARI0GJzngezVIEz+QGTv3E1T0ENX7h9wFOyFk+/RCemapY/x2NO5rrQ3PTBiYTgNwoaa8qNBaJ1mCvkrefhe6+6rNnZE1JtMWTMNsbfDMKW1OksBT2zpANnzpneP6tgSrWvPzm6y/+Q4ab4zA8PeP0VBwy+EUtbsz6DBAFuejkH7Hs8ikFaxl89OS61S5/I5YBvMg0NSbFBzLkInMzFesXxixqLSiFmCLgF7wFe/NOLVFZEpSmHMs/qCibPy0HXLjlH7GkNvQZ5ukcmcu4+SvbpMLAnU2fmTKyRTj1Ta3xrPOI3lM3B0sSicmZbeGUK+1wxd2rvKr4DnvAL+e/wEDw0PbI1Fi8kK2ytzrP3I6a92Es0484wd4wWWfHG9Ncj2f+KhnbOCjpmq0wGkRN2Tzt5Yuv0Qz+QlXlsrS59YosgEcXTjji3nWeqvNvTwcbhdbahuPW8xn0tkboooMFdGu8HyXkTpTdmFDwoDfWwnhcbeyTgOmJkhPW7kpofyKA0RPWiuK+z7PC3hqjpoZf18zl287OVj5tWNT70OP62YuWR+GHGHGE1o3v1OuV6dD7F+3ZEzqN3T3lLw5+Z+PhyngjdEQ/oJ1YJIy0zJbRFXNd3hSUcwllSs8pUVI9tCGseg5H4y+RVMERFdzG726mqXsRIuQN60Kjqu+s+kiahJT/Kns715AOZDXf7p1aMqpLXzyMSKz/nCgY3DIpQIcGQ8i+i+YaxjIT3Fbn+Yl2ik1eFHAq6cyLbvsnuOMJLV6Ez5ztzEfxishCje3FIKhct+KS37rYvA1eA82GUEtm2Xaqdy+uM/vWJckYwRCYddur3alnnP51GrMFe0rvo73jthNxeiNNfNTVzDC7UZms1bXbE0fQYVvU28vwmum1a5/UWELr/rK6lv4P2KXXN6RkJwA4LRPnQecZIfPPTNAq7I47/x5/1JDIqg7OYM/F7wJMjxmQiJSUxGQrQfCvh3ivhFk8V4tmYADA4ed+DV6WJtPg/LVf7FPB9Wq3C3kS+mCUnIr42qJlMikMYv6cYkQA0/Ug7xAGu4Y6H/fCno1+pAfiZsPi98pSdnQ2XhvuIc6SGyuDgo/bGFrWturG1wsaFow/cMTa7yrc30gQ0RQTrSsQKSiYP9HtCERZR9H1F9HUjF8bCRSF2cjsDGAAUlAqdlZrLxcyGTGqsDikgo4r/LHL8Ptbbl9vAA4v3YOwCM+uHW7GHxAf39vtBvH4jc2dnbyeT2EXINCXlEhL0jw2IDAiWC5QSlg+XExT+iEyKTs3MD4+Mzk0JzMcZHR0UFR2bmRgbHxidHHfcA+YPA9IFg9QHg8ZBgAGJA2+3A9AW0Zfvv6NjD0ZGe4xT7v6n3KaaD1iBhAMABM6Vc6QB+x9Amv6fzcglvf0mL7BsaflMUfsKu/WEahvAyvx6IwrPBUQBgns/dKM2hpalFgITIS/a0iCmOo7zPmJlCUL6wmcWkxtN+1ZAkNdvSmFc5F5JGDEmkEFCtNFvWZ3gNQeCWb0hcGYIbuf3gf/TyS8twkaAE2Kik0kT0sULzzYYw4M5/SV2P6To54t/7KvKanBx+sZ6dssN8fz5jYUG+70dJQp2d0cnL9ywX8hdQCuih/Y/p++4uws4XWqLHJrqVcqNqycImwjIjfAw1MnaJbk1RUAC1YFA0NYllPTWhocldpKHXG36g2BsEGAnBBOLFLc4Mry6KhtYu9hGcmn4zgFmFwza3RKPKTiLDctVIdd3UkoW0JtqOj++L7X6f+A+6OJhL2ztuTN9HtioZzLUS7mgZlYzNqV77rqhQrRfYxHM/1OY47vus4gdmP+ZAMbB/g4Ki+94cgoK+uYqiFxYWwAgMN3S/8YgEi/rkiHzwLzE+e78UJERpYn7wSILfqYgavtgwIlDe7HjP/f3QnfcFrwGfwtKQMTlH72yWUmhIhXDFqWRyxHJyM3DR34OKEyaAFn4bRvKYydZtiDvIYDIbR1/t2B1/Q+vhE8d1foy8PWpfy/57tL2Th8mDBAHAS2o9+skdNn5Qcv8uAzujq5782Ft5Zl//6fEz3NfH7cRivcybjhF98SqitVgjGOhGNxUKRHBcGmr4NCKCgukjIxEJCQuBlujruGz9EoACoYv+QIW8/wChoIx9CqTal/Md0UsPv+mrOnJw/PLKAse9ZRAWeLgXDQ4J+bSpGtSnEBwyFOMdVFaMRcf4Duo5rfX5vVYVcNDEjp/+d9eW849jKsK4S9prU4334Fw9Nx2NOi7vaS9zXzQ2j2l9KqXS0FP764bVwl5Xnrtuy8IeFoSYWuty9Dayse3g8Sbyu6y5+XxVoAYB1XHHrxeh2sMvL7op1Lb+4+MLlFxUqKy4rrUv7kWqxjfbyLu6MkCI6Yg2CDFsJ0+p8ABq/AfszvCl71l8HJOdI0C8JaC4P4xkte/JX5wdvf13pHC3bg6c4qrPXXTb9DXMHx5oYMi79sBHQ2HlHQeFTxsf0RCCfwrrFX2ngN22gm8t7Mivmvea+reTV9Acngkw3a6F53xxN4RDledW6g19het9bEqk3CLVKHwH8W7u+egrrQtQXT19Y11d43e1FuDFr5XKPysECRy4scnpG+8aEsDx20ANIP5zrguQ/beBil9bWjk8KiREJjkLZTGHY6NDfSN9YySEQ519Y7h9OJgDRPydXYOjnT2kvb1dQ0M4o6NDvUMd3wUV1QztDNUABeHw9K3sbyeOn9laAGiAZSUbAORFJQBkR0wASB4AgBATMP/BAUD+g1vA/Huh/+SD4TkSeAAi1REARACf51yB7B2bHH+wbED3jcP6814Av2xNfs/If0GgPrOrqX8NDfY4c7cE6sBuer6sdlPV92UTxhY82QpIGPkLn0Tw5zeWuExBTwQpB9FTwXqKNauqqQfaHl6aLUsePt93RkCobZxKUlv3HY5kUhLST59pREf0lUSby1l/b5QeJuH/gyqCRNuyEnx4RnrppyO6QLF9tWVE8cKuvWi7Abyeeeo6ArwDs4RBiJF/mXJ3HeubUW/Fs8+S1VcPuYKjtI2Fkuc8bu47KaV0aQPPPOgjBV8A0CiVrXy9Wh/jHM38wPS2weHYzvonnbJ+WFhp3zJNUQp9apvYor0jdMO8Z8E9ltEivZn5TO1oLzGBgb2k/yBTzYvfRSvSvL2NFI97xhYrVU8Fi9IROcPIWdxxm14qxf7GeFPBC68522TswDpur22CAe0svQrotIw5saDM2nf4YpxnBoNj23x9AJIWVXOCm+3Pc5vxTw3Ukor7nSfBdLWICyoJ1bzhwUrnirHrU5CSpN2MjYpzEfsEHsRxZ6koEuN+N3j+eewR8fUJ/bWdfoum+J7LVAUchxTC6MnGiPis+jaNk93CX/YttDwoqidL7I0XpsPaPssWcVc6HR6i9xBStbxoMxqohYhQulFxpLTMUulOe9o7fdmZ7jOZ0R9l7MPVl2omS0o9qofZ/fPwStRnlcZAutSVBEKC2e0Cuu6qm+j01PkqBaGGhEqpYl0/8sxjswGA5dak2WKZoHSc6kdFk+f0v9El/UnIFpRNJ2PRU08kl45FI6PII13YSQiiNiHmWoqWZ40dcHxviyQHJmYUFzS5TDGdJgQsBei+kUH0lIumWbaQJQ8fywfVGuqEK3vznkSQNrGVld6ZtraKiqs24tfbtU7K2vunjenPaSFV+MUg24Mszhtx1vKkfwiiWp4+/U6o6eo5abheZnmO0DmN1Lnwi4ohkQ300eGUJUixpusS8oEPfd1Gl6AHjoUCCfJ+rcki6CxQp/plIKbpeKO9A72kVACVBtTCa7U+7l7IeFFeprys350ey+mFn1ABkLb4BJ6b7An5dctbxI6/dD6cx1s8p7UTDqS1kOKjDoCr8loxjtv1Y/Xm0rUpTCDT66S3P4als76AMhIljZafcma2gR0mR3t5J7MIWWqzXri9G8hBEtNKJRbX41LkcchmRHjQ+PdJvmPT7P+pWPgCWvwHUW2lJtKumBI/aZGBcAAixNiOxBONk8a/gvNbPufKzTBUIjB5pxdiim4FU7fiYp3XzQqjXI0JcdJZ+vo9no85Tpl3arEfbhqPeJgef5WxXdeJt/IwIlhdzbt2tUEUWh2hkS7DY0/aYE3pYiunQJhnhk0CY8hjtHqwBaNQSa743+Zu+u229K+tGPOMK9kQwWuRzGBAi9SY/F2oVoYmBI0xA0tXGZbz2TyqOQJdLZ8LreuDpYbhwscrBAqHL6I7Yep7gt5TeqeQSGej13A07XnU9rksdbjyTyxrPJkWvsja40NaD1sv6mQJXmme9zGWYba+xxZ/sxYTLSMoYnmK+F76hTdNxRU=
*/