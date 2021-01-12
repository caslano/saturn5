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
chFv5wO8g69xEd/k3XyP9/Ij3s+P+QA38kHuJI2Pcnc+xj24mA25hG24lJ34DDvzeR7DFziQL3I4X+JILuNYvsxc/pln8lWezb/wIr7J3/Nt3sHVfIDv8Bm+y+e4hsv4IcvJ379zZ37M3fgJq/NTpvBz1uMXbMKv2Ynf8ER+y8H8nsP4E0+jV4tTs1meE1mBV7Ei57ASY33FiVi5h1AOIoW7iSlhR9vZ/GpzF/6WFdmYldiM
*/