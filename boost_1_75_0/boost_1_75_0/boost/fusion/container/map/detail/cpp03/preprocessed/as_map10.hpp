/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN
    template <bool is_assoc>
    struct as_map<1, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0;
            typedef map<T0> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            
            return result(gen::D0::call(i0));
        }
    };
    template <bool is_assoc>
    struct as_map<2, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1;
            typedef map<T0 , T1> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0);
            return result(gen::D0::call(i0) , gen::D1::call(i1));
        }
    };
    template <bool is_assoc>
    struct as_map<3, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2;
            typedef map<T0 , T1 , T2> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2));
        }
    };
    template <bool is_assoc>
    struct as_map<4, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3;
            typedef map<T0 , T1 , T2 , T3> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3));
        }
    };
    template <bool is_assoc>
    struct as_map<5, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4;
            typedef map<T0 , T1 , T2 , T3 , T4> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4));
        }
    };
    template <bool is_assoc>
    struct as_map<6, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4; typedef pair_from<I5, is_assoc> D5; typedef typename D5::type T5;
            typedef map<T0 , T1 , T2 , T3 , T4 , T5> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4) , gen::D5::call(i5));
        }
    };
    template <bool is_assoc>
    struct as_map<7, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4; typedef pair_from<I5, is_assoc> D5; typedef typename D5::type T5; typedef pair_from<I6, is_assoc> D6; typedef typename D6::type T6;
            typedef map<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4) , gen::D5::call(i5) , gen::D6::call(i6));
        }
    };
    template <bool is_assoc>
    struct as_map<8, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4; typedef pair_from<I5, is_assoc> D5; typedef typename D5::type T5; typedef pair_from<I6, is_assoc> D6; typedef typename D6::type T6; typedef pair_from<I7, is_assoc> D7; typedef typename D7::type T7;
            typedef map<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4) , gen::D5::call(i5) , gen::D6::call(i6) , gen::D7::call(i7));
        }
    };
    template <bool is_assoc>
    struct as_map<9, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4; typedef pair_from<I5, is_assoc> D5; typedef typename D5::type T5; typedef pair_from<I6, is_assoc> D6; typedef typename D6::type T6; typedef pair_from<I7, is_assoc> D7; typedef typename D7::type T7; typedef pair_from<I8, is_assoc> D8; typedef typename D8::type T8;
            typedef map<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4) , gen::D5::call(i5) , gen::D6::call(i6) , gen::D7::call(i7) , gen::D8::call(i8));
        }
    };
    template <bool is_assoc>
    struct as_map<10, is_assoc>
    {
        template <typename I0>
        struct apply
        {
            typedef typename fusion::result_of::next<I0>::type I1; typedef typename fusion::result_of::next<I1>::type I2; typedef typename fusion::result_of::next<I2>::type I3; typedef typename fusion::result_of::next<I3>::type I4; typedef typename fusion::result_of::next<I4>::type I5; typedef typename fusion::result_of::next<I5>::type I6; typedef typename fusion::result_of::next<I6>::type I7; typedef typename fusion::result_of::next<I7>::type I8; typedef typename fusion::result_of::next<I8>::type I9;
            typedef pair_from<I0, is_assoc> D0; typedef typename D0::type T0; typedef pair_from<I1, is_assoc> D1; typedef typename D1::type T1; typedef pair_from<I2, is_assoc> D2; typedef typename D2::type T2; typedef pair_from<I3, is_assoc> D3; typedef typename D3::type T3; typedef pair_from<I4, is_assoc> D4; typedef typename D4::type T4; typedef pair_from<I5, is_assoc> D5; typedef typename D5::type T5; typedef pair_from<I6, is_assoc> D6; typedef typename D6::type T6; typedef pair_from<I7, is_assoc> D7; typedef typename D7::type T7; typedef pair_from<I8, is_assoc> D8; typedef typename D8::type T8; typedef pair_from<I9, is_assoc> D9; typedef typename D9::type T9;
            typedef map<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
        };
        template <typename Iterator>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator const& i0)
        {
            typedef apply<Iterator> gen;
            typedef typename gen::type result;
            typename gen::I1 i1 = fusion::next(i0); typename gen::I2 i2 = fusion::next(i1); typename gen::I3 i3 = fusion::next(i2); typename gen::I4 i4 = fusion::next(i3); typename gen::I5 i5 = fusion::next(i4); typename gen::I6 i6 = fusion::next(i5); typename gen::I7 i7 = fusion::next(i6); typename gen::I8 i8 = fusion::next(i7); typename gen::I9 i9 = fusion::next(i8);
            return result(gen::D0::call(i0) , gen::D1::call(i1) , gen::D2::call(i2) , gen::D3::call(i3) , gen::D4::call(i4) , gen::D5::call(i5) , gen::D6::call(i6) , gen::D7::call(i7) , gen::D8::call(i8) , gen::D9::call(i9));
        }
    };
BOOST_FUSION_BARRIER_END
}}}

/* as_map10.hpp
MrgeTJeu4d7JYsltGS9J/4Bh0ICsIbK1wO00yh0/yFFmcD+zrFFyIPuNc+2jnKWP0h7FnnXNaFHDlTTKDxKlrkVm51yMHqf59f269wbR9zwk2bF+M8Lat6huORVHRQ654DpZym4ZpZZFRXkiVZVgWN38+tMmXptssJ6ywnz8CJQLJ+ajqRUIhdejUHi72oZcId+GFg+eKSUw1Cfo88jbBTqu4I2xQszFxVcnq0DtGAIhhEJYdt2ukw6sW8q68ZPKIkG6XrPbrmjSA76afHgjWjmkfy/rPF9JoFMPje+S+HPt9lGJPD+SdVoqv6MAJizZ042HuFl/7+bw9y613gt1FgFxVgIu3VhYmmI0E3OWuciJtxAwR3RWymUtlw3ICs1Lr+RyFj522udx8bjwoJTH7hZx/QIu0WQP8qxwP01cbnYQFBQ51IogFFRYUPDveAUgo8H4ayvlv3qii7X8peHLLy0ZP9zlMdTK83Ray1/Cy18ilv+SMdbyl8BrB8bT3OLEiOXHUi5/iW2CsUo0LXFoy4AXka1wGaCOl/9LjzUyWn7djq1CLT8bzYFWeyqujulftickV49DAvRPodUDag/vp/D0e7hM42UwePozuMzkZTCNDpfhHE/UZeja+TCW4fzvD3cZNlwZtgyb3DS3bYyFbUaHy9DGWNiuY0N7ODa0WdjQbmHhJPc/WAaYZvOUX/eEwlJYK8r5ZDdwF/8F
*/