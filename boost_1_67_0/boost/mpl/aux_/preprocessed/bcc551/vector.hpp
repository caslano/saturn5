
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector.hpp" header
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
struct vector;

template<
     
    >
struct vector<
          na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector0<  >
{
    typedef vector0<  >::type type;
};

template<
      typename T0
    >
struct vector<
          T0, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector1<T0>
{
    typedef typename vector1<T0>::type type;
};

template<
      typename T0, typename T1
    >
struct vector<
          T0, T1, na, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector2< T0,T1 >
{
    typedef typename vector2< T0,T1 >::type type;
};

template<
      typename T0, typename T1, typename T2
    >
struct vector<
          T0, T1, T2, na, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector3< T0,T1,T2 >
{
    typedef typename vector3< T0,T1,T2 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct vector<
          T0, T1, T2, T3, na, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector4< T0,T1,T2,T3 >
{
    typedef typename vector4< T0,T1,T2,T3 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct vector<
          T0, T1, T2, T3, T4, na, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector5< T0,T1,T2,T3,T4 >
{
    typedef typename vector5< T0,T1,T2,T3,T4 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct vector<
          T0, T1, T2, T3, T4, T5, na, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector6< T0,T1,T2,T3,T4,T5 >
{
    typedef typename vector6< T0,T1,T2,T3,T4,T5 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, na, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector7< T0,T1,T2,T3,T4,T5,T6 >
{
    typedef typename vector7< T0,T1,T2,T3,T4,T5,T6 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, na, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector8< T0,T1,T2,T3,T4,T5,T6,T7 >
{
    typedef typename vector8< T0,T1,T2,T3,T4,T5,T6,T7 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, na, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
{
    typedef typename vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, na, na, na, na, na, na, na
        , na, na, na
        >
    : vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >
{
    typedef typename vector10< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, na, na, na, na, na, na
        , na, na, na
        >
    : vector11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >
{
    typedef typename vector11< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, na, na, na, na
        , na, na, na, na
        >
    : vector12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >
{
    typedef typename vector12< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, na, na, na
        , na, na, na, na
        >
    : vector13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >
{
    typedef typename vector13< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, na, na
        , na, na, na, na
        >
    : vector14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >
{
    typedef typename vector14< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, na
        , na, na, na, na
        >
    : vector15<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        >
{
    typedef typename vector15< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, na, na, na, na
        >
    : vector16<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15
        >
{
    typedef typename vector16< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, na, na, na
        >
    : vector17<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16
        >
{
    typedef typename vector17< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, na, na
        >
    : vector18<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17
        >
{
    typedef typename vector18< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17 >::type type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18
    >
struct vector<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, na
        >
    : vector19<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18
        >
{
    typedef typename vector19< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18 >::type type;
};

/// primary template (not a specialization!)

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    >
struct vector
    : vector20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename vector20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* vector.hpp
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
*/