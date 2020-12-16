//
// detail/win_iocp_overlapped_ptr.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/io_context.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/io_object_executor.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/win_iocp_overlapped_op.hpp>
#include <boost/asio/detail/win_iocp_io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Wraps a handler to create an OVERLAPPED object for use with overlapped I/O.
class win_iocp_overlapped_ptr
  : private noncopyable
{
public:
  // Construct an empty win_iocp_overlapped_ptr.
  win_iocp_overlapped_ptr()
    : ptr_(0),
      iocp_service_(0)
  {
  }

  // Construct an win_iocp_overlapped_ptr to contain the specified handler.
  template <typename Executor, typename Handler>
  explicit win_iocp_overlapped_ptr(const Executor& ex,
      BOOST_ASIO_MOVE_ARG(Handler) handler)
    : ptr_(0),
      iocp_service_(0)
  {
    this->reset(ex, BOOST_ASIO_MOVE_CAST(Handler)(handler));
  }

  // Destructor automatically frees the OVERLAPPED object unless released.
  ~win_iocp_overlapped_ptr()
  {
    reset();
  }

  // Reset to empty.
  void reset()
  {
    if (ptr_)
    {
      ptr_->destroy();
      ptr_ = 0;
      iocp_service_->work_finished();
      iocp_service_ = 0;
    }
  }

  // Reset to contain the specified handler, freeing any current OVERLAPPED
  // object.
  template <typename Executor, typename Handler>
  void reset(const Executor& ex, Handler handler)
  {
    const bool native = is_same<Executor, io_context::executor_type>::value;
    win_iocp_io_context* iocp_service = this->get_iocp_service(ex);

    typedef win_iocp_overlapped_op<Handler, io_object_executor<Executor> > op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_object_executor<Executor>(ex, native));

    BOOST_ASIO_HANDLER_CREATION((ex.context(), *p.p,
          "iocp_service", iocp_service, 0, "overlapped"));

    iocp_service->work_started();
    reset();
    ptr_ = p.p;
    p.v = p.p = 0;
    iocp_service_ = iocp_service;
  }

  // Get the contained OVERLAPPED object.
  OVERLAPPED* get()
  {
    return ptr_;
  }

  // Get the contained OVERLAPPED object.
  const OVERLAPPED* get() const
  {
    return ptr_;
  }

  // Release ownership of the OVERLAPPED object.
  OVERLAPPED* release()
  {
    if (ptr_)
      iocp_service_->on_pending(ptr_);

    OVERLAPPED* tmp = ptr_;
    ptr_ = 0;
    iocp_service_ = 0;
    return tmp;
  }

  // Post completion notification for overlapped operation. Releases ownership.
  void complete(const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    if (ptr_)
    {
      iocp_service_->on_completion(ptr_, ec,
          static_cast<DWORD>(bytes_transferred));
      ptr_ = 0;
      iocp_service_ = 0;
    }
  }

private:
  template <typename Executor>
  static win_iocp_io_context* get_iocp_service(const Executor& ex)
  {
    return &use_service<win_iocp_io_context>(ex.context());
  }

  static win_iocp_io_context* get_iocp_service(
      const io_context::executor_type& ex)
  {
    return &ex.context().impl_;
  }

  win_iocp_operation* ptr_;
  win_iocp_io_context* iocp_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OVERLAPPED_PTR_HPP

/* win_iocp_overlapped_ptr.hpp
RSdc1PwRLvpzJ/4N1wlXn+fOtP+J7nydbLf/0fOl7X/UOkbYOtr/6xve/g+qR/vvvG/GJEXWvVV1ff11b1UdwfMSTffWtqTIurdqrj883VvI167j7AjKuT66t5z30zQuJhpt9LyGaZjZdtsdyI+MtdD/kGNGbqrrZLrUnXIzlkvWcdP3Em601ZJr9MNofjW+Y4OfGYad+swY/xQ9J4mxr9gvsNrb2ngw9thnByleS1/woj32STjXCtf14chsQWa7yAxwnWHv2F+qxzm6jq7o6VJvNa+u55J8hJ+Bgbv9d6OuvV6OqbCfy9WhZTq3dGZeBbNO7MUw41CPjkO13DRMd3NG1p1iLxb5dgH5PKLQcnTku5ozhW4X+yyRbxs4C9roS8sy8p3EPhH77zS8awyn96VK/BeKfYIJnxo+Dg+eT1IZT8iZpd8Okl0oeRV5h8bcW0RuqDnz+C7u0QuYu+txr5y631fulZShuU/txE3KyeiWpCzkeXDu58iwMaZ7LiO07R2uCrBKdT13PiziOlm/OXSP8/NK8ueW5FUUytNTNru4QrQXR5uz0LCcQa1zdbPEPtpzguWL+MzpPddw7YxusZ+IfZznRCtWw6neOA3pzLOtFbl4o8fn1kA8Hr5CuudFVNfVsyKTorqvmMn7B3tnAl9FcQbwfeQgkAeEACGEK0C4AwTkCCgYDjHcQcGCR0mAaMAQUggUq2KwqFhQUWnBq8YLkGoFi0otbaNSi1UptWq1pRUtVWrRIqLS1mr/78u3w763u+EloL1efr/J/83uN7MzszOzuzPffHO72MsiRIZrrGQh8ntE/k9h++2kqr24D+XcHdYSQqeprbj9cmyf1YKj64hT6yF/el+0XjeR666wJiGjdvY07HNWH44SFlk7bFHZZTWPT7O/yAGR3WKt1GtPNuH3WPEcJbzsZ5lC+OzWOo4XX3lbMKFxMG6m/75rGRqmijAHCBNX+UxiYlwLbCqlpjj6HunPcpBZhqvpzyrfdvVnKnMn7tUamVcj+zOR02vuQm5nSK5J5VbX3moqc7C1jkM1WtEzcgzK9h+IwraLR/uQ/nJGRH/p2oe1XU0kVwWIQzkf+cw7vNrNksXFi6TJRLYZ87wZJOHmBzry/3zuobYlja9VrePjE4xcB7N3zwjxFwVakeqCQAMzLhxwjQvTf0r48L23csV/SSCDNjs9EOe5//FckWmMPay/mrawSI71DHzVqjZ2/PbKsV+yJqIJ6zXaqKx9/GFa/DelXJpIyZIxyzI2FG8XmXG07lyzB/Qf5dhOa7XVR4/ZcW0mnevC20uBFJexcXeFyHUJJAcaudukbU9NZLaTqj56zJVW7fdlK//j+y3dGZLprX56BPE3ENt1+RROVQZ68D2ps3HpwQTGISPH0jNUbq8tl3RhMK5/LXsjqvxR5F8IyTcud9usU5kebe1rV94RTEgCtxGxd7x2egva2vFWbg3GpUTGba5f0VbbfnBFtqvtq8wGZP4YkklY0cF8h0aM9R5LYS6mj/28jG6sN89jnD7fe6xfzhX4j+Gbd+M726uNEVx7ZTFhrLuOt+3i0JtxUUVtY/cq39v09b3Fv5gWlBg5F2X2gCsXmRTC4OdXjvjnU//zI59l5nmXKTLLkUoJb6faJrvK+ct4dw6Y9y1L37fMXJXINDLPlZHiv4i1rhl6zE7LLEmLfc8e5T69jXsHdzDKe1bb+PynXVQHOo4xQOVc0rvXUfahWTHP+U3Ny9NV0i/pfbDDZpn+46j4S7Fp0Eje5Vgo5TlfOcGEzaEU5J2EyoCfVf1TeCd52prK+sKnkQ2dY3fAu2UPYGMT0zU3qTYx/ylxlqBvHZCwJeY6fVSGXfA=
*/