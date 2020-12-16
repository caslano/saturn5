//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
bozDw/gob0CONx+hDnr4fUqM6Da7i+BEDx5HjCxOQz1YeONuPKoHz+7Ko+ORvQl4/gqejvcXR3A63i++OcSpnt3w8XR+7Ddy9W7CGfuNfD7kYFXwDcBbLIduDsJ5+aWxPDovb7w15GCWpFwdjy5aw/o99DbCGVu/f4/l0O/h6lHg4Ko6jL829fYQp+dh10I8WGO8AHh3JgT19tYiHmfqnZRTK0tBzvFjhIPfd3+eehfhBN9b5A3ePY43mucP3+Pz8Pvm1//GccIx3yccny+8l+DwjcE3TO9HLJjPsd4fsBw6J0749f7geI5JCteWH0JeMHeivciHkYNzozfHz1iczmsawjqfQI6Zl1xZJ04RLJhHvG/6LPJwHsBy5HOIk/HrtcvGaeTQMUf7+Qf3WF4wVrx+vj7vOKjrXhp/OAM4nF3urudPfQQ5u+n5Yx9Fzm56/o17CWdXPd/4GOHtqucLH0febno+f5ZyQj2/iyEe6vm/EdtVz1+IkLObnj8dE86uev5Egrzd9PwHnHJCPR8IxHfT84spckI9n88ItqueH80pL9TzCYn4bnr+IuHsrufPFJa3u54/WVoO1fPG3stcoufKpaqSpOKv2MOVPVgGe+19Wo+HrQ/PcbyxBmvYSYdgnFvb7nsQd89ntrdtOBO02R7Dw9hGGNc75MCGHfPT+N5RjqZsbyzRuF03KI+sxR6doliflhl9S63R9s1FmbV5ecs2GaftPYCf3hmVqTSOG9759Yji86JZIC/i0Uft82v0nDSJsrTMRM7OntIKIc41kXYNCBpPPEGir4uXiXzLZCVUJXnC9PON9hy8RbZn5JBAWhnnhal+lWxektgUMZbBXZeI74G6TtqozRgkkFdYh4E7o/P5c6LJ4jaWOYOsOucaWqyxYrG9S/ZlIOxHI2We5ym7sKnf9a70+v3eqnW6SF2Zom+My5/wy1kqmaZ5I5ieY+j57kWfN6/aSndOnbDgFHXiy6nhs0vUBreIkjLNY6yQ8V/apqZTaMtsuLM90i684U1SiJihF0lIqKBndF/1ZWqWiTateVGyuG21IlhVoncXP/Rl7pFpXak4UswWbTSzCc+vKekHwVRZFUmTJF4pN1bBDebVrkPAAA3ScXV1b/NJXZuCx1GbRp1rS8cFG4Avgu1vZwOg/dVoxzmDxW14dtC9HTys5yn84ixG5zIav/hdZr86bq4a7EHcPd/r7ZiJCOehw5Mhz1FwPzeGs3nF0pDH947yttZXR9J7YZQHz6ksD+1zppAXzmt37aNYf5f6vRzySP0wNiLh7FK/xw8EvF3q943pgEfrh2cSBx0Ppn5jUoF+9C7eDjjMrIibhz2Ow19jOaF1J3IevctyTBLLW1vwMMG3qbzxxoCz1h/6rjL4394c4Prf3iV4/oD5HHtLwNlaxjfrhvPIW0POOonpfuSoxd2nDuvtpfPEMeD1v2CWHlF1QUB0NWy7d43ienq/2vO+eTz45lVJWTV5fctrCn/98G6vP3vXqD32Y3sIDiC2yyRg2NfGJMvV5/Epivd0ILlVSMHjPDYNHKoLJiHgON8IIcckg5xDwCF9YJLB9v/bHaOcbnwafHAYcNL++KjIs614YHsP2kx0ymKqZiY0ZzPxOrQ7wIJ3pJ7lvPB6y8FCmXR6zk9quM7JEinj5P+2NYM+fw/pc3rm9KM9FAcQ2xrWgYCH/UrPXCYOWE5YdW/vcdByaNXJ+DwEHNInloP+UgNOOK6+egfidFxhX23/ztn/hptSjHf6L8uhG7vGrgN7QT9Fdd5kzSv2VzOun47TftKbDc8vxDTBAXRt+/BBim3qTzUQiD3lbcCBXCHpzpgO2+xOi4GUxrEbHWfwauQ=
*/