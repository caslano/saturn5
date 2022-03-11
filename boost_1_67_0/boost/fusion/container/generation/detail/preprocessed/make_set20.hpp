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
        struct make_set;
        template <>
        struct make_set<>
        {
            typedef set<> type;
        };
    }
    
# if defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# else
    BOOST_CONSTEXPR
# endif
    BOOST_FUSION_GPU_ENABLED
    inline set<>
    make_set()
    {
        return set<>();
    }
    namespace result_of
    {
        template <typename T0>
        struct make_set< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type>
    make_set(T0 const& arg0)
    {
        return set<typename detail::as_fusion_element<T0>::type>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct make_set< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>
    make_set(T0 const& arg0 , T1 const& arg1)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct make_set< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct make_set< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct make_set< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct make_set< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>
    make_set(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18 , T19 const& arg19)
    {
        return set<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* make_set20.hpp
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
*/