
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/deque.hpp" header
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
struct deque;

template<
     
    >
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque<
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
struct deque
    : vector20<
          T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
        , T15, T16, T17, T18, T19
        >
{
    typedef typename vector20< T0,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19 >::type type;
};

}}


/* deque.hpp
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
*/