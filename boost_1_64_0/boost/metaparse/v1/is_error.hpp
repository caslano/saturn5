#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
vxpxdJotkfAidj7hSUK2XSKRvx6UyOau8fW1/JD9vlUrkR8qJLJrs0Tcuwlxnc7KPvQJIav6E3LorxI54lrw015C3q4HLS4XuHa9QMhfF2NcL8OYPZO47xv/ZbgU9a+UyMseiRzZUyI+yNKgaxj8g98IPJ9mc75oGc+v+8Ls949H4+t9+EhCfjtaIr2eksh9nNf3nhtf7oVxhCzJlMge8Ni9LxufHblOIg8emUFahSQiT2CwgfcT92VyTyPuJUskMg88uxM6613e9h2/SOT9meDlL8GXw0X5ta0JaXd0BqnbIZG5P6P8LeJZ/nhx/v0c9jupB8N3xQjxrGIgu3f8aIn060RI7x/Zs4W1hDx/UAY5aBx4AfdDrTNYnR1EWztiPH/8vGk5nna8RFpPl8gFGRlk0RBCvlotyv70KiE1GySy+AiJrACtmjuunSaRvaeL6y+fZ3ikQ9l19VxCTptIyIVL2f3MScY27f6AXX9/n7j3XA/w7Hro4cMzyEvLJfL1Gok8/yF4+SlRZiLk7ZMFAteZYwk5tYVEPmjLrmvQLm28D2qaBrcCR+zxWlXTff31XeP13rXg1yqJHJffdB0FoGEr8IBcScgo6Bj3JbA/sBO3DxB0/bmfRIZeKZE3/87wrAcfZU1LwP+cRjva4BkvO20nu7flFEL83L681l4iX/aSyN3/lMhN4LsZLaHD+mWQ636SSOWhxvEMgaajemWQq9+DbvDChn0k6v31fvZ7zQ52r+gd6JyeAv7x5yDn5RLZmgn9lyuR7Xg+MkiIu4SVvxI8lgs+6h5PZyEnIyFTExM/P5rTO8x5as8p8eXmHwb6/imRq/pkkJugIwOXSeRvKzE2N8A2fgs9RjJIxsEM7gnQqvN7EhksdHLcMWgQbNA54EvQ807oWgWw3btLZG1QIhfPl0g57ldBb/pdAuaXOnH+UxkhX3hAU5WQ5XOgVzFO92VmkB1nYMzbw1aDlkoNIQMfI+SsiyTS+ROJPHITIT8eA7omOZ65A7LxNEl6rOnbNK6vJsC+Hyyud74tkZU9jeXf/5TXtw71gQe+vRI0wRg/CT9hNOgr/SCR80fqxqkz5P17RuM3Yd9vxXi+9xHk9lxCFv8lkQHA9/Jpovzv90KvXCeRhT0I2YAx/QN9qoHNaAde7QR764L/MQt9yBpDiC8AHQP/oEch6tllHP9Ph7HrI35g1x99TlI6bixF/+6RyHeHJR+L9WjXSYdDvu6Jf3aVEs+ntYP4M/gAt74rnt/SGvV9YixbBzld8wMr87zOL94+O7GcnAR90QP6ZCvoSo+73pLI+Cz2rD33i/45AD4Q7OZUr0S+nQX7Pxn6v1sGWVABP+c3QoqPI0T9FPBHEDIYvsi+PQzXoQslckM+fJJXjXVXjpHIQZDzUE9CPkFdc2fBxp0vkZOfga6Hzr3iakLehW3ZovPFRj4X3/biJmT/4d7Jx4Aeq36Ov3f+mxLxwv++5mxC+lwskQe6wV+/TdTT6xJR9pG14n77T2PaArm99BF26nLwWKMG/hL+tmH8fWhiZIZEei8Bz9dJ5Lw1DL6kNfgefumcmyUSaZG4H+MPI+TuRaz8pNu4Lv6JkOlvsnurTxZteU/nCx+la+/9Dez87n9wHxe+X5tDWH2FV8H/2s7jls7s3raLBZ7zVsOHng0dzXVBlxMlck5vidTmSGQTeGYs9NiyY0VdF0LGT3xNIjdzn2jEUQznX60I2dobzw410m5DL/w3jt0b2j2DVIYl0hO6ZlGPeHr474Bu/RZ89qQRx9u3S6Rb1wwSmg4b8zB81XPgB+vk7duhfEwuMMJ1PEycd4iJ9d46BHpCp/9c8NG2bWo+3lnpE+f3OeA=
*/