// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <map>

namespace boost
{
    template<class T>
    struct is_std_map
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_map< ::std::map<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multimap
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_multimap< ::std::multimap<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_map.hpp
IaCzq3zTRnlaf3DxD87/E/v/IEjzEgN//MH4P3h4ZeCvUsfYoyflDlzkV/359zqVlZ8GlBGaYOCwoTu/2x3GAOz/JE9nvWYV+Fq3s6kwSuCVZSZ1itrr1Zgks9cN7S78rAIBXzTksU+Vk9PrQHvZ5oaX2cwqcKjmOud6SEtxxuqfbLC316cGfWRtz58SiMt2yyL0X3VNlODBjIIBjCdLf7lX4Pj+ncoBQFxW+kEU/dsgltlZ5aY23bF3D4aBKRYlfCaNZrqymnfxoCeL3lFUkq3z3vFdNJF+MApFB07CB/UworvYj+27/gZ6V0y6y32ydPSYx2eCW4xfeOjaOv1gbGYNLzZ2MFb+quaVACPXPH2NkizZh29KkSNL+wV9m39/h86R3w/XSw4C1riJqxHl0y2mLMmdPyQ8zD6g1YpiMP56ocMELz1rTOvYMpb/u2vk9UExpEDcX11pUc5Rat2MgzrI62eQmxfqLr27P37EOeUhDaP7VqNYr2lbv1/gEhmIfEIKQcIXELxZvEGO9Bmf3+Q1fYcQfXPWl0AiyO8LEEAkFdc53TL/slnD6L0LwOxH4vdE/fP25FswPlLywZib+gG4f80z1CCy9mqX826wyPxMXBadVaU4S6ZDLYTPwUS6xvMCGn7PMy1/8ly9Yq2si/JMahnnzk8GdatQHIzlcMmq2rf5pGXBsPCtqEPjJke33WPw5+2jOSJTwK+Q
*/