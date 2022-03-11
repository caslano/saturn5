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
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
*/