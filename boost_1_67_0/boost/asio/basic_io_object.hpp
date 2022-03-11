//
// basic_io_object.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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