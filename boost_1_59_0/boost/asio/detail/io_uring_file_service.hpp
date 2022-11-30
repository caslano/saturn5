//
// detail/io_uring_file_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_URING_FILE_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IO_URING_FILE_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_FILE) \
  && defined(BOOST_ASIO_HAS_IO_URING)

#include <string>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/io_uring_descriptor_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/file_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Extend the io_uring_descriptor_service to provide file support.
class io_uring_file_service :
  public execution_context_service_base<io_uring_file_service>
{
public:
  typedef io_uring_descriptor_service descriptor_service;

  // The native type of a file.
  typedef descriptor_service::native_handle_type native_handle_type;

  // The implementation type of the file.
  class implementation_type : descriptor_service::implementation_type
  {
  private:
    // Only this service will have access to the internal values.
    friend class io_uring_file_service;

    bool is_stream_;
  };

  BOOST_ASIO_DECL io_uring_file_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new file implementation.
  void construct(implementation_type& impl)
  {
    descriptor_service_.construct(impl);
    impl.is_stream_ = false;
  }

  // Move-construct a new file implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    descriptor_service_.move_construct(impl, other_impl);
    impl.is_stream_ = other_impl.is_stream_;
  }

  // Move-assign from another file implementation.
  void move_assign(implementation_type& impl,
      io_uring_file_service& other_service,
      implementation_type& other_impl)
  {
    descriptor_service_.move_assign(impl,
        other_service.descriptor_service_, other_impl);
    impl.is_stream_ = other_impl.is_stream_;
  }

  // Destroy a file implementation.
  void destroy(implementation_type& impl)
  {
    descriptor_service_.destroy(impl);
  }

  // Open the file using the specified path name.
  BOOST_ASIO_DECL boost::system::error_code open(implementation_type& impl,
      const char* path, file_base::flags open_flags,
      boost::system::error_code& ec);

  // Assign a native descriptor to a file implementation.
  boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& native_descriptor,
      boost::system::error_code& ec)
  {
    return descriptor_service_.assign(impl, native_descriptor, ec);
  }

  // Set whether the implementation is stream-oriented.
  void set_is_stream(implementation_type& impl, bool is_stream)
  {
    impl.is_stream_ = is_stream;
  }

  // Determine whether the file is open.
  bool is_open(const implementation_type& impl) const
  {
    return descriptor_service_.is_open(impl);
  }

  // Destroy a file implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return descriptor_service_.close(impl, ec);
  }

  // Get the native file representation.
  native_handle_type native_handle(const implementation_type& impl) const
  {
    return descriptor_service_.native_handle(impl);
  }

  // Release ownership of the native descriptor representation.
  native_handle_type release(implementation_type& impl,
      boost::system::error_code& ec)
  {
    ec = success_ec_;
    return descriptor_service_.release(impl);
  }

  // Cancel all operations associated with the file.
  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return descriptor_service_.cancel(impl, ec);
  }

  // Get the size of the file.
  BOOST_ASIO_DECL uint64_t size(const implementation_type& impl,
      boost::system::error_code& ec) const;

  // Alter the size of the file.
  BOOST_ASIO_DECL boost::system::error_code resize(implementation_type& impl,
      uint64_t n, boost::system::error_code& ec);

  // Synchronise the file to disk.
  BOOST_ASIO_DECL boost::system::error_code sync_all(implementation_type& impl,
      boost::system::error_code& ec);

  // Synchronise the file data to disk.
  BOOST_ASIO_DECL boost::system::error_code sync_data(implementation_type& impl,
      boost::system::error_code& ec);

  // Seek to a position in the file.
  BOOST_ASIO_DECL uint64_t seek(implementation_type& impl, int64_t offset,
      file_base::seek_basis whence, boost::system::error_code& ec);

  // Write the given data. Returns the number of bytes written.
  template <typename ConstBufferSequence>
  size_t write_some(implementation_type& impl,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.write_some(impl, buffers, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_write_some(impl, buffers, handler, io_ex);
  }

  // Write the given data at the specified location. Returns the number of
  // bytes written.
  template <typename ConstBufferSequence>
  size_t write_some_at(implementation_type& impl, uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.write_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous write at the specified location. The data being
  // written must be valid for the lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl,
      uint64_t offset, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_write_some_at(
        impl, offset, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.read_some(impl, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_read_some(impl, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some_at(implementation_type& impl, uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return descriptor_service_.read_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl,
      uint64_t offset, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    descriptor_service_.async_read_some_at(
        impl, offset, buffers, handler, io_ex);
  }

private:
  // The implementation used for initiating asynchronous operations.
  descriptor_service descriptor_service_;

  // Cached success value to avoid accessing category singleton.
  const boost::system::error_code success_ec_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/io_uring_file_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_FILE)
       //   && defined(BOOST_ASIO_HAS_IO_URING)

#endif // BOOST_ASIO_DETAIL_IO_URING_FILE_SERVICE_HPP

/* io_uring_file_service.hpp
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
*/