//
// buffered_read_stream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERED_READ_STREAM_HPP
#define BOOST_ASIO_BUFFERED_READ_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_resize_guard.hpp>
#include <boost/asio/detail/buffered_stream_storage.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Adds buffering to the read-related operations of a stream.
/**
 * The buffered_read_stream class template can be used to add buffering to the
 * synchronous and asynchronous read operations of a stream.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class buffered_read_stream
  : private noncopyable
{
public:
  /// The type of the next layer.
  typedef typename remove_reference<Stream>::type next_layer_type;

  /// The type of the lowest layer.
  typedef typename next_layer_type::lowest_layer_type lowest_layer_type;

  /// The type of the executor associated with the object.
  typedef typename lowest_layer_type::executor_type executor_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The default buffer size.
  static const std::size_t default_buffer_size = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(std::size_t, default_buffer_size = 1024);
#endif

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  explicit buffered_read_stream(Arg& a)
    : next_layer_(a),
      storage_(default_buffer_size)
  {
  }

  /// Construct, passing the specified argument to initialise the next layer.
  template <typename Arg>
  buffered_read_stream(Arg& a, std::size_t buffer_size)
    : next_layer_(a),
      storage_(buffer_size)
  {
  }

  /// Get a reference to the next layer.
  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  /// Get a reference to the lowest layer.
  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  /// Get a const reference to the lowest layer.
  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return next_layer_.lowest_layer().get_executor();
  }

  /// Close the stream.
  void close()
  {
    next_layer_.close();
  }

  /// Close the stream.
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    next_layer_.close(ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Write the given data to the stream. Returns the number of bytes written.
  /// Throws an exception on failure.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    return next_layer_.write_some(buffers);
  }

  /// Write the given data to the stream. Returns the number of bytes written,
  /// or 0 if an error occurred.
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return next_layer_.write_some(buffers, ec);
  }

  /// Start an asynchronous write. The data being written must be valid for the
  /// lifetime of the asynchronous operation.
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return next_layer_.async_write_some(buffers,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation. Throws an exception on failure.
  std::size_t fill();

  /// Fill the buffer with some data. Returns the number of bytes placed in the
  /// buffer as a result of the operation, or 0 if an error occurred.
  std::size_t fill(boost::system::error_code& ec);

  /// Start an asynchronous fill.
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_fill(
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Read some data from the stream. Returns the number of bytes read. Throws
  /// an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers);

  /// Read some data from the stream. Returns the number of bytes read or 0 if
  /// an error occurred.
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec);

  /// Start an asynchronous read. The buffer into which the data will be read
  /// must be valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type));

  /// Peek at the incoming data on the stream. Returns the number of bytes read.
  /// Throws an exception on failure.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers);

  /// Peek at the incoming data on the stream. Returns the number of bytes read,
  /// or 0 if an error occurred.
  template <typename MutableBufferSequence>
  std::size_t peek(const MutableBufferSequence& buffers,
      boost::system::error_code& ec);

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail()
  {
    return storage_.size();
  }

  /// Determine the amount of data that may be read without blocking.
  std::size_t in_avail(boost::system::error_code& ec)
  {
    ec = boost::system::error_code();
    return storage_.size();
  }

private:
  /// Copy data out of the internal buffer to the specified target buffer.
  /// Returns the number of bytes copied.
  template <typename MutableBufferSequence>
  std::size_t copy(const MutableBufferSequence& buffers)
  {
    std::size_t bytes_copied = boost::asio::buffer_copy(
        buffers, storage_.data(), storage_.size());
    storage_.consume(bytes_copied);
    return bytes_copied;
  }

  /// Copy data from the internal buffer to the specified target buffer, without
  /// removing the data from the internal buffer. Returns the number of bytes
  /// copied.
  template <typename MutableBufferSequence>
  std::size_t peek_copy(const MutableBufferSequence& buffers)
  {
    return boost::asio::buffer_copy(buffers, storage_.data(), storage_.size());
  }

  /// The next layer.
  Stream next_layer_;

  // The data in the buffer.
  detail::buffered_stream_storage storage_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/buffered_read_stream.hpp>

#endif // BOOST_ASIO_BUFFERED_READ_STREAM_HPP

/* buffered_read_stream.hpp
n5tinodTYDs91siNbQ/dbZl5qL5O0WAN/jRRadVwsGxnB/GpDs65OMC5NbeNpjhxNIOpavqt7B08YOFqjDM7dqyVT99lyY9xDOVnJ9ya67VJUOsLPzGvaBSdCu3jBrHr0KcUbTKS36ll0RI/lUZjz8pQjU3PZ9LFmULplgY5J7gdjg9nciT9UF6h1/0uxQ/T6xk5dhgNEvMfYkax3Qiy2cJX21nmC6ViGntsOkszOV0spTGFo5kkTB0dLWTyF7P8o6U7zhUMms6MT2awNd7FRLs3WerD5SUWRyxcrqzSosT1ndiL+BoZaej5ksd8YuACbMdhAWbdoTSKVgjXfqHIxVddYccaX+Iq+fi4EoqfVoo0Lymd5qVxnEzX/She06dW81pRPd2fhdyxOfE3zu9ryPEplT9xvEgJoj82mUnPj91OpmV/y6THSW7azxSC3jtTeqKgctBvVUL6LWGknOPDEiGfO1LpQrZkbD6+ANI/s5Tfn1GGL9rYxhFJ5uNE5jvtXyiKCc6y1xZ21qrfsqK63/LEOp8TAOjfl9nmL8zUelcq17mcuG7H1mk7snBxYFeSzDj57BDHnhx2q5SStIeaaN/NPBOGHDLz6NyoiNGSu3Z6rd0Sz9VJI9BVI7+pMEk1brVzcL934lY7I/E/pAISSnwV/90OWrh0P9ntZmLfcfCZl07i5z5PxMFLRCzDZ2T6FSK+iOKTrxSxHiq4YNo3sjaydzePLwd3qbh+ubJvRNpone+onHgldwjnrbLHmtahgyrt12pd8SGddTPLtW5j7ULv2B2592R+bZfM3t11+SinOxld1OM2B7sU1C7H5czNLspBfTdTTkIbNwKp7zCYwnbyr5vbVxf+8SrhJzteY/aXM68nf3qziAffIuJzPO71/SP5ETpfx/ePl5T+v0f4/5m3kf+/PVve2XeQ3u8U8WfeLeLD7yF6ivXQYFFkLzF6Yuxsn/NU/o6LqP7vM8s7+QHS48OkB8UnP2KmD5nn8tGrF3v5p9rNtVhn1j1arnPKqoR8/VrzV6y7txoBqyZnP4htDvueq1bVX7pJZFVs59SezHPXROlErjBWkH+Ld03RSipfZIu/ed4afmJ8YjjFO0y8w6l8oCDTuYnCGBBdjlVZjjmVjDyNfpgYJP2wZHCruaiBg33O9pZyuNgZRobToS1WEaRHLoWYHp8YFbqKv4UMZgOF0sTEuMgXf0v8QiEv0OJvCJ08YOBxbii/H9J0+0aIlPL3jQj8yGAGj2mAsckEhzFApYbg+adrqZ3EwmhpcS8nob/FXBjF6fycUxH+QHkyTfaxWYQakhFk0JGjEyVeD1GSSGNS0q3JOZA3yJFIKQcRaTmYlHRSTn7vPk0OITNyEJGWg0lJx+t9dGJ2dno0ozQoPKLJHg3+SGHLtMyXSup8iM7wybTMl0rpfIjO8Mn00fG9SYy9eTjXqCaJ0tToEEYKH9VticD1Z47yM+lcntLTuLIcH9o3yH3IDVijinGjiojuxg+HP/jy7Zxevt9EPvnE3eW8I8hzhxrVMp+6+PyDK+jy0dET5aPj5dL0nSbAHF7QB7ADFPTvEPjnXu4yYp65vIhluGSPH0c8f02+CH2a/B1X2Jz8F/YB9KX036bJP/+jS29K/os0+QOa/It+vDn5j+jX5ENW/pmfbk7+ozeQ/9yfbE7+wway8i+m6//zzcl/CfnP1bfIP18s5W+Rf76U/OfqW+SfL5Pyt8g/H9lP8rfIPx8j5W+Rfz58gORvkX++gvzH2iL/fLmUv0X++UryH2uL/PNVUv4W+eej+kn+FvnnY6X8LfLPRwyQ/C3yz/ulxufLAMDylcXC5czvhNzzvxfxa38h4pf2gzE=
*/