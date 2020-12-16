//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_12_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_12_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_12.hpp
zoc3/QCnkHbUcEUmX9FMVkLN5K+Mw72jXEb/FIcs+/E/wfsOS8vnamrwe/ePLg5LGa2A0e/8FaAMjhjmSsSIsnvrwdk0SUxds7VI54/DeuxuCJ4HpRXKzw/v3z45/uC9GfCuGmOsl3/AWu6ZwHNUuYMLeI7yFlCvhCzXJU2PmLwMSk5SXq5yz06Oi8PerfYm4HzoNx8BdeQmEV3SUBW+3f2WI/Gk3jv18hHlfu08ZgbNb8Q3eRWHNeXTPcahVM6ruDYbknvnd7KL1TofaMbA/CuaORciqqkgD8bHAvuLTl/tsdejKKEx9KxTuRwffU2+DevncBnb1G8Am/vRle/D93uML+YnjNEJMr3O6XQ6r/0Z6KRQYklzmTBqyVy36XVcY1T8GcS4UZHJFOKG8525iecdxwfqmXgvHxG3OEkSQgFMjrA4sFXe15f3mJRtUU4mfOww3WOy3l8HciVhKLXYdbh4fDT4L7seE5BUDkvm6YKJzcG39de39ZjrPpT3DbxCkh7f9N6FHElSqVMUDdA42r7iz8M7Ciak8MJA0BuPWzLaZr9PDvZLxFpNqh1ym+nj0/sXq3O5zw2cXCgnbaycUwCmg3Oyd+dO7v1wnvwqwGrEuMciWAh9X3710dBTv6rn0QOeBpenSuGHAkb643oeDfC0nEkIi2nF073TqdPcrM9Mu7e6f4HjXGouy6voZusc7zQzt2ZqbfuKHhsytERhIabrDLu3yE3YPq/tMQkFyXgiRFVMo4LnkQnUk6AorA4sBWij9674bg84k6TW2Ay48wXX+iDAUZQ8ZwJTsca9ZWXTTww2pS5xKhXoS1ODVNaG/dyAJUJyFbQb27IZqWG/MtSZcUZ1DBhgAW3DfhdgBXI4Ymm5qnXefy/dO7tdrkP8+R1oq9/+ZXzflVdoJcV6ADTm6rv/V8gbGaNJxfXgad2i+SgDLEfBmeg4XvO25m339wCLkaU4Smr7MdPVt/XDWwBHkA0Wl2VghXvLkJ9vwBFtQlAOwM63zIUfBjiGInfMagJw0LIN+8nBPlGHbNyAIRhUt63/A5bzZD0XcsS2OjfbfnXQ1THsGWW6YnPkgb7KtQ8CHEXClnudhNe4t6x0/eWATTJZrZUE2FZbgH3k34b+i2MJ680hdnv/feHfhv4bvWMiMoCFRm656Qcsp5GWKLoQu73vvwVgGWIsSB9EW4np5olyQ7Y6nwIsRVQomo2FARaMmvYW6WMAq5G3llkla9uSvYv9u/j2vcNjQH5c3/4O+NxEDkvJtuHPt+C/AvASRa+0Sikt+GmSymsWrH/Df2/AM02M0aYOKH+A37sNX7/Tx74ShTMuVf3fcHBHZG+6Ho3qd/rfh/4teKA4tPZeNxmq+0KAJchTyZ1kFmLXY+q1AyfRWmgSIsCBcdHqe+vv4/zBtHEU1Fcfv7ejbfU96rEJMaes8qwugbwkzp9R4E3oRwCnRCZ3bJKw7PZ+9zcHC/kIlfBV+3x6qLMmESfHWMPnfWNDgzp/cbBxMix3TWpXewwO5/avDTjNEmaCD7jziqt3wUPbRB61TlGtcW9Ztc1vAZYhpqQ3zMbVHqOyNuxj/zGMf50HscNqvU/gK97LAMvy+KMxas9X2FbpFqcMYDVK2FGNndu+x1jYW9u+BeA5csFLQR1d7zMqFtc5b8B6hSUmYY09X2M/BrACWStEiba7FUuGu1qAxchFI4OCC3+rb7vL/BLAEeQEzlCWVrhhn/GNga+s2ZoTyNd0rH3x+0O7EhqYTnC9h6Zt2D8Otk1Y6YQJ3YYd9xlPvPTQ4fuDsODZwAuq3L6VAZYgmwzPzZJW+wU+zIkARxGnSjvPKMCB2jbOWwNnKJM41wPneqw=
*/