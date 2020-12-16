
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
bb63dXxsL3ifAnwOz0zRr7t+X3ydft1xLt/pP3wC6eLzaDrqn/LKq8ZzgbhRKD7QebvEgQWv8JdliTPuqWi8Hp7pLZ9MpU/cRJcu8P7OIy61z7e9iac8Bie1qvPWi7uv23cX0aUPw0dS4IJ/eY4m40BfW09fqFTvWLwYrvU5uS+Z/+B8YLpYkn2zHP+qUr+JPxnuftd72Tc1K/XPrfE+H/MdfIenxPIvHEonSqIHdIbpNOrmT1qHF/SVx4P7MiLmRXxJ5WdowpMCPeFC6xQPzcfninaJ141wsPydH6V+scW49QnzMeI7L+OZj0acA6wO6Hsat6uHLBWvbwjOaYHDP+5NFxO/R/Z0L6bnwwvqXqGjTpQvxO0OeCPrHnhqHX0rF3903kbDS0GeMI5B/zA9OcF8zaGjt000Lt320YtwUsCv+vI59RafjW/Vg+LPJfQz8a9Zvm7N4y+7HE9uw7sH8uXSEzPNd82h9Gl6YUIr3epaeexjcSY4H2m1/u6jI/aL9UHH6JzOV9VGJ3iC3ljL73cz/+DT9kE+HV9fWZ51n7maDmR8qvCijG/grHfEiynq33BP44P4GL2kXj2kqMu+XyRur6PD3+h96B7hCZ57p/V0DjxT4fPoZNuuDtGH6Uan/I+pe4FPqB0DAH4QQhjCMMx97nMfhmEYhmEYhmEYhhBCGMIQhhCGEEIYQghDCCEMIYQhhBBCLv/s+PHx/07b2nOe93nfc3a6PH3h+8TuGP49ukD4uKccPp8evt7/rWK4vv4RPm4Lx/GD8O/RMz4cvi72ufDx1yXC14P/GD6uPQyvT8J1+qrwfapPCj+H623XDd+f/7lw/YTXs7cOx3PtO4fPQ4XXLZf9VPh8V/j82d174XVl+HzqV8LXRf8UPt59djsIj7/w+mUp/Ht9nfD8+L7w+uyq4d/V8PnWW4TPA/31guG8RcPHp73w/XvhfD/gdeH83Da8Hg3n/WHnDR/XnCd8PPTG8PWLD58jfP9Q+N817Vwg/LtzVod3Xit8PuVt4bzdJKzvXNivWQjPz+HnKF9wLRxPeDzf9J5hfs85R3j8h/Menpe/Ep4XHxkNz6vh128Lz7PXDuflAeG8/OPX4XVu+LzGd58V1iH8u/iJW4bH+9vPET7+CR8f/Ck8L9wsnK/Xh+/bnQvPu9Hw86lveq7w/Zb/fb95eB14ufA64p/h83zhdf1rHxqO6zfh+5jD9y3eejr873y8Ney7fFv4ekp4/Xzf8P39V/ho+Hfzb+Hjx3C+v/uA8LgNn6+6yEX/+7nS4fHxsfBxevh+9HP3wtcBzh32AYTnsZffJXwdObwOeup7wvw+Fh43rwvfd9sO3ycTPr7/YtgX+st/hOO7dni9ecfw+uR64eO/bDif9w7/PrwufN46PJ88/lLh63I3DP8O3ze8PnlEOB8XDfM++u/zmuH7td8SPi8fnr+/fovwuu6x4eOSd4THaz/sKwqvx27x8vBxSfh8+Tn+EF6HbIfHUdiXePln/f1f/vnnv/6z+cs/fvepf/zuX/908wf+/SzbT/zrH/+a/P9xf/3Lv/71nWc96x//mvzzrE/9618/mtz4+3cm/5rc80F//k+gyc+f+dd/Pesv/5r82qf+9Yx/ufX3f/zlX7/719Mnd/jP7//uh//806d+Nz776lP+969/iHCWyOTHgk928cnJz//q61v968//if33f33ya/+5549EvdW/wnhv+s+Nv//Fzd/97j/f+ue/+pMk3/ivH/0ny198apLEPx74r7OsnzUZ7N/t5T/7+tS/fvfPf/3xX7/762T8k5//6FZP+edv/i7evz41SeuP/5jc+S+Tnb7pcZ+ajOlT3//7v35zluY=
*/