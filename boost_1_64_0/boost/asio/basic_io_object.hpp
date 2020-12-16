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
i9n+oplPwuHXdpEcNbWx8l0WOjum8slLozFe/AdLXPGUpp4NRNd1V5i9MuMOfChM0iy5i6UJbtuNpHEXf9PvxqG0yeIIrX+mx8R3NSDmkDYrtT8l8K7gehP08CstnLsErKAw3XxUz4pBTNYbBK72xs9jf0lT5S09uAh+ZkkXxUtlQjQxl64eqYNdgCsOnP7E7wdZw0XhPU5vHA1baxlm/Gw9JfdJY9hXTYFfvcwa73LqOnGOndqZiSDD0/yvUTLtSrvPeqq3Y/+KWJSeGQmxM/5U7PEeZrXX0N3SAodj1/mNw+a0sG4Ie+eWh4C3p7mYuTaWiJjy5MtCKLxjQTrRNlSluIBP3FRFTm72pKv7H0YFrcPZE4/RM1aVn+maReXXA9irS6thdFmLXrjvIslvX5nTk30YKuuJJzotpP7KhFXpmGGTXzMrFm6hetsWZtzuDJGdwmyIFaMLep5Y2P8ATfft2LJsa+QWdPFxZS8oTHQG23atgeTi/Lm68Hpo7nKghysSyS+2km9OkKOiXXaYZtdIWy45svuf1yE5pBYthQaQ3tgGe/0O+rzUnYssCKSfYfHsQHoAEs6JM1ftU/Rl+0w2aD2C8p4HMxfvEtyR1iVVbQfsTZmF3wfb6WaBMNm8qqMaPoHfavhHcsEWJLZ/NmV4FPA9v/RQ5X6OysPm0uuOieyCykO6YhzFFh9MwRD983xfpDmdLjnF1U5+xRmjNfSxp4IibpdQ/aHXlGFkxk3y1eGXfowFWYSSp08TWY4OpyWDWhSwbxi93X+Jpoz5jYUCx/M2byctefWFJ5r/gdZqbWR1uNPNT3uYXXcvhcjk0rKZ6dQ7V5anaKchwimS3Ys9Q7X2hfyuuz6m1U+B/BBjDAnuIZHOGhqadInJ1vThlsoN/iO0hHQ8HpB2z1EKWbSWDyqPJBmbWwInYAAbXXOebByCacXm8J0tjDFPLvMZsIPI+cdc9ZoCidktEHirHHT0JLIVW2VIb2Y2OSzoprtV5TQvxhrXwxXo5fHHmG4lhMsvNGHZsgb7NDbQhMqvuGEpSXnLQylO5iWpy2rQQ6vnNBjWDKtsWcFcKkaHYT9l7FdkRzQLSfT7ZwqVdkRQ5HHSqZxBpbudmAuGYq1QLjlKvYLbKBmKNLhM1WYCBrokDJpcn58yvEw2+1bC2jAGB59Usk1+M2kFTLFWPJPKB+VYTkIImuaO4af/a6PqP4e5z/ltODfvHmU/aUSpdADVVjiQ6uZM7j8gR1NW5THvK3souliGP4mtgGTWSuKlC2ir0VP68ewnLrufZx2xsWixfMdWebtTzoVPTI2UMGlmNlvl841SXj4mq4YqnLreyxpSVlB0exB70FMCnYidTG7vOAoZf4P7Py0j4/EuNDVsOM3MdMXKYy0wTchDcNUHpF0dg/FaJ6g6uhZDlDVxyCCUL/Tdje17WpFyvg17HzEki7iRoUIMk7cPxPz6IPRlRtLw5I98pf0VeC+JZpvkvMl9II19rVOmsZMEvcKwdfQn+xyTyn6GT0F5WDt2FAYWdfFRYqNpYsVRXnVYHclhobBwn08yz48whVgzen3tD5c9/QRFC1K56Y05UHLuZDsyulBXznCYz6EW0d2IpQZ632VMHqkFVKpqzotLzfHr6U5u02GAeI0eGnvCDv39j/n+Ya7UvruFvTf+i9f10kjra0fFjw6yHXiGrUY+tHeZKs7evcqdlRfCqV2S/9xVTWbX37OhQztgtcGEb1rcQsObWvki2U84qu7Exp5jSCr/Suo/opB5bAxGNCfT/LnE7O1vQmhdA4p29pJv43r2+6466R3v585DxbD5eB58Tlgh9MdHdiRXH59+6LLq/ERY5qhAZX8=
*/