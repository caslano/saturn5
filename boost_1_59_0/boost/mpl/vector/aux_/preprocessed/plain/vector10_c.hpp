
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