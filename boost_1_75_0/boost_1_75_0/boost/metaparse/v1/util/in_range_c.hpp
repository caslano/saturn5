#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
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
      namespace util
      {
        template <class T, T LowerBound, T UpperBound>
        struct in_range_c
        {
          typedef in_range_c type;
        
          template <class Item>
          struct apply :
            boost::mpl::bool_<(
              LowerBound <= Item::type::value
              && Item::type::value <= UpperBound
            )>
          {};
        };
      }
    }
  }
}

#endif


/* in_range_c.hpp
PxAkcpw9y8O8nelhdcX1zWrOmGu72AX2xmHnBq9+GhEjP+oiLay7MgP12xqvezE5x7dyw7f24yK7QnqKTYmAXUjQ/ZlBoz7Zp3R+mNs59ude02azvbQxfabo+54FdraMYu0Wrbm2cfCHs5DCOfUgMHQyXzv9EA99J3JQFIWQc5+r8mASEaa5vtiRLfRQ0EfS45DTAzY1BQA+hL80zpOveLzuqm7iBS5cpvzmaEphLX7fRV0Lm33iM3h5yvYK0pYLhEC5IKDNfi75nAX5PXxC9/nmJzzqZPMoq2FndD+3JrrcfIeRYNEWyAdBckOghXVByVtM3vHCP06ln9kv/fYeXrSMZZ5/jjvQiu9CFbsPW5pei5EVy6Gxfx6IDrRaEE3H+Or9myAiVG1cCBNz+sD87j67tsQLniwFpFGxc5GjUVWQsL7uxLMinYmeRArr1Cv4pZo3+PPgBkqjGskfe2jTZSppo9dVBQHQr7BMeql8mNgEtJ0G8zeTctNMTD3ZrZmm2uLR1ynqJCQa0Ju6JHGmf2c4iZRACPQr1JKSA4NYwn99+YfZ2ZMjwlmKMYWPffebTI22Y9g/lo/PpCKG09dsrd5nsOvKkOPZrPSFIjJ0cqStlUoMMg3JIX98HmkNW7mLp+XiJiQ3ZbkQEjaaOZTCu0sk9wmpIvWK80GygQg7V6AUUDHAS5017zLPlLK/V9SSLg2bCz98jcBfCxWf
*/