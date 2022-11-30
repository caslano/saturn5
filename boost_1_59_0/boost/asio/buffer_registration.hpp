//
// buffer_registration.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFER_REGISTRATION_HPP
#define BOOST_ASIO_BUFFER_REGISTRATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <iterator>
#include <vector>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/execution/context.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/query.hpp>
#include <boost/asio/registered_buffer.hpp>

#if defined(BOOST_ASIO_HAS_IO_URING)
# include <boost/asio/detail/scheduler.hpp>
# include <boost/asio/detail/io_uring_service.hpp>
#endif // defined(BOOST_ASIO_HAS_IO_URING)

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class buffer_registration_base
{
protected:
  static mutable_registered_buffer make_buffer(const mutable_buffer& b,
      const void* scope, int index) BOOST_ASIO_NOEXCEPT
  {
    return mutable_registered_buffer(b, registered_buffer_id(scope, index));
  }
};

} // namespace detail

/// Automatically registers and unregistered buffers with an execution context.
/**
 * For portability, applications should assume that only one registration is
 * permitted per execution context.
 */
template <typename MutableBufferSequence,
    typename Allocator = std::allocator<void> >
class buffer_registration
  : detail::buffer_registration_base
{
public:
  /// The allocator type used for allocating storage for the buffers container.
  typedef Allocator allocator_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The type of an iterator over the registered buffers.
  typedef unspecified iterator;

  /// The type of a const iterator over the registered buffers.
  typedef unspecified const_iterator;
#else // defined(GENERATING_DOCUMENTATION)
  typedef std::vector<mutable_registered_buffer>::const_iterator iterator;
  typedef std::vector<mutable_registered_buffer>::const_iterator const_iterator;
#endif // defined(GENERATING_DOCUMENTATION)

  /// Register buffers with an executor's execution context.
  template <typename Executor>
  buffer_registration(const Executor& ex,
      const MutableBufferSequence& buffer_sequence,
      const allocator_type& alloc = allocator_type(),
      typename constraint<
        is_executor<Executor>::value || execution::is_executor<Executor>::value
      >::type = 0)
    : buffer_sequence_(buffer_sequence),
      buffers_(
          BOOST_ASIO_REBIND_ALLOC(allocator_type,
            mutable_registered_buffer)(alloc))
  {
    init_buffers(buffer_registration::get_context(ex),
        boost::asio::buffer_sequence_begin(buffer_sequence_),
        boost::asio::buffer_sequence_end(buffer_sequence_));
  }

  /// Register buffers with an execution context.
  template <typename ExecutionContext>
  buffer_registration(ExecutionContext& ctx,
      const MutableBufferSequence& buffer_sequence,
      const allocator_type& alloc = allocator_type(),
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : buffer_sequence_(buffer_sequence),
      buffers_(
          BOOST_ASIO_REBIND_ALLOC(allocator_type,
            mutable_registered_buffer)(alloc))
  {
    init_buffers(ctx,
        boost::asio::buffer_sequence_begin(buffer_sequence_),
        boost::asio::buffer_sequence_end(buffer_sequence_));
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  buffer_registration(buffer_registration&& other) BOOST_ASIO_NOEXCEPT
    : buffer_sequence_(std::move(other.buffer_sequence_)),
      buffers_(std::move(other.buffers_))
  {
#if defined(BOOST_ASIO_HAS_IO_URING)
    service_ = other.service_;
    other.service_ = 0;
#endif // defined(BOOST_ASIO_HAS_IO_URING)
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Unregisters the buffers.
  ~buffer_registration()
  {
#if defined(BOOST_ASIO_HAS_IO_URING)
    if (service_)
      service_->unregister_buffers();
#endif // defined(BOOST_ASIO_HAS_IO_URING)
  }
  
#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move assignment.
  buffer_registration& operator=(
      buffer_registration&& other) BOOST_ASIO_NOEXCEPT
  {
    if (this != &other)
    {
      buffer_sequence_ = std::move(other.buffer_sequence_);
      buffers_ = std::move(other.buffers_);
#if defined(BOOST_ASIO_HAS_IO_URING)
      if (service_)
        service_->unregister_buffers();
      service_ = other.service_;
      other.service_ = 0;
#endif // defined(BOOST_ASIO_HAS_IO_URING)
    }
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the number of registered buffers.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return buffers_.size();
  }

  /// Get the begin iterator for the sequence of registered buffers.
  const_iterator begin() const BOOST_ASIO_NOEXCEPT
  {
    return buffers_.begin();
  }

  /// Get the begin iterator for the sequence of registered buffers.
  const_iterator cbegin() const BOOST_ASIO_NOEXCEPT
  {
    return buffers_.cbegin();
  }

  /// Get the end iterator for the sequence of registered buffers.
  const_iterator end() const BOOST_ASIO_NOEXCEPT
  {
    return buffers_.end();
  }

  /// Get the end iterator for the sequence of registered buffers.
  const_iterator cend() const BOOST_ASIO_NOEXCEPT
  {
    return buffers_.cend();
  }

  /// Get the buffer at the specified index.
  const mutable_registered_buffer& operator[](std::size_t i) BOOST_ASIO_NOEXCEPT
  {
    return buffers_[i];
  }

  /// Get the buffer at the specified index.
  const mutable_registered_buffer& at(std::size_t i) BOOST_ASIO_NOEXCEPT
  {
    return buffers_.at(i);
  }

private:
  // Disallow copying and assignment.
  buffer_registration(const buffer_registration&) BOOST_ASIO_DELETED;
  buffer_registration& operator=(const buffer_registration&) BOOST_ASIO_DELETED;

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<execution::is_executor<T>::value>::type* = 0)
  {
    return boost::asio::query(t, execution::context);
  }

  // Helper function to get an executor's context.
  template <typename T>
  static execution_context& get_context(const T& t,
      typename enable_if<!execution::is_executor<T>::value>::type* = 0)
  {
    return t.context();
  }

  // Helper function to initialise the container of buffers.
  template <typename Iterator>
  void init_buffers(execution_context& ctx, Iterator begin, Iterator end)
  {
    std::size_t n = std::distance(begin, end);
    buffers_.resize(n);

#if defined(BOOST_ASIO_HAS_IO_URING)
    service_ = &use_service<detail::io_uring_service>(ctx);
    std::vector<iovec,
      BOOST_ASIO_REBIND_ALLOC(allocator_type, iovec)> iovecs(n,
          BOOST_ASIO_REBIND_ALLOC(allocator_type, iovec)(
            buffers_.get_allocator()));
#endif // defined(BOOST_ASIO_HAS_IO_URING)

    Iterator iter = begin;
    for (int index = 0; iter != end; ++index, ++iter)
    {
      mutable_buffer b(*iter);
      std::size_t i = static_cast<std::size_t>(index);
      buffers_[i] = this->make_buffer(b, &ctx, index);

#if defined(BOOST_ASIO_HAS_IO_URING)
      iovecs[i].iov_base = buffers_[i].data();
      iovecs[i].iov_len = buffers_[i].size();
#endif // defined(BOOST_ASIO_HAS_IO_URING)
    }

#if defined(BOOST_ASIO_HAS_IO_URING)
    if (n > 0)
    {
      service_->register_buffers(&iovecs[0],
          static_cast<unsigned>(iovecs.size()));
    }
#endif // defined(BOOST_ASIO_HAS_IO_URING)
  }

  MutableBufferSequence buffer_sequence_;
  std::vector<mutable_registered_buffer,
    BOOST_ASIO_REBIND_ALLOC(allocator_type,
      mutable_registered_buffer)> buffers_;
#if defined(BOOST_ASIO_HAS_IO_URING)
  detail::io_uring_service* service_;
#endif // defined(BOOST_ASIO_HAS_IO_URING)
};

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
/// Register buffers with an execution context.
template <typename Executor, typename MutableBufferSequence>
BOOST_ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence>
register_buffers(const Executor& ex,
    const MutableBufferSequence& buffer_sequence,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return buffer_registration<MutableBufferSequence>(ex, buffer_sequence);
}

/// Register buffers with an execution context.
template <typename Executor, typename MutableBufferSequence, typename Allocator>
BOOST_ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence, Allocator>
register_buffers(const Executor& ex,
    const MutableBufferSequence& buffer_sequence, const Allocator& alloc,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return buffer_registration<MutableBufferSequence, Allocator>(
      ex, buffer_sequence, alloc);
}

/// Register buffers with an execution context.
template <typename ExecutionContext, typename MutableBufferSequence>
BOOST_ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence>
register_buffers(ExecutionContext& ctx,
    const MutableBufferSequence& buffer_sequence,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
{
  return buffer_registration<MutableBufferSequence>(ctx, buffer_sequence);
}

/// Register buffers with an execution context.
template <typename ExecutionContext,
    typename MutableBufferSequence, typename Allocator>
BOOST_ASIO_NODISCARD inline
buffer_registration<MutableBufferSequence, Allocator>
register_buffers(ExecutionContext& ctx,
    const MutableBufferSequence& buffer_sequence, const Allocator& alloc,
    typename constraint<
      is_convertible<ExecutionContext&, execution_context&>::value
    >::type = 0)
{
  return buffer_registration<MutableBufferSequence, Allocator>(
      ctx, buffer_sequence, alloc);
}
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BUFFER_REGISTRATION_HPP

/* buffer_registration.hpp
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
*/