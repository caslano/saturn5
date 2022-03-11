//
// basic_streambuf.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <streambuf>
#include <vector>
#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/limits.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/throw_exception.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Automatically resizable buffer class based on std::streambuf.
/**
 * The @c basic_streambuf class is derived from @c std::streambuf to associate
 * the streambuf's input and output sequences with one or more character
 * arrays. These character arrays are internal to the @c basic_streambuf
 * object, but direct access to the array elements is provided to permit them
 * to be used efficiently with I/O operations. Characters written to the output
 * sequence of a @c basic_streambuf object are appended to the input sequence
 * of the same object.
 *
 * The @c basic_streambuf class's public interface is intended to permit the
 * following implementation strategies:
 *
 * @li A single contiguous character array, which is reallocated as necessary
 * to accommodate changes in the size of the character sequence. This is the
 * implementation approach currently used in Asio.
 *
 * @li A sequence of one or more character arrays, where each array is of the
 * same size. Additional character array objects are appended to the sequence
 * to accommodate changes in the size of the character sequence.
 *
 * @li A sequence of one or more character arrays of varying sizes. Additional
 * character array objects are appended to the sequence to accommodate changes
 * in the size of the character sequence.
 *
 * The constructor for basic_streambuf accepts a @c size_t argument specifying
 * the maximum of the sum of the sizes of the input sequence and output
 * sequence. During the lifetime of the @c basic_streambuf object, the following
 * invariant holds:
 * @code size() <= max_size()@endcode
 * Any member function that would, if successful, cause the invariant to be
 * violated shall throw an exception of class @c std::length_error.
 *
 * The constructor for @c basic_streambuf takes an Allocator argument. A copy
 * of this argument is used for any memory allocation performed, by the
 * constructor and by all member functions, during the lifetime of each @c
 * basic_streambuf object.
 *
 * @par Examples
 * Writing directly from an streambuf to a socket:
 * @code
 * boost::asio::streambuf b;
 * std::ostream os(&b);
 * os << "Hello, World!\n";
 *
 * // try sending some data in input sequence
 * size_t n = sock.send(b.data());
 *
 * b.consume(n); // sent data is removed from input sequence
 * @endcode
 *
 * Reading from a socket directly into a streambuf:
 * @code
 * boost::asio::streambuf b;
 *
 * // reserve 512 bytes in output sequence
 * boost::asio::streambuf::mutable_buffers_type bufs = b.prepare(512);
 *
 * size_t n = sock.receive(bufs);
 *
 * // received data is "committed" from output sequence to input sequence
 * b.commit(n);
 *
 * std::istream is(&b);
 * std::string s;
 * is >> s;
 * @endcode
 */
#if defined(GENERATING_DOCUMENTATION)
template <typename Allocator = std::allocator<char> >
#else
template <typename Allocator>
#endif
class basic_streambuf
  : public std::streambuf,
    private noncopyable
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The type used to represent the input sequence as a list of buffers.
  typedef implementation_defined const_buffers_type;

  /// The type used to represent the output sequence as a list of buffers.
  typedef implementation_defined mutable_buffers_type;
#else
  typedef BOOST_ASIO_CONST_BUFFER const_buffers_type;
  typedef BOOST_ASIO_MUTABLE_BUFFER mutable_buffers_type;
#endif

  /// Construct a basic_streambuf object.
  /**
   * Constructs a streambuf with the specified maximum size. The initial size
   * of the streambuf's input sequence is 0.
   */
  explicit basic_streambuf(
      std::size_t maximum_size = (std::numeric_limits<std::size_t>::max)(),
      const Allocator& allocator = Allocator())
    : max_size_(maximum_size),
      buffer_(allocator)
  {
    std::size_t pend = (std::min<std::size_t>)(max_size_, buffer_delta);
    buffer_.resize((std::max<std::size_t>)(pend, 1));
    setg(&buffer_[0], &buffer_[0], &buffer_[0]);
    setp(&buffer_[0], &buffer_[0] + pend);
  }

  /// Get the size of the input sequence.
  /**
   * @returns The size of the input sequence. The value is equal to that
   * calculated for @c s in the following code:
   * @code
   * size_t s = 0;
   * const_buffers_type bufs = data();
   * const_buffers_type::const_iterator i = bufs.begin();
   * while (i != bufs.end())
   * {
   *   const_buffer buf(*i++);
   *   s += buf.size();
   * }
   * @endcode
   */
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return pptr() - gptr();
  }

  /// Get the maximum size of the basic_streambuf.
  /**
   * @returns The allowed maximum of the sum of the sizes of the input sequence
   * and output sequence.
   */
  std::size_t max_size() const BOOST_ASIO_NOEXCEPT
  {
    return max_size_;
  }

  /// Get the current capacity of the basic_streambuf.
  /**
   * @returns The current total capacity of the streambuf, i.e. for both the
   * input sequence and output sequence.
   */
  std::size_t capacity() const BOOST_ASIO_NOEXCEPT
  {
    return buffer_.capacity();
  }

  /// Get a list of buffers that represents the input sequence.
  /**
   * @returns An object of type @c const_buffers_type that satisfies
   * ConstBufferSequence requirements, representing all character arrays in the
   * input sequence.
   *
   * @note The returned object is invalidated by any @c basic_streambuf member
   * function that modifies the input sequence or output sequence.
   */
  const_buffers_type data() const BOOST_ASIO_NOEXCEPT
  {
    return boost::asio::buffer(boost::asio::const_buffer(gptr(),
          (pptr() - gptr()) * sizeof(char_type)));
  }

  /// Get a list of buffers that represents the output sequence, with the given
  /// size.
  /**
   * Ensures that the output sequence can accommodate @c n characters,
   * reallocating character array objects as necessary.
   *
   * @returns An object of type @c mutable_buffers_type that satisfies
   * MutableBufferSequence requirements, representing character array objects
   * at the start of the output sequence such that the sum of the buffer sizes
   * is @c n.
   *
   * @throws std::length_error If <tt>size() + n > max_size()</tt>.
   *
   * @note The returned object is invalidated by any @c basic_streambuf member
   * function that modifies the input sequence or output sequence.
   */
  mutable_buffers_type prepare(std::size_t n)
  {
    reserve(n);
    return boost::asio::buffer(boost::asio::mutable_buffer(
          pptr(), n * sizeof(char_type)));
  }

  /// Move characters from the output sequence to the input sequence.
  /**
   * Appends @c n characters from the start of the output sequence to the input
   * sequence. The beginning of the output sequence is advanced by @c n
   * characters.
   *
   * Requires a preceding call <tt>prepare(x)</tt> where <tt>x >= n</tt>, and
   * no intervening operations that modify the input or output sequence.
   *
   * @note If @c n is greater than the size of the output sequence, the entire
   * output sequence is moved to the input sequence and no error is issued.
   */
  void commit(std::size_t n)
  {
    n = std::min<std::size_t>(n, epptr() - pptr());
    pbump(static_cast<int>(n));
    setg(eback(), gptr(), pptr());
  }

  /// Remove characters from the input sequence.
  /**
   * Removes @c n characters from the beginning of the input sequence.
   *
   * @note If @c n is greater than the size of the input sequence, the entire
   * input sequence is consumed and no error is issued.
   */
  void consume(std::size_t n)
  {
    if (egptr() < pptr())
      setg(&buffer_[0], gptr(), pptr());
    if (gptr() + n > pptr())
      n = pptr() - gptr();
    gbump(static_cast<int>(n));
  }

protected:
  enum { buffer_delta = 128 };

  /// Override std::streambuf behaviour.
  /**
   * Behaves according to the specification of @c std::streambuf::underflow().
   */
  int_type underflow()
  {
    if (gptr() < pptr())
    {
      setg(&buffer_[0], gptr(), pptr());
      return traits_type::to_int_type(*gptr());
    }
    else
    {
      return traits_type::eof();
    }
  }

  /// Override std::streambuf behaviour.
  /**
   * Behaves according to the specification of @c std::streambuf::overflow(),
   * with the specialisation that @c std::length_error is thrown if appending
   * the character to the input sequence would require the condition
   * <tt>size() > max_size()</tt> to be true.
   */
  int_type overflow(int_type c)
  {
    if (!traits_type::eq_int_type(c, traits_type::eof()))
    {
      if (pptr() == epptr())
      {
        std::size_t buffer_size = pptr() - gptr();
        if (buffer_size < max_size_ && max_size_ - buffer_size < buffer_delta)
        {
          reserve(max_size_ - buffer_size);
        }
        else
        {
          reserve(buffer_delta);
        }
      }

      *pptr() = traits_type::to_char_type(c);
      pbump(1);
      return c;
    }

    return traits_type::not_eof(c);
  }

  void reserve(std::size_t n)
  {
    // Get current stream positions as offsets.
    std::size_t gnext = gptr() - &buffer_[0];
    std::size_t pnext = pptr() - &buffer_[0];
    std::size_t pend = epptr() - &buffer_[0];

    // Check if there is already enough space in the put area.
    if (n <= pend - pnext)
    {
      return;
    }

    // Shift existing contents of get area to start of buffer.
    if (gnext > 0)
    {
      pnext -= gnext;
      std::memmove(&buffer_[0], &buffer_[0] + gnext, pnext);
    }

    // Ensure buffer is large enough to hold at least the specified size.
    if (n > pend - pnext)
    {
      if (n <= max_size_ && pnext <= max_size_ - n)
      {
        pend = pnext + n;
        buffer_.resize((std::max<std::size_t>)(pend, 1));
      }
      else
      {
        std::length_error ex("boost::asio::streambuf too long");
        boost::asio::detail::throw_exception(ex);
      }
    }

    // Update stream positions.
    setg(&buffer_[0], &buffer_[0], &buffer_[0] + pnext);
    setp(&buffer_[0] + pnext, &buffer_[0] + pend);
  }

private:
  std::size_t max_size_;
  std::vector<char_type, Allocator> buffer_;

  // Helper function to get the preferred size for reading data.
  friend std::size_t read_size_helper(
      basic_streambuf& sb, std::size_t max_size)
  {
    return std::min<std::size_t>(
        std::max<std::size_t>(512, sb.buffer_.capacity() - sb.size()),
        std::min<std::size_t>(max_size, sb.max_size() - sb.size()));
  }
};

/// Adapts basic_streambuf to the dynamic buffer sequence type requirements.
#if defined(GENERATING_DOCUMENTATION)
template <typename Allocator = std::allocator<char> >
#else
template <typename Allocator>
#endif
class basic_streambuf_ref
{
public:
  /// The type used to represent the input sequence as a list of buffers.
  typedef typename basic_streambuf<Allocator>::const_buffers_type
    const_buffers_type;

  /// The type used to represent the output sequence as a list of buffers.
  typedef typename basic_streambuf<Allocator>::mutable_buffers_type
    mutable_buffers_type;

  /// Construct a basic_streambuf_ref for the given basic_streambuf object.
  explicit basic_streambuf_ref(basic_streambuf<Allocator>& sb)
    : sb_(sb)
  {
  }

  /// Copy construct a basic_streambuf_ref.
  basic_streambuf_ref(const basic_streambuf_ref& other) BOOST_ASIO_NOEXCEPT
    : sb_(other.sb_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move construct a basic_streambuf_ref.
  basic_streambuf_ref(basic_streambuf_ref&& other) BOOST_ASIO_NOEXCEPT
    : sb_(other.sb_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the size of the input sequence.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return sb_.size();
  }

  /// Get the maximum size of the dynamic buffer.
  std::size_t max_size() const BOOST_ASIO_NOEXCEPT
  {
    return sb_.max_size();
  }

  /// Get the current capacity of the dynamic buffer.
  std::size_t capacity() const BOOST_ASIO_NOEXCEPT
  {
    return sb_.capacity();
  }

  /// Get a list of buffers that represents the input sequence.
  const_buffers_type data() const BOOST_ASIO_NOEXCEPT
  {
    return sb_.data();
  }

  /// Get a list of buffers that represents the output sequence, with the given
  /// size.
  mutable_buffers_type prepare(std::size_t n)
  {
    return sb_.prepare(n);
  }

  /// Move bytes from the output sequence to the input sequence.
  void commit(std::size_t n)
  {
    return sb_.commit(n);
  }

  /// Remove characters from the input sequence.
  void consume(std::size_t n)
  {
    return sb_.consume(n);
  }

private:
  basic_streambuf<Allocator>& sb_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_HPP

/* basic_streambuf.hpp
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
*/