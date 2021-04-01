//
// ip/resolver_query_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/resolver_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_query_base class is used as a base for the
/// basic_resolver_query class templates to provide a common place to define
/// the flag constants.
class resolver_query_base : public resolver_base
{
protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_query_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

/* resolver_query_base.hpp
NwZQdmadkRzvXrdNRzDbNydFUF3tjti9d5aAdQfW1E1w2xwf2Iz3GCH5kXkjGGO1Hwy+zwCyFuwZrudgVziebNCvRn1LuQZpKW/Vvy8HQwktp9FsYVwMlJFk59v/OlubGF0YpatFS7YQLK4If26exRP6GapQ4g0h7Oav2GgLGino5Dy9TSgMST/hZZOvLazflTKHTiOFMYOpmYb/3rbeSaY5KPDTb+I3Zb1NKhEH19yAQZ7/Z+cQMQ7XeWVd7eaqKRK2NZWe29nIGBvm8uCx+Tw6VvCXQ+axY56EGe55gsNcxNGtTm67wJnJJRq5Feb8pP21aiQPz0VyWxIfHCvuiytjkPZR2E39HghO/Q0FqR/5p9FgBVQqW8dWr5nJ3tAjPHYnLrBlCbPd21eQfkBu5mU8OXJLlC6H4yr3Pp3+87OUvA4SAO8aQPcxPYnPgbhZzJ7xD1HcEBG2/heprP49sUTK01DkaKLFYobhpaW+LwY/99asPTWRYWCSub4AVtewnonwiNJfLu7OgyoM8T/I9gUMrAKdrs/csAt0q7e+U2/tDpcUBn5Ld5PjNw==
*/