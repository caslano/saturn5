
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