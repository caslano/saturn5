//
// detail/event.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EVENT_HPP
#define BOOST_ASIO_DETAIL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_event.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_event.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_event.hpp>
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# include <boost/asio/detail/std_event.hpp>
#else
# error Only Windows, POSIX and std::condition_variable are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

#if !defined(BOOST_ASIO_HAS_THREADS)
typedef null_event event;
#elif defined(BOOST_ASIO_WINDOWS)
typedef win_event event;
#elif defined(BOOST_ASIO_HAS_PTHREADS)
typedef posix_event event;
#elif defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
typedef std_event event;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_EVENT_HPP

/* event.hpp
HLgG2p1KbZhinkpNoHqXTqX2tLbh3YqnUoMPp1I7jjmV7QEDJt/+xXPxDrrJ1Kw1RhY5mLPTg+E1ksFnero7Rp/Q5FAbCapyZnF1GamWzKoKmVXFzKpCZlXMLMfFOxQzqypmVsXMCmTmM2RW5TML+WS/jeqX1nw0sO253MeP9RXoRf5B1D/qsEPXaZGj02iX/ENAGXr+o3DdIER/duy66+V06nkCeTQWIjoydSt5gqMwJjn6iLpH8bpRTP0zAVPgaKYhDd55he/cBMiDhU9Icqg6DS49XuAtp+grP/ZcmdhhVnkHWbGDBCh3kJXvIH1zA8o9T+frZ4RQqPb1hbyV22mLud5cH8M/DNhUdCIyy5+WvitPS8eltRVexqiaQtZwknnl3g3HX2y/rU5TEaViIkzLhFEqYOhTnz3Hw4yq0rCk5haND8NDlJhWtlLJBwZ7C2kr0JqmxzTPXrPj6cIh9ISJB+TQQUfNG2PqQQkdqVEiy5QSRrdiv8lYTlsDbrg+uGZ6q0KiqixRVUwUqHVCMHAuGHAerJwXVTEvKp8XVciLyqXYF1vMJPsydbdeb0s3jE2E7FrgucGQQIeyJDwYx+D1kHU2y5v+k4Fqukxj1HTF4WmCNjLFNXZB0B8GBKiD4rrpe4MN9Ye+Aegb1+5WIBrBsbmC/jA4QB0c1w3f2H9Bf+gboPaNa38zEHXwHbbdoYduatGhaUmm4LQYJDXvJsY7ekJdFKXEBJVPLsVCsbAkENhhDb0rlpEdtOiQ/ma83JyXeloUio0cpntQyzw35eXx6XKPzTfTD3IIdUX5Cf0povB0ZGXwQohmK0h7vjRs2bFJbU7KBuFHz1YcH7ajPACSQF5nSW84wv0KXH/zFIcbLR+WqKQi9ukYaML22rGHjx89gNJ2CZXlOj3R8TEELP3e1r1dPYkXTp6YLhoffZhSjDqpE+IA6eMAkcVRa5T0mdt+t/5WPX5o5IjkYbf+Zltssfuum22RDtp2WAKQkLH26JCFcVWgFy0aRRpP6fHRA8eH21blWKtyrFUWK+q9ZZION7A2YCapP8mfVAfZh/o1j9kEmV+OTOUp1HsjZL7xEIw7DjrEkQxHJu2oPj+biq5w49l048h5sYXfqHNptXdTgmo4m+AYubuwdooBSBFPqnPcsKrqz4ewNH10tJOmo/nxQHBkuulo6OLR+V5SnNZlBjpetClJQm6ibMQOArnDblv3t91h5131bOucQm0M3lC86WVfiT+qOiynUfMyilUmF1QtUVeMGt+o+fDND5EB+Q2yY5A0vQRbJwvYXR+m1Sp910mOMYVPkSMLBcnGb+cgCt8e5yTesWdU1cTIif7oKGSCC6mfZpHQ2oyaSJKDF6VQOnoZc7Uq5EZVvn+V378q3b8K95f5d3uvi89qhd9tZ/sGGHbEaBFGaOltRi6UIXxgjxrklKriaC13Esgd+8As8JNqEjVA3jmc91QUsLci295jRW/sm3IRB8QYXzohe5EgiZ0JZbFDoTTrVHKRDnqzjIoyVPqjXRHV42xqaiOG+js149mUce3K8LCgAfnJ+Mjh0Y7JS9SVpm8KYFqTVxWiUjuQqnueZkcmoJaya4O8GUB6Myolmxzfd2eNJXrQJJREaXSbC5AnGcWsyQXMocUab9TYNZNj/+xppNRh9tQkI3GYa3VekN8i9t4UxS6cotiPRzk7c0p8jx55l1Wxb6eMHXxgOaagIHb/lNTdgqe1BUayOshzvg8H76oKcKgnZEMXSUF72vlwydly2qvWtLNLzOmY9iqmPXt+8am1G3t48vEhRd6+jPRsXbdJJQsto5DTZNzJHJHmzT3PfA6SajJOPZOuF95+652yMT7qbZM=
*/