//
// ip/basic_resolver_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_ITERATOR_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <string>
#include <vector>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_resolver_entry.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_utils.hpp>
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// An iterator over the entries produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_iterator class template is used to define
 * iterators over the results returned by a resolver.
 *
 * The iterator's value_type, obtained when the iterator is dereferenced, is:
 * @code const basic_resolver_entry<InternetProtocol> @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_iterator
{
public:
  /// The type used for the distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of the value pointed to by the iterator.
  typedef basic_resolver_entry<InternetProtocol> value_type;

  /// The type of the result of applying operator->() to the iterator.
  typedef const basic_resolver_entry<InternetProtocol>* pointer;

  /// The type of the result of applying operator*() to the iterator.
  typedef const basic_resolver_entry<InternetProtocol>& reference;

  /// The iterator category.
  typedef std::forward_iterator_tag iterator_category;

  /// Default constructor creates an end iterator.
  basic_resolver_iterator()
    : index_(0)
  {
  }

  /// Copy constructor.
  basic_resolver_iterator(const basic_resolver_iterator& other)
    : values_(other.values_),
      index_(other.index_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move constructor.
  basic_resolver_iterator(basic_resolver_iterator&& other)
    : values_(BOOST_ASIO_MOVE_CAST(values_ptr_type)(other.values_)),
      index_(other.index_)
  {
    other.index_ = 0;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Assignment operator.
  basic_resolver_iterator& operator=(const basic_resolver_iterator& other)
  {
    values_ = other.values_;
    index_ = other.index_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-assignment operator.
  basic_resolver_iterator& operator=(basic_resolver_iterator&& other)
  {
    if (this != &other)
    {
      values_ = BOOST_ASIO_MOVE_CAST(values_ptr_type)(other.values_);
      index_ = other.index_;
      other.index_ = 0;
    }

    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Dereference an iterator.
  const basic_resolver_entry<InternetProtocol>& operator*() const
  {
    return dereference();
  }

  /// Dereference an iterator.
  const basic_resolver_entry<InternetProtocol>* operator->() const
  {
    return &dereference();
  }

  /// Increment operator (prefix).
  basic_resolver_iterator& operator++()
  {
    increment();
    return *this;
  }

  /// Increment operator (postfix).
  basic_resolver_iterator operator++(int)
  {
    basic_resolver_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  /// Test two iterators for equality.
  friend bool operator==(const basic_resolver_iterator& a,
      const basic_resolver_iterator& b)
  {
    return a.equal(b);
  }

  /// Test two iterators for inequality.
  friend bool operator!=(const basic_resolver_iterator& a,
      const basic_resolver_iterator& b)
  {
    return !a.equal(b);
  }

protected:
  void increment()
  {
    if (++index_ == values_->size())
    {
      // Reset state to match a default constructed end iterator.
      values_.reset();
      index_ = 0;
    }
  }

  bool equal(const basic_resolver_iterator& other) const
  {
    if (!values_ && !other.values_)
      return true;
    if (values_ != other.values_)
      return false;
    return index_ == other.index_;
  }

  const basic_resolver_entry<InternetProtocol>& dereference() const
  {
    return (*values_)[index_];
  }

  typedef std::vector<basic_resolver_entry<InternetProtocol> > values_type;
  typedef boost::asio::detail::shared_ptr<values_type> values_ptr_type;
  values_ptr_type values_;
  std::size_t index_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_ITERATOR_HPP

/* basic_resolver_iterator.hpp
P8rtaNvW906a/T1cqe8hR5R9l2U4dbbSPF/GorO1FeevXl6xyNUHarbpDr7YupP4Ak8fSOI9fSCJj+UDkebEfaDmU+gDzQvr3u/0gVabfoC77k3Vu+mc9DH9IOJj+kHE998Pau6HHyR9CYV22t4ayn/QWX67L+TUATwxfQji++8L2cvo7dc95VKec083XxiO8tj8oR32spA+ZlmI778/tMO7LPbvGQxxluU8ylLkLIvTJ3KWCb6Y/QLxfb/3ihb33yfa0U+fSJ9nPdSpjwvQRzC2PvCLXPUBX2y/KBiHPoKL++8X7einXyTfg0AB7vZR7dSHu2/k1Am8sX2j6jh0Ur24/77Rjn76RmEb6XLRyXpzTOutE/GPXG0Evv77R1IWW3/7bJZTvg3I1xVDPnwkV9m6Yrdn4mP6SMTH9JGI77+PtOMk+Ujhfn1FtlNvG9FbT0Rvrr7RCwG7znpi64z4mL4R8TF9I+L79o16Fp+4b/RC4NT5RjNE54tynL7RRaZvYNe5qXI3XZMupk9EfEyfiPj++0QvBI7fJwrPp/hznbZWYJ6xs0SX2+4LOctO2pj+A/H994VsZXOWQ9dfr0s5JlKOskg5bD7QoagylMUuA/H994EOBeLz554d7ixDDmWocpRB+z5uZSF9zHZPfN/vtaol/fd9DgX65/uE9XAwz6mHanNc7a4HfB5XPZA+ts/TEoceWpb03+c5FOifzzM/7APmu9vDHrsenL6OUxfwxPZ19sShiz1L+u/rHAr0z9cJ28SuAqcu/mqe2+rUhfg4rjZB+v77OFIGW//54AinXFfNoj9ykQvfxlWm3tjtlfiYvg3xMX0b4vvv2xwKnBzf5ijYmzhvr9/n7bmfY3fqz+G7+2xV3i+8fsbO/b69Q248/N3uN2Zs8jpv7//vXD29z21R5Bym7qh9bvNkf80ZYCZ4JpgtYb3fWPjHC791f93Zwh8Ei8AFYDjfbuErcMm3VPjKwABYDuZIWO/fjcE/RfinCv804Ses+Y/E4C8Q/hHCP1L4CWv+zApv/iLhHyP8Y4WfsOYvi8E/XvgnCP9E4Ses+ati8OcIf67wDxf+XAt/Swz+mcI/S/hnCz9hzb8nBv/twv8J4e8SfsKR8xQqvO3mo8J/g9jNjZZ8D8bI90PCd73ku0fyJaz5jcXe/O8X/muF/zrhJ6z5i2LwXyb8lwv/O4WfsOYPxuB/j/B3Cv+VJr+EdXuNwb9L+HcL/9XCT1jzd8bgbxf+DuG/RPgJa/6uGPw3Cf/Nwn+L8BPW/D0x+JuEv1n4dwg/4ci+58XedrNF+GvFbuqs7XWJd74XCd8mybcazJGwbq8x+C8U/g3C/zbh32BtrzH4lwr/MuFfLvzLrO01Bv8q4V8t/FXCv9raXmPwnyv864T/fOFfZ+2vY/AvEv4K4V8s/BXW/joGf73wNwj/O0x+CVenGse1dzHlbsf+RevexZO+b1H2LLrtV/yP3KsYvUdR9if+V+xNPN59iSe6HzFqL2Kf+xCj9iCesv2H8e49tOw7dNtzeFL2Gr5V+wyj9hj+2/cXRu8tlH2FXnsK49pP2A2F9xEWs+etEqqHPgDth56G3oAmpaUYVVA7dBvUA70E+QekGHOgWugGqAd6CUpPZ18etAiqhnZB90C90NH0xN66xJW4ElfiOpXXW7f+v7X1ZKz/H2X4A2eeHhqMJxtqOritvXWT+cEm8xPfKn7JZMaze23xrcjW3EQCc//ARMv+gUaffGRF5pvnm/KZTn5o3XDF2rV8/LumdlP4SQgj30HZEEgGH+Upjynqew44PG9b7/Oafzz++VP3eTqv+USv+TjvecafqfnKXx9c9eH9y1t/9/IT9Uk=
*/