//
// detail/call_stack.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CALL_STACK_HPP
#define BOOST_ASIO_DETAIL_CALL_STACK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/tss_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to determine whether or not the current thread is inside an
// invocation of io_context::run() for a specified io_context object.
template <typename Key, typename Value = unsigned char>
class call_stack
{
public:
  // Context class automatically pushes the key/value pair on to the stack.
  class context
    : private noncopyable
  {
  public:
    // Push the key on to the stack.
    explicit context(Key* k)
      : key_(k),
        next_(call_stack<Key, Value>::top_)
    {
      value_ = reinterpret_cast<unsigned char*>(this);
      call_stack<Key, Value>::top_ = this;
    }

    // Push the key/value pair on to the stack.
    context(Key* k, Value& v)
      : key_(k),
        value_(&v),
        next_(call_stack<Key, Value>::top_)
    {
      call_stack<Key, Value>::top_ = this;
    }

    // Pop the key/value pair from the stack.
    ~context()
    {
      call_stack<Key, Value>::top_ = next_;
    }

    // Find the next context with the same key.
    Value* next_by_key() const
    {
      context* elem = next_;
      while (elem)
      {
        if (elem->key_ == key_)
          return elem->value_;
        elem = elem->next_;
      }
      return 0;
    }

  private:
    friend class call_stack<Key, Value>;

    // The key associated with the context.
    Key* key_;

    // The value associated with the context.
    Value* value_;

    // The next element in the stack.
    context* next_;
  };

  friend class context;

  // Determine whether the specified owner is on the stack. Returns address of
  // key if present, 0 otherwise.
  static Value* contains(Key* k)
  {
    context* elem = top_;
    while (elem)
    {
      if (elem->key_ == k)
        return elem->value_;
      elem = elem->next_;
    }
    return 0;
  }

  // Obtain the value at the top of the stack.
  static Value* top()
  {
    context* elem = top_;
    return elem ? elem->value_ : 0;
  }

private:
  // The top of the stack of calls for the current thread.
  static tss_ptr<context> top_;
};

template <typename Key, typename Value>
tss_ptr<typename call_stack<Key, Value>::context>
call_stack<Key, Value>::top_;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CALL_STACK_HPP

/* call_stack.hpp
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
*/