//
// detail/regex_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REGEX_FWD_HPP
#define BOOST_ASIO_DETAIL_REGEX_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(BOOST_ASIO_HAS_BOOST_REGEX)

#include <boost/regex_fwd.hpp>
#include <boost/regex/v4/match_flags.hpp>

namespace boost {

template <class BidiIterator>
struct sub_match;

template <class BidiIterator, class Allocator>
class match_results;

} // namespace boost

#endif // defined(BOOST_ASIO_HAS_BOOST_REGEX)

#endif // BOOST_ASIO_DETAIL_REGEX_FWD_HPP

/* regex_fwd.hpp
xw35CunThWK0qY5mZRcItVbaWMpXm4kHxKEiE57mscubrdJEsbORMBunlaLsjju8D+AQAaXADJPwbwlDL4ogC1y8YU2qJdewkjk4fpqVWjVBFQo7D19aUK1dDhttchHFx+xNDPyiRjZ7ULYpVjMMYWByg6RnGv0WTTIZqhec/2fxdZRpRbMtLMLTXuH83NpoLLMCHacxsOPFAla8GwL5wWhBFarvGhMomT6YwOmsZSOMFKvVQ8kyqYlaDMA2utI6oq2xMeUN5TTj489JBrNCJhoMraLJhncUiXhYjI55tOhb5a8+SSgK5v1WASp/IqC6y7958uQJ8An344up8ubR2+a/hVDu7FezJ8Ko8Ap7nOvv87eXb17l386ePP19HO3HK3xwGjNJ+buWiXlQeViUBZLqT/3oe4nAJOr71ew3v+Ta6rwRklyU9e7TY1cmb/7F13/NT/78VFbz8ff29jezb2ZPv83LX//216dpduuDNW6q+WE3JSRIg5mQ2XJDnyQrCKFHQhV17PhWxYA6VCzP2gmyoWgwX2v042mezPpE1/EIkTdH8ue6IdBPwSIMnGiOrhWghI4tf6esd+P9FuSTD6q9leAJdmXDrAbfuh+zOWL+utGUetNC6GDt8nmgw7N5vNcDaTMenvZFpM+k
*/