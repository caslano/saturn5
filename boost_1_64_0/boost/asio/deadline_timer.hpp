//
// deadline_timer.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DEADLINE_TIMER_HPP
#define BOOST_ASIO_DEADLINE_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/socket_types.hpp> // Must come before posix_time.
#include <boost/asio/basic_deadline_timer.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of timer. Uses a UTC clock.
typedef basic_deadline_timer<boost::posix_time::ptime> deadline_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_DEADLINE_TIMER_HPP

/* deadline_timer.hpp
sMWRMqKrpU9MyWetcoVXTGiknWTRSDo2gA9jnXuNpoYpfx/WnU3snVM+0WyN/nwm/pqFYkS+nMfIa4CJcSexTgaEvGgx1JHoWUeEt7WnRpcHXQ1WbTyecKvrWe0DlddIiBPqmRusyRaWW0SR+XYFGpZUCbG6eWISIKFG6mXbQE+2jkiyd0ZljfNztR+xk+ZRnnlM1KIlhTYuI5oPEgaTqcJz0dLo3jacPsprX0MPuJQtqhPSfqNu/kyQsGL+/pOAfUDq0Vk8sNMU/KSZAcIHspQuYPJB1BmnkDq4sT7tY23OBsxB7/qHWK0gin7AV1EGu4rvELZWah+WnKr9riyXu1Mm9KQufXIe6Y1QGEHYt16KyLVmoR9ML5iE/vbbVJc2Yq5O7cPbRRpTrOkP8IMTcoPplMHqdiBNVIk43imQ1mXnNvVNQhD49CaAOyKb8Zu5S1HS4db5jqUurCLAvxXa1+rHyEnVXOuIrEfyQetfiT4bilVQE+8Mb63zOk8P95N0lQv8RAQbQWoUmnjhwM4RCmpohGICzfV8YiW0b+9RGCwnOKf3FpnQvjxe8A==
*/