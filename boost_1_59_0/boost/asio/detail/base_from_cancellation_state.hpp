//
// detail/base_from_cancellation_state.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BASE_FROM_CANCELLATION_STATE_HPP
#define BOOST_ASIO_DETAIL_BASE_FROM_CANCELLATION_STATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/cancellation_state.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename = void>
class base_from_cancellation_state
{
public:
  typedef cancellation_slot cancellation_slot_type;

  cancellation_slot_type get_cancellation_slot() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_state_.slot();
  }

  cancellation_state get_cancellation_state() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_state_;
  }

protected:
  explicit base_from_cancellation_state(const Handler& handler)
    : cancellation_state_(
        boost::asio::get_associated_cancellation_slot(handler))
  {
  }

  template <typename Filter>
  base_from_cancellation_state(const Handler& handler, Filter filter)
    : cancellation_state_(
        boost::asio::get_associated_cancellation_slot(handler), filter, filter)
  {
  }

  template <typename InFilter, typename OutFilter>
  base_from_cancellation_state(const Handler& handler,
      BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
      BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
    : cancellation_state_(
        boost::asio::get_associated_cancellation_slot(handler),
        BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter))
  {
  }

  void reset_cancellation_state(const Handler& handler)
  {
    cancellation_state_ = cancellation_state(
        boost::asio::get_associated_cancellation_slot(handler));
  }

  template <typename Filter>
  void reset_cancellation_state(const Handler& handler, Filter filter)
  {
    cancellation_state_ = cancellation_state(
        boost::asio::get_associated_cancellation_slot(handler), filter, filter);
  }

  template <typename InFilter, typename OutFilter>
  void reset_cancellation_state(const Handler& handler,
      BOOST_ASIO_MOVE_ARG(InFilter) in_filter,
      BOOST_ASIO_MOVE_ARG(OutFilter) out_filter)
  {
    cancellation_state_ = cancellation_state(
        boost::asio::get_associated_cancellation_slot(handler),
        BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
        BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter));
  }

  cancellation_type_t cancelled() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_state_.cancelled();
  }

private:
  cancellation_state cancellation_state_;
};

template <typename Handler>
class base_from_cancellation_state<Handler,
    typename enable_if<
      is_same<
        typename associated_cancellation_slot<
          Handler, cancellation_slot
        >::asio_associated_cancellation_slot_is_unspecialised,
        void
      >::value
    >::type>
{
public:
  cancellation_state get_cancellation_state() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_state();
  }

protected:
  explicit base_from_cancellation_state(const Handler&)
  {
  }

  template <typename Filter>
  base_from_cancellation_state(const Handler&, Filter)
  {
  }

  template <typename InFilter, typename OutFilter>
  base_from_cancellation_state(const Handler&,
      BOOST_ASIO_MOVE_ARG(InFilter),
      BOOST_ASIO_MOVE_ARG(OutFilter))
  {
  }

  void reset_cancellation_state(const Handler&)
  {
  }

  template <typename Filter>
  void reset_cancellation_state(const Handler&, Filter)
  {
  }

  template <typename InFilter, typename OutFilter>
  void reset_cancellation_state(const Handler&,
      BOOST_ASIO_MOVE_ARG(InFilter),
      BOOST_ASIO_MOVE_ARG(OutFilter))
  {
  }

  BOOST_ASIO_CONSTEXPR cancellation_type_t cancelled() const BOOST_ASIO_NOEXCEPT
  {
    return cancellation_type::none;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BASE_FROM_CANCELLATION_STATE_HPP

/* base_from_cancellation_state.hpp
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
*/