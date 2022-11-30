
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
    : vector1< integral_c< T,C0 > >
{
    typedef vector1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct vector2_c
    : vector2< integral_c< T,C0 >, integral_c< T,C1 > >
{
    typedef vector2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct vector3_c
    : vector3< integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 > >
{
    typedef vector3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct vector4_c
    : vector4<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >, integral_c<T
        , C3> 
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
    : vector5<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 > 
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
    : vector6<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 > 
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
    : vector7<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c<T
        , C6> 
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
    : vector8<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 > 
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
    : vector9<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 > 
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
    : vector10<
          integral_c< T,C0 >, integral_c< T,C1 >, integral_c< T,C2 >
        , integral_c< T,C3 >, integral_c< T,C4 >, integral_c< T,C5 >, integral_c< T,C6 >
        , integral_c< T,C7 >, integral_c< T,C8 >, integral_c< T,C9 > 
 >
{
    typedef vector10_c type;
    typedef T value_type;
};

}}

/* vector10_c.hpp
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
*/