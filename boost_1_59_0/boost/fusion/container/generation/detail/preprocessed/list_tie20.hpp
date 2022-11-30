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
        struct list_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct list_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0&>
    list_tie(T0 & arg0)
    {
        return list<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct list_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1&>
    list_tie(T0 & arg0 , T1 & arg1)
    {
        return list<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct list_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return list<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct list_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return list<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return list<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* list_tie20.hpp
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
*/