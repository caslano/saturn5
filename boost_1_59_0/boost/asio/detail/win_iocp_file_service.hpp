//
// detail/win_iocp_file_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_FILE_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_FILE_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) && defined(BOOST_ASIO_HAS_FILE)

#include <string>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/win_iocp_handle_service.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/file_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Extend win_iocp_handle_service to provide file support.
class win_iocp_file_service :
  public execution_context_service_base<win_iocp_file_service>
{
public:
  // The native type of a file.
  typedef win_iocp_handle_service::native_handle_type native_handle_type;

  // The implementation type of the file.
  class implementation_type : win_iocp_handle_service::implementation_type
  {
  private:
    // Only this service will have access to the internal values.
    friend class win_iocp_file_service;

    uint64_t offset_;
    bool is_stream_;
  };

  // Constructor.
  BOOST_ASIO_DECL win_iocp_file_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new file implementation.
  void construct(implementation_type& impl)
  {
    handle_service_.construct(impl);
    impl.offset_ = 0;
    impl.is_stream_ = false;
  }

  // Move-construct a new file implementation.
  void move_construct(implementation_type& impl,
      implementation_type& other_impl)
  {
    handle_service_.move_construct(impl, other_impl);
    impl.offset_ = other_impl.offset_;
    impl.is_stream_ = other_impl.is_stream_;
    other_impl.offset_ = 0;
  }

  // Move-assign from another file implementation.
  void move_assign(implementation_type& impl,
      win_iocp_file_service& other_service,
      implementation_type& other_impl)
  {
    handle_service_.move_assign(impl,
        other_service.handle_service_, other_impl);
    impl.offset_ = other_impl.offset_;
    impl.is_stream_ = other_impl.is_stream_;
    other_impl.offset_ = 0;
  }

  // Destroy a file implementation.
  void destroy(implementation_type& impl)
  {
    handle_service_.destroy(impl);
  }

  // Set whether the implementation is stream-oriented.
  void set_is_stream(implementation_type& impl, bool is_stream)
  {
    impl.is_stream_ = is_stream;
  }

  // Open the file using the specified path name.
  BOOST_ASIO_DECL boost::system::error_code open(implementation_type& impl,
      const char* path, file_base::flags open_flags,
      boost::system::error_code& ec);

  // Assign a native handle to a file implementation.
  boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& native_handle,
      boost::system::error_code& ec)
  {
    return handle_service_.assign(impl, native_handle, ec);
  }

  // Determine whether the file is open.
  bool is_open(const implementation_type& impl) const
  {
    return handle_service_.is_open(impl);
  }

  // Destroy a file implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return handle_service_.close(impl, ec);
  }

  // Get the native file representation.
  native_handle_type native_handle(const implementation_type& impl) const
  {
    return handle_service_.native_handle(impl);
  }

  // Release ownership of a file.
  native_handle_type release(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return handle_service_.release(impl, ec);
  }

  // Cancel all operations associated with the file.
  boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec)
  {
    return handle_service_.cancel(impl, ec);
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
    uint64_t offset = impl.offset_;
    impl.offset_ += boost::asio::buffer_size(buffers);
    return handle_service_.write_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous write. The data being written must be valid for the
  // lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some(implementation_type& impl,
      const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    uint64_t offset = impl.offset_;
    impl.offset_ += boost::asio::buffer_size(buffers);
    handle_service_.async_write_some_at(impl, offset, buffers, handler, io_ex);
  }

  // Write the given data at the specified location. Returns the number of
  // bytes written.
  template <typename ConstBufferSequence>
  size_t write_some_at(implementation_type& impl, uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return handle_service_.write_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous write at the specified location. The data being
  // written must be valid for the lifetime of the asynchronous operation.
  template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
  void async_write_some_at(implementation_type& impl,
      uint64_t offset, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    handle_service_.async_write_some_at(impl, offset, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some(implementation_type& impl,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    uint64_t offset = impl.offset_;
    impl.offset_ += boost::asio::buffer_size(buffers);
    return handle_service_.read_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some(implementation_type& impl,
      const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    uint64_t offset = impl.offset_;
    impl.offset_ += boost::asio::buffer_size(buffers);
    handle_service_.async_read_some_at(impl, offset, buffers, handler, io_ex);
  }

  // Read some data. Returns the number of bytes read.
  template <typename MutableBufferSequence>
  size_t read_some_at(implementation_type& impl, uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return handle_service_.read_some_at(impl, offset, buffers, ec);
  }

  // Start an asynchronous read. The buffer for the data being read must be
  // valid for the lifetime of the asynchronous operation.
  template <typename MutableBufferSequence,
      typename Handler, typename IoExecutor>
  void async_read_some_at(implementation_type& impl,
      uint64_t offset, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
  {
    handle_service_.async_read_some_at(impl, offset, buffers, handler, io_ex);
  }

private:
  // The implementation used for initiating asynchronous operations.
  win_iocp_handle_service handle_service_;

  // Emulation of Windows IO_STATUS_BLOCK structure.
  struct io_status_block
  {
    union u
    {
      LONG Status;
      void* Pointer;
    };
    ULONG_PTR Information;
  };

  // Emulation of flag passed to NtFlushBuffersFileEx.
  enum { flush_flags_file_data_sync_only = 4 };

  // The type of a NtFlushBuffersFileEx function pointer.
  typedef LONG (NTAPI *nt_flush_buffers_file_ex_fn)(
      HANDLE, ULONG, void*, ULONG, io_status_block*);

  // The NTFlushBuffersFileEx function pointer.
  nt_flush_buffers_file_ex_fn nt_flush_buffers_file_ex_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_iocp_file_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_IOCP) && defined(BOOST_ASIO_HAS_FILE)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_FILE_SERVICE_HPP

/* win_iocp_file_service.hpp
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
*/