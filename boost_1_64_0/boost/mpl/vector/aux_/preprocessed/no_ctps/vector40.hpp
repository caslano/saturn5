
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector40.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30
    >
struct vector31
{
    typedef aux::vector_tag<31> tag;
    typedef vector31 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    

    typedef void_ item31;
    typedef T30 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,31 > end;
};

template<>
struct push_front_impl< aux::vector_tag<30> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector31<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
    {
        typedef vector30<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<30> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector31<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
    {
        typedef vector30<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<31>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item31 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<31> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
        : long_<31>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<31> >
    : size_impl< aux::vector_tag<31> >
{
};

template<>
struct clear_impl< aux::vector_tag<31> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31
    >
struct vector32
{
    typedef aux::vector_tag<32> tag;
    typedef vector32 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    

    typedef void_ item32;
    typedef T31 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,32 > end;
};

template<>
struct push_front_impl< aux::vector_tag<31> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector32<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
    {
        typedef vector31<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<31> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector32<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
    {
        typedef vector31<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<32>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item32 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<32> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
        : long_<32>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<32> >
    : size_impl< aux::vector_tag<32> >
{
};

template<>
struct clear_impl< aux::vector_tag<32> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32
    >
struct vector33
{
    typedef aux::vector_tag<33> tag;
    typedef vector33 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    

    typedef void_ item33;
    typedef T32 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,33 > end;
};

template<>
struct push_front_impl< aux::vector_tag<32> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector33<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
    {
        typedef vector32<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<32> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector33<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
    {
        typedef vector32<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<33>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item33 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<33> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
        : long_<33>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<33> >
    : size_impl< aux::vector_tag<33> >
{
};

template<>
struct clear_impl< aux::vector_tag<33> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33
    >
struct vector34
{
    typedef aux::vector_tag<34> tag;
    typedef vector34 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    

    typedef void_ item34;
    typedef T33 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,34 > end;
};

template<>
struct push_front_impl< aux::vector_tag<33> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector34<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
    {
        typedef vector33<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<33> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector34<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
    {
        typedef vector33<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<34>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item34 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<34> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
        : long_<34>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<34> >
    : size_impl< aux::vector_tag<34> >
{
};

template<>
struct clear_impl< aux::vector_tag<34> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    >
struct vector35
{
    typedef aux::vector_tag<35> tag;
    typedef vector35 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    

    typedef void_ item35;
    typedef T34 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,35 > end;
};

template<>
struct push_front_impl< aux::vector_tag<34> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector35<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
    {
        typedef vector34<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<34> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector35<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
    {
        typedef vector34<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<35>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item35 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<35> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
        : long_<35>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<35> >
    : size_impl< aux::vector_tag<35> >
{
};

template<>
struct clear_impl< aux::vector_tag<35> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35
    >
struct vector36
{
    typedef aux::vector_tag<36> tag;
    typedef vector36 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    

    typedef void_ item36;
    typedef T35 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,36 > end;
};

template<>
struct push_front_impl< aux::vector_tag<35> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector36<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
    {
        typedef vector35<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            , typename Vector::item35
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<35> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector36<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
    {
        typedef vector35<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<36>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item36 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<36> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
        : long_<36>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<36> >
    : size_impl< aux::vector_tag<36> >
{
};

template<>
struct clear_impl< aux::vector_tag<36> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36
    >
struct vector37
{
    typedef aux::vector_tag<37> tag;
    typedef vector37 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    

    typedef void_ item37;
    typedef T36 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,37 > end;
};

template<>
struct push_front_impl< aux::vector_tag<36> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector37<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
    {
        typedef vector36<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            , typename Vector::item35, typename Vector::item36
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<36> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector37<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
    {
        typedef vector36<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<37>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item37 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<37> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
        : long_<37>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<37> >
    : size_impl< aux::vector_tag<37> >
{
};

template<>
struct clear_impl< aux::vector_tag<37> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37
    >
struct vector38
{
    typedef aux::vector_tag<38> tag;
    typedef vector38 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    

    typedef void_ item38;
    typedef T37 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,38 > end;
};

template<>
struct push_front_impl< aux::vector_tag<37> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector38<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
    {
        typedef vector37<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            , typename Vector::item35, typename Vector::item36
            , typename Vector::item37
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<37> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector38<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
    {
        typedef vector37<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<38>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item38 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<38> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
        : long_<38>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<38> >
    : size_impl< aux::vector_tag<38> >
{
};

template<>
struct clear_impl< aux::vector_tag<38> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37, typename T38
    >
struct vector39
{
    typedef aux::vector_tag<39> tag;
    typedef vector39 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    typedef T38 item38;
    

    typedef void_ item39;
    typedef T38 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,39 > end;
};

template<>
struct push_front_impl< aux::vector_tag<38> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector39<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
    {
        typedef vector38<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            , typename Vector::item35, typename Vector::item36
            , typename Vector::item37, typename Vector::item38
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<38> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector39<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
    {
        typedef vector38<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<39>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item39 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<39> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
        : long_<39>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<39> >
    : size_impl< aux::vector_tag<39> >
{
};

template<>
struct clear_impl< aux::vector_tag<39> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20, typename T21, typename T22, typename T23, typename T24
    , typename T25, typename T26, typename T27, typename T28, typename T29
    , typename T30, typename T31, typename T32, typename T33, typename T34
    , typename T35, typename T36, typename T37, typename T38, typename T39
    >
struct vector40
{
    typedef aux::vector_tag<40> tag;
    typedef vector40 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    typedef T9 item9;
    typedef T10 item10;
    typedef T11 item11;
    typedef T12 item12;
    typedef T13 item13;
    typedef T14 item14;
    typedef T15 item15;
    typedef T16 item16;
    typedef T17 item17;
    typedef T18 item18;
    typedef T19 item19;
    typedef T20 item20;
    typedef T21 item21;
    typedef T22 item22;
    typedef T23 item23;
    typedef T24 item24;
    typedef T25 item25;
    typedef T26 item26;
    typedef T27 item27;
    typedef T28 item28;
    typedef T29 item29;
    typedef T30 item30;
    typedef T31 item31;
    typedef T32 item32;
    typedef T33 item33;
    typedef T34 item34;
    typedef T35 item35;
    typedef T36 item36;
    typedef T37 item37;
    typedef T38 item38;
    typedef T39 item39;
    

    typedef void_ item40;
    typedef T39 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,40 > end;
};

template<>
struct push_front_impl< aux::vector_tag<39> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector40<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , typename Vector::item38
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
    {
        typedef vector39<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19, typename Vector::item20
            , typename Vector::item21, typename Vector::item22
            , typename Vector::item23, typename Vector::item24
            , typename Vector::item25, typename Vector::item26
            , typename Vector::item27, typename Vector::item28
            , typename Vector::item29, typename Vector::item30
            , typename Vector::item31, typename Vector::item32
            , typename Vector::item33, typename Vector::item34
            , typename Vector::item35, typename Vector::item36
            , typename Vector::item37, typename Vector::item38
            , typename Vector::item39
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<39> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector40<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , typename Vector::item38
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
    {
        typedef vector39<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18, typename Vector::item19
            , typename Vector::item20, typename Vector::item21
            , typename Vector::item22, typename Vector::item23
            , typename Vector::item24, typename Vector::item25
            , typename Vector::item26, typename Vector::item27
            , typename Vector::item28, typename Vector::item29
            , typename Vector::item30, typename Vector::item31
            , typename Vector::item32, typename Vector::item33
            , typename Vector::item34, typename Vector::item35
            , typename Vector::item36, typename Vector::item37
            , typename Vector::item38
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<40>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item40 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<40> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
        : long_<40>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<40> >
    : size_impl< aux::vector_tag<40> >
{
};

template<>
struct clear_impl< aux::vector_tag<40> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

}}

/* vector40.hpp
36+5LMo4wTtb3FN2k/2Jd2zGq3NL6CE18k4ZHtfTehrFv2Q8co3H+tH21Tg6uHldUhcjzuPjC8WPBvhkNtzj3r+WMXxM9nNCkF+L4d3n8I9v4Mto8epx66hD3WY3XCQvlE3gp9oL3hri/71rPyzXl+yct+5S77VdXnFPSWs9PW1mX/q9fP8nn7D1lnyZPqxzvccK+/A9eaevz4f/G77lG7EON7/K1wgHx6/ls/o2it7LD1dFrx0HB/T2Pa+LY+X2Yw++v5PVPeH4avm5eb1/n+ichVfF1Rfl+1Oj1IflX/y5yLqfpv60/HT5hg5ZOhN+Ml7TDvd8b8N/f4or6pmL/X2Z/d50m/gy3bgcDmd8aR1tolccKX4+jceJq9kbAl2N77fEPjDvjV18DO10gN/pz5fG0kucp2RcU8StBbV0XXglw/w1LjbvbXS/WuuRztCuTzZ+mvP/gr7mR8XFT/nYUugH+6sv0VG68Mes2fLd8rB8Zp3vg5+eh6/+Ic6NEVeCe3zUtSIb4Fz+ueLJ0eqMeNnbcFyrvLeQfqpOmLuebySa/k9HSmqhD+wOq3+77+Ut9cF1fAydcOVk/sIB8nCEX0B9vYoulK6/LA6+bbEeKkeJX7/gKVHiK39+5tHiK12vtAf+uNT5d9/j8Z10Eny7KU2c2NVDHAuJR/bBOP1Ke1tPO8T7anVxOt+cYfSIWnrhZZ5/p/lU369sc07QneoIMZ7zWePi3s85eHHjR/Lak/bb2XxSD+sfj5VHjEuW+J9wQxi/1Rf0EL72pnnH28r5zCO7jeOD8liO/Wfc6y7wXM4LKVOfz+frXdPGXxqmD6TyORb4fPk2s6/1sksdPuhj3KKezgdfNBwfsi7ye/H38O8VOKe2UL2pXd0wZ4Z6xEt0ttnW/zK8jh81LhZvmALXRKwf67Fsvjw7AD+mT82De7L47oqcW7Z4qTqKelR1OX71j7g2ks4rv9Sat3T1rWT5t5k+ki8/df+MT/Gprr2PrzFf/eIfdYJv6Vgviiv0+Ub7Y7P9kVNpHmZZN+J9jnp4Ywf83u4+FnpkyQLrcwd+VQH/tMLrnqPhYLrdBdb/FPV3ennrKnE4s4d+ULqE++jT+4qjDXhTGXwzRRw6Ca8cZx4q1RErjeMy84AXlyaqF10B9zwf8FN/30/fwpnqPepjpUP43yP4XpL6tjzXeaR4fLr3VF9NplM2/2Wd6hNck2G+J+/596696cv78LseqS+OXtsxSZ0XD1z/G1xyTF/1J30awTnXR4mvB3lv9feaAPfqT0i8kN/5azxyvrjON/R/mcT9DPbFg86Rukn8GUl/PVCceNa4dYT0BdDVOvnCVvJL7qaHBP3PcGbav8Uj+7suTzzoARdeEuZv1B92qPpjvv0yWl4r8f14QUIc3pVC19uPXpMFDx0Dl+ymM7wj3h1tnvDHOHwv43RxwHNFMqPw1aBvjy/buqrgA285Xp552Hi9EMu/3YcP1f51T1fBLXD7y9afOF37Df1X//yqRerXL6mfbwjrQ+QTV4dJjIYTL7bvnrHuz5UPfF/pUrhTPSu1nm491vz42dRL/eRZOIeOVT4T37yIvnI4feWb4J5w/qM1cFyp/LFOnJ0tL8N3ecdG6Q8TNzbbb1lw81Py9hDr/xM6VoM675l0o0lworp/2Sz9WOJpwz720RF8IPzJc44M7omx750XEXko6AuGW81/zRH+39F7Pr9OnsyhOy3pp0/hGfMeLY5fZjzoD3FHwHON3vtQOF08r9uIV92g7jMIXv7dfNIP02rNw/F0vzfM80A60Ap46mb+rvvgvhOto2jfr56YuNnvX2rdz8MDY/F/+vvyIC+ehbevxxu3Wj8RugY=
*/