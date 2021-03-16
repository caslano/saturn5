#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
Ny07NLMyVYRPzqvKSwsNzKxZPgav0YWqUCpJzslNS63rWK9AshKYOT0tVcyIW5ublgbVEHWxmMKLIJkWmvlm1pp4LJmsHU3yPUphl79PqWOp4rijVdEU+N+p4pVHq6Ip8JtUMWRU0c0vBKUX2IVVnFAfMyazZj++3xYuce1DcC0jBBczREUws6buBqx7PrQ6WbY6AxsVlI3KNxuVVtfFFQYVdaxXWKkoDWuTQd+gsDTWRbrSRbrURTroImToAp0=
*/