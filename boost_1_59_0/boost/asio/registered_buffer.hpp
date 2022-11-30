//
// registered_buffer.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_REGISTERED_BUFFER_HPP
#define BOOST_ASIO_REGISTERED_BUFFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class buffer_registration_base;

} // namespace detail

class const_registered_buffer;

/// Type used to identify a registered buffer.
class registered_buffer_id
{
public:
  /// The native buffer identifier type.
  typedef int native_handle_type;

  /// Default constructor creates an invalid registered buffer identifier.
  registered_buffer_id() BOOST_ASIO_NOEXCEPT
    : scope_(0),
      index_(-1)
  {
  }

  /// Get the native buffer identifier type.
  native_handle_type native_handle() const BOOST_ASIO_NOEXCEPT
  {
    return index_;
  }

  /// Compare two IDs for equality.
  friend bool operator==(const registered_buffer_id& lhs,
      const registered_buffer_id& rhs) BOOST_ASIO_NOEXCEPT
  {
    return lhs.scope_ == rhs.scope_ && lhs.index_ == rhs.index_;
  }

  /// Compare two IDs for equality.
  friend bool operator!=(const registered_buffer_id& lhs,
      const registered_buffer_id& rhs) BOOST_ASIO_NOEXCEPT
  {
    return lhs.scope_ != rhs.scope_ || lhs.index_ != rhs.index_;
  }

private:
  friend class detail::buffer_registration_base;

  // Hidden constructor used by buffer registration.
  registered_buffer_id(const void* scope, int index) BOOST_ASIO_NOEXCEPT
    : scope_(scope),
      index_(index)
  {
  }

  const void* scope_;
  int index_;
};

/// Holds a registered buffer over modifiable data.
/** 
 * Satisfies the @c MutableBufferSequence type requirements.
 */
class mutable_registered_buffer
{
public:
#if !defined(BOOST_ASIO_HAS_DECLTYPE) \
  && !defined(GENERATING_DOCUMENTATION)
  typedef mutable_buffer value_type;
#endif // !defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && !defined(GENERATING_DOCUMENTATION)

  /// Default constructor creates an invalid registered buffer.
  mutable_registered_buffer() BOOST_ASIO_NOEXCEPT
    : buffer_(),
      id_()
  {
  }

  /// Get the underlying mutable buffer.
  const mutable_buffer& buffer() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_;
  }

  /// Get a pointer to the beginning of the memory range.
  /**
   * @returns <tt>buffer().data()</tt>.
   */
  void* data() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_.data();
  }

  /// Get the size of the memory range.
  /**
   * @returns <tt>buffer().size()</tt>.
   */
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_.size();
  }

  /// Get the registered buffer identifier.
  const registered_buffer_id& id() const BOOST_ASIO_NOEXCEPT
  {
    return id_;
  }

  /// Move the start of the buffer by the specified number of bytes.
  mutable_registered_buffer& operator+=(std::size_t n) BOOST_ASIO_NOEXCEPT
  {
    buffer_ += n;
    return *this;
  }

private:
  friend class detail::buffer_registration_base;

  // Hidden constructor used by buffer registration and operators.
  mutable_registered_buffer(const mutable_buffer& b,
      const registered_buffer_id& i) BOOST_ASIO_NOEXCEPT
    : buffer_(b),
      id_(i)
  {
  }

#if !defined(GENERATING_DOCUMENTATION)
  friend mutable_registered_buffer buffer(
      const mutable_registered_buffer& b, std::size_t n) BOOST_ASIO_NOEXCEPT;
#endif // !defined(GENERATING_DOCUMENTATION)

  mutable_buffer buffer_;
  registered_buffer_id id_;
};

/// Holds a registered buffer over non-modifiable data.
/** 
 * Satisfies the @c ConstBufferSequence type requirements.
 */
class const_registered_buffer
{
public:
#if !defined(BOOST_ASIO_HAS_DECLTYPE) \
  && !defined(GENERATING_DOCUMENTATION)
  typedef const_buffer value_type;
#endif // !defined(BOOST_ASIO_HAS_DECLTYPE)
       //   && !defined(GENERATING_DOCUMENTATION)

  /// Default constructor creates an invalid registered buffer.
  const_registered_buffer() BOOST_ASIO_NOEXCEPT
    : buffer_(),
      id_()
  {
  }

  /// Construct a non-modifiable buffer from a modifiable one.
  const_registered_buffer(
      const mutable_registered_buffer& b) BOOST_ASIO_NOEXCEPT
    : buffer_(b.buffer()),
      id_(b.id())
  {
  }

  /// Get the underlying constant buffer.
  const const_buffer& buffer() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_;
  }

  /// Get a pointer to the beginning of the memory range.
  /**
   * @returns <tt>buffer().data()</tt>.
   */
  const void* data() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_.data();
  }

  /// Get the size of the memory range.
  /**
   * @returns <tt>buffer().size()</tt>.
   */
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_.size();
  }

  /// Get the registered buffer identifier.
  const registered_buffer_id& id() const BOOST_ASIO_NOEXCEPT
  {
    return id_;
  }

  /// Move the start of the buffer by the specified number of bytes.
  const_registered_buffer& operator+=(std::size_t n) BOOST_ASIO_NOEXCEPT
  {
    buffer_ += n;
    return *this;
  }

private:
  // Hidden constructor used by operators.
  const_registered_buffer(const const_buffer& b,
      const registered_buffer_id& i) BOOST_ASIO_NOEXCEPT
    : buffer_(b),
      id_(i)
  {
  }

#if !defined(GENERATING_DOCUMENTATION)
  friend const_registered_buffer buffer(
      const const_registered_buffer& b, std::size_t n) BOOST_ASIO_NOEXCEPT;
#endif // !defined(GENERATING_DOCUMENTATION)

  const_buffer buffer_;
  registered_buffer_id id_;
};

/** @addtogroup buffer_sequence_begin */

/// Get an iterator to the first element in a buffer sequence.
inline const mutable_buffer* buffer_sequence_begin(
    const mutable_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return &b.buffer();
}

/// Get an iterator to the first element in a buffer sequence.
inline const const_buffer* buffer_sequence_begin(
    const const_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return &b.buffer();
}

/** @} */
/** @addtogroup buffer_sequence_end */

/// Get an iterator to one past the end element in a buffer sequence.
inline const mutable_buffer* buffer_sequence_end(
    const mutable_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return &b.buffer() + 1;
}

/// Get an iterator to one past the end element in a buffer sequence.
inline const const_buffer* buffer_sequence_end(
    const const_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return &b.buffer() + 1;
}

/** @} */
/** @addtogroup buffer */

/// Obtain a buffer representing the entire registered buffer.
inline mutable_registered_buffer buffer(
    const mutable_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return b;
}

/// Obtain a buffer representing the entire registered buffer.
inline const_registered_buffer buffer(
    const const_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return b;
}

/// Obtain a buffer representing part of a registered buffer.
inline mutable_registered_buffer buffer(
    const mutable_registered_buffer& b, std::size_t n) BOOST_ASIO_NOEXCEPT
{
  return mutable_registered_buffer(buffer(b.buffer_, n), b.id_);
}

/// Obtain a buffer representing part of a registered buffer.
inline const_registered_buffer buffer(
    const const_registered_buffer& b, std::size_t n) BOOST_ASIO_NOEXCEPT
{
  return const_registered_buffer(buffer(b.buffer_, n), b.id_);
}

/** @} */

/// Create a new modifiable registered buffer that is offset from the start of
/// another.
/**
 * @relates mutable_registered_buffer
 */
inline mutable_registered_buffer operator+(
    const mutable_registered_buffer& b, std::size_t n) BOOST_ASIO_NOEXCEPT
{
  mutable_registered_buffer tmp(b);
  tmp += n;
  return tmp;
}

/// Create a new modifiable buffer that is offset from the start of another.
/**
 * @relates mutable_registered_buffer
 */
inline mutable_registered_buffer operator+(std::size_t n,
    const mutable_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return b + n;
}

/// Create a new non-modifiable registered buffer that is offset from the start
/// of another.
/**
 * @relates const_registered_buffer
 */
inline const_registered_buffer operator+(const const_registered_buffer& b,
    std::size_t n) BOOST_ASIO_NOEXCEPT
{
  const_registered_buffer tmp(b);
  tmp += n;
  return tmp;
}

/// Create a new non-modifiable buffer that is offset from the start of another.
/**
 * @relates const_registered_buffer
 */
inline const_registered_buffer operator+(std::size_t n,
    const const_registered_buffer& b) BOOST_ASIO_NOEXCEPT
{
  return b + n;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_REGISTERED_BUFFER_HPP

/* registered_buffer.hpp
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
*/