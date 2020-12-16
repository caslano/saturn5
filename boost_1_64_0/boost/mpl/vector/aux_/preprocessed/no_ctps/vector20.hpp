
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector20.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10
    >
struct vector11
{
    typedef aux::vector_tag<11> tag;
    typedef vector11 type;
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
    

    typedef void_ item11;
    typedef T10 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,11 > end;
};

template<>
struct push_front_impl< aux::vector_tag<10> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector11<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
    {
        typedef vector10<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<10> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector11<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
    {
        typedef vector10<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<11>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item11 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<11> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
        : long_<11>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<11> >
    : size_impl< aux::vector_tag<11> >
{
};

template<>
struct clear_impl< aux::vector_tag<11> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11
    >
struct vector12
{
    typedef aux::vector_tag<12> tag;
    typedef vector12 type;
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
    

    typedef void_ item12;
    typedef T11 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,12 > end;
};

template<>
struct push_front_impl< aux::vector_tag<11> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector12<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
    {
        typedef vector11<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<11> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector12<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
    {
        typedef vector11<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<12>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item12 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<12> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
        : long_<12>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<12> >
    : size_impl< aux::vector_tag<12> >
{
};

template<>
struct clear_impl< aux::vector_tag<12> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12
    >
struct vector13
{
    typedef aux::vector_tag<13> tag;
    typedef vector13 type;
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
    

    typedef void_ item13;
    typedef T12 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,13 > end;
};

template<>
struct push_front_impl< aux::vector_tag<12> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector13<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
    {
        typedef vector12<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<12> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector13<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
    {
        typedef vector12<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<13>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item13 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<13> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
        : long_<13>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<13> >
    : size_impl< aux::vector_tag<13> >
{
};

template<>
struct clear_impl< aux::vector_tag<13> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    , typename T10, typename T11, typename T12, typename T13
    >
struct vector14
{
    typedef aux::vector_tag<14> tag;
    typedef vector14 type;
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
    

    typedef void_ item14;
    typedef T13 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,14 > end;
};

template<>
struct push_front_impl< aux::vector_tag<13> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector14<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
    {
        typedef vector13<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<13> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector14<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
    {
        typedef vector13<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<14>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item14 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<14> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<14> >
{
    template< typename Vector > struct apply
        : long_<14>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<14> >
    : size_impl< aux::vector_tag<14> >
{
};

template<>
struct clear_impl< aux::vector_tag<14> >
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
    >
struct vector15
{
    typedef aux::vector_tag<15> tag;
    typedef vector15 type;
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
    

    typedef void_ item15;
    typedef T14 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,15 > end;
};

template<>
struct push_front_impl< aux::vector_tag<14> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector15<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
    {
        typedef vector14<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<14> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector15<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
    {
        typedef vector14<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<15>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item15 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<15> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<15> >
{
    template< typename Vector > struct apply
        : long_<15>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<15> >
    : size_impl< aux::vector_tag<15> >
{
};

template<>
struct clear_impl< aux::vector_tag<15> >
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
    , typename T15
    >
struct vector16
{
    typedef aux::vector_tag<16> tag;
    typedef vector16 type;
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
    

    typedef void_ item16;
    typedef T15 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,16 > end;
};

template<>
struct push_front_impl< aux::vector_tag<15> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector16<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
    {
        typedef vector15<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<15> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector16<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
    {
        typedef vector15<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<16>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item16 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<16> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<16> >
{
    template< typename Vector > struct apply
        : long_<16>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<16> >
    : size_impl< aux::vector_tag<16> >
{
};

template<>
struct clear_impl< aux::vector_tag<16> >
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
    , typename T15, typename T16
    >
struct vector17
{
    typedef aux::vector_tag<17> tag;
    typedef vector17 type;
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
    

    typedef void_ item17;
    typedef T16 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,17 > end;
};

template<>
struct push_front_impl< aux::vector_tag<16> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector17<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
    {
        typedef vector16<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<16> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector17<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
    {
        typedef vector16<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<17>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item17 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<17> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<17> >
{
    template< typename Vector > struct apply
        : long_<17>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<17> >
    : size_impl< aux::vector_tag<17> >
{
};

template<>
struct clear_impl< aux::vector_tag<17> >
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
    , typename T15, typename T16, typename T17
    >
struct vector18
{
    typedef aux::vector_tag<18> tag;
    typedef vector18 type;
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
    

    typedef void_ item18;
    typedef T17 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,18 > end;
};

template<>
struct push_front_impl< aux::vector_tag<17> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector18<
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
            , typename Vector::item16
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
    {
        typedef vector17<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<17> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector18<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
    {
        typedef vector17<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<18>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item18 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<18> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<18> >
{
    template< typename Vector > struct apply
        : long_<18>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<18> >
    : size_impl< aux::vector_tag<18> >
{
};

template<>
struct clear_impl< aux::vector_tag<18> >
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
    , typename T15, typename T16, typename T17, typename T18
    >
struct vector19
{
    typedef aux::vector_tag<19> tag;
    typedef vector19 type;
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
    

    typedef void_ item19;
    typedef T18 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,19 > end;
};

template<>
struct push_front_impl< aux::vector_tag<18> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector19<
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
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
    {
        typedef vector18<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<18> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector19<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
    {
        typedef vector18<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<19>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item19 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<19> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<19> >
{
    template< typename Vector > struct apply
        : long_<19>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<19> >
    : size_impl< aux::vector_tag<19> >
{
};

template<>
struct clear_impl< aux::vector_tag<19> >
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
    >
struct vector20
{
    typedef aux::vector_tag<20> tag;
    typedef vector20 type;
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
    

    typedef void_ item20;
    typedef T19 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,20 > end;
};

template<>
struct push_front_impl< aux::vector_tag<19> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector20<
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
            , typename Vector::item18
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
    {
        typedef vector19<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9, typename Vector::item10
            , typename Vector::item11, typename Vector::item12
            , typename Vector::item13, typename Vector::item14
            , typename Vector::item15, typename Vector::item16
            , typename Vector::item17, typename Vector::item18
            , typename Vector::item19
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<19> >
{
    template< typename Vector, typename T > struct apply
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
            , typename Vector::item18
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
    {
        typedef vector19<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8, typename Vector::item9
            , typename Vector::item10, typename Vector::item11
            , typename Vector::item12, typename Vector::item13
            , typename Vector::item14, typename Vector::item15
            , typename Vector::item16, typename Vector::item17
            , typename Vector::item18
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<20>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item20 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<20> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
        : long_<20>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<20> >
    : size_impl< aux::vector_tag<20> >
{
};

template<>
struct clear_impl< aux::vector_tag<20> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

}}

/* vector20.hpp
OjN9O7tJv4rn7H5XfjmDP3+6fYGflU/kH1jN581flPAdHerHML0XnnjU/RSfydtHwi9F+HotnKyOUQY/ZdweTR/sw/fMf1SAx9GLwy/RC+lc4Sfk9eF0yuCegJnmRV2++VC66Erz8Ai/6lj7fh9xa6G497FxHUpXGuNzrqd/vaHefhy96Vd8kD5d9iB9WN1mY3AO9Ch5WB9dm/VadAH/Ob6+Fn/K895FK/GkG9T95NecM/B/Olv3CvF7gvrLpfABP/jmqeo26kUF24NzTeD8V+DDz8Q1eL1Y/ih+1X7/Qr3lYnWIbHm0ShxMxwcXqcPRNUOp6jmXwfnJ5jfHvg/qQvB6Cb2jKEHd5gZ4rsh8Pm1/v41HeY6uGj64VdZdX/mcrzQzDn+lyxdNgFefFKfo+kmf2g8b5NeAL/9K56mRh1LU36daR/Jy7uP6QpfIu2+p2+NZ+dfRSegg9Tv6mF+6xSl4X095IMs5TmfZlz6vtVU/xEJ1g1T87Td1Sudjhc6y7gbL10ercxyjzh7mF3deet1q/O1h58e5ly3+ZPWeI6yPbjjIvs7RTxXyuVk/99TX4PyUidbberrT+XSYV8zjOfoE3ZMyL/B1XMcvehXcNIMPIEq/6lFwzGZ6+Tb1TnXj4jQ8JPDtJuInn/PLXakO8LY82IGHLqUDwOGN54TpR/ZpGB/Yyne/r3idJt65v7UumY52CR3jNfWJw+1H/Swl6vJl9JG19OwFvaxH/cP1If6JQ+xj/Ko4lz7Jr1b+kTg7VTzbLW7tDzcV0O+C/TSGr1eeKE+VN5yLGHch/m1dtI0UL+gIlfrnSvlgUxfiL735kgbSea6X39+Hex/W5+Rn3v34wly4N/CPBX1bb+ArUfo58YqMGPktjZ5yrvGZxJfUR5yfIf8bj8Ipe8ataJM+i1us/+IeeIO+kWU9fL77y/jnqr3/4j/hpEPCfID8EeopefX6G2d7vr/VjfhPa+XJ5S/SrQ+gE3biNX/Af+quXfqpuuP5S7bQoRp8bvSef68fFvH/nLM60X2qge9+DHw6jr+VjtrxjHymb2xxfF+6r3sj5fG8PPetVdpnHXSoe/rwp8qrdMA5e8kXT8IzK+Gqo33O/tb78b35UeTdKP0F1n07XJ68uQ8/Zi99turiMeLFJfIpvNPOZ9p8M96URI/qT9/ebL2Nxh9Sg/4b69dzpHmO5hnOWV1r/tXjQ/JnO5yedLJ4PtM6uiG8Z51fLl7p10i6TV61DpIX0oNfoc+cYz4ieNUJUepx4t8M9YO1xkP/1bwI/l4Fn+rHWDzC78MFtXhfvnpCZwq89LV5a5DviqyTGOORjE+UhfiGgnNE6FKT6aml9Eh1zYzv1VMmy2t0rcx0Ptxr+dgW2rd8u6FT7Gf+nto/5SF62ObbQ+rE8Oky63AG3ew+8d7nJFuXVUEf2Wj87S77H15pjjN/g8WHBHwqLN8Pow/yx1SkWIfnwumL9SOdrf6ID6Z9xAdbTUfiq8y7WXylWyR9aT0OUe/mn63fqf+W7pX4kv1yHJxxPFxQqG4/Vt57yjmWZfD8377P55Tupy6xVp7IpYeEgv4L4zGfvlArz/xm3Ryg/ws/zqUDt9Gnc/QnT5tlfj4N0fX4yifZ/+E+8Il7uvvxiZ/JD9Klr45fvW0n3BLP91ZAJy/XX3WGdTQUb5imLmcdzuGTWHwIva+Av7hW/voZTu1Nt0vgo6kTN/ay7sxngvpMwXR1pu+DdSRf8IstCPY7/rfKOXuZZ+MR8c5f5SOsWw8nvRslHqmT0LPyk/RVvkUngSdrKvnd9AnlqKvOu4sP4R04Gf9uy+FXgntb6Bbhh8XFO/hoTqXDlISNV6z9GOucWbg=
*/