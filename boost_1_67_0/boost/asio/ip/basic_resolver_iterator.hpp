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
+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
*/