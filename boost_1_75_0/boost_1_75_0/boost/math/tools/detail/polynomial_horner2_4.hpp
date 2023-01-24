//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_4.hpp
LCkhkZNr+/UAA4rNhqkm5ZkwQFdg5uBkOlzyVy74qh55pjrVJR0ig0gMASqyTgKtjca1sv8IJbnDSUW4R1dnKwvAOnzyOEm+IUgb9cBlzNKGOlTPaDoAGlZZM8SuH8EHwHHtYaq0z9Htviv1nibfsD9mGRWJ7H+6ic+MU3xmNKaI7A3/Kdy6y6rM9PZhspAGpqNP/d2IiPsx86YhbZVwAwoAS8uLXU80dZXPQXol7O46PLSxq30EyT/eslC649LyMjSuKy+TO7AYYKNwNmpAyQ6uvJifZqADJioB8dSnbHEUDcnfAz188S8NPQCcDKKjCYWtpDzG4DDAzhp5YQRWIExTbMIN2T65BXG0CrgzeSXJ6y/T9vgIpKzoNeVpwnj5E4XzlGz1RltVZJlzTbv8ime0XS7SJvI5jHM6ckbKnJ70Qj+Ww19nuEQPuaMNbPbnGNzOrff9LpYG9xgM4J1/p6K5wKXd0FzZpQaa04bFX1eZ+v2D35EopPBmgdWHDbBocf1IT/N7w9F+1g0aZpoMw5C9KNCvbUBSvbMr5p0jTFVERDRSSXSRkkLE06WYIWg30uIflarLGKVpLlya5mI4o51KB0vPyepxIEvbhfB8Cj8Xu2Igy9rxRCnj6Cj8TYoA19GdfOEjqAJnIzQZJ+Oep3v47c9sxnwoInLCzEojPh4K6IEf/Ywo1D9bBJmOaUFc7jQ88P7lesgrSSXF
*/