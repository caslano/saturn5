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
6Tmt2BneqWaPMXxXwMcdTxvs9zEy7zX7/udhu0Zo1OJH8ismMR70h6ebmMTPEeZZIOdPmPkWW25wUdbCWtSM65Mog8bjw+lT8bSDv9U8f7UwhqBvNbrFDUWXwcQaOv0AubaZ/Rn5jHXQ3VqH7dtoh6yNyDrYRgwhZw9Sj1nTwHM7+Z+ae6dmzoL+6/DayPnzyBqJ7f88C/+b/3m1IBtlx5txHRrvmXuTxMdO5Pwau8aC0mT6JnF05QhkKiHmkeEljofSvsdMZKJ8OvUOjKYuZXFeKWY2PqHOJrNPfhht5hMDpD8h7x0wHjn22miHXx6Ffxs6nuejPw5FVvM/Q/JvRo7IYik/ldgxcxH0d5lnG6WMDXVSX/OfniHo3kDc5LDWhOap1G3IQC90+YPZe47cPWe4lQzKwFjQAhaB74EV4Bbwc/Aw+C14GXwA9oMobtq4QQmoAhNAC1gELgI/BPeCreAF8A74BPSZ5VYqGAjGgjawFKwA68FDYCfYAw6AaJ9bKaAM1AAf+A74PvgRuB88BV4DnwLLbLcKQDVoBmeAq8Hd4AnwB7APRLS6lQj6gePBJDAbLAaXglvAvWALeB68B3pwQ88BskB/MBw0gDlgMbgArAEbwDbwOtgHItuwFSgBY0AL+A64HPwY3AueBH8En4LouW5lg+FgKmgHF4FV4KfgYfA0+BP4DETOcysdlIAa0AwWgXPBSnAn2AJeBu+CA6DvfLeSQBGoBrPAYnApuAH8DGwGL4E94HNgWYC9wETQCr4DloM14C7wKNgBdoEO8DWIWQgfkA8Gg9GgBZwFvg9WgfVgC3gNvAd6nAgvkAaGgangNHA5+DF4CLwKPgBfA9dJ0AeDQS2YAU4Bl4AfgbvAFvAK6ADhi5AJlAEPmATmg4vBSnATuAPcB54AL4E94FMQxs2eWJAOysAJoB60giXgYrAK3AruA4+BF8G74DPQ+xS3nCAbVIKxYDo4GZwPVoIbwc/Bg+BJsBO8CT4GX4CIU4lD4AZFYCRoAt8BK8Ht4FfgRbAHfAls7W7lgEowFkwDC8F5YDW4FzwFdoFPQPhp9FNQDsaCJrAQLAEXgqvAzeAOcD/4NdgJ9oADIIo/F2WASjAaTAVz/0bBXYZlsa0BGF792b1173Ms3HY3Kna32NiJnYhdqNjdYmJhi9hiJyaK3QV2Byrmec6P+998M2ve9cYaLy4xClMRip04iet4iwR4BrA3KIQqaI7uGIrJmI8N2I7zeIHvSB+YVeSGD5qiLXpgECYgBJsRiZO4jAd4jV9wA7kHvFAYNdAK3RGA0ZiPMOzHadzEc8TDMyirSIec8EFdtEVXDMIYzEAI1mA7LuARPiHRYPoR8qM8GqIthmI6VmAnTuEmXuIXkg+hPyIHiqA86qIVemEEpmA+VmELDuI8ruEBXuI7kg/NKv5GdnijAmqjOdqjOwIwGpOxEGEIRyRO4CLu4gW+I+Uw8gj54INaaIZOGILJWIoN2ItTuIo30MPpH8iCQiiPWmiMduiNwZiKVdiP83iMeCTlEJ0HZVAb3TEac7AW23AAUbiMOHzAHyQfybqRD6VQC03RBQEYizkIw26cxW28xW+kGcWzURVN0A1DMQMrsA1HEYNH+IbEo7OKf5AHldAM/TAaEzAHSxGGbTiIKMTgIV4iASqIuCMTsqMkyqMmGqAVuqIPBmIkZmEhtuAwruIV1BjWhMKogSboiBGYj3CcQSx+IcNY8hDlUANN0Rl9MATBmIv1OIJzuI5YvEMCzLisIjUyogBKoRZaYAAmYRE2Yh+icB2v8AdJgumNKIlKqAc/dMdAjMYEzEEINmAfzuAWXuA79HjiiKzIh+KoiAbojF4Yhkk=
*/