#ifndef BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP14_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
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
      namespace impl
      {
        template <char... Cs>
        struct any_of_c
        {
          typedef any_of_c type;

          static constexpr bool run(char c_)
          {
            const bool values[] = {(c_ == Cs)...};
            for (const bool* i = values; i != values + sizeof...(Cs); ++i)
            {
              if (*i)
              {
                return true;
              }
            }
            return false;
          }

          template <class Chr>
          struct apply : boost::mpl::bool_<any_of_c::run(Chr::type::value)> {};
        };

        template <>
        struct any_of_c<>
        {
          typedef any_of_c type;

          template <class>
          struct apply : boost::mpl::false_ {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
PoC/1gUT42NHjH/s8PGxbpI0k2ZOtdwYXkdywMzYDtTYU2Xy+ArdNeAPr5RyJJUyMVyQoDks8APfciONTdbh+w14wGk4caM1O5P04eSzSYM86tFhbGqWCcQMn1lG/r4WMT2wbMNyPQkBhkiH/a44weQ8SK+325P1xhbK1BmPtcgOgrBgJuIDY/qF7WQoZ5zbbuyVwJnxsa319jCpyvM9zQwj+CKHtaaTQWam7nQ6UxEYeD7X/djNoUmjAadM+ik=
*/