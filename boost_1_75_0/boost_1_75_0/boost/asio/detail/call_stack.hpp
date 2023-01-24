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
pJr9bueHOcl+unVb0h7uJCUOlpecBW7oTR+ydf4xrnPzrimGYeeLphi01xcmF5O6ZMp4jU7y9WqV6wbXa3WH9bpmB12vVAWKI6/NUpdQyUhFE2Zu7N7EEyx8gxUuRI3JSDIjOE6MGLo7W3QYcEA/gK5WD8yy4mMkFzTR76nnQtAVS1KCnTlHUu1uDdRAM5VJyW+Ti1P07OeXpM+riBK2ld2dnJ+JTfHCD18ForPgBg6U2Z9mKh262jFcKA8j7EihnWYP9r0CPM4CRu1b55inrxM299drNELipUdl3HXF57Z/TPHmSpf1xe6BgGqpyCpsL2KfqdDEshGUJoblFaiuE3KsnTahl8AYMDMyGToTvR5M2fNaYzXJQdPGBJ36aMuoemxOSIG2SUaXJdO76myMpkDN30oPiJLYj2ikLNUdt32KOtI4ugRw+1tZAndnKcMtHE6HmwFSMg1PsOHVW3Qua1AtssiKEIrPWEUtKilIxe2GhCyVLuLQvc8RM3yoVBRgUq5/RJWebnTOjMcFJa4x4s1oJnGNwUHzaVLc7mqh8yzqlUnGiOPUNP5twPN7yQFMt4s9frRKWSJdzfPmT9mdgPQmwnTKXNoYtmzkFGWUeNsTddLIcxsbRHQVneHYC6cg79q3dBZyO7VBOit+qyDMQq8vDxYHp4k1HtpVKW0brpTCdD29E6arcCxMVxOgEdehSVmH8WTbzSq+Dw5j
*/