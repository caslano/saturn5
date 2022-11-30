
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list/list10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0
    >
struct list1
    : l_item<
          long_<1>
        , T0
        , l_end
        >
{
    typedef list1 type;
};

template<
      typename T0, typename T1
    >
struct list2
    : l_item<
          long_<2>
        , T0
        , list1<T1>
        >
{
    typedef list2 type;
};

template<
      typename T0, typename T1, typename T2
    >
struct list3
    : l_item<
          long_<3>
        , T0
        , list2< T1,T2 >
        >
{
    typedef list3 type;
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct list4
    : l_item<
          long_<4>
        , T0
        , list3< T1,T2,T3 >
        >
{
    typedef list4 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct list5
    : l_item<
          long_<5>
        , T0
        , list4< T1,T2,T3,T4 >
        >
{
    typedef list5 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct list6
    : l_item<
          long_<6>
        , T0
        , list5< T1,T2,T3,T4,T5 >
        >
{
    typedef list6 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct list7
    : l_item<
          long_<7>
        , T0
        , list6< T1,T2,T3,T4,T5,T6 >
        >
{
    typedef list7 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct list8
    : l_item<
          long_<8>
        , T0
        , list7< T1,T2,T3,T4,T5,T6,T7 >
        >
{
    typedef list8 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct list9
    : l_item<
          long_<9>
        , T0
        , list8< T1,T2,T3,T4,T5,T6,T7,T8 >
        >
{
    typedef list9 type;
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct list10
    : l_item<
          long_<10>
        , T0
        , list9< T1,T2,T3,T4,T5,T6,T7,T8,T9 >
        >
{
    typedef list10 type;
};

}}

/* list10.hpp
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
*/