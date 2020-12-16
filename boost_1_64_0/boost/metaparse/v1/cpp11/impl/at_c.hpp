#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_AT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/fwd/string.hpp>

#include <boost/mpl/char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S, int N>
        struct at_c;

        template <char C, char... Cs, int N>
        struct at_c<string<C, Cs...>, N> : at_c<string<Cs...>, N - 1> {};

        template <char C, char... Cs>
        struct at_c<string<C, Cs...>, 0> : boost::mpl::char_<C> {};
      }
    }
  }
}

#endif


/* at_c.hpp
yrW7Z+DOhq6QP72Hsb0dd1WQlmlk+opqXvsYoWOL89bnGK+5nff9oX+i6zc/b61ebGtnvdjezndO2iGru5bg7qmkX50p6BK0Z05wz5Npe7Cn3T0nW7fU9RlwCOEM9mq3G7+O89slsb3DieFzY+f7ZvTu2OjOId8Z57wYaN8dqLMc+6fXCR9z7e7YfU6gyxBHdDo6cZcYNy5GHOHZtIMsr+CPOz6ets6XhWFRBsFQBuvLEdBk4J7wz51RPpb3EN7UOm4vCvvve2NM3CHafp8aE8+HnKMcW+4FXDeKd3l2Ubu4G1TNv5Un2x/qwH3k8aqOF6o6PkHF71PxY4Gdgfgn0G+ccfxXA4LxFDi76DdEvwH6jdDvMfRrc9Is9yaDNkKaHvr1Kzx7i1flfRb9tos8B/CTeR9QdRpQdcqodt2xDmf37Tog97F/rjZr+rwWeP5Kt4/NtLt3z+qFfddwyty9kwLTZeP0XkgJdFF54d7IyPx9Eos6I+RUIDHa3bPLdxFbPjqcRxwSOujASp/+O6p8u6S0MpB3pvcw4R9a6fLxyUI2TJqbxP58CTrrUvSBQ6IPXKb6wNPaVTrK++ntbtklxctnslxE6ELMlZUN92zRr3LI7zB0xnNFeTehLrK857ert3uJV9Kme4TyJ39ixB3RF2O8eokary6nMPzUs8xA/l/aLu+e+vEbVb4vC8YFkdc7V0aPCy/nfkf5aTwu95XMX+ctwA2YL6Mch7+vDunAmKNwJR2vYToIl3F0/V/HeMBheiTeG9rdudZx3B5IN7c93oz2GEO/R33R7+f2/fET3fq+zdXNlFrYFuCbHnu2w7a4Rsjb0MqIvYl2N7x+k0/ruyE7KMeR+/dE8Pm9opzVEfu572f5QvxcPn2QcbCHOxfnWsaxeSxbq952I5zrBM4pZcq6XpUVdfb2Y+3u2zk3qLfH5Dmhx0APfYLliOrJ+/Fajj7p0Ag8Vf6nwrzQxgqvhLw+I/EETp16I/VzjCfpgkxwfje3u2+lbiIZ57HKl88Z9A99N+tWyLo566L9sd2mZO1LTltCxhQPvsJ2CMWjTPq+4izwRL2F+zXQvpHfUg99Fn6jnc9mGfu6yrzH0u7ctUoVEvYcCBZzRZjPaWg66OfDiF+OffBtrh/SGFzXpvnu/PVDnly/75eb+8xHO2zjH6rxgGnS5VR7t7e775lv4XdUy7aDrv9PTHlVwd5VIjEQ70507+0e2GUshMS+psbQ15KOi8djDfDjExW3vQF7WCqOvvYhz+o5cbHBfrJQdiD+mKi0KNObGzeyO/S5rOMGY0ODklYdZxI3bvfu8ffBjsU+2J3EG4E7sGtg9Hw4CVJQfx8s+owmzYTIm5O/P9cXo3M4A8OjQ/4KcXQUv3Uj7LIu0VesnanCq0X4OvSlX9p+M72toSkxeTbxDe/zBbAS1djCjmkOYekmrCH8itOmtzX6ePc9gmFBfr8WeJQf3uriMoL8nidgQX6/2cwwyo9kd5nh/ebftPt3/E2Mdb3of1q+ZB0/+MO07iLPotujYWF4hTfivClWZ2GjtJzD4QeHONs8ft8kgDV452Af+rdSBx1lmz7d8YEwMOG+wRa4XJJvsPVOJcnDckbAqvGmDMLUR4ZmxunWvfvOy2iycDG/g1XjnZs6PJvL07pc+B7H76Pqo6uioeX8DSwivX0TqZ3vRv1RzAXujpD3GinvCF/nyMB043YjyuDRn9oBMyIP2KktgBnxBp/+HOBZ8YYv2VNDWJh2dVCGFW9+9w7lhvlN1oYwPz+8HQqYze/hkO+/tPu+LSgG4k1fWBs6xbQ74V7lhTp5ZLQ30bvz3PjouYEuBmzvyCh5lo/HrfdgxC1B3NA=
*/