//
// detail/thread_info_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP
#define BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <climits>
#include <cstddef>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
# include <exception>
# include <boost/asio/multiple_exceptions.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       // && !defined(BOOST_ASIO_NO_EXCEPTIONS)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#ifndef BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE
# define BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE 2
#endif // BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE

class thread_info_base
  : private noncopyable
{
public:
  struct default_tag
  {
    enum
    {
      cache_size = BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE,
      begin_mem_index = 0,
      end_mem_index = cache_size
    };
  };

  struct awaitable_frame_tag
  {
    enum
    {
      cache_size = BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE,
      begin_mem_index = default_tag::end_mem_index,
      end_mem_index = begin_mem_index + cache_size
    };
  };

  struct executor_function_tag
  {
    enum
    {
      cache_size = BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE,
      begin_mem_index = awaitable_frame_tag::end_mem_index,
      end_mem_index = begin_mem_index + cache_size
    };
  };

  struct cancellation_signal_tag
  {
    enum
    {
      cache_size = BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE,
      begin_mem_index = executor_function_tag::end_mem_index,
      end_mem_index = begin_mem_index + cache_size
    };
  };

  struct parallel_group_tag
  {
    enum
    {
      cache_size = BOOST_ASIO_RECYCLING_ALLOCATOR_CACHE_SIZE,
      begin_mem_index = cancellation_signal_tag::end_mem_index,
      end_mem_index = begin_mem_index + cache_size
    };
  };

  enum { max_mem_index = parallel_group_tag::end_mem_index };

  thread_info_base()
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
    : has_pending_exception_(0)
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       // && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  {
    for (int i = 0; i < max_mem_index; ++i)
      reusable_memory_[i] = 0;
  }

  ~thread_info_base()
  {
    for (int i = 0; i < max_mem_index; ++i)
    {
      // The following test for non-null pointers is technically redundant, but
      // it is significantly faster when using a tight io_context::poll() loop
      // in latency sensitive applications.
      if (reusable_memory_[i])
        aligned_delete(reusable_memory_[i]);
    }
  }

  static void* allocate(thread_info_base* this_thread,
      std::size_t size, std::size_t align = BOOST_ASIO_DEFAULT_ALIGN)
  {
    return allocate(default_tag(), this_thread, size, align);
  }

  static void deallocate(thread_info_base* this_thread,
      void* pointer, std::size_t size)
  {
    deallocate(default_tag(), this_thread, pointer, size);
  }

  template <typename Purpose>
  static void* allocate(Purpose, thread_info_base* this_thread,
      std::size_t size, std::size_t align = BOOST_ASIO_DEFAULT_ALIGN)
  {
    std::size_t chunks = (size + chunk_size - 1) / chunk_size;

    if (this_thread)
    {
      for (int mem_index = Purpose::begin_mem_index;
          mem_index < Purpose::end_mem_index; ++mem_index)
      {
        if (this_thread->reusable_memory_[mem_index])
        {
          void* const pointer = this_thread->reusable_memory_[mem_index];
          unsigned char* const mem = static_cast<unsigned char*>(pointer);
          if (static_cast<std::size_t>(mem[0]) >= chunks
              && reinterpret_cast<std::size_t>(pointer) % align == 0)
          {
            this_thread->reusable_memory_[mem_index] = 0;
            mem[size] = mem[0];
            return pointer;
          }
        }
      }

      for (int mem_index = Purpose::begin_mem_index;
          mem_index < Purpose::end_mem_index; ++mem_index)
      {
        if (this_thread->reusable_memory_[mem_index])
        {
          void* const pointer = this_thread->reusable_memory_[mem_index];
          this_thread->reusable_memory_[mem_index] = 0;
          aligned_delete(pointer);
          break;
        }
      }
    }

    void* const pointer = aligned_new(align, chunks * chunk_size + 1);
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
      if (this_thread)
      {
        for (int mem_index = Purpose::begin_mem_index;
            mem_index < Purpose::end_mem_index; ++mem_index)
        {
          if (this_thread->reusable_memory_[mem_index] == 0)
          {
            unsigned char* const mem = static_cast<unsigned char*>(pointer);
            mem[0] = mem[size];
            this_thread->reusable_memory_[mem_index] = pointer;
            return;
          }
        }
      }
    }

    aligned_delete(pointer);
  }

  void capture_current_exception()
  {
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
    switch (has_pending_exception_)
    {
    case 0:
      has_pending_exception_ = 1;
      pending_exception_ = std::current_exception();
      break;
    case 1:
      has_pending_exception_ = 2;
      pending_exception_ =
        std::make_exception_ptr<multiple_exceptions>(
            multiple_exceptions(pending_exception_));
      break;
    default:
      break;
    }
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       // && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

  void rethrow_pending_exception()
  {
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
    if (has_pending_exception_ > 0)
    {
      has_pending_exception_ = 0;
      std::exception_ptr ex(
          BOOST_ASIO_MOVE_CAST(std::exception_ptr)(
            pending_exception_));
      std::rethrow_exception(ex);
    }
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       // && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

private:
#if defined(BOOST_ASIO_HAS_IO_URING)
  enum { chunk_size = 8 };
#else // defined(BOOST_ASIO_HAS_IO_URING)
  enum { chunk_size = 4 };
#endif // defined(BOOST_ASIO_HAS_IO_URING)
  void* reusable_memory_[max_mem_index];

#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR) \
  && !defined(BOOST_ASIO_NO_EXCEPTIONS)
  int has_pending_exception_;
  std::exception_ptr pending_exception_;
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
       // && !defined(BOOST_ASIO_NO_EXCEPTIONS)
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_INFO_BASE_HPP

/* thread_info_base.hpp
8fWeaZ+OAifJC0xDafPd0JqBdm4FPcf2H66FbuGQzkdgBU2L+931eNOaPlkj/hGjTX0R2H9a76eCc9b56uNXL02sGbyGFdaWEEpKXTP6TAEbFAlheYwkMmxrYvZFy7tOwhn7869HaWWjm5pc0MwVRnMZsDCJJ/Q5zHI7FNghkdC1zyyQwUnRfJ2htjrzO7o4cxMlNBISHBY4M0LyXgrSWEt25HAySY54xGp9qK/fwnwoA64IaJHnI8AvyfSbkBV7SsXLBMechDNbgImvpCHapZUce1vCDaoLSQ73UIrOULRpbuVdXQSyiWcZz3X1UeqLMPbODV9xglcVP+aUjUp9WXeiexAuxFQ9rqq+zx5CBIOD+9memr9xKQqVHVOEOu0OT7tqUKDobGdIuzm/Q++MqNcAbja3m8FVH/sffBIhI/DZGJ9oWSCUUnY6P9kMbiszLy7vb7ddowsaw7cSI1LvbSvMsqSRg+9cn9isMZR2I9gOfDNTIuzdduIDTz4FI2sDlW6lnjv1SvYYM96HxTaGwPcLEWsDUjp8IJWwVpix9U7HGb1aREb7BfGYOpABZKY1I13cX9svel80q7Gmp+WanH23opjYt+X7bB33LT8uFuJ0zznTWAuvSY92usoU653oX5WYmXc6VYgmqxNnYBZ0zSsU0CAEpcqKcntFF1Y2EoVqiT7Jao/9CViKduH0ITi6jSRGwjrp7w0v3r/qMvNXpo5uCxKmBiGi4AneZ/Hl74Gkk2eaq2eNnv92OBvy8mOrW0frEf3yaJhv6NdfqJbWLWeBjYm/Gqvan4XbK2lrO2EBhcooNg3tSMvdDFMIk6EkywRn891aObotvDOcS8UTyKqyr/Got0Ywi+BklObjxpgb1SuqX6WwvfOVtB6dsVgQjR+Pwsv2+tea2nisrlx0DTtueZR6vl70gVA47Ty1N94WJzWPUgXM7OgXVQ9Og9kDpdV5orm7c727UvVcOi+KS+4Odi7zdLc8m3sKXSLuIaKYlpFv+GHMPD6WwbFs+LJkIZFgUXMHOPr3NFV57ncPbb5mzZWE3/Lc6RaqfbCxm6sRXZQCbVws/sVivVFnPBIObq9hQ9bM3b0reXXh1b3Xzvb6VVgvl1xvB1i6RLiCyVUgLRXEJBxlZhy550NjBKxma/Kv1YcjqROl7LlIxR5MvRJ3JsQWxiW9GrG/1cKjB+7ZUTWAMlJGZGAagaG8FbpjuqBx8i5CdkKIM5+pP/G999DWwyFrpH/5D41CDAgYVPI7hUHpj4SN4Gg6Gt/igCbgYmnSWdtx3ftl6cs0Ngh1cbHvs5pZDMyNQlB2Hpi3hsmLkb38d1rL0E1mgXuJjLE5H0gd89TDm/01/8wGQxBKREXxOVups47ZoKQX+ZkgiEeh2FOK29Uf6UoiWSOTf3ur/EuJF27yoaiIqIV8aMLhhwPGCeZGqMf0ZomQ85r8o8M9gqs3SHqyQs/jQfnAD787I5ucRMvQtYxDpPeTkpIMUcmbQlwfjU0K23nbCW4C1hEaH7uwdVr97tNbP+NBUoFA1vG3+8go+2IMEvsr4dTlRslbz71ERxECOcOv/R9vzFpPajT5+eT6sCJZ9FHdpAZEGpGVmBVcRDzkPi5YL18E8syU8OiG9TTwRQrYU+fNKQ4vd335O81XInP7ISt3tv7Df3qtcx1k3S9RcilozHf2oZ+gb086UxH/Ymcv650oUC2FNmLwqJ++NePBtqmHp4OmCam/GLD7GnwJYdTzBcfq/jpaCXFz29S/dKWOP6X/GFAly9IbZYWxEV9abSe6oTCiFb46fBSsuHzgzNwNrWJs3yCQYYWJNtpP4F8EmvXdNZye0R8/4NKXV7DzDJbUvzHU3f9vT677mXwbpxC2f9zqLj2dLIeoSx/Lo7mr89ZRopL+I06UdM/MggzmQTRoc84n7mwJ5kIThdyeVapcJ3/RIjiFBcVOe8GZvxq4WWZCRk/TipZ6n67dF9dwbbVUc51M01UybKveeqbvIr+rY5Cpnr8dkP0uLpNmzvjZZKLGVnulRZiSYfQefoDL31HZpMWvdWjP9lgXN2GNDkHFd3DCjq+OMzNXbU0h1ZbUhhgx4efpimyQXRI2azkY1FvKsWwhtX84CIHIATg1TEtJaKgiC9tVle80/BgyTfV1dcscV45Qb2qLUfaImPVJIzRu9iiu7nc9cOU4UVWdPdX3LcgCT/NePf3aTsJm8C52JEinihsD1BAwEtut96VEoOjBUW8ezYoFFz9cKQ8WMMg7aQQe3vN1HHIy1RYCuuY5gi8Y/Pocc3kqaohFidyqIFjr3z2nb0tb8FEcuEmaZkjmuPXBnGR45c39p/3QdF5DobYT0tBiHayfbhPiD+pb/T/AofiCAVS9D/rcjeMf96y1BoxEtcc+zH4zAqN+18h5YnXgAhiU08TU9P9u8fD9awy3JSQt0BZMk6ytm8iaRljbU9pu2iWK7gIKisjeqyqNkbVJ5w40dlu5i34+j+pgEbrfhUnwoSaUQ0X6hREo3oRX0UHsIaFRA+KXRLt86c9K01OpML3O11xNMmABKcAWuoePSvk1NCNvxcTSb6LRE0+2OYjS9kvwMCg0UwPSn1kUtNu/yhcB0tyIHIFmbnMF0KLwK1kCUs9Z2OwF7gi9jh86UQAcSMC7GZ/RrOC5vdA+wClopEk9OSkux5e+9KEJdpaLdSHXFO9oLqUYgngr7RgVwjWZ2yA1eSza2GsNWB2JqsmT30wQwwARjVHkWTkxDACqb67FeXCkfWlTSQPL0IMFD/3uPkPewuUGlHwbyJ0XsMJ/Ln+qYi48ICZctvhgwvnhJLxcTScsf9xvcdfT2ifKUF9890ep6mepXorEvqFWjCNfb+bnyyY6c55ua0bog4hFFZiqAA1c+O2GIWKHGWl0H7CtjEdhmJ7ABbhD+8sdTFUhn3jnd6r5oHidR5/JNUs0z6kUJyQTIEtEADH3obHtbqf0QOJ+3dgR5xGC6CGhXqf7OZSM1gA+0LKiaKX8UpnkYUMoM/F3DeA4QnKTDIL4oJpDkRsrxknV8XWZRUYoHm3yXyfxsi7BBdT9EQp+rTmhqGh6yvnGuCSOrAS06KMHOuzNdXNGs8I8St0XHYrq4oe2/DjRTM/oEN8Vv8sOXl49le/2qs1knBLKdTDV64OoHWOGAtrAs1Yz0Tc9240T1hKLcoIuepWVwhGiFrtRqCC4vExSopGFODCHSStJf3aLo7RfH6lxfyCq8WH5bkuF1s8yR4dITgE1px2VL/4ZJgL6xMwof00e8v+mIYhJiG/R6PnwhZtfcyjYdeZx3GvmlpPO2mEp2Up7G1MwD44t9nCX3qEyE1XJwyn4/vO+odyhXZSDnMWD/GzcyapgCW+ebUxkiQIcvgGwTjGYK/f/fYtmlNZ/8L0F2HcVnB5H/9SliIUhbTGwoQrBnNpy1dCNOH+No1bud4s0gPxNN5wMqWhrZmKTjAnjFfbz34+Vgwi9R2oekzSDuEgkhXdB7NskenkzELUzmkxSTmJJ9MqVccST/BQogWRJ3TZLLx3ywZIHieT2KypvVTPBF5W7MWF4Ze9iYPXZf1WMGWcQGwzdyVLB8SuJg8mUPqTkhDnevN0Znk5ghp+Ngz6QmADvioGn03jpfCkGel3FZkDfqNoOM+3YLasNSkrZD6glWGMrdsIsxFi66+69TM3XtGyFB7mIshqD3MXR6JJrQpEHSkyPJLUxgJ0N7z7mOLkNRJY2jToUOyuOlyXanzacbM0Ys6qoI0gPYpfOlJwhPtfuNuRjsmIC75s38gSPzDlpS02rTNLbzYp8GZ+lkVqDhOncSKcvXVQuh6eN4UkK57fh8Tq1ijn/9WQ+kLxsOEt/1QKzXHfB2Qu74mzUUy8jl/RSL+gqxpqHPbF7OKT87WHm7Lh/HpOTwZ5ihQnCdZXXJnKlT8GEUxTinhfLrIw/AhRKWQuBXLA6uy9bI75RxKg/G46TgfO+OoSxSvXxjHEI/0rxJxR2Lx37EaE4H22zqPWRrkL0fSaE6ZuThdnsl4C89LhPbpKHSoRSuhvVHYk45nUqkzwqHL6r86DoiCbi4LWCkiKuj3RS46VjQcBif/Q/Qn6ukOTygbqenU0aXMYZzlIDD7bBuErfLpwMYik/Ej637YFmAuOBV81up3RtTusFnOfrtjUH8syHZV9OagXVEr5SE9L6IbcPIJYE1bUAq6fFA01ND+/47HTkFVE2itrjEnlbLCZS8lbe6vLHe/f5p7er2ml0xCfrKx118J9rpHVtAt4r4zm3j7fDaeFWSLgr3JKyVvqtjibMdIaHM70X1WMA//e4i6EyPjR0sPk4/+dDJMPk5cH5dOHleaHMz9pi6hv22dRihJt+j2qbfVo+A/eDXshGXl9+6lpsFfxN3yJ5fxcwv/MADOl/ojzw/E3IyohHGJoTF+53BmevvGdeblZE2UsrPutSBepfG8Pyo0Ozkkc+IjuBhmoZz0eZ8v6oUcPk7wr5Ir1vfSKDwu//btWGMW63zvHCe8SCEXJztT2kntpyVOalFgdT9MUzpKlmNXKlyBuBsm9fD4RzH71w7S7edyrnQgEZIRhPGUeabbU6/Pi0Sv1Sz50OlKjHIqosyYzPRoWxj6gsDt74Q3WYM+Y73dVbjehyQLwCzJHvKupPf59IwuKtK+dJ5X2Du57qsZAbPFrDvPcxJL1qqbrZ7UWTAiL4OOjYhu8c51BWh7j1H10UetQ7JEKoR+QsjYN84TnUxkjQoLiGzwinE6lgJEpwfcOYcMlIMEvutl5OdCNWNTtktIpn7NZK1NFFk2DvLOo8g3w+q0mfyHtevZlquTOX3Vjp/4laPSrw15J3eE5kBVulkLwvFs3Kyn0Uj1PIFeglk8t17pzvHnK5HI9XZGr/rokiXKdN9sftDffCoVXSiJg9VYJsv8jB/adUOIuSLIRVzvX2Y1F3nYkRp6g6XJ4K2b5Ql83ecXejDGN3S3fAgi6iAaaIy/XaoD0Zhq9D3sb8GPXiGwuIaHPgwGI2FucXgOwvLAHd1FUtRIV3RmJ/KpYRxtwzME/LjPYwulAkduuLV83jr+q35bXfh8N/TB7f72/QMYr3VkpN+7wSPvBst0vpqKEailhOFwb+nsg8Ttffma/LjUoIBMji0wAHvZUpG+cCqXL18n1Kw0RpHd4iUoBHe9dlCS+/IDuTOVFiIPyhRYN8DMOJSdtLu/ZvKVfHBth/MwMPlXEE+F7tHgnyvvFtmITXQhL4wyMXO/w45MXF3NwGEkiin2cNot6UMij09b96hhnyYbf4PGZLmtioY3YIYn9Wza7MvCHVa/xDe6FjCqH+IpVhLRntatYtbCF3ipHsxAep/241EuCudsoP5P6zboy1SoQ2WuxKQaDRrl2V8ZKqKF/LR/xujPSxUGoh1oW3laPZhAPX36P9eHIJKV4ZfdZoZDvcyu78L0jRUCZm8kYc/LAC4KcwLs+T0D999wBQER665CWQB9ttdkDeefenBi/kx3a7CzaA50yCx/HJs34c6DUHQu5mAojUum7P122IfOn8LZxpNF/pPn9cd/C3ZZQfdYEJWp8o6UqzPlaysjrcizHL7I7BC5kOH22AqN5BnmSORemZd2Lut+YGVt6BESZ3bat+QJMHm5FBZ8rgZM07zRwv6qIC5fKtpxczzSbD43sileoERKkpRXUeE37UL9Slw9zkkRi9751JrVYTXbFIbdd6pCs+3NoJFqmfb/iNKo7P+yXSHbALpkvLdIezvTceITer8HskQFzQ/jI4nuAfqmQtYSjDBfGI7lMa2SjL71w/8Dn4DSy+2xD9AQFTBoz1jNyHjFVFOlhDBpnGh4UTF/7EJqfWFT7HBjvWl+1WtB3AefsvnOtqQg+2Jbql7jKPiBiLpOnMIzeAxY6wGsBUVrmxfPCeEE2kLL3Ck16wR/9/uyurvUn31YPNi885YLIDscutysc+j4dt3CamQSRFXp2rYnxWECmMzTnMQqZrQ4uO3OdIyl7Pj1K3Wav0DqYE0D8L4p7h55CDLrIzN/L2WI1oj2bwFhPaj6hjJiiZH5z91BdL9xpG7zkI+70gJNDnBmitbUlBXyAmgNk5uUnV4p6iO5ph3TIp7phImrGrr83WhhNfXbnDcyIiyCLfUAg1NRleyJc+idKjAoq8uM0SVy6fUCXs225eFLk3LIwVESj35CVPvXyzpLW9vAwSAULaLWPLSa81KdN4egOkj6+4OjMh/ZtpmdlWUch4Z/25c3gNhNaLWxs/Lm7ILjslkirYSXGFMEcZh9kHJwiwVzBejHqm16rnb0Iinz4i02QSaQoXHCJIfSk4y3mAybqruYbdDfKH9ZS/8E7C07ZJPMODF+sQb6wm6UVYqGZtDasRUTOZ+x04r+PntNWPsYOScwGfEPMujlOiVqNq9+jKxPlDmX6m35mhzA8zhqxiJF2gruQOIpBQbT5snkwkonwL9IFU7BvfT9TzUSjxVIJD94CqQoIbmcsP/SdMduTN03NE/Wxml495/wAHLPjTdqrJf3JdIfVulk93drcgtZuCrpOnrG+yvb3wJSg8grI5gJ9MsTuO1javPAyx20zOMDPRNTUwsMc2mN154nCgeVtX1k9ipON6ZPGojDh4Z/CFE/ClAbtyABWZrOzYQ+R2r2ceR0ndeZi6ZOPfeha1gC80eQi+7bjyj/dbEKi2sYm6yJHRnh4p3C+07lOJBjL9b1d2daFEECuISgf9Y5l2AzVI76FcbfgIrsqhyV76YABBfiV/4+y3u8qJB5XZ6n7NRiPhz/ePt/tgR7JYT9+Ma95tPs8h4QMfUGMMvx+WcsUoH8RJYXp8tbXSf/tiJqxrJowUeQanSzKteA1a3zerDZGfxOGx2Tflq9Fib7Zb8+Wyj07rT5SpX1rtL1eSR0sRVrkZccoUWnTHL2/peYXNaYI/2nLoaYzUA/sJPxQwd4sXh153atb5Uw5MnuhnDyrsiMuj7clZcR/L72xTBOyQxEMTkZsaDZj0WVVkzb10L9ab1VORNHyFdUWsdOrtXy5aebHpU1GrJjUpy9DbrJs6OIrAf7zY/uMBYMgJAEX0IB16GNU2ykaNiHeii9V/3useHDjj/rgjPmz2tbCnz1rPldhEj9AZFbmK5dy9uNDkD5m/REFjaZ7/qFN/DzmJ56dtGppyMLmivFJVXlF3lr9muv3YyD84/kq2gZwB27nGj/zYxPl9VZDWbRva3bIRvDYMSjSahI23MuAK58hJQjZrrb957XcgbG7zMaRcaWUGub1Dc6PpObFaznaJ0PMHpgn9TrB4iQlX685Ta2hiF/NH7an+KFAbbvAWbpC+FReNczBwnzKfkk8j95iIGw5DckSYmdeL74EVpzHGTKFbwZpejatTiGKjsUUj2IM08ls6QNZJ0ySKq+OrKuaukj5hrd1ojYMldnMDW5FdgFmPg5IP1/ayCUFBUrb2W4Z3XI+Tv/dTLhxI/jliuHviH7JueVTWdlvAWoqV3Bqwzky3Af9ShyJPv9vUe62PkWMorq14beD155RiqMUZNz6vqQmWNUH719iDEf6Rw0GKNpb8UkdtwVgZqYZT5C/yWK3m5p7dMMQ+HqtFlMOIMoEbd0DvLBgeids45HNCjRydWIT0ouBLY6N/CTsqIoC0
*/