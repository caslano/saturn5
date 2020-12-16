//
// detail/executor_function.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EXECUTOR_FUNCTION_HPP
#define BOOST_ASIO_DETAIL_EXECUTOR_FUNCTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class executor_function_base
{
public:
  void complete()
  {
    func_(this, true);
  }

  void destroy()
  {
    func_(this, false);
  }

protected:
  typedef void (*func_type)(executor_function_base*, bool);

  executor_function_base(func_type func)
    : func_(func)
  {
  }

  // Prevents deletion through this type.
  ~executor_function_base()
  {
  }

private:
  func_type func_;
};

template <typename Function, typename Alloc>
class executor_function : public executor_function_base
{
public:
  BOOST_ASIO_DEFINE_TAGGED_HANDLER_ALLOCATOR_PTR(
      thread_info_base::executor_function_tag, executor_function);

  template <typename F>
  executor_function(BOOST_ASIO_MOVE_ARG(F) f, const Alloc& allocator)
    : executor_function_base(&executor_function::do_complete),
      function_(BOOST_ASIO_MOVE_CAST(F)(f)),
      allocator_(allocator)
  {
  }

  static void do_complete(executor_function_base* base, bool call)
  {
    // Take ownership of the function object.
    executor_function* o(static_cast<executor_function*>(base));
    Alloc allocator(o->allocator_);
    ptr p = { detail::addressof(allocator), o, o };

    // Make a copy of the function so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the function may be the true owner of the memory
    // associated with the function. Consequently, a local copy of the function
    // is required to ensure that any owning sub-object remains valid until
    // after we have deallocated the memory here.
    Function function(BOOST_ASIO_MOVE_CAST(Function)(o->function_));
    p.reset();

    // Make the upcall if required.
    if (call)
    {
      function();
    }
  }

private:
  Function function_;
  Alloc allocator_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_EXECUTOR_FUNCTION_HPP

/* executor_function.hpp
7piOgAnioFS0Mcsy1NQoi7Zm9MDaHEWwOb1glHlE5fIEyjjLgSiPGYDPxxt5DZRyyqGjiKCEXVOB3eZ22rXn3kJ6mvGT4+bIJYGsdCtLpgsLGHohYxf9g5wmuvMSnrNRgrBsBV5sL4EnLclJbzrLkunR6eE1HGRS7nVTlSTMhyBB+otB2hPuRkVRCiXaclUeR/8olNsOWuWad+1y1tyCH1asIGKFKNcleeXZKkCHND85PIj51qksmkdiRpP2ROGPmRlF/1BIi8bjI6fzeZWI8lj8drxVa2Uz2/CfKwJ7+RYJ1lTlQprS5GL3gOfVwjxeQsI73jmGEGn4yoTlgsFBRw+DwDXnINFsQLvEpjjBR9Yuo9QWlw9CM3SL8CL/z5WS82QlUblCVllFjoL2cLEiZ4s5osBKKhNxYUvkJbODoLU+VS31idts5dzCoozSttBgsyeNe59RZXysOG3dYGsX+E/d3z91ff/a7ZW7vLZuqdzftPc1/9jPtPcx5c6htWOQhfeLNHWVl7jm6LsKeSUUC6dqKZyqrXCqfyic6h8Kp/qXwqmKhdNs1lB+crhLcbFhlxtnuWFW5TKuWsu4+ocyrtrLuNz4iw283LjbG/b06Kzc3RT93K67y9FVDchsJsXRKTGNHZKciSDJATdJy2xHMrUkq6GDoRffQ3fKIhpRwiqui+NkI3Qk10aVbdLJQQcvGpaF2PpgXE2izG1eEKRU0tHMWEfn+Rtl88PhQrs87VvXX4RJt0XRQ1YkUcYmE2VMXpRhgNEu5zMsE3Fckkv4pMkFs4Me/yELyuWeergSnU2rRCELPMpG8+2S9LFZi5SaBxk/JSrK/7lwq/YC9H1clKV0tsr/uYBDFxal5eJnJxdl0gxdf+RnPsgsDDHasJci5FPMOc0JEnltJo2QmBUFWX18Ywqpuasap8xlnOpXEJB33a34OejI0aCJDzmogbQmktDaR4waR+RqWXzuxhlN0iwuUiwIvunBRT2yZhmCJconmNzMqE0yScrYEabzT/DAiPujUZwbTQwdJqZIHj2ebHYo1j96avPhoTZPEKddScimCJNGYF+3eKPCxFY2dUvOEoEiSA9ICiYHV7MA+FyOJGttdsPpaGCQnRbx+JBKsro8LcxlujqmOwhvRVtEeG3bLsFbuGPLUr4VLouKIa1+8qb5kNtNFJYmCEsTg+0TgnEiMEwAch57MEwfssrRTrWMNY89IgSlBRcgYwQyWl00PLpBLIyPPyHQrKYOw59tYE5RrI9xhj3S7MnKs+5xxh3EUbGVHZW3Mp7+lHC2cCY2e3Y5QcS3r838TQFysuzVv6+tB4nIST2Lr4HZ/ydrqrZ/WLnJZ5z3Vo9DUstExHyU6PhTul3HpAd7UikdKRZliba6S6HQh3FCtSxUokV4zPSgRXjAWa1qzr2y63VsCpb0Ksv8YCaKpyjgdj8Ss0sss9C9zHFvy0kQpWbjHkzSr8u4PTGp4FmxSfmKHUzI8kKrytp06iHIxXaev1YqvzQov2gKL5n4gsm/XGKDT0f35xzzlfdgEyPL1uTp2Mggmp9PR5WxsxSBdQsewZcSPJ9ACTwOXTm56cPGAKs2jHmdWmkg3Cc5SXrQhC+TA8FHTeTxuCEf30aDDy+PQR1ma4GzKMDn/qIGpPPQ8YXtsevVI17ChcTR8PL8PLJzdHygFw7CajLHHnIQvucbnehI0eHQUc7F4Hb/ypOVRountROgoqGqO8p27UmNqSxZGMo+QP1m2Go0sB1ExguZYpD5zCEf0wsypgJklgoK8lSAylIRJeVU5ENuMMjlAmTNyVlUHLJhqJSJtErtU3/Mhyt8zJeutt9px63Txe6U7l6LsaLvICw=
*/