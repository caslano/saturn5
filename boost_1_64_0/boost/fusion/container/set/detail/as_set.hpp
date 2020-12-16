/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_SET_11062014_2121
#define FUSION_AS_SET_11062014_2121

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/set_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_SET)
# include <boost/fusion/container/set/detail/cpp03/as_set.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <int size
            , typename = typename detail::make_index_sequence<size>::type>
    struct as_set;

    template <int size, std::size_t ...Indices>
    struct as_set<size, detail::index_sequence<Indices...> >
    {
        template <typename I>
        struct apply
        {
            typedef set<
                typename result_of::value_of<
                    typename result_of::advance_c<I, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif


/* as_set.hpp
DcdjOsZhBs7ETMxDK96Pt+JazMbNmIPPYK623U66brc20m5+Un5babd20m7tMRc7SLt1lnbzR3v/ajl/CiEm/auVZ7k0wG+xBZ7DLvgdqv28Zfr+Ju1+Wqb/Uqb/B3bCrzAUz2ifpSDzaWDyPftQxpj+COvjKe0zBWQ6H5Pp/iXT/Y7N8A91rHQ5NyjnDPMNY9s+KevLU9gXn8Yw3IIj8RlMwmdxMT6H6liHMt+vTPoRvyjz3YmB+HcMwZcxE3dhNr6Ka/E1fBh34zO4B3fjXvwcX1frI+fpcLVJfQ5JuUekPkelPsekPkWYjm/jSnwH7c8SkvNrct4t3/AsoVFyn0Y0tsYxsnxjsBuOxT44AZNxIi7BOCzABHwQJ+OjmIhPYjJuwxR8E6fiUUzFd3G61D8N/4np+Atm4O94KzYixmxsgTnYDm/DAJyBcTgLk3A2rsS5uBrn4X2Yh/vwb3gQF+JFvAN/weU4Xtn/wvlYgAvwHlyNq/E+vA834v34OD6Az+I63IkP4V5cj4fxYSzCR9T7WuS8HK4yua/lSdkP2YI98Bnsg4VoxedxOW519HdnRsUyv0Gyv96e/yfJcq0lxxOe6IW1sSXWwQ5YF7tifRyNDXAWNsQ89MK12BhfQ2/ch83wPfTBj7A5/oQt8DdsjUxj8cW+2AbDsR2OwfaYhB0wHzvicuwsy8kfz2AAnsMgrEjduqAfdsWO2BN7Yy+Mxt44E/vgPAzFbdgP38cwPIn98XccgC1ot4HYCgdjBxyK3XAYhuJwDMcRjuVYTs4FwqOyH+yrLEdp9/2yHA+gFx7ElvgWdsBD2BUPy/I9ipF4DEfj25iA7+B0fBez8TjOxBM4G9/DfPwA1+JJfAw/xM34Mb6Mn+Bu/BSP4mf4IX6O5/AL/BFP48/4Jf6C/8Aq1OkMhuBZ7Inf4CD8FmPwO4zDf+J0vIC5+APegRdxJf6ID+BP+BD+rO43yzlGHErKN3nmSB38DQfiv1DGVpfzgrQ1Kd8wtvpo+V0dg34Yg90wFvvhWEzBcTgNJ+BdOBHvw0n4Esbhq5iAr+NklP0yOe/HsYDJflkXKb879sZgHIQhOAx74GjsiZOwl8TRGzPwFlyK/fA5DMNtOAB34kDN77+cx+PYtuTv/x5pv704Cl/HabgPL9PQ3JNy1bFc/8x7VnzQD3vJ/SoT+vxv3LNy+b/gvpVoUpKb963UI60J+++6b2XZf/G9K6Fu3L9yivtOLpO8jzDuLGkCaSZpNWkn6QOS5aiHxY80lGQlFZAKSYdJF0n1jjGOLGkCaS5pHWk36TTJo4hpSREkK2k16TDpDMnzbcbBJaWRVpN2vV12D0zZS/f6T/T/5zLo9ff/b8q4fq9y8BLKAWkF5bJ3dk4W17wTsjMzsm3X6Pn7a62VSmj+npKbkZiTbbt3INbbIn1yZP+OV6T0ZRxCWlqP47e37NfUo6Li0jITkuLscyGM7Kv3P5NrYewzu752Y34NxdW1iRt37cz82pb7z/k1v4bl+prRXtu1mPAfex5c/FTrE2917LjrkVffr+B4zq+0N0barnXoj5VulnOF3tgOm2AwNsUB2ByHYAv0Y9pTnPG9TJJ9F9lvkX0VdT9Fv3/iodkP2YC7Scax5aNlf+ISavcR9pEKNfeuribJePDqWPATSI4x4JPkt/kiyTmuu/zOmvy+yhju/I7qxmzX/UbK76P6uzfU9Vjs/F6Rr1xVS9mr7FX2KnuVvcpeZa+yV9mr7FX2+v99/QXH/4m35Vz/8b9yDB/tbVH76c6VY/g7SM3lXP0ryvmBg45+8QOjRoyOVO4clNsGBw4ITL96P92auj7UVtv7WPV9gu19vPp+sozTb94=
*/