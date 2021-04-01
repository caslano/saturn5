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
O/M38BSuhqVaFNl7CiuWAKH2MBQkocYOw13awyd1RkY8sicJIci/ijHOUoM4GjjPSdliokODAjh7CelIUC3mjeSfzQpj3wkBOMt7HyrcaZc7PqRapV6bXJzoCFtO4G2hXusE4fOlCBW54yOQrZKZveg7gEkIKWT76yOyzx6YhSOzGhKG8wO6/nBZlODtXOJGpc5m2enp+eNWwXSQH+savD465QvUF+MFh7fnO491lDBYPLEF75NHzpkPajVUIw7MXM+UYwaFcpW1NrjDWo+YPmLnU88dUKgXYQ6gyfpodhz/1/IeoHE+x7/yoo2pCX7stD5qknh+kXcAh7L1v3FiRg0XEfahcZQC3Kq9Vqt4CiBsMwu2gzAweAL/im7JfyXjVUcgD1Cr/uQ+LM5HQ38QUJU++zodA2RhHDW9iOQlX4rgnPBUo3seppLUGcFLdcGN+pZ1/3p5Ds0Br/0NeEaRm+azvelKiI0CXwj+eHsMw4FT0lqWXXk6MEOrfocrpHj0ddN7p6MxVeqLxzi6mriiNgQLUmyLxk7XLGMh84L7OEYLraa4nLcPtY0Big==
*/