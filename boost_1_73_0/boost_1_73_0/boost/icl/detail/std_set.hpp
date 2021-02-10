/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007
#define BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007

#include <set>
#include <boost/config.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_set.hpp>


namespace boost{namespace icl
{

template <class Type>
struct is_set<std::set<Type> >
{ 
    typedef is_set<std::set<Type> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


template <class Type>
struct type_to_string<std::set<Type> >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +">"; }
};

template <class Type>
struct type_to_string<std::set<Type, std::greater<Type> > >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +" g>"; }
};

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007


/* std_set.hpp
l9rJzY16y5PGLVyG2I2ZPqS2QfBfEsyc0GYX1CVH8nBpEdyTpt7QlJXnels1vrATf1ufOtvRebNtrAxWTAWjuoldl8aX25JK7oaKUNIahP7JKwn1ZHg/ovnF7KmXyY2HqDn/UeoBgqy/jF7gPs/STMZu6IX2uam1GoRSmJmtb5BP/IZUtpNAKMR/1E6CLSkE9IliqR7aOZjNSDSf4WWkEVHbJpgmdpYgPvefKMP6H+rcPtfJ3bi8U82oJfQJevtK/1tp/UoyySnOPmcKyOc6M4B4wHuVucplY3AJ6XedltqVrLxVUZ6DX0C4gHshstVWq9NUVyU6A72AZAb1QgRrhtHu0M2qqxJdKLGA8BTyhYhvddpX+P8KpFfO8c9Cezy1IYiNInuMl4FFdCES0/rg//S+vSUcyZGxgB8CbhVurM0mcEY32ME77IoyujdvEExnEAyG4jbl57udSvZbO8J/a1UBWL8nCfTauHNfu7B2RRQVBC2QSbnE71c4lt4uD2j/3QJKiHqWkLDU70VQtD0Xnd75SuHGi3uyDCXLfBkDfVE5SPjF9u3QpL9ydm00snmR8cdqWyK69Iq09MoxO3RwhPTgDtm030bbZVZTRf2c7ktMZk3z70zgubaKC0nXPHCMs0yX0sHQs7a18GvO
*/