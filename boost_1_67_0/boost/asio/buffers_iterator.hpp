//
// buffers_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BUFFERS_ITERATOR_HPP
#define BOOST_ASIO_BUFFERS_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <iterator>
#include <boost/asio/buffer.hpp>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  template <bool IsMutable>
  struct buffers_iterator_types_helper;

  template <>
  struct buffers_iterator_types_helper<false>
  {
    typedef const_buffer buffer_type;
    template <typename ByteType>
    struct byte_type
    {
      typedef typename add_const<ByteType>::type type;
    };
  };

  template <>
  struct buffers_iterator_types_helper<true>
  {
    typedef mutable_buffer buffer_type;
    template <typename ByteType>
    struct byte_type
    {
      typedef ByteType type;
    };
  };

  template <typename BufferSequence, typename ByteType>
  struct buffers_iterator_types
  {
    enum
    {
      is_mutable = is_convertible<
          typename BufferSequence::value_type,
          mutable_buffer>::value
    };
    typedef buffers_iterator_types_helper<is_mutable> helper;
    typedef typename helper::buffer_type buffer_type;
    typedef typename helper::template byte_type<ByteType>::type byte_type;
    typedef typename BufferSequence::const_iterator const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<mutable_buffer, ByteType>
  {
    typedef mutable_buffer buffer_type;
    typedef ByteType byte_type;
    typedef const mutable_buffer* const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<const_buffer, ByteType>
  {
    typedef const_buffer buffer_type;
    typedef typename add_const<ByteType>::type byte_type;
    typedef const const_buffer* const_iterator;
  };

#if !defined(BOOST_ASIO_NO_DEPRECATED)

  template <typename ByteType>
  struct buffers_iterator_types<mutable_buffers_1, ByteType>
  {
    typedef mutable_buffer buffer_type;
    typedef ByteType byte_type;
    typedef const mutable_buffer* const_iterator;
  };

  template <typename ByteType>
  struct buffers_iterator_types<const_buffers_1, ByteType>
  {
    typedef const_buffer buffer_type;
    typedef typename add_const<ByteType>::type byte_type;
    typedef const const_buffer* const_iterator;
  };

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)
}

/// A random access iterator over the bytes in a buffer sequence.
template <typename BufferSequence, typename ByteType = char>
class buffers_iterator
{
private:
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::buffer_type buffer_type;

  typedef typename detail::buffers_iterator_types<BufferSequence,
          ByteType>::const_iterator buffer_sequence_iterator_type;

public:
  /// The type used for the distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of the value pointed to by the iterator.
  typedef ByteType value_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The type of the result of applying operator->() to the iterator.
  /**
   * If the buffer sequence stores buffer objects that are convertible to
   * mutable_buffer, this is a pointer to a non-const ByteType. Otherwise, a
   * pointer to a const ByteType.
   */
  typedef const_or_non_const_ByteType* pointer;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::byte_type* pointer;
#endif // defined(GENERATING_DOCUMENTATION)

#if defined(GENERATING_DOCUMENTATION)
  /// The type of the result of applying operator*() to the iterator.
  /**
   * If the buffer sequence stores buffer objects that are convertible to
   * mutable_buffer, this is a reference to a non-const ByteType. Otherwise, a
   * reference to a const ByteType.
   */
  typedef const_or_non_const_ByteType& reference;
#else // defined(GENERATING_DOCUMENTATION)
  typedef typename detail::buffers_iterator_types<
      BufferSequence, ByteType>::byte_type& reference;
#endif // defined(GENERATING_DOCUMENTATION)

  /// The iterator category.
  typedef std::random_access_iterator_tag iterator_category;

  /// Default constructor. Creates an iterator in an undefined state.
  buffers_iterator()
    : current_buffer_(),
      current_buffer_position_(0),
      begin_(),
      current_(),
      end_(),
      position_(0)
  {
  }

  /// Construct an iterator representing the beginning of the buffers' data.
  static buffers_iterator begin(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.current_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.end_ = boost::asio::buffer_sequence_end(buffers);
    while (new_iter.current_ != new_iter.end_)
    {
      new_iter.current_buffer_ = *new_iter.current_;
      if (new_iter.current_buffer_.size() > 0)
        break;
      ++new_iter.current_;
    }
    return new_iter;
  }

  /// Construct an iterator representing the end of the buffers' data.
  static buffers_iterator end(const BufferSequence& buffers)
#if defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
    __attribute__ ((__noinline__))
#endif // defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
  {
    buffers_iterator new_iter;
    new_iter.begin_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.current_ = boost::asio::buffer_sequence_begin(buffers);
    new_iter.end_ = boost::asio::buffer_sequence_end(buffers);
    while (new_iter.current_ != new_iter.end_)
    {
      buffer_type buffer = *new_iter.current_;
      new_iter.position_ += buffer.size();
      ++new_iter.current_;
    }
    return new_iter;
  }

  /// Dereference an iterator.
  reference operator*() const
  {
    return dereference();
  }

  /// Dereference an iterator.
  pointer operator->() const
  {
    return &dereference();
  }

  /// Access an individual element.
  reference operator[](std::ptrdiff_t difference) const
  {
    buffers_iterator tmp(*this);
    tmp.advance(difference);
    return *tmp;
  }

  /// Increment operator (prefix).
  buffers_iterator& operator++()
  {
    increment();
    return *this;
  }

  /// Increment operator (postfix).
  buffers_iterator operator++(int)
  {
    buffers_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  /// Decrement operator (prefix).
  buffers_iterator& operator--()
  {
    decrement();
    return *this;
  }

  /// Decrement operator (postfix).
  buffers_iterator operator--(int)
  {
    buffers_iterator tmp(*this);
    --*this;
    return tmp;
  }

  /// Addition operator.
  buffers_iterator& operator+=(std::ptrdiff_t difference)
  {
    advance(difference);
    return *this;
  }

  /// Subtraction operator.
  buffers_iterator& operator-=(std::ptrdiff_t difference)
  {
    advance(-difference);
    return *this;
  }

  /// Addition operator.
  friend buffers_iterator operator+(const buffers_iterator& iter,
      std::ptrdiff_t difference)
  {
    buffers_iterator tmp(iter);
    tmp.advance(difference);
    return tmp;
  }

  /// Addition operator.
  friend buffers_iterator operator+(std::ptrdiff_t difference,
      const buffers_iterator& iter)
  {
    buffers_iterator tmp(iter);
    tmp.advance(difference);
    return tmp;
  }

  /// Subtraction operator.
  friend buffers_iterator operator-(const buffers_iterator& iter,
      std::ptrdiff_t difference)
  {
    buffers_iterator tmp(iter);
    tmp.advance(-difference);
    return tmp;
  }

  /// Subtraction operator.
  friend std::ptrdiff_t operator-(const buffers_iterator& a,
      const buffers_iterator& b)
  {
    return b.distance_to(a);
  }

  /// Test two iterators for equality.
  friend bool operator==(const buffers_iterator& a, const buffers_iterator& b)
  {
    return a.equal(b);
  }

  /// Test two iterators for inequality.
  friend bool operator!=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !a.equal(b);
  }

  /// Compare two iterators.
  friend bool operator<(const buffers_iterator& a, const buffers_iterator& b)
  {
    return a.distance_to(b) > 0;
  }

  /// Compare two iterators.
  friend bool operator<=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !(b < a);
  }

  /// Compare two iterators.
  friend bool operator>(const buffers_iterator& a, const buffers_iterator& b)
  {
    return b < a;
  }

  /// Compare two iterators.
  friend bool operator>=(const buffers_iterator& a, const buffers_iterator& b)
  {
    return !(a < b);
  }

private:
  // Dereference the iterator.
  reference dereference() const
  {
    return static_cast<pointer>(
        current_buffer_.data())[current_buffer_position_];
  }

  // Compare two iterators for equality.
  bool equal(const buffers_iterator& other) const
  {
    return position_ == other.position_;
  }

  // Increment the iterator.
  void increment()
  {
    BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
    ++position_;

    // Check if the increment can be satisfied by the current buffer.
    ++current_buffer_position_;
    if (current_buffer_position_ != current_buffer_.size())
      return;

    // Find the next non-empty buffer.
    ++current_;
    current_buffer_position_ = 0;
    while (current_ != end_)
    {
      current_buffer_ = *current_;
      if (current_buffer_.size() > 0)
        return;
      ++current_;
    }
  }

  // Decrement the iterator.
  void decrement()
  {
    BOOST_ASIO_ASSERT(position_ > 0 && "iterator out of bounds");
    --position_;

    // Check if the decrement can be satisfied by the current buffer.
    if (current_buffer_position_ != 0)
    {
      --current_buffer_position_;
      return;
    }

    // Find the previous non-empty buffer.
    buffer_sequence_iterator_type iter = current_;
    while (iter != begin_)
    {
      --iter;
      buffer_type buffer = *iter;
      std::size_t buffer_size = buffer.size();
      if (buffer_size > 0)
      {
        current_ = iter;
        current_buffer_ = buffer;
        current_buffer_position_ = buffer_size - 1;
        return;
      }
    }
  }

  // Advance the iterator by the specified distance.
  void advance(std::ptrdiff_t n)
  {
    if (n > 0)
    {
      BOOST_ASIO_ASSERT(current_ != end_ && "iterator out of bounds");
      for (;;)
      {
        std::ptrdiff_t current_buffer_balance
          = current_buffer_.size() - current_buffer_position_;

        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_balance > n)
        {
          position_ += n;
          current_buffer_position_ += n;
          return;
        }

        // Update position.
        n -= current_buffer_balance;
        position_ += current_buffer_balance;

        // Move to next buffer. If it is empty then it will be skipped on the
        // next iteration of this loop.
        if (++current_ == end_)
        {
          BOOST_ASIO_ASSERT(n == 0 && "iterator out of bounds");
          current_buffer_ = buffer_type();
          current_buffer_position_ = 0;
          return;
        }
        current_buffer_ = *current_;
        current_buffer_position_ = 0;
      }
    }
    else if (n < 0)
    {
      std::size_t abs_n = -n;
      BOOST_ASIO_ASSERT(position_ >= abs_n && "iterator out of bounds");
      for (;;)
      {
        // Check if the advance can be satisfied by the current buffer.
        if (current_buffer_position_ >= abs_n)
        {
          position_ -= abs_n;
          current_buffer_position_ -= abs_n;
          return;
        }

        // Update position.
        abs_n -= current_buffer_position_;
        position_ -= current_buffer_position_;

        // Check if we've reached the beginning of the buffers.
        if (current_ == begin_)
        {
          BOOST_ASIO_ASSERT(abs_n == 0 && "iterator out of bounds");
          current_buffer_position_ = 0;
          return;
        }

        // Find the previous non-empty buffer.
        buffer_sequence_iterator_type iter = current_;
        while (iter != begin_)
        {
          --iter;
          buffer_type buffer = *iter;
          std::size_t buffer_size = buffer.size();
          if (buffer_size > 0)
          {
            current_ = iter;
            current_buffer_ = buffer;
            current_buffer_position_ = buffer_size;
            break;
          }
        }
      }
    }
  }

  // Determine the distance between two iterators.
  std::ptrdiff_t distance_to(const buffers_iterator& other) const
  {
    return other.position_ - position_;
  }

  buffer_type current_buffer_;
  std::size_t current_buffer_position_;
  buffer_sequence_iterator_type begin_;
  buffer_sequence_iterator_type current_;
  buffer_sequence_iterator_type end_;
  std::size_t position_;
};

/// Construct an iterator representing the beginning of the buffers' data.
template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_begin(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::begin(buffers);
}

/// Construct an iterator representing the end of the buffers' data.
template <typename BufferSequence>
inline buffers_iterator<BufferSequence> buffers_end(
    const BufferSequence& buffers)
{
  return buffers_iterator<BufferSequence>::end(buffers);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BUFFERS_ITERATOR_HPP

/* buffers_iterator.hpp
qsypzK7MPcEywTHBlppunbH7bTd9N203A+fbyOj2TtjOmwtyt0KfGp8In1KfNJ8WnzCfQp9kn4aW4fb+9rn28fa19p/tU+1DBo5rDlWszqzOnM7sztynLKccp2ynXKes8+mHo35j96P3Y0ijvm4dLT9XbJzYSDhI2Ei4uDPivumPSo8NjA6M0YxW7gB31Hemd9h36nbcdi52UHaiduR3RnYYdsp37He4LjwuUC8UL5guHC+I3NqgVdBsaCc0BJrX0rNiG2hxwuaV4TcaN6Y8qjw2MToxBhgFjFWPVo85j3bsNO147dzsCF0gXUhf0FxYX+BcaF9wX3hdoF8oXwDcuny6BWyI2YC6lFFWNYzZVJYRjLzyQ2p19YyCI4NsdbW1+Baco8PjdkmzPOWyWtMVVrpjdXoWDaN2ybN85YpayxWeusd1rrX+ukS1fFbbVh7DB5nJqbNU5fZaTRUnuoK1vlZXwwdZszQMwiM5lpYItZ90EXTzKj5qUTKkz3KX5+wZ6mqr/sSZgUJ/uQqTCHqFqGnrOulCyRoqvn/3N1X0idEw0DYsRGeqLGNK4yyvqNUiEi6vqG///l2COUvTUFOtXJOJvrwqTVPTkBpACwgzc3Ww8lj8ztbSKypXYaekabnoX0gZtn1bkXhQJue9IOpSjFaIi5Jsmrc5s1qLha/KVl7VqFAlk/e+dPQNkixFcL6GaR1Rcqthmli+WiE9URKnr5PhdmbiQSvCByqPBl3NtSQB5isRjzcx8oLaWWJb6mmcaGw0o2V6P3IpqRDr5oDxNAWR83wyChXM1ZkUB0f2c70UPPNEP33syq7ViQqUPSQrcg4SzT4if3yPuZMym3LG6jYiKdv3q4Xqe33F90YJutCnUphAzm037KSzpUS+zo9OPloHhAmrZIXsDPW16laaSYw/SofTW8MsZ7c1ZyG/avFLlBhKq6r0DFS52rRcSlrDWkPLj3t0SzOuoRlYnHVlnlVf+uQYFFPTddWLtDXnxxvuKwt+ucduzyTxSgdE1wIPh3GSNZI0x+kx3coP7IZrRcjoy3aSJuhLSyrKZo9/uZXJ09vhtIJH9aSf30Au3ut/jVJbiIM+kW6+Nmt3Nu0M24cpgv/G3L2L8vC15ukTjBmjsUowz2eeaFzoB4n3A+9wyJUuIiiYpTJlfr+DoJM9/8fBmTFP3Xe7OX+Eu/5+8uSyb1m/Zhu+VVWm6avpUWeWq/Gt/1xywJ3P5dQs3qMrw/dVK61kBqSpN7GElbMa6qX9+lC3rbs9W0c/XA8ZlmT/mZI0u4S1M8tIi/RIn6aJGFkzqHiW3irn47kIp4I61Pk1PazbIF1TlVt9lIkBFrtwmwqljF4+BsGDs4TRElWAw4adgC86eYKdXh5ba3ZGS5sp014/R866ImXskzSRy+2FutnlvWo7K5bf2z5s8ZoPVJdlYZbJpdcMNQhUJsn0yYlYXJFHTaX6LG3fj7DM50z1AHwCJtYtBWrRyqmFPwwya79YooGi0IXVdxL7TdDDeYnRQtFTs7cSd0yq8dK3ZHHFBa5GBRXkxa1SNOTdfpOjVzJV0zIBR4gK3vY1ppjrhxct6WXXrohP0aYW/2AdVb9v76nnXVnOhkpT7mikJmtqJWmkpEywSXufanhj5rdHyCl/wtEe/22Z7JY0tTBJ77C3pyFeTmgReyFkfPxh0FsZaC8Al2aCUjCHPdibJHKgBpf21f8gfqIXK6c1SYT6u8iBCumAn53xUV6x9x5VuC1so69SDHHdbljSEMBFlkor8xeVJRqX1LxGUneu+15ZT72WGXpwZC0EA+rN8m2ysY/O3d+OWTeT3sPf1kfXA290bWmTg0pZ9oPBZm4F8DCX+L6y2yDVbpaq8HoDbkgjSTvVxpKzIReDZZLDe4LNT+ib/dx4WKfCFGf/EUTSdqkiRI5+mlvg14QnNbnyl5LKsoqyITnuQdl9Vj8hN5k6Hs4sXuSGZq7kctRKsWHCjm6hq4xWZ6VLrDlpAG0GkH6mhDCS5KcoD2GB2LdzLDCpYoO1+gbpYnLUbyoUnJRgYI2JlS0yge6A1GzN0PYbV3PzYWhzi6ZZO/uAEm2pejw7IF1/fGAmKUNckJBgc8xdD8D74Gu5Ns8g32Xkc3eVPkcELQHSjX3+ZBZ7DC9TvBTTCGxoZCddRI+EKk0zqClWV5gXJ/W8c1kaK9/VGoo1h+FC1xdA0XtbUFLbZ+lLNcsS2qK7neyRpT2nWVXhuJxGMnpD0fgO6R3SexxSNDI0iljSWPJYMmYJg8/NuC7kYerMMCbgQ+nOwP8oeOIxA59KP2FDmuK7wh6YwM5kQShQ/cF1sX/PBAsmEfnvBKJgEon/ToAw2AQDxSZdhwPrB/ujxDvDQphEOv/R+PAm3hhrnTsdQgR5tM0h1wwSNRUyEzZDcYFxeecCu3npZtr7vle1N+xr1LuB9zgUSg3lua+h2GTr5GD9z/5b3sKxNy9BdmfccaR52+ZCFU8jQ+xfUdbehU6eRkDscZT5/eZCpxnYOPohKiGIFQKQeuob7MKF4lA8/5MR7lDRpAO5gjvkilqN2T2Q0WrjfrFWlM/qJjU8ltTQYqTrt+mSLMHCydoPCVE+u5FlcX1Uw6XAosGcBKWLsab7ZXFpAff3oEB0R5+94HA03z04dCLI5Ht0oqtJVnTDvbwoAfdz09aF6UYz5eVIwWO66/rihekvmz/C/4pkb+r0t0kIusp4L6WdnckRpujLPVc8PHDE/ukyQT3vxinI6k/J6rfI6tfJ6q3J6oX/UfLgGOM8aT970mL9eni3Ew6CwvaK9iJ8Ff/a85Xia/5X8681hnnNfMVmQ79afn9kUTRRPP/kjqiVLKKFzBj/2jTkq7Ciji15PDWoQerNW39hfer90Y/pXwsiaDGmHjgSqgTS/xJ8DpW5ax056yL9D4raxJLvP0cp9nZYp2qnNEdAhiF63DW5FfUCVwaUwvHUn2y/kyrmJlGQYdYUy8kQVmFgeCaXbk59jVigyx6OllTszeYjdWlGe0mhSOke/dzk/Utf4DedkYYF+TVWHA4Psj8ew6Ov1t1VhUr66+IImfRutMhXkOnPfxWTqVmkdedfpDcfV5KY7yQvStB9k8Uw3kmcZYx2m1gHSneD9JHMjLAfG808GgwOZyGSI+3fZYEkkMilumUrg4tXZLv/gKn4lP+KCiOC3EGFdrVWRe9VXv1rMdv3n0G/UAvDCJS6dHiYVj7qNf+u/zgNz4WhNE/4jyI7n0lcn3CZG1OA5EgpaEOR4D72IvvvCWTjFmR8e6VAFFyJrrYY50lRSDwJne+TGI7enRrQkDDypCuMSBzhfdCCYYdfGyW1QuxIQ/imuzHWG2Lrg1S0TfQtxctEz3T0rd9h95SdZLuHxF+ywdP4fY3P7Bvexdz7v0T1a1rY2ubfhKeZ6XTjy+di74Qmb0L2rbVNF+fz5iaeJfkRewBTdUd9ZEffFIsu8sQ9EkSxd01B2OquI60EAbYa+5UKChysMuZLbSDH86x8hjmQJt1jIr7ERveNyt959aa9D+UvUS2GM8p64+1BvzFbCnOgQXrERHyNje4Xld+I0L6EfWan313uCDvTGOw199rbOuaPyiVGbPfFPTsw7S4PFz3Ky11XJ8QIjxL/pU54z2zjE6W/tpnSxHNtN7lcLupcjdjRgd9rhOrrx7l3PJvbpB268E/Wy2u7d/9sXTNCNXuxpnx/Jy1nWkPD/pUI/1LpWvSoMXde5lWN26e1cWRffppvB5kO/voDWinzGpqECabCh0OvLVJehHaQUTVelzxTl/xqLt184hGasl7ImPqmWWOy8I0BPVjNNDWyWYNDEQFiOLz9/qPPKwNi2FTp7n8Vdfd5ZUgsmio9+Y/R/w+MGsLL/DoAgENL7bwFXFTd1gc8Q4dISHeoNEwwMLTUUEpLCIh0d4OECIIwpAiChIAojaKEtLQiIKGAdEl3h/ANxlWfx/s8vt+9733v9/s4rrP3Wmvn2fvstdf898EvLCZPJFq87I3WjNop1dE1NgdP0jIRPL2v6pYpYifPQD16pl+w+vSG8bJ9U8Ruf2YbpogdPaX16Il/werTq8bL9kwRu/6B7eQj9POtVtzVf+2U7a+IqZ9TmynJQ+aWHaL4QuSAh7CmtX55baXiz6yTZ9nE4HKEc41w+6cl+HbFj4KuKtjL7rJrZpZTwZlk62SfS/EOzcUjdL2HGi3E1xf4UHuRWVt+TqIB5JmVan9eDiZU/UW2P88oAGXAN/ok6Ns/Ij9JJ94UjvuU7WCE9h5XzfLyFG1xTlGem52na7ZmRdlrJquo0n2lJZytx5JBuKfIAKz4jkTgkpHIxW2WQo0ZSlAB+KCsSS4oFGjsQ16dEGRvsn27ane88vYz1YloyUGu/JxkHU3V4h2HR0HMT6PSgk5xm1gYSnFfJ8ansTG8mf/cwaHT2BCd2+YagAbnkXDcx4K7D9lFP27FXR2P6X9aL3ylXdgk3sTMQwG+PM89ZsK3GevAaXfFKfaivX4Euce8EyTRQ+Gh7vDDyWVPxJy2gpVsfoPU47VkN8NqKYGLUxXcltpOJtSpzh/8OwRdbmr4JtrejGGJufJU8YWn16qhIEOBAY/S4sVHVm087aROOmYIx0c9rZDMq9f5suPpLs01JqjxtsZ6rao+vLq1LeIzM+bO6S5vm8UZ5BRPvah2eak7g1Bc37XMNQNqUMUBNXZ5xJUDMQXvWRRlCSVyIcxfp3Ook2dEMoflZLTUgTOzk0dy6h/emefjuDsfRZCkV0pMkBMh9yjF8d7jFMcWLlaBNu7c1/e7zpdrJA+k3A7mzBO+qCQy+Ly8frKhPj9PePD1bdmSoqUWTZTydXl9fpKHNOd8hMUUafyV8RKn12N48bT0dOpqGcbyViPDW96fZBwbGkPUiXXFlwJ3HFkbIoWZfAdxVyeUQhjcJQ/Kzow3JxP9nNQclpTlBzhIv+D7ZDsvJgj+UrvTf1op2qf5Tntpd1lpoLeO6mBr6PjwZdLtgvQyLbLGqhy2pcsyjpFctzqaV3YplwwbHQjxt7MCymTJGkRzGJdUMR0JOUK8VV5KTgZ7qx7K5dBzVrnf8oa+HHfJo46/zGT/hikWDnH0sCRXYHtbUWWYUzJdOQxSv0kSm2oFx92/JzFUxxVf0vGASttGVcc136r7We5cDjjJgJE8vkcj1iJMkZw7QbdotIfkhZmEvExj+q1g7GvLMXMxCZT5zRYiS+S3HEpBpE1EWpS93Yb2DSzI3I9PBMaJm4od+2i28SZi+BcIHIMcx6hPe0IdPam3eJTry0gIvLXSDfVu36oCBj4R8CfawiKqK0MQePdmGS5TwxYIGAPBUWRbWEV1wxc0+2ha8IwZORcITIKqbuQ9EYgia/qi9EbXMbRn5ERGZz8RMKHfmlPty5UlRurIrFVJfLpuryI+oku7zz8efle68mlMiIAmycurkR7G54jt884eK1UYmIe15RtoOG8fK5H/yLXapMCcpf0tF0qJY6XVQNMV6iF1hdhejjPAi2J1Th9jk2c83F9apYIZbH9+TuXh2/u3E0nY18zSxaTHhy8+pye2VzkfkEO0isWe0Temah8FCR2i3jzdz+Z2tUfYJKNPRnU5KtxIVroqbY4tVHiOrlmVtll1GR6R/jBj2JFWplOmKj0sfSZ9+AbV5uk3We7XEKpZqsu1SC9ssx5hUAbb0rGqCh06R3dPdSHkRyE9S6COdvPK/nHU2B7mJcx7K5liPeL9PffnTZUZsFv7WeCFV/fcKZsq60Ef6W6BFyZ+FD79IPSE/SjcuydgQrV+i8t4OMr0lCv7x3eZlBFtfcS60VmK4EKexspy0vU5tS8J97Tija7qh6Z9077JVQT3fNN6urLf+oe2kIcs/QOp17tHb3P5g64Ws0tbq8zA1oKushgcR1n6QVcXOTastNK0KvBUK/CqPlyeeVcgWehGlu5G5lWc+zb3cwbpf+RBZQj5Rx5UBiJUHmFWUq/pQMnlJJUQL62ZoY9sG3bOpF6lgnidk2ReVbGShfFqM5tqeKo38KvW5ZhyLNPc6dmlTbk2OIzTtKjwq15rh7zWnkk2xOukJ/P6FCpZaKDq0aApkqMXrTUVWol3efJyPPOyi1qg/tXJZKXQJ8Zhld3yxG4G0e5C7HVKHGuJ/swLocyFuGySNyg8p+8xk1pHa+XJsL1nLtQOU1GSuSpINvaWa+10G/PylwiV3vumWdVjtd7ZJR3kWoYPSlG5PcEW7j29AI9oLHNvj5gICfMOQnKWEBX0SK66FHv4Y2hZMellBzlkktdBrZlEnv1dlLZhPVbOFnuVYiyhWOX4B0A17sKjwN7rrJUfhcdgI7gLtQARLO7TPwi0YNzlEHkP2Yt1wkYks4jMgJtBs/K5LdZ8YWqIMxQlTO5+5yaXCgMH79m0DBngYqoHzyXhPsgpt3qfl3N+OBttXe26OrYdkGIeX9FK8ePWVb2UK/1SmuMr7ZpwZynupBdp5O2DKvjmdllBUIGeumGC4roAJAHszUosjmncMZkfU4hJXEjZuSfxAVXzOYrzIGI3kpTz+9CRl9C4Aw+TeoaX92QxjOmJkZ7SoI/EvxCiXaQf4ICb9JgpnV92Fx2yrTWG3BIPPUhvIWSh9UU67KzOxKNE0PhYc0gwAwu9L9JjJ8PSl3LiJU4IAwvjIeVaGFPNLwJxZNYOOGC8GSeUgYXNV2Rqvlm9+luEfLIDrkMlhYnTGb7sRqkX53kvrtdv13/hm7+qJA9lWmpwdimYjpgnDQIPwqL8iNdQSguqTyhaxUDk1c32aXIwcGf+LdVQDtwk7zZALrIjPEfZr4mnoG1NfI2I5cTpb2ywRvmh7aIC5sYRBR8HnL7IPknaC7TSep+RKXgAXN/glCPTOHPD8UYGLrplANPeuXwz6OfocQe3Xx/t8qe97KY7tSR9JCJHVmPbBOS+I9eOo5Sw4pV9LPwa6ycrFf88ypPseVBLTG0y5n6a3Hf62q8jQT38jrErHqd7OeRGmreMAjvqloFcB/S1n6PTqAhwHHHUuo1tA8h9CVEFDPA7dq94tPfWOVeTp6wXryQVBk1f5xaZtv4pSRNnNzjK7zgQR3Dkg9YIWY6OAz8ROpugaHH60yV1LeLIg/qfA0ezpw6/TV1giyRDLhQhk3Xh3dq/Q+DJyFVcfHP6vyfjbfJ2kb8lTcNEhmreXyfykbeDvtJSl3aZovEYT3hQBd8PgljNsbx3eEzt2uR7a+TtKr9Jmo6OUnmETLHRp80fslDNZrHSFTkihL6JPdukfvaK8IylFdWlYGhXNPJ5qZ19vxxiKBpZziLLzvBKznt+azjMrIeuLUs4UdV9g63De16pVTh26SbShY2Frl1OFtI1Wy5F5UrH/UUYLgmCphCaP+dOUjWAZ1Q7IAYqTVmoXGUhcxG0mdfPsizmD3jzomriy1iyQAx1Zogs5wtz33FA+AVB9ziTOg3GkId45hta8IyCt6pdaUgXOAvd506I3X81b7HNQmW57C0LSYk0EWF4ZaF7NqNaDtXAdjqqAehcBKqboq/Xh8u7FyNMNrTOZtQwU30iezVTKIfwk4HM4dGdo3st9+0pl5+NIcvrZV8wfOl1eZUpdITlznbna29T6jYPscTV63wTuxaIgXQqW8VeuraZQgtUJaguJnYadCIPQ816yIQUvg2jpf3QsHk9lWtwpJN4UnSEycMqV+9WBOqJTXroBBV25RAfdEu3rz5CQkY4n3Gr9orjjirA/Dl7AAUq6GWSBKN4sKhUHgYpvZAyHEdaR/B4LANZ7V1LgNYjoF4CloMp9XdhxXsf4GvPULu8iF5GTzDqxec/3wkokP1B8C2kqnW1BPRmAPUisRxEqWs3LX4QlhfQyw5Pje5B/ec7AAXiPws7yT6AmmeEo+5bwIN2Mf+RfuwVYVRz5gzHxf6YmIn1F4k/lNRDJVoDapwJRt0LUIkw//lBQIEzelk7waiQwG8LfYACY/QyJZTA5D8fCCg4g1amhPOzQC8B2MZBW3Wp6uMZZMG5dpbLfz4UUMCJVlaAM1rO/Cth1jHsj1pENRrlLt61SU7/6MKfhAvMnypoPLBONXsSTbBKIJ0xntbc7BuRWFhm3HIn2hcO+UTXcHjayA/7ZzWlwno91AqlQFpjgAuIG8oQRBPUEj3BjHNSx8x37ea5EMdwxiZYwJhHvY5iTisnx2vzS4U5xUfKcm+at64lsYQ4RjA2CQZQTuMY/SRcZwlZRRUUCKAc+UGI3li+dK2KsgbHqJI5ZDWUsYklgDISx0gEJYQwNjEEUPrhGB0whawG/1K4jhKCGJsoAigNUCmM2vd4IhfrdySIJrAlkAwYYF+ihu+CE11DiyvRBK4EUg8bXEDUUCZJNIEngeTECAtVv6+s+SEAa8ISyX0hjFj6D4T/2xRG9LfU0OdOZDyyY+ztv0oBe5vBVtvnDvQix5zRIX1gruqfInMs7M7urcQLva2vZVhGR9aQBtAjgF6UmJSvOGvlrgIRa3gOZ0lH5di+CSakoy3fBFCMln90JRqtICbcCc9hcrSwDoiohgfgOWCQjeJw1BJr+LNkAWSJDhP1xA4Taa9NhqHE7Qg8o1kDO1wjaZF7YpgL8vuis7WqXcTKHw73eBbkKUwf3pxd4zfwc8xJBe4T64agh9wMwScKJgomliWS/XwaxSNJK6uHhEfX+R7D4r8R/F8h5zWAXQrGI7RJA/8D/Cg/4BrvhV8rmSYZJH8nMJxkQPxOQJzHG7Ap86Qa5z3Fyz1mbQOM+bBrPl+Uqz7pO2Kq11PZqpVJR1hDl8/IHKpOMnwN2PcXlR9UKfw1TT5GuYGfJ2DTF/e51p9I+U8k+1vE2UY4QrioivZvIOU/0aV/QhfRFhXTGfV5SxgW5dH+d4g54IC5hfcfAeGvOsIc8zF4OWzr/I2/o+gSge/TBZ5kkPqdIKilhmiXgvlIctIg5AA/2p5pjVu6OqillGiXnHlEclI35PoXpWS1TEvp97OZsCh74l8paXebor8FjdEGPwYN0cq0u6QsqUaT6sjrodHK4GoD8JY1eI0bUd3YUkq5S84yYjSpi1zW+XqUo8xYg7GmeBzIM6b+MTg00VSwB07waj/aIAcdYmgpKAOPLcCEsmNj1+ZDXy/OQPGXl6PmajD23uFu5J6Z0UI/fQ+K2iC84zXfaca+6xldTe7hTZimMMo=
*/