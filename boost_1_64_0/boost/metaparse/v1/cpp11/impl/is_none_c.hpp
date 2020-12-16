#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_IS_NONE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/is_none_c_impl.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <char... Cs>
        struct is_none_c
        {
          typedef is_none_c type;

          template <class C>
          struct apply : is_none_c_impl<C::type::value, Cs...> {};
        };
      }
    }
  }
}

#endif


/* is_none_c.hpp
NiUHg7TnlE+bIKshm8gXi+lEbuxAatwvfA6U+5ZpmzuJZvopWYFfUPQffDv95xcs/zb9zyH/vxT9h+D8Zp7qP78pk/4upHfidH+BnP0KcvZb9Inf6TxZxrlOQsb/2CHxmPaouLuUjB9B2XezjAPflfHXQ8Z/atP78vyzCuTZnKP8vcXTjUp5kKz/wcj63Egr8/domSdZ/lO0LFt5OpZk+M9Sho9Snnrml2tX1zsQzsO00b1C7u5VcnefaGMT91fIzd+E3N0r5O4fSu7+WSb9v5Bex7EuZrn7O9r+fuhgr1Oli5C7ey0dwOuUeEx7VNy/lNxVd/plHxOUWQ18JXev0LrVrN1SGoftkKUlBL/UjbBytIzgSncSbmW6c3lntLz1QN5qOoW8HYWM3CHWtL/Ae5X0zW2/otNt+weLdjJ4x1HYtP1DQIuO02O0TvedcnF6/Da+gAlu/tbi70r8XdWJOgj5WNMp8vLK0qdljOrL9+BW1vp4Jyq8/nLrc0XBavvGpLUkoyKsLQnZAy2u7H2QZO/YNUQLwc2Yvpr+ujJH+60EUzrKOwH1vJSRLXwdwakob3YKPmnJEj7JwhJ9hlAjlydUKJcnl5HLFozlD5VyWaGNusB4njS7epBnhFxZfhjaDd+OvnuEkFkT93DIXh3oJDxKwzK/Ucn8KWXSb0J6HcdyreOi7dIN0Een0l9T3mbI9SN1ua4coq4s81s7JR7XLyIOtLNOfBRoOJ11IvBduXxxhL25hXDCZoE+PA36EECrC8+I0IWnVShzZ84jcw8imTtLylyFcjO4gMzl88nD5rXyBJ58DLLREXK+tE3I4TYlh2eL9jRxDZCV7UIOtwk5bFRy+Jgy6ZuQXsVFjruPRjs3Q8ZadJ4RMrZNyFh7p8Rj2qPimpSMdaDsTpYx4LsydrUvYyR/PO620ndko9zjy1tbIG8aAXOYrgjZa6tQ9rrLyN4gxuEeKXv/ofz8FOMwvh35iYm2MnF9aP9+lh9Kw/KzU8nPQJn05yC9juOxW8dF67EdaN9zocd2QcZ2o1yTln56nqTz1vJH6Vj+Htsp8bjuUXHnKPkbAX1xlj/gLzynHiQcMbG0c5ChzoXnIEY2h61scmIjj6MR8jhcoTzuWWD83SvlscI5cUuUTbOINdp9nTgrHZ3P8G4cO6QPY/uUuyNYSJA7qNEB62JjZ5rYQyfeDysCFkIK322+UOjSi0DfpcFZRMujGVU/ecaM9lfMccQk+ceY6EkWUv6ZtAsoXQ1ZUbT/Ic5G842w4EzL4whvnTdjaRQFHNmLtw0e3ynXUIMqmXJUEpxqmQfB1DfaD/sDkK/h4xMEH5OdvBY/1sl7A8G5wHFbL6vhhiYjci1QPsFe+YTgQdVcWrtNJoJKHWXpa3DeapieoBNMHr91MCPC9l6kDW/GOvakKH9FhIwuM5rTG7b1nkK9z4y0GcJNJ9u7whD6xoFOnlsdELzMKP08LfSzwbsY+jnr04m8WBfOdAo8z8XLiHlMCfnllW41cfUcJ/PA/CcqnaJxEXOjkC88N1IRem6EMpR+/gXmRmmCm3lQrlO0AOZGT5yrX70CwaaShamEueQDWFHitXtzYBsEbCxFh63h56lEYbyTFYbzydkEw1Z7B4O5GBNn512zct5F+vxQGX1uZG0F6fPDiDcyuGIeWTunMh1QUb8ysvokIatPhvxPOufhC7T9QTdOhC6s1roQ8BqjT8NyOO4ptk4ziri7w/O7l4o+WvsAjg/SD7tZimxx3k1J7MkG7t4mBsO71Zeh3WQM1SN8G+9pgtaao5D5gwvyNqfv31A54xM4Bm1h51t+6nGNx6TaecakZwj61zCvc+SiiW4gDNmVSuM=
*/