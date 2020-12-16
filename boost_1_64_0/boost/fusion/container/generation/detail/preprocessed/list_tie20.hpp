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
gRvxS9yGB3E7foX78BDux8NSf77Gb/Ab/B0r0Uc5f2MH/AE74Y9SfmUm6f/DvZJ+5RZuq6T/F0n/7xiOxzAa/8Ah+CeOw79QBnhYyscHC7EOzkNfXIx+uAxPwzVYD1/Cs/AjrI+f4dn4KzbAJqSrCT6IgfgwNsNHsTm+hS3wbWwpvztxJulLw01SLwJwuO2ZTNZri7dgV7wVe+FcXI534Cqch0/hfNyARWgpNx/pu5I+LWX7vZVyk/PGItYLx3uwDy7GYbgUx+B9eBUuw3Qsxhn4oJTPw/g8rsCt+AgexJX4Da7GRsT1KDbHNdgfH8OB+ARm4lrMwRKcg+twOT6NT+B6fBY34Af4DJbjRvwWn8NjuAnbk8fNGIJbcAQ+j6PwBSzAF/E6LMW5+BKuwpdxA76C23Erfo+v4s/4Gvr70naEXXAb9sA3cCxux3H4JqbgDpyJb+H9uBOXYxk+iLuwBHfjJnwXy3Av7sd9+D2+jz/jftmvlSbpv8IFcjwo9b9C6s0VrBeE47EbTsQIvFL281UYj/E4GRMxFZMwCyfhAkzGe3EyrsYpuA5T8T1Mk+MhAw+jGX/C6ehLurKxMeZgB8zDizBf9n8BjsGZWIBX47V4Hd6O1+M8nCX5LjRJ/xT6SL7Pkvs0ZXlGrmOexRDchHG4Ga/FLViIL+BcfBEfxlJ8HV/CN/EV3I1b8St8DY8h60j52/uQ6FtyLf/t8kz2DuyOb2NvLMMxuAsLcDfOwj14O76Lz+N7uBX34Uf4Pn6J+/FMIv0AG+FH2AM/xt74CU7AckzAz3Aqfo63YQU+hgfwCTyI6/Er3IWH8Wv8Fn3J03cYgJWS7zgfW78PdUDyTTnzey/1ziT1DrvhBIzAiSapdxiD8TgKEzAfE/E6nIRzMBkXYwo+iJPxVZyCOzAN9+JUfB+nYTmm4zeYiWfJs/490YyRmINDMBfHYR6mYj7m4AxcjVfj03gtPo/X4ad4PR7AQmV/4E14BG/BY3grBlEmt2Ew3o4d8Q4cinfiSJyPV2ERTsK7HOUr/UuUjU753u/DM/q4HIOxGEPxQbwQH8JofBgTcAVOxUdwOq7EIlyFS3A13ouP4gpcg4/hY7gBH8dD+CQewbX4O5ZgXdL0FDbBpzEC12Nf3IBD8Bkcjc/iBHwOk3ATzsQtOA+fx4fxBdyIL+JbWIof4Ev4Fb6Mv+Ar6KOcn7ENvoZ98HUcgNtwHL6BE3C7pN9skn4pXCi/t2dishy3b0n57sQOWIb9cBcOwt04DN/BSbgHr8Z38WZ8D+fgXpyP+yTeZsoxJPEOld/hKOt1hWX5S37XTb7kA3zwcqyD8eiLaeiHueiPc7Au3oWn4X0YgI/h6fgMnoEv4pn4FtbDj/As/ATrYwCJOhsbYAOMwIbYH5tgDAZiLDbFsXguJmNzNGMLvBFb4gJsjQ9hG9yBQfgztkXlPqod1sf22BaDsSN2wDDsiP0xBEdjZ0zEbpiO3XEhhuFG7IkvYjh+jr3wIJ6H5MXUGwMxEoPwAjwPL8SB2AenYl/Mwn54PfbHlXgRrsYo3InRWIaDcD8OwYN4MR7FS/BPHI4B7O8RGIiXYje8DMMxFq33B9IPhTt07g/GKOWEY7ELjsORGIdxeAXG43icgRNwHk7EJXglbsGr8GVMwNcxEaVdQfqCKFuddoVh1M+mOBw74wh1u4l8r6fO92LleyMxFEeh/Z2u8r1knXe6dpff8R7YG8NwAPbEIRiO47EXxmMEHsEEk/SZ4DrZ7uk4RrbbSuZMaa16p2tvbItXYDu8Btvj/RiMa7ADPoEdHXPsSF8I+rjOsXMe+WyJvbE3RuIleCEmYR/Mx75YhP1wBfbH5/AifAs=
*/