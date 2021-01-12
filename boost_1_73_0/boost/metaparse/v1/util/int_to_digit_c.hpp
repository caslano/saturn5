#ifndef BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_INT_TO_DIGIT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <int N>
        struct int_to_digit_c;

        template <> struct int_to_digit_c<0> : boost::mpl::char_<'0'> {};
        template <> struct int_to_digit_c<1> : boost::mpl::char_<'1'> {};
        template <> struct int_to_digit_c<2> : boost::mpl::char_<'2'> {};
        template <> struct int_to_digit_c<3> : boost::mpl::char_<'3'> {};
        template <> struct int_to_digit_c<4> : boost::mpl::char_<'4'> {};
        template <> struct int_to_digit_c<5> : boost::mpl::char_<'5'> {};
        template <> struct int_to_digit_c<6> : boost::mpl::char_<'6'> {};
        template <> struct int_to_digit_c<7> : boost::mpl::char_<'7'> {};
        template <> struct int_to_digit_c<8> : boost::mpl::char_<'8'> {};
        template <> struct int_to_digit_c<9> : boost::mpl::char_<'9'> {};
      }
    }
  }
}

#endif


/* int_to_digit_c.hpp
NRyG3XA49sUROA5HoW1+8i45+jmYXzjpcuFA9MBBWAQj0BcjsTFGoVrvSTK/bg7qva/MJxA7YT9U99f3ZLpGBOP++m+5qUesgDmxIubHSlgGK2MVrIKvYjWU8sj72fwGHZSnBuk8sCYORl+U8vCOtSyHg/LkzUZ50B3zYj6si/mxBRbAdlgQ/bAQKuXJrL5LbXvH2hPLEMrK8YNtgfqmfrA8BmFV7I++GIKNMBT9cQB2w3CM
*/