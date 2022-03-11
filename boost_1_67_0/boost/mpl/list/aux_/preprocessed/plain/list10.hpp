
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