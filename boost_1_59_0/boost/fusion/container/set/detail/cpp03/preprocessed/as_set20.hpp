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
    struct as_set<1>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1;
            typedef typename fusion::result_of::value_of<I0>::type T0;
            typedef set<T0> type;
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
    struct as_set<2>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1;
            typedef set<T0 , T1> type;
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
    struct as_set<3>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2;
            typedef set<T0 , T1 , T2> type;
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
    struct as_set<4>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3;
            typedef set<T0 , T1 , T2 , T3> type;
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
    struct as_set<5>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4;
            typedef set<T0 , T1 , T2 , T3 , T4> type;
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
    struct as_set<6>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5> type;
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
    struct as_set<7>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
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
    struct as_set<8>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
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
    struct as_set<9>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
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
    struct as_set<10>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
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
    struct as_set<11>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> type;
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
    struct as_set<12>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> type;
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
    struct as_set<13>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> type;
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
    struct as_set<14>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> type;
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
    struct as_set<15>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> type;
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
    struct as_set<16>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> type;
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
    struct as_set<17>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> type;
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
    struct as_set<18>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> type;
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
    struct as_set<19>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> type;
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
    struct as_set<20>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> type;
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
BOOST_FUSION_BARRIER_END
}}}

/* as_set20.hpp
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
*/