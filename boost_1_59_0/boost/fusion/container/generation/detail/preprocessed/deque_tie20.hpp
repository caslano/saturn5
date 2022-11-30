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
        struct deque_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct deque_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0&>
    deque_tie(T0 & arg0)
    {
        return deque<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct deque_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1&>
    deque_tie(T0 & arg0 , T1 & arg1)
    {
        return deque<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct deque_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return deque<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct deque_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return deque<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return deque<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* deque_tie20.hpp
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
*/