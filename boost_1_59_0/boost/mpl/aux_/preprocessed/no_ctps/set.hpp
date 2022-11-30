
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< int N >
struct set_chooser;

}

namespace aux {

template<>
struct set_chooser<0>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef set0<
             
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<1>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set1<
              T0
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<2>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set2<
              T0, T1
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<3>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set3<
              T0, T1, T2
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<4>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set4<
              T0, T1, T2, T3
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<5>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set5<
              T0, T1, T2, T3, T4
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<6>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set6<
              T0, T1, T2, T3, T4, T5
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<7>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set7<
              T0, T1, T2, T3, T4, T5, T6
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<8>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set8<
              T0, T1, T2, T3, T4, T5, T6, T7
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<9>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set9<
              T0, T1, T2, T3, T4, T5, T6, T7, T8
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<10>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set10<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<11>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set11<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<12>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set12<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<13>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set13<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<14>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set14<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<15>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set15<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<16>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set16<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<17>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set17<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<18>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set18<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<19>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set19<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18
            >::type type;

    };
};

} // namespace aux

namespace aux {

template<>
struct set_chooser<20>
{
    template<
          typename T0, typename T1, typename T2, typename T3, typename T4
        , typename T5, typename T6, typename T7, typename T8, typename T9
        , typename T10, typename T11, typename T12, typename T13, typename T14
        , typename T15, typename T16, typename T17, typename T18, typename T19
        >
    struct result_
    {
        typedef typename set20<
              T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
            >::type type;

    };
};

} // namespace aux

namespace aux {

template< typename T >
struct is_set_arg
{
    BOOST_STATIC_CONSTANT(bool, value  = true);
};

template<>
struct is_set_arg<na>
{
    BOOST_STATIC_CONSTANT(bool, value  = false);
};

template<
      typename T1, typename T2, typename T3, typename T4, typename T5
    , typename T6, typename T7, typename T8, typename T9, typename T10
    , typename T11, typename T12, typename T13, typename T14, typename T15
    , typename T16, typename T17, typename T18, typename T19, typename T20
    >
struct set_count_args
{
    BOOST_STATIC_CONSTANT(int, value =
          is_set_arg<T1>::value + is_set_arg<T2>::value 
        + is_set_arg<T3>::value + is_set_arg<T4>::value 
        + is_set_arg<T5>::value + is_set_arg<T6>::value 
        + is_set_arg<T7>::value + is_set_arg<T8>::value 
        + is_set_arg<T9>::value + is_set_arg<T10>::value 
        + is_set_arg<T11>::value + is_set_arg<T12>::value 
        + is_set_arg<T13>::value + is_set_arg<T14>::value 
        + is_set_arg<T15>::value + is_set_arg<T16>::value 
        + is_set_arg<T17>::value + is_set_arg<T18>::value 
        + is_set_arg<T19>::value + is_set_arg<T20>::value
        );

};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct set_impl
{
    typedef aux::set_count_args<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        > arg_num_;

    typedef typename aux::set_chooser< arg_num_::value >
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
struct set
    : aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type
{
    typedef typename aux::set_impl<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
        >::type type;
};

}}


/* set.hpp
8F6GWRBJxbMMpOIzD8BnWsNvF9cl3oOofOLPrWmZmyMuD2KRP39Bmf7UM1d4D2MVTui2+0JtW8mYsWvI7UFFbeWRiO+aDPfpZfMRs8S49+jNYCkAjVwQ1dLrSJLx88u5ECBJkx0T/Ji+fy1DY8oIjizkm0aajCRGupDbs4Yis+mDV5Qj+WAu4IM6dGqjgnP0vB2L5hNoyE0TTOHtm8+yD5MyN92bWEJ8y4wGFf2NuiZ4Jmo5smhu0SSlN0bMFpI9PABf6ibsxdvoGuGPxG/hkws0ngDX97utH/Elujqh7pFCEubTa/o/xlXdWiF1QIU2y66/c37eTD9ETYFbJHEOyuaBi8J7fMZrQ16lwZyyyVAGqpOq74ucm2aX6zfm4J2CceM5874p0P7hgxP0QEAHRoWzi0lbh3AJtKp3q2ZzTXOZJLIIXSjblC2QfDPirwPR5U2GE2cwdlc8ijOHuoO5kXMxbvGeMPdnTvnC0Nw3mMHJS7lsPYh9WBUZQAx83fH52R3GtcmRxb2oiUwAACz/06CwUUSPtGnquIFGXbVQLl9nJ5o5naz4/biFXcaILvAGDj9kP3Qu3eulRGrPhyzUVW77/GPEDhMOQFR7GPbORSdhU0og8yq0MY+LU8Sm4hrdVIEbJBLdIqbp8b8xIN45KP3i3GudfK5e8cT1S0Nkz1ywnOy3SnaPWeketTOPN2vigmiM8QtAzoJDIJm8Xs4J5C+MMX/G+u7S0fpBD24SmXrJEsIhxuX/+kfTlvw8lxJsPBtGYaZfI/h4PVnrr4PkIezql0Pt2pAK0TF57i5eesYlM9eGNadbu0gbl+MNi5DvgYPq4VWx2vcOuoOGoUmvdhYgUiRiej7isB8UUb+kFAyYPF6FbSZ2ddnHdbpFrVH8wkasyKFKw7segPxRSBc1nmJBqGar1hzGtbyw+w+SsdU8UJycDy3osqpvWaSKj6POCrEYtIjlT8ZQJmqf65KiOSQPmYy2j1ceVbTFpkDR5qUiLLnYQSxhE6vDd/OrXBU33bevyEhq7BGL1icOMdFLGVEJestDdGy5n6kMBOvIgPzpyEq38N74V6HOk5gbVb3w44riklAgHJLqXoz2uRBPSJ928yjGkuPkqP2lWgYDT5GtiqRtL/g0iCSryqLIpZyE5/ypWY523VRjb17h7AhyMpJ3Hyi53Yr6U2mzHfx443fjsmGloKkp6+8S7VI/s9CKiFmkP/roIKBfsd+e4fllcFIpAHTy27AbbfPwKTGvLSnPS71Kr585Fqb3CQpL54vqrcaFG1er7gqe8eGEg6EogW4Et2XwWK6Kef1d5yTl19CZFfifj1U7zEOYc4mZUrHpd4wVPB/s0HxVuUxkSQUjPKgTA/L0TvyacgciqNPN6rwuFXEp1Gkvas1dxYvoNk832nIiIzt3WpfXsVX9n5T9ui9kCjtwmpDb9IMj2dkk7cfgaLhVD1WpBFVpus68jJk4/kBQcD2SqGenD3srBGdHZrQuEJvwtgiwvTLEZ4jzdVg95R7krOu1/ZyqrW68Q512yvusThNJdHHhGDLT01hBsDmia3vUpTawuSGOg13VdXzN/Ld3CZRQrfWH2G4MXoJVtEoH/uUu7ecTd8sp1m3X9hYaETCfN9lnGbcPGs7PbHmX1vHasOF2bEKHSzl++ZNeSWp3uJMt7b/2yYLJ21PukrUyEKQUM1bNlNoEjZSdAe4SnMvI6UDVc47kfXPN0Ewbd58eM8DPKyDWoFDoAtSjfp7uYZ5y7bplehg3eaZkPl2PUociJwk755LI1OEmyjewJ0I08qqahcPCyc+HmFiSm3Ojnk3NDdzpOH4tK9KJos9RPpOEtYJGhuWawXA1cqvqes8sBqDAc8yieXA0Kr0mz4KDtn1p+y2gJ+S8llRwDvYG3MgaG+vzfpIt82q/RrswH/lIniaF8HH7Z5X9SKctyreaNAZhfRmEf/geCNAYTG0tVDcYr5/0mg1t5+4Q0x4LFRzMhDFJMr/x03eb8CSKBInc11cVj/RuCsnYlfGiFbfFlvK7pkJsRJn7Jn7HO8FvEqoCYCU1XpFS46PaDd/28N3TV2QfZxHWj3LZN5PUIt2xzsZvQ3wv9ubbmNlFJJVhYlCumh7h9ZuUCCck3PKHxMTOfM/gzo+P0PA5v+czPM5uGd69jY2DeXWvjhj0qu0QI2tUy039FAtj3O/pZX7aDqi8gpXcaYtPL859/gLdTRd2ejz0Rt0+bTMsocZWwrnR45CyL14HeBbNMJ+p6GkfdK6FuXKcHCFArotYBwhoXKui21lzYT+FF5BuOEPrpZaKPOdozY6+KCsyXHEZzcYa61nUTwcFwi0r3Ls0A4oz+AF21QOH41Y7SOeqKEN75njfYKmJTPOpsoqMOoWp1iEXzUAtRAFzzIZ5Dh9v9Hi27MK2HlGHrfQVWLJzm+LtbkAVcWmVD72m6/1pNkF3xe0Y6+qVwQ2dpfJPNGZrLiFepO1EtJ0Hh0wvtsgKD+U/7mMqxN3QAS9ig1wLzvTR7xHlYOvuAYLjrCGpegsot8wDF8v7x0+EdQTb3kBJfXSdlcuNQCO9sXg+uCqcCsKiGXELpv7GMXL4Lr7EzquF1FsrC6TjTiXr9IqeDrpVoRm5DXzNWZcpaPHxWm+J3IMIT+a/GZZ/4UpDWk7GQdhPUQVObeb+3tzbsLrWR0KgcCaBZan6GNPx/jtm0SI/4hXLhPdZVvTcxPFwvP1o/y3eIxlK8KjwGyVktIDyrD+6uT8yNX9e8waRhLdWiq/eynGtVJyAuMbG+QcXLAfFL763+8M3KKHJgBblSxgectmhsPHIOQfK2pZQulVzYah3iqSLPS5icAhG54IUy/unx0jXz4Qjg2ohJBo8kaaIv5JZske4Y6SALq6AmpDWM2JZmIM8flHtsAU5yHxFPQgBj5Alwnwmv2yKR72ay24dhytQKBbnZejGz3GW4+ikmxnQ2pdt6TTi3GwKr3FhLm9VF5CIujiTghwcKCQRPnY3AegidaQTVKDUBKDO7gbmFcoeKGQMu0aBtqfBIbOVwvkHRbMEsOsPqhmuv+nCHstvf5RCZPsY5H6bnh+vvV4MaaafF3k/FDZNRGKxyCZY3p+pbKTiFBBswHqq+2LBW29m6vSVvYcD4lUhh9UMrAZ3acLB+77uiBTcX2ykaxvCcIhPzK7Vnb6WB0WMCXMhXs5BC0zG0wQ/+qfeWI9FmXf6ajj2H4ed4Yyi+bBs2hMBInS7M4Ts20Z7wgWkrKQ92bD0U0Rz7OQKnx/4VzImFhy1JvvCxJDgdrMFKRGybl8XW4mv3ixFrKssxUuhRqstnALmmZHx0hh4Ecfmjx5rSX84aLc2v/FSqBRHuqHH4BlRyA5nFdhldIWWDgdl1wI+lNUDOU8CFyKvjAZsMFWVfETY0fzjEpjhsOitGviLsRZtkRiP7zhw0NIkdFJzIKuJhWliCjeLEm0lYs/yk8rdKeeu0qif6Bejrc+xgZtDaaZxu8xUkOwG7AT/hCKawXUM2Tt5DLLlQy075pZ+JJfrsyKas584ec0q9bJoFriYrdp8bmjQ+rlUQPvD1P3MGAF+NSmjTVBa6aR7fwZQmZ8x7cYGykCCmiKLv1OjecyrS/dH2oYd7KwjHvXnQuGL/r4lXQ7vNwTneBx+gtLQjD1IdqQeN1jY3IDSnVXYXO9LDMe1nm7fMUOPX9NLrbVThf3+tmhCxTqwN+UAKfkid5PHi4fpU32uhE0uTn4RuQsvzn4bVBdc2yh23J3Kq6l0nTUTLVbv22wzbktTqJbPKfiZya7O0sGZawGwMbTrUM9s8pvWnVb8o+9WjwzF3V7fnlTa4fmdXqra15P03RXQfzbVydSPx+dEI2VWjcXM+cQNUF/VOkgJ+8mPpBj6UHfJcrQHdYUHdjrZXB+cUtthf1yYskrvv8RaaQnH5tx+GfkZp2ZDZqQ/Tl0MWRn31vM5vSeHLFumQ1SkwwjttSGSuSs1M0y653pxc9VC0iDluGQARPAfK5hQgSZV1mj6H9BfICZwwaj+u3gQqonGeWFxpBqjJhai5XMeJf4H1jk16egwND7aYNTQ32x4vCCyUoZf2bM8Wm5jyz2XjpixZDBjIXu3TQyHN8P0wsxc2rf5yRH3QJg9cb91ys8k+6G8vYQiSXv5irsHD6ur9U8BLp3mRiAttzvuEZ5z94Pl68pXvtnYdnCDwr0tuWWtRr1Dix9Gthq9Q82+5efLHziUCBcdW0wZ1yd/nfhRnWKXrp5ZJIe7yOWx9fcuV8B5hA2Bd5gv27wwHB4Q7pFyRTyl7a7iRiU+JEuCniWhwNms+y3Qc15g2ASDJBfKKld4D8ufj0I0eKLWCvi3aCjy/CRgn1IlWnVqkEz9ti9Si453jd2iZTcvy6LbXrWaw9JQiddh5DYl0bvAwGJCmUpdacIi9DZO8PasebLgy3K8YYBTzAHWcjXsuQFzxBut+bwBOHvfpQzLONCsOCrSmUmih3d0R1YdY2rieGBEjL16/m1Zcgcr0s3Bg3OBxV8AzPmEdhw4CtuKIo7XS1W1gSIJ7uTXZAgAHOQ93DpcpI2GG22b1sxe+46Xz1jrh+/Iy2Qw9RSFzsYD5iy3U+AUoEqdS5Osti2PYAiqeVmXBEFWaN7CjFDHeBsFhmqCSNCOsK6gPS4eCsms5JrAsJjs0eqAokivxYahi3WFlLXfACdZu2GzlSMos9G/+dsubuYg7l37dlgdunGS+YNlA09m/6Q/ybJupurJj0nRqgY1YatsimSmRNj6Dg4Sq5GkYxxbiVs69ybOeYNxEnaWW1taehe0R9aNlE8QsgqFuZu122du2eaY3pknpoUM2UNT0dzWkhG25v5wfhxaX5snYxqHY8ItTlmVtIHvTOGMnSuIo6M8NkxFgnPJRmxGtwpXvewOvrqZy9qMiWKRnS7hQtOZ1eOrdqdZwpGdm/WFGwsz2Xx2zgTXQbELzXPxO+bQPgzACmcPjPpXQ9ANOCdgyuw30rZG6487hrO7bI4/VKffMaczMc/zeZjXU/rhxcVhJeKUeNahoNuZy3XhQ5M38ktLiuyA8Nr2InLM/LWQTSsGvx44PakCMRt0HqAh9VQP+k4RjHtp1unzZ/5NRWnN+eRE1QALaIIJiVzdKJQytCQ1h/djGsoXANPCQALLhKZ3MvVxiTOObo6abTsGpyTuSCuKaPJ7yzB9Pjcy5xClUGja1YQhH2ohXUXhxePE2TbxQieCtC2Am2t8BlJkamsNOUXjQjT9V7Gdo/oLHRHPOFg2qheRst2ed/tmU8bngY/c+d1BTeZa7cm+Qens5yLOZYr7KSF9OTGZpKxb4VJe2lFaDLb5mUO9e7Und72UnCF8uG2WUNaybuAASg1atKmRYfft3z5K+KVb858EEfGIZL3pE6bF8xU5y9YZ8sGIdo0TXg8GH1tWJ4HadCqma+GwZY0AVWviLYXLjOYaoBKtWxC5iPYwIkcz4dvYcR6EDjbCN5Hjd0cOBHUAM+L8eeAv8bIJcKEaOf4TNIrbg0mfAEvuAQWG4Ibe/flaFS+hI9SPy5NGGvtexGsNxGslTE862/A8bzgbQBMz/VjEa2XMTrnf9FaNd0y+D/qaSIFOUqEKitGNMCAQdu+8C/yAibaUzwPAN/v3+trngAkWf7jaUa+ZeX8v8m49v7g+nL05XK5ghKlkN4S0qeTPAcA3fcTBL7u+vjwfNEfqi853iFPMhv+2ay+HkRlhneSU3Q7+SZyMiD7JJ7LqKVJdysAQo0SkBbgaZyxoiovk5dWERmtNcCDXXAzJWDy5z9KOVyeMm9XXZXSsjQepE79fVhi8uf57SZwKy4dscr8i2LAW1uJG16ulax7APyn4OeI+pnU25b4SeoE0sMmeeUaL+/O5fXlpb+FQVI31iuUbygugde1Ma12odRIQRM2Tl3rPERBWraSyt7Cule3eEI5XpP2KrvvaQ+spHebba9FCGHWLNfSuGKwMKcXdpe0Bs2zucM8NFq8A3DNcSQkFE7ouiESqLqA3wKWAutUedPECtFeYV4cuHDbDOsW9qurqR2CmlajH/X5H9G+sdua6NBehUs7C8idnsg0p9rO8uAbJ0xyJxXMi5YEieXy8RaGBYHwxhpMA18pEa8s+kbmJKoFYE73Q7r9cxre9Q+1Xz1vCiydCnYHdIrwrJAaukBChbaCSX+9Go/ILCyDLhyK2t46/7jAOAHiYSsN1PnsLrKPuyT8Yq1K4zOYkPBfpit/hoJV6IQYuNK1HnZKwzNdBu2sOW7lb+WNDEvboV9BJkvKeeqjvsXn05ZTHf03F14fUlFQ+kPs9eFO2TWsJMriK9sPLeigdX1Ms+DTlgWlgYDURBRavW171AgyEvhtqvMJzGN2UKi0gtFXZENpAefF9m10ztMZDIVG5EiJoRb9bMwMURQmfBK028A1hkO6nkbzRAqhGcRYT2h1hKjN6u/vJUhwSPMMyVfEMx7c/Jt7+oTzVJ4pQo2U7j/05P1bWhBcTDi6Wsr9DoUl9vh6gby94jBp19wdRC/c57iRv9yvDG0R/gHk/N1igS9/flwkZt00uMR5Ej//kL35DyHv1UV6AOHjxiDVG40mn+n9QyUPRzkf1nu2JBhFteroT268lAqjPV4gmoW53TiH+spHS2PV6yFfeJFHiZaLHYWwsjsEPhMOauOi5mHXDKRu4P2iFuACUgVG1NKZuoJMUAfG5JdbnDDyWjcZniZFljBFxk/ik6Jtn1uGEiXNvTQOaTRuPMY8ayuZ9o4hLPb82O8J3i1qodQ2aYbaeuV1+yB21dZFwPbMCMWw+ZRtlbENHKoV3S7uNsy7FLGbt1VvOFkmbfAk3SKNrS1rIL4aiv1vicA5LnzUE843n0+JmuPXALglhmfVo3w46m1cvnkoInHqvyQyjHjIUzTIpMtOKib6haRo3GbPZ2yFXD6wrknTzNxbj8esa8Yyfr9uSemdeIKlDm0yYbVrpM2mwU8VuyB4yd5tS8KbQMDSJjy3Jz4MK1NFZjumyxYt8ZS6WTxsuuFS6+p7HYZ7hXcg6qz/RDM5xXzPD3M4AL2cVnNzAascKzNIS9jczT4bZ7F8b3zhS6FwEl1ygZqc6PSxN/yXEylXhsawvtUKqyLgd98ZUUiQelk6WnfQk/riI5WnwZtj8ZhgTV2yK+E7+FQPH/Lc0riHgx5MMzy5rM+Bpk7wC/BMryritANYQygMITNdmX1TSG/HeRXrtNOQSiF+UZ0FFy8V4lsPS8EVumOB9AzPZ5qpnckMAUUT830OCHSmv5epiac0xspaUTB/Wo5ac4fmGcopf3EfrKhpC0UIGZKXM0mb+MDS5wAfCPmPFik4vDkn3LbgukggCe9V45XEoRXrqRYLXC/TXS3gei031azo/KK6M/dKmZbbYVbbnhiGS5D74T2O0GrZhvYghX8wjyr4n9lJ3oPBx6MSUx1y2rRVOhJitfRe4rVdSsUSodWfsLhdrmAtrab/1FOFVM3L/CwOw5iG2gi7KaK79H1TZ8FOsp+DzSqwn/wSXYDF51qV6JF7bm3RVneyj5dnsP77brANfnmO2+LozrUBvt8fP97vuIobXAK0YFkU1sbNn4tuuaNUiCv2NrruEDXDk9vFhe6vBOH5ABJaLa8hNIXbN
*/