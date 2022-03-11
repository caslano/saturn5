/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    namespace result_of
    {
        template <
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_ , typename T10 = void_ , typename T11 = void_ , typename T12 = void_ , typename T13 = void_ , typename T14 = void_ , typename T15 = void_ , typename T16 = void_ , typename T17 = void_ , typename T18 = void_ , typename T19 = void_
          , typename Extra = void_
        >
        struct make_deque;
        template <>
        struct make_deque<>
        {
            typedef deque<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<>
    make_deque()
    {
        return deque<>();
    }
    namespace result_of
    {
        template <typename T0>
        struct make_deque< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type>
    make_deque(T0 const& arg0)
    {
        return deque<typename detail::as_fusion_element<T0>::type>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct make_deque< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>
    make_deque(T0 const& arg0 , T1 const& arg1)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct make_deque< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct make_deque< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct make_deque< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>
    make_deque(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18 , T19 const& arg19)
    {
        return deque<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* make_deque20.hpp
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
*/