/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN
    template <>
    struct as_vector<1>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1;
            typedef typename fusion::result_of::value_of<I0>::type T0;
            typedef vector1<T0> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(*i0);
        }
    };
    template <>
    struct as_vector<2>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1;
            typedef vector2<T0 , T1> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0);
            return result(*i0 , *i1);
        }
    };
    template <>
    struct as_vector<3>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2;
            typedef vector3<T0 , T1 , T2> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1);
            return result(*i0 , *i1 , *i2);
        }
    };
    template <>
    struct as_vector<4>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3;
            typedef vector4<T0 , T1 , T2 , T3> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2);
            return result(*i0 , *i1 , *i2 , *i3);
        }
    };
    template <>
    struct as_vector<5>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4;
            typedef vector5<T0 , T1 , T2 , T3 , T4> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3);
            return result(*i0 , *i1 , *i2 , *i3 , *i4);
        }
    };
    template <>
    struct as_vector<6>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5;
            typedef vector6<T0 , T1 , T2 , T3 , T4 , T5> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5);
        }
    };
    template <>
    struct as_vector<7>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6;
            typedef vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6);
        }
    };
    template <>
    struct as_vector<8>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7;
            typedef vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7);
        }
    };
    template <>
    struct as_vector<9>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8;
            typedef vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8);
        }
    };
    template <>
    struct as_vector<10>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9;
            typedef vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9);
        }
    };
    template <>
    struct as_vector<11>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10;
            typedef vector11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10);
        }
    };
    template <>
    struct as_vector<12>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11;
            typedef vector12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11);
        }
    };
    template <>
    struct as_vector<13>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12;
            typedef vector13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12);
        }
    };
    template <>
    struct as_vector<14>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13;
            typedef vector14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13);
        }
    };
    template <>
    struct as_vector<15>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14;
            typedef vector15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14);
        }
    };
    template <>
    struct as_vector<16>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15;
            typedef vector16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15);
        }
    };
    template <>
    struct as_vector<17>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16;
            typedef vector17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16);
        }
    };
    template <>
    struct as_vector<18>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17;
            typedef vector18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17);
        }
    };
    template <>
    struct as_vector<19>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18;
            typedef vector19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18);
        }
    };
    template <>
    struct as_vector<20>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19;
            typedef vector20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19);
        }
    };
    template <>
    struct as_vector<21>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20;
            typedef vector21<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20);
        }
    };
    template <>
    struct as_vector<22>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21;
            typedef vector22<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21);
        }
    };
    template <>
    struct as_vector<23>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22;
            typedef vector23<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22);
        }
    };
    template <>
    struct as_vector<24>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23;
            typedef vector24<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23);
        }
    };
    template <>
    struct as_vector<25>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24;
            typedef vector25<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24);
        }
    };
    template <>
    struct as_vector<26>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25;
            typedef vector26<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25);
        }
    };
    template <>
    struct as_vector<27>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26;
            typedef vector27<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26);
        }
    };
    template <>
    struct as_vector<28>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27;
            typedef vector28<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27);
        }
    };
    template <>
    struct as_vector<29>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28;
            typedef vector29<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28);
        }
    };
    template <>
    struct as_vector<30>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29;
            typedef vector30<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29);
        }
    };
BOOST_FUSION_BARRIER_END
}}}

/* as_vector30.hpp
EI36ebG0+aOq02Lvmuth+LaBHMM2cfs/yfeJ0/gh9Tb+Yl3vlBhTrruU+AlJBte/22m+M+vl3tC59wvEn+ubrg3qtKYl/Ba8Qur/FsVLYsJ2Kfv5V0v9uY+2+7AuTX4a28/nMLTNOxqh/V6vvU7UlX5yciwekWMx/zc3TQ4QLhXFN3y3fDz2lXXm6OQh+J55C6+5WeUD6EX9aY4oki72ipsQHxWTUtp8BCfV3Aja9beoZx+Dfop53a+XvP7S5iU46UJuhuI6rdXJBXCZ94do6vRgzKQJVIhDXbktMlerdPkBLjbQz93RWycu/wrzZjpff6lj9S+60C49i9tF6uVBuUPa5iPl+JR62eesiJlMiyQkuFAf688kv/r6uTEKr7v9qbkx8urb52X4hHndbzhYrzEtJa4U661u19bYQPKF2dSlSwP9PB0hN9z+sjwdxXXJbWC/33fz/mypi+SJ6DGo35AHS7vPi699Nb3t93kTVpins47S7m8/D/39vcLbfn9/qhxneuuUbBylyQfzq04+jgc1OUi0bdDCx74+n1Mfn9/t61PaY4+62O1vvnfLsaetx3of+2OvKRWK0KlHaY87Pw/nx13x9cbL1/64K1C+W9vUIzT0wf49h4b2Ke2x11bWk+Vrf+ztYz35mvXcei4W6/u/kzrbNJ91FWnWpW6J0/VZb0dIQ/0cNu433f6wHDbF6ypoaH+s5jBvkHZdylHq8rrUNrP73YVj1KYdQxvp567JvOn2l+SuCf4Lctfo5ypxnNNGP7eMo1w3jnPOhJimH/5b9LOveVx651StMcc+mrmt2Z+fG+e/PdeNfu6X/7wcOPo5bRznwNHPdeM4p81KU04bw8W+N4z5g6IvbH3YuGj3nl4l57QJMkj/Lun35cm5VQnby1l6r8QydkRfDMRm2AlbYGe8iAEUoyyntSynAvrJcgrKEduFe7EZ7sPiGMA8eV+GvM86BpB46MyaWBm98DZsiVWwA1bFvlgNB+PtGI5uOBbvwHSsjuZ6Sh8ovFOnnjlKjDy+iNVxEarbV8L7npf3zZf3LbB6X7bj9xEzzvvwLqyOd1vVM0/e10vnfbsldnUPdsNPZX1hBumrg+PlfVVwkLzvfdkP29Ab89Eft2NH3IEDcCeG4YcYi/+Q5UeUkz430hfHU/pphMpv0dOo/134KPrgDPTHx7EtzsTh+ASG45MYi1k4A2fhXHwa5+MzmIvPYh5m47v4HJ7AeXgKF2Id6vACdsUc7ImLMRKXYjwuwyR8CWdhLj6LL+NyfAVX4XLchivwG3wVT+BreApXSm6RVVgJ1+C9uBYfwTdwJOZhLK7D6bgen8CNuAQ34Wu4GVfhFtn/nuWkb4/0+VHa2Uc5rsvJfpR23ob1MB/9cDu2wB3YAXdiD/wQY/AfOAE/lvb9BJfgbnwN9+A6/BTz8TP8DD/H37EAK1CHfVgbv8B6+CV2wgPS7gexH36NY/AQZuA3mImHMQuP4NN4FNfjMdyCx/EonsQf8Ts8h99L+2SXkz5B0lfIk9JaOb6UCZKDwx+rYFusil2wGvbB2/F+vBOHojtmYA2cjjVxLtbCd9ETd2Ad/B7r4Rn0xjtYpw/ehQ2xGTbCwdgYH8JmGI7NMQFbYDa2wgXYBt/GtngA2+NR7IDH8F78ETvieQzEG3gf1lJyG2B97IwNsQsGYFfsgN0wFrvjeAzCadgD52FPnI+9cB/2wa+xL97AYKxEG9+Pd+JgrINDsD4+gKbrVgXpVyT9jWg303NDP+TF78WSywqb4Unshd/hWPwBk/BHzMTTmIVn8Bk8iy/hOVyJ53EtFuFOvIh78RJ+iz/jT3gFlUr9gtXxKtbD3/AevIYD8To=
*/