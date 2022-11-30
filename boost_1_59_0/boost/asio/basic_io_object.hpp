//
// basic_io_object.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_IO_OBJECT_HPP
#define BOOST_ASIO_BASIC_IO_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_MOVE)
namespace detail
{
  // Type trait used to determine whether a service supports move.
  template <typename IoObjectService>
  class service_has_move
  {
  private:
    typedef IoObjectService service_type;
    typedef typename service_type::implementation_type implementation_type;

    template <typename T, typename U>
    static auto asio_service_has_move_eval(T* t, U* u)
      -> decltype(t->move_construct(*u, *u), char());
    static char (&asio_service_has_move_eval(...))[2];

  public:
    static const bool value =
      sizeof(asio_service_has_move_eval(
        static_cast<service_type*>(0),
        static_cast<implementation_type*>(0))) == 1;
  };
}
#endif // defined(BOOST_ASIO_HAS_MOVE)

/// Base class for all I/O objects.
/**
 * @note All I/O objects are non-copyable. However, when using C++0x, certain
 * I/O objects do support move construction and move assignment.
 */
#if !defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
template <typename IoObjectService>
#else
template <typename IoObjectService,
    bool Movable = detail::service_has_move<IoObjectService>::value>
#endif
class basic_io_object
{
public:
  /// The type of the service that will be used to provide I/O operations.
  typedef IoObjectService service_type;

  /// The underlying implementation type of I/O object.
  typedef typename service_type::implementation_type implementation_type;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use get_executor().) Get the io_context associated with the
  /// object.
  /**
   * This function may be used to obtain the io_context object that the I/O
   * object uses to dispatch handlers for asynchronous operations.
   *
   * @return A reference to the io_context object that the I/O object will use
   * to dispatch handlers. Ownership is not transferred to the caller.
   */
  boost::asio::io_context& get_io_context()
  {
    return service_.get_io_context();
  }

  /// (Deprecated: Use get_executor().) Get the io_context associated with the
  /// object.
  /**
   * This function may be used to obtain the io_context object that the I/O
   * object uses to dispatch handlers for asynchronous operations.
   *
   * @return A reference to the io_context object that the I/O object will use
   * to dispatch handlers. Ownership is not transferred to the caller.
   */
  boost::asio::io_context& get_io_service()
  {
    return service_.get_io_context();
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// The type of the executor associated with the object.
  typedef boost::asio::io_context::executor_type executor_type;

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return service_.get_io_context().get_executor();
  }

protected:
  /// Construct a basic_io_object.
  /**
   * Performs:
   * @code get_service().construct(get_implementation()); @endcode
   */
  explicit basic_io_object(boost::asio::io_context& io_context)
    : service_(boost::asio::use_service<IoObjectService>(io_context))
  {
    service_.construct(implementation_);
  }

#if defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_io_object.
  /**
   * Performs:
   * @code get_service().move_construct(
   *     get_implementation(), other.get_implementation()); @endcode
   *
   * @note Available only for services that support movability,
   */
  basic_io_object(basic_io_object&& other);

  /// Move-assign a basic_io_object.
  /**
   * Performs:
   * @code get_service().move_assign(get_implementation(),
   *     other.get_service(), other.get_implementation()); @endcode
   *
   * @note Available only for services that support movability,
   */
  basic_io_object& operator=(basic_io_object&& other);

  /// Perform a converting move-construction of a basic_io_object.
  template <typename IoObjectService1>
  basic_io_object(IoObjectService1& other_service,
      typename IoObjectService1::implementation_type& other_implementation);
#endif // defined(GENERATING_DOCUMENTATION)

  /// Protected destructor to prevent deletion through this type.
  /**
   * Performs:
   * @code get_service().destroy(get_implementation()); @endcode
   */
  ~basic_io_object()
  {
    service_.destroy(implementation_);
  }

  /// Get the service associated with the I/O object.
  service_type& get_service()
  {
    return service_;
  }

  /// Get the service associated with the I/O object.
  const service_type& get_service() const
  {
    return service_;
  }

  /// Get the underlying implementation of the I/O object.
  implementation_type& get_implementation()
  {
    return implementation_;
  }

  /// Get the underlying implementation of the I/O object.
  const implementation_type& get_implementation() const
  {
    return implementation_;
  }

private:
  basic_io_object(const basic_io_object&);
  basic_io_object& operator=(const basic_io_object&);

  // The service associated with the I/O object.
  service_type& service_;

  /// The underlying implementation of the I/O object.
  implementation_type implementation_;
};

#if defined(BOOST_ASIO_HAS_MOVE)
// Specialisation for movable objects.
template <typename IoObjectService>
class basic_io_object<IoObjectService, true>
{
public:
  typedef IoObjectService service_type;
  typedef typename service_type::implementation_type implementation_type;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  boost::asio::io_context& get_io_context()
  {
    return service_->get_io_context();
  }

  boost::asio::io_context& get_io_service()
  {
    return service_->get_io_context();
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  typedef boost::asio::io_context::executor_type executor_type;

  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return service_->get_io_context().get_executor();
  }

protected:
  explicit basic_io_object(boost::asio::io_context& io_context)
    : service_(&boost::asio::use_service<IoObjectService>(io_context))
  {
    service_->construct(implementation_);
  }

  basic_io_object(basic_io_object&& other)
    : service_(&other.get_service())
  {
    service_->move_construct(implementation_, other.implementation_);
  }

  template <typename IoObjectService1>
  basic_io_object(IoObjectService1& other_service,
      typename IoObjectService1::implementation_type& other_implementation)
    : service_(&boost::asio::use_service<IoObjectService>(
          other_service.get_io_context()))
  {
    service_->converting_move_construct(implementation_,
        other_service, other_implementation);
  }

  ~basic_io_object()
  {
    service_->destroy(implementation_);
  }

  basic_io_object& operator=(basic_io_object&& other)
  {
    service_->move_assign(implementation_,
        *other.service_, other.implementation_);
    service_ = other.service_;
    return *this;
  }

  service_type& get_service()
  {
    return *service_;
  }

  const service_type& get_service() const
  {
    return *service_;
  }

  implementation_type& get_implementation()
  {
    return implementation_;
  }

  const implementation_type& get_implementation() const
  {
    return implementation_;
  }

private:
  basic_io_object(const basic_io_object&);
  void operator=(const basic_io_object&);

  IoObjectService* service_;
  implementation_type implementation_;
};
#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_IO_OBJECT_HPP

/* basic_io_object.hpp
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
*/