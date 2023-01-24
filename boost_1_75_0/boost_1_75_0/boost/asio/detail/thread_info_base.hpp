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
9xUlFq1ZcR80eSzCm7NqZenasrXFfHhtC4Q1/Cpo9pxV95WuKN3EqYoqKz22cVz+SK63vXjA7j9nl89WfsHBWsl0akCj7cVP7f4v7HID3pzMmZq8XP6AY+GBnGJqoiEWud5PLKMwo/8LCwbSIl/xWyrP0WSnvNzCAY3yUdsrH8VXfk2LOzug0f9NvOmzZQMaUUNdoLk9eBdLkWtH1suHAB6TH35aLSOP+pstJr//X/H0tnd2/4dtnx9q9Z+DCJD/RhU+gzd/oEyXpqSXW4RYIkTpi/onmpmiCyWaqtMQlx+K28jihrup0lEYmu7gB5H0UPxCGk/Fq/Ty2PUt6eXx/Nl0x/oA3meq5MUz0w6TEJvtcJSdDLSC5HQ8HIxvIvWi+vYE43go7sLZXsD4eyj+2NkfAgNE67x4di5LA+V44EsA5ai6KeZEA/CPazTxSM6zIhBujzcjX/zizpTD5I6YSwo60rfIl/Fy9cMkKvqS0qe+zyfUxKRbKQeuX8pxS49Svu5RCkjY6QWIlk8i9Ka1f0abvg7I0V6FKt23QnGfsrhct6oSTi+IXR+RXhAPqZ4MpXqNpRqXPnx9XHi3DAZczHAMLw3QVYfFTV7/JxVXlSi5fumyHhA5Q+UVsvJ4HaKxobhZLM7TC0SmUKoRLFUqQDS4Zw9pUH2tQTX8WqjCV0peBVdAv/YFVSdY1hKLOcZO5hOqVt9NVN2KN3Te
*/