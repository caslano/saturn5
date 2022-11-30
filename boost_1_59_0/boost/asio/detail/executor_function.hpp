//
// detail/executor_function.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_MOVE)

// Lightweight, move-only function object wrapper.
class executor_function
{
public:
  template <typename F, typename Alloc>
  explicit executor_function(F f, const Alloc& a)
  {
    // Allocate and construct an object to wrap the function.
    typedef impl<F, Alloc> impl_type;
    typename impl_type::ptr p = {
      detail::addressof(a), impl_type::ptr::allocate(a), 0 };
    impl_ = new (p.v) impl_type(BOOST_ASIO_MOVE_CAST(F)(f), a);
    p.v = 0;
  }

  executor_function(executor_function&& other) BOOST_ASIO_NOEXCEPT
    : impl_(other.impl_)
  {
    other.impl_ = 0;
  }

  ~executor_function()
  {
    if (impl_)
      impl_->complete_(impl_, false);
  }

  void operator()()
  {
    if (impl_)
    {
      impl_base* i = impl_;
      impl_ = 0;
      i->complete_(i, true);
    }
  }

private:
  // Base class for polymorphic function implementations.
  struct impl_base
  {
    void (*complete_)(impl_base*, bool);
  };

  // Polymorphic function implementation.
  template <typename Function, typename Alloc>
  struct impl : impl_base
  {
    BOOST_ASIO_DEFINE_TAGGED_HANDLER_ALLOCATOR_PTR(
        thread_info_base::executor_function_tag, impl);

    template <typename F>
    impl(BOOST_ASIO_MOVE_ARG(F) f, const Alloc& a)
      : function_(BOOST_ASIO_MOVE_CAST(F)(f)),
        allocator_(a)
    {
      complete_ = &executor_function::complete<Function, Alloc>;
    }

    Function function_;
    Alloc allocator_;
  };

  // Helper to complete function invocation.
  template <typename Function, typename Alloc>
  static void complete(impl_base* base, bool call)
  {
    // Take ownership of the function object.
    impl<Function, Alloc>* i(static_cast<impl<Function, Alloc>*>(base));
    Alloc allocator(i->allocator_);
    typename impl<Function, Alloc>::ptr p = {
      detail::addressof(allocator), i, i };

    // Make a copy of the function so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the function may be the true owner of the memory
    // associated with the function. Consequently, a local copy of the function
    // is required to ensure that any owning sub-object remains valid until
    // after we have deallocated the memory here.
    Function function(BOOST_ASIO_MOVE_CAST(Function)(i->function_));
    p.reset();

    // Make the upcall if required.
    if (call)
    {
      boost_asio_handler_invoke_helpers::invoke(function, function);
    }
  }

  impl_base* impl_;
};

#else // defined(BOOST_ASIO_HAS_MOVE)

// Not so lightweight, copyable function object wrapper.
class executor_function
{
public:
  template <typename F, typename Alloc>
  explicit executor_function(const F& f, const Alloc&)
    : impl_(new impl<typename decay<F>::type>(f))
  {
  }

  void operator()()
  {
    impl_->complete_(impl_.get());
  }

private:
  // Base class for polymorphic function implementations.
  struct impl_base
  {
    void (*complete_)(impl_base*);
  };

  // Polymorphic function implementation.
  template <typename F>
  struct impl : impl_base
  {
    impl(const F& f)
      : function_(f)
    {
      complete_ = &executor_function::complete<F>;
    }

    F function_;
  };

  // Helper to complete function invocation.
  template <typename F>
  static void complete(impl_base* i)
  {
    static_cast<impl<F>*>(i)->function_();
  }

  shared_ptr<impl_base> impl_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

// Lightweight, non-owning, copyable function object wrapper.
class executor_function_view
{
public:
  template <typename F>
  explicit executor_function_view(F& f) BOOST_ASIO_NOEXCEPT
    : complete_(&executor_function_view::complete<F>),
      function_(&f)
  {
  }

  void operator()()
  {
    complete_(function_);
  }

private:
  // Helper to complete function invocation.
  template <typename F>
  static void complete(void* f)
  {
    (*static_cast<F*>(f))();
  }

  void (*complete_)(void*);
  void* function_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_EXECUTOR_FUNCTION_HPP

/* executor_function.hpp
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
*/