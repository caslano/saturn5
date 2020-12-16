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
CdmwBNHPnMt0u6ewFMmKp93GJaztE6Joe5a0nWvSTnNNeYfRVvG1Et7WfdS6h3dbTRgi77GQ8vIbl+UvtzhE8MQeh4g6HXGIqCc8DpGZb8WbuM+3Om85xQrFW8a6pucb+bHboUQz3wKy5XR2ynYA5RuakE1/9Yhs+zllo2yTtijkx26Lsl8UtiiBe8na1CnbizzQ1oTIpiTLLxw/amyhr4w9gmq/jc0bnV1sbEy7jVxGJpNnvpWjl4m6jEztQmUKGatqF3k2VsyXeshjTMRitxHr3MVZ54d94fSs09hh8g3p6EPKxW4jxvXc46C5tPFA9T7waKPcnF7jLOWy5BvR5V1waez3JvU55i91uL4L1m3mlMun3gVecs1iCcVbLspFsHVsQu4iW/ngb7SWyW3uW7N/4d0XL27u7Is3mA81Hn0hDynPeVjTdF+QH/szanXfyM+oeDy4DRsP7kYysNM4eYvbT/ypfv93Dh20eeolnQ6Nx4P7+C+IB3c3xKF/r65EzvFqrtv+Zz3I/P+R7X/Wksz/w23/54otyoFKD9f2/xDb/7vZ/s+z/c8eGTrrfpuAfPm/t9Lrlf8Ba3f5/wyJSZdjyd43SLN1XqLsw8vaPrq6lAU5RzqoO18v5U5Q6TDd+S7wtQc3B3cCtwD3AbPBieA24EFgV/AwcCtwNtgNPBLsDs4VPtGdl71U+lTqM7rzonu6MXi5tPMKcBhYB44ArwPHgleJruLV4AJwMXia5J8vuqaLwGvBl+X8Gkl/A5ZYsj8JXiztaAMWSzvOFbnPA7uCC8Hxkj5AdGdLwQvBgyX/XNGtXajOG9sG2ceTMSoPs224UcblJqnnZnA7sN4WG7BGyl9jOWMDPio2HU/J+DwN7gY+A44Cn5VxapT2Pifj8wJYAz4PninpReAq8GKVlvqLFF0Q2v6NwBFS/2nS/jPAbPBMkeNscBvwLLCHpLeTtNgAyB4LfSXXtdsAHCnXPQrsAh4j158r1z8F7AkeB/YFjwV3kPQ+4Dxwf7BGzU/hnwYeD84ET5R5OR883ti4wCftywisv8ueQrn4sE8CLdHJ7yE6/XlgT3AP0eUfD24P7gv2BQ8A+4FlortfDu4AzgB3BGeJ7r62cQVrRXf/anA0eDs4BrwHLAQfB4vAJ8Bi8GlwAvgKuI/o+O8L/iI69+vAA0Fl43UQ2An0gduDk8G+YB44AJwK7gJOA/cFDwYngeWg/zkj671gsstz5gGxWXoQbA02WFLOrHfSR9KfW6ty0p8fwbcF+InMk0/BHPAzcCD4OTgU/ALMA78ER4JfgcXg1+Ak8BuwBPwOnAH+KPP8J3k+/AyeKelaSV8ltmpLwd/BG8AkpaMv5R8ELdIrFIBPga3Ap8W27VlwHfg8uJGMQxvwDTAV/AhMA78G24M/gBkyLh3ABLFRSwE7yvhA0t+yHgi2c+nvXtLfvUHRHTDl1niWI1/K9ZNypMUmTda/gL5Szm6Tdpvw3w52BO+Q+/FOsLuke0na6ObL9bJcbOEOtOvmR8lXEyVfXZR8DVHyrbHxrQzjG2/jsy6Njq9rlHy5UfKVRMlXE4FvkejQN3yIjiq0Fkr/CL3VZ9ENvROdVv4fChVD1dDn96AnCy6DVkBrIOtjdD2hAVABVAEtgJZBK6H3oaRP0CeFql+ljqfQW33er7c/4hMQmgsthG6Aim+hHLjmk8j6/AWVkfX54zEf14/O/oaK9xiP9egV63H9xHmMx3hseYzHdZ/Q3k/hh0qg+dAyaCX0MZT+GX0EHQDNhRZCy6HVkPU54wIVQ3OhZVAjtA7q+gVthCq++G/rzf9Xjg2m/4/vxvWh/690+XfsZ5kYKfhQMFsRbaEMaJQ=
*/