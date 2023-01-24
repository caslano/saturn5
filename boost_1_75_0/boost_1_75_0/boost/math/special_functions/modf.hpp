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
BkxvP9j381tbdnzL1nnG9egOrJ/DhvAQfdzFszPFGIYeUcPQE2o4K9MYPhITHskyhnuyjeHtOcawM9cYrsozhk/EhPfmG8P5MfTQENPMQyyef0O/porvTm6fMLMhlY/RGVWErwGnK98ZimmRqXz3iF+UvZhEop6g3/uxZVH/epfLNSLmMCksLeodig70hUXaiirer4FjBe1ru+dzX9l2aqOY6aCxpZLKUQW3i8apLG9ZIMZ8Kqenad6d9D0OWaDpFloXnfKQU2IvwgkzISdo/Aht4xO0nj34NvO0znmE3DuP2/H7qrhtd4TK2hEK6yCF7aH5OuEUoXzeRfPk0fBBWsfr83j5IRreTstVzefhKC13mOK3v5zbov0UFqHvc/S7hvbxiiruO+uk5Wqh4wQdFkrzYgrPRmHUUXpHK/Q2K6KwsmjZLFrHJM1TQ+kap/COADbNd6SI+8SRN0TzjNA6LbSeYVqPida7leJimafXZ6b07KSwbbSOyTk8/l6x7gS/N9Ztaikvx2n9HgpvJ63DSus8TX/vpflP0u89ldzXXyT2fxyh9e+p5vOIENqS8uAUfsE7Gr+N8uAQxa2evlaa5yhN24ZwNfdjSNzyyBuXr3bYmj2+aDBs962Xdlap9eHnafy6rublrQ5n15p1zbZWZ0eXS9pbJdbBN1tXRzxd3j5fJBrezCtwuaTdVWBt3IT0RnfEG5uWQ8r2O/qD
*/