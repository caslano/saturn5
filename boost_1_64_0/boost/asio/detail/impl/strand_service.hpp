//
// detail/impl/strand_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/call_stack.hpp>
#include <boost/asio/detail/completion_handler.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

inline strand_service::strand_impl::strand_impl()
  : operation(&strand_service::do_complete),
    locked_(false)
{
}

struct strand_service::on_dispatch_exit
{
  io_context_impl* io_context_;
  strand_impl* impl_;

  ~on_dispatch_exit()
  {
    impl_->mutex_.lock();
    impl_->ready_queue_.push(impl_->waiting_queue_);
    bool more_handlers = impl_->locked_ = !impl_->ready_queue_.empty();
    impl_->mutex_.unlock();

    if (more_handlers)
      io_context_->post_immediate_completion(impl_, false);
  }
};

template <typename Handler>
void strand_service::dispatch(strand_service::implementation_type& impl,
    Handler& handler)
{
  // If we are already in the strand then the handler can run immediately.
  if (call_stack<strand_impl>::contains(impl))
  {
    fenced_block b(fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(handler, handler);
    return;
  }

  // Allocate and construct an operation to wrap the handler.
  typedef completion_handler<Handler> op;
  typename op::ptr p = { boost::asio::detail::addressof(handler),
    op::ptr::allocate(handler), 0 };
  p.p = new (p.v) op(handler);

  BOOST_ASIO_HANDLER_CREATION((this->context(),
        *p.p, "strand", impl, 0, "dispatch"));

  bool dispatch_immediately = do_dispatch(impl, p.p);
  operation* o = p.p;
  p.v = p.p = 0;

  if (dispatch_immediately)
  {
    // Indicate that this strand is executing on the current thread.
    call_stack<strand_impl>::context ctx(impl);

    // Ensure the next handler, if any, is scheduled on block exit.
    on_dispatch_exit on_exit = { &io_context_, impl };
    (void)on_exit;

    completion_handler<Handler>::do_complete(
        &io_context_, o, boost::system::error_code(), 0);
  }
}

// Request the io_context to invoke the given handler and return immediately.
template <typename Handler>
void strand_service::post(strand_service::implementation_type& impl,
    Handler& handler)
{
  bool is_continuation =
    boost_asio_handler_cont_helpers::is_continuation(handler);

  // Allocate and construct an operation to wrap the handler.
  typedef completion_handler<Handler> op;
  typename op::ptr p = { boost::asio::detail::addressof(handler),
    op::ptr::allocate(handler), 0 };
  p.p = new (p.v) op(handler);

  BOOST_ASIO_HANDLER_CREATION((this->context(),
        *p.p, "strand", impl, 0, "post"));

  do_post(impl, p.p, is_continuation);
  p.v = p.p = 0;
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_SERVICE_HPP

/* strand_service.hpp
6HkMYl1V/n4Eel0eYZb9O7HbJ3HJ4FCVreTRNxx8H1gKrgUtuWaVW+AjN1w/lxkBTgZHGjm1iQYu9ZHbyaAzErwTLAY/D74OlkENKnebynUGF6rcNpWrBqeA7wdngDeBc8Ea8ErwA+By8GawGvyQ3p8xQ21hMRbq/VPAXL3/cqL7gVeDI8BVYL6GLflGld/gI38pfEPBy1RuMbgUvNzIq90lcJ2PfJnWw1IwD7wSXAxeZa+P4cHlWqvlc5uW6x2gymETJ1juoyr3MZXbbpNrVLmrfeSKNb+zwYvBuSaflt0U0EduvrabBWAReIlNriEnuL1lqdxgbW/ZoNVuxO4GuMOn3Vyr+q0Dp4Nh1fM6cD64AbwK3AiuBDeBN4HX29pN08jgdjNV2800bTdFWv+ERb4kpDYawGtUvhM4ReVXkM5gcBU4HFwNjgYrwcngGvDdGrby06D32+LJD6jtcAyY7/SppPL6fT9Y5SM/Qev1Qm2HE7UdFxp99Lt54P0++mRqPfUDx4H9NR/ngXPAAeA6DVv5qdP7jfLJz2D07g4O0XLKBodp2NRPFPlUle+u8j1UnrCRzxoTLD9a5XNVfozKE24tzyjyGSrfV+UzVZ5wq/5R5N+l8mUqv1Tly+z6R5GfpfLFKj9b5Anb9R8bLH+xyl+i8otEnrBd/yjyhSp/kcpPFnnCdv3HBvevvdq/vqb9625tT4SNfHMU+V0q/wWV/6LKEzbyReOC8/9bzf+rmv+jkn/C9udKFPnvqvyDKv+QyBO29+co8veo/NdV/l6VJ2zkQ3nB8l9S+TqVv0vlCbfqH0U+tYP2H1D6DzhMw0b/KPK/0vRf0vR/LekTtusfRb6Dpp+s6ado+oRb9c8Pln9W0z+o6T8n6RO2658f3H5e0/ZzTNvPH7X9EDbytVHkn1L5n6j8AZUn3Np/o8i/ofInVP5vKk/YyOeND5Y/qPLPqfzzKk+4tf7GB5ffm0R3B/8BDgZPgcM0bOovivwvVf4Flf+VyhNurb8LgvN/m+b/ds3/HZp/wka+NIr8h1X+Iyp/q8gTtj9/osg/ovI/UPkfijxh+/gTRf7bKn+/yj8g8oTt48+EYPltKl+t8jeKPGF7+4siH1b561R+g8gTtrc/lc/2kR+u/WcE2B/MAQdpWOU5Sxss31Pl01W+l8qn2/tfFPk8lc9X+fEqT9jIh6PID1D5gSp/nsoTbq3/KPLLVP4qlX+PyhM28o1R5EtUfp7Kz1d5wpY8FRcsf5nKL1b5JSpPuLX/R5GfpvLTVb5I5Anbn98Tg9vPvdp+vqHt55vafggb+foo8nep/JdV/isiT1jl14T0DBdwpcp3BZep/F/IZwZ4XMfvN/Q9+U0wH/wbOAs8Cc7RcImGLwb/Di5Sfiu9cJT0HtP0ntD0fqzp/UTT26/pPanpESY9wpreU+Ai5Tf9a1Jw/bym9XNM6+dP4CANm/5VECz/sMo/ovI/FHnC9v4VRf5bKl+v8veJPGF7/4oiv1vlv6rye0SesL1/RZE/R5/vncH+YBdwkIZN/4oif0jT/6Wm/4KkT9jevwqD5f+p8m+p/NsiT9jev6LI/1Tlf6byjSJP2N6/CoP7R7P2j79o/3gdzNew6V+B8qSj8o0q/3OVJ9yq/0XB8m+rPAzIA2C+hs3zNYp8k8r/RtN/GczXsKn/i4LLL0XLr6OWXydwkIZN/UeR/21I38/B/uDvwEEaNvpPDs7/ZzT/n9X87wTzNWz0jyL/cZXfrvKfEHnCdv2jyD+m8j9S+cdFnrD9/SKK/IMqv0/lH1J5wq39f0qwfI3Kf0DlPyjyhO3vF1HkN6n8ZpW/HszXcHUn8UEc0//wwvVO38MNUPM=
*/