#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_SIZE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/int.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct size;

        template <char... Cs>
        struct size<string<Cs...>> : boost::mpl::int_<sizeof...(Cs)> {};
      }
    }
  }
}

#endif


/* size.hpp
jlG+rErbl/PSpYdusdKhcaoaTRhkxIi2HB0QHyZx/h9YevLP1nOtamePQ5cmuxxugG9BhDw7QGds19aAUipkP2dixZQdbY+04n0+D7uQ/7jWptwH+Lv/05hPwMcYjKVRPn4m7/VrZTMCSu031fKW3LmcYTLAApse95eWu7qk3aBlN8iMYJ1bXg3j70wETKAIejEG5Q95hxhmYdjw2kTQxzHaQP3maB1tAPWqOrxaNg9qiIXD8FOfMcB7zaBAiW8ULZj9TFgIAHOhg6eYUXqOKZd96W8Kj1XPiLm/ioPGzB4dt0XODKxHE2D1tUeoupxJkYhUeHFrwe386JDnPF4TgEn+v+tprwZbJjJluJQAsRqnOo8gwWiyP6rZQ8GKurOUDyzOsfIUkfjuISr8cT95elQFuNfvGgKJ5hUolp6X67j3bvZUwFHJfdwBkXz18kDakJ+aMtXCcP0BFlXFoNIQMSi73rb/dKScb0dQcF0NR6twc4hKTri73eQvc8CUBON9g6TiSbGWnpBru5fT+CKQxRy0rp7S/WYrMkxZXLpLz9D65Roo0ji0vF5BMQ==
*/