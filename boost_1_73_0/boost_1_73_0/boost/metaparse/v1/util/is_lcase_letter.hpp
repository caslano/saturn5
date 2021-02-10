#ifndef BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LCASE_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/in_range_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_lcase_letter : in_range_c<char, 'a', 'z'>::apply<C> {};

        template <>
        struct is_lcase_letter<boost::mpl::na>
        {
          typedef is_lcase_letter type;

          template <class C = boost::mpl::na>
          struct apply : is_lcase_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_lcase_letter.hpp
SwMECgAAAAgALWdKUnyk4r24AQAA5QIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMzc4VVQFAAG2SCRgXZJRb5swEMffLfEdTkx5S2qte9hUEbQpMC3SpDKgrbY3F45i1fgQdpry7Wc7pI36grHvf7/739mJRWMbYTBlidQdueUZ5yNNrUnZz7pgZV6XLOHvhwk/6dgnqHB6wWljZIssmXBUswu3wgrQ1PTYPG/jGU2cso6I2OA/CfdxT1n0DrNTErVdME3YOIEJcJdrR6c+7xItBgzOIPu9hk4qhKO0PR0s7EhbD8qkGclIK0mD1B67hoOR+gk2BJ0HOOCJkzQ0DEK3QKOXb2NNG4caD3bt/qRu1KHFOJi44Xz167aq98XNypUvbsuaj8L23Hv4/OXrN09X9MRbOmpFovVnrtBSwdVypmwYS8pGnBSsqnKX7Uuu5KO/Ba7J4qs01lyNKpDOZEe5yHXIZUZudvc4yW6GMHTRWZzA9ggeB70w8IioITY92ZglL0HrjUxkqSGVsrsqL0Fo0vNABxOx4kdVgWv2O76KYVR45dy704csYruHDHy/EcuL6j5i9d8ih33Eqv2/HM5Oo/BeLrZ/7vZ15P2/lWRJiIK/gG38cWAfHkuQnnOuL3KM
*/