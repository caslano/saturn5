//
// detail/thread_info_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP
#define BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <climits>
#include <cstddef>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_info_base
  : private noncopyable
{
public:
  struct default_tag
  {
    enum { mem_index = 0 };
  };

  struct awaitable_frame_tag
  {
    enum { mem_index = 1 };
  };

  struct executor_function_tag
  {
    enum { mem_index = 2 };
  };

  thread_info_base()
  {
    for (int i = 0; i < max_mem_index; ++i)
      reusable_memory_[i] = 0;
  }

  ~thread_info_base()
  {
    for (int i = 0; i < max_mem_index; ++i)
      ::operator delete(reusable_memory_[i]);
  }

  static void* allocate(thread_info_base* this_thread, std::size_t size)
  {
    return allocate(default_tag(), this_thread, size);
  }

  static void deallocate(thread_info_base* this_thread,
      void* pointer, std::size_t size)
  {
    deallocate(default_tag(), this_thread, pointer, size);
  }

  template <typename Purpose>
  static void* allocate(Purpose, thread_info_base* this_thread,
      std::size_t size)
  {
    std::size_t chunks = (size + chunk_size - 1) / chunk_size;

    if (this_thread && this_thread->reusable_memory_[Purpose::mem_index])
    {
      void* const pointer = this_thread->reusable_memory_[Purpose::mem_index];
      this_thread->reusable_memory_[Purpose::mem_index] = 0;

      unsigned char* const mem = static_cast<unsigned char*>(pointer);
      if (static_cast<std::size_t>(mem[0]) >= chunks)
      {
        mem[size] = mem[0];
        return pointer;
      }

      ::operator delete(pointer);
    }

    void* const pointer = ::operator new(chunks * chunk_size + 1);
    unsigned char* const mem = static_cast<unsigned char*>(pointer);
    mem[size] = (chunks <= UCHAR_MAX) ? static_cast<unsigned char>(chunks) : 0;
    return pointer;
  }

  template <typename Purpose>
  static void deallocate(Purpose, thread_info_base* this_thread,
      void* pointer, std::size_t size)
  {
    if (size <= chunk_size * UCHAR_MAX)
    {
      if (this_thread && this_thread->reusable_memory_[Purpose::mem_index] == 0)
      {
        unsigned char* const mem = static_cast<unsigned char*>(pointer);
        mem[0] = mem[size];
        this_thread->reusable_memory_[Purpose::mem_index] = pointer;
        return;
      }
    }

    ::operator delete(pointer);
  }

private:
  enum { chunk_size = 4 };
  enum { max_mem_index = 3 };
  void* reusable_memory_[max_mem_index];
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP

/* thread_info_base.hpp
+yt0bKEJGwwGuY0etkFZy1J2d2I1FXXlzHLC8veTE8Z6Gewi5Ce/p/e0C9xV0GJMhSSbBjGHGFJog5cKjrvaPDmHroLH8uG+vDMv6PsKPjDSaYJ0RlhIEE7LC+OIcZajE7U2odlq6UKcKkheTFEU5ojeC7RD9JACjP/XgmaCQYi7PDfbm0G9MN/xc0BJsLIXW8J+Wx+yZu+Vss5hAL8SslDg0pjXvIZ0XZ8UAO2QbePRgWV360CQnSgIxKP15GCFZVeqVk8R3dpElD6w4AZocf4DgAxdp35EUZv+CnW2Ag0iK20MF3QbEyJw+FVRqvU+G4zYIo36ZdaaL5c1sv2TJS+a6pgj0XzeiJz8BIG10LX3eFVA4xHP9H2PXNe7DTzzkG+TU7/VNTS2veTEpfkGUEsDBAoAAAAIAC1nSlLzUK4q6wAAAE4BAAApAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvY2VydC10eXBlLmRVVAUAAbZIJGA1jtFKw0AQRd/3K+6jQpKij0EEaYMKVYLtD6ybabI43Q07k5b49W4afJiXO3fOmX0MfQ1HSUudRzJtihpdZKlx3B/MS8rbp2XzbN6IxxrbXPUn76wSlhx3u+Zr0zYfm+bz9d4ciErLElcmfmhe
*/