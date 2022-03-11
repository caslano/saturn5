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
        struct make_list;
        template <>
        struct make_list<>
        {
            typedef list<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<>
    make_list()
    {
        return list<>();
    }
    namespace result_of
    {
        template <typename T0>
        struct make_list< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type>
    make_list(T0 const& arg0)
    {
        return list<typename detail::as_fusion_element<T0>::type>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct make_list< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>
    make_list(T0 const& arg0 , T1 const& arg1)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct make_list< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct make_list< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct make_list< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18 , T19 const& arg19)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* make_list20.hpp
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
*/