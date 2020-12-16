//
// detail/handler_work.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_HANDLER_WORK_HPP
#define BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// A helper class template to allow completion handlers to be dispatched
// through either the new executors framework or the old invocaton hook. The
// primary template uses the new executors framework.
template <typename Handler,
    typename IoExecutor = system_executor, typename HandlerExecutor
      = typename associated_executor<Handler, IoExecutor>::type>
class handler_work
{
public:
  explicit handler_work(Handler& handler) BOOST_ASIO_NOEXCEPT
    : io_executor_(),
      executor_(boost::asio::get_associated_executor(handler, io_executor_))
  {
  }

  handler_work(Handler& handler, const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
    : io_executor_(io_ex),
      executor_(boost::asio::get_associated_executor(handler, io_executor_))
  {
  }

  static void start(Handler& handler) BOOST_ASIO_NOEXCEPT
  {
    HandlerExecutor ex(boost::asio::get_associated_executor(handler));
    ex.on_work_started();
  }

  static void start(Handler& handler,
      const IoExecutor& io_ex) BOOST_ASIO_NOEXCEPT
  {
    HandlerExecutor ex(boost::asio::get_associated_executor(handler, io_ex));
    ex.on_work_started();
    io_ex.on_work_started();
  }

  ~handler_work()
  {
    io_executor_.on_work_finished();
    executor_.on_work_finished();
  }

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(Function)(function),
        boost::asio::get_associated_allocator(handler));
  }

private:
  // Disallow copying and assignment.
  handler_work(const handler_work&);
  handler_work& operator=(const handler_work&);

  IoExecutor io_executor_;
  HandlerExecutor executor_;
};

// This specialisation dispatches a handler through the old invocation hook.
// The specialisation is not strictly required for correctness, as the
// system_executor will dispatch through the hook anyway. However, by doing
// this we avoid an extra copy of the handler.
template <typename Handler>
class handler_work<Handler, system_executor, system_executor>
{
public:
  explicit handler_work(Handler&) BOOST_ASIO_NOEXCEPT {}
  static void start(Handler&) BOOST_ASIO_NOEXCEPT {}
  ~handler_work() {}

  template <typename Function>
  void complete(Function& function, Handler& handler)
  {
    boost_asio_handler_invoke_helpers::invoke(function, handler);
  }

private:
  // Disallow copying and assignment.
  handler_work(const handler_work&);
  handler_work& operator=(const handler_work&);
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_HANDLER_WORK_HPP

/* handler_work.hpp
USjr8JWYqUv/8KwxV/fwFv/0junwA1iow3s85P3X4aOwTodHP+w96+jq9SUYpCsL29Jjj1iPzi1qS+ehrsNVrNThJVivwzMe9Q1munr9ewzV4SuR1+FbMVbnFrsuxjk3fAcm6vADmK7DCzFbh5/GAp0es4bH/XMxzxPuY4n16NKTjIk6vMdT9kqHx2CWDv8I83SFv/Yvf25+xTfC38fizq5eX/a0+9Xhe5A28oyeaUu3Y7rj4f9ilg5f8m9r0g3ut9S7anz4Ntypwzf+x3uiw3dhve5e1pbOQj/d62e9Gzp8JEbpsBcsFXV4S0zR4W7M0FXu+5zfH2vo5rnI6XD3836fdXhfjNXhUZioK9znBcQYLiFnT8o8Fz26xmes8E7q8EMv+q50eOOXrEFXeTmG6yZv8rJnrHN8ELp1gU9FXpf5BazV4fcb1tCnq9cdr3gPdXgHDNfh76Og67zPq9bn3PC617wbOrzNSu95rJmXY4hu8Dave3bOzfOFaOgefh9lnV3Vlk5GRVf489V+G2PMm23phLfsQzTv9rbfOF3k67Fah1/DOh1+Y41n2df9vtOW2t61fp3nizBah5dgnA63veeZ6vAAVHT4SczR4ZewOOZs+v1833V1ldehdeOuXu//gX3T4d0+tM86fCjG6fCkQDf43bXuXec/ssb/ukdd4z2/9N7q3Abt6SQs3qSr17diuQ5vu2F7auoSz0NOh1ejW4ffxWgdXoeiDg9raU9TdDiPig5PwRxd4w+w1BrCX2ttTyt0+NtYq8O/RZ8Yzwe3taf5usSXtDuedY/8p472NE2z79X8OlzDAl3eyHkYoMOnfsX6dfgsFHT4tyjpOr/Qpz3Vda6vNaOpw2nj9tT61a5efx0DdJH/gmG6xkM2aU9jdIFXY6wOn5xtTxN0+CpM1U3u+Wp7mqnDO2xq/Tp8BBbEnLzR19rTCJ3jKRils/3a07lYGufyQozZ1Pp5aFd7GqQrOfPs1J5WGlPfxb5ilONp1/b0nb3di+4Z2Z5ewljd5F33aU/jdYH/gAm6yh9gks7uaywm6xJfgakxDz+MmbEG/hAzdPxv7P0E03SZ78HsGMPv7O9+4/gB7emAUe4hmocfZK063PyuZ/016zmkPW1XaE8Nx4s/aE9bHt6elkT/2H0fYd+NqfN+Jf9YN85oT4edab90ePIvvR86PBNVnZ3iXs52XZ2fap1Yo0s8F2t1jd/Aeh3ud4719Ovq9RYYpPN8JIbrIj+PvE7ntqc9MUEX+CRM0iXe+DxrinP5GEzV4dmYpsOL4x/r8Ge4U4e3L7t3Hd4LK3WZ/4mxusH7/9rz3cx6eJPzrVvn+Vz00T3cdoH7Mj7Ho6d53+I4j7zQfuoqf4hROnzkRebX4dtR0uGFmK7DizFbZ6e3p0OwPNbAH6Ghcxe3p72R37yr16ditA7PRVE3ueO39keH85iqw5MxU4fPwzydndGetsJ684cPRqvj4bEYoKu8HN06XdqeTsHw6N+1pwuw1rk1fh2rYw088DK/a7qbj0ZTl/gapK+bkx9Hw/E6v4WM403eqOJ6sTbeHotjHj4YdV3gk1DTJb4Cw53bw09itG5w39+7f53jQ1HQRT4L3brMV2NcnMv3YYiu8fPoH/Pwp8jp9If29E1kY07+Hoo6fD5KOvwYpsf4y/3zMz2bmJNfQo9u8tNXeA919sr2dC369bcPvOJq72Rc90/tadPZ3jfHc/w3jI8xPOwa+6YLvAirY8y17elZLNbZP3suWK57+G1UdPxvZp6IWbrCy9GjmzzyOnsbc/JVmK5rnJ1j/brKzb/6BnX+BudhbJzL377RM/1GV68fRz8dXoFuHf4Co3T463Ptiy4=
*/