//
// detail/call_stack.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
lnS5BS7FyP0EQ1H55rasnOrpAJWgT4/9XUvuyOw7QRr+hUl97j5vbe4vBtE3JuKr77CJb/1k/zPATXF4VgYBGpCbcux2Y0UcodxJNHRJCEHN1Vdt0UoXFtXwEsNAcZyoaxMyhJWbEVn8n7SzLw878a5J7mVMQb9WKR74WlKkapurUwg2FoR+y2E47F3p5qNASJDGwGVqQh1+aLvT+Ol8cXS1gEd03WDz9/KDOnANZpOuJYfy3azVAPp+HAXY/j6UDYiJk9lRrw1UbC6XnEE1pCfdThbz3nt0Qs3CaxFKonf6V+E/15MVX8XCjuDq2uc0+FPiluX4k5j+DEZFxkfEh5huyIkxGg/HgbleYtOQKmu2pUubEjYkFFeHm4swGQhP60RxIhQlNIFNO591y6do1G/0HZ/xcrm44YxV/20RtrMysOOXBcHGNWEq20hVlIAWm7uUxdHvYvDi4iahKhMFEeYjG4d6/vWRq5IALUW0s05s8uEfrkKE4CgNg6c2HZAjqlpFWmXm4rHHMRzT7lZDPbUrBTr/Q1tUCc4Rg3Fu8ASZliCqkY1OltxqhA==
*/