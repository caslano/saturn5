//
// basic_streambuf.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
yLNOZ7nYE71bvZAokwuzvz0BwjKyJGJ6F+KH4OBv6WVOBa//15McuRFDyGDPpV4m0JPeu6bLLweouoMHFVdC1HO0UiDAwsKXrkzTgnLcMNOoYIt60epEDolvS9xXljNEaW5hkwApBqk6JGvMqgHUwQHY+0Vo8Ae8eQ1WlF8JwF9Y+qob1AFnIpV2ndbMLHVochIGjfn3KRqaTBxKJI3SRGPWoNGctGGURuP76Mv2Mr/u8kDkN/ru+pF3E1+qCdbNSGlfqbnsLozkXGBkpiXarpOY97/WHQIoBTBibyHnp6427NcYbWBPGAufeExx1MECAZSHx44bicwHLh92qqGLoJKOgH5VtFyb7rsiM45SsMAFYTWmV+oIJ1w2gqk41VSbGcTTXDRQyG+YxMxcvG//sdqC1U0Fqu4uaALpJ4EcYgDyLdorZSb4kE7UljZ2oALutbg8cAs1yuPG1Y4txVldXfH/tisAWHZpfc8fiKc2Xuu607WFlTynFnLkqomFd92EL7w1F3B09xK/5NQY2wZBbNkOxW0vlVDxGMIvvQwtFXmb4QhMpsazV0F8YYfGzyFvw0NOcsQUiLDDUQD2Y8CNNM2KMW/wgUtYq2IMMOYmKpNhVx6Kaswus2Z7BcndzuGxr8HXr8k+hnlBtdL8+ppNoAaE5nm1w2JFg4DergttUPXbXEKievKWOtzEAKvtSSlKJkchZjBruJt1ut5qN/Gws7QThBoD02kRPgmTV5zNts57xcHpo+v0+scD7q9YulBwIpn6/IlEPbcVDbfFA4WbYrvDJAPb1ZcPibiqXzOz8sbFl+B+HMTtBeXksOICL4QGCUkrE1X79i4sY9uR7m4x6UPwTzD2dtXSy1+AcyHpqAvVAqDbz/xdqxUKbdmsYdUki1QddjRaryhCK5B8fYeqiVD4jncVf2aeD2NmH+MfOlQgQyESZW+HISXYdlLFs9jT2QrrALyPnntv0xeR0KUtfadoDrcg+HCMUiGKSJvj4nqkICC6LbD6Vt5MuLIXPQNERCyxJ8LkGTLw/LElImzzdT/qfgJV7atMRMI/qvkylC+QYlf35jYpDCy2gMRtaChQpvFi9ZYorwtsN8H8NY1dqL3s5tHAM/IF2OwCeoR7K0S2vsF9EWGfQt4WO/XL9pPSLyebBIhKI2INFY/3/hJjrMf04ejBTsoMPXvsnLthrloRc1Apjhmz5qGEW9PGCEzZKifY2Q1YMCFmQs4SXeJ+aGrCuP0+hXgvap1iDbjCGhb6PGk/y06nD6AKtd13WzQGnVvLxkFLVy73aBp10r1GTBDNPJu1P7wmrUAg0myvCQKOuUIy8j4WDivNN1N8ekCbYegegOezV0dapGTm98+UvHK83MDAsFhvqTgcLHcDGQsJjnUY0uB3AkjZ/3w3L7V/TmJNhO8QXehnmkFi3fD4Ij0lTzJ3sc+8HA8n9n3blil8uTJskn1FqPSvgZoUW5oyNhc7nqlYpwRfCwLHZ72CmSoqKg+iu7Fe5K6+8sT4fRzBQ4BgRefA/ApLcnrxZ/YcwyZW4UrrXg3AuwetfKNs6ZoHFLZoL67mvvbqCyp1UUNGtmZ3pMs9GgfvFIjP0ZzMUutWb4JbPoAuKEDmojQF5AkCyTKrti+t7xOdcTsTBb4oXGOr5yhwz7Fw5nu2dG76vagmkbJ0iTZStZ3Kpa7+0qCmY286lOasK4jYLfu67BOKUOlA/T1ANWnWQnZ/UOeGrevmZsMTiFW76SiEs0wctOxqcY8Y+jvWwFG4ASs8ImtEA1j0Me5ZNJKpfaXB8FjkbJw65BlTAAFLteHeNFklMHQSY/6VPy4A3Hlaa0iGTdTFO3D40jD9cvQ3JEIYi0UlhclxbOK+jXDuw8pDv5SZSF/6lYF1fR4EghOjDQPG0EkteiO4HW1qdu7Tp5VpxVtvvFxc6krLC9NlK5FTnTLfhaMHR9qGRiNMEnmipWhcguCa09VeLaf4dN3fKTCr3gPDiDBWDwUscPXD2tj3EwimnLNfg+118o1KKmSwX1+cnBo8bgWkYO1oBXBzaqrpMk0dWiAwUTDSYbLL53v0pLubA7e8uzsPO4khXoXqLWa8x4tKByYuw1v7o2GhqCvaBvnbHRbd76DALnyCI4d3VM+RO2jGf85x7gVHjlAXW+bfhcYiQ97aLIlcZjpM3juKSaosN/F7zdj09OB6l8jkrgPcsMuSbXk7RmXG+TjVzumYdKOX8MkbnorznCB3wZ/r0y6UJnTB7zJpgIkq7NG3hs9jc/lxzXqoAIeutyJkVbr5kpeSyW4f8J/vqMoLdyACofvQCBbt2jU5dLRwIMApJHbjrrvB2OmyUvpRzYzr3B+Q1FyzmBNzrxSpjosx0hDzhwD7DoehvaUzRxWbTbvpk/ghZShMES0YVzdej/K9mzMIQeLUXJQ1o6qaDl2bleCm65u4KLmnrJLZNOebhBz5h41F2nwbQjcdYboB9WFLiW3NXVq26Acx1lTYqxhZcHslpxuqZJeVEUUjdFNQsKmrbXiD843DiXCJ7DND+R5gLB+WgI8nJnkXNKR5xRNqTFQ0dQ1kTHRpOoytZ2wKh9OKmfHOk21xHaVL8aGa8gZfi7Qag0gzeS4qZuAv1EaVjy2wIDpFCNv1i9qzkMVQgk2NqkWg6ZF770rahxy64VcHd3ehiQfdZFvfmZ7KmAJFDhEjd+8uuLskZ3yBIEo1y/o7b+5qD5omfJiRI/1lnMe2ohFdHTugNjhcmKv38wOrHe+v4y2ZW9bPRJYUAG+jTNLgUs2dqRTWADHEuF69Yw8/zEyJsq3FOhhTlrAQWrZFFwAlyFQvx0WwkJRMl2tOm286pSoT9ryRLxJM2d6sdoxruq1E+g6Rfz/1qL7Mhy1pD6wuOU7eyHUNAWQBBOpqzjocH2u0Xo5XFTB3vJrk1VRNgkxIejyWMPd8eXJF9DcmKVl7rlavcQ1V7Mb8/NMaQHUMnQdFnOfjXsEFXxEopY+KEQlx1avZbOx4/M/zTaiUm3abzpsrvI7M/1aVZyMKYcPpSJEcmFsMMNc7H0pIGCyAUAYR4qrd0yw84CMgJNE5SZ6vX7maFHgUEtpcqT3kFPONoG53u2dlseESxXVkMjw0jU/CarOsdRxUVjhgbUgRgwIl/wHWn8sSf9x/Y82Lu4GxbzkzUFApHPy9qp74N1wVaovVpiGBdn1gXDn1150jWLerW3RZK1t2SHJSuyc4QsNMx8rMMoNLyjP10qPLfmblAHaYnRY/zTWlzb8bf7iU4AMbsGglm/8Gon/jEQ6Wj8XfAuS5QwcWEoS6zKop/zPdSlNxkuej0I9Gvk47vGNfLDmNyhJTHWOZIhwl9qsoMLz6O1u1AzuE9Z9STZVpMTegSiBkzB+dHiJFtIcSTNjkx40LHU6VWV8D/JM91VDN66Y/9oYgewo3Km89QLHA7cWwYvaElbFuvcKi4GI4VjdL30w8Wg1WpcQuiL7l3PAMakvbLxqd3zJxGGop0BZNlrPUmPocf7knP5iGmcYqOC3MMbas/i7tIWdGn6Rs76Yj2C1I1aH0PEwjlgpndrDKev19U/RF4vS0OSbSWkWxy31cGzIPpctiaPZ75NaET67Z+v5qN8i7MqSBwzDJT/xp9j9ThwJc570xFjfdBv0cEiMFrypDBDULWRamo18XEzCwS+JTulTz5f539Kq4jfbc1dIaFsxSlhaoP6H7Luubnaxw/uf27Nt7MeUPz82CZLdNg+F7OyavviZbvqv7JXC+OeEAPJNzd78SZtqeeFE0yvMuua0Y2lvs1stFlaL3X9pBSNHaIB6o7fvKP0vJGWxoFiAyzQUZwkxAojDoQj7KOmCfDqOMnbgFZiCROjlu1qCA9yJRdAlbWbCLiNZHKZbf93aecTWm8yZXryy78Y6SUKo9nxF5dYNAWMbtsxVV4uAYIUKnF+24D+TYg5gakfsLixaixIy3EVg7dM71ERisObJlsons7NRjPBzoiHUre3odwanZmlsHAKE3w0IOAKmF+9ALZTvSzieoH2ezy+e9yh8OKvzD6fZoBxOsVhjzy6w5ZdfCekSkMbAnDyx5Owbu/aii+gfPhj4tF5PNbNh9eCL/QETyuhOU0x5oM9sdYKoUQUH3HTRSkqgtfB5Tcm/a+HM8ulrZQop6K1FOdCtBEb01Rm07Vo/tFjRTH6IM9L4jHQHAIhA+5ZCccg1aLhx5OhHuV7um788t5TRzq+mxAx+q3ERWtK3+IEpGktAxiwRnDMlgwAY3Sd9uWu6fbpx4efeG0bJNEyYX4oWVGtm073JPbK5cuoaRc5UwdApAUcR1jU9M3xohPIBhXHj+vKhOQ7t+Qdgo/HW+dGubMM6xIRcGuZnTXL2Ah/L0ylkPduvirirO7KGhAyelVvYokx6SH9skVmFoP+tAa7TTcagSQiDrV3n8JmAjZeBTaISuEkYSmHc40Mv9jL6gBI7kIxvBbEWnHbhdTVpJAtwjvJnmXbrCJ3LZiq056ABjXreQZa5AvKRy1FYPF61S8WIDByxryl3bd+24/PiMNr+vq3v0pxoJ/6NGXM9BiNwnvR2RfQczw96CMuJWxujV/OJCUSAzFMw4eD0NaD7zZmCC7hq013KRYT2A88W9EbeuwTmRyvsOE9dY1YOnYF80z86Lt2WYs7/C8bHxaDyjNkgPKBBgdnjCc3faUKLYSetotVLb8BTTP+KE0/hghVE/lnRp975NSS4PnSJFoI1qpLkCn6iyeLBkFZoFOCOI2Fl98161Bfm6mHYtoX49A3nK/6i5KqEwGyBs7j198VBMipQAD/XMJUawiulkvPez3XNWxc+Mu6oc3sKkXAiZ8Pddc+pO5XRk4mn8XR7d95pai2Z+E46hgYENGw7hs/9PkW4R902TBca3rKgqandqW6DkSIbzSOItOEZffV2/KySJzcl48N3DNkDXfJx5toXSaPzujHWbEJgxAsT0MRqNpL1nHq1janWqMe/4o/o/0FWpLy3xOFIIqw/xq8T+KGYxUNALv2BtPJU96iFKV43rPXI6NoRkLixm4ddZGO9jQ1U0G3swn7mFD0cdnalKK3c/IDJeChIwKI0zzKD8GMmPWACflAgOGk4QU7Mb1niE7Iwh7okbtASatA1hWjEf77Z3XJ9cgjDkLrj664sXey/I0afsj10JxRtgPDPqeaTU1bp/ZH0ZN/wdkxJXFkiaxlsR9OUYFaXRXxzCLB6WvKPCx7SAvLXcq/bMHjgf3wqHBNQ184KiDrmLSCY7nXShPAgAJJqE40Q2ZLrrNMqKFRnTB9RuoCI7WpRwWmV00ZhaOVjZouG1UK1aaWwqb+Vbd91zcjD3CZp0SgGmD5XLQc9FKYF3etV+7K9W/fWDxe/AZiIx7oRcpp+O4E3Y6mphiknMEBapxJvORPqbdWAj3NloNUMpklAimEkCg+NsVix/lJ3OwJhuuhEii+YEC3DUcfFAQG/CkN89GKoYdX8MCP2dzz9XeSKli8UglUDKZrhu3xHUHyJGnk+oGqZNSOpxsFI2A/70pIWguQGE6ZArV/KmnNB0alotuwhmVv1Lhbz2j0Dr/7oCJT5oP6dFhDZXAQ0WJ74FWuHQ7CuOdVi847N+/qbW2TH7K8oIxftg2vO5VsLmGq1mzipm1qsAb26+iemiIFA+FfnNZSqX9WH+UyDoXvKahIBbEjaBUwzN8dVkUhQ1+fBqzfOokM/44szuB7wXt2+xnIvEphcv30bAetvk3o2nIdivX3oAo45vxXeU7YMCYabWuuHKkQ/3aAwu9fputAULwWOeD3mxpBizzz5AVJ0HR4Y7TL9mdDcXZ+xg4lELbNVvcxq4uwnaqV8Evjwww3W9MiRvYJKJEXXcrX1VwbO2Fc7/bnevDUdIDoa5lg+GrmbGKn1TRRhLR1YiCEUas+AzGU/53pyrA0Yebg17GDBjngw5D18MXbrSbufo0TMgigkUmwgk1rlYFFjX98/kIbqVYscY74U8y0+J7U+N+IYIvAhkARSeGHsFb8wYd8HhkrBwoWm2rnYG5Ft8OJ9FnFWjvQHZTzgMaHEj5ATuu1aBDH5SVHVs+wnBVXqolOgg5g6RuibyqPu6eDpJd2bmN1+T+KklSwjYS3ubuP+c9UNbjXA78CGwtkAJxsErOgcRXWeBxucLfvK6cnPr9bvmxmYmLVh0mFhu73sSs4lX44MwvOfHQ0g9ZhXLR/ackimkBAj+S7j2Qmkfn3IoW97Emw8bnl4Q764Hi8nmthljfXFhgRxfJmPiOsrgUJ7+eY0ZHZ+qCk2rYXYkOXBtyrwT70EXyJ7GA8w+FOvI1/YhmqMdJn7ncWRDgZYWrZCwCuIlQmEt5iHjeHXKdHsTNZr/1XLz8vY/ib7olbRDw1EsTvfejuV55Kieboziwdk1WFbkUIV6bHqjBn0p+mBCSWRVgVUMYYXknmUDADTF0f2fT2/eNdEPXzqvffO0KFko0vZT2o52N8zSbWexWNO65P03y36jySjyVQRDccXsSa7iTFoVdchr0ee6Sx8uD3cs855t153Ix4e5A7v+KFtZrfuigYH47YzxLH4v2EPI6+l9ZlE4ygDpZiiI1Kmqx4T2j1Tygz7sC0ftYsWdiC2F2PkqMqK4kd3Fq7IlCLHZqZ4H1TC6SskOXMyHeRQpgjYySJVRipwFpFoQcAYAmdK2CDQxJsjOPwxc1IHYVIOZASJc0Z1wevIlO65gUQyl2nMqXuBvnoXff1WzLsYM/1xsI6cTej2+/+m503M28Di5ilo9tfkGym95Afy4kM3edracHN5wqwDPs2doMuToza3Q4l4W28u/M94xv7iYnEI5lTFxScHy/6OOTXdOZW4YY+H6FaI7TtDgHl1VS7Nm3NttLr2PZk4pDQ/7J7xK3BLin3BjzpY8G+/wBGSrVJYGjz0nRiOP6x6PKA68RfNi7VcQh77pYtjVLJE9D3x82Idxb5PnRL5IMzjGZTOziEXH37JORRckzmD5g8EiGQghOIGMIfkVLD/PLeWKLQQ2aVVVEvoF2F2fVZjYOYICg3stH93eGxs8pAgNoXb6Mc37cvtyc5AgI+Gw9sMi/Zmn1di+WWBM6HmoxRTX5T4ZOTxQV15UNE1t9CQTmQhDY3YCPJY2W/emBKc5SKTo8RIMZvO8a3lgjLgBYB2plJZB1O4Fd9dYviN+HwEoRZqTEppKmRSsgaJafTdJlYzJLWOpOsdnikZWG/EuFVCfpojmAG8AfljkKQlSAsjLOdeXOjGL+xVf8TiufnL9xC8Ww5EuZix46MEGYosJ4hMXJJoDssnp3XV0Pj1CmZ8YIn/FURkVQcFnS41LZuUmOwqJMY8JORoQlAIfTJonAmKdGptxEa67hY2UD5hAheh6r+APicLkVuMaLNklYYL7Vbo9GMVE+zc3WeNS/C1UjNs8UCVOmvh5rvDMLhKdLchZGFUmHldFpk2xspR0ZfVpCDaBJwIb0Ddzj0C2WCEI9p6B56VTXlA+x6iV9W0px5QKuaO+f4GqOc6Wm7zVxGbu5VcxZMIPft5vIOoOtORCeleMZ916Myaw+2eOwNL/8P6lV2Z8zMZASsC7yRxn53NAMlOrQDc5asaIsPJKX/BEeZjHc4hYO591wIIu57XvSZOMT8q7AS217wpSP0k6
*/