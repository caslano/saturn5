//
// is_read_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_READ_BUFFERED_HPP
#define BOOST_ASIO_IS_READ_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_read_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_read_buffered_helper(buffered_read_stream<Stream>* s);

struct is_read_buffered_big_type { char data[10]; };
is_read_buffered_big_type is_read_buffered_helper(...);

} // namespace detail

/// The is_read_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of read data.
template <typename Stream>
class is_read_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// read data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_read_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_READ_BUFFERED_HPP

/* is_read_buffered.hpp
69BzAaWAOvrANEsYNYFsAhbK6HESBZ+aY5+xUAqjQpewT0qZK+thqbZg68OSBYTNWrl9oc06pyVY4At0yGSJyzoi7BHuxpri0Z4Xz+puH/cehkHfKGsufvtBMurVNsoVrERiSxCVTpO+B/Xts1aG1kFohfnjthZJuC3L2MXzr8A+dR6jqz+EL7NrlbJWau/IQ7iwBq00WSu1aXkYBvVWnufqN7Q8W+BSlDLSeUxfIhHSa9bKTGUiPkvyW0urRoyNg1Of/wB49sBBq5YnmyCHkiWEZPacZAlpG4W5QWCLbFFv1DbJHXk2e1qs3fDYA/U2CzCYH90GFXpsaMtSaCvlxZMM04YR7RZb7kZ7o6ywXdtyREsI+IahJXyzlMxHpQiDVbxj3HcV+9GN0PArm3XD1Zp1h2gWtUlOEW2SqE2zr9amsyvQ1i6/eVs6okmdIMxtDKxpg6IuZImi6m1aHWdFGdooIMI2tkgCytDaJ+UAQYPlKTlbaYJu8Ujapgyt/LRW/inijU9BUytYrNJEEpIhD+uEXNqKT7XSTK1oHpquEszUzT2e5OjERrpnzauJzlvf2FKfQKDb36UbShWkQZsXr4rdtjLEtfPYNfcZYHh2/dRCzkD/OdkwsAw8J05pBTZ1Q7gcO5VzrShnFZyh0AOFuc/kQwmBPqvyllFoJ7QFtoNgfacZ2bZgql7QyQfvQsvTzlp0mDx9Kw5ap5e3
*/