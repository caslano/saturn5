
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector30.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13, typename T14
    , typename T15, typename T16, typename T17, typename T18, typename T19
    , typename T20
    >
struct vector21
{
    typedef aux::vector_tag<21> tag;
    typedef vector21 type;
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
    

    typedef void_ item21;
    typedef T20 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,21 > end;
};

template<>
struct push_front_impl< aux::vector_tag<20> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector21<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
    {
        typedef vector20<
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
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<20> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector21<
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
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
    {
        typedef vector20<
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
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<21>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item21 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<21> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<21> >
{
    template< typename Vector > struct apply
        : long_<21>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<21> >
    : size_impl< aux::vector_tag<21> >
{
};

template<>
struct clear_impl< aux::vector_tag<21> >
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
    , typename T20, typename T21
    >
struct vector22
{
    typedef aux::vector_tag<22> tag;
    typedef vector22 type;
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
    

    typedef void_ item22;
    typedef T21 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,22 > end;
};

template<>
struct push_front_impl< aux::vector_tag<21> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector22<
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
            , typename Vector::item20
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
    {
        typedef vector21<
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
            , typename Vector::item21
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<21> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector22<
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
            , typename Vector::item20
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
    {
        typedef vector21<
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
            , typename Vector::item20
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<22>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item22 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<22> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<22> >
{
    template< typename Vector > struct apply
        : long_<22>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<22> >
    : size_impl< aux::vector_tag<22> >
{
};

template<>
struct clear_impl< aux::vector_tag<22> >
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
    , typename T20, typename T21, typename T22
    >
struct vector23
{
    typedef aux::vector_tag<23> tag;
    typedef vector23 type;
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
    

    typedef void_ item23;
    typedef T22 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,23 > end;
};

template<>
struct push_front_impl< aux::vector_tag<22> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector23<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
    {
        typedef vector22<
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
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<22> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector23<
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
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
    {
        typedef vector22<
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
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<23>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item23 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<23> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<23> >
{
    template< typename Vector > struct apply
        : long_<23>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<23> >
    : size_impl< aux::vector_tag<23> >
{
};

template<>
struct clear_impl< aux::vector_tag<23> >
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
    , typename T20, typename T21, typename T22, typename T23
    >
struct vector24
{
    typedef aux::vector_tag<24> tag;
    typedef vector24 type;
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
    

    typedef void_ item24;
    typedef T23 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,24 > end;
};

template<>
struct push_front_impl< aux::vector_tag<23> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector24<
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
            , typename Vector::item22
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
    {
        typedef vector23<
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
            , typename Vector::item23
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<23> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector24<
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
            , typename Vector::item22
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
    {
        typedef vector23<
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
            , typename Vector::item22
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<24>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item24 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<24> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<24> >
{
    template< typename Vector > struct apply
        : long_<24>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<24> >
    : size_impl< aux::vector_tag<24> >
{
};

template<>
struct clear_impl< aux::vector_tag<24> >
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
    >
struct vector25
{
    typedef aux::vector_tag<25> tag;
    typedef vector25 type;
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
    

    typedef void_ item25;
    typedef T24 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,25 > end;
};

template<>
struct push_front_impl< aux::vector_tag<24> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector25<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
    {
        typedef vector24<
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
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<24> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector25<
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
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
    {
        typedef vector24<
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
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<25>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item25 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<25> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<25> >
{
    template< typename Vector > struct apply
        : long_<25>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<25> >
    : size_impl< aux::vector_tag<25> >
{
};

template<>
struct clear_impl< aux::vector_tag<25> >
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
    , typename T25
    >
struct vector26
{
    typedef aux::vector_tag<26> tag;
    typedef vector26 type;
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
    

    typedef void_ item26;
    typedef T25 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,26 > end;
};

template<>
struct push_front_impl< aux::vector_tag<25> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector26<
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
            , typename Vector::item24
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
    {
        typedef vector25<
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
            , typename Vector::item25
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<25> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector26<
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
            , typename Vector::item24
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
    {
        typedef vector25<
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
            , typename Vector::item24
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<26>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item26 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<26> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<26> >
{
    template< typename Vector > struct apply
        : long_<26>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<26> >
    : size_impl< aux::vector_tag<26> >
{
};

template<>
struct clear_impl< aux::vector_tag<26> >
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
    , typename T25, typename T26
    >
struct vector27
{
    typedef aux::vector_tag<27> tag;
    typedef vector27 type;
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
    

    typedef void_ item27;
    typedef T26 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,27 > end;
};

template<>
struct push_front_impl< aux::vector_tag<26> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector27<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
    {
        typedef vector26<
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
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<26> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector27<
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
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
    {
        typedef vector26<
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
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<27>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item27 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<27> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<27> >
{
    template< typename Vector > struct apply
        : long_<27>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<27> >
    : size_impl< aux::vector_tag<27> >
{
};

template<>
struct clear_impl< aux::vector_tag<27> >
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
    , typename T25, typename T26, typename T27
    >
struct vector28
{
    typedef aux::vector_tag<28> tag;
    typedef vector28 type;
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
    

    typedef void_ item28;
    typedef T27 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,28 > end;
};

template<>
struct push_front_impl< aux::vector_tag<27> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector28<
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
            , typename Vector::item26
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
    {
        typedef vector27<
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
            , typename Vector::item27
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<27> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector28<
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
            , typename Vector::item26
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
    {
        typedef vector27<
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
            , typename Vector::item26
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<28>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item28 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<28> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<28> >
{
    template< typename Vector > struct apply
        : long_<28>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<28> >
    : size_impl< aux::vector_tag<28> >
{
};

template<>
struct clear_impl< aux::vector_tag<28> >
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
    , typename T25, typename T26, typename T27, typename T28
    >
struct vector29
{
    typedef aux::vector_tag<29> tag;
    typedef vector29 type;
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
    

    typedef void_ item29;
    typedef T28 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,29 > end;
};

template<>
struct push_front_impl< aux::vector_tag<28> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector29<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
    {
        typedef vector28<
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
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<28> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector29<
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
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
    {
        typedef vector28<
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
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<29>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item29 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<29> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<29> >
{
    template< typename Vector > struct apply
        : long_<29>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<29> >
    : size_impl< aux::vector_tag<29> >
{
};

template<>
struct clear_impl< aux::vector_tag<29> >
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
    >
struct vector30
{
    typedef aux::vector_tag<30> tag;
    typedef vector30 type;
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
    

    typedef void_ item30;
    typedef T29 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,30 > end;
};

template<>
struct push_front_impl< aux::vector_tag<29> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector30<
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
            , typename Vector::item28
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
    {
        typedef vector29<
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
            , typename Vector::item29
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<29> >
{
    template< typename Vector, typename T > struct apply
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
            , typename Vector::item28
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
    {
        typedef vector29<
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
            , typename Vector::item28
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<30>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item30 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<30> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
        : long_<30>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<30> >
    : size_impl< aux::vector_tag<30> >
{
};

template<>
struct clear_impl< aux::vector_tag<30> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

}}

/* vector30.hpp
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
*/