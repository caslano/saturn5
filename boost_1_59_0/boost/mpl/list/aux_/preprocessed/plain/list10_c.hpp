
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/list/list10_c.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T
    , T C0
    >
struct list1_c
    : l_item<
          long_<1>
        , integral_c< T,C0 >
        , l_end
        >
{
    typedef list1_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1
    >
struct list2_c
    : l_item<
          long_<2>
        , integral_c< T,C0 >
        , list1_c< T,C1 >
        >
{
    typedef list2_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2
    >
struct list3_c
    : l_item<
          long_<3>
        , integral_c< T,C0 >
        , list2_c< T,C1,C2 >
        >
{
    typedef list3_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3
    >
struct list4_c
    : l_item<
          long_<4>
        , integral_c< T,C0 >
        , list3_c< T,C1,C2,C3 >
        >
{
    typedef list4_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4
    >
struct list5_c
    : l_item<
          long_<5>
        , integral_c< T,C0 >
        , list4_c< T,C1,C2,C3,C4 >
        >
{
    typedef list5_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5
    >
struct list6_c
    : l_item<
          long_<6>
        , integral_c< T,C0 >
        , list5_c< T,C1,C2,C3,C4,C5 >
        >
{
    typedef list6_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6
    >
struct list7_c
    : l_item<
          long_<7>
        , integral_c< T,C0 >
        , list6_c< T,C1,C2,C3,C4,C5,C6 >
        >
{
    typedef list7_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7
    >
struct list8_c
    : l_item<
          long_<8>
        , integral_c< T,C0 >
        , list7_c< T,C1,C2,C3,C4,C5,C6,C7 >
        >
{
    typedef list8_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8
    >
struct list9_c
    : l_item<
          long_<9>
        , integral_c< T,C0 >
        , list8_c< T,C1,C2,C3,C4,C5,C6,C7,C8 >
        >
{
    typedef list9_c type;
    typedef T value_type;
};

template<
      typename T
    , T C0, T C1, T C2, T C3, T C4, T C5, T C6, T C7, T C8, T C9
    >
struct list10_c
    : l_item<
          long_<10>
        , integral_c< T,C0 >
        , list9_c< T,C1,C2,C3,C4,C5,C6,C7,C8,C9 >
        >
{
    typedef list10_c type;
    typedef T value_type;
};

}}

/* list10_c.hpp
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
*/