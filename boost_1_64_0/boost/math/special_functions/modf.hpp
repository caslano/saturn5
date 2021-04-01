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
Z3n9dcCglZGzNp0c+s6FoGkvn3ZD92jnHBvIbbxwAsQl/0Z9+9cxy3MrgkjbWZ4UTtP9DpIolBbSInHQ9HAgfyZjXihRBdBkSpDq8HjQncq1kOaszcmP6+SDzJZ3TaRAN6fEXCRB4O71aWeOQsUQTepmXiQ7MAFMldiq4wceGLT611LOOBo8BmsUrQ7rtS+eBfz91ccRQ0Yvcyk2rAltTkubAaotSPdMudNCIS3F3Z/KApsJyWQ3WMTKoP/b8YgQd4T0X/n3OjSgTtu5OKrIPAK+K8EQ/kpUe8pXtGv3ghXTIOXd0PfLBfhtd34j+Av42zQ2ooqtPi98iPfYxkwmis4rijWpfUrKCcH5i3XvMMy7ENj6oauzSqKMtUphRoeH97Q1XzQyl7cbg+qjc9uuw9MkHzgvo94JqNgR2dO1Ga2huYpwvi6tRsy+8Bhw6y95zPLaVOIZjULfrREx0tbdv76ipr2mUnhr129sO8Df6NYDUnHmQ4Z11LoewzZWR6Kq92cNfUcdvWSpcoy9G9R1sasQziMbaoV7+JuloBlOD69Gl1Z1M3hH2Kkq3g==
*/