
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/set/set10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct set1
    : s_item<
          T0
        , typename set0<  >::item_
        >
{
    typedef set1 type;
};

template<
      typename T0, typename T1
    >
struct set2
    : s_item<
          T1
        , typename set1<T0>::item_
        >
{
    typedef set2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct set3
    : s_item<
          T2
        , typename set2< T0,T1 >::item_
        >
{
    typedef set3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct set4
    : s_item<
          T3
        , typename set3< T0,T1,T2 >::item_
        >
{
    typedef set4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct set5
    : s_item<
          T4
        , typename set4< T0,T1,T2,T3 >::item_
        >
{
    typedef set5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct set6
    : s_item<
          T5
        , typename set5< T0,T1,T2,T3,T4 >::item_
        >
{
    typedef set6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct set7
    : s_item<
          T6
        , typename set6< T0,T1,T2,T3,T4,T5 >::item_
        >
{
    typedef set7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct set8
    : s_item<
          T7
        , typename set7< T0,T1,T2,T3,T4,T5,T6 >::item_
        >
{
    typedef set8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct set9
    : s_item<
          T8
        , typename set8< T0,T1,T2,T3,T4,T5,T6,T7 >::item_
        >
{
    typedef set9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct set10
    : s_item<
          T9
        , typename set9< T0,T1,T2,T3,T4,T5,T6,T7,T8 >::item_
        >
{
    typedef set10 type;
};

}}

/* set10.hpp
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
*/