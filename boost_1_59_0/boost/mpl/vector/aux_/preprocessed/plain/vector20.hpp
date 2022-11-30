
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

template< typename V >
struct v_at< V,11 >
{
    typedef typename V::item11 type;
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

template< typename V >
struct v_at< V,12 >
{
    typedef typename V::item12 type;
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

template< typename V >
struct v_at< V,13 >
{
    typedef typename V::item13 type;
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

template< typename V >
struct v_at< V,14 >
{
    typedef typename V::item14 type;
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

template< typename V >
struct v_at< V,15 >
{
    typedef typename V::item15 type;
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

template< typename V >
struct v_at< V,16 >
{
    typedef typename V::item16 type;
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

template< typename V >
struct v_at< V,17 >
{
    typedef typename V::item17 type;
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

template< typename V >
struct v_at< V,18 >
{
    typedef typename V::item18 type;
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

template< typename V >
struct v_at< V,19 >
{
    typedef typename V::item19 type;
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

template< typename V >
struct v_at< V,20 >
{
    typedef typename V::item20 type;
};

}}

/* vector20.hpp
C5hsxF/1+ALFrTekKMDkDZT5oxAR6yQ4FgYmw+dq+6kz7sBJwWURamoh4hLySWL9Q/VHY+GOKOCPQMMA/RlrkV9RcLcjGHvt4BrhZ42CRDw+H+HXURsm3hkK3Kqujjo+6CYpIUnq6nuk2CvEfZbSir0bV+gU6gundz89mfap0KAuOKMLyTQWp5wtUbMqgZc2YgCkndh2dsgetYcadKgSRHQCp7M76ElBGnqh3iAJupCiK7THADGwOAjkYgga+onw4jhwWD2B/ng0G81F89EytAqtQz+gTehH0G+b0Vb0E9qBtqOdaBf6Ge1Ge9AvaB86gPajg+gwOoSOo2PoBEqghony6YP8qOHQehuhlQKoMdB2/pQnmoPWUONQCOVFCXIw2YBrE6AFEdqGjqLp4DYHAhu7UuPhyEQUS40ADCzz06CuoBkoDq2kFFQt0ZUeTA2h3KiB6AhccZpqD67yaMG5pnwpP8odRVKDqKFgpMxCC9BMtBDNQ4vREqRBi9C3aAXcsRx9j9ai71AR1QNMoElUL6o35QKmTT+qD9UTGYljcG/gJAOtOAvqLtR7L9pHxVGrJA0lv0oe0Yn8jxY1LOpaqCx4iyYWVhY2Fo4WvS3CLaZaLLbY27hJE9MmfJN+Tbya+BOj9+/F8WkL8G8HcG4f2g9Q6kuuSDL0UDiL+haNLCxEKJ1FKFEW8VWg+BH0/v37XMrq/dn3Z94nUar3ie/3vG/29/S/J5Ude/JLbmJux9z2ufa5drntcq1y+VxlriMcsc3Zn9M5u39292yzx+8fl7E+Xyi//+uP1gfSj1UfJKKQkTD9QCmqaG7hiI22NtK+orQlJkj7WqJ9TWvfGJGaJODPtD9rM+YI1Z9Uawdke4aawrbBszooQyLOkdaCrtIQOoXg6TlAswwA0fWE7jwJBCgWGnguNO5KaNAfgL2HUAI6iy6j6+g+ykXPURHCgLkm1YCypNpR9lRHygmauz+Ix0hqHAjLJCpajIzPE2f8dlFHqJPUWeo6lU49on6jnlMF1GsKS2hJLYkSmt5K0lLSRmIvcZQ4S/pI3CVekgBJsGSKZJ5kiWSF5HvJJskuyWHJKckFyS3JA0mO5JnkpaRY8lbyJ03RxrSCrks3oHm6Nd2J7k73oYfSY+kJdAQ9hZ5FL6JX0Wvpn+gD9HE6ib5EX6VT6If0b3QhraWJETJijGobKY3qGzU2amlka9TFqLfRQKMRRp5GgUYRRjONNEYbjPYYnTa6ZpRhlG30mjFizJiWTHumOzOM8WUimJnMQmYFs57ZzuxnEpjzzA0mncllCpi3zF+sMWvKNmKbsTZsF9aFHcyOZH3ZIDaKncEuYdey29kj7Hn2NpvFFrB/So2l9aXNpR2kfaUjpROkMdKF0nXS3dJD0gTpWSk2rmvcxLhFjxBv34gwMDjFrIdPhH+Mv7e47RE2ISzUf5K3Luvl7Rsd5e8rbnv5Bkb4RocEBPtP8a0s9vILi/L29fUPjfKtKPXy9QaovuK2t7j105cjwryj/MStiw61vy5zEXH7i1uXCjj+FSUXHTn+usxFhOYvbvtWkjKhsthXhDRB3PatgDKhotTXNywkxFt/1KDcrxLExMpiPx/viImQXKMCg/38A8Wtq47wQF3mKmIKFLeuOiIDdZlrBU7X/oFB/SuBBlUWBxhQMMmwPCHC3z80GEyiQF83sQ2Cxa2bwTXBBmU3kSPB4tYN8AZDGiTeESpuBxlcG2pQHiTeEarbegtuR0RY+ER/l9AJYGUN1tUwTJcNFqsYJm4HT4wGIywiOiTYOzoqzHBnmIguQtwOM0AUYVAeJqKLELfu4pWR4ta9ki+RlUV3sA0Dg4O9I/X5cANIUQbl4SK8KHE7HJosCtIIscGixe0IXTWiddkIsR7R4nZERGDohGhhM8KwKtGGOyN0bRqty0ZWkhdbWRxVWZxaWRwt1m2auB1dIRLTKkrBYaETIt0NKhJpUI4ODbSxs+2hy3pCZuvS2cUlOiIsMDQgMDQwaqp3eHhE2BT/ydHewaFhUWIe7B8ZKRZAhryhLcRygGcA/HsGChtDwYH7g/0DPIOm+UeEWQuxR6iemEfF6vajJoIkiqWAsOgIXQFscLEQGThFlwMTQ8WSv+BOiKXQQD2giVNBoEKthZhouHcECLV/QFTlnuh/iLs+IDST/KMqTuv3q17gX+W0f+VJb102IRpEBFyDSjAVRyqvFQ5FQmsHV7lIPFJ5kX+on3fkRF0xpKIYDijD/EQNFQHeknBocrR/ZFQgKLqwWF0tQUkGe4dU7PpEAx4dTJHJ4Z5hkQECl8WCwGZdQeSzWBQZrSsJnBZLAqt1BZHXYlHHbLEoclss6RqyHEdUOY6oShxRFTiiKnBEleOIqsQRVYkjqgKHWPILg34YYQ0lgRNCHgn8CAYGCuWpcK8ANzgMupRQEuTVupw0QUgivKPCBDVeuSOQWLkjklmxK5JauSeQW7EnkFy5I5JdsasjvWJXJL9iT6TFzx+UW2BoOTUGuwI9hrsiRQYHRJoM9wWqDPYFugx3RcoMDuhoMzggUlcFY2BopOAXC13fpoeNLuv9b936z7rYVb36QWERId7B6Jpg29mC4zIRrQfj+hBKQ6UUS7lSY6jJ1BrqscRE0lgyECyrQ5LjkueSd7QRLaPr0M1oa7oD7UK70+PoZfRK+gR9nr5Lp9NP6XywkxijukZORj2M+oB15G40HqyjaKNkpjHTjGktvq3EjfmBOcC8Z2uwdVlPNpSdyZ5h06R1pebS1tIgaZR0lvR76RbpPrBoXkhfS0uNjYxrGpsZq42bGn9jPNbYyzjQOMQ4yniBscZ4hfF645+MdxvvMz5s/MD4pXFxDbMaTjX61QipMaXGwhqra6yrcabGxRopNR7LkPhCy3YyB5mjrJfMVTZCNkbmLQuQTZZNk8XJ5sqWyL6V7ZLtkx2VJcjOyC7K7steyF7J/pAROZLT8tpypby5vI3cTu4sd5H3l4+WB8kj5DHymfJ54ist18q3yw/IT8hPy8/Kr8vvyDPkj+VP5fnyQjmWl5lITRQmpiZmJioTSxNrk04mPU3cTDxMvEz8TCaaTDaZZjLXZKnJCpPvTTaZbDXZafKLyYHT+E8l8cP2pAP2ipRhT2KHbYlXpDn/OsgcW2JjYkysJ8uIJamBTbA9Lx+T19xcXbSiq0x+GK9SEmusIEa4dYQ5bksUmCatJ5vzxWZvH9x/WZDp3KSx8IHRrul/8HKyao+sKUtW/eXBvGZTsSeDf2RJPW0rpWbDgLUT+EwSxZAg9gGOYtYe2Hhdo5Irc9izD5ll7LkuTA5rP9zcilVwOU1l8svmP6/Z/zN/fGPfWw1v7zvxWO3Chs6ZEMJ7Tb/dr2HfQK+OajlOk+K6vVJJXWLcc7CGP9Kb0SQnZl4/FdaJnxMt7UDC55Eu8t3m3BEncy6ysTlnItcE3CcKYuFIEGlGrHIIgxunndqd9DMfa75k+nRVgNSyl599d7d9Gh53wf2VNu53375Juv7bg+v+pD6pP8DbRS1XlrC/YS5B5uHILGZHZiXIFKdxqZL44pbA2YnYpRAbacQXaU4lL/2wleriuVP348z73BFextamPZHwJAS/3EvaTpPJb8jwPtyahTv3MdiIJa3wTmbWtrl55tKM7Unpear8sXd67eS/Cw9e2aMhCWaLyXMlXolZ6YVt82f/qD4QuzlgpKrrmNHdeOGlmutin6lOHP3h2MOE8Rr+cBqjGXmR0FadR7bjSWe87kdrlY93tLf9sCsaXn4Er1SSNtgIqm+P66dmafgOMvm9d1dvDsKbHFkyjuxlRmE/KTG9qVwmLcL1mA1b1u/UqGLNF02arCK1pHLPJxgTbwcsbSbVONkDR1uAbDC4E279CtfEjtjkQR8Nn3SP0djnECfiQ6xJe+EVoDdk2vHskXnJMbK9A3b48fh22XimsNSjRZkn67fKbb550PXJh3hyS+vJtGTl3NXW5nKccJMEsitf4LHfASsfDDzbud34Xho+cTyj2X868djPYQF8czJxLnFSxS+btTSOV+ADcc+0J/Mux2AutrVM/iJl7cGh5gOIaQzpwstNmwmvfxxrbunoZy5fHfdce/z5VvPLr/CCV9yNVuKLDN22mdsLr7MsMNN272XOym1nmp8pxg7F+jdm7r8pC5Txwod7p0Wp5Kb7ZNyNZsLxw2Za18fkOzZo2uIr5lLN1s1bdvB4Nb7HXCxz6IRnS/duXOYni42NDufJapLGyDuYT5MrTxzddfKUzy7P8b5hY8cdCUtQHzWKnbX+xy3r1m/+cf3MmCkzZ05RK74V3pPJxXY0l+eSLByLV+aSlXgyvp5bZi1X2pgrlA9LurDnZGImd5aZyhtmbXDvrSYXCnGGFCuH3yBy+fc6GN3M5cGyVLimoJh72kXgxGEZ9mX3LN+zZjd/f9ulE9cabli3SKMuEL7AOctpyNAeUfxU82Wbtqjkf620lA03b8rKlSNk/HKZ3NnczSlZrrydfCRDvb5XnFTOaNYsXTPJnB8qlW8QvuL5WKqZsTxaruwh1axZvP40ZjeCSimQcldf56w6YC58UW/V76psKbYj7MYxM+cs0fBw5QrNGp5L2X51Tmu1pbRFVliWTKpxjLRUEam09aA5ETyXM2eBJk2mJPaYnX56/ZplGv6e8BK6uXAmYtCaAjWWSt84/iS+AC5rV7HqjbTg6prtAHL1So1GDZfOWTpzDGGnEzu+oxR0TId5Gt5B/CDgvGYqBeYYeSrmB5rLt8i2L9u2cjOftuXaGblXyNTQ4NAfjoH07DfnMizMOQs5PqUkQ0AHynArXO9FPjbDtezzSYOBAyJ9goUXXhptuI2Ncd2GFxOiNepfHjAaj50dSUhr4kec+dd+ylPXEx7knRvWpcvYoY5tBxTl8IpCPFBJnLAy9sbm9VCrcebCOx/rvyzEalzP7jVRDRwQ7hsifCOzxoZboJ3NAHIUQM5hNCN2dyJhLUgwcSXjMEPq49b8kmdK2z5vnp+5fvph3gU3h86j3RzVCu3yVmS2tPkgG/lm83UlPI6eKZPK0+jz+A8l8RQ/RDgKjwFt0AF7wtAAORlDRhE4Tjz5NDNQhrWglvbYAdcmZqQL/ITcgdgT4Th0Lc22eb+cObP12vHg7T4reN0LOD1iRbnrL5PrvnBqiZu9/AP0gzlhf7X+jsfD8WQmuczRAc+VHt6y3E8WMyUKOog1cd3mwSSyTzK82nfv79G1WZ+MNBnpuCVG6/By/m1z7lJ/c277b22F97pOUmpSbLEF/FAuNsd1rbJIIw/fKfPNv12/bAu/ATdi8PpsUshOJA8uxDKaM3tSHt4fZ2/XdXy3Nu53NLxi5sVUHl9oJZWnaHK1e3bKuHPdhd6cq9TcaYmb4abvXuNGmGv1hrQc6RcNUDcu3cJvwi0ZvC2XaAHqm0sxjCZpf8qz1MEdHHoN69R8eDpANd0u4zKaCHIy2JwzHWnOyYbKzPAsFgfjJsCsKBxJmmAlCVaTWXIzbI1rgKxYyvdsnR0TFTU3Ijp2lUa+KUImN9OOySVv2GXA87wDeIYKK6yzgOf2A4hKw6eNBsR5+ffOjXXhiSMpnkBWqKYtm7p8ivB2ztWpZDWrUJatF9/0SSSDe3nGCj1ZTlqDqqZJWzlujRXYCFvLiRc0oS3xlOfJNHK8XUma3APiumDHe8DUptjSGTclnYmjM2lKmvJFS5Wvjpe8Kjph1by5l1WL5l4lr3hFXLy5HBSiPN1smAyvBV4K7+ucIHNfcUglH/O81KMVmSWdsmzGfHO/h5Nk8g2ss7k8xnyOTO4uK5MQb3eZIu/GIA2f8IjRyLPx39lycmyeTE40cTK58i42OQH8cVBhS2/coAeW8R103xltQBqrSEt/0tKZNOIVKdjx8otU6mgmtr9PYx/5OXONMLJmvGXxEJIhDqyhupdxeuPfGEKxpA9JYprgpBagMXEjf9wSt1ThxkdwA+H7px3YHkTmDShA7zicINZ3he+fKouKWwrv7AwzV5hp6z4mvNbXgSUDCHOi77PzwsflNgij45JJ4SpyhbSRKrSOyu9knW+5ZqvlqS8uY8cU6sB9bJ9BHxAGFvtcklKKAPmvcevN5T9jTxiL/3B78+bdNdyW12rIzw64T1l7qfXwScPd3fcW8D+3lMrztnwPEoGf7pE5C+/g9GDkKbjztexbFP4pncaD5EpCF/SGEZi6cV3De6Qwmm+83FzHnLjIYxY7bcNtVMIrOF+z+LL2JXO9zKsTviDdvx7GpGkxU/x4hd9IlUYmv4lvpFCnHmGzdDpJeO9lArSU8HZGcgz63vLb5vI8p8w0GJLHLDEnjcoclS9YeSnaLGPlhaBcWDk+MB9gaKWxFO50n74jzwV9u3hmQG/5jS27wZrrYy6fL9tqfvq1vBhGfDleosRRZMkjvARHZpJIvKQzWUKiWLnuZZp7Zd6TJnnL42SU/K45nlooZ4gRKzRqslZCkn8yJ8llEpzcQnjLZud7LJfTpbQ7y6U8TCOdWUWcLA9wxWIWtqdfa394LdfwuVJ5e1ZxzPwvD6NX7HztGuageUxRrKkcmijnccrNR1l9bnXq0K+fIyguux3mcmVxIcBOJ2OVhTiW3bH4hxiZ/M2WSzL5s1JprBzXziC18VhrMpbU7IZryslx4pNdahyLw2Op9AIaaErIJQmsYh5QH6Nlb1GX5abHi/HhQjlbMNxcniUTaumcWfJ7x0NgJcbiVblkFQzpN3Ll0uyzozp0GOnRQa3Ixc8zsVWsXJnKyjXqZbrXYDrqXoOpTDkjs2EV90q7p5nKY0rvAMNiStOhOtr1ZvKHTx7Ki1xf4hXZHYu4p/J95umFclI3G3d8iHdlU/J9Jw5t3sTLn8qewnhWJNc6Q30GdsjpgLtxOcJLMYdma10AHr6SSWEKX1HK457h7o/xqWeUPO4FPpqLO+VScmJBzilxN7xarnzJHscjhVdjqrgMkEJbOVHFxJTuBBDa0zF4SCyVLC/EJkU4JJ8GaVqSiZfAqS3PQYz6Koug/YgXtpWv0ahAOflevgb1QLlgTLjJKUSx4D+iGh3RDIR6WiA/hAIQmovQHoQ0CAUhtBahHUJIC21FaBNC2xH6GaGZSFgBH4lQBELzEfoeoW8RmoLQjwhtROgnhKYjtB+hXyh0EKF9CB1AaAkCFxUdQ+iwBJ1E6LgEbUDoFEJnhPgTOotQEkK7EVqG0CWEzkvQZYR+QOg7hK4jdJVCNxFKRugGEsJPtxC6g9BtCbqP0F0J2oVQOkIPEcqgUBZCDxDaLK5tyEXosQQ9EWJi6DdELbRBKxGVoEBLEVqFqF8VaDlCaxB1X47OIfQIUU+U6AqitDT6FaGniCpDyB9Rf9FoFkI83WOMME3TKOBnbdu2bdu617Zt27Zt27Zt27Z3v31zkjPJlVRV+s9kJp3qP12R8Bky+e7gNMLksPkg4oIEyCFzBkEeYXA8IkQEB6iRQeha7MEF8BmS+RLIDyKIEIC/2NfCiBkCBElForYVctbj+EgXFXu9cPyBc1ZN0RbC1Slqki4SslI6iypO4N0ROzJkC6vnZKKsoryiXNE/yHys9ykspq3i5hR016TZ+NrEPLQ0TLAssmUKvSG60dYsNUtupFjUkfE0KSQT
*/