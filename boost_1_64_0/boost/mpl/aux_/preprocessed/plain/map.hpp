
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/map.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0 = na, typename T1 = na, typename T2 = na, typename T3 = na
    , typename T4 = na, typename T5 = na, typename T6 = na, typename T7 = na
    , typename T8 = na, typename T9 = na, typename T10 = na, typename T11 = na
    , typename T12 = na, typename T13 = na, typename T14 = na
    , typename T15 = na, typename T16 = na, typename T17 = na
    , typename T18 = na, typename T19 = na
    >
struct map;

template<
     
    >
struct map<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map0<  >
{
    typedef map0<  >::type type;
};

template<
      typename T0
    >
struct map<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map1<T0>
{
    typedef typename map1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct map<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map2< T0,T1 >
{
    typedef typename map2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct map<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map3< T0,T1,T2 >
{
    typedef typename map3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct map<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map4< T0,T1,T2,T3 >
{
    typedef typename map4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct map<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map5< T0,T1,T2,T3,T4 >
{
    typedef typename map5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct map<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename map6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename map7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename map8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : map9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename map9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : map10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename map10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : map11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename map11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : map12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename map12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : map13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename map13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : map14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename map14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : map15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename map15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : map16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename map16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : map17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename map17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : map18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename map18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct map<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : map19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename map19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct map
    : map20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename map20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* map.hpp
PBgi6b0Ow2Q926Uvjz9gABZjEO7AjvgQBuMf0dxnYqmsbw/BqOsz8RFZ36Poi49hO9yLo/BxnIn7cB4+gSlYgkb8Ey7G/bgMD+Bd+BRux6dxBz6Lf8Q/4yN4COX+QergcG/l4P7hbUnfB5K+DyV9H2EXPIO98CwOwo8xCT+R9JzDVfgprsZ/4C48j4fwMzyBn+NH+AWexwr8HL/CCqzEy/gN1iRt32IHrMIB+B2G4/c4HH/A8XgR4/BHzMSfMA9/xmV4GfPxF1yBv2IhGmqanzukDg6uc/DckS73VzdhAGbhUMzGKZiDCzEXM3AxGnEJFmAersallj4Ope6M1Kkx6vo4/ELi+wp98Wtsh5XYBb/BELwg6fgWx2MV3oQ/4Bq8iPfij7gNf8IH8WfciZfwafwFD+Ov+DwaOE6OQE08gV74Bnqjqc8aqfci9WGMuj5rXpTnxJfwBjyCQXgUu+LLOAxfxRF4DM195ZXIemcRjLq+8vbLep+U9R7ARvgUtsansT0+g73xIIbhszgc/4wT8RBG4mGcis9hDJJ30/apYa6PYqqnQjo4x6jHK4OpD65m6I9B2ByDsQX2wwDZLq1wFrbGBGyLCzEI12I7vB074mPYCUuwCx7HrliOIXgOe+F32BebkJZ+6I/9sT8OxDAMw5l4I87FIZiBQzEbw3E1jsS7cBTux9H4DI7BMhyLX+A4rMLx2JCymIC+OAkjMBJjMQoTcAoux6m4CqfjYzgDD2AMnsCZeApn4yWMxRaU9xzsg3OxL8bjFEzEWJyPi3ABLsMULMCFKOdjqWfC3w7Ox7lyvluCvpiHLXApBuHN2Atvwf64HAfiCozBlTgLCzEB1+ICXIfZuAGX4ka8C+/AzViEch2TeiVsMwe/syyX69itGIAF2BtXYH9ciZbfa66wntWynttkPWtkPWtlPetkPaUGqccBbeT64KceX6Yh2yDlhQGYhxG4DKfjzTgX8zEeb0EjLscsvBWLcAVuwpVYgrfh07gGX8d1eBI3YgXeid/hXfgjbsJf8G7pK2gztsR70HRdl7oZOMjBdd1fzh/NsSm2wB7YEntjKxyArTXno1JZ304H56PjUi5lsr7XsRuekPWV42R8A2fgSSmPN3ExvoX5+Dbeh+/gA/guFuN7kg7uXaReBfcIsn2CNO36wiUdo7APjsaxOEbiH4szcRzOw/GYhhMwByfiLTgJ12Ak3olRuAWn4HaMxiM4Dd/F6XgWZ+BnGCPpnYVVOAeV56S5sp3icRgm4Aych/MwERdiEmZjMt6M87EQF+AdmIL3YSrej4twB6bhHszQXkfGy/nbwXbbIuV1P7bFB2S7b8Mw3I5DsBin4Q4pv4dwNj6MS/ERKbfduBofw/W4F019hEr9DXycYNT1EdpW9scg9MF22B7bY3fsgCOxo2zPzpKeLrgQu+EyDMa12F32ox74BwzBx7CXti+mic77bIrQ9sUk8/lVM1+RZn1RuvnaafuyMq+vmvnKZb66Mp+zPqrOaON1Ph87tcR7xfkILs4XPsmavjyCdr48bTlPkvRVM5/RHG818xW5OF+Ji/OVa/JRrusLbIa2nDX50M+XoC3nSFlfNfP5RLq2vhCZz6+a+aKqmS/2Otf7DCsh9dJvGDfDBFN/OJ5+w1zoN+zAnV6GY3d6/Vf0H1ZP6R/qTq9q+xGj0yOX+hLbefD360/M1b7E2pPWK/YnVuT1X9WnWE6R1zXvV4y+AH9z32J7n/339C+2kfLQ9DH2H9G/GH0qXlUfY/Xq1jWEEGIIBYS9hNME7xuYTognFBJ2EU4RqggB9ehvjJBEWEvYRSgnVBEC6rM9CfmEXYQyQiXBtwHLEGIJ+YRiwjE=
*/