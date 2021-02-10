//
// detail/recycling_allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_RECYCLING_ALLOCATOR_HPP
#define BOOST_ASIO_DETAIL_RECYCLING_ALLOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/thread_context.hpp>
#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T, typename Purpose = thread_info_base::default_tag>
class recycling_allocator
{
public:
  typedef T value_type;

  template <typename U>
  struct rebind
  {
    typedef recycling_allocator<U, Purpose> other;
  };

  recycling_allocator()
  {
  }

  template <typename U>
  recycling_allocator(const recycling_allocator<U, Purpose>&)
  {
  }

  T* allocate(std::size_t n)
  {
    typedef thread_context::thread_call_stack call_stack;
    void* p = thread_info_base::allocate(Purpose(),
        call_stack::top(), sizeof(T) * n);
    return static_cast<T*>(p);
  }

  void deallocate(T* p, std::size_t n)
  {
    typedef thread_context::thread_call_stack call_stack;
    thread_info_base::deallocate(Purpose(),
        call_stack::top(), p, sizeof(T) * n);
  }
};

template <typename Purpose>
class recycling_allocator<void, Purpose>
{
public:
  typedef void value_type;

  template <typename U>
  struct rebind
  {
    typedef recycling_allocator<U, Purpose> other;
  };

  recycling_allocator()
  {
  }

  template <typename U>
  recycling_allocator(const recycling_allocator<U, Purpose>&)
  {
  }
};

template <typename Allocator, typename Purpose>
struct get_recycling_allocator
{
  typedef Allocator type;
  static type get(const Allocator& a) { return a; }
};

template <typename T, typename Purpose>
struct get_recycling_allocator<std::allocator<T>, Purpose>
{
  typedef recycling_allocator<T, Purpose> type;
  static type get(const std::allocator<T>&) { return type(); }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_RECYCLING_ALLOCATOR_HPP

/* recycling_allocator.hpp
BG1JeiG3ktbKmrkSRKX1HgEVPwtRFV1ACclBa/F5ZHUvGzi3pmXvtK4abDpi+F09IcPBaxHiI6EapCug87x5c5m+X5UM71UX7+oaP8uIkCDfRfgfi3oQj504gBrvsKGYnA7JDf3Jdw5IP2Uc21wXnDKGeb2huNRIjdAMgaI0i5ZxJrIVeayyXe42LKnB3eFJMeUtMwj/C1FCgdAgUaEuDg/mIRcABkn2Aqc5U2xOxHHypJC804RjSUDc0m+N4owKA9aVlcpO027WOCNev19IGHCN/YmnB1dxtWtJtIWHvOP4Rz1ahlOl0/i2CWjiP5rhADd8QHaGiP3zUWelIY2IsRNeOG71uWMLJU/2vrPawKbsRHEgAj6dBFga3BfrXIhOkHbd0l1gOWzQTaL0LQxLO7Sz2CujiPLAj92ZephCvWgKbXWxWjIgkWRc9aMiSpFZ/w7xn2vbkm31XJosWTwbOC6Vmmb4AaJea3ismiuYSdxVVqzTKhOg03O3LYvgauuKBlXZoaGqKxWofg1PhxwRNkCXJ9Os9yzpr0w6SeAD19ZAHQOQCFHjrqcxus+0KkEWsHmTFv9V04xcUUJOCD7XsduIGGSz55DWNyzJAZVhHw5bSPT7h92hz7nhA0L+/Bpo0iz/jweKIaO5Jwy6
*/