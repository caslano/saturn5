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
TUO+BmHS110K/xN9xtTjZ9+F3LUieJ+r/vcyoHvOA9FfyJyoPQh+PewtsgrLgulznV5n2XbEdJx0G0ZPHkOQRXuybfKVTRdmqU25B0CpklkzT5TKjtvxqdR69AHMae5Z6kzdB7qyWXdaAeGzyeDFCaYlvQ3iy5Y0f/DSrMtEfHKIS8Qi3fUnbggJJGnUyfsbGwxIhIgLPdSgHKUCkHI7zednPAxGTFd43lu8njXY1+XD1pgHuL83YFalN1fcR5312uHTx//HNzy7vaT5RK94iIhNG1c0q7G/ZkNJT27uPzU5aV6FGfgChQbFB95WxEDX7a4B0UPGmLAwEclCU8Jb3aB7nbjgaLAJHKSpgECjgJ0aFFs66m6RqlGXwKn2P2xN62UeKW72nDrd/UlTSjdhKak9rTb3lyercsA91qSoooPLlGg52L34EkBIrZaxf+X2AqEbkwYnkIJ6ic6nOud28r8RD5Ba8QwoyyRtKH5W1b4qNgcu2kNYL+FZWv4kpnWdIzAf/quJO/AeWPkQplUCH6AxYpHUOy0IjwBTzlC6N5xbanwfX/BGbniZSA==
*/