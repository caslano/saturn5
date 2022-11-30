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
    template <>
    struct as_set<21>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20> type;
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
    struct as_set<22>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21> type;
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
    struct as_set<23>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22> type;
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
    struct as_set<24>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23> type;
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
    struct as_set<25>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24> type;
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
    struct as_set<26>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25> type;
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
    struct as_set<27>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26> type;
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
    struct as_set<28>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27> type;
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
    struct as_set<29>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28> type;
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
    struct as_set<30>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29> type;
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
    template <>
    struct as_set<31>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30);
        }
    };
    template <>
    struct as_set<32>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31);
        }
    };
    template <>
    struct as_set<33>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32);
        }
    };
    template <>
    struct as_set<34>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33);
        }
    };
    template <>
    struct as_set<35>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34);
        }
    };
    template <>
    struct as_set<36>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33); typename gen::I35 i35 = fusion::next(i34);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35);
        }
    };
    template <>
    struct as_set<37>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33); typename gen::I35 i35 = fusion::next(i34); typename gen::I36 i36 = fusion::next(i35);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36);
        }
    };
    template <>
    struct as_set<38>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33); typename gen::I35 i35 = fusion::next(i34); typename gen::I36 i36 = fusion::next(i35); typename gen::I37 i37 = fusion::next(i36);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37);
        }
    };
    template <>
    struct as_set<39>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38; typedef typename fusion::result_of::next<I38>::type I39;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37; typedef typename fusion::result_of::value_of<I38>::type T38;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33); typename gen::I35 i35 = fusion::next(i34); typename gen::I36 i36 = fusion::next(i35); typename gen::I37 i37 = fusion::next(i36); typename gen::I38 i38 = fusion::next(i37);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38);
        }
    };
    template <>
    struct as_set<40>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38; typedef typename fusion::result_of::next<I38>::type I39; typedef typename fusion::result_of::next<I39>::type I40;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37; typedef typename fusion::result_of::value_of<I38>::type T38; typedef typename fusion::result_of::value_of<I39>::type T39;
            typedef set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8); typename gen::I10 i10 = fusion::next(i9); typename gen::I11 i11 = fusion::next(i10); typename gen::I12 i12 = fusion::next(i11); typename gen::I13 i13 = fusion::next(i12); typename gen::I14 i14 = fusion::next(i13); typename gen::I15 i15 = fusion::next(i14); typename gen::I16 i16 = fusion::next(i15); typename gen::I17 i17 = fusion::next(i16); typename gen::I18 i18 = fusion::next(i17); typename gen::I19 i19 = fusion::next(i18); typename gen::I20 i20 = fusion::next(i19); typename gen::I21 i21 = fusion::next(i20); typename gen::I22 i22 = fusion::next(i21); typename gen::I23 i23 = fusion::next(i22); typename gen::I24 i24 = fusion::next(i23); typename gen::I25 i25 = fusion::next(i24); typename gen::I26 i26 = fusion::next(i25); typename gen::I27 i27 = fusion::next(i26); typename gen::I28 i28 = fusion::next(i27); typename gen::I29 i29 = fusion::next(i28); typename gen::I30 i30 = fusion::next(i29); typename gen::I31 i31 = fusion::next(i30); typename gen::I32 i32 = fusion::next(i31); typename gen::I33 i33 = fusion::next(i32); typename gen::I34 i34 = fusion::next(i33); typename gen::I35 i35 = fusion::next(i34); typename gen::I36 i36 = fusion::next(i35); typename gen::I37 i37 = fusion::next(i36); typename gen::I38 i38 = fusion::next(i37); typename gen::I39 i39 = fusion::next(i38);
            return result(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19 , *i20 , *i21 , *i22 , *i23 , *i24 , *i25 , *i26 , *i27 , *i28 , *i29 , *i30 , *i31 , *i32 , *i33 , *i34 , *i35 , *i36 , *i37 , *i38 , *i39);
        }
    };
BOOST_FUSION_BARRIER_END
}}}

/* as_set40.hpp
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
*/