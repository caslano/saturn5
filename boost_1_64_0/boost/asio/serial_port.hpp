//
// serial_port.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SERIAL_PORT_HPP
#define BOOST_ASIO_SERIAL_PORT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_serial_port.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of a serial port.
typedef basic_serial_port<> serial_port;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SERIAL_PORT_HPP

/* serial_port.hpp
5vteQ0y/bdxdhR0yq+9f42/jwEPyt/JUcnwO51jSRKc0ZpsbMw3K3pMCSQs9GVXN8aS510I4LK71VKkYgdPZ18YAhm5Z+4e9ZvtjZD+2Wq3PFn44uVbFj6jIqZn6zpnVtD2hvjPj2wtyzmx6/NRjurzNFyA+kT75CqQ/1Nea37pm8ls9a8/Gq2w76jMTP5cUl890y6/2ejivYAvJFQZTMLuYsodN8YW2gZzQuakickuw0MdN2jN+3/yS5OvMl5Pjb37+tOs4Jq+Z/EydHV9eO49rRh9k9p71B5ojpW/zRosa9+/8FYSf5gmHpXYg07NoLPlKZLoKJaywlAtkuohWMOWWztvhRnKxFOEnw/esf7nbvBn6uQX92/4meR/kha7x+7cbo1P/Zh7fzHr8+D3rX2fs/NbtdJQUFOchnr8pGHtCkMndL7BAg0r2rD0zX0d9u63JjRfu5rub3t8sjdHZ+uaEZu7DuxPch0d8v37W/c0uTM9wPN6e9Q938iOivE2BQ8Zsf4QTaPxNszud8BmOUuF4V0vHVY0nbB1X8NEtTaPvb8mnEwmaU5Hxx8GxogaSQRgkHm/GCx50sXtwQreY2StFr0FHPWaioxf5XI1qXk9YVVjAoGYNifrKGtd/1mr8NarAoh/DqUFRV9poUjjECj9/HAC+dMpU0NmDDYrT9JaDJyj7U76RqQbCWK6QVwtLL8o3yEZxRT01YWtZo6KYAo255KPueRneOZiJuhano82QPq3kXAjrP9jj6OMc9nZ7un8KQ03ib6BKJID1THLy48Oj6N7qnsmLPSu/ltBA2iUoIy4YmVz5EzmlbRdZr9ZdWpTOLb6m1293++KvF+d7m1m/YTzuuD0rrq/6LMb7ms1fu5rJb4Pv75GPwp0cCqoCSj0GHJfl8AIlfljw+zTp1+VKnPeVywcY57UQYBakB1RtkP7VP1vZA/6pD6rRuAz0Wxtsh0Nb1u/k5hwk4805uEuLvh9nVjK+wXlstcr7gcdrWT+BeX/3JIe9tKxE7p1BBkVrNTe9hIWO4911WS1q32hAg3sELe+X2mgAo6H9KNWGsrBBQPiiVOmBWQDP+YuKYR8VzMjQ5XGW382/TZFdFje+NaG6xe0lOASEZVMQVVcT3+PEq2Inqyxck7fKLHeq3XSJnfwmjSNfyO3z44V49MNuFF96NfziIKFS+KtEUM0t3tZ3iysZFJOcP0tz6zfmHEVl06AVSh15VnyBfQSs+GFtwcLjDTsjnTp34rNW0lsWRcDJlPCgou0GNWvrvpGFk/tAr6ppYofuNturjUD/CRtvEI/8IozBj+Dn9UA8qwfDF+eWOkrdRhSDrs8i9G1XU6PQIcDpuhKXG5sX5ZQbuAgCuj0aMifDs7wb0WvpHSrCV0FuPD3Es/B1UE52dxjxWL+JBUbtEJ+4/5DObWYgPtFdPqTr2l9mfyKdE6Kzb8Fx8cDlhIeahy3xuU0kxOMwEkYMrPklOtMjepy9L6OzNTjicS1vZIh4Jkslfhh0InwS93vdxrtGzK7hdN1Kz1Ac7BwvhwXDQ1MLGmE53o2m9eLSMRuOl7KF4YEBjTHL8dGIWL5yvCyvuyKEI9dCD4utAxzX09RC9nBLnMUuh1EjhtdUDC7fdfWH6e0aRCJe2vBHf1A8RJhVwR9OAUQ0pHi04FBFyP0qNWINgEIYkYYep/E4LBaGwteGA1JbVaxqjIc+9fgKtChsUPQL9rTosdIhSZ3KeAPpUEROgXsj8qV7j4L9olhEPwUXEaHoWmO8pXpx4oFElw/ZMDzUWy8qf4SKxxfd3zgDfwCUdMUjbTXhaLwnvvzAfRFd61LOFPhYlBL1VMV9f8yj0ROyHI92Gxg=
*/