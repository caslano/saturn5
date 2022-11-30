//
// cancellation_signal.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CANCELLATION_SIGNAL_HPP
#define BOOST_ASIO_CANCELLATION_SIGNAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cassert>
#include <new>
#include <utility>
#include <boost/asio/cancellation_type.hpp>
#include <boost/asio/detail/cstddef.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class cancellation_handler_base
{
public:
  virtual void call(cancellation_type_t) = 0;
  virtual std::pair<void*, std::size_t> destroy() BOOST_ASIO_NOEXCEPT = 0;

protected:
  ~cancellation_handler_base() {}
};

template <typename Handler>
class cancellation_handler
  : public cancellation_handler_base
{
public:
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename... Args>
  cancellation_handler(std::size_t size, BOOST_ASIO_MOVE_ARG(Args)... args)
    : handler_(BOOST_ASIO_MOVE_CAST(Args)(args)...),
      size_(size)
  {
  }
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  cancellation_handler(std::size_t size)
    : handler_(),
      size_(size)
  {
  }

#define BOOST_ASIO_PRIVATE_HANDLER_CTOR_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  cancellation_handler(std::size_t size, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    : handler_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)), \
      size_(size) \
  { \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_HANDLER_CTOR_DEF)
#undef BOOST_ASIO_PRIVATE_HANDLER_CTOR_DEF
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  void call(cancellation_type_t type)
  {
    handler_(type);
  }

  std::pair<void*, std::size_t> destroy() BOOST_ASIO_NOEXCEPT
  {
    std::pair<void*, std::size_t> mem(this, size_);
    this->cancellation_handler::~cancellation_handler();
    return mem;
  }

  Handler& handler() BOOST_ASIO_NOEXCEPT
  {
    return handler_;
  }

private:
  ~cancellation_handler()
  {
  }

  Handler handler_;
  std::size_t size_;
};

} // namespace detail

class cancellation_slot;

/// A cancellation signal with a single slot.
class cancellation_signal
{
public:
  BOOST_ASIO_CONSTEXPR cancellation_signal()
    : handler_(0)
  {
  }

  BOOST_ASIO_DECL ~cancellation_signal();

  /// Emits the signal and causes invocation of the slot's handler, if any.
  void emit(cancellation_type_t type)
  {
    if (handler_)
      handler_->call(type);
  }

  /// Returns the single slot associated with the signal.
  /**
   * The signal object must remain valid for as long the slot may be used.
   * Destruction of the signal invalidates the slot.
   */
  cancellation_slot slot() BOOST_ASIO_NOEXCEPT;

private:
  cancellation_signal(const cancellation_signal&) BOOST_ASIO_DELETED;
  cancellation_signal& operator=(const cancellation_signal&) BOOST_ASIO_DELETED;

  detail::cancellation_handler_base* handler_;
};

/// A slot associated with a cancellation signal.
class cancellation_slot
{
public:
  /// Creates a slot that is not connected to any cancellation signal.
  BOOST_ASIO_CONSTEXPR cancellation_slot()
    : handler_(0)
  {
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  /// Installs a handler into the slot, constructing the new object directly.
  /**
   * Destroys any existing handler in the slot, then installs the new handler,
   * constructing it with the supplied @c args.
   *
   * The handler is a function object to be called when the signal is emitted.
   * The signature of the handler must be
   * @code void handler(boost::asio::cancellation_type_t); @endcode
   *
   * @param args Arguments to be passed to the @c CancellationHandler object's
   * constructor.
   *
   * @returns A reference to the newly installed handler.
   *
   * @note Handlers installed into the slot via @c emplace are not required to
   * be copy constructible or move constructible.
   */
  template <typename CancellationHandler, typename... Args>
  CancellationHandler& emplace(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    typedef detail::cancellation_handler<CancellationHandler>
      cancellation_handler_type;
    auto_delete_helper del = { prepare_memory(
        sizeof(cancellation_handler_type),
        BOOST_ASIO_ALIGNOF(CancellationHandler)) };
    cancellation_handler_type* handler_obj =
      new (del.mem.first) cancellation_handler_type(
        del.mem.second, BOOST_ASIO_MOVE_CAST(Args)(args)...);
    del.mem.first = 0;
    *handler_ = handler_obj;
    return handler_obj->handler();
  }
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)
  template <typename CancellationHandler>
  CancellationHandler& emplace()
  {
    typedef detail::cancellation_handler<CancellationHandler>
      cancellation_handler_type;
    auto_delete_helper del = { prepare_memory(
        sizeof(cancellation_handler_type),
        BOOST_ASIO_ALIGNOF(CancellationHandler)) };
    cancellation_handler_type* handler_obj =
      new (del.mem.first) cancellation_handler_type(del.mem.second);
    del.mem.first = 0;
    *handler_ = handler_obj;
    return handler_obj->handler();
  }

#define BOOST_ASIO_PRIVATE_HANDLER_EMPLACE_DEF(n) \
  template <typename CancellationHandler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  CancellationHandler& emplace(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    typedef detail::cancellation_handler<CancellationHandler> \
      cancellation_handler_type; \
    auto_delete_helper del = { prepare_memory( \
        sizeof(cancellation_handler_type), \
        BOOST_ASIO_ALIGNOF(CancellationHandler)) }; \
    cancellation_handler_type* handler_obj = \
      new (del.mem.first) cancellation_handler_type( \
        del.mem.second, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    del.mem.first = 0; \
    *handler_ = handler_obj; \
    return handler_obj->handler(); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_HANDLER_EMPLACE_DEF)
#undef BOOST_ASIO_PRIVATE_HANDLER_EMPLACE_DEF
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  /// Installs a handler into the slot.
  /**
   * Destroys any existing handler in the slot, then installs the new handler,
   * constructing it as a decay-copy of the supplied handler.
   *
   * The handler is a function object to be called when the signal is emitted.
   * The signature of the handler must be
   * @code void handler(boost::asio::cancellation_type_t); @endcode
   *
   * @param handler The handler to be installed.
   *
   * @returns A reference to the newly installed handler.
   */
  template <typename CancellationHandler>
  typename decay<CancellationHandler>::type& assign(
      BOOST_ASIO_MOVE_ARG(CancellationHandler) handler)
  {
    return this->emplace<typename decay<CancellationHandler>::type>(
        BOOST_ASIO_MOVE_CAST(CancellationHandler)(handler));
  }

  /// Clears the slot.
  /**
   * Destroys any existing handler in the slot.
   */
  BOOST_ASIO_DECL void clear();

  /// Returns whether the slot is connected to a signal.
  BOOST_ASIO_CONSTEXPR bool is_connected() const BOOST_ASIO_NOEXCEPT
  {
    return handler_ != 0;
  }

  /// Returns whether the slot is connected and has an installed handler.
  BOOST_ASIO_CONSTEXPR bool has_handler() const BOOST_ASIO_NOEXCEPT
  {
    return handler_ != 0 && *handler_ != 0;
  }

  /// Compare two slots for equality.
  friend BOOST_ASIO_CONSTEXPR bool operator==(const cancellation_slot& lhs,
      const cancellation_slot& rhs) BOOST_ASIO_NOEXCEPT
  {
    return lhs.handler_ == rhs.handler_;
  }

  /// Compare two slots for inequality.
  friend BOOST_ASIO_CONSTEXPR bool operator!=(const cancellation_slot& lhs,
      const cancellation_slot& rhs) BOOST_ASIO_NOEXCEPT
  {
    return lhs.handler_ != rhs.handler_;
  }

private:
  friend class cancellation_signal;

  BOOST_ASIO_CONSTEXPR cancellation_slot(int,
      detail::cancellation_handler_base** handler)
    : handler_(handler)
  {
  }

  BOOST_ASIO_DECL std::pair<void*, std::size_t> prepare_memory(
      std::size_t size, std::size_t align);

  struct auto_delete_helper
  {
    std::pair<void*, std::size_t> mem;

    BOOST_ASIO_DECL ~auto_delete_helper();
  };

  detail::cancellation_handler_base** handler_;
};

inline cancellation_slot cancellation_signal::slot() BOOST_ASIO_NOEXCEPT
{
  return cancellation_slot(0, &handler_);
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/cancellation_signal.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_CANCELLATION_SIGNAL_HPP

/* cancellation_signal.hpp
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
*/