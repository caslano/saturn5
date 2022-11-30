//
// cancellation_state.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CANCELLATION_STATE_HPP
#define BOOST_ASIO_CANCELLATION_STATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cassert>
#include <new>
#include <utility>
#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/detail/cstddef.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// A simple cancellation signal propagation filter.
template <cancellation_type_t Mask>
struct cancellation_filter
{
  /// Returns <tt>type & Mask</tt>.
  cancellation_type_t operator()(
      cancellation_type_t type) const BOOST_ASIO_NOEXCEPT
  {
    return type & Mask;
  }
};

/// A cancellation filter that disables cancellation.
typedef cancellation_filter<cancellation_type::none>
  disable_cancellation;

/// A cancellation filter that enables terminal cancellation only.
typedef cancellation_filter<cancellation_type::terminal>
  enable_terminal_cancellation;

#if defined(GENERATING_DOCUMENTATION)

/// A cancellation filter that enables terminal and partial cancellation.
typedef cancellation_filter<
    cancellation_type::terminal | cancellation_type::partial>
  enable_partial_cancellation;

/// A cancellation filter that enables terminal, partial and total cancellation.
typedef cancellation_filter<cancellation_type::terminal
    | cancellation_type::partial | cancellation_type::total>
  enable_total_cancellation;

#else // defined(GENERATING_DOCUMENTATION)

typedef cancellation_filter<
    static_cast<cancellation_type_t>(
      static_cast<unsigned int>(cancellation_type::terminal)
        | static_cast<unsigned int>(cancellation_type::partial))>
  enable_partial_cancellation;

typedef cancellation_filter<
    static_cast<cancellation_type_t>(
      static_cast<unsigned int>(cancellation_type::terminal)
        | static_cast<unsigned int>(cancellation_type::partial)
        | static_cast<unsigned int>(cancellation_type::total))>
  enable_total_cancellation;

#endif // defined(GENERATING_DOCUMENTATION)

/// A cancellation state is used for chaining signals and slots in compositions.
class cancellation_state
{
public:
  /// Construct a disconnected cancellation state.
  BOOST_ASIO_CONSTEXPR cancellation_state() BOOST_ASIO_NOEXCEPT
    : impl_(0)
  {
  }

  /// Construct and attach to a parent slot to create a new child slot.
  /**
   * Initialises the cancellation state so that it allows terminal cancellation
   * only. Equivalent to <tt>cancellation_state(slot,
   * enable_terminal_cancellation())</tt>.
   *
   * @param slot The parent cancellation slot to which the state will be
   * attached.
   */
  template <typename CancellationSlot>
  BOOST_ASIO_CONSTEXPR explicit cancellation_state(CancellationSlot slot)
    : impl_(slot.is_connected() ? &slot.template emplace<impl<> >() : 0)
  {
  }

  /// Construct and attach to a parent slot to create a new child slot.
  /**
   * @param slot The parent cancellation slot to which the state will be
   * attached.
   *
   * @param filter A function object that is used to transform incoming
   * cancellation signals as they are received from the parent slot. This
   * function object must have the signature:
   * @code boost::asio::cancellation_type_t filter(
   *     boost::asio::cancellation_type_t); @endcode
   *
   * The library provides the following pre-defined cancellation filters:
   *
   * @li boost::asio::disable_cancellation
   * @li boost::asio::enable_terminal_cancellation
   * @li boost::asio::enable_partial_cancellation
   * @li boost::asio::enable_total_cancellation
   */
  template <typename CancellationSlot, typename Filter>
  BOOST_ASIO_CONSTEXPR cancellation_state(CancellationSlot slot, Filter filter)
    : impl_(slot.is_connected()
        ? &slot.template emplace<impl<Filter, Filter> >(filter, filter)
        : 0)
  {
  }

  /// Construct and attach to a parent slot to create a new child slot.
  /**
   * @param slot The parent cancellation slot to which the state will be
   * attached.
   *
   * @param in_filter A function object that is used to transform incoming
   * cancellation signals as they are received from the parent slot. This
   * function object must have the signature:
   * @code boost::asio::cancellation_type_t in_filter(
   *     boost::asio::cancellation_type_t); @endcode
   *
   * @param out_filter A function object that is used to transform outcoming
   * cancellation signals as they are relayed to the child slot. This function
   * object must have the signature:
   * @code boost::asio::cancellation_type_t out_filter(
   *     boost::asio::cancellation_type_t); @endcode
   *
   * The library provides the following pre-defined cancellation filters:
   *
   * @li boost::asio::disable_cancellation
   * @li boost::asio::enable_terminal_cancellation
   * @li boost::asio::enable_partial_cancellation
   * @li boost::asio::enable_total_cancellation
   */
  template <typename CancellationSlot, typename InFilter, typename OutFilter>
  BOOST_ASIO_CONSTEXPR cancellation_state(CancellationSlot slot,
      InFilter in_filter, OutFilter out_filter)
    : impl_(slot.is_connected()
        ? &slot.template emplace<impl<InFilter, OutFilter> >(
            BOOST_ASIO_MOVE_CAST(InFilter)(in_filter),
            BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter))
        : 0)
  {
  }

  /// Returns the single child slot associated with the state.
  /**
   * This sub-slot is used with the operations that are being composed.
   */
  BOOST_ASIO_CONSTEXPR cancellation_slot slot() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? impl_->signal_.slot() : cancellation_slot();
  }

  /// Returns the cancellation types that have been triggered.
  cancellation_type_t cancelled() const BOOST_ASIO_NOEXCEPT
  {
    return impl_ ? impl_->cancelled_ : cancellation_type_t();
  }

  /// Clears the specified cancellation types, if they have been triggered.
  void clear(cancellation_type_t mask = cancellation_type::all)
    BOOST_ASIO_NOEXCEPT
  {
    if (impl_)
      impl_->cancelled_ &= ~mask;
  }

private:
  struct impl_base
  {
    impl_base()
      : cancelled_()
    {
    }

    cancellation_signal signal_;
    cancellation_type_t cancelled_;
  };

  template <
      typename InFilter = enable_terminal_cancellation,
      typename OutFilter = InFilter>
  struct impl : impl_base
  {
    impl()
      : in_filter_(),
        out_filter_()
    {
    }

    impl(InFilter in_filter, OutFilter out_filter)
      : in_filter_(BOOST_ASIO_MOVE_CAST(InFilter)(in_filter)),
        out_filter_(BOOST_ASIO_MOVE_CAST(OutFilter)(out_filter))
    {
    }

    void operator()(cancellation_type_t in)
    {
      this->cancelled_ = in_filter_(in);
      cancellation_type_t out = out_filter_(this->cancelled_);
      if (out != cancellation_type::none)
        this->signal_.emit(out);
    }

    InFilter in_filter_;
    OutFilter out_filter_;
  };

  impl_base* impl_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_CANCELLATION_STATE_HPP

/* cancellation_state.hpp
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
*/