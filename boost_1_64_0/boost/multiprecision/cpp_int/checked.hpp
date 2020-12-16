
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CHECKED_HPP
#define BOOST_MP_CPP_INT_CHECKED_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {

//
// Simple routines for performing checked arithmetic with a builtin arithmetic type.
// Note that this is not a complete header, it must be included as part of boost/multiprecision/cpp_int.hpp.
//

inline void raise_overflow(std::string op)
{
   BOOST_THROW_EXCEPTION(std::overflow_error("overflow in " + op));
}
inline void raise_add_overflow()
{
   raise_overflow("addition");
}
inline void raise_subtract_overflow()
{
   BOOST_THROW_EXCEPTION(std::range_error("Subtraction resulted in a negative value, but the type is unsigned"));
}
inline void raise_mul_overflow()
{
   raise_overflow("multiplication");
}
inline void raise_div_overflow()
{
   raise_overflow("division");
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b > 0) && ((integer_traits<A>::const_max - b) < a))
         raise_add_overflow();
   }
   else
   {
      if ((b < 0) && ((integer_traits<A>::const_min - b) > a))
         raise_add_overflow();
   }
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add_imp(A a, A b, const mpl::false_&)
{
   if ((integer_traits<A>::const_max - b) < a)
      raise_add_overflow();
   return a + b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<checked>&)
{
   return checked_add_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_add(A a, A b, const mpl::int_<unchecked>&)
{
   return a + b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::true_&)
{
   if (a > 0)
   {
      if ((b < 0) && ((integer_traits<A>::const_max + b) < a))
         raise_subtract_overflow();
   }
   else
   {
      if ((b > 0) && ((integer_traits<A>::const_min + b) > a))
         raise_subtract_overflow();
   }
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract_imp(A a, A b, const mpl::false_&)
{
   if (a < b)
      raise_subtract_overflow();
   return a - b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<checked>&)
{
   return checked_subtract_imp(a, b, mpl::bool_<boost::is_signed<A>::value>());
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_subtract(A a, A b, const mpl::int_<unchecked>&)
{
   return a - b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<checked>&)
{
   BOOST_MP_USING_ABS
   if (a && (integer_traits<A>::const_max / abs(a) < abs(b)))
      raise_mul_overflow();
   return a * b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_multiply(A a, A b, const mpl::int_<unchecked>&)
{
   return a * b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<checked>&)
{
   if (b == 0)
      raise_div_overflow();
   return a / b;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_divide(A a, A b, const mpl::int_<unchecked>&)
{
   return a / b;
}

template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<checked>&)
{
   if (a && shift)
   {
      if ((shift > sizeof(A) * CHAR_BIT) || (a >> (sizeof(A) * CHAR_BIT - shift)))
         BOOST_THROW_EXCEPTION(std::overflow_error("Shift out of range"));
   }
   return a << shift;
}
template <class A>
inline BOOST_MP_CXX14_CONSTEXPR A checked_left_shift(A a, boost::ulong_long_type shift, const mpl::int_<unchecked>&)
{
   return (shift >= sizeof(A) * CHAR_BIT) ? 0 : a << shift;
}

}}}} // namespace boost::multiprecision::backends::detail

#endif

/* checked.hpp
rmf/DR/3sCsuLsuCqBAyZc/rpefmO1dldZ6LuD0UayTi/kVwNS/rOOHNwZfGT5n+kIvTx49aFlGzK+7F04u/76xFj4qzKA3ypLnZofuW68v07jzNpSx40cTCCeg8i2eCfZ7dQlHUich5zPTUmgzWKJ+1q72/yydZXSSlqCLebBckTmq2bLMuvmQFLOmFkgEzJw6xMlhd9u92mctTM2jyNBbm2lprHevgeKBO0HvTBZfnqFBVECgeNE2gHVr23pHdAngSGyVKyrzOu+q7PFiXDcojgrgsUgFb0xPNeujyYDufJ+0csKzMyyiqW0W6vrcgtYG5zMS92Hm/5gNQ3U438FRJR79o3hZ8AeiX+3QTjMKmccsHOkwzDZgkbNyLHZ+OSbSYC/B27ucNhrZ8h3qIiePxsEb2sUIUZPztnTo04SOa77fAd5o6lN95d3OB1lGbAiD9byPoK7r++BYH6LR+wG7pP+/RaSwJuQvovXpRu7dvjMToZCxmbnoUhsYhuIIY2xK+v87p3X2MG2PgHKVjNsQGS2Maf+6k3Wyb7UG60y62nH9Dulcf12f8XsR4Peus5TOA0f7Bx5TjHYTeL8eB2yB9bDmuIKZXDvRRduC2GtMYtpxyfXjtvAffXuvDR2OrMcSzPvC817MlSSte1GGG75Lax0iuicdk2e33Xd5IsTQM8oDf9FODibzT05CypCxPpY7rXjLTrk88VoDS5FHt0yj4I5a1RngL/pY/8dFmun5Etx67aR2tirgI8iJG7cej/PfCfwM8sYWCebcSacTarQc32o6OMcq79ed99LwIS1sVRVXN2r6+gSLbMj/MTetokimZSUAor8zzHX7OxR+LdZzauqqYX1Y8EzJS1pDBiidTbaNitoKWka71Cy7fY+pSQsEEazQCj/SxtxAsLBKpKFWLPeLH5l11sZJVWRWppKhZp1qCxHvr3TmPpyh4mtUJ8hwZwXPJ5SlZUgYqr1PBltYHp09DTEinyofyTrZJW0lWqBCGRaJY25VZCWESIfzWvDbgmG+GI1/gx08QWURdjtfutVJxKouUpYtD0EngFkXLiSn8Auou3+fd6/BAyUIw7ZmnLYqxgdU5t8zI+xsv31TzRjVIFGwOxuT7iG48uLyPDrM4kVmRQ+11fHaET5w1/Q4KL7ff47KKZVIoZtrJs3EBLLnrBEHkpYyZVrN3OYyvIM5dh0k6gT6n5iKKcnai0fmYbRxUbnanK+82jgWXt2RRIqs6keyRc/8jz5rkGTGtDi6CtGALRvU832wF3VwnUSdL8xQiS/NUFCyMepmizl77qHvhoW4ep9O4eXOMZ5dXTiyvd7awa1uWdm0SaOjXhcYb2j/l0ugZ7FxDG2FgO+H43dyFGGIcQWI3NRjPqNRZuw5PGzqek/EdOXz3jDWddKf3uHQ8gGLdVvc6dOMjB9+Jz7g0fK6A9J9a+taOLvHGkLT3j2+j6WgQSt6R3+N2Lg0TR/ovkH52GZJuW8WhP3MfoaN/GEz/9kgHCvaJ9TVL6Njclv8OHV0rxJEf63Yd6dqQmL7t/9UdkYbyQPLeT+g9WXjYnQjdSKql/8DSh0NM3srbLXd26Y3mDBPBd/x3QQxa3bh9d+EA0rdPaUfvDu+/CA3ztz4V7urSsXqY9jPv5tBNyfDN+90Njb6dQN4tpIM4GV59tniDPltkNVfxIx8927rRIzqmV1kq+tT58QMOaP3X5srG4OwyEEb4mtu+b6engT+vtmmggzl8rzFJ6eBkjuqCKJ04m8OYE1MUYxzO4ZvfeJemjy+ue3595nvcfY8K07xI64JtLs3pWRRiRW/iFIo8Z1yeo2mShomMZMcDLY0srf+Rq7rNozntyo4=
*/