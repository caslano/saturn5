//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_3_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_3_HPP

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


/* polynomial_horner2_3.hpp
VmAQ9nYjx3EZR5z37XI4JnHAMft9rL9QPvuWl/XsuTb1hfUZtUjKvIpj37vVPgPG8uvjcs2g6oHpwwbr8vI9nil9hcLMaW0A1+WEcVFSeD15orYprn/Mu0SbJcb2ilV3unB2YPmktDjoEtOe02leu4XzTLeMVPvMgMudv4Bn4+ibMefoHQ5bHb3fttXlwk4A2WBsm4MvzZHvTxeDwYpiIR/i2zlPz8VoHuTgujTo/JuZ54whD9eR+C3fxgb95XF5h8vpL49X7WS8/1oeL97Fubw86Nwtcf57ebz8Dpzrlscz78hwVh7tnVysvzwm9jCeLg9qzwdvA7xnD9kqs0uc4+4zI2/8zsDbcPuOvnHdhfP4tIPmaXvuyni4ReOe3b7Ww9PTaurP70YcmsKQjv37COddFvWfnwQO3y+CXR/EX3UPF4ezjLSf88x7At5/qsvspzzK6LrXxlxrMwL5u++9MR+OARujPczw7/Pf+OfYHun19/P5XZn6YVJ6za331bT/8CRdJ3X7QGxiM2FuPZzaAlj/lq5dH9412sdTynAedMrO05E6i9uk9BPhlSWfLz3+ZZusuV3UZnWVtJUIU0UjfR88ZM8Bi7os01gSosDxI7toxztRJmWa+XUh4BhV547Vqs19TF2EcR54pdBnH/nd1RczbpRGlQ9zS31Gk3NfztIQe21Y+kEoYCHe8Z13u82tROn/h7QrDbLrmeJvCJkQJARBEMS+zW5iS9/b3XdfWjKIdbLMS2aYzbwJiUJR9n0n9thjj30LlQ8++PC3FAqllF2VIlQUyr70udPb6XdfJinImLnnd053n+4+vZ0+DUFiGG3As/Tg48RMbXj03PGcy7O/YqykQZgR4xOpGEil7xeh9lWRVAQRi8R178Hr8v0Kl6+ORRQWMZF23UwwJda2RdJ6PgS+n82+ox0Dh9qwFnd354yMtJwHdVAs7XaMucehbc4WwC0sN4DmqMWJbevO+yvC8igTLMr1QqkZ8vw7f5c/7917KrM8jurAMMGYDIOa5FaRgodMjNsvoPTqLE8pY9ywwq6ASm9dp7f7Czg9kcLd3Lw0TL3+9HQ7mnB5C8ICWhdJRexkfgO/rvPHcP4qGgZMJClxZvgmf3rfbAblLyNJHocirg0TTC0WenKk7x4/1ez0ezpZd/lLUkVpJQJRKnZUBaem9Pk0SjMgFcvruiwilwkSVoyLOq9nEV9CUtnJRRpmPp9qQ4rd5vUzLn9NJGcW5FVEkCXe4FrTef0aSpOSRARpGspK73OdwOvyH3t8FRc84kVI+lyRMN+fEV9I4kg2s6yOiL8U8+IfDX8R67QUmYjykhG0RDNs9m6nx8fiOE3CMCLe0s2PJzOC+HISpWlOswKlh89PGwmmHwrEH5G8KrOKV5nPb1ltDJVFL8+0qOMoCYm3mjRxnk08EZevJIyKMC3imtjR1hST6LRe46WVpGUdVSwj3jJSMQa6fO9DfIzUrMh5Fhakf+lo4nBo3V5EvCmhYZIWBUvIgOMBv25+iPgTwqo4owHNSPuxgRm/Qt0GEX9J6qCqwziPyODjBKM4s3/yJWy7Cl5WQVoTu6LB+/f3+RJuTxkL6jqpSzLQxQHfNU9c/poUPOZ1YZoT0vSCTvOwlyYtIcCMNQj9wxJO8zROMw3zjKWMOezG4M5O6bkHSjMgYUiLpOAujxtzYkG3p7cjvpgwVtcQS4q0Hhdj3X4B8SYkybOcs5KR9qlk3xzoe7iccR0kcclCgnZgNriWdTl/5ZWz4lEaZWkFl8YbQ62OCDbY7J3mvyG+iNRFFtVRWTZ8Kr86dJbSkomRtOvLuJxxFlVBmYUu79LK3KnFLurrNoacyw9uUFkSxSw=
*/