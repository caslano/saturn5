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
BOOST_FUSION_BARRIER_END
}}}

/* as_vector10.hpp
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
*/