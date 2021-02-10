#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_char_except_c :
        accept_when<
          one_char,
          impl::is_none_c<Cs...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except_c.hpp
jQo4pq4A5+Kcx5A1nLNBOd3YZaCpnbqrciCbAtSL/tpqELxZjl+TcV6JgVMiVzJBMzOBF/m3D3hx+s7jW5fmiBflmgOzfH5qi+A7EfIUMSbITibVpo0T/fjqE1/YJ25nyA3aJ45Qi4IZIUb1MbMDNMwOUMJQXg5T9GJjkxFho77rUUQzYErnZGQAgZq7kk/z0upXCqaY0Ie9tlr5yYRCsEwBif0suqbSieRBusCbEsmFjHFCK4or64Rd7DCFfHHC72JKtyuljAnNZbNslqzkZGSL8iYzu+KVrehLwvtiepdQv5JNHrHfaOx3zNz29emON/Kz07hn4YEsCTs1VciQvlD/W5lagrpMNtYmmlCP4MjDDXFzGsKqQgi1vGLECp+4diAJkGV1YlOtzCghFO83+7IHiyoZCZPYHpuCwZygWNiN4kJG6mvXOL1Zgighb1HwJHaJOla2FcDFYRfhNTlFJXglgAm1kDmaupOxFFwE0eEiiJ/P4III9LqjSyhk8Hq1o3PnT2FHWSGVVxbkQ4uK82auOL8ArF9tZ/yJErUEzmQVQ0xpwmll8/Bslj19jRWp3h85VsSKo5qh5LuCJG2eCB9Q1Zkqf4jNUsaq5mFq1hImTEIqL53eqEo2tRw96MrhA8Lpkji7FYdmQuwq
*/