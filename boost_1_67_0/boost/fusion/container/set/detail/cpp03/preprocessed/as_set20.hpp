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