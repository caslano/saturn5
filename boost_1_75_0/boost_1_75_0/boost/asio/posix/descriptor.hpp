//
// posix/descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of basic_descriptor.
typedef basic_descriptor<> descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_HPP

/* descriptor.hpp
UMTXNNaN2oy/gGtOZsdH6oeRHL4X0+g1BMdJBw58FN1cMEEQZ2s/nmgSax+SjOssCK2apGIFJ0nU0u5Ff5Sv+xPMn59tXb68rgljd5D/zqKof4mLnJhFJ4fXZ4ww/Ftn/qyTM/XviG6n3YyIs6Lsv361JREO1jvtaYwQBbuTdE+DPB/5lzY1tlqGaf78pkZ7h5A1adYf1VSzklbc6gplsZsVyh/mCBsbBEXNy3ig11wyDvvxYNzeOK6fBn1aZIK5/Rk6SidTHGGPw6eSbHC03GnXkN9f5sVtjq2W9tfFTlUa1FKn2Sb/fukINMRoTPGbyfptjPmCumn99hJR+fEo4YRYzpyOzwj1FDY1DuO8rWmzA1evlPyd7XK0OplrL07mXkwRF3w3n30Zb9ebx40FXsJAN3wDzHgegBkPCP+e6taFv93vdKeD3M2nmx181Ab9kOLD7IMJ5mIhZcssd4g27fKRtYeBtdF3suVRoWmp6366A9VaMb5UvZjWzhL0kn9MtDmso9jKOgtcJ8Gm3US7iexveKygD9cwa6Gaa3h84VCuIYN9kGuYB01NqI+Wa+AerAE/p22p03dcH47JtffjtD5oKxeq5M0xzatk0LetV8nCX91Vya+n26wSzZV/Y5X87iOMpojsd4s2XxIPKcCgOEQjrm9Q7hoOkW3I9kQihVH6W6Px4IyMr9L3xyyg8ENPt174JTY7eRWqpW2H
*/