//
// detail/strand_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP
#define BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/operation.hpp>
#include <boost/asio/detail/scoped_ptr.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Default service implementation for a strand.
class strand_service
  : public boost::asio::detail::service_base<strand_service>
{
private:
  // Helper class to re-post the strand on exit.
  struct on_do_complete_exit;

  // Helper class to re-post the strand on exit.
  struct on_dispatch_exit;

public:

  // The underlying implementation of a strand.
  class strand_impl
    : public operation
  {
  public:
    strand_impl();

  private:
    // Only this service will have access to the internal values.
    friend class strand_service;
    friend struct on_do_complete_exit;
    friend struct on_dispatch_exit;

    // Mutex to protect access to internal data.
    boost::asio::detail::mutex mutex_;

    // Indicates whether the strand is currently "locked" by a handler. This
    // means that there is a handler upcall in progress, or that the strand
    // itself has been scheduled in order to invoke some pending handlers.
    bool locked_;

    // The handlers that are waiting on the strand but should not be run until
    // after the next time the strand is scheduled. This queue must only be
    // modified while the mutex is locked.
    op_queue<operation> waiting_queue_;

    // The handlers that are ready to be run. Logically speaking, these are the
    // handlers that hold the strand's lock. The ready queue is only modified
    // from within the strand and so may be accessed without locking the mutex.
    op_queue<operation> ready_queue_;
  };

  typedef strand_impl* implementation_type;

  // Construct a new strand service for the specified io_context.
  BOOST_ASIO_DECL explicit strand_service(boost::asio::io_context& io_context);

  // Destroy all user-defined handler objects owned by the service.
  BOOST_ASIO_DECL void shutdown();

  // Construct a new strand implementation.
  BOOST_ASIO_DECL void construct(implementation_type& impl);

  // Request the io_context to invoke the given handler.
  template <typename Handler>
  void dispatch(implementation_type& impl, Handler& handler);

  // Request the io_context to invoke the given handler and return immediately.
  template <typename Handler>
  void post(implementation_type& impl, Handler& handler);

  // Determine whether the strand is running in the current thread.
  BOOST_ASIO_DECL bool running_in_this_thread(
      const implementation_type& impl) const;

private:
  // Helper function to dispatch a handler. Returns true if the handler should
  // be dispatched immediately.
  BOOST_ASIO_DECL bool do_dispatch(implementation_type& impl, operation* op);

  // Helper fiunction to post a handler.
  BOOST_ASIO_DECL void do_post(implementation_type& impl,
      operation* op, bool is_continuation);

  BOOST_ASIO_DECL static void do_complete(void* owner,
      operation* base, const boost::system::error_code& ec,
      std::size_t bytes_transferred);

  // The io_context implementation used to post completions.
  io_context_impl& io_context_;

  // Mutex to protect access to the array of implementations.
  boost::asio::detail::mutex mutex_;

  // Number of implementations shared between all strand objects.
#if defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)
  enum { num_implementations = BOOST_ASIO_STRAND_IMPLEMENTATIONS };
#else // defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)
  enum { num_implementations = 193 };
#endif // defined(BOOST_ASIO_STRAND_IMPLEMENTATIONS)

  // Pool of implementations.
  scoped_ptr<strand_impl> implementations_[num_implementations];

  // Extra value used when hashing to prevent recycled memory locations from
  // getting the same strand implementation.
  std::size_t salt_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/strand_service.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/strand_service.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_STRAND_SERVICE_HPP

/* strand_service.hpp
wDvD27O9NEw5a1fZcvtlzmrBO+XPW62ILvJEz1WNzFP9eeapLnk2ske6yx7poiuNzE+trL7155ifuuQd2hFuF+593DFcrXcJ/25EBxv5RX7/T7+Tpv/POXHr/42rpxa/VXbR/foM7TO8x+DMi0b2HDG8Tx//FACzTmDy+UpuaI8hfZxWCfTa/g9obRn78pUeB7v22nzyrtJjYkEJ6hE/Pf4/P3AvfuQrZF8esEbgfIe9+Gu52PsXOV8XpuLh25iXtnffi7/Qwc5/TBfCOKeLmXnYtv0Dg/cH+EHs2Vt6SE94b0fqcLVOK6QSx2dNHM93uC7/j7VOepaUvy9MY7NH7nnan+D5UelIkK9SX8nnjLfZXUuYNKMbb6P91TzfW4k2HQ9j6aInmqjPP8U7fifGAy4Q/RFWFw+q47V1OsUIUhKMXft1NR11uDijA7lQ+fnS+Rf/2/VRdUSXdKM+v90axj7B9xFviuiU3tbH0znaQ6c1W+t5Juegedb6Lb5N9PHLU/Q1TLRfwwodNl6fH1tHh5uYYzv/kz6fqHUvC9S4KnVTs7lay61wn1K+VGnJ/5aL7kXCFBAmRYWpXlgarDNpjl+F39XEQlvJce7BnS24D/m7q98Py7cTqS66ho+1rmGWsQ+hjvHrOtbH0iBlxDFdRgHzaZITZB0q39iZtL2iB93bHuPjQy3n9ifhBri1NTnfzqzZt1f7n/U84okNbGvSBnY/pM4/wzXHUt+b5TgB9fHZnnpWjGeMp65bO3Bti++odEkxRXS0n2j/Ks+Nnio6zDe6B8lXUZn1NYP3slbN5ysdbqnnak+SDsf4ZEibS3hI2pzR3Wbl2M+n6PNxRg9aT/uv9PS3GnjO1Mckv1h9pbA61DJC7qZE9uKiPFWtUz2N1LWJ/UWW1hmjx5Iw8zzVzXV7lVcpch+31+cHeRowOnGFaqGxSFT1tr3owk1xNZKiouOqJ0XFJVWtkXhOYvPE/ok5iX0Se8ZFRScnNklsGtcwOjauSXR1/VcV/qqS2Bo5JdUisXdcbc42SoqqEVctqcrFvvtlaGvtHOt6mb6eD7n+31kFjECeGVLX/UPyLnUvcU0bWzA+y+wz3lOFY6RwDk+NVH3MY8qkJ0dfYGfPHOKoLs8xpeMdp54PUi9Xatl7GJ9qzrhpqhz3WOv08TvIw+WMe8YFtgvRDffXMgsY76xirueAPraBfUVHEBtytuvpj6S6nlxPfFnXqvulZB6Ch5Wthndv7U1JsfWSojPK0AlLmCTqNoMw6HJLgvslX7zdq0q8MXPPT4qNS4rpxv/lxDvBF2/i3D7B8SondnH0eYF9XVtcC9zYZHU8HF0vutyg/m5RGP2dT5/2jdc+kUPEJbpe7hmOZQU8jzcmhD77v7iA/9Y694n2+XZci/19iDCVfx8irpD3oSaJzu9Dq1c5XluF5txlnO/+PlSUGFomU9T8L+cyqci8O9/7kLFt7ZLkYtu6tgK2rWvLsW1de3y2rT5debKE3uuhHOETcKqyo/Re64TcTGXemjN22sRMPgQIP3ZKTkF+mWvlStj6+rmTJ3ls2kHJFtDS8uVZ6pM7w9i+bMWvnmF+W9dxKrjZJ2izPr/GI3ZHhJc9fuy2riJfC27U50dq/xQjf6p5D/OsU/6BntN5AvnrQeVV5a9PzXTCUOcSzqPywz0Xanukyu1zLTPNY/pinVe/bdAZOq2vsb7aJ8fs6X+t197tTrs5Vs3XL9ZJisUfbNfSSOSaVffJDaPjTIqe28W9/7xQwvSugZ7N2+euiE7mKZjCky8meijGgFGxiS040Eg9FhPP5nC16BpxydFVOFUjStbcFftfr5O/5Z1Al32e/Z2gk85biuM=
*/