//
// detail/null_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_reactor
  : public execution_context_service_base<null_reactor>
{
public:
  // Constructor.
  null_reactor(boost::asio::execution_context& ctx)
    : execution_context_service_base<null_reactor>(ctx)
  {
  }

  // Destructor.
  ~null_reactor()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // No-op because should never be called.
  void run(long /*usec*/, op_queue<scheduler_operation>& /*ops*/)
  {
  }

  // No-op.
  void interrupt()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

/* null_reactor.hpp
M886fDlW6PAP0NAt3t/0LnX84l9cE6ZNjf+vjet+wFw4Zomvx6xzh7/qP2CeDh+z1fF1iXsetE7iOLx8m3EaW/qr+4BNtlf4W9u9T2xv8eS/mQfnKvNrHjJm58rzd3Y45hT9sPWJpusNH/0Px9fhn6Otw49gkOOEux+xfnT4VIzVTV7W8h40hha/7lHr02fDp2GsDr/wmO8zHX4J83X1cWtqp/et41T4YWwyNvbPODRfOnwZ+nV4xi7X6LMtnrvbuv2I5uKTjqXD/8V0HU5P/Z+d84+Psq4D+AcZtGzUWbexDOWsScvADqU1DfSQMYcNvWANUnA3ths33Y+n7TaGQZ5KOHXomXNOBX02xja2AafSmgl2JREp1Gm0qLCuWrQU7FJa00b2/owHIS3rVVl/dI+vt+/3nj33PN/n+/zYVr1iO9qNZ73IdsxnAH/8MO9wnX88DKtox5EPyEdijI2Oxejf826hnbjqZa4j91gEn/4K9x7jUTdDFq1+FDx0DE/7Az9r9Lzw7D+yTzqMZw7z85cxqOte5ecCrb4XZtK213jfQh/bq3fDXlr9A4jR6nl/4h7lvEz8PAzqmPEFI5wj27jxKuhkn+qPHWOftPphOECreyFGq3dCAvtRPw3ptPPP/A0idhnQY+HPj7FLAtc6iK89zS6NdAjvhlydH3wI8ugYHj/WLjNpG54CWbQTZ0OSvrtwCdhpA6+FVXQQt0MDHcK7YQ0dwYegjI7h8Ql28dM2PAVm0k6cDcW0G5fADNrAa2EqHcTtMIkO4d2QS0fwIcijY3j8OMZM2/AUWEI7cTak0W5cAks4LwOvhWI6iDshQfeP3zueYzFXTrwQptIe/Dsw2V5d/S67hGj1fbCHVrdBlJZEu6x+N+dOR/G7T+d7S7lv8UqIXsNx8fchtGSyqH8LfbT64++xS4RWfwoGafVnYYQO4m1g0BE8PskuQfbpwNdAKscycQRstGOCnf/bUrs0s03gfXZ5GRyst9nssgLqdJ/4WahnmxhOO4Ox0S68HBrYxsB3go828fPQSMew7/12WU8H8YsQ5rO2DzD/EKPVFSBso26AVFr9Kjhp9Tg715cO4achwmej+DU4QEsy20I64zfwR1PYF+3Bz0y0i4s2Urm+kKnzjNshnQ7h3ZBDR/AhcNExPP6D7Je24SngoJ04GxJpNy4BoQ28FoavZv+4HVJ1/3g32OgIPgQ+OobHn2mXAG3DU8BDO3E2uGk3LoE62sBrwaCDuB0W0yH8LDg5xyge8yHOkQ7iR2Exrc6exP5p9eVQR9vOsst5kHQtx8XzIIF241o4yDYBvAkG6BDuh/10FE8/2y67aDcOwWE6gt83mXuSduMtkMY+I3iMg+eItuFpYKddOB969HrhWthBB3ATbKdNfOE53PMFbIPP+DDz6eGz+FXYq+s/wpyl8Q5hfRAnnstzSjtxCWSxjfrCKTzvtHoe+Gn1F6GejuAZH2UMtBu/CibtTOe+BmGfIfxbbdarAx9jPLR6HTjpCP4D5HGOcp5droQYbeCdEKQj+M9g0uryjzOPtPoLEKFNLFMZM+3AfwaDNqZxP0AWHcTtkEuH8G6YQUfwIZhJx/BZ5/N+0znBS2EJbeANkEeHcPQTvKNop9MuF0zn3OgA3gLNdBi/ACbtvIBzvZB3JW3gH0LSMo6FPz2D4xYyh3gz9Oln8Wc/yXVimwDuhRG2ieDLMriXaA/+HkTpGJ73KcbA9h78OPjoCL4gk/Ho/rEJITqM33MRzzXtwNshk+2jOOViri/rnfhBSGN9GGd+mvHocfF+KKNlpl2+BDbaxE9DczH7wafP4pkqYv/4CqhnvQffDjmsN/HT0Kfb49Mv4Vk=
*/