
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
iwR5H38PuedhxDeIYeO7unUxo6Q2yn/PblnTvkFn2jfItEv80n5Xtnfynekxxz9E4veWtvNXZJm9RHpTmZfHS8fPQaYpNjVtZnJsimX5cmL5dXjPRtrt8RyL7Dfku1H6PrJ+72a/7G2UeDdIvOtIR5W6eK90vPQVrYq2/Pe2lxsrqusuStq251aXd0bju8QS+r59LLY24+qVQeouoJx1YfsnpdeFtzXzXvs8Qr5m3l/TtPUuUrXZbiDtxSnPcnQcHZdsyrSUVaB9n7f9+7vt3hUeax6XW93NzJ9IKuP1ysyXE8Su/C5twHcTt+0F4pJ/H5XblPwv8X3iyZL8pyQmyqHz79Q7pH8r2zARDFONzK0+MA9jW9+fpQzzcir5SXbz7LLMs3ayvrbC9xkm4DP9eaZZact9XsQ6j45r10/NPCpW1aN6H5JQu/S+8kNle3JG4lMd7Ff0WPyk+lhDjn9P1Xawr9QpryLHwCcc7yd51qL0fvIUseXrlcmMcGb/bN5GyDTtq6M/TemW/X9ZJ5nlltOE6RvYiGctzOeTyaksFKlMIoPabxuCPUvPx48DieNMmTFU+Phxt8xT9fTneupPf3bZ01+hY8n8fpr5q9pG+9YtPX8/IU7PgjLLd/q40rrsPlJXfzpzZDpLTsIJ0Yk6tU7bsRCdZVfK9PTSL3OVlKm9gODMvLQuUwEh2mXKfnqXOih7o07ZFVlXTTrTG2I99/EqvRx/qmwvZV5qL/xUdJv0rCy/6jpOr+fgnPyIfpkVmVZDP8fTeqJe6eX2M+KLdDCtFdk2Wc+zYuSAr4WU0Yx0ljLSLWUkGJOjbeflzozbWo9npB6txyuFTERyasmxlZccu6q3w0U6sRQq+xp1LOpzlgrE8/lNxJMr7/8vkPOb06SvGE++Jh7b3rgCzwkmtXMuHmt7Ie3xte15PNnHF6ufc9PM46gGlgC+l+n4hvSbcr3urHo6bFNR7vmZdRquN3FuGmrLNHxKfo437GLLaWgZ8dNy7rYLldh8v1DHlpE8O9aUOCJxrjm2RuUco2760nqM+q/HKsenUtclzz2eVOYHYUXPICg5dpxIPUcxPcF8DygkBtX5XFemNl3yMv22/OvIfxu/FSj5Zfznrc9VzoqLTos3RVuXg3MSh/yujMf83GGMZXoN3wZonvdtVHp9+oa4s79S1a3q2KYi6/fXFVqf5DigsbyTWZ5p9cDvGE+OJR65FWB5sNVofhjVuXOSWd86d36+2fqMq9Rzod35eLTRYHteVX6P5i/ym5xXmI//jTL8b3x8DXIOMS8xI03yqs7NowNV66cMb/vtvCqfUeryhOY513P2MSqD2p1T8Zi05dxI8sVKzOpnicN95Bk0N+odN+H3ynbsO516N590lTx73amcuo/7wbm6fyJQzuc0521Mp20d0z7TLvVlOcdi2QljOqqyfQj6vmRduaZ3Hme7viBlynUnxmO+T3GZtFTZBsp45Hos88J2Tm3LG0qZyu8PXSjJe8Kat5vl+2nr90B5ttn63ag651Nt8w7J/FBwIzUm/cCwMUXm+ZFsTLi5fe6Jrvbr5MV61O8sk902Iaxp6bJ/pOxVtrJvfh97PLD88gul/E2yL1pPusRwebbyNfvUCvSJwHKnV74sT5rr8bJPZfmyPx5qZhlxP6mfPqQaVNaqH1Xx2aIr/xqONTb2J7qxqctOby79Rsi+8AAqZReoytbuC1uXs36OumxdP8uPRZ6Nt2urXCzLcjrFWvePBap1V70dY79EFlkvdfaRsh1lO2X53SAxFMlvDG9/PNi89LL6s7KeXLHWx83vv64Elj8/VrewDDhVrs1MxmJlXbGWn6bMDyY6OZ7Z4fxy+pw=
*/