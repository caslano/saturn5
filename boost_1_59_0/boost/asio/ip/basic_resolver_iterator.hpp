//
// ip/basic_resolver_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/