//
// detail/win_object_handle_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP
#define BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)

#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/wait_handler.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_io_context.hpp>
#else // defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/scheduler.hpp>
#endif // defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_object_handle_service :
  public execution_context_service_base<win_object_handle_service>
{
public:
  // The native type of an object handle.
  typedef HANDLE native_handle_type;

  // The implementation type of the object handle.
  class implementation_type
  {
   public:
    // Default constructor.
    implementation_type()
      : handle_(INVALID_HANDLE_VALUE),
        wait_handle_(INVALID_HANDLE_VALUE),
        owner_(0),
        next_(0),
        prev_(0)
    {
    }

  private:
    // Only this service will have access to the internal values.
    friend class win_object_handle_service;

    // The native object handle representation. May be accessed or modified
    // without locking the mutex.
    native_handle_type handle_;

    // The handle used to unregister the wait operation. The mutex must be
    // locked when accessing or modifying this member.
    HANDLE wait_handle_;

    // The operations waiting on the object handle. If there is a registered
    // wait then the mutex must be locked when accessing or modifying this
    // member
    op_queue<wait_op> op_queue_;

    // The service instance that owns the object handle implementation.
    win_object_handle_service* owner_;

    // Pointers to adjacent handle implementations in linked list. The mutex
    // must be locked when accessing or modifying these members.
    implementation_type* next_;
    implementation_type* prev_;
  };

  // Constructor.
  BOOST_ASIO_DECL win_object_handle_service(execution_context& context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new handle implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Move-construct a new handle implementation.
  BOOST_ASIO_DECL void move_construct(implementation_type& impl,
      implementation_type& other_impl);

  // Move-assign from another handle implementation.
  BOOST_ASIO_DECL void move_assign(implementation_type& impl,
      win_object_handle_service& other_service,
      implementation_type& other_impl);

  // Destroy a handle implementation.
  BOOST_ASIO_DECL void destroy(implementation_type& impl);

  // Assign a native handle to a handle implementation.
  BOOST_ASIO_DECL boost::system::error_code assign(implementation_type& impl,
      const native_handle_type& handle, boost::system::error_code& ec);

  // Determine whether the handle is open.
  bool is_open(const implementation_type& impl) const
  {
    return impl.handle_ != INVALID_HANDLE_VALUE && impl.handle_ != 0;
  }

  // Destroy a handle implementation.
  BOOST_ASIO_DECL boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec);

  // Get the native handle representation.
  native_handle_type native_handle(const implementation_type& impl) const
  {
    return impl.handle_;
  }

  // Cancel all operations associated with the handle.
  BOOST_ASIO_DECL boost::system::error_code cancel(implementation_type& impl,
      boost::system::error_code& ec);

  // Perform a synchronous wait for the object to enter a signalled state.
  BOOST_ASIO_DECL void wait(implementation_type& impl,
      boost::system::error_code& ec);

  /// Start an asynchronous wait.
  template <typename Handler, typename IoExecutor>
  void async_wait(implementation_type& impl,
      Handler& handler, const IoExecutor& io_ex)
  {
    // Allocate and construct an operation to wrap the handler.
    typedef wait_handler<Handler, IoExecutor> op;
    typename op::ptr p = { boost::asio::detail::addressof(handler),
      op::ptr::allocate(handler), 0 };
    p.p = new (p.v) op(handler, io_ex);

    BOOST_ASIO_HANDLER_CREATION((scheduler_.context(), *p.p, "object_handle",
          &impl, reinterpret_cast<uintmax_t>(impl.wait_handle_), "async_wait"));

    start_wait_op(impl, p.p);
    p.v = p.p = 0;
  }

private:
  // Helper function to start an asynchronous wait operation.
  BOOST_ASIO_DECL void start_wait_op(implementation_type& impl, wait_op* op);

  // Helper function to register a wait operation.
  BOOST_ASIO_DECL void register_wait_callback(
      implementation_type& impl, mutex::scoped_lock& lock);

  // Callback function invoked when the registered wait completes.
  static BOOST_ASIO_DECL VOID CALLBACK wait_callback(
      PVOID param, BOOLEAN timeout);

  // The scheduler used to post completions.
#if defined(BOOST_ASIO_HAS_IOCP)
  typedef class win_iocp_io_context scheduler_impl;
#else
  typedef class scheduler scheduler_impl;
#endif
  scheduler_impl& scheduler_;

  // Mutex to protect access to internal state.
  mutex mutex_;

  // The head of a linked list of all implementations.
  implementation_type* impl_list_;

  // Flag to indicate that the dispatcher has been shut down.
  bool shutdown_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_object_handle_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)

#endif // BOOST_ASIO_DETAIL_WIN_OBJECT_HANDLE_SERVICE_HPP

/* win_object_handle_service.hpp
eq7Jp1/JY+hSVzXf//WEPKX7q9J1Bw9Y+//qw/cqsB+YB2aB12t/TQKngVPAOeBUcAn4TnA1OA2sAq8BN4ALwK3gQvC9YAG4B1wM3qPl7gWvBb8EzgIPgnPAF8Fl4OvgdeBJpT8FRq39NfBW5SMFLFY+5tN/aeACsB+4HLwEXAReBhaA14KLwQXgErAQXAauBq8DK8BC8CbJb8mv7mGBXX3kt1LHvwpMBqvB9uBGsAO4AUzV+CnwICFPy/uulpcO7rPsm6DLAC8AszQ+UONDND5M4+vACFil8RqNvwvsBG4HO4O3g13A3WAGeD+YCj4IdgUfAdPAz4PdwC+C3cHHwRTwkOYz7S8Nbn+2tn8kmKXxgRofovFhGl8HjgKrNF6j8XeBl2v7R2v7r9D2T9D252r7x2j7x2r7r9T2j9f2X6btn6Dt3xvStWbwMW1/Gni3tv9LOh8eVz30FXCgXh+s10fo9fHgIXASeBicB34NjIJfB28F63U+fAPcDj4B7gKfBD8MPqXz4ptgnfrE3qvlaX+zBhrc38dUz70MZml8oMaHaHyYxteBJ8Aqjddo/F3gL7R9vwRvB38F7gZfB+8HXwUfBH8NPgL+Bvw8+Fvwi+DvwMfBV8BDmk/1FGtqzeup7YTlSnef0nUGNytdzzDjAvbR+d1X5etiMAfsB+aC/cHxYBa4ArwQLFa6CnAgeDM4CNwGXqRyNRi8S+nU57eu5Wh7XD6/J2p7Jmt7pmh7Zml7pmo73qntmKbtmKXtuEbbMUPbMVPbca22Y5a2oyakax/AGm1HBCzTdjyt988jYG/wGZWD7+t974cqBw3gGPA58FrwB+BijS/V+HLweXCF5tNx4b0/eFze0PlyWu8fb2r9/wBzwD+CueCfdL68peX/GSxWugrwr+DN4BlwG/g3lb+/g3cpnfFxX9G8PO0K6bsieJPS2X3X99fnhCwwDRyg7R+p8+cd2m8DweHgReBYcDB4NZgNTgOHgyvBEWCJ5lsLXgpWaHnVet3yzb5L258U5qLLN/sabUep6pt1On/LwBngenAWuAO8HoyqL/kb1Hd8pfbfBvBOcBP4CXAz+GnwXeBnwK3gfnAb+EUt75tgLf//GtwOvqHXc9s2/93+2ItEFmH5UIcv9nP6hv/Rn/37z/tOhqcCQtC537YvnZ+zvzkvec//bqZe9xngXbckva3ngJfRjtf4+wD1NHUe+Ajp1pngk7ckvS3ngqMvOc8G7yRuPx/c9takt/WM8L6X/o3nhOGt8axwfOeE4zkjHNnb9DnhUdQ5n1BN2E04RDhGOEPoU5sUmkwoI+wk7CU8RThBaLuF7/4T8gjLCJsJdxMObDn/54j/Nf7/yovWl5z79/8Hq23/8lPGtn/WxGunFE6ZNX+uzb5f6OrTqcOHbvqUedjqlqyPkQ5Vuqw/OOmmz5o/Ze6siTMNIb9e0JZyY44KbYwtYapw1arG8wRTh4fMemN92N/eeNc8WW/0NCgRH3wnTwX74Cto4/WLF+EGnr/Qp97F4h5P1uBPOW0MoW+5f7xTam9ob9dJH9+Ap0mp9W+XOWNxyvntR+hbfsbilM939Nck+Y9Tnd84JWgbXtfEOD3v4y8wzDjt9+uPFtqHW9/ezG8b4AtS6/IT+lACfOb9IdgG/kRbjzxyr0Ye3HUjida+cb1LFk8mJouOMa/3sX2t8bHLf4KUrEWuNokUapuccghty+Ww3kcOj7c7u9+UqWswH4zNW3ebxEi4uERs0E27ynmEtdmuSJ6rsDFO0fZa5Qy12xJRiO5NmPR+xv6oXOILQhfSxjTyDGxn5VEbbd3DWCd014Uu0X3lfFNWb9kX3kxfbybv74aihy7oF0k=
*/