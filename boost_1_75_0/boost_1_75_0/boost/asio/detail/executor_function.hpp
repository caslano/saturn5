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
vKYe0HbllZ7DK6/yVK66khC/hrMvZIbJfLLHj3wYPgiqwKoa6dTipnhQ2Mx0cSRXuv3x5o0lvjBpH2jaO6XpRq8pCXr1NK2MAtBjoEmU7y1PMW38MjaeFNJ4UrBxgTTdoDYGbXllHDTp0ZCLcqJ4FcbLi3iC4WJ9sAQEktlriAGTi3ZTCd0UQzcY9A/9gT5kFnvJBxnuIFfdgksH5PDyW5gPSqAyeJb8dK9krdJZj+CuC5WFw9sUQsaspNL0BCCJyFXjgKLXjJKs+7VVz50LBDD8R358rlVp+TxNeHrE1S3bK1SfebNhg8rrd1Ux0mE+7B3n1VBadtD6r5oX3fCFhukMtRqzczr34Hhq+EeowsnDv93K9Bwox4EmPyrH9znpbRdxw0D2mbdbT77guhvo3bw961epxBWVbd4unC7LCB9blhEG/xk5qRUQbkgq0hfsTiqy6yj+4TGDPdMl2bLIkIRPGRFF9khQ8HuQDU0KC/vgoFa6P9DkZ7rqZY5FllD8w3Qsi+lYInEsyWwst9tDxnL2BVcUcA8YSxMMw+9KKpsePrFsehj8Z+T+H3PfHh9Fdf69tyRLEpiFBAi3EEUURRQMakIQCTEJKIENaRIiDWiVSNcLCDOASiA4u7qbcYs32tpKvbe22pa2EtCKZgnNRfxpRNQgqFFRZ50UI8SwJCH7Ps9zZmZnc0Ft+8fL50N2dy7nPOc5z/V7bkB0
*/