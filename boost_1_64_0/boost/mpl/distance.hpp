
#ifndef BOOST_MPL_DISTANCE_HPP_INCLUDED
#define BOOST_MPL_DISTANCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/distance_fwd.hpp>
#include <boost/mpl/iter_fold.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>


namespace boost { namespace mpl {

// default implementation for forward/bidirectional iterators
template< typename Tag > struct distance_impl
{
    template< typename First, typename Last > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : aux::msvc_eti_base< typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type >
    {
#else
    {
        typedef typename iter_fold<
              iterator_range<First,Last>
            , mpl::long_<0>
            , next<>
            >::type type;
        
        BOOST_STATIC_CONSTANT(long, value =
              (iter_fold<
                  iterator_range<First,Last>
                , mpl::long_<0>
                , next<>
                >::type::value)
            );
#endif
    };
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct distance
    : distance_impl< typename tag<First>::type >
        ::template apply<First, Last>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, distance, (First, Last))
};

BOOST_MPL_AUX_NA_SPEC(2, distance)

}}

#endif // BOOST_MPL_DISTANCE_HPP_INCLUDED

/* distance.hpp
uhjb6G/Q1i7GlfR3HdFmM8FJ9HuY4Cz6raW/BE9HeXid1vGzedo73jtEffPv+t97bP9/RFCF2aEBWbR+y2SDpoJv6PWbxYFWgnF95RDPbyCbwyCbMwovRTqsgr51u16uXa3nI61Cwhummecgm+yBbLLNIQqk6D2NVMvpQtMstdTD6Dhjzgmuo2LvP1ztWO9dg8wL58csqaZovrhW2HPhtXYLobofLAK1q0XfpFnORV/hlcePrLXe673aPT/cNf2Y1nszrz3+9V7zJKz33PTwEA1jFDwdoqjmuqAD2uVAfWXv3fZwksYVT8kv9DE6he05Cvl7wnSyFMtqdetC3mwlz6Tkaj6njwy2oLVLvqVnIU42EJn3pMSUgDInTkOZU0aU+XE5KzpSez9ZDXvUOPY6G3QXXPJVPSej8ofz7YZpTijqDf54hu4NOMcvnaHHEOo95xatVxsGP0znYlLRjLP6YUSmSndTc8GbFWgnVn0g855K0HpRwpFnzspjM4Q9xsdqj4dWOdtD+n2dbonMm10t8V6eqyXaWye5bnC1xu2XuVrj8q9aNwegNXq7WmPpQ6o1lrYr39ka6a2aZNtyVF2WdeGTr7rN/6oUvc+7SdM0TFBobsuY6C/BeKt2WNiYNd9yInisPsus+yXGVaF9bfnvRt2GIv/lKrCJCpTdWYh8zWUlzfdC5FsFqaiZRb6fQeRr3K6uTflAaiD3x1PL4/7eFqrZA8A4+ijHkihBqoksle9Uc/jhBjaAR3et17nCQF5umGBjc2/YY2XX0A1IJYvehDm5V8kiV30J/dZwKEFll+fKLheRfAWIZGf30wTLkOGVZfjmlqmacs1PKzSqyGL8CpGLwpRSxB7mLPVCgNdKl2k3aF0UO9o2Q4qdaQlShG+hav/9sjjan2tWfdt5v+l5qmIVM+IKQk1k4GhjJhR6+U+7GNXUSf3o70r6e4zgX9FfM/29SnCCrU72dPiMHq/1luhTL+3+m9Ta9vl/IgTTpNnQdZ+rEiN2T0enWUJGVf6xztSUvyU1jEJeI0PqRrwxQnpa/5vv0v9KgUe3VLfn/xVR8/+0Y5v/Zx///D8zyz3/p4D/EwtwaJ2W0sgzGj7xKGwuusG1Wj10qeZWUPWamLC748IYYUnXSiOpZeUWbbOaRhMm2udNkqfs72s91nLojSVxtMVIS+ddFkJN9bVozdwAYWKJl7u0pcNQUJ9y6SQ/ct+7SA/pJFtbyyrlbkdSKZdiYZ2KuPaGIW4Q3OHx2avGWFHiea1jNBL9ZR/5qLjbgmyMy2/pXuKpoplhxtoYZYvrFU3wAFpg9bLscLUZbhK0YKSPMSyLJ5hycr639kNV7+2kW7ibkiIWlmjp4mzoFVeHSXOluO1s+YaUkTI1zZrHQE//6se6T+Kd8hh9sE2ua+a5yHXiVE2uTkJFxbde5yTUrR6tc70XWWF7Krj8V+5t3zZsqG3TtAFimralh3ScNn89Luu0L2slsa3t9adPDBSNdkLY6QW1SPkBXT5UjANsC5pIR7feH8SsnHhtVBbi20GUMtG7SRAT7xNZanhpNeICyEtKG2nI+PYU90OzFjupD13y0R2a+mYqVqCi/rZ9dNRfWlGHqK1qnDq51ibXTRIDsccu/XzcJHY0/V9ZlP7vGrf+72ItYccab9wSXJFp6fu2vw7hbz39xNnKsU2/xNbM+orFuG3MZnM0fE3D12jNzr2LLfXV7/RwMGzFX5zd+mvsFI97lPFkKuYEhwawkeW9RsGisW3l3ul2XnPsvIrPQOs93d4xf0Bm1XOErfg786MYxR/rwr2RvXozOr5RrNbtxajzyr9uYfQLiqjYatqi+EYOBVZsYLwO1fFhLW0=
*/