//
// write.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

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
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

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
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

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
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

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
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

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
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * boost::asio::async_write(s, boost::asio::buffer(data, size), handler);
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream, typename ConstBufferSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * that they remain valid until the completion handler is called.
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
 * @code boost::asio::async_write(s,
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream,
    typename ConstBufferSequence, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, const ConstBufferSequence& buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_const_buffer_sequence<ConstBufferSequence>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * that they remain valid until the completion handler is called. Successfully
 * written data is automatically consumed from the buffers.
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream, typename DynamicBuffer_v1,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * that they remain valid until the completion handler is called. Successfully
 * written data is automatically consumed from the buffers.
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream,
    typename DynamicBuffer_v1, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s,
    BOOST_ASIO_MOVE_ARG(DynamicBuffer_v1) buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v1<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0,
    typename constraint<
      !is_dynamic_buffer_v2<typename decay<DynamicBuffer_v1>::type>::value
    >::type = 0);

#if !defined(BOOST_ASIO_NO_EXTENSIONS)
#if !defined(BOOST_ASIO_NO_IOSTREAM)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream, typename Allocator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type));

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * remains valid until the completion handler is called.
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream,
    typename Allocator, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, basic_streambuf<Allocator>& b,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token);

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_EXTENSIONS)
#endif // !defined(BOOST_ASIO_NO_DYNAMIC_BUFFER_V1)

/// Start an asynchronous operation to write all of the supplied data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * that they remain valid until the completion handler is called. Successfully
 * written data is automatically consumed from the buffers.
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream, typename DynamicBuffer_v2,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(
          typename AsyncWriteStream::executor_type)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    BOOST_ASIO_MOVE_ARG(WriteToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(
        typename AsyncWriteStream::executor_type),
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/// Start an asynchronous operation to write a certain amount of data to a
/// stream.
/**
 * This function is used to asynchronously write a certain number of bytes of
 * data to a stream. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately. The asynchronous
 * operation will continue until one of the following conditions is true:
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
 * that they remain valid until the completion handler is called. Successfully
 * written data is automatically consumed from the buffers.
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
 * if they are also supported by the @c AsyncWriteStream type's
 * @c async_write_some operation.
 */
template <typename AsyncWriteStream,
    typename DynamicBuffer_v2, typename CompletionCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      std::size_t)) WriteToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
    void (boost::system::error_code, std::size_t))
async_write(AsyncWriteStream& s, DynamicBuffer_v2 buffers,
    CompletionCondition completion_condition,
    BOOST_ASIO_MOVE_ARG(WriteToken) token,
    typename constraint<
      is_dynamic_buffer_v2<DynamicBuffer_v2>::value
    >::type = 0);

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/write.hpp>

#endif // BOOST_ASIO_WRITE_HPP

/* write.hpp
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
*/