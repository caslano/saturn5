//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_MODF_HPP
#define BOOST_MATH_MODF_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/trunc.hpp>

namespace boost{ namespace math{

template <class T, class Policy>
inline T modf(const T& v, T* ipart, const Policy& pol)
{
   *ipart = trunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, T* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

template <class T, class Policy>
inline T modf(const T& v, int* ipart, const Policy& pol)
{
   *ipart = itrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, int* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

template <class T, class Policy>
inline T modf(const T& v, long* ipart, const Policy& pol)
{
   *ipart = ltrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, long* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG
template <class T, class Policy>
inline T modf(const T& v, boost::long_long_type* ipart, const Policy& pol)
{
   *ipart = lltrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, boost::long_long_type* ipart)
{
   return modf(v, ipart, policies::policy<>());
}
#endif

}} // namespaces

#endif // BOOST_MATH_MODF_HPP

/* modf.hpp
LnB1Yi5wZW1VVAUAAbZIJGBlkbuWgjAARHu+Yvs9HgQESZkgYEB5swE6QV4iARFF+PrVbXeqOXO7uavVO0jVsfXlhOiAlS9TjT/bijlijPAFWqhsblVT62BaI+iqGoS2Al0ZfrhSmu+uQoDEPMDznpZ0w/EY2M6YMy1vpLCWfoDbheXo7lm7WK73o68PTfP99FAhJMSJuRn7vbFwnqLEGYF9Pd2ySF+zRskM6Vhp0uFmBWombO+U7QURsOCWVcrF24fbMRB5nT2X/WVvBjy2i5ZPKN5McSEL4l33mMSdq45X0VaIsgtnZmS5ahZxzG95OJ+bTsmP/nSwl3q2NpSCkygtNO98O+EIiXLbkBlFI1ETexN4H0GSZZYdMcuimq26jd90YaHlQlCy0zV0fB0dOSGf5pMkPft5bccvJD4YYcQtjaVqtoDTtyfWDMZHPlD/SV3yGoKd198NPTRTFJHHmLzSDkTVuf1J7HROIldxmWrCO+hCxPxJUa3dP0+/UEsDBAoAAAAIAC1nSlJpelXxTwIAAAADAAAxAAkAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdDBoLXN2LmNybFVUBQABtkgkYF2SS7OaQBCF9/yK7KlbF0T0sshiXuCg
*/