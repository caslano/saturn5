
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
pmrG2LUeonSDFesJn++nlj/A+eMltIPgE5G3/ER/Q8sv36wo1PAeUbLxp7ONSTRb77+Z7VrRcn9bRIvQ7KGdcuy88Zj5zgk8HbgHtd0c/BX1gLbLfWhmtiB/MkD11pdzD8r7y9odRZ6cX/y98diGVWsDqvKjM1w6IR/oq9ZWxmu7rV1tSXVdRHXZjfAe9qrwWqHm72YAkCtzU4E8tz2Q7mkztMxnkcPBAI8KafVLw8m1h9xDRq3LJ/01MY5zk+gMSP39I94F2jQBeeX08o5oRPJqBPLawWgziwWNAX32xIRVTObvBTp1uyoGhDa7XcsGhPP90kQnzmuRTq2cTluMdLpj5bViwwz2n1ks9lpDIUxi6qQ9f7TsIn8ZIk3oA8pAv9af+5iBKCcA5BMK/NFz/dGlVvizL4yuyLPZAfgjtjXA+RiZw7IE7pJfW4mG8F73y6D7+nnqbrT6KIdlUM03ddWsJjl2Kwj8pLydy0vVvJ3hAZgYFFncrie1ddNyEGP1pJxON7caZ5CpOZ2+6tnBYddW+VlaGq68RLNOd/XsVvz30qTUTWD2XfFDhiGeBoYee+RB0UGLQl8Cm4fP81PS7b8ii/+VJgl/F6VLidEu7GtgtEAlMNoaxmisDScgq6lTW6ha/iVb6JvcLm2hAe1tIbJt5WXtbSGyfdCWBTpwG+2iurlusIXEVFto/bJObSG0gd8aq9rAEbqbAFxm
*/