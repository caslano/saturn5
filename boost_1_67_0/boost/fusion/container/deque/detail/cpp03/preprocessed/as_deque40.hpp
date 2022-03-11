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
    struct as_deque<1>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1;
            typedef typename fusion::result_of::value_of<I0>::type T0;
            typedef deque<T0> type;
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
    struct as_deque<2>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1;
            typedef deque<T0 , T1> type;
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
    struct as_deque<3>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2;
            typedef deque<T0 , T1 , T2> type;
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
    struct as_deque<4>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3;
            typedef deque<T0 , T1 , T2 , T3> type;
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
    struct as_deque<5>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4;
            typedef deque<T0 , T1 , T2 , T3 , T4> type;
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
    struct as_deque<6>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5> type;
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
    struct as_deque<7>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
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
    struct as_deque<8>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
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
    struct as_deque<9>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
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
    struct as_deque<10>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
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
    struct as_deque<11>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> type;
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
    struct as_deque<12>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> type;
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
    struct as_deque<13>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> type;
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
    struct as_deque<14>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> type;
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
    struct as_deque<15>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> type;
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
    struct as_deque<16>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> type;
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
    struct as_deque<17>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> type;
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
    struct as_deque<18>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> type;
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
    struct as_deque<19>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> type;
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
    struct as_deque<20>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> type;
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
    struct as_deque<21>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20> type;
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
    struct as_deque<22>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21> type;
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
    struct as_deque<23>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22> type;
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
    struct as_deque<24>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23> type;
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
    struct as_deque<25>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24> type;
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
    struct as_deque<26>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25> type;
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
    struct as_deque<27>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26> type;
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
    struct as_deque<28>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27> type;
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
    struct as_deque<29>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28> type;
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
    struct as_deque<30>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29> type;
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
    struct as_deque<31>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30> type;
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
    struct as_deque<32>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31> type;
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
    struct as_deque<33>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32> type;
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
    struct as_deque<34>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33> type;
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
    struct as_deque<35>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34> type;
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
    struct as_deque<36>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35> type;
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
    struct as_deque<37>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36> type;
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
    struct as_deque<38>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37> type;
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
    struct as_deque<39>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38; typedef typename fusion::result_of::next<I38>::type I39;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37; typedef typename fusion::result_of::value_of<I38>::type T38;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38> type;
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
    struct as_deque<40>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9; typedef typename fusion::result_of::next<I9>::type I10; typedef typename fusion::result_of::next<I10>::type I11; typedef typename fusion::result_of::next<I11>::type I12; typedef typename fusion::result_of::next<I12>::type I13; typedef typename fusion::result_of::next<I13>::type I14; typedef typename fusion::result_of::next<I14>::type I15; typedef typename fusion::result_of::next<I15>::type I16; typedef typename fusion::result_of::next<I16>::type I17; typedef typename fusion::result_of::next<I17>::type I18; typedef typename fusion::result_of::next<I18>::type I19; typedef typename fusion::result_of::next<I19>::type I20; typedef typename fusion::result_of::next<I20>::type I21; typedef typename fusion::result_of::next<I21>::type I22; typedef typename fusion::result_of::next<I22>::type I23; typedef typename fusion::result_of::next<I23>::type I24; typedef typename fusion::result_of::next<I24>::type I25; typedef typename fusion::result_of::next<I25>::type I26; typedef typename fusion::result_of::next<I26>::type I27; typedef typename fusion::result_of::next<I27>::type I28; typedef typename fusion::result_of::next<I28>::type I29; typedef typename fusion::result_of::next<I29>::type I30; typedef typename fusion::result_of::next<I30>::type I31; typedef typename fusion::result_of::next<I31>::type I32; typedef typename fusion::result_of::next<I32>::type I33; typedef typename fusion::result_of::next<I33>::type I34; typedef typename fusion::result_of::next<I34>::type I35; typedef typename fusion::result_of::next<I35>::type I36; typedef typename fusion::result_of::next<I36>::type I37; typedef typename fusion::result_of::next<I37>::type I38; typedef typename fusion::result_of::next<I38>::type I39; typedef typename fusion::result_of::next<I39>::type I40;
            typedef typename fusion::result_of::value_of<I0>::type T0; typedef typename fusion::result_of::value_of<I1>::type T1; typedef typename fusion::result_of::value_of<I2>::type T2; typedef typename fusion::result_of::value_of<I3>::type T3; typedef typename fusion::result_of::value_of<I4>::type T4; typedef typename fusion::result_of::value_of<I5>::type T5; typedef typename fusion::result_of::value_of<I6>::type T6; typedef typename fusion::result_of::value_of<I7>::type T7; typedef typename fusion::result_of::value_of<I8>::type T8; typedef typename fusion::result_of::value_of<I9>::type T9; typedef typename fusion::result_of::value_of<I10>::type T10; typedef typename fusion::result_of::value_of<I11>::type T11; typedef typename fusion::result_of::value_of<I12>::type T12; typedef typename fusion::result_of::value_of<I13>::type T13; typedef typename fusion::result_of::value_of<I14>::type T14; typedef typename fusion::result_of::value_of<I15>::type T15; typedef typename fusion::result_of::value_of<I16>::type T16; typedef typename fusion::result_of::value_of<I17>::type T17; typedef typename fusion::result_of::value_of<I18>::type T18; typedef typename fusion::result_of::value_of<I19>::type T19; typedef typename fusion::result_of::value_of<I20>::type T20; typedef typename fusion::result_of::value_of<I21>::type T21; typedef typename fusion::result_of::value_of<I22>::type T22; typedef typename fusion::result_of::value_of<I23>::type T23; typedef typename fusion::result_of::value_of<I24>::type T24; typedef typename fusion::result_of::value_of<I25>::type T25; typedef typename fusion::result_of::value_of<I26>::type T26; typedef typename fusion::result_of::value_of<I27>::type T27; typedef typename fusion::result_of::value_of<I28>::type T28; typedef typename fusion::result_of::value_of<I29>::type T29; typedef typename fusion::result_of::value_of<I30>::type T30; typedef typename fusion::result_of::value_of<I31>::type T31; typedef typename fusion::result_of::value_of<I32>::type T32; typedef typename fusion::result_of::value_of<I33>::type T33; typedef typename fusion::result_of::value_of<I34>::type T34; typedef typename fusion::result_of::value_of<I35>::type T35; typedef typename fusion::result_of::value_of<I36>::type T36; typedef typename fusion::result_of::value_of<I37>::type T37; typedef typename fusion::result_of::value_of<I38>::type T38; typedef typename fusion::result_of::value_of<I39>::type T39;
            typedef deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39> type;
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

/* as_deque40.hpp
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
*/