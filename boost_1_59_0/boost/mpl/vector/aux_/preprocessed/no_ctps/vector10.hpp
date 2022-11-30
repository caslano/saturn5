
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/vector/vector10.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template<> struct v_at_impl<0>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item0 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<0> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct size_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : long_<0>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<0> >
    : size_impl< aux::vector_tag<0> >
{
};

template<>
struct clear_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0
    >
struct vector1
{
    typedef aux::vector_tag<1> tag;
    typedef vector1 type;
    typedef T0 item0;
    typedef void_ item1;
    typedef T0 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,1 > end;
};

template<>
struct push_front_impl< aux::vector_tag<0> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector1<
              T
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<
             
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<0> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector1<
             
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<
             
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<1>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item1 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<1> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
        : long_<1>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<1> >
    : size_impl< aux::vector_tag<1> >
{
};

template<>
struct clear_impl< aux::vector_tag<1> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1
    >
struct vector2
{
    typedef aux::vector_tag<2> tag;
    typedef vector2 type;
    typedef T0 item0;
    typedef T1 item1;
    

    typedef void_ item2;
    typedef T1 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,2 > end;
};

template<>
struct push_front_impl< aux::vector_tag<1> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector2<
              T
              ,
              typename Vector::item0
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
    {
        typedef vector1<
              typename Vector::item1
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<1> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector2<
              typename Vector::item0
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
    {
        typedef vector1<
              typename Vector::item0
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<2>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item2 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<2> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
        : long_<2>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<2> >
    : size_impl< aux::vector_tag<2> >
{
};

template<>
struct clear_impl< aux::vector_tag<2> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2
    >
struct vector3
{
    typedef aux::vector_tag<3> tag;
    typedef vector3 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    

    typedef void_ item3;
    typedef T2 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,3 > end;
};

template<>
struct push_front_impl< aux::vector_tag<2> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector3<
              T
              ,
              typename Vector::item0, typename Vector::item1
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
    {
        typedef vector2<
              typename Vector::item1, typename Vector::item2
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<2> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector3<
              typename Vector::item0, typename Vector::item1
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
    {
        typedef vector2<
              typename Vector::item0, typename Vector::item1
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<3>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item3 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<3> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
        : long_<3>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<3> >
    : size_impl< aux::vector_tag<3> >
{
};

template<>
struct clear_impl< aux::vector_tag<3> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3
    >
struct vector4
{
    typedef aux::vector_tag<4> tag;
    typedef vector4 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    

    typedef void_ item4;
    typedef T3 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,4 > end;
};

template<>
struct push_front_impl< aux::vector_tag<3> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector4<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
    {
        typedef vector3<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<3> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector4<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
    {
        typedef vector3<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<4>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item4 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<4> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
        : long_<4>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<4> >
    : size_impl< aux::vector_tag<4> >
{
};

template<>
struct clear_impl< aux::vector_tag<4> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    >
struct vector5
{
    typedef aux::vector_tag<5> tag;
    typedef vector5 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    

    typedef void_ item5;
    typedef T4 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,5 > end;
};

template<>
struct push_front_impl< aux::vector_tag<4> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector5<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
    {
        typedef vector4<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<4> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector5<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
    {
        typedef vector4<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<5>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item5 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<5> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
        : long_<5>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<5> >
    : size_impl< aux::vector_tag<5> >
{
};

template<>
struct clear_impl< aux::vector_tag<5> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct vector6
{
    typedef aux::vector_tag<6> tag;
    typedef vector6 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    

    typedef void_ item6;
    typedef T5 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,6 > end;
};

template<>
struct push_front_impl< aux::vector_tag<5> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector6<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
    {
        typedef vector5<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<5> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector6<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
    {
        typedef vector5<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<6>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item6 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<6> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
        : long_<6>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<6> >
    : size_impl< aux::vector_tag<6> >
{
};

template<>
struct clear_impl< aux::vector_tag<6> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6
    >
struct vector7
{
    typedef aux::vector_tag<7> tag;
    typedef vector7 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    

    typedef void_ item7;
    typedef T6 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,7 > end;
};

template<>
struct push_front_impl< aux::vector_tag<6> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector7<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
    {
        typedef vector6<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<6> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector7<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
    {
        typedef vector6<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<7>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item7 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<7> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
        : long_<7>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<7> >
    : size_impl< aux::vector_tag<7> >
{
};

template<>
struct clear_impl< aux::vector_tag<7> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7
    >
struct vector8
{
    typedef aux::vector_tag<8> tag;
    typedef vector8 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    

    typedef void_ item8;
    typedef T7 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,8 > end;
};

template<>
struct push_front_impl< aux::vector_tag<7> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector8<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
    {
        typedef vector7<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<7> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector8<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
    {
        typedef vector7<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<8>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item8 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<8> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
        : long_<8>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<8> >
    : size_impl< aux::vector_tag<8> >
{
};

template<>
struct clear_impl< aux::vector_tag<8> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8
    >
struct vector9
{
    typedef aux::vector_tag<9> tag;
    typedef vector9 type;
    typedef T0 item0;
    typedef T1 item1;
    typedef T2 item2;
    typedef T3 item3;
    typedef T4 item4;
    typedef T5 item5;
    typedef T6 item6;
    typedef T7 item7;
    typedef T8 item8;
    

    typedef void_ item9;
    typedef T8 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,9 > end;
};

template<>
struct push_front_impl< aux::vector_tag<8> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector9<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
    {
        typedef vector8<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<8> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector9<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
    {
        typedef vector8<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<9>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item9 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<9> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
        : long_<9>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<9> >
    : size_impl< aux::vector_tag<9> >
{
};

template<>
struct clear_impl< aux::vector_tag<9> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

template<
      typename T0, typename T1, typename T2, typename T3, typename T4
    , typename T5, typename T6, typename T7, typename T8, typename T9
    >
struct vector10
{
    typedef aux::vector_tag<10> tag;
    typedef vector10 type;
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
    

    typedef void_ item10;
    typedef T9 back;
    typedef v_iter< type,0 > begin;
    typedef v_iter< type,10 > end;
};

template<>
struct push_front_impl< aux::vector_tag<9> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector10<
              T
              ,
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8
            > type;
    };
};

template<>
struct pop_front_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
    {
        typedef vector9<
              typename Vector::item1, typename Vector::item2
            , typename Vector::item3, typename Vector::item4
            , typename Vector::item5, typename Vector::item6
            , typename Vector::item7, typename Vector::item8
            , typename Vector::item9
            > type;
    };
};

template<>
struct push_back_impl< aux::vector_tag<9> >
{
    template< typename Vector, typename T > struct apply
    {
        typedef vector10<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8
              ,
              T
            > type;
    };
};

template<>
struct pop_back_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
    {
        typedef vector9<
              typename Vector::item0, typename Vector::item1
            , typename Vector::item2, typename Vector::item3
            , typename Vector::item4, typename Vector::item5
            , typename Vector::item6, typename Vector::item7
            , typename Vector::item8
            > type;
    };
};

namespace aux {
template<> struct v_at_impl<10>
{
    template< typename V_ > struct result_
    {
        typedef typename V_::item10 type;
    };
};

}

template<>
struct at_impl< aux::vector_tag<10> >
{
    template< typename V_, typename N > struct apply
    {
        typedef typename aux::v_at_impl<BOOST_MPL_AUX_VALUE_WKND(N)::value>
            ::template result_<V_>::type type;
    };
};

template<>
struct front_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

template<>
struct back_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::back type;
    };
};

template<>
struct empty_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

template<>
struct size_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
        : long_<10>
    {
    };
};

template<>
struct O1_size_impl< aux::vector_tag<10> >
    : size_impl< aux::vector_tag<10> >
{
};

template<>
struct clear_impl< aux::vector_tag<10> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

}}

/* vector10.hpp
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
*/