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
pwdwTgTbeTpQHMdiXDcOA88Ycr0wnlTmzt04ku08HIF4fXlFBPM2juF5G+KMLoy9gzuSx7TreHy+0htSxri6xxnKY+QTlfHhlPSDjw+nYl3GMTx3gZ/tr8mg55FMPk8dsx6HMeswj4kRj1yFW/4ibdmFhWUyg/k53jwTLtJobY2If6rj+RnF913p/iqkWfoRxeyluRP7kfNZDqf7K/iexrdlPtH7J+eTXMb4ZMwrYP+Y0+A9gyZjgN/ZHb9nfDTfR33+EH/dy59o4G9ZR7feFbH/691CTrbVOzn34EIOo1Nj80nmefMOZvpzR7z8EvK5vhx5gjIskOVF6RayUp/LaePym47y24fyOxZzDhbDBvmJLD82QHKKsK8kP4vSn4T0P5biup+WB0nj3PBbyXppzQM9rsXJAshBXLMQ17pxflwbaoKx9cvqvb7sDumZ3ru7+zABvBwS67Sec+eidKF2WjxzRbQmzK++y3HnKL2R6tahiL9G6y3mbQ+tCI3Bu+z5TQUn5Bw3XtTJ1lQP+9C8llJKZ3N6bqd0yqdNxW2Gt5nfZlibWcnN2qZ2tuQ7z2GZTfKObttECRtOjczvaWD6WXIvkHuO3PPkWpCfweSGkBtFroLciyT/A7kO5K93r59WhsM53q0OuuYrleaeNDDXGVQdqaawKAy0N5RfVC8jWpuyvaXwfAzay/nkbu5M7fUEznNuacvDYTQpFJa/1o2DRnvi8Udw+xHmuV6Ex+IuhdvIfsr6tUsp817rKOrGXHta5qdwGU/meOdTueF9w5o1Clu8sxwuPY9leB6nbzLSt6UV5mMhfQtRj6/V01dVHouLNGK+0w7Kl9xW9LdbLwZQdeja3Yx/MC9QVo9y2N0byQtRjxpJf6aRfp5D9BCHy3VOT2Mb4akV3pskdx4YPbffRJlG0krEiX2Vot+0932enz6MZwicfFI+4B0by/hXzkj6/2xqV9Efwl+qN6eNfifgSVQn0R+czJybnLlUj5F3bulVRbhfmsXlO505H6JPcXEOxp/f9iCe04PK6Hwqn/taU/huGW28vc1wKqa+lBd6f4G8JpkbnNsJlJGsO13L6Xq4e/2JfcpLHIdWB+1TMEdR7ef9OYoZLOO8Neo25weX9wJ+Do25TRP3F8t7rd3cSv9z/5JE6cH1g6HUVk9Syj9eXxVoN0WZg3cqzcIc78/tvJtlXZW+mlRoVRdgvAeHUUth/Izvz0oqcZrzM1LF/FYKQfTtlzGelTST0KmhYzmcVf6zhwkdgP7681ShA7T218vWMbaQuZjLiPm0F/P9yUnzKTda85xW1kEIz07JJzzNj2eI69dG/357kpyzWh/hcwCh05zDeCSphP7f2ay10HXo7884XgO894Z+eG9Qt79mfx2SUv16G6+u43deznW9aIqIf0+nhV+fX57syo7FvZ9+fs7lPPJY2xDHc/KI35r5Xzfj+t+G6n871P/RXvW313+P/77H33gNPDTO79we/E1XML99G+i64Kvc7cTt6XJPPSu5eVJvYnfv4vWhvUjeG++afLf5S8TXodUyifG9KJNpnCfBspBtCB+DzuHQI7Q4veTF/9Tsg8a/eQdwT5vH3P4HyZtxHv/UjxvNy3kkc1/RXdT3j6E/+pCfvnD9yN2TwvlCbRMcy+Tf1YT1xrWr1k7Jb9BUvJcXcj0sozdz/CG1aQPQpt3I/gYntaI55ic6nztrQtc5/Zpd5zzdrJDbuZmNzndtK+bNT6MwoIP8aqrQQXLzxk5wILtGysZ7snwpO9KTzZGysZ7s6ym+bIwn+7OUpXuyjb5sjP/clVLmP/dIKfOf+/BkX8bhtSfZrb5sEt9f7N9P5PtN/v0Evq/176k=
*/