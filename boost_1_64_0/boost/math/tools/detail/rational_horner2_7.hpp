//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_7_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_7_HPP

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
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_7.hpp
9YagEuC6K3m5z8ntIuvoc4KRI96VrUFrrctnzORnUBGayFbTR/t89c6vj/6Cr2iJ8d+6aM4v7Y3iBulwxJpqU1Cfg399bK9YOCHCdiDnlqHWh0uVHiRoetDJqkmDHmAvOaK3AT0Q/wnbO0FKgq4LUcUgUWOQbq13zYWGRgMMqktFMS62CrpuGWqdjKqYY5Lg8OCBM1+XI+1szQKHyeDQ3wSHyvF8Jc90Cep8ukrpQrKmC12sJpcuLHrOAAORi8fqKSgJ6lyq3OfkbKQIBrHYeuR/drUoVa83Xv846/3heA+HGrALSkpHn6lc6UOqpg8Zu+lD+jwzLNgxuPOZyhQDj8ag224MJpthwHZI6Qj41+8Yd7cW47dM3Klv4b1TH+8iu1nIde8lS3x0MHwmn9CD59a9dZxs3cO6Er5CPnymkg/YfSbxxVpD2S1DcSjy0Ufg4Bcc8rZdPB8aYA3JjOc5wnc0xKGILe9VE6Gf157nc2q7BQSHhdsKTm1vFNmwo4ah3kpXWX8msy/7WhmZwB5lUiK0e9Zn++hmnM8FBYfmEzJQBXMvqwb7yRF4y4bms9sG8cX5yJEmQl8nzlIxxzSrY45jD6vEVZ+J+rDmOMpOsla300TodvJon3OvtpPg0OPJ+3BnpKeVhbTnV+I1D5uN2AfmyKMSod2dOUr5Dem2nXzijUNlay+rBXH4IUmwk2Y4hCvZ0j01EbqdHOajauhDZ8FhaMWxRbJ1b6sO55RRL3Je+/HbycpwVTHvcuFIUHvLoT6nHlMXwWDCsl04qe5tNUAXRifirHZ/fgahWpGBFWLdYysZHe8W5/ioJzh0FRzeGvbVuPZGYTHa/OqMMt3+yZ/LERGnZxFmCnEJ/8KX7rObL50/hn+9DFWHWfdUEKDn9Az0UQn0oJvQg033nvOjbN3HWuSBRoh5kWb/fJT1rky8i0NCdhIW9wZTl6THXg700UAw6S6Y7Mqp/0iOel+rBDZiZLze5QADc6M6zLrPhADdh+rro2Yw2EMw2OOUU+E79LV2dIUPhfsyeQcYYcC6z4QAvc6nYJAMBpmCwROPvLKfbN3PWgw9aE6g9r1H/3ea+RlUlTObSAjoeE9mXxWL3VOLxfaz2hJhIzEXJh9oQA+4Y7FKgorL9/bRCjDYSzBIeKp1tRzl/lZBIH5eiTy3gQYYiNxtvtRPJUG7N9bFR6eDQQ/BoG1CfWb8ZsBS1Mlu8Ms99ohBBhiIWiGDeRnEJajzWr+IO4FBT8Ege6o3Kkc5wMroqt8h7H+QGQbsCNx37//0Om8p9xIMjsz/GIXtDrAeRg5DvlfqQb0JBuGSQvFvbnYoWlV+Wc7gbGan4R/E6XusX72O77C35jscaHlgK6KwFbUHm+BTyHcDW0nQbcWPXudOVW/B4Pt+U7fJUQ60CnogTu+Re4sWE3uLsEg8KC8vZbaZHaWo3K/vlD5kafowyGr16/owOtsAiyLewAM+X+0vxPjjtYv6WB1rFx1kzbTUfctOts2MGRh/YSRmX3qSnr/473OHDuMF8o8C9fhUB0b7dGQkTjmmuxhF/w9GrAee/yhO34us8tIMxK32FXwWpA64VLZmW4EzcWc9S2QH2P4X79sU6DD3ulu427prP7p+I3Skr2CQmX41Yvs5Vms6dMSDO2kfsscwi0vHRXjXFSVB5ZQ/73Vid/vZfrj3ZPhfuVZtZ1T4wP2jRv55EjZx90YJccVtGr3OnZN+gkWf9fORETHYarDiZ+E4A93Irg9h8WQf7+ZUSVB28wkv7eWRDPYXDI455YYKRPOt+NvKDamI6xtiwHq8oSQo/6LBS7fDNvYXDL5Zt3+LHOVQ67gM5Mj4sTcdzD4nikqrQlU=
*/