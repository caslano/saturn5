
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct vector1
    : v_item<
          T0
        , vector0<  >
        >
{
    typedef vector1 type;
};

template<
      typename T0, typename T1
    >
struct vector2
    : v_item<
          T1
        , vector1<T0>
        >
{
    typedef vector2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct vector3
    : v_item<
          T2
        , vector2< T0,T1 >
        >
{
    typedef vector3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct vector4
    : v_item<
          T3
        , vector3< T0,T1,T2 >
        >
{
    typedef vector4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct vector5
    : v_item<
          T4
        , vector4< T0,T1,T2,T3 >
        >
{
    typedef vector5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct vector6
    : v_item<
          T5
        , vector5< T0,T1,T2,T3,T4 >
        >
{
    typedef vector6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct vector7
    : v_item<
          T6
        , vector6< T0,T1,T2,T3,T4,T5 >
        >
{
    typedef vector7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct vector8
    : v_item<
          T7
        , vector7< T0,T1,T2,T3,T4,T5,T6 >
        >
{
    typedef vector8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct vector9
    : v_item<
          T8
        , vector8< T0,T1,T2,T3,T4,T5,T6,T7 >
        >
{
    typedef vector9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct vector10
    : v_item<
          T9
        , vector9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >
        >
{
    typedef vector10 type;
};

}}

/* vector10.hpp
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
*/