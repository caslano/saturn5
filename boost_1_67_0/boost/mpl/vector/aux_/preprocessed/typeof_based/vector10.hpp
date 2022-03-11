
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