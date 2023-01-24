
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
Jk8StGVKPfaEyRRa41F5ORvsoUstqirh9b3u5WdKrxO0Nax9lxrWsCT1pBrFsZV/HdRwV8W+1vnh7ku54DEcCa3SuCZ4OjhMCgWPutGnSuhg9Yo4HWTPjeuY7EFZkCp79p/FpMl3Z5NwSZzNfv6D/fyYXf7KLrvZpZld4rxoA79uZI+f4T9/d7YhN4ge5gbQmzMHaBYLWCDfKo7AaIPyP3QdPwsZJdAcJoHu30njesEukkCZ71j4occ1NzHlDwaEaTQX5aI8uJQpf92gy78kxaArnlNpq2FHvMysYErWSQd30MFkZPDo5zs/OFOTK0/w4cXjn6WZlbhjhojmLjR251SS2qR4wuicCsPoidroiYanhbwohZqox8ARvKvGqNaX2LHBGMRxffxxHNfZeFxn8qCeMZKGYvDITvwNtf27nMscHf0Law9VQvLaw67R3ZnLfPPbzuYyQ4d1vvbwYb8u1x4AICzf0yaO7szxUJXqeBg2ujsmre+3XTkeVpyZYtvOQENcO81hpAqs9zgFO0fRn1R0lAKjMk14BvduxQdGDR55fb4Hj7y21XzNLONWzK0Z9R7yNFxAy/MzDsmf1dDqfBjm9XMXidKMQ2IsIMvHR9P5W33gR1tKKMJuForADv4WMdEmO+cgU3GMKsGNDLa658giyz2d8nnfHmeKMzwF9cIeGc9e8zRcqLb/mxrkLkPTt/xXTW++GJuuHAlf
*/