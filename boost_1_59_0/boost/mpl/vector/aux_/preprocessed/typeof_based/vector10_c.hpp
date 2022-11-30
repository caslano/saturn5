
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct vector1_c
    : v_item<
          integral_c< T,C0 >
        , vector0_c<T>
        >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : v_item<
          integral_c< T,C1 >
        , vector1_c< T,C0 >
        >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : v_item<
          integral_c< T,C2 >
        , vector2_c< T,C0,C1 >
        >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : v_item<
          integral_c< T,C3 >
        , vector3_c< T,C0,C1,C2 >
        >
{
    typedef vector4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct vector5_c
    : v_item<
          integral_c< T,C4 >
        , vector4_c< T,C0,C1,C2,C3 >
        >
{
    typedef vector5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct vector6_c
    : v_item<
          integral_c< T,C5 >
        , vector5_c< T,C0,C1,C2,C3,C4 >
        >
{
    typedef vector6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct vector7_c
    : v_item<
          integral_c< T,C6 >
        , vector6_c< T,C0,C1,C2,C3,C4,C5 >
        >
{
    typedef vector7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct vector8_c
    : v_item<
          integral_c< T,C7 >
        , vector7_c< T,C0,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef vector8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct vector9_c
    : v_item<
          integral_c< T,C8 >
        , vector8_c< T,C0,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef vector9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct vector10_c
    : v_item<
          integral_c< T,C9 >
        , vector9_c< T,C0,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
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
*/