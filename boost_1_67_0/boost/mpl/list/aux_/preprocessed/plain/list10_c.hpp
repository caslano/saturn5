
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