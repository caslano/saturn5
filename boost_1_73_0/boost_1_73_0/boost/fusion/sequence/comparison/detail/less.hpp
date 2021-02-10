/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_1141)
#define FUSION_LESS_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) < extension::as_const(*b) ||
                (!(extension::as_const(*b) < extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less.hpp
3DzhVplMv99d9Xb3y6/VdDHvvKlhmrA5REAJXhQWKQVtjrhUDZ/78csYBuF7/KXXp4q3Q29vEQ/evLuC+h9QSwMECgAAAAgALWdKUiqj0QsbDwAAQU4AAB0ACQBjdXJsLW1hc3Rlci9saWIvZWFzeW9wdGlvbnMuY1VUBQABtkgkYK1c+2/bRhL+3X/FXooDkpwb2+kD7bU9gCJXEmuKZMmVbPVwWMgWHelOkQw9ksu1/d9vls99zVIB6qJw/M18M7uzz9klefX6z/u5IK9J7w8v/+fwA79LRrrf/bt4PNq1Of+dVP8BC371+bgiHeN3/uoMyu/kZUnhtZMfxb8573MkSgb/XwkeL3+EI8Hyd8+f9ut3qyN56b8iN99//x35kry9fntzSYLFdl1sSH4stg/F/t0l+XFZIm8OxT8uSXEki82b2gpbrQ/ksHs6flzsCwL/3qwfi+2hWJLFgSyLw+N+/QB/rLfkuCrI03pTED9J52E8uiQfV+vHlTDyaXcih9XutFmS1eJDQfbFY7H+UNl4XuyPZPcEdDC+XB+OYPB0XO+2b8B3QY7F/v1B2BDuF5vDjiw+LNabxQM4WhzJ6nh8Pvz96urxtBelv1ruHg9Xj03N36yO79uazKEQ7xefyO75SI47cjoUl0Ro
*/