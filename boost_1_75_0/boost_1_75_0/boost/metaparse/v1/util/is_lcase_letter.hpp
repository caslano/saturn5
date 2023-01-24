#ifndef BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_lcase_letter : in_range_c<char, 'a', 'z'>::apply<C> {};

        template <>
        struct is_lcase_letter<boost::mpl::na>
        {
          typedef is_lcase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_lcase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_lcase_letter.hpp
VPyqBmGXuP8IRieF1GVNYtD8N9mkmhi5HyNgG0kL2ey60gRXGp7OZGXoeutUm05Tbj1G6pOQrqSj+xfCvCLRqDE6VZXWJ1WLO5OSchuhJo1yzsM7fp7XNpuTc83ejYaN79kPAIlE5DryWqboTux4rclR3JDl99/MLdzMQtTNzrKkkj6SkQFOnyFFON0Svb6kCB4mDs6e1OHdeW77V1rOP3h1JLjsGNlwKkbfaJpXtYbzuBU5WTV/UV5Gv9D4e+FQcRfSS+Zriy8QVceWuBMnOGdF46INF03EKyolfitXk2Z/0NomB7C8szhubrhfvZSNfHbULQ8LeIVd/3a72aMiI9gX+BOPfO7KOG7Wv0r95aL9c9fdJ/uqnhDBtsY3fHOxXi+FkgQDz/rfXllf3lGKVIyv4sP9LM71H4mYIplHsn8xqFX/dDZ6Lsm5lX4wDbndSfYx01z2Wcgvhs+JD193PuSa0BcuRrt3hNyKjq5KJjGpPv2oel1QOW4Qzs5FSPzwITohSjNxLVrUGPLaMURHSsCMMZeKyjD9esN3jdetjvPfV45mlULcymKaIjEJVQRU1T+sMln6yo4DUR2J3G0fP78gSJwRPNU/LoUsUS+TfAwIbSFr7F1lDFuiWPZeTQ1ZYlwmtN5Mt97Q+2LsUKjhna2G7DQQHQAuOjIdYqJ72D3GV7uovKy82UTR9/3J4ndb3eo4tIXtK+skcmDA
*/