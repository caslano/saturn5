
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct map_chooser;

}

namespace aux {

template<>
struct map_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef map0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct map_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename map20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_map_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_map_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct map_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_map_arg<T1>::value + is_map_arg<T2>::value 
        + is_map_arg<T3>::value + is_map_arg<T4>::value 
        + is_map_arg<T5>::value + is_map_arg<T6>::value 
        + is_map_arg<T7>::value + is_map_arg<T8>::value 
        + is_map_arg<T9>::value + is_map_arg<T10>::value 
        + is_map_arg<T11>::value + is_map_arg<T12>::value 
        + is_map_arg<T13>::value + is_map_arg<T14>::value 
        + is_map_arg<T15>::value + is_map_arg<T16>::value 
        + is_map_arg<T17>::value + is_map_arg<T18>::value 
        + is_map_arg<T19>::value + is_map_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct map_impl
{
    typedef aux::map_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::map_chooser< arg_num_::value >
        ::template result_< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

} // namespace aux

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct map
    : aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::map_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* map.hpp
retExxlNibY82a3PJ0mj+bp8Oq3Lp0I38kmdvylzrfeyYy0Mhr1yjzSlcUNnlNIUYmMbP/QgiWKWvCtR5V1j5o878lzZ2LqlHD+fv9Wz5BcppYy6KedyxHEunLpcE7pr4DhpefQ6a58ox9+Ua0B1vSbLZ05pY7/cksfEP1g7FmgnaeOfLZ/19bZ+BF6u0Mbfrc+3bb851Sre+x5uw73vPcd+ExZausqodL+2a0c59zhzhqbPh5rSeYUfwUeCXzDpoj1ORkpa5fcnV9eoXH/a/h7kuA3lmPWlr5Lik47jJqeoeyu5+uObnRy/Zg3nxy9XHV91dLfq5blzfFv+rpTjd5Djtyeca8v/HPdvS+Z6ctyG/pUfN/B6qZOojLePg2T8YP/X7cfV9PERWMlxyxz9a8jYtY77p/Rzor9fW+LTUeKzRuITIOngT/hXM64D6/Vn+US7Pv+Wmn5NytguOpItpF+M96Qu4Ncs55iV9uvsvA6k52O9Ou1nwWW/Fa76TfC832Xn/Ud4XifT034xnNcp9byf5h+6K8tnd0jrkWcK/nTPyu03JIZduOyqHxBX/X14XmfVVf8g1jFh5fem3Is36caEjZM6pfFYHY3q/ihku+mynbou6gxp/x6FTfA2DMbbsQtGYyTG2Nvdy+9HrCP7c7S7d4yxm1BVfgPKb0NlvTHKcVhukPb1QZiJLfBOOe4SOW429sINOAA34hDMwRS8D824Ce/AzbgKt2AObsV9uA0LcTs+gzvwBczFl3EXvosP4ke4Dy/jfgwgznkYjI9jGOZjOB7ESHwCY/BJTMQCXIyHcCX+DU/iUXwbX8CzeAx/xeNYnTR5Cdvgy9gPizAcX8Fp+CrOwNdwLp7AeXgSN+Lr+AC+gc9gMT6Pb+LH+BaW4jt4Bd/FKlwwH2NLPIPBeBb74ScYjudwBn6K8fhPvBPLcTd+jY/hRSzAb/ApvITP4nf4An6PxfgLnsdf0Y/rggtkaTVfwEZYFTujD4ahLw7F63AMVsdpWANvwetRud5SfeT3r/wu3lTF+ruNOFumANZriM2wPTbHztgee+NAHIiDcBQOxggcgtNwKM7AEZiGM3AnRuFuvB2fxDgsxFn4Ms7GNzEBP0YTfo5zJd6J+D0mIWlgSMXrcR7WxXTsg2YchEtxOi5DIy7HVFyFC3A93oF/xRW4CXfjZnwMt+DjuBUP4TZ8Hnfiy5iLxbgLv8AH0Zfr5SFsiA9jO3wEu+MeHIEH0IgHMQWfQDM+icvxEGbh07gHCzEfD2MRPoMn8UV8B4/hl3gcy/ElvI68/DvegC9jPSzCNvgKhuBrOBBP4FA8iTPxdZyNxZiOb+IifAu34du4C0vwOL6Dr+C7+E98D8vwFFblunsfq+GH2AL/gcPxIxyPH2MknsEoPIvz8BNMx3OYgf/El/A8voqf4/t4AT/Cf2FNruevsAmWYzO8iK3xG+yK3+IA/A6H4vc4ES/jVPwBZ+BPmI5XcDn+gndhFbp22IFVcT/64AH0w7/jdfgWVsMSrIEXLf2iyDMGZsv3QU1MJChTgnwvmbA+zsEWOBc7YCL2xiQcg8kYhSk4G1NxHs7DJZiG6zEd7d+L77n+XtxQlePjRqyO90q8QwzybIF+sl1VbGrrn0i224TW48gzATZ0cpyasn4trI+1VduV/8Z29WW7BrJdQ/t28hscOjjZrlYVtsPa2B7r4EUsN8hvaBxaxbqd8r1eKts1Yf+1sCX2xVY4GNvgaAzBydgBY7EjLsAbcRV2wtV4E67HLpiDofgQhuFe7INPYV98Hvvh69gfT+EgPIvh+BkOxnIchkHEeQQ2x1EYgmPwJhyL/XECDsKJ6vyR/AwgnNGlVwM=
*/