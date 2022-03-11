
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