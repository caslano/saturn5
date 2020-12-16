///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_UTYPE_HELPER_HPP
#define BOOST_MP_UTYPE_HELPER_HPP

#include <limits>
#include <boost/cstdint.hpp>

namespace boost {
namespace multiprecision {
namespace detail {
template <const unsigned>
struct utype_helper
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<0U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<1U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<2U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<3U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<4U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<5U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<6U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<7U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<8U>
{
   typedef boost::uint8_t exact;
};

template <>
struct utype_helper<9U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<10U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<11U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<12U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<13U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<14U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<15U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<16U>
{
   typedef boost::uint16_t exact;
};

template <>
struct utype_helper<17U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<18U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<19U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<20U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<21U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<22U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<23U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<24U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<25U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<26U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<27U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<28U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<29U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<30U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<31U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<32U>
{
   typedef boost::uint32_t exact;
};

template <>
struct utype_helper<33U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<34U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<35U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<36U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<37U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<38U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<39U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<40U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<41U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<42U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<43U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<44U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<45U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<46U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<47U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<48U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<49U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<50U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<51U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<52U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<53U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<54U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<55U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<56U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<57U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<58U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<59U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<60U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<61U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<62U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<63U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<64U>
{
   typedef boost::uint64_t exact;
};

template <class unsigned_type>
int utype_prior(unsigned_type ui)
{
   // TBD: Implement a templated binary search for this.
   int priority_bit;

   unsigned_type priority_mask = unsigned_type(unsigned_type(1U) << (std::numeric_limits<unsigned_type>::digits - 1));

   for (priority_bit = std::numeric_limits<unsigned_type>::digits - 1; priority_bit >= 0; --priority_bit)
   {
      if (unsigned_type(priority_mask & ui) != unsigned_type(0U))
      {
         break;
      }

      priority_mask >>= 1;
   }

   return priority_bit;
}

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_UTYPE_HELPER_HPP

/* utype_helper.hpp
V9+3gqcpKl3fDoPyTtNE91oX7K6+oIj8OHblzL86Yzxpq3alMO6V9KLE83OrMQBqthVrdD8MtxfanpXEcTV9UHO7tmpXDHt56BeWHzrNL0rTHu3dKoz+jGUFrpVlDd9XLxqYimI651rw8aJlR15Sv3PTP40bHQ+fXu4ab5wx26mIYzvzw6Bot13n9pHDz6vTQLbHSn5W0E5dO/UK3facGhco27tKvl7p5EXgeE7Lu50zDkRkaoVuS8drt8XgjmJuO/Tle4mebnt2trLtqO9dWvLvnR+Xvu2LKM95H6cs+fxB4ttRUjLVi/V336Gz6LrMZOGFpVsmqSiCo3Q/xCKd4eNxT0Pbiu2Sua1rrrltlOyt87wokjKB8plH6bQqn9RH4/EvLdsOojDSDfRXXsznEM6Wxh5kN0tsJ6cL9rC3MzN4J32K7qfjthzfTqwycHgZWOB7bC+W5hsX2A9ICqG6VFPS0tTySbpmj/qU6lv3pdJYr469yC+K0iz40P423jm5rsuWwi2s0MtLu75Tj6eU9pUZ9rIkTqPSixv2YNBh7r/Y8UxjL1ToWXaZWc30qj40t/1YJm+L1La9LLfzhu3lha7aR031RJdNRWSXYZ5aOc3baufdurS/jNnzROl5uWXnzbSe7p86Apu5zDPEXW4zzTw/L5OQbGpn0k7RfkdmsxRh5AZ2GVpN/67hCyPT9OzY4UNqT8Es3WHA7WdJ5DthXpJ9WtvQxigfMOyXRZAFcRT9b/uHn6rsP0W1yUyXJew8shOnsMWpVTgQML+8Anfga16YprkIIw6JJwvKf/FBtVKg+4DOFBzlcQhSz/aTOOZxIE9QHPYxuVI4jlOEoRX97zg0/ZAacQi9MoysoOBxoBNw06r8HWdyngicMArt0DI+LIdx5+rCCrUNL6VzyYZdx3LdJPBSbpdKPtXTNzI5X4BMGBS+aRZnOPCdqYbd84Zdt3Bst8wDw65KL91f+AkmFwnXjlIn9WPTsDwV3p+HFVhK81OV7W8atjMnSYLSsbltmldx6F0sw9dJmAe+60am7ZnpGZxeaayhjE0bd0t6SWTHaSic+Vn4NQEdPiggLz1wcP9UQ3bPtHknTlnaYdO0q5mmcyyG3cTNEztPE3wXcK6yu2LYHeyfZbKRsIOkzLPEtFs/K0m2af5lXpc/FKVxWqZFTCmmuwfoLURmLxMZJNTxgtw06D7bma7nY/XyZdEdg8xukQVhFmaUYN7HexezmYuySOI0ieN2m/0V6F72NKMWzddP87Y0jSM/DC2xttg/2dMefqS7OJldbPyDPCt9l3fMqO62zrH/dZrf3ZJ7pZNHcXUczdetDvXo3MoMP7fp5nEeR2lh2oVNL+s4W5jOnuipzgy916/rOJQUTlDmhY1m8bmgo775pt8ks5mJwksCO0s90+bpRW8D7v/uhnAIg17q0Hx8jNm1wyIs4tJDF4NdeGPePC/TZXYj4WVBGfuhze1SAQ4XtPf8abzDbMaxlScO1IAV8E+UeMZ7GcxeLNI4dZPMDQ172B2A7wF7C1X46vtq+qq0Y98rgsokzt3ilcI9dUe4twFlGh73JF/Rm+BMTy4Cx8mL2AnMuPSW4NCAwx6G5fe7s/SXZRjahR0KEHrJ7IrlmO9Ywkq4cb99FgeRlSWtPm8+bmPZ6vvK9CQislLHirxAOGuw1eXACm5lr1ZmnmOVNIvN3z9xmQ5fOH4e+qVr5j+29s+eXVxvpP24Ln/Y96PMdty0TvtzZkqznC8ye7nIfcsqEs8y7UFdXoDN7pByrF10qRzl3VmmpxSpHzhJ6Ll12ksj7dUzIdpBU3rnzIhP6vmW56ebZMVRfKuBnhrQz11eY3oc4dqlFxc=
*/