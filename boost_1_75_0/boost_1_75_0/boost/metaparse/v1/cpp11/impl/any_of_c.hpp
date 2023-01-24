#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_ANY_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/or_c.hpp>

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

          template <class Chr>
          struct apply : or_c<(Chr::type::value == Cs)...> {};
        };
      }
    }
  }
}

#endif


/* any_of_c.hpp
1tKC6vkv90/hKsHrSpBYupvn9va+g2eR+kedjAM+5d0iW0NATfdpmwdiZvlNts9zf0VilUPj8Y72q5fkxYYqjbYuvRG2RKoPBnj7STiaa3W82OR+nady9yRUh/Ti9inFPmycNGULvJQeRIdEmzc6QkQ61Ajr8Pb3WUYQCaq7Z2gyz5FMM7eO6br691rzIK/ExDp46Obv8ioaLKNPnVSsFe0FJr4PPFzIYTHSFP6EkbjjYS2AjUAheAH3WngBc3ABfeqU4y5g/qf5OiDBJT61LK/cG5mwcHQoVW+MufVm4NzTF/KqbKRVycZV2ehumtcHyO9GkoLT4Bw9yYkqjTOvtFpsrTFbpDFFb3b/Ovc1dbLVi1ZU5qcAOK/uYr6pxmJE/93iideOuS7xnM1MyD1Uiv7PERM4JahpZKeVtiAIVWSBZ59oNGGwsXw6+WaiSONTuNw40OxiC+oZ86iuqC8K7Iw25xgz2isQPeFhpAKDrjJ0POGBb+FZwsShuoTOwvn4GGAVtgRkoREbK/BRIR3cdygnaeOB6JB3/1TSnX5aYiVGqpgHRPxOCYnSGbLR6cgSZoCKTQao2GIEUMbswK4xGEsQjLfstBhVMI8HQzO+fLpDeMhnFO6yAYgaoNVS4+zVMDSOzxwNTrJhR4hOkvsGa3E/xtgmD55spbLh2FFjOHagGUWbIVwvhVc7Ejl82ihHk9G400b+0JYacg0B
*/