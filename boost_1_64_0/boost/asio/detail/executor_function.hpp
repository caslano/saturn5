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
9WxdH/EX92gn6Co+Q/vcuHN2UVcArneBih+o+liP1WVpdPjlP9xXF+McAc2MOaLLbG6S1rGSq6WlZ7dFU7GCeBrtAbMy/TGH1fjVSth8aWDvmO/5MYvOSVUmXtJc+7Ore/MvArE48ZLEKj069CPY3CbZ3Yk5kGqJ8Ik3blXcBraZVHY0IgBSra7huBgkki0u15n0op6LvbKxZ0X8QvMoxDxvQtM9Kpa9vSmPYYYtljku4dPwvqh8Kx4dZW5T9HBbDqtQ6FGANGZ559VJ19qcEtE506ZaCQTnbNrnFCI4S5VwzwVEmYmpwApZbq31oJastKDE9UwBEVFu+l6qOj13QXSsIjDE/Q82u2O1b0PavBeJ+lq/8JiezAWd7lZzd1eHOwMWBMv8TOeJZI4noGLWefEJXDiW2jGeo+xTnqgS5kKy+HVh2r13j6GDAFP2kDLlrm0rqc0RHk1uoc4PUq3CkNGKyZaTeGeMGjLXpE7JSaPEOKexSCnPukhB4GsCr6ON71FpwxdfQxxbspg72x1ZQwuwvJ5ZrCJgEb8DbhFwasG04/i91YqYyhtEyQ==
*/